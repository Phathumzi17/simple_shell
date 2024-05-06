#include "shell.h"

/**
 * determineInteractive - Evaluate if shell operates in interactive mode
 * @data: Structure containing necessary data
 *
 * Returns: 1 if interactive mode, 0 otherwise
 */
int determineInteractive(data_t *data)
{
	return (isatty(STDIN_FILENO) && data->readFileDescriptor <= 2);
}

/**
 * checkDelimiter - Check if a character is a delimiter
 * @ch: The character to be checked
 * @delimiter: String of delimiters
 * 
 * Returns: 1 if true, 0 otherwise
 */
int checkDelimiter(char ch, char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == ch)
			return (1);
	return (0);
}

/**
 * alphabeticCheck - Verify if a character is alphabetic
 * @ch: The character to be checked
 * 
 * Returns: 1 if alphabetic, 0 otherwise
 */
int alphabeticCheck(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * convertToInteger - Convert a string to an integer
 * @str: The string to be converted
 * 
 * Returns: 0 if no numbers in string, converted number otherwise
 */
int convertToInteger(char *str)
{
	int index, sign = 1, flag = 0, result;
	unsigned int output = 0;

	for (index = 0;  str[index] != '\0' && flag != 2; index++)
	{
		if (str[index] == '-')
			sign *= -1;

		if (str[index] >= '0' && str[index] <= '9')
		{
			flag = 1;
			output *= 10;
			output += (str[index] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		result = -output;
	else
		result = output;

	return (result);
}
