#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list	*tmp;

	tmp = lst->next;
	(*f)(lst);
	if (tmp)
		ft_lstiter(tmp, f);
}
