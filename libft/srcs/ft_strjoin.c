#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *tmp;

	if ((tmp = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		ft_strcpy(ft_strcpy(tmp, s1) + ft_strlen(s1), s2);
	return (tmp);
}
