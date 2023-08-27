#include <stdio.h>
#include "main.h"

/**
 * get_flags - to calculate all active flags
 * @i: set parameter
 * @format: the format of string to print
 *
 * Return: flag
 */

int get_flags(const char *format, int *i)
{
	int a, c;
	int f = 0; /*where f = flags*/
	const char f_char[] = {'-', '+', '0', '#', ' ', '\0'};
	const int f_arr[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (c = *i + 1; format[c] != '\0'; c++)
	{
		for (a = 0; f_char[a] != '\0'; a++)
			if (format[c] == f_char[a])
			{
				f |= f_arr[a];
				break;
			}

		if (f_char[a] == 0)
			break;
	}

	*i = c - 1;

	return (f);
}
