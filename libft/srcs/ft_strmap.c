#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*tmp;

	if ((tmp = ft_strnew(ft_strlen(s))))
	{
		i = 0;
		while (s[i])
		{
			tmp[i] = (*f)(s[i]);
			++i;
		}
	}
	return (tmp);
}
