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
	int c;
	int w = 0; /*where w = width*/

	for (c = *i + 1; format[c] != '\0'; c++)
	{
		if (is_digit(format[c]))
		{
			w *= 10;
			w += format[c] - '0';
		}
		else if (format[c] == '*')
		{
			c++;
			w = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = c - 1;

	return (w);
}
