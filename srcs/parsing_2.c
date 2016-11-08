/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmenzagh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 15:49:44 by hmenzagh          #+#    #+#             */
/*   Updated: 2016/11/08 17:13:59 by hmenzagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fillit.h"

int					count_occurences(char *s, char c)
{
	int				i;
	int				acc;

	i = 0;
	acc = 0;
	while (s[i])
		if (s[i++] == c)
			++acc;
	return (acc);
}

int					verif_neighbour(char *buf)
{
	int				i;
	int				check;

	i = 0;
	check = 0;
	while (buf[i])
	{
		if (buf[i] != '#')
			++i;
		else
		{
			check += (i + 5 < 20 && buf[i + 5] == '#') ? 1 : 0;
			check += (i - 5 >= 0 && buf[i - 5] == '#') ? 1 : 0;
			check += (i + 1 < 20 && buf[i + 1] == '#') ? 1 : 0;
			check += (i - 1 >= 0 && buf[i - 1] == '#') ? 1 : 0;
			if (check >= 2)
				return (1);
			check = 0;
			++i;
		}
	}
	return (0);
}

int					verify_tetra(char *buf)
{
	int				i;

	i = 0;
	while (i < LINES)
		if (buf[5 * i++ + 4] != '\n')
			return (0);
	if (count_occurences(buf, '.') != 12 || count_occurences(buf, '#') != 4 ||
			!verif_neighbour(buf))
		return (0);
	i = 0;
	while (buf[i])
	{
		if (buf[i] != '#')
			++i;
		else if ((i - 5 >= 0 && buf[i - 5] == '#')
				|| (i - 1 >= 0 && buf[i - 1] == '#')
				|| (i + 1 < 20 && buf[i + 1] == '#')
				|| (i + 5 < 20 && buf[i + 5] == '#'))
			++i;
		else
			return (0);
	}
	return (1);
}
