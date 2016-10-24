#include "fillit.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void	print_coords(t_tetra *list)
{
	int	p;

	while (list)
	{
		printf("tetra #%d : ", list->number);
		p = 0;
		while (p < PTS)
		{
			printf("(%d, %d)", list->pts[p][0], list->pts[p][1]);
			p++;
		}
		printf(" in position %d", list->position);
		if (list->same)
			printf(" similar to #%d", list->same->number);
		printf("\n");
		list = list->next;
	}
}

int		count_occurences(char *s, char c)
{
	int	i;
	int	acc;

	i = 0;
	acc = 0;
	while (s[i])
		if (s[i++] == c)
			++acc;
	return (acc);
}

int		verify_tetra(char *buf)
{
	int	i;

	i = 0;
	while (i < LINES)
		if (buf[5 * i++ + 4] != '\n')
			return (0);
	if (count_occurences(buf, '.') != 12 || count_occurences(buf, '#') != 4)
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

void	normalize_points(int t[PTS][CDS])
{
	int p;

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

t_tetra	*newtetra(char *s, int num)
{
	t_tetra	*t;
	int		i;
	int		p;

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

t_tetra	*push_tetra(t_tetra **alist, char *line)
{
	t_tetra	*tmp;
	t_tetra *cur;
	int		i;

	if (*alist == NULL)
		return ((tmp = newtetra(line, 0)) ? (*alist = tmp) : NULL);
	cur = *alist;
	i = 1;
	while (cur->next)
	{
		cur = cur->next;
		++i;
	}
	return ((tmp = newtetra(line, i)) ? (cur-> next = tmp) : NULL);
}

int		get_all_tetras(char *arg, t_tetra **alist)
{
	char	*line;
	int		fd;

	if ((fd = open(arg, O_RDONLY)) == -1 || !(line = ft_strnew(20)))
		return (ERR);
	while (42)
	{
		if (read(fd, line, 20) != 20
				|| !verify_tetra(line)
				|| push_tetra(alist, line) == NULL)
			return (ERR);
		if (read(fd, line, 1) == 0)
			return (1);
		else if (line[0] != '\n')
			return (ERR);
	}
}

int			equal_tetras(t_tetra *a, t_tetra *b)
{
	int	p;
	int	equal;

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

void		find_same_tetras(t_tetra *list)
{
	t_tetra	*cur;
	t_tetra	*tmp;

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

int		list_len(t_tetra *list)
{
	int	i;

	i = 0;
	while (list)
	{
		++i;
		list = list->next;
	}
	return (i);
}

int		smallest_square(int t)
{
	int i;

	i = 0;
	while (i * i < PTS * t)
		++i;
	return (i);
}

t_tetra	*find_tetra(t_tetra *list, int t)
{
	while (list->number != t)
		list = list->next;
	return (list);
}

int		valid_position(char *s, int side, int pt[PTS][CDS], int ref[CDS])
{
	int	p;

	p = 0;
	while (p < PTS)
	{
		if (pt[p][0] + ref[0] > side - 1
				|| pt[p][1] + ref[1] > side - 1
				|| s[(pt[p][0] + ref[0]) * side + pt[p][1] + ref[1]] != '.')
			return (0);
		++p;
	}
	return (1);
}

int		find_available(char *s, int side, t_tetra *list, int t)
{
	int		ref[2];
	t_tetra *tmp;

	tmp = find_tetra(list, t);
	ref[0] = tmp->position / side;
	ref[1] = tmp->position % side;
	while (ref[0] < side)
	{
		while (ref[1] < side)
		{
			if (valid_position(s, side, tmp->pts, ref))
				return (ref[0] * side + ref[1]);
			++ref[1];
		}
		ref[1] = 0;
		++ref[0];
	}
	return (ERR);
}

void	reset_from(char *s, t_tetra *list, int pos, char letter)
{
	while (*s)
	{
		if (*s >= letter)
			*s = '.';
		++s;
	}
	list = (find_tetra(list, pos));
	while (list)
	{
		list->position = list->same ? list->same->position + 1 : 0;
		list = list->next;
	}
}

char	*make_bigger_square(char *s, int side, t_tetra *list)
{
	free (s);
	if ((s = ft_strnew((side + 1) * (side + 1))) == NULL)
		return (NULL);
	reset_from(s, list, 0, 'A');
	return (s);
}

void	insert_tetra(char *s, int side, t_tetra *list, int t)
{
	int		p;
	t_tetra *tmp;

	p = 0;
	tmp = find_tetra(list, t);
	while (p < PTS)
	{
		s[tmp->position + tmp->pts[p][0] * side + tmp->pts[p][1]] = tmp->number + 'A';
		++p;
	}
}

int		increment_position(t_tetra *list, int t, int side)
{
	t_tetra	*tmp;

	tmp = find_tetra(list, t);
	if (tmp->position < side * side - 1)
	{
		++(tmp->position);
		return (t);
	}
	else
		return (t == 0 ? ERR : increment_position(list, t - 1, side));
}


int		place_tetras(char *s, int side, t_tetra *list, int t)
{
	int	pos;

	if ((pos = find_available(s, side, list, t)) != ERR)
	{
		(find_tetra(list, t))->position = pos;
		insert_tetra(s, side, list, t);
		if (t == list_len(list) - 1)
			return (1);
		return (place_tetras(s, side, list, t + 1));
	}
	else
	{
		if (t == 0)
		{
			if ((s = make_bigger_square(s, side, list)) == NULL)
				return (ERR);
			++side;
		}
		else
			t = increment_position(list, t - 1, side);
		reset_from(s, list, t + 1, t + 'A');
		return (place_tetras(s, side, list, t));
	}
}

int		ft_sq_root(int n)
{
	int i;

	i = 0;
	while (i * i < n)
		++i;
	return (i);
}

void	print_square(char *result)
{
	int	side;
	int	i;

	side = ft_sq_root(ft_strlen(result));
	i = 0;
	while (result[i])
	{
		if ((i + 1) % side == 0)
			printf("%c\n", result[i]);
		else
			printf("%c", result[i]);
		++i;
	}
}



int		main(int ac, char **av)
{
	t_tetra	*tetras;
	char	*result;
	int		side;

	tetras = NULL;
	if (ac != 2)
		printf("usage ...\n");
	else if (get_all_tetras(av[1], &tetras) == ERR)
		printf("error\n");
	else
	{
		find_same_tetras(tetras);
		side = smallest_square(list_len(tetras));
		if (!(result = ft_strnew(side * side)))
			printf("error\n");
		ft_memset(result, '.', side * side);
//		insert_tetra(result, side, tetras, 0);
		if (place_tetras(result, side, tetras, 0) == ERR)
			printf("error\n");
		else
			print_square(result);
	}
	return (0);
}
