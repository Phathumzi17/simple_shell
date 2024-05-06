#include "shell.h"

/**
 * printErrorMessage - Prints an error message
 * @message: The error message to be printed
 * 
 * Return: Nothing
 */
void printErrorMessage(char *message)
{
	int index = 0;

	if (!message)
		return;
	while (message[index] != '\0')
	{
		writeCharacter(message[index]);
		index++;
	}
}

/**
 * writeCharacter - Writes the character to stderr
 * @c: The character to print
 * 
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int writeCharacter(char c)
{
	static int index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || index >= WRITE_BUFFER_SIZE)
	{
		write(2, buffer, index);
		index = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[index++] = c;
	return (1);
}

/**
 * writeCharacterToFileDescriptor - Writes the character to given file descriptor
 * @c: The character to print
 * @fd: The file descriptor to write to
 * 
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int writeCharacterToFileDescriptor(char c, int fd)
{
	static int index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || index >= WRITE_BUFFER_SIZE)
	{
		write(fd, buffer, index);
		index = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[index++] = c;
	return (1);
}

/**
 * printStringToFileDescriptor - Prints an input string to given file descriptor
 * @str: The string to be printed
 * @fd: The file descriptor to write to
 * 
 * Return: The number of characters written
 */
int printStringToFileDescriptor(char *str, int fd)
{
	int index = 0;

	if (!str)
		return (0);
	while (*str)
	{
		index += writeCharacterToFileDescriptor(*str++, fd);
	}
	return (index);
}
