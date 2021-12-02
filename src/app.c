#include "g_file.h"
#include "s7.h"
#include "utest.h"
#include "utf8.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUILT_IN_LOAD "load"

#define VAR_HOT_RELOAD "gsys-hot-reload"
#define VAR_QUIT "gsys-quit"
#define VAR_REPL "gsys-repl"

void load_script(s7_scheme *s7, const char *str_init_script, const size_t script_bytes)
{
	if (s7 != NULL && str_init_script != NULL && script_bytes > 0)
	{
		s7_load_c_string(s7, str_init_script, (s7_int)script_bytes);
	}
}

/// Loads a module (another Scheme file).
static s7_pointer built_in_load(s7_scheme *s7, s7_pointer args)
{
	// Check first arg is string
	// If so then attempt to load module
	if (s7_is_string(s7_car(args)))
	{
		s7_pointer s7_str =
			s7_car(args);

		const char *str = s7_string(s7_str);

		struct GFile script = g_file_load(str);
		if (script.success)
		{
			load_script(s7, script.contents, script.size);
		}
		else
		{
			printf("error loading %s/n", str);
		}
		g_file_close(script);

		return s7_str;
	}
	else
	{
		return (s7_wrong_type_arg_error(s7, "module", 1, s7_car(args), "a string"));
	}
}

/// Sets the given name in the environment
void set_bool(s7_scheme *s7, const char *name, bool value)
{
	s7_define_variable(s7, name, s7_make_boolean(s7, value));
}

void define_engine_methods(s7_scheme *s7)
{
	if (!s7)
	{
		return;
	}

	s7_define_function(s7, BUILT_IN_LOAD, built_in_load, 1, 0, false, "(load module-name) loads a module");
}

s7_scheme *init_scheme(const char *str_init_script, const size_t script_bytes)
{
	// Init Scheme
	s7_scheme *s7;
	s7 = s7_init();

	// Set values
	set_bool(s7, VAR_HOT_RELOAD, false);
	set_bool(s7, VAR_QUIT, false);
	set_bool(s7, VAR_REPL, false);

	// Define built in methods
	define_engine_methods(s7);

	// Load script

	load_script(s7, str_init_script, script_bytes);

	return s7;
}

void execute_repl(s7_scheme *s7)
{
	if (!s7)
	{
		return;
	}

	char buffer[512];
	char response[1024];

	// Get input
	fprintf(stdout, "\n> ");
	fgets(buffer, 512, stdin);

	// Eval input
	if ((buffer[0] != '\n') ||
		(strlen(buffer) > 1))
	{
		snprintf(response, 1024, "(write %s)", buffer);
		s7_eval_c_string(s7, response);
	}

	printf("\n");
}

struct GFile try_load_main(const bool debug_log)
{
	// Load script
	struct GFile script;
	script = g_file_load("./main.scm");
	if (script.success && debug_log)
	{
		printf("-------\nContents\n-------\n\n%s\n-------\nEnd Contents\n-------\n", script.contents);
	}

	return script;
}

bool get_var_bool(s7_scheme *s7, const char *name)
{
	s7_pointer var = s7_name_to_value(s7, name);
	if (s7_is_boolean(var))
	{
		return s7_boolean(s7, var);
	}

	printf("variable '%s' should be #t or #f\n", name);
	return false;
}

int app()
{
	// Init interpreter
	struct GFile script = try_load_main(true);
	s7_scheme *s7 = init_scheme(script.contents, script.size);
	g_file_close(script);

	// Init system vars
	bool hot_reload = get_var_bool(s7, VAR_HOT_RELOAD);
	bool quit = get_var_bool(s7, VAR_QUIT);
	bool repl = get_var_bool(s7, VAR_REPL);

	// Main loop
	while (quit != true)
	{
		// Potentially run repl
		if (repl)
		{
			execute_repl(s7);
		}

		// Source variables
		hot_reload = get_var_bool(s7, VAR_HOT_RELOAD);
		quit = get_var_bool(s7, VAR_QUIT);
		repl = get_var_bool(s7, VAR_REPL);

		// Reload scripts
		if (hot_reload)
		{

			struct GFile script = try_load_main(false);
			if (script.success)
			{

				load_script(s7, script.contents, script.size);
			}
			else
			{
				printf("Didn't reload script\n");
			}

			g_file_close(script);
		}
	}

	s7_free(s7);

	return 0;
}
