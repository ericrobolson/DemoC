#include "g_file.h"
#include "g_free.h"
#include "g_malloc.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>

struct GFile g_file_load(const char file_name[])
{
	struct GFile f;
	f.success = false;
	f.size = 0;
	f.contents = NULL;

	// Flags to use. 'r' for reading, 'b' for binary. The 'b' removes the \r\n issue with windows + linux.

	FILE *file;
	file = fopen(file_name, "rb");

	if (errno != 0)
	{
		printf("fopen() failed: Attempted to read file: %s\n", file_name);
		printf("File error: %s\n", strerror(errno));
	}
	else
	{

		if (file)
		{
			fseek(file, 0, SEEK_END);
			long fsize = ftell(file);
			rewind(file);

			char *string = g_malloc(fsize + 1);
			string[fsize] = 0;

			fread(string, 1, fsize, file);
			fclose(file);

			f.contents = string;
			f.success = true;
			f.size = fsize;
		}
	}

	return f;
}

void g_file_close(struct GFile file)
{
	if (file.contents)
	{
		g_free(file.contents);
	}
}
