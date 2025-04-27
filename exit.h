#include "shell.h"

/**
 * check_exit_builtin - Checks if the input command is
 * "exit" and exits the shell.
 * @input: The input string from the user (already trimmed).
 * @ctx: Pointer to the shell context structure containing state variables.
 */
void check_exit_builtin(char *input, shell_ctx_t *ctx)
{
	if (input == NULL)
		return;

	if (strncmp(input, "exit", 4) == 0)
	{
		if (ctx->input_line != NULL)
		{
			free(ctx->input_line);
			ctx->input_line = NULL;
		}
		exit(ctx->exit_status);
	}
}
