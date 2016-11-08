/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmenzagh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 15:44:50 by hmenzagh          #+#    #+#             */
/*   Updated: 2016/11/08 16:50:51 by hmenzagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fillit.h"

int				make_bigger_square(t_square *sq, t_tetra *list)
{
	free(sq->s);
	++(sq->side);
	if ((sq->s = ft_strnew(sq->side * sq->side)) == NULL)
		return (0);
	ft_memset(sq->s, '.', sq->side * sq->side);
	reset_from(sq, list, 0, 'A');
	sq->placed = 0;
	return (1);
}

int				smallest_square(int t)
{
	int			i;

	i = 0;
	while (i * i < PTS * t)
		++i;
	return (i);
}

t_square		*new_square(int side)
{
	t_square	*tmp;
	char		*str;

	if ((side > 1)
			&& (tmp = (t_square *)malloc(sizeof(t_square)))
			&& (str = ft_strnew(side * side)))
	{
		ft_memset(str, '.', side * side);
		tmp->s = str;
		tmp->side = side;
		tmp->placed = 0;
		return (tmp);
	}
	else
		return (NULL);
}
