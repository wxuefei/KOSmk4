# Copyright (c) 2019-2020 Griefer@Work
#
# This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgement (see the following) in the product
#    documentation is required:
#    Portions Copyright (c) 2019-2020 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

# depends: libzlib

# xorg-macros
. "$KOS_MISC/utilities/misc/xorg-macros.sh"

VERSION="0.16"
SO_VERSION_MAJOR="0"
SO_VERSION="$SO_VERSION_MAJOR.11.1"
COMMIT="fbd1f0fe79ba25b72635f8e36a6c33d7e0ca19f6"

SRCPATH="$KOS_ROOT/binutils/src/x/libpciaccess-$VERSION"
OPTPATH="$BINUTILS_SYSROOT/opt/x/libpciaccess-$VERSION"

# libpciaccess
if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/src/.libs/libpciaccess.so.$SO_VERSION" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			if ! [ -f "$SRCPATH/configure.ac" ]; then
				cmd rm -rf "$SRCPATH"
				cmd cd "$KOS_ROOT/binutils/src/x"
				cmd git clone "https://gitlab.freedesktop.org/xorg/lib/libpciaccess"
				cmd mv "libpciaccess" "libpciaccess-$VERSION"
				cmd cd "$SRCPATH"
				cmd git checkout -f "$COMMIT"
			fi
			cmd cd "$SRCPATH"
			apply_patch \
				"$SRCPATH" \
				"$KOS_PATCHES/libpciaccess-$VERSION.patch"
			cmd aclocal
			cmd autoreconf -i
			cmd autoconf
		fi
		cmd rm -rf "$OPTPATH"
		cmd mkdir -p "$OPTPATH"
		cmd cd "$OPTPATH"
		(
			export CC="${CROSS_PREFIX}gcc"
			export CPP="${CROSS_PREFIX}cpp"
			export CFLAGS="-ggdb"
			export CXX="${CROSS_PREFIX}g++"
			export CXXCPP="${CROSS_PREFIX}cpp"
			export CXXFLAGS="-ggdb"
			cmd bash "../../../../src/x/libpciaccess-$VERSION/configure" \
				--prefix="/" \
				--exec-prefix="/" \
				--bindir="/bin" \
				--sbindir="/bin" \
				--libexecdir="/libexec" \
				--sysconfdir="/etc" \
				--sharedstatedir="/usr/com" \
				--localstatedir="/var" \
				--runstatedir="/var/run" \
				--libdir="/$TARGET_LIBPATH" \
				--includedir="/usr/include" \
				--oldincludedir="/usr/include" \
				--datarootdir="/usr/share" \
				--datadir="/usr/share" \
				--infodir="/usr/share/info" \
				--localedir="/usr/share/locale" \
				--mandir="/usr/share/man" \
				--docdir="/usr/share/doc/libpciaccess" \
				--htmldir="/usr/share/doc/libpciaccess" \
				--dvidir="/usr/share/doc/libpciaccess" \
				--pdfdir="/usr/share/doc/libpciaccess" \
				--psdir="/usr/share/doc/libpciaccess" \
				--build="$(gcc -dumpmachine)" \
				--host="$TARGET_NAME-linux-gnu" \
				--enable-shared \
				--enable-linux-rom-fallback \
				--with-gnu-ld \
				--with-pciids-path="/usr/share/hwdata" \
				--with-zlib
		) || exit $?
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

# Install the PKG_CONFIG file
#     The make process above will have already created that file
#     under "$OPTPATH/pciaccess.pc", however we don't actually want
#     to use that one since it contains the lines:
#     >> includedir=/usr/include
#     >> Cflags: -I${includedir}
#     Which in combination would cause the ~real~ system include
#     path to be added to include path, so we need to edit the file
if ! [ -f "$PKG_CONFIG_PATH/pciaccess.pc" ]; then
	cmd mkdir -p "$PKG_CONFIG_PATH"
	cat > "$PKG_CONFIG_PATH/pciaccess.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: pciaccess
Description: Library providing generic access to the PCI bus and devices.
Version: $VERSION
Cflags:
Libs: -lpciaccess
EOF
fi

# Install libraries
install_file /$TARGET_LIBPATH/libpciaccess.so.$SO_VERSION_MAJOR "$OPTPATH/src/.libs/libpciaccess.so.$SO_VERSION"
install_symlink /$TARGET_LIBPATH/libpciaccess.so.$SO_VERSION libpciaccess.so.$SO_VERSION_MAJOR
install_symlink /$TARGET_LIBPATH/libpciaccess.so libpciaccess.so.$SO_VERSION_MAJOR
install_file_nodisk /$TARGET_LIBPATH/libpciaccess.a "$OPTPATH/src/.libs/libpciaccess.a"

install_file /bin/scanpci "$OPTPATH/scanpci/.libs/scanpci"

# Install headers
install_rawfile "$KOS_ROOT/kos/include/pciaccess.h" "$SRCPATH/include/pciaccess.h"

