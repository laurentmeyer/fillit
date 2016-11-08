/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmenzagh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 16:00:58 by hmenzagh          #+#    #+#             */
/*   Updated: 2016/11/08 17:28:20 by hmenzagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"

t_tetra			*newtetra(char *s, int num)
{
	t_tetra		*t;
	int			i;
	int			p;

	if ((t = (t_tetra *)malloc(sizeof(t_tetra))))
	{
		i = 0;
		p = 0;
		while (s[i])
			if (s[i++] == '#')
			{
				t->pts[p][0] = (i - 1) / 5;
				t->pts[p++][1] = (i - 1) % 5;
			}
		normalize_points(t->pts);
		t->number = num;
		t->position = 0;
		t->next = NULL;
		t->same = NULL;
	}
	return (t);
}

t_tetra			*push_tetra(t_tetra **alist, char *line)
{
	t_tetra				*tmp;
	t_tetra				*cur;
	int					i;

	if (*alist == NULL)
	{
		if ((tmp = newtetra(line, 0)))
			return ((*alist = tmp));
		return (NULL);
	}
	cur = *alist;
	i = 1;
	while (cur->next)
	{
		cur = cur->next;
		++i;
	}
	if ((tmp = newtetra(line, i)))
		return (cur->next = tmp);
	return (NULL);
}

t_tetra			*find_tetra(t_tetra *list, int t)
{
	while (list->number != t)
		list = list->next;
	return (list);
}

void			reset_from(t_square *sq, t_tetra *list, int pos, char letter)
{
	char		*s;

	s = sq->s;
	while (*s)
	{
		if (*s >= letter)
			*s = '.';
		++s;
	}
	list = (find_tetra(list, pos));
	while (list)
	{
		list->position = (list->same ? list->same->position : 0);
		list = list->next;
	}
}

void			find_same_tetras(t_tetra *list)
{
	t_tetra		*cur;
	t_tetra		*tmp;

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
