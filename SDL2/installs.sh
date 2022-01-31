MAIN_DIR=${PWD}
INSTALL=.installs
BUILD=.build

echo "$MAIN_DIR"

function installThis() {
    echo "Did you install this: ${1}"
    read INPUT
}

installThis "Are you in sudo?"

# Make installs
[ -d $INSTALL ] && mkdir $INSTALL
[ -d $BUILD ] && mkdir $BUILD

## Do OS specific things
OS=UNKNOWN
if [[ "$OSTYPE" == "darwin"* ]]; then
    OS=MAC
    brew install clang
    brew install cmake
else
    echo "Unknown OS: $OSTYPE"
    return 1
fi

## Install SDL2
cd $INSTALL
git clone https://github.com/libsdl-org/SDL.git
cd SDL
./configure; make; make install
cd $MAIN_DIR

## Install GLFW
cd $INSTALL
git clone https://github.com/glfw/glfw
cd $MAIN_DIR
cmake -S $INSTALL/glfw -B $BUILD/glfw
cd $BUILD/glfw
make
cd $MAIN_DIR
