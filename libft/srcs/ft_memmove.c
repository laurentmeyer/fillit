#include "libft.h"
#include <string.h>

static	void	*ft_membcpy(void *dst, const void *src, size_t n)
{
	if (n)
	{
		*((unsigned char *)dst + n - 1) = *((unsigned char *)src + n - 1);
		ft_membcpy(dst, src, --n);
	}
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (src < dst)
		return (ft_membcpy(dst, src, len));
	return (ft_memcpy(dst, src, len));
}

