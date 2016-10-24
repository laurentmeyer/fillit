#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	if (!*s1 && !*s2)
		return (0);
	else if (*(unsigned char *)s1 != *(unsigned char *)s2)
		return (*(unsigned char *)s1 - *(unsigned char *)s2);
	else
		return (ft_strcmp(++s1, ++s2));
}
