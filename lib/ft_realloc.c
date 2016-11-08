/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmenzagh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 13:50:04 by hmenzagh          #+#    #+#             */
/*   Updated: 2016/11/07 14:01:16 by hmenzagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_realloc(void **data, size_t cp_len, size_t size_new)
{
	void	*ptr;

	if (!(ptr = ft_memalloc(size_new)))
		return (0);
	cp_len = (cp_len > size_new) ? size_new : cp_len;
	ft_memcpy(ptr, *data, cp_len);
	free(*data);
	*data = ptr;
	return (1);
}
