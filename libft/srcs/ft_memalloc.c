#include "libft.h"
#include <stdlib.h>
#include <string.h>

void	*ft_memalloc(size_t size)
{
	void	*z;

	if ((z = (void *)malloc(size)))
		ft_bzero(z, size);
	return (z);
}
