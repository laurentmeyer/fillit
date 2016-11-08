/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmenzagh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 15:44:09 by hmenzagh          #+#    #+#             */
/*   Updated: 2016/11/08 17:48:00 by hmenzagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"

void				same_tetras(t_tetra *list)
{
	t_tetra			*cur;
	t_tetra			*tmp;

	if (list == NULL || list->next == NULL)
		return ;
	cur = list->next;
	while (cur)
	{
		tmp = list;
		while (tmp->number < cur->number)
		{
			if (equal_tetras(tmp, cur))
				cur->same = tmp;
			tmp = tmp->next;
		}
		cur = cur->next;
	}
}

int					equal_tetras(t_tetra *a, t_tetra *b)
{
	int				p;
	int				equal;

	p = 0;
	equal = 1;
	while (p < PTS)
	{
		if (a->pts[p][0] != b->pts[p][0] || a->pts[p][1] != b->pts[p][1])
			equal = 0;
		++p;
	}
	return (equal);
}

int					get_all_tetras(char *arg, t_tetra **alist)
{
	char			*line;
	int				fd;
	int				i;

	if ((fd = open(arg, O_RDONLY)) == -1)
		return (ERR);
	if (!(line = ft_strnew(20)))
		return (ERR);
	i = 0;
	while (42)
	{
		if (read(fd, line, 20) != 20
				|| !verify_tetra(line)
				|| push_tetra(alist, line) == NULL)
			return (ERR);
		++i;
		if (read(fd, line, 1) == 0)
		{
			close(fd);
			free(line);
			return (i);
		}
		else if (line[0] != '\n')
			return (ERR);
	}
}

void				normalize_points(int t[PTS][CDS])
{
	int				p;

	while (t[0][0] > 0 && t[1][0] > 0
			&& t[2][0] > 0 && t[3][0] > 0)
	{
		p = 0;
		while (p < PTS)
			--t[p++][0];
	}
	while (t[0][1] > 0 && t[1][1] > 0
			&& t[2][1] > 0 && t[3][1] > 0)
	{
		p = 0;
		while (p < PTS)
			--t[p++][1];
	}
}
