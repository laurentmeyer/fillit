/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmenzagh <hmenzagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:43:45 by hmenzagh          #+#    #+#             */
/*   Updated: 2016/11/07 12:55:57 by hmenzagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ns;
	int		i;

	ns = NULL;
	if (s && (*f))
	{
		i = 0;
		if (!(ns = ft_strnew(ft_strlen(s))))
			return (NULL);
		while (s[i])
		{
			ns[i] = (*f)(i, s[i]);
			++i;
		}
	}
	return (ns);
}
