/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmenzagh <hmenzagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:45:29 by hmenzagh          #+#    #+#             */
/*   Updated: 2016/11/07 12:58:42 by hmenzagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	int		i;
	int		y;
	char	*chaine;

	chaine = NULL;
	if (s1 && s2)
	{
		len = ft_strlen(s1) + ft_strlen(s2);
		i = 0;
		y = 0;
		if (!(chaine = ft_strnew(len + 1)))
			return (NULL);
		while (s1[y] && i < len)
			chaine[i++] = s1[y++];
		y = 0;
		while (s2[y] && i < len)
			chaine[i++] = s2[y++];
	}
	return (chaine);
}
