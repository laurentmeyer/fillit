/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmenzagh <hmenzagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:29:11 by hmenzagh          #+#    #+#             */
/*   Updated: 2016/11/06 14:15:00 by hmenzagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s1)
{
	int		c;
	char	*cp;

	c = 0;
	while (s1[c])
		c++;
	c++;
	if (!(cp = malloc(c * sizeof(char))))
		return (NULL);
	c = 0;
	while (s1[c])
	{
		cp[c] = s1[c];
		c++;
	}
	cp[c] = '\0';
	return (cp);
}
