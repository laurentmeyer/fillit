#include "libft.h"
#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	if (!n)
		return (NULL);
	else if (*(unsigned char *)s == (unsigned char)c)
		return ((void *)s);
	else
		return (ft_memchr(++s, c, --n));
}
