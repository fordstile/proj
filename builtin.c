#include "shell.h"
/**
 * _mycd - change current directory of process
 * @infos: Struct containing arguments, used to maintain.
 * const func prototype.
 * Return: Always (0)
 */
int _mycd(info_t *infos)
{
char *s, *dir, buffer[1024];
int chdir_ret;
s = getcwd(buffer, 1024);
if (!s)
_puts("TODO: >>getcwd failure emsg here<<\n");
if (!infos->argv[1])
{
dir = _getenv(infos, "HOME=");
if (!dir)
chdir_ret = chdir((dir = _getenv(infos, "PWD=")) ? dir : "/");
else
chdir_ret = chdir(dir);
}
else if (_strcmp(infos->argv[1], "-") == 0)
{
if (!_getenv(infos, "OLDPWD="))
{
_puts(s);
_putchar('\n');
return (1);
}
_puts(_getenv(infos, "OLDPWD=")), _putchar('\n');
chdir_ret = chdir((dir = _getenv(infos, "OLDPWD=")) ? dir : "/");
}
else
chdir_ret = chdir(infos->argv[1]);
if (chdir_ret == -1)
{
print_error(infos, "can't cd to ");
_eputs(infos->argv[1]), _eputchar('\n');
}
else
{
_setenv(infos, "OLDPWD", _getenv(infos, "PWD="));
_setenv(infos, "PWD", getcwd(buffer, 1024));
}
return (0);
}
/**
 * _myhelp - it changes current directory of process
 * @infos: Struct containing arguments, used to maintain.
 * const func prototype.
 * Return: Always (0)
 */
int _myhelp(info_t *infos)
{
char **arg_array;
arg_array = infos->argv;
_puts("help call works. Function not yet implemented \n");
if (0)
_puts(*arg_array);
return (0);
}
/**
 * _myexit - to exit the shell
 * @infos: Struct containing arguments, used to maintain.
 * const func prototype.
 * Return: exits if given an exit status
 * if infos.argv[0] != "exit" (0)
 */
int _myexit(info_t *infos)
{
int exitscheck;
if (infos->argv[1])
{
exitscheck = _erratoi(infos->argv[1]);
if (exitscheck == -1)
{
infos->status = 2;
print_error(infos, "Illegal number: ");
_eputs(infos->argv[1]);
_eputchar('\n');
return (1);
}
infos->err_num = _erratoi(infos->argv[1]);
return (-2);
}
infos->err_num = -1;
return (-2);
}
