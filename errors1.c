#include "shell.h"

/**
 * _erratoi - converts string to int
 * @str: string to convert
 * Return: if no numbers in string (0) converted num
 * otherwise -1 on error
 */
int _erratoi(char *str)
{
	int index = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;

	for (index = 0; str[index] != '\0'; index++)
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
 * print_d - prints a decimal int number (base 10)
 * @inputs: input
 * @fd: filedescriptor to write
 *
 * Return: number characters printed
 */
int print_d(int inputs, int fd)
{
	int (*putchar_func)(char) = _putchar;
	int index, count = 0;
	unsigned int absolute_value, current;

	if (fd == STDERR_FILENO)
		putchar_func = _eputchar;

	if (inputs < 0)
	{
		absolute_value = -inputs;
		putchar_func('-');
		count++;
	}
	else
		absolute_value = inputs;

	current = absolute_value;

	for (index = 1000000000; index > 1; index /= 10)
	{
		if (absolute_value / index)
		{
			putchar_func('0' + current / index);
			count++;
		}
		current %= index;
	}

	putchar_func('0' + current);
	count++;

	return (count);
}

/**
 * print_error - print error msg
 * @infos: parameter and return info struct
 * @est: string with specified type error
 * Return: if no numbers in string 0 converted number
 * otherwise -1 on error
 */
void print_error(info_t *infos, char *est)
{
	_eputs(infos->fname);
	_eputs(": ");
	print_d(infos->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(infos->argv[0]);
	_eputs(": ");
	_eputs(est);
}

/**
 * remove_comments - replaces '#' with '\0'
 * @buffer: address of string to modify
 *
 * Return: Always (0)
 */
void remove_comments(char *buffer)
{
	int index;

	for (index = 0; buffer[index] != '\0'; index++)
		if (buffer[index] == '#' && (!index || buffer[index - 1] == ' '))
		{
			buffer[index] = '\0';
			break;
		}
}

/**
 * convert_number - convert function clone of itoa
 * @numb: number
 * @base: base
 * @flag: argument flags
 *
 * Return: a string
 */
char *convert_number(long int numb, int base, int flag)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long b = numb;

	if (!(flag & CONVERT_UNSIGNED) && numb < 0)
	{
		b = -numb;
		sign = '-';
	}

	array = flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[b % base];
		b /= base;
	} while (b != 0);

	if (sign)
		*--ptr = sign;

	return (ptr);
}

