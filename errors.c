#include "shell.h"

/**
 * print_error_message - Prints an error message.
 * @message: The error message to be printed.
 *
 * Return: Nothing.
 */
void print_error_message(char *message)
{
	int i = 0;

	if (!message)
		return;
	while (message[i] != '\0')
	{
		write_error_character(message[i]);
		i++;
	}
}

/**
 * write_error_character - Writes a character to the standard error.
 * @c: The character to write.
 *
 * Return: On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int write_error_character(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * write_to_file_descriptor - Writes a character to a specified file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int write_to_file_descriptor(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * print_to_file_descriptor - Prints an input string to a specified file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */
int print_to_file_descriptor(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += write_to_file_descriptor(*str++, fd);
	}
	return (i);
}
