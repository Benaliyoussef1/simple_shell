#include "shell.h"

/**
 * error_string_to_int - Converts a string to an integer, handling errors.
 * @s: The string to be converted.
 *
 * Return: The converted number or -1 on error.
 */
int error_string_to_int(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: Investigate why this affects the return value */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error_message - Prints an error message.
 * @info: The parameter & return info struct.
 * @error_string: String containing the specified error type.
 *
 * Return: Nothing.
 */
void print_error_message(info_t *info, char *error_string)
{
	_eputs(info->fname);
	_eputs(": ");
	print_decimal(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(error_string);
}

/**
 * print_decimal - Prints a decimal (integer) number (base 10).
 * @input: The input number.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */
int print_decimal(int input, int fd)
{
	int (*custom_putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int absolute, current;

	if (fd == STDERR_FILENO)
		custom_putchar = _eputchar;
	if (input < 0)
	{
		absolute = -input;
		custom_putchar('-');
		count++;
	}
	else
		absolute = input;
	current = absolute;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute / i)
		{
			custom_putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	custom_putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number_to_string - Converts a number to a string.
 * @num: The number.
 * @base: The base.
 * @flags: Argument flags.
 *
 * Return: The converted string.
 */
char *convert_number_to_string(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_first_comment - Replaces the first instance of '#' with '\0'.
 * @buf: Address of the string to modify.
 *
 * Return: Always 0.
 */
void remove_first_comment(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
