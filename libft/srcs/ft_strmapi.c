#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*tmp;

	if ((tmp = ft_strnew(ft_strlen(s))))
	{
		i = 0;
		while (s[i])
		{
			tmp[i] = (*f)(i, s[i]);
			++i;
		}
	}
	return (tmp);
}
