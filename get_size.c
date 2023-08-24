#include <stdio.h>
#include "main.h"

/**
 * get_size - to calculate the size of the argument
 * @format: the format of string to print arguments
 * @i: the list of arguments
 *
 * Return: Precision.
 */
int get_size(const char *format, int *i)
{
	int aa = *i + 1;
	int s = 0;

	if (format[aa] == 'l')
		s = s_long;
	else if (format[aa] == 'h')
		s = s_short;

	if (s == 0)
		*i = aa - 1;
	else
		*i = aa;

	return (s);
}
