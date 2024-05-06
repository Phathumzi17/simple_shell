#include "shell.h"

/**
 **CopyString - Copies a string
 *@destination: The destination string to be copied to
 *@source: The source string
 *@length: The number of characters to be copied
 *Return: The pointer to the destination string
 */
char *CopyString(char *destination, char *source, int length)
{
	int index;
	char *startingPoint = destination;

	index = 0;
	while (source[index] != '\0' && index < length - 1)
	{
		destination[index] = source[index];
		index++;
	}
	if (index < length)
	{
		int tempIndex = index;
		while (tempIndex < length)
		{
			destination[tempIndex] = '\0';
			tempIndex++;
		}
	}
	return (startingPoint);
}

/**
 **ConcatenateString - Concatenates two strings
 *@destination: The first string
 *@source: The second string
 *@maxLength: The maximum number of bytes to be used
 *Return: The pointer to the concatenated string
 */
char *ConcatenateString(char *destination, char *source, int maxLength)
{
	int destIndex, sourceIndex;
	char *startingPoint = destination;

	destIndex = 0;
	while (destination[destIndex] != '\0')
		destIndex++;
	sourceIndex = 0;
	while (source[sourceIndex] != '\0' && sourceIndex < maxLength)
	{
		destination[destIndex] = source[sourceIndex];
		destIndex++;
		sourceIndex++;
	}
	if (sourceIndex < maxLength)
		destination[destIndex] = '\0';
	return (startingPoint);
}

/**
 **LocateCharacter - Locates a character in a string
 *@string: The string to be parsed
 *@character: The character to look for
 *Return: A pointer to the memory area where the character is located
 */
char *LocateCharacter(char *string, char character)
{
	do {
		if (*string == character)
			return (string);
	} while (*string++ != '\0');

	return (NULL);
}
