#include "shell.h"

/**
 * changeCurrentDirectory - Change the current directory of the process.
 * @infos: Struct containing arguments, used to maintain const func prototype.
 *
 * Return: Always (0)
 */
int changeCurrentDirectory(info_t *infos)
{
	char *currentPath, *dir, buffer[1024];
	int chdirResult;

	currentPath = getcwd(buffer, 1024);
	if (!currentPath)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!infos->argv[1])
	{
		dir = _getenv(infos, "HOME=");
		if (!dir)
			chdirResult = chdir((dir = _getenv(infos, "PWD=")) ? dir : "/");
		else
			chdirResult = chdir(dir);
	}
	else if (_strcmp(infos->argv[1], "-") == 0)
	{
		if (!_getenv(infos, "OLDPWD="))
		{
			_puts(currentPath);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(infos, "OLDPWD=")), _putchar('\n');
		chdirResult = chdir((dir = _getenv(infos, "OLDPWD=")) ? dir : "/");
	}
	else
		chdirResult = chdir(infos->argv[1]);

	if (chdirResult == -1)
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
 * showHelp - Display help information.
 * @infos: Struct containing arguments, used to maintain const func prototype.
 *
 * Return: Always (0)
 */
int showHelp(info_t *infos)
{
	char **argumentsArray;

	argumentsArray = infos->argv;
	_puts("help call works. Function not yet implemented \n");

	if (0)
		_puts(*argumentsArray);

	return (0);
}

/**
 * exitShell - Exit the shell.
 * @infos: Struct containing arguments, used to maintain const func prototype.
 *
 * Return: Exits if given an exit status. If infos.argv[0] != "exit" (0)
 */
int exitShell(info_t *infos)
{
	int exitStatus;

	if (infos->argv[1])
	{
		exitStatus = _erratoi(infos->argv[1]);
		if (exitStatus == -1)
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

