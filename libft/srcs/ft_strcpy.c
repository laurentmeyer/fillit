#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	if ((*dst = *src) != '\0')
		ft_strcpy(dst + 1, src + 1);
	return (dst);
}
