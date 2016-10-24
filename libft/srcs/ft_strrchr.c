#include "libft.h"
#include "string.h"

char	*ft_strrchr(const char *s, int c)
{
	if ((char)c == '\0')
		return (ft_strchr(s, c));
	else if (!ft_strchr(s, c))
		return (NULL);
	else if (!ft_strchr(ft_strchr(s, c) + 1, c))
		return (ft_strchr(s, c)); 
	else
		return (ft_strrchr(ft_strchr(s, c) + 1, c));
}
