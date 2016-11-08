/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmenzagh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 15:57:19 by hmenzagh          #+#    #+#             */
/*   Updated: 2016/11/08 17:34:44 by hmenzagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"

void			print_square(t_square *sq)
{
	int			i;

	i = 0;
	while (sq->s[i])
	{
		if ((i + 1) % sq->side == 0)
		{
			ft_putchar(sq->s[i]);
			ft_putchar('\n');
		}
		else
		{
			ft_putchar(sq->s[i]);
		}
		++i;
	}
}
