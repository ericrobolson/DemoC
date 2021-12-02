## Welcome
This is a simple C program that runs a Scheme interpreter. It could be a good starting point for a new program or application.

## Installations:
* Windows - `sh _setup/windows.sh`
* Linux - `sh _setup/linux.sh`
* Mac - `sh _setup/mac_m1.sh`

## Make Commands:
* `make clean_all` - Cleans all files
* `make clean` - Cleans all binaries and obj files
* `make copy_res` - Copies all assets
* `make run` - Builds and runs the program
* `make test` - Builds + executes tests using [utest.h](https://github.com/sheredom/utest.h)
* `make` - Builds the program

## Architecture
* `include/` - Header files
* `res/` - Asset files + scripts
* `src_extern` - 3rd party source files, not held to strict warnings
* `src/` -  My source files

## External Libs
### External libs should be header only, or at most 2 files. This is to make it more cross platform.
* [S7 Scheme](https://ccrma.stanford.edu/software/snd/snd/s7.html) is used for a scripting language
* [utest.h](https://github.com/sheredom/utest.h) for unit testing
* [utf8.h](https://github.com/sheredom/utf8.h) for strings

## Roadmap:
- [x] Integrate Duktape
- [x] Integrate Makefile
- [x] Integrate test.h
- [x] Integrate [S7](https://ccrma.stanford.edu/software/snd/snd/s7.html)
- [x] Uninstall cygwin
- [x] Install gcc using mingw using chocolatey
- [x] Get a simple setup script for Windows
- [x] Get app cross compiling on Linux, Mac + Windows
- [x] Added copying of `res/`
- [x] Implement barebones file loading
### Scheme
- [x] Implement loading of script for Scheme
- [x] Implement 'quit' method in Scheme.
- [x] Implement file loading
- [x] Implement hot reloading of Scheme (https://c-for-dummies.com/blog/?p=3004)
- [x] Implement a C function that is called in Scheme
- [x] Figure out why windows behaves differently with \r\n vs linux with \r\n?
- [x] Figure out bug with Windows calling weird shit in CLI when loading Scheme file.
- [x] Implement a 'modules' C method which takes other Scheme modules to load into the environment. 'modules' is a C function that loads other .scm files. Ensure that this works when passed a garbage file, a non-existant file, and a badly written file. Test on all platforms.
- [x] Rename 'module' to 'load' to match Scheme/Common Lisp

## Nuklear + GFX
- [ ] Checkout this tutorial: https://github.com/whkelvin/Nuklear_gui_with_glfw-glad-opengl
## Profiling 
- [ ] Implement a new make target `make profile`, [following this comment's tips](https://stackoverflow.com/a/1794846)

## Hotreloading contd.
- [ ] Add file watcher to copy res whenever a file changes. Perhaps it runs rsync in the background?

### Rest of roadmap
- [ ] Integrate [Sokol](https://github.com/floooh/sokol) or SDL2. [Sokol tutorials](https://www.geertarien.com/learnopengl-examples-html5/)
- [ ] Integrate Nuklear
- [ ] Implement building for Web using Emscripten?
- [ ] Implement building for Android
- [ ] Implement building for iOS
- [ ] Add in simple threading lib
- [ ] Idea for GUI: https://news.ycombinator.com/item?id=22977095
