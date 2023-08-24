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
	int length = 0, i;
	char *str = va_arg(types, char *);

	unused(buffer);
	unused(flags);
	unused(width);
	unused(precision);
	unused(size);
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
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}

/**
 * print_percent - to print a percent sign
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
	unused(types);
	unused(buffer);
	unused(flags);
	unused(width);
	unused(precision);
	unused(size);
	return (write(1, "%%", 1));
}


/**
 * print_int - Print int
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
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, precision, size));
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
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	unused(buffer);
	unused(flags);
	unused(width);
	unused(precision);
	unused(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
