#include "shell.h"
/**
 * _eputs - it prints input string
 * @stri: string to print
 *
 * Return: Nothing
 */
void _eputs(char *stri)
{
int z = 0;
if (!stri)
return;
while (stri[z] != '\0')
{
_eputchar(stri[z]);
z++;
}
}
/**
 * _putfd - write char c to given fd
 * @ch: char to print
 * @fd: filedescriptor to write
 *
 * Return: 1 if success.
 * -1 if error and errno is set appropriately.
 */
int _putfd(char ch, int fd)
{
static int z;
static char buffe[WRITE_BUF_SIZE];
if (ch == BUF_FLUSH || z >= WRITE_BUF_SIZE)
{
write(fd, buffe, z);
z = 0;
}
if (ch != BUF_FLUSH)
buffe[z++] = ch;
return (1);
}
/**
 * _putsfd - prints input string
 * @stri: string to print
 * @fd: filedescriptor to write
 *
 * Return: number chars put
 */
int _putsfd(char *stri, int fd)
{
int z = 0;
if (!stri)
return (0);
while (*stri)
{
z += _putfd(*stri++, fd);
}
return (z);
}
/**
 * _eputchar - writes char c to stderr
 * @ch: char to print
 *
 * Return: 1 if success.
 * -1 if error and errno is set appropriately.
 */
int _eputchar(char ch)
{
static int z;
static char buffe[WRITE_BUF_SIZE];
if (ch == BUF_FLUSH || z >= WRITE_BUF_SIZE)
{
write(2, buffe, z);
z = 0;
}
if (ch != BUF_FLUSH)
buffe[z++] = ch;
return (1);
}
