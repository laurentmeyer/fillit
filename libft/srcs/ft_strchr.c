#include "libft.h"
#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	if (*s == (char)c)
		return ((char *)s);
	else if (*s == '\0')
		return (NULL);
	else
		return (ft_strchr(s + 1, c));
}	
