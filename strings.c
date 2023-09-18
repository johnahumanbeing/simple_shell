#include "shell.h"
/**
 * str_num - Convert a number to string format
 * @num: Number to be converted
 *
 * Return: Pointer to string representation of "num"
*/
char *str_num(int num)
{
	int num_rev = 0;
	int i, digits = 0;
	char *num_str = NULL;

	if (num == 0)
		digits = 1;
	else
		while (num > 0)
		{
			digits++;
			num_rev *= 10;
			num_rev += num % 10;
			num /= 10;
		}

	num_str = malloc(sizeof(char) * (digits + 1));
	if (num_str == NULL)
		dispatch_error("Error: Coudn't allocate memory for number conversion");

	for (i = 0; i < digits; i++)
	{
		num_str[i] = (num_rev % 10) + '0';
		num_rev /= 10;
	}
	num_str[i] = '\0';

	return (num_str);
}

/**
 * str_scan - string scanning operation
 * @s: string 1
 * @c: character to search
 * Return: return a pointer to the byte, or
 * a null pointer if the byte was not found.
 */
char *str_scan(const char *s, int c)
{
	size_t i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i++;
	}
	if (c == '\0')
		return ((char *)(&s[i]));
	return (NULL);
}

/**
 * n_strcat - concatenate first n chars of s2 to s1 string
 * @s1: string 1
 * @s2: string 2
 * @n: numbers of characters of s2 to concatenate to the s1
 * Return: return a pointer to the resulting string dest.
 */
char *n_strcat(char *s1, const char *s2, size_t n)
{
	size_t i;
	size_t j;

	i = strlen(s1);
	j = 0;
	while (s2[j] && j < n)
		s1[i++] = s2[j++];
	s1[i] = '\0';
	return (s1);
}
