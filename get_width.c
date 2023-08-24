#include <stdio.h>
#include "main.h"

/**
 * get_width - to calculate the width
 * @format: the format of string to print arguments
 * @i: the list of arguments
 * @list: list of arguments
 *
 * Return: the width
 */
int get_width(const char *format, int *i, va_list list)
{
	int aa;
	int w = 0;

	for (aa = *i + 1; format[aa] != '\0'; aa++)
	{
		if (is_digit(format[aa]))
		{
			w *= 10;
			w += format[aa] - '0';
		}
		else if (format[aa] == '*')
		{
			aa++;
			w = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = aa - 1;

	return (w);
}
