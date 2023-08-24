#include <stdio.h>
#include "main.h"
/**
 * handle_print - to print an argument based on the type
 * @fmt: the formatted string to print
 * @list: the list of arguments
 * @ind: index
 * @buffer: to handle print.
 * @flags: to calculate flags
 * @width: the width
 * @precision: to specify precision
 * @size: to specify the size
 *
 * Return: 1 or 2;
 */
 
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, len = 0, print_char = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (i = 0; fmt_types[i].fmt != '\0'; i++)
		if (fmt[*ind] == fmt_types[i].fmt)
			return (fmt_types[i].fn(list, buffer, flags, width, precision, size));

	if (fmt_types[i].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		len += write(1, &fmt[*ind], 1);
		return (len);
	}
	return (print_char);
}
