#include "libft.h"
#include <string.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *tmp;

	if ((tmp = ft_strnew(len)))
		ft_strncpy(tmp, s + start, len);
	return (tmp);
}
