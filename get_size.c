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
	int c = *i + 1;
	int s = 0; /*where s = size*/

	if (format[c] == 'l')
		s = S_LONG;
	else if (format[c] == 'h')
		s = S_SHORT;

	if (s == 0)
		*i = c - 1;
	else
		*i = c;

	return (s);
}
