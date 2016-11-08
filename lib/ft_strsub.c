/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmenzagh <hmenzagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:45:14 by hmenzagh          #+#    #+#             */
/*   Updated: 2016/11/07 13:06:35 by hmenzagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*chaine;
	unsigned int	i;

	i = 0;
	chaine = NULL;
	if (s)
	{
		if (!(chaine = malloc((len + 1) * sizeof(char))))
			return (NULL);
		while (i < len)
		{
			chaine[i] = s[i + start];
			++i;
		}
		chaine[i] = '\0';
	}
	return (chaine);
}
