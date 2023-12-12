#include "shell.h"

/**
 * get_history_file - get history file
 * @infos: param struct
 *
 * Return: allocated string with history file
 */
char *get_history_file(info_t *infos)
{
	char *buffer, *directory;
	directory = _getenv(infos, "HOME=");

	if (!directory)
		return (NULL);

	buffer = malloc(sizeof(char) * (_strlen(directory) + _strlen(HIST_FILE) + 2));

	if (!buffer)
		return (NULL);

	buffer[0] = 0;
	_strcpy(buffer, directory);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);

	return (buffer);
}

/**
 * write_history - creates a file/appends to existing file
 * @infos: param struct
 *
 * Return: if success 1 else -1
 */
int write_history(info_t *infos)
{
	ssize_t fd;
	list_t *nodes = NULL;
	char *filename = get_history_file(infos);

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (fd == -1)
		return (-1);

	for (nodes = infos->history; nodes; nodes = nodes->next)
	{
		_putsfd(nodes->str, fd);
		_putfd('\n', fd);
	}

	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - read history of file
 * @infos: param struct
 *
 * Return: if success hist-count otherwise 0
 */
int read_history(info_t *infos)
{
	ssize_t fd, read_len, file_size = 0;
	int i, last_index = 0, line_count = 0;
	struct stat st;
	char *buffer = NULL, *filename = get_history_file(infos);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);

	if (fd == -1)
		return (0);

	if (!fstat(fd, &st))
		file_size = st.st_size;

	if (file_size < 2)
		return (0);

	buffer = malloc(sizeof(char) * (file_size + 1));

	if (!buffer)
		return (0);

	read_len = read(fd, buffer, file_size);
	buffer[file_size] = 0;

	if (read_len <= 0)
		return (free(buffer), 0);

	close(fd);

	for (i = 0; i < file_size; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			build_history_list(infos, buffer + last_index, line_count++);
			last_index = i + 1;
		}

	if (last_index != i)
		build_history_list(infos, buffer + last_index, line_count++);

	free(buffer);
	infos->histcount = line_count;

	while (infos->histcount-- >= HIST_MAX)
		delete_node_at_index(&(infos->history), 0);

	renumber_history(infos);
	return (infos->histcount);
}

/**
 * renumber_history - after change, renumbers histo linked list
 * @infos: Struct containing arguments, used to maintain.
 *
 * Return: new histcount
 */
int renumber_history(info_t *infos)
{
	list_t *node = infos->history;
	int count = 0;

	while (node)
	{
		node->num = count++;
		node = node->next;
	}

	return (infos->histcount = count);
}

/**
 * build_history_list - add entry to hist linked list
 * @infos: Struct containing arguments, used to maintain.
 * @buff: buffer
 * @line_count: history linecount (histcount)
 *
 * Return: Always (0)
 */
int build_history_list(info_t *infos, char *buff, int line_count)
{
	list_t *node = NULL;

	if (infos->history)
		node = infos->history;

	add_node_end(&node, buff, line_count);

	if (!infos->history)
		infos->history = node;

	return (0);
}

