#include "libft.h"
#include <string.h>

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	if (n < ft_strlen(s2))
		ft_strncpy(ft_strchr(s1, '\0'), s2, n)[n] = '\0';
	else
		ft_strcpy(ft_strchr(s1, '\0'), s2);
	return (s1);
}
