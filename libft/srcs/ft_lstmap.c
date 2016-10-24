#include "libft.h"
#include <stdlib.h>
#include <string.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*nxt;
	t_list	*tmp;

	nxt = lst->next;
	tmp = (*f)(lst);
	if ((new = ft_lstnew(tmp->content, tmp->content_size)) == NULL)
		return (NULL);
	else if (!nxt)
		return (new);
	else if ((tmp = ft_lstmap(nxt, f)) == NULL)
	{
		free(new);
		return (NULL);
	}
	else
	{
		new->next = tmp;
		return (new);
	}
}
