/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmenzagh <hmenzagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:46:02 by hmenzagh          #+#    #+#             */
/*   Updated: 2016/11/06 13:48:23 by hmenzagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	char	*chaine;
	int		off;
	int		end;
	int		i;

	if (!s)
		return (NULL);
	off = 0;
	end = ft_strlen(s) - 1;
	i = 0;
	while (s[off] && (s[off] == ' ' || s[off] == '\t' || s[off] == '\n'))
		++off;
	while (end > off && (s[end] == ' ' || s[end] == '\t' || s[end] == '\n'))
		--end;
	if (!(chaine = malloc(sizeof(char) * (end - off + 2))))
		return (NULL);
	while (i < end - off + 1)
	{
		chaine[i] = s[off + i];
		i++;
	}
	chaine[i] = '\0';
	return (chaine);
}
