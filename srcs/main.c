/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmenzagh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 21:04:34 by hmenzagh          #+#    #+#             */
/*   Updated: 2016/11/08 17:49:41 by hmenzagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fillit.h"

int	main(int ac, char **av)
{
	t_tetra			*tetras;
	t_square		*sq;
	int				l;

	tetras = NULL;
	if (ac != 2)
		ft_putstr("usage: fillit file\n");
	else if ((l = get_all_tetras(av[1], &tetras)) == ERR
			|| !(sq = new_square(smallest_square(l))))
		ft_putstr("error\n");
	else
	{
		find_same_tetras(tetras);
		while (sq->placed != l)
			place_tetras(sq, tetras);
		print_square(sq);
	}
	return (0);
}
