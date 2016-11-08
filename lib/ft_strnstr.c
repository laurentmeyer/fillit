/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmenzagh <hmenzagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:33:48 by hmenzagh          #+#    #+#             */
/*   Updated: 2016/11/06 13:45:47 by hmenzagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	c;
	int		i;

	c = 0;
	i = 0;
	if (!*little)
		return ((char*)big);
	while (big[c] && c < len)
	{
		i = 0;
		while (big[c + i] == little[i] && c + i < len)
			if (little[1 + i++] == '\0')
				return ((char*)&big[c]);
		c++;
	}
	return (0);
}
