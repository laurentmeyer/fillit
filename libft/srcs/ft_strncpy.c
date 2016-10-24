#include "libft.h"
#include <string.h>

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	if (len != 0)
	{
		if ((*dst = *src) == '\0')
			ft_bzero(dst + 1, len - 1);
		else
			ft_strncpy(dst + 1, src + 1, len - 1);
	}
	return (dst);
}
