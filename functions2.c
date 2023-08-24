#include <stdio.h>
#include "main.h"


/**
 * print_pointer - to print the value of a pointer variable
 * @types: list out types of arguments
 * @buffer: the buffer for print
 * @flags:  to calculate all flags
 * @width: to measure width
 * @precision: to specify precision
 * @size: to specify size
 * Return: number of chars
 */
 
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = buff_size - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	unused(width);
	unused(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[buff_size - 1] = '\0';
	unused(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	/*return (write(1, &buffer[i], buff_size - i - 1));*/
	return (write_pointer(buffer, ind, length,
		width, flags, padd, extra_c, padd_start));
}


/**
 * print_non_printable - to print ascii codes in hexa of non printable chars
 * @types: list out types of arguments
 * @buffer: the buffer for print
 * @flags:  to calculate all flags
 * @width: to measure width
 * @precision: to specify precision
 * @size: to specify size
 * Return: number of chars
 */
 
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(types, char *);

	unused(flags);
	unused(width);
	unused(precision);
	unused(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			buffer[i + offset] = str[i];
		else
			offset += append_hexa_code(str[i], buffer, i + offset);

		i++;
	}

	buffer[i + offset] = '\0';

	return (write(1, buffer, i + offset));
}


/**
 * print_reverse - to print reverse string.
 * @types: list out types of arguments
 * @buffer: the buffer for print
 * @flags:  to calculate all flags
 * @width: to measure width
 * @precision: to specify precision
 * @size: to specify size
 * Return: number of chars
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int i, count = 0;

	unused(buffer);
	unused(flags);
	unused(width);
	unused(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		unused(precision);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}

/**
 * print_rot13string - Print a string in rot13.
 * @types: list out types of arguments
 * @buffer: the buffer for print
 * @flags:  to calculate all flags
 * @width: to measure width
 * @precision: to specify precision
 * @size: to specify size
 * Return: number of chars
 */
 
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	unused(buffer);
	unused(flags);
	unused(width);
	unused(precision);
	unused(size);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[i];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
