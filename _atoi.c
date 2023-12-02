#include "shell.h"
/**
 * interactive - if shell is interactive mode returns true
 * @infos: the struc address
 *
 * Return: in interactive mode 1 otherwise 0
 */
int interactive(info_t *infos)
{
return (isatty(STDIN_FILENO) && infos->readfd <= 2);
}
/**
 * _isalpha - it checks for an alphabetic character
 * @ch: char to input
 * Return: if c is alphabetic 1, 0 otherwise
 */
int _isalpha(int ch)
{
if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
return (1);
else
return (0);
}
/**
 * _atoi - converts string to int
 * @str: string to convert
 * Return: if no nums in string 0, otherwise converted number
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
 * is_delim - it checks if a character is a delimeter
 * @ch: character to check
 * @delime: delimeter string
 * Return: if true 1 if false 0
 */
int is_delim(char ch, char *delime)
{
while (*delime)
if (*delime++ == ch)
return (1);
return (0);
}
