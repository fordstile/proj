#include "shell.h"

/**
 * interactive - Checks if the shell is in interactive mode.
 * @infos: Pointer to the info_t structure.
 *
 * Return: 1 if in interactive mode, 0 otherwise.
 */
int interactive(info_t *infos)
{
	return (isatty(STDIN_FILENO) && infos->readfd <= 2);
}

/**
 * _isalpha - Checks if a character is alphabetic.
 * @ch: The character to check.
 *
 * Return: 1 if the character is alphabetic, 0 otherwise.
 */
int _isalpha(int ch)
{
	return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

/**
 * _atoi - Converts a string to an integer.
 * @str: The string to convert.
 *
 * Return: If no numbers in the string, 0. Otherwise, the converted number.
 */
int _atoi(char *str)
{
	int z, signs = 1, flags = 0, outputs;
	unsigned int result = 0;

	for (z = 0; str[z] != '\0' && flags != 2; z++)
	{
		if (str[z] == '-')
			signs *= -1;
		if (str[z] >= '0' && str[z] <= '9')
		{
			flags = 1;
			result *= 10;
			result += (str[z] - '0');
		}
		else if (flags == 1)
			flags = 2;
	}

	if (signs == -1)
		outputs = -result;
	else
		outputs = result;

	return (outputs);
}

/**
 * is_delim - Checks if a character is a delimiter.
 * @ch: The character to check.
 * @delime: The delimiter string.
 *
 * Return: 1 if true, 0 if false.
 */
int is_delim(char ch, char *delime)
{
	while (*delime)
		if (*delime++ == ch)
			return (1);

	return (0);
}

