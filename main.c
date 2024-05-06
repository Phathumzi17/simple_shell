#include "shell.h"

/**
 * main - Entry point
 * @argCount: Argument count
 * @argVector: Argument vector
 * 
 * Return: 0 on success, 1 on error
 */
int main(int argCount, char **argVector)
{
	info_t information[] = { INFO_INIT };
	int fileDescriptor = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fileDescriptor)
		: "r" (fileDescriptor));

	if (argCount == 2)
	{
		fileDescriptor = open(argVector[1], O_RDONLY);
		if (fileDescriptor == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				printErrorMessage(argVector[0]);
				printErrorMessage(": 0: Can't open ");
				printErrorMessage(argVector[1]);
				writeCharacter('\n');
				writeCharacter(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		information->readFileDescriptor = fileDescriptor;
	}
	populateEnvironmentList(information);
	readHistory(information);
	shellFunction(information, argVector);
	return (EXIT_SUCCESS);
}
