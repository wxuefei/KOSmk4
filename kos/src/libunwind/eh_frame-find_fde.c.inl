/* Copyright (c) 2019-2020 Griefer@Work                                       *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "eh_frame.c"
#define FIND_SPECIFIC_ADDRESS 1
#endif

#include <string.h>
#include <kos/kernel/types.h>
#include <hybrid/overflow.h>

DECL_BEGIN


#ifndef FIND_SPECIFIC_ADDRESS
/* Load the next_chunk eh_frame function descriptor from `*peh_frame_reader', which
 * must either be a pointer to the start of the `.eh_frame' section, to be the
 * value written back to `*peh_frame_reader' after a previous call to `unwind_fde_load()'.
 * @return: UNWIND_SUCCESS:  Successfully read the next FDE entry.
 * @return: UNWIND_NO_FRAME: Failed to read an FDE entry (Assume EOF) */
INTERN NONNULL((1, 2, 3)) unsigned int
NOTHROW_NCX(CC libuw_unwind_fde_load)(byte_t **__restrict peh_frame_reader,
                                      byte_t *__restrict eh_frame_end,
                                      unwind_fde_t *__restrict result,
                                      uint8_t sizeof_address)
#else /* !FIND_SPECIFIC_ADDRESS */
/* Same as `unwind_fde_load()', but quickly search for and return the
 * FDE descriptor containing the given `absolute_pc' text address.
 * @return: UNWIND_SUCCESS:  Found the FDE entry associated with `ABSOLUTE_PC'.
 * @return: UNWIND_NO_FRAME: Failed to read an FDE entry (Assume EOF) */
INTERN NONNULL((1, 2, 4)) unsigned int
NOTHROW_NCX(CC libuw_unwind_fde_scan)(byte_t *__restrict reader,
                                      byte_t *__restrict eh_frame_end,
                                      void *absolute_pc,
                                      unwind_fde_t *__restrict result,
                                      uint8_t sizeof_address)
#endif /* FIND_SPECIFIC_ADDRESS */
{
#ifndef FIND_SPECIFIC_ADDRESS
	byte_t *eh_frame_start = *peh_frame_reader;
	byte_t *reader         = eh_frame_start;
#else /* !FIND_SPECIFIC_ADDRESS */
	byte_t *eh_frame_start = reader;
#endif /* !FIND_SPECIFIC_ADDRESS */
	byte_t *next_chunk;
	byte_t *cie_reader, *fde_reader;
	size_t length;
	uint32_t cie_offset;
	uint8_t enclsda;
	char *cie_augstr;
	struct CIE *cie;
again:
	if (reader >= eh_frame_end)
		ERROR(err_noframe);
	length = (size_t)UNALIGNED_GET((uint32_t *)reader);
	reader += 4;
	if unlikely((uint32_t)length == (uint32_t)-1) {
#if __SIZEOF_POINTER__ > 4
		length = (size_t) * (u64 *)reader;
		reader += 8;
#else /* __SIZEOF_POINTER__ > 4 */
		ERROR(err_noframe); /* Too large. Impossible to represent. */
#endif /* __SIZEOF_POINTER__ <= 4 */
	}
	if unlikely(!length)
		ERROR(err_noframe);
	next_chunk = reader + length;
	cie_offset = *(uint32_t *)reader; /* f_cieptr */
	if (cie_offset == 0)
		goto do_next_chunk; /* This is a CIE, not an FDE */
	cie        = (struct CIE *)(reader - cie_offset);
	fde_reader = reader + 4;
	if unlikely(!((byte_t *)cie >= eh_frame_start &&
	              (byte_t *)cie < eh_frame_end))
		ERRORF(err_noframe, "cie=%p, eh_frame_start=%p, eh_frame_end=%p",
		       cie, eh_frame_start, eh_frame_end);
	/* Load the augmentation string of the associated CIE. */
	cie_reader = (byte_t *)cie;
	cie_reader += 4; /* c_length */
	if (UNALIGNED_GET(&((uint32_t *)cie_reader)[-1]) == (uint32_t)-1) {
#if __SIZEOF_POINTER__ > 4
		cie_reader += 8; /* c_length64 */
#else /* __SIZEOF_POINTER__ > 4 */
		goto do_next_chunk;
#endif /* __SIZEOF_POINTER__ <= 4 */
	}
	cie_reader += 4; /* c_cieid */
	cie_reader += 1; /* c_version */
	cie_augstr = (char *)cie_reader;
	cie_reader = (byte_t *)strend(cie_augstr) + 1;
	/* Read code and data alignments. */
	result->f_codealign = dwarf_decode_uleb128(&cie_reader); /* c_codealignfac */
	result->f_dataalign = dwarf_decode_sleb128(&cie_reader); /* c_dataalignfac */
	result->f_retreg    = (unwind_regno_t)dwarf_decode_uleb128(&cie_reader); /* c_returnreg */
	/* Pointer encodings default to ZERO(0). */
	result->f_encptr   = 0;
	enclsda            = 0;
	result->f_sigframe = 0;
	/* No personality function by default. */
	result->f_persofun = 0;
	result->f_lsdaaddr = 0;
	if (cie_augstr[0] == 'z') {
		char *aug_iter = cie_augstr;
		/* Interpret the augmentation string. */
		uintptr_t aug_length;
		byte_t *aug_end;
		aug_length = dwarf_decode_uleb128(&cie_reader); /* c_auglength */
		aug_end    = cie_reader + aug_length;
		if unlikely(aug_end < cie_reader || aug_end > eh_frame_end) {
			/* Check for overflow/underflow. */
			ERRORF(err_noframe, "cie_reader=%p, aug_end=%p, eh_frame_end=%p",
			       cie_reader, aug_end, eh_frame_end);
		}
		while (*++aug_iter && cie_reader < aug_end) {
			if (*aug_iter == 'L') {
				enclsda = *cie_reader++;
			} else if (*aug_iter == 'P') {
				uint8_t encperso;
				encperso = *cie_reader++;
				result->f_persofun = (void *)dwarf_decode_pointer(&cie_reader,
				                                                  encperso,
				                                                  sizeof_address,
				                                                  0,
				                                                  0,
				                                                  0);
			} else if (*aug_iter == 'R') {
				result->f_encptr = *cie_reader++;
			} else {
				/* XXX: What then? */
			}
		}
		/* `aug_end' now points at `c_initinstr' */
		cie_reader = aug_end;
	}
	result->f_pcstart = (void *)dwarf_decode_pointer(&fde_reader,
	                                                 result->f_encptr,
	                                                 sizeof_address,
	                                                 0,
	                                                 0,
	                                                 0);
	result->f_pcend = (void *)dwarf_decode_pointer(&fde_reader,
	                                               result->f_encptr & 0xf,
	                                               sizeof_address,
	                                               0,
	                                               0,
	                                               (uintptr_t)result->f_pcstart);
	if (OVERFLOW_UADD((uintptr_t)result->f_pcstart,
	                  (uintptr_t)result->f_pcend,
	                  (uintptr_t *)&result->f_pcend))
		goto do_next_chunk;
#ifdef FIND_SPECIFIC_ADDRESS
	/* Check of the CIE points to the proper bounds. */
	if (absolute_pc < result->f_pcstart)
		goto do_next_chunk;
	if (absolute_pc >= result->f_pcend)
		goto do_next_chunk;
#endif /* FIND_SPECIFIC_ADDRESS */
	/* Found it! - Save the pointer to the initial instruction set. */
	result->f_inittext = cie_reader;
	/* Figure out the max length of that instruction set. */
	cie_reader = (byte_t *)cie;
	length     = UNALIGNED_GET((uint32_t *)cie_reader);
	cie_reader += 4;
#if __SIZEOF_POINTER__ > 4
	/* Above code already asserted that the length fits into 32 bits of the CIE. */
	if unlikely((uint32_t)length == (uint32_t)-1) {
		length = (size_t) * (u64 *)reader;
		reader += 8;
	}
#endif /* __SIZEOF_POINTER__ > 4 */
	cie_reader += length;
	result->f_inittextend = cie_reader;
	/* Parse augmentation data of the FDE. */
	if (cie_augstr[0] == 'z') {
		uintptr_t aug_length;
		byte_t *aug_end;
		aug_length = dwarf_decode_uleb128(&fde_reader); /* c_auglength */
		aug_end    = fde_reader + aug_length;
		while (*++cie_augstr && fde_reader <= aug_end) {
			if (*cie_augstr == 'L') {
				if unlikely(fde_reader == aug_end)
					break;
				result->f_lsdaaddr = (void *)dwarf_decode_pointer(&fde_reader,
				                                                  enclsda,
				                                                  sizeof_address,
				                                                  0,
				                                                  0,
				                                                  (uintptr_t)result->f_pcstart);
			} else if (*cie_augstr == 'S') {
				result->f_sigframe = 1;
			}
		}
		fde_reader = aug_end;
	}
	result->f_evaltext    = fde_reader;
	result->f_evaltextend = next_chunk;
	result->f_addrsize    = sizeof_address;
#ifndef FIND_SPECIFIC_ADDRESS
	*peh_frame_reader = next_chunk;
#endif /* FIND_SPECIFIC_ADDRESS */
	return UNWIND_SUCCESS;
do_next_chunk:
	if unlikely(next_chunk < reader) {
		/* Underflow */
		ERRORF(err_noframe, "next_chunk=%p, reader=%p", next_chunk, reader);
	}
	reader = next_chunk;
	goto again;
err_noframe:
	return UNWIND_NO_FRAME;
}
#undef FIND_SPECIFIC_ADDRESS

DECL_END
