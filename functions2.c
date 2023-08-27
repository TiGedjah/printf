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
	char xtra = 0, p = ' ';
	int index = BUFF_SIZE - 2, len = 2, p_start = 1;
	unsigned long address;
	char map[] = "0123456789abcdef";
	void *a = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (a == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';

	UNUSED(precision);

	address = (unsigned long)a;

	while (address > 0)
	{
		buffer[index--] = map[address % 16];
		address /= 16;
		len++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		p = '0';

	if (flags & F_PLUS)
		xtra = '+', len++;

	else if (flags & F_SPACE)
		xtra = ' ', len++;

	index++;

	return (write_pointer(buffer, index, len,
		width, flags, p, xtra, p_start));
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
	int a = 0, x = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[a] != '\0')
	{
		if (is_printable(str[a]))
			buffer[a + x] = str[a];
		else
			x += append_hexa_code(str[a], buffer, a + x);

		a++;
	}

	buffer[a + x] = '\0';

	return (write(1, buffer, a + x));
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
	int a, c = 0; /*where c = count*/

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (a = 0; str[a]; a++)
		;

	for (a = a - 1; a >= 0; a--)
	{
		char z = str[a];

		write(1, &z, 1);
		c++;
	}
	return (c);
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
	unsigned int a, b;
	int c = 0; /*where c = count*/
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (a = 0; str[a]; a++)
	{
		for (b = 0; in[b]; b++)
		{
			if (in[b] == str[a])
			{
				x = out[b];
				write(1, &x, 1);
				c++;
				break;
			}
		}
		if (!in[b])
		{
			x = str[a];
			write(1, &x, 1);
			c++;
		}
	}
	return (c);
}
