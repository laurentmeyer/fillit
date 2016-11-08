/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetra_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmenzagh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 15:44:30 by hmenzagh          #+#    #+#             */
/*   Updated: 2016/11/08 16:56:17 by hmenzagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fillit.h"

int						valid_position(t_square *sq, t_tetra *list)
{
	int					p;
	int					l;
	int					c;
	t_tetra				*tmp;
	int					t;

	t = sq->placed;
	tmp = find_tetra(list, t);
	l = tmp->position / sq->side;
	c = tmp->position % sq->side;
	p = 0;
	while (p < PTS)
	{
		if (tmp->pts[p][0] + l > sq->side - 1
			|| tmp->pts[p][1] + c > sq->side - 1
			|| sq->s[(tmp->pts[p][0] + l) * sq->side
			+ tmp->pts[p][1] + c] != '.')
			return (0);
		++p;
	}
	return (1);
}

int						find_available(t_square *sq, t_tetra *list)
{
	t_tetra				*tmp;

	tmp = find_tetra(list, sq->placed);
	while (tmp->position < sq->side * sq->side - 1)
	{
		if (valid_position(sq, list))
			return (1);
		++(tmp->position);
	}
	return (ERR);
}

void					insert_tetra(t_square *sq, t_tetra *list)
{
	int					p;
	t_tetra				*tmp;
	char				*s;

	p = 0;
	tmp = find_tetra(list, sq->placed);
	s = sq->s;
	while (p < PTS)
	{
		s[tmp->position + tmp->pts[p][0] * sq->side
			+ tmp->pts[p][1]] = tmp->number + 'A';
		++p;
	}
	++(sq->placed);
}

void					place_tetras(t_square *sq, t_tetra *list)
{
	int					pos;

	if ((pos = find_available(sq, list)) == ERR && sq->placed == 0)
	{
		if (!make_bigger_square(sq, list))
			exit(1);
	}
	else if (pos == ERR && sq->placed > 0)
	{
		--(sq->placed);
		reset_from(sq, list, sq->placed + 1, sq->placed + 'A');
		++((find_tetra(list, sq->placed))->position);
	}
	else
		insert_tetra(sq, list);
}
