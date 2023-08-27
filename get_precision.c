#include <stdio.h>
#include "main.h"

/**
 * get_precision - to calculate the precision
 * @format: the format of string to print arguments
 * @i: the list of arguments
 * @list: list of arguments
 *
 * Return: p
 */

int get_precision(const char *format, int *i, va_list list)
{
	int c = *i + 1;
	int p = -1; /*where p = precision*/

	if (format[c] != '.')
		return (p);

	p = 0;

	for (c += 1; format[c] != '\0'; c++)
	{
		if (is_digit(format[c]))
		{
			p *= 10;
			p += format[c] - '0';
		}
		else if (format[c] == '*')
		{
			c++;
			p = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = c - 1;

	return (p);
}
