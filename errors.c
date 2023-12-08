#include "shell.h"

/**
 * _eputs - Prints input string to stderr.
 * @str: String to print.
 *
 * Return: Nothing.
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _putfd - Writes char to the given file descriptor.
 * @ch: Char to print.
 * @fd: File descriptor to write.
 *
 * Return: 1 if success. -1 if error, and errno is set appropriately.
 */
int _putfd(char ch, int fd)
{
	static int index;
	static char buffer[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, index);
		index = 0;
	}

	if (ch != BUF_FLUSH)
		buffer[index++] = ch;

	return (1);
}

/**
 * _putsfd - Prints input string to the given file descriptor.
 * @str: String to print.
 * @fd: File descriptor to write.
 *
 * Return: Number of characters written.
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str)
	{
		i += _putfd(*str++, fd);
	}

	return (i);
}

/**
 * _eputchar - Writes char to stderr.
 * @ch: Char to print.
 *
 * Return: 1 if success. -1 if error, and errno is set appropriately.
 */
int _eputchar(char ch)
{
	static int index;
	static char buffer[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(2, buffer, index);
		index = 0;
	}

	if (ch != BUF_FLUSH)
		buffer[index++] = ch;

	return (1);
}

