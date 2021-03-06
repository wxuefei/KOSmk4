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

SRCPATH="$KOS_ROOT/binutils/src/deemon-git/deemon"
if ! [ -f "$SRCPATH/configure" ]; then
	rm -rf "$KOS_ROOT/binutils/src/deemon-git" > /dev/null 2>&1
	cmd mkdir -p "$KOS_ROOT/binutils/src/deemon-git"
	cmd cd "$KOS_ROOT/binutils/src/deemon-git"
	cmd git clone "https://github.com/GrieferAtWork/deemon.git"
fi

cmd cd "$SRCPATH"
DEEMON_VERSION=$(git rev-parse HEAD)
OPTPATH="$BINUTILS_SYSROOT/opt/deemon-git-$DEEMON_VERSION"

if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/deemon" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		rm -rf "$OPTPATH" > /dev/null 2>&1
		mkdir -p "$OPTPATH"
		cmd cd "$OPTPATH"
		cmd bash "$SRCPATH/configure" \
			--cross-prefix="$CROSS_PREFIX" \
			--config-exe-extension="" \
			--config-dll-extension=".so" \
			--with-deemon-home="/usr/$TARGET_LIBPATH/deemon" \
			--with-deemon-path="/usr/$TARGET_LIBPATH/deemon" \
			--config-pthread=""
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

install_file /bin/deemon "$OPTPATH/deemon"

# install dex modules
for filename in $OPTPATH/lib/*.so; do
	install_file "/usr/$TARGET_LIBPATH/deemon/$(basename -- "$filename")" "$filename"
done

# install user-code modules
for filename in $SRCPATH/lib/*.dee; do
	install_file "/usr/$TARGET_LIBPATH/deemon/$(basename -- "$filename")" "$filename"
done

for folder in _codecs net python rt; do
	for filename in $SRCPATH/lib/$folder/*.dee; do
		install_file "/usr/$TARGET_LIBPATH/deemon/$folder/$(basename -- "$filename")" "$filename"
	done
done
