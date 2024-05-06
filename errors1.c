#include "shell.h"

/**
 * errorToInteger - Converts a string to an integer
 * @str: The string to be converted
 * 
 * Return: 0 if no numbers in string, converted number otherwise
 *         -1 on error
 */
int errorToInteger(char *str)
{
	int index = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;  /* TODO: Check why this affects main's return value */
	for (index = 0;  str[index] != '\0'; index++)
	{
		if (str[index] >= '0' && str[index] <= '9')
		{
			result *= 10;
			result += (str[index] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * printErrorMessage - Prints an error message
 * @info: The parameter & return info struct
 * @errorMessage: String containing specified error type
 * 
 * Return: Nothing
 */
void printErrorMessage(info_t *info, char *errorMessage)
{
	writeString(info->fileName);
	writeCharacter(':');
	printDecimal(info->lineCount, STDERR_FILENO);
	writeCharacter(':');
	writeString(info->argumentVector[0]);
	writeString(": ");
	writeString(errorMessage);
}

/**
 * printDecimal - Function prints a decimal (integer) number (base 10)
 * @input: The input
 * @fileDescriptor: The file descriptor to write to
 * 
 * Return: Number of characters printed
 */
int printDecimal(int input, int fileDescriptor)
{
	int (*putCharacter)(char) = writeCharacter;
	int index, count = 0;
	unsigned int absoluteValue, current;

	if (fileDescriptor == STDERR_FILENO)
		putCharacter = writeCharacterToStderr;
	if (input < 0)
	{
		absoluteValue = -input;
		putCharacter('-');
		count++;
	}
	else
		absoluteValue = input;
	current = absoluteValue;
	for (index = 1000000000; index > 1; index /= 10)
	{
		if (absoluteValue / index)
		{
			putCharacter('0' + current / index);
			count++;
		}
		current %= index;
	}
	putCharacter('0' + current);
	count++;

	return (count);
}

/**
 * convertNumber - Converter function, a clone of itoa
 * @number: Number
 * @base: Base
 * @flags: Argument flags
 * 
 * Return: String
 */
char *convertNumber(long int number, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *pointer;
	unsigned long n = number;

	if (!(flags & CONVERT_UNSIGNED) && number < 0)
	{
		n = -number;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pointer = &buffer[49];
	*pointer = '\0';

	do	{
		*--pointer = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--pointer = sign;
	return (pointer);
}

/**
 * removeComments - Function replaces first instance of '#' with '\0'
 * @buffer: Address of the string to modify
 * 
 * Return: Always 0;
 */
void removeComments(char *buffer)
{
	int index;

	for (index = 0; buffer[index] != '\0'; index++)
		if (buffer[index] == '#' && (!index || buffer[index - 1] == ' '))
		{
			buffer[index] = '\0';
			break;
		}
}
