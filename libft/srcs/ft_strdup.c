#include "libft.h"
#include <stdlib.h>
#include <errno.h>

char	*ft_strdup(const char *s1)
{
	char	*tmp;

	if ((tmp = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char))) == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	return (ft_strcpy(tmp, s1));
}
