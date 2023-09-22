#include "shell.h"

/**
 * my_history - Display the command history list, one command per line,
 *              preceded with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        a consistent function prototype.
 *
 * Return: Always 0
 */
int my_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_shell_alias - Unset a shell alias by name.
 * @info: Parameter struct.
 * @name: The name of the alias to unset.
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_shell_alias(info_t *info, char *name)
{
	char *p, c;
	int ret;

	p = _strchr(name, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, name, -1)));
	*p = c;
	return (ret);
}

/**
 * set_shell_alias - Set a shell alias to a string.
 * @info: Parameter struct.
 * @alias_string: The alias string to set.
 *
 * Return: Always 0 on success, 1 on error
 */
int set_shell_alias(info_t *info, char *alias_string)
{
	char *p;

	p = _strchr(alias_string, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_shell_alias(info, alias_string));

	unset_shell_alias(info, alias_string);
	return (add_node_end(&(info->alias), alias_string, 0) == NULL);
}

/**
 * print_shell_alias - Print a shell alias string.
 * @node: The alias node to print.
 *
 * Return: Always 0 on success, 1 on error
 */
int print_shell_alias(list_t *node)
{
	char *p = NULL, *alias = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (alias = node->str; alias <= p; alias++)
			_putchar(*alias);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_alias - Mimic the alias built-in command (man alias).
 * @info: Structure containing potential arguments. Used to maintain
 *        a consistent function prototype.
 *
 * Return: Always 0
 */
int my_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_shell_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_shell_alias(info, info->argv[i]);
		else
			print_shell_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
