#include <stdbool.h>
#include <stddef.h>

struct GFile
{
	bool success;
	char *contents;
	size_t size;
};

/// Attempts to load the given file.
struct GFile g_file_load(const char filename_literal[]);

/// Closes the given file.
void g_file_close(struct GFile file);
