/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmenzagh <hmenzagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:20:30 by hmenzagh          #+#    #+#             */
/*   Updated: 2016/11/06 14:12:40 by hmenzagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_c;

	s_c = (unsigned char*)s;
	while (n > 0 && *s_c != (unsigned char)c)
	{
		s_c++;
		n--;
	}
	if (n == 0)
		return (NULL);
	else
		return (s_c);
}
