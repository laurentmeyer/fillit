#include "libft.h"
#include <stdlib.h>
#include <string.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;

	if ((*alst)->next == NULL)
		ft_lstdelone(alst, del);
	else
	{
		tmp = (*alst)->next->next;
		del((*alst)->next->content, (*alst)->next->content_size);
		free((*alst)->next);
		(*alst)->next = tmp;
		ft_lstdel(alst, del);
	}
}
