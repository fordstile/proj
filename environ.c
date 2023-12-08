#include "shell.h"

/**
 * printCurrentEnvironment - Prints the current environment.
 * @infos: Struct containing arguments, used to maintain const func prototype.
 *
 * Return: Always 0.
 */
int printCurrentEnvironment(info_t *infos)
{
	print_list_str(infos->env);
	return (0);
}

/**
 * initializeOrModifyEnvVar - Initializes a new environment variable
 * or modifies an existing one.
 * @infos: Struct containing arguments, used to maintain const func prototype.
 *
 * Return: Always 0.
 */
int initializeOrModifyEnvVar(info_t *infos)
{
	if (infos->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}

	if (_setenv(infos, infos->argv[1], infos->argv[2]))
		return (0);

	return (1);
}

/**
 * getEnvVarValue - Gets the value of an environment variable.
 * @infos: Struct containing arguments, used to maintain.
 * @names: Environment variable name.
 *
 * Return: Value of the environment variable.
 */
char *getEnvVarValue(info_t *infos, const char *names)
{
	list_t *currentNode = infos->env;
	char *position;

	while (currentNode)
	{
		position = starts_with(currentNode->str, names);
		if (position && *position)
			return (position);
		currentNode = currentNode->next;
	}

	return (NULL);
}

/**
 * populateEnvList - Populates the environment linked list.
 * @info: Struct containing arguments, used to maintain const func prototype.
 *
 * Return: Always 0.
 */
int populateEnvList(info_t *info)
{
	list_t *node = NULL;
	size_t index;

	for (index = 0; environ[index]; index++)
		add_node_end(&node, environ[index], 0);

	info->env = node;
	return (0);
}

/**
 * removeEnvVar - Removes an environment variable.
 * @infos: Struct containing arguments, used to maintain const func prototype.
 *
 * Return: Always 0.
 */
int removeEnvVar(info_t *infos)
{
	int index;

	if (infos->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}

	for (index = 1; index <= infos->argc; index++)
		_unsetenv(infos, infos->argv[index]);

	return (0);
}

