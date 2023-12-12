#include "shell.h"

/**
 * read_buf - reads buffer
 * @infos: parameter struct
 * @buffe: the buffer
 * @z: the size
 *
 * Return: t
 */
ssize_t read_buf(info_t *infos, char *buffe, size_t *z)
{
	ssize_t t = 0;

	if (*z)
		return (0);

	t = read(infos->readfd, buffe, READ_BUF_SIZE);

	if (t >= 0)
		*z = t;

	return (t);
}

/**
 * input_buf - chains buffers for commands
 * @infos: parameter struct
 * @buff: address of the buffer
 * @len: address len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *infos, char **buff, size_t *len)
{
	ssize_t t = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);

		#if USE_GETLINE
		t = getline(buff, &len_p, stdin);
		#else
		t = _getline(infos, buff, &len_p);
		#endif

		if (t > 0)
		{
			if ((*buff)[t - 1] == '\n')
			{
				(*buff)[t - 1] = '\0';
				t--;
			}
			infos->linecount_flag = 1;
			remove_comments(*buff);
			build_history_list(infos, *buff, infos->histcount++);
			{
				*len = t;
				infos->cmd_buf = buff;
			}
		}
	}

	return (t);
}

/**
 * get_input - gets line until newline
 * @infos: parameter struct
 *
 * Return: bytes
 */
ssize_t get_input(info_t *infos)
{
	static char *buff;
	static size_t v, k, len;
	ssize_t r = 0;
	char **buf_p = &(infos->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(infos, &buff, &len);

	if (r == -1)
		return (-1);

	if (len)
	{
		k = v;
		p = buff + v;
		check_chain(infos, buff, &k, v, len);

		while (k < len)
		{
			if (is_chain(infos, buff, &k))
				break;

			k++;
		}

		v = k + 1;

		if (v >= len)
		{
			v = len = 0;
			infos->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buff;
	return (r);
}

/**
 * _getline - gets next line input from STDIN
 * @infos: parameter struct
 * @ptri: address pointer to buffer (preallocated or NULL)
 * @lengt: size preallocated ptr buffer if !NULL
 *
 * Return: s
 */
int _getline(info_t *infos, char **ptri, size_t *lengt)
{
	static size_t v, len;
	static char buf[READ_BUF_SIZE];
	size_t kt;
	char *p = NULL, *new_p = NULL, *c;
	ssize_t rt = 0, st = 0;

	p = *ptri;

	if (p && lengt)
		st = *lengt;

	if (v == len)
		v = len = 0;

	rt = read_buf(infos, buf, &len);

	if (rt == -1 || (rt == 0 && len == 0))
		return (-1);

	c = _strchr(buf + v, '\n');
	kt = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, st, st ? st + kt : kt + 1);

	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (st)
		_strncat(new_p, buf + v, kt - v);
	else
		_strncpy(new_p, buf + v, kt - v + 1);

	st += kt - v;
	v = kt;
	p = new_p;

	if (lengt)
		*lengt = st;

	*ptri = p;
	return (st);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sign_num: signal num
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused)) int sign_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

