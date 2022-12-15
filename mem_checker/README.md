# mem_checker

A collection of code and macros that allow tracing for memory de/allocation.

Code in `core_mem.h` and `core.h` to replace `malloc` and `free` with calls that log out the line number and file then call the respective code.
