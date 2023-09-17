#include <shell.h>
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
