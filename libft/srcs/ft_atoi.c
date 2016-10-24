#include "libft.h"

int		ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		acc;

	i = 0;
	sign = 1;
	acc = 0;
	while (str[i] == ' ' || (str[i] >= 7 && str[i] <= 13))
		i++;
	if (str[i] == '+' && str[i + 1] >= '0' && str[i + 1] <= '9')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		acc = 10 * acc - (str[i] - '0');
		i++;
	}
	return (-sign * acc);
}