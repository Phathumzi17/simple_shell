#include "shell.h"

/**
 * get_length - Counts the number of nodes in a linked list.
 * @h: Pointer to the first node of the list.
 *
 * Return: The number of nodes in the list.
 */
size_t get_length(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		h = h->next;
		count++;
	}
	return (count);
}

/**
 * list_to_strings - Converts a linked list of strings into an array of strings.
 * @head: Pointer to the first node of the list.
 *
 * Return: Pointer to an array of strings.
 */
char **list_to_strings(list_t *head)
{
	list_t *current = head;
	size_t size = get_length(head), index;
	char **strings_array;
	char *string;

	if (!head || !size)
		return (NULL);
	strings_array = malloc(sizeof(char *) * (size + 1));
	if (!strings_array)
		return (NULL);
	for (index = 0; current; current = current->next, index++)
	{
		string = malloc(_strlen(current->str) + 1);
		if (!string)
		{
			for (size_t j = 0; j < index; j++)
				free(strings_array[j]);
			free(strings_array);
			return (NULL);
		}

		string = _strcpy(string, current->str);
		strings_array[index] = string;
	}
	strings_array[index] = NULL;
	return (strings_array);
}

/**
 * print_list - Prints all elements of a linked list.
 * @h: Pointer to the first node of the list.
 *
 * Return: The size of the list.
 */
size_t print_list(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		count++;
	}
	return (count);
}

/**
 * find_node_starts_with - Returns the node whose string starts with a given prefix.
 * @node: Pointer to the head of the list.
 * @prefix: Prefix to match.
 * @c: The next character after the prefix to match.
 *
 * Return: The matching node or NULL if not found.
 */
list_t *find_node_starts_with(list_t *node, char *prefix, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = starts_with(node->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Gets the index of a node in a linked list.
 * @head: Pointer to the head of the list.
 * @node: Pointer to the node.
 *
 * Return: The index of the node or -1 if not found.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}
