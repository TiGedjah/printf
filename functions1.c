#include <stdio.h>
#include "main.h"

/**
 * print_unsigned - to print an unsigned number
 * @types: list out types of arguments
 * @buffer: the buffer for print
 * @flags:  to calculate all flags
 * @width: to measure width
 * @precision: to specify precision
 * @size: to specify size
 * Return: number of chars
 */

int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	unsigned long int n = va_arg(types, unsigned long int);

	n = convert_size_unsgnd(n, size);

	if (n == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (n > 0)
	{
		buffer[a--] = (n % 10) + '0';
		n /= 10;
	}

	a++;

	return (write_unsgnd(0, a, buffer, flags, width, precision, size));
}


/**
 * print_octal - to print an unsigned number in octal notation
 * @types: list out types of arguments
 * @buffer: the buffer for prints
 * @flags:  to calculate all flags
 * @width: to measure width
 * @precision: to specify precision
 * @size: to specify size
 * Return: number of chars
 */

int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int a = BUFF_SIZE - 2;
	unsigned long int n = va_arg(types, unsigned long int);
	unsigned long int init_n = n;

	UNUSED(width);

	n = convert_size_unsgnd(n, size);

	if (n == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (n > 0)
	{
		buffer[a--] = (n % 8) + '0';
		n /= 8;
	}

	if (flags & F_HASH && init_n != 0)
		buffer[a--] = '0';

	a++;

	return (write_unsgnd(0, a, buffer, flags, width, precision, size));
}

/**
 * print_hexadecimal - to print an unsigned number in hexadecimal notation
 * @types: list out types of arguments
 * @buffer: the buffer for prints
 * @flags:  to calculate all flags
 * @width: to measure width
 * @precision: to specify precision
 * @size: to specify size
 * Return: number of chars
 */

int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/**
 * print_hexa_upper - to print an unsigned number in upper hexadecimal notation
 * @types: list out types of arguments
 * @buffer: the buffer for prints
 * @flags:  to calculate all flags
 * @width: to measure width
 * @precision: to specify precision
 * @size: to specify size
 * Return: number of chars
 */

int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/**
 * print_hexa - to print a hexadecimal number in lower or upper
 * @types: list out types of arguments
 * @map_to: An array of values to map the number to
 * @buffer: the buffer for prints
 * @flags:  to calculate all flags
 * @flag_ch: to calculate all flags
 * @width: to measure width
 * @precision: to specify precision
 * @size: to specify size
 * @size: to specify size
 * Return: number of chars
 */

int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	unsigned long int n = va_arg(types, unsigned long int);
	unsigned long int init_n = n;

	UNUSED(width);

	n = convert_size_unsgnd(n, size);

	if (n == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (n > 0)
	{
		buffer[a--] = map_to[n % 16];
		n /= 16;
	}

	if (flags & F_HASH && init_n != 0)
	{
		buffer[a--] = flag_ch;
		buffer[a--] = '0';
	}

	a++;

	return (write_unsgnd(0, a, buffer, flags, width, precision, size));
}
