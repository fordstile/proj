#include "shell.h"
/**
 * unset_alias - set alias to a string
 * @infos: param struct
 * @str: string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *infos, char *str)
{
char *o, x;
int retu;
o = _strchr(str, '=');
if (!o)
return (1);
x = *o;
*o = 0;
retu = delete_node_at_index(&(infos->alias),
get_node_index(infos->alias, node_starts_with(infos->alias, str, -1)));
*o = x;
return (retu);
}
#include "shell.h"
/**
 * _myhistory - displays history list starting from 0,
 *  one command by line preceded with line numbers.
 * @infos: Struct containing arguments, used to maintain.
 *  const func prototype.
 *  Return: Always (0)
 */
int _myhistory(info_t *infos)
{
print_list(infos->history);
return (0);
}
/**
 * print_alias - prints the alias string
 * @nodes: alias node
 *
 * Return: 0 on success and 1 on error
 */
int print_alias(list_t *nodes)
{
char *o = NULL, *b = NULL;
if (nodes)
{
o = _strchr(nodes->str, '=');
for (b = nodes->str; b <= o; b++)
_putchar(*b);
_putchar('\'');
_puts(o + 1);
_puts("'\n");
return (0);
}
return (1);
}
/**
 * set_alias - it sets an alias to the string
 * @infos: param struct
 * @str: string alias
 *
 * Return: if success always 0, if error 1
 */
int set_alias(info_t *infos, char *str)
{
char *o;
o = _strchr(str, '=');
if (!o)
return (1);
if (!*++o)
return (unset_alias(infos, str));
unset_alias(infos, str);
return (add_node_end(&(infos->alias), str, 0) == NULL);
}
/**
 * _myalias - mimics alias builtin
 * @infos: Struct containing arguments, used to maintain.
 * const func prototype.
 *  Return: Always (0)
 */
int _myalias(info_t *infos)
{
int z = 0;
char *p = NULL;
list_t *node = NULL;
if (infos->argc == 1)
{
node = infos->alias;
while (node)
{
print_alias(node);
node = node->next;
}
return (0);
}
for (z = 1; infos->argv[z]; z++)
{
p = _strchr(infos->argv[z], '=');
if (p)
set_alias(infos, infos->argv[z]);
else
print_alias(node_starts_with(infos->alias, infos->argv[z], '='));
}
return (0);
}
