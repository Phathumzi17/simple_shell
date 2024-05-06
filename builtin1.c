#include "shell.h"

/**
 * displayHistory - Display the history list, one command per line, preceded
 *                  by line numbers, starting at 0.
 * @data: Structure containing potential arguments
 * 
 * Returns: Always 0
 */
int displayHistory(data_t *data)
{
	printList(data->history);
	return (0);
}

/**
 * unsetAlias - Remove an alias
 * @data: Structure containing potential arguments
 * @str: The alias string
 * 
 * Returns: Always 0 on success, 1 on error
 */
int unsetAlias(data_t *data, char *str)
{
	char *ptr, c;
	int result;

	ptr = findCharacter(str, '=');
	if (!ptr)
		return (1);
	c = *ptr;
	*ptr = 0;
	result = deleteNodeAtIndex(&(data->alias),
		getNodeIndex(data->alias, nodeStartsWith(data->alias, str, -1)));
	*ptr = c;
	return (result);
}

/**
 * setAlias - Set an alias
 * @data: Structure containing potential arguments
 * @str: The alias string
 * 
 * Returns: Always 0 on success, 1 on error
 */
int setAlias(data_t *data, char *str)
{
	char *ptr;

	ptr = findCharacter(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unsetAlias(data, str));

	unsetAlias(data, str);
	return (addNodeEnd(&(data->alias), str, 0) == NULL);
}

/**
 * printAlias - Print an alias string
 * @node: The alias node
 * 
 * Returns: Always 0 on success, 1 on error
 */
int printAlias(list_t *node)
{
	char *ptr = NULL, *alias = NULL;

	if (node)
	{
		ptr = findCharacter(node->str, '=');
		for (alias = node->str; alias <= ptr; alias++)
			putCharacter(*alias);
		putCharacter('\'');
		printString(ptr + 1);
		printString("'\n");
		return (0);
	}
	return (1);
}

/**
 * manageAlias - Mimics the alias built-in command
 * @data: Structure containing potential arguments
 * 
 * Returns: Always 0
 */
int manageAlias(data_t *data)
{
	int i = 0;
	char *ptr = NULL;
	list_t *node = NULL;

	if (data->argumentCount == 1)
	{
		node = data->alias;
		while (node)
		{
			printAlias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; data->argumentVector[i]; i++)
	{
		ptr = findCharacter(data->argumentVector[i], '=');
		if (ptr)
			setAlias(data, data->argumentVector[i]);
		else
			printAlias(nodeStartsWith(data->alias, data->argumentVector[i], '='));
	}

	return (0);
}
