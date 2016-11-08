/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmenzagh <hmenzagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:56:41 by hmenzagh          #+#    #+#             */
/*   Updated: 2016/11/06 13:44:22 by hmenzagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *restrict s1, const char *restrict s2, size_t n)
{
	size_t	c;
	size_t	i;

	c = 0;
	i = 0;
	while (s1[c])
		++c;
	while (i < n && s2[i])
	{
		s1[c + i] = s2[i];
		++i;
	}
	s1[c + i] = '\0';
	return (s1);
}
