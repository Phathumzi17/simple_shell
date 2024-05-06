#include "shell.h"

/**
 **BufferChainedCommands - Buffers chained commands
 *@info: Parameter struct
 *@buffer: Address of buffer
 *@length: Address of length variable
 *
 *Return: Bytes read
 */
ssize_t BufferChainedCommands(info_t *info, char **buffer, size_t *length)
{
	ssize_t bytes_read = 0;
	size_t length_pointer = 0;

	if (!*length) /* If nothing left in the buffer, fill it */
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, SignalInterruptHandler);
#if USE_GETLINE
		bytes_read = getline(buffer, &length_pointer, stdin);
#else
		bytes_read = CustomGetLine(info, buffer, &length_pointer);
#endif
		if (bytes_read > 0)
		{
			if ((*buffer)[bytes_read - 1] == '\n')
			{
				(*buffer)[bytes_read - 1] = '\0'; /* Remove trailing newline */
				bytes_read--;
			}
			info->lineCountFlag = 1;
			RemoveComments(*buffer);
			BuildHistoryList(info, *buffer, info->historyCount++);
			/* If (_strchr(*buffer, ';')) Is this a command chain? */
			{
				*length = bytes_read;
				info->commandBuffer = buffer;
			}
		}
	}
	return (bytes_read);
}

/**
 **GetInput - Gets a line minus the newline
 *@info: Parameter struct
 *
 *Return: Bytes read
 */
ssize_t GetInput(info_t *info)
{
	static char *buffer; /* The ';' command chain buffer */
	static size_t iterator, nextIterator, length;
	ssize_t bytes_read = 0;
	char **bufferPointer = &(info->argument), *pointer;

	_putchar(BUFFER_FLUSH);
	bytes_read = BufferChainedCommands(info, &buffer, &length);
	if (bytes_read == -1) /* EOF */
		return (-1);
	if (length)	/* We have commands left in the chain buffer */
	{
		nextIterator = iterator; /* Initialize new iterator to current buffer position */
		pointer = buffer + iterator; /* Get pointer for return */

		CheckChain(info, buffer, &nextIterator, iterator, length);
		while (nextIterator < length) /* Iterate to semicolon or end */
		{
			if (IsChain(info, buffer, &nextIterator))
				break;
			nextIterator++;
		}

		iterator = nextIterator + 1; /* Increment past nulled ';' */
		if (iterator >= length) /* Reached end of buffer? */
		{
			iterator = length = 0; /* Reset position and length */
			info->commandBufferType = COMMAND_NORMAL;
		}

		*bufferPointer = pointer; /* Pass back pointer to current command position */
		return (_strlen(pointer)); /* Return length of current command */
	}

	*bufferPointer = buffer; /* Else not a chain, pass back buffer from CustomGetLine() */
	return (bytes_read); /* Return length of buffer from CustomGetLine() */
}

/**
 **ReadBuffer - Reads a buffer
 *@info: Parameter struct
 *@buffer: Buffer
 *@iterator: Size
 *
 *Return: Bytes read
 */
ssize_t ReadBuffer(info_t *info, char *buffer, size_t *iterator)
{
	ssize_t bytes_read = 0;

	if (*iterator)
		return (0);
	bytes_read = read(info->readFileDescriptor, buffer, READ_BUFFER_SIZE);
	if (bytes_read >= 0)
		*iterator = bytes_read;
	return (bytes_read);
}

/**
 **CustomGetLine - Gets the next line of input from STDIN
 *@info: Parameter struct
 *@pointer: Address of pointer to buffer, preallocated or NULL
 *@length: Size of preallocated pointer buffer if not NULL
 *
 *Return: Bytes read
 */
int CustomGetLine(info_t *info, char **pointer, size_t *length)
{
	static char buffer[READ_BUFFER_SIZE];
	static size_t iterator, bufferLength;
	size_t endIndex;
	ssize_t bytes_read = 0, totalBytesRead = 0;
	char *ptr = NULL, *newPtr = NULL, *character;

	ptr = *pointer;
	if (ptr && length)
		totalBytesRead = *length;
	if (iterator == bufferLength)
		iterator = bufferLength = 0;

	bytes_read = ReadBuffer(info, buffer, &bufferLength);
	if (bytes_read == -1 || (bytes_read == 0 && bufferLength == 0))
		return (-1);

	character = _strchr(buffer + iterator, '\n');
	endIndex = character ? 1 + (unsigned int)(character - buffer) : bufferLength;
	newPtr = _realloc(ptr, totalBytesRead, totalBytesRead ? totalBytesRead + endIndex : endIndex + 1);
	if (!newPtr) /* MALLOC FAILURE! */
		return (ptr ? free(ptr), -1 : -1);

	if (totalBytesRead)
		_strncat(newPtr, buffer + iterator, endIndex - iterator);
	else
		_strncpy(newPtr, buffer + iterator, endIndex - iterator + 1);

	totalBytesRead += endIndex - iterator;
	iterator = endIndex;
	ptr = newPtr;

	if (length)
		*length = totalBytesRead;
	*pointer = ptr;
	return (totalBytesRead);
}

/**
 **SignalInterruptHandler - Blocks ctrl-C
 *@signalNumber: The signal number
 *
 *Return: Void
 */
void SignalInterruptHandler(__attribute__((unused))int signalNumber)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_FLUSH);
}
