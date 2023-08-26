#include <stdio.h>
#include "main.h"

/**
 * is_printable - checks if a char is printable
 * @c: the character to evaluate
 *
 * Return: 1 or 0
 */
 
int is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - adds ascii in hexadecimal code to buffer
 * @buffer: an array
 * @i: Index
 * @ascii_code: ascii code
 *
 * Return: Always 3
 */
 
int append_hexa_code(char ascii_code, char buffer[], int i)
{
	char map[] = "0123456789ABCDEF";
	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = map[ascii_code / 16];
	buffer[i] = map[ascii_code % 16];

	return (3);
}

/**
 * is_digit - to check if a char is a digit
 * @c: the char to evaluate
 *
 * Return: 1 or 0
 */

int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - converts the size of a number
 * @num: the number
 * @size: the size
 *
 * Return: value
 */
 
long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * convert_size_unsgnd - attaches a sign to a number
 * @num: the number
 * @size: the size
 *
 * Return: value
 */
 
long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
