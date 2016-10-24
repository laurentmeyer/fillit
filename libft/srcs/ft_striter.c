#include "libft.h"

void	ft_striter(char *s, void (*f)(char *))
{
	if (*s != '\0')
	{
		(*f)(s);
		ft_striter(++s, f);
	}
}
