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
	int i = buff_size - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[buff_size - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
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

	int i = buff_size - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	unused(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[buff_size - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & f_hash && init_num != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
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
	int i = buff_size - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	unused(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[buff_size - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & f_hash && init_num != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
