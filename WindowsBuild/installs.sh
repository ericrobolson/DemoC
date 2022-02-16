#
# Helper funcs
#

# Make directories
function dir (){
	[[ ! -d ${1} ]] && mkdir ${1}
}


#
# Directories
# 
CURRENT_DIR=$PWD
BIN=bin
BUILD=.build
INCLUDE=.include
INSTALLS=.installs
LIB=.lib

rm -rd $BUILD
rm -rd $INSTALLS
rm -rd $LIB
rm -rd $INCLUDE
rm -rd $BIN

dir $BUILD
dir $INSTALLS
dir $LIB
dir $INCLUDE
dir $BIN

#
# OS specific stuff
#
OS=undefined
if [[ "${OSTYPE}" == "cygwin" ]]; then
	OS=windows
else
	echo "Unknown OS '${OSTYPE}'"
	exit 1
fi


function installSdl(){
	cd $CURRENT_DIR

	if [[ "$OS" == "windows" ]]; then
		# Download + extract
		FILE=SDL2-devel.tar.gz
		curl https://www.libsdl.org/release/SDL2-devel-2.0.20-mingw.tar.gz --output SDL2-devel.tar.gz
		tar -xf $FILE -C $BUILD
		mv -T $BUILD/SDL2-* $BUILD/SDL2

		# Copy files to where they need to go
		SDL2=$BUILD/SDL2
		src=$SDL2/x86_64-w64-mingw32

		

		# Headers
		dir $INCLUDE/SDL2
		cp -r $src/include/SDL2/ $INCLUDE/

		# Library
		cp -r $src/lib/. $LIB

		# binary
		cp $src/bin/SDL2.dll $BIN

		# Readme - do this on all installs
		cp $SDL2/README-SDL.txt $BIN
	else 
		echo "TODO: sdl2 on $OS"
		exit 1
	fi
}


installSdl
