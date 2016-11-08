/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmenzagh <hmenzagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:54:19 by hmenzagh          #+#    #+#             */
/*   Updated: 2016/11/07 12:46:03 by hmenzagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*ptr_actual;
	t_list		*freturn;
	t_list		*ptr_save;

	ptr_save = NULL;
	if (lst)
	{
		freturn = (*f)(lst);
		if (!(ptr_save = ft_lstnew(freturn->content, freturn->content_size)))
			return (NULL);
		ptr_actual = ptr_save;
		lst = lst->next;
		while (lst)
		{
			freturn = (*f)(lst);
			if (!(ptr_actual->next = ft_lstnew(freturn->content,
												freturn->content_size)))
				return (NULL);
			ptr_actual = ptr_actual->next;
			lst = lst->next;
		}
	}
	return (ptr_save);
}
