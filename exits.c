#include "shell.h"

/**
 * _strncat - concatenates two strings
 * @dest: destination string
 * @src: source string
 * @n: maximum number of bytes to concatenate
 * Return: concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int dest_index, src_index;
	char *result = dest;

	dest_index = 0;
	src_index = 0;

	while (dest[dest_index] != '\0')
		dest_index++;

	while (src[src_index] != '\0' && src_index < n)
	{
		dest[dest_index] = src[src_index];
		dest_index++;
		src_index++;
	}

	if (src_index < n)
		dest[dest_index] = '\0';

	return (result);
}

/**
 * _strchr - locates a character in a string
 * @str: string to search
 * @c: character to find
 * Return: a pointer to the first occurrence of the character c in the string,
 * or NULL if the character is not found
 */
char *_strchr(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}

/**
 * _strncpy - copies a string
 * @dest: destination string
 * @src: source string
 * @n: maximum number of characters to copy
 * Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int dest_index, src_index;
	char *result = dest;

	dest_index = 0;

	while (src[dest_index] != '\0' && dest_index < n - 1)
	{
		dest[dest_index] = src[dest_index];
		dest_index++;
	}

	if (dest_index < n)
	{
		src_index = dest_index;
		while (src_index < n)
		{
			dest[src_index] = '\0';
			src_index++;
		}
	}

	return (result);
}

