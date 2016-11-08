/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmenzagh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 13:33:39 by hmenzagh          #+#    #+#             */
/*   Updated: 2016/11/07 14:03:11 by hmenzagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstat(t_list *ptr, int pos)
{
	if (ptr)
	{
		while (ptr && pos > 0)
		{
			ptr = ptr->next;
			--pos;
		}
		if (!pos)
			return (ptr);
	}
	return (NULL);
}
