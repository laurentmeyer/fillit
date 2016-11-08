/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmenzagh <hmenzagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:12:38 by hmenzagh          #+#    #+#             */
/*   Updated: 2016/11/06 14:12:47 by hmenzagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_c;
	unsigned char	*s2_c;

	s1_c = (unsigned char*)s1;
	s2_c = (unsigned char*)s2;
	while (n > 0)
	{
		if (*s1_c != *s2_c)
			return (*s1_c - *s2_c);
		++s1_c;
		++s2_c;
		--n;
	}
	return (0);
}
