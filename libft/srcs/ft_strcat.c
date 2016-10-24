#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	ft_strcpy(ft_strchr(s1, '\0'), s2);
	return (s1);
}
