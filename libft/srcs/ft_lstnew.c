#include "libft.h"
#include <stdlib.h>
#include <string.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;
	void	*c;

	if ((new = (t_list *)malloc(sizeof(t_list))))
	{
		new->next = NULL;
		if (!content)
		{
			new->content = NULL;
			new->content_size = 0;
		}
		else
		{
			if ((c = ft_memalloc(content_size)) == NULL)
			{
				free(new);
				return (NULL);
			}
			new->content = ft_memcpy(c, content, content_size);
			new->content_size = content_size;
		}
	}
	return (new);
}
