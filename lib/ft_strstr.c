/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmenzagh <hmenzagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:34:18 by hmenzagh          #+#    #+#             */
/*   Updated: 2016/11/05 16:34:23 by hmenzagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char		*ft_strstr(const char *big, const char *little)
{
	int		c;
	int		i;

	c = 0;
	i = 0;
	if (!*little)
		return ((char*)big);
	while (big[c])
	{
		i = 0;
		while (big[c + i] == little[i])
			if (little[1 + i++] == '\0')
				return ((char*)&big[c]);
		c++;
	}
	return (0);
}
