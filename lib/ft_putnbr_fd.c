/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmenzagh <hmenzagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:50:44 by hmenzagh          #+#    #+#             */
/*   Updated: 2016/11/06 14:14:11 by hmenzagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr_fd(int n, int fd)
{
	char	c;
	long	x;

	x = n;
	if (n < 0)
	{
		write(fd, "-", 1);
		x = -x;
	}
	c = 0;
	if (x >= 10)
	{
		ft_putnbr_fd(x / 10, fd);
		ft_putnbr_fd(x % 10, fd);
	}
	if (x < 10)
	{
		c = (x + '0');
		write(fd, &c, 1);
	}
}
