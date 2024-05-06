#include "shell.h"

/**
 * printEnvironment - Print the current environment
 * @data: Structure containing potential arguments
 * 
 * Returns: Always 0
 */
int printEnvironment(data_t *data)
{
	printListString(data->environment);
	return (0);
}

/**
 * getEnvironmentVariable - Get the value of an environment variable
 * @data: Structure containing potential arguments
 * @name: Environment variable name
 * 
 * Returns: The value
 */
char *getEnvironmentVariable(data_t *data, const char *name)
{
	list_t *node = data->environment;
	char *ptr;

	while (node)
	{
		ptr = startsWith(node->str, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * initializeEnvironmentVariable - Initialize a new environment variable,
 *                                  or modify an existing one
 * @data: Structure containing potential arguments
 * 
 * Returns: Always 0
 */
int initializeEnvironmentVariable(data_t *data)
{
	if (data->argumentCount != 3)
	{
		errorPrint("Incorrect number of arguments\n");
		return (1);
	}
	if (setEnvironmentVariable(data, data->argumentVector[1], data->argumentVector[2]))
		return (0);
	return (1);
}

/**
 * removeEnvironmentVariable - Remove an environment variable
 * @data: Structure containing potential arguments
 * 
 * Returns: Always 0
 */
int removeEnvironmentVariable(data_t *data)
{
	int i;

	if (data->argumentCount == 1)
	{
		errorPrint("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= data->argumentCount; i++)
		unsetEnvironmentVariable(data, data->argumentVector[i]);

	return (0);
}

/**
 * populateEnvironmentList - Populate the environment linked list
 * @data: Structure containing potential arguments
 * 
 * Returns: Always 0
 */
int populateEnvironmentList(data_t *data)
{
	list_t *node = NULL;
	size_t index;

	for (index = 0; environ[index]; index++)
		addNodeEnd(&node, environ[index], 0);
	data->environment = node;
	return (0);
}
