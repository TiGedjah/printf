#include <stdio.h>
#include "main.h"


/**
 * print_char - to print a char
 * @types: list out types of arguments
 * @buffer: the buffer for prints
 * @flags:  to calculate all flags flags
 * @width: to measure width
 * @precision: to specify precision
 * @size: to specify size
 * Return: number of chars
 */

int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/**
 * print_string - to print a string
 * @types: list out types of arguments
 * @buffer: the buffer for prints
 * @flags:  to calculate all flags flags
 * @width: to measure width
 * @precision: to specify precision
 * @size: to specify size
 * Return: number of chars
 */

int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, a;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(buffer);
	UNUSED(precision);
	UNUSED(width);
	UNUSED(size);

	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}
	while (str[length] != '\0')
		length++;
	if (precision >= 0 && precision < length)
		length = precision;
	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (a = width - length; a > 0; a--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (a = width - length; a > 0; a--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}
return (write(1, str, length));
}

/**
 * print_percent - to print the percentage sign
 * @types: list out types of arguments
 * @buffer: the buffer for prints
 * @flags:  to calculate all flags flags
 * @width: to measure width
 * @precision: to specify precision
 * @size: to specify size
 * Return: number of chars
 */

int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(flags);
	UNUSED(buffer);
	UNUSED(precision);
	UNUSED(width);
	UNUSED(size);

	return (write(1, "%%", 1));
}


/**
 * print_int - to print out an int
 * @types: list out types of arguments
 * @buffer: the buffer for prints
 * @flags:  to calculate all flags flags
 * @width: to measure width
 * @precision: to specify precision
 * @size: to specify size
 * Return: number of chars
 */

int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int numb;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	numb = (unsigned long int)n;

	if (n < 0)
	{
		numb = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (numb > 0)
	{
		buffer[a--] = (numb % 10) + '0';
		numb /= 10;
	}

	a++;

	return (write_number(is_negative, a, buffer, flags, width, precision, size));
}


/**
 * print_binary - to print an unsigned number
 * @types: list out types of arguments
 * @buffer: the buffer for prints
 * @flags:  to calculate all flags
 * @width: to measure width
 * @precision: to specify precision
 * @size: to specify size
 * Return: number of chars
 */

int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int a[32];
	int c;
	unsigned int x, y, i, sum;

	UNUSED(flags);
	UNUSED(buffer);
	UNUSED(precision);
	UNUSED(width);
	UNUSED(size);

	x = va_arg(types, unsigned int);
	y = 2147483648;
	a[0] = x / y;
	for (i = 1; i < 32; i++)
	{
		y /= 2;
		a[i] = (x / y) % 2;
	}
	for (i = 0, sum = 0, c = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			c++;
		}
	}
	return (c);
}
