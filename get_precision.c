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
	int aa = *i + 1;
	int p = -1;

	if (format[aa] != '.')
		return (p);

	p = 0;

	for (aa += 1; format[aa] != '\0'; aa++)
	{
		if (is_digit(format[aa]))
		{
			p *= 10;
			p += format[aa] - '0';
		}
		else if (format[aa] == '*')
		{
			aa++;
			p = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = aa - 1;

	return (p);
}
