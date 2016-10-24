#include "libft.h"
#include <string.h>
#include <stdlib.h>

void	ft_strdel(char **as)
{
	free(*as);
	*as = NULL;
}
