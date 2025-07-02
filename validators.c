#include "shell.h"

/**
 * validate_input - Validate if PATH exists
 * @arguments: String of tokens
 * @argv: String of arguments from input
 * Return: A pointer to an array of the tokenized PATH directories
 **/
char *validate_input(char **arguments, char **argv __attribute__((unused)))
{
	char *new_arguments, *first, *slash_argument = "/";
	char **tokens_path, holder_env[1024];
	int i = 0;

	if (arguments[0][0] == '/' || arguments[0][0] == '.')
	{
		new_arguments = arguments[0];
		if ((access(new_arguments, F_OK) == -1))
		{
			fprintf(stderr, "%s: No such file or directory\n", arguments[0]);
			return ("Fail access");
		}
	}
	else
	{
		strcpy(holder_env, getenv("PATH"));
		tokens_path = tokenizer_path(holder_env);
		while (tokens_path[i])
		{

			first = str_concat(slash_argument, arguments[0]);
			new_arguments = str_concat(tokens_path[i], first);
			if ((access(new_arguments, F_OK) == -1))
			{
				free(new_arguments);
				free(first);
			}
			else
			{
				free(tokens_path);
				free(first);
				return (new_arguments);
			}
			i++;
		}
		free(tokens_path);
		fprintf(stderr, "%s: No such file or directory\n", arguments[0]);
		return ("Fail access");
	}
	return (new_arguments);
}

/**
 * validate_spaces - Validate spaces, tabs and line breaks
 * @input: String from input
 * Return: 0 if not find spaces, tabs or line break
 */
int validate_spaces(char *input)
{
	int i = 0, flag = 1, len = 0;

	len = strlen(input);

	while (input[i] == ' ' || input[i] == '\n' || input[i] == '\t')
		i++;

	if (i != len)
		flag = 0;
	return (flag);
}
