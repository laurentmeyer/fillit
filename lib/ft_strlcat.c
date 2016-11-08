/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmenzagh <hmenzagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:31:14 by hmenzagh          #+#    #+#             */
/*   Updated: 2016/11/06 14:15:27 by hmenzagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t size)
{
	int	len;
	int	j;
	int	save;
	int	save_1;
	int	save_2;

	j = 0;
	while (dst[j])
		j++;
	save_1 = ft_strlen(dst);
	save_2 = ft_strlen(src);
	save = j;
	len = 0;
	while (src[len] && (len + save_1) < (int)size - 1)
	{
		dst[j] = src[len];
		++j;
		++len;
	}
	if (j != save)
		dst[j] = '\0';
	if (save_1 > (int)size)
		return (save_2 + size);
	return (save_1 + save_2);
}
