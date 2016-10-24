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
		printf("tetra #%c : ", list->number + 'A');
		p = 0;
		while (p < PTS)
		{
			printf("(%d, %d)", list->pts[p][0], list->pts[p][1]);
			p++;
		}
		printf(" in position %d", list->position);
		if (list->same)
			printf(" similar to #%c", list->same->number + 'A');
		printf("\n");
		list = list->next;
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
		t->side = 0;
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

void	set_side(t_tetra *list, int side)
{
	while (list)
	{
		list->side = side;
		list = list->next;
	}
}

t_tetra	*find_tetra(t_tetra *list, int t)
{
	while (list->number != t)
		list = list->next;
	return (list);
}

int		valid_position(char *s, int side, int pt[PTS][CDS], int start)
{
	int	p;
	int l;
	int	c;

	l = start / side;
	c = start % side;
	p = 0;
	while (p < PTS)
	{
		if (pt[p][0] + l > side - 1
				|| pt[p][1] + c > side - 1
				|| s[(pt[p][0] + l) * side + pt[p][1] + c] != '.')
			return (0);
		++p;
	}
	return (1);
}

int		find_available(char *s, t_tetra *list, int t)
{
	t_tetra *tmp;
	int		start;

	if ((tmp = find_tetra(list, t)) == NULL)
		return (ERR);
	start = tmp->position;
	while (start < tmp->side * tmp->side - 1)
	{
		if (valid_position(s, tmp->side, tmp->pts, start))
			return (start);
		++start;
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
		list->position = (list->same ? list->same->position : 0);
//		list->position = 0;
		list = list->next;
	}
}

char	*make_bigger_square(char *s, t_tetra *list)
{
	int		side;

	free (s);
	side = list->side + 1;
	if ((s = ft_strnew(side * side)) == NULL)
		return (NULL);
	ft_memset(s, '.', side * side);
	set_side(list, side);
	reset_from(s, list, 0, 'A');
	return (s);
}

void	insert_tetra(char *s, t_tetra *list, int t)
{
	int		p;
	t_tetra *tmp;

	p = 0;
	tmp = find_tetra(list, t);
	while (p < PTS)
	{
		s[tmp->position + tmp->pts[p][0] * tmp->side + tmp->pts[p][1]]
			= tmp->number + 'A';
		++p;
	}
}

//int		increment_position(char *s, t_tetra *list, int t)
//{
//	t_tetra	*tmp;
//
//	tmp = ;
//	if (tmp->position < (tmp->side * tmp->side - 1))
//	{
//		++(tmp->position);
//		//printf("incrementing position of %c to value of %d\n", t + 'A', tmp->position);
//		reset_from(s, list, t + 1, t + 'A');
//		return (t);
//	}
//	return (t <= 0 ? ERR : increment_position(s, list, t - 1));
//}


int		place_tetras(char *s, t_tetra *list, int t)
{
	int	pos;

//	printf("====\n");
//	print_square(s);
//	print_coords(list);
//	printf("t = %d\n", t);
	if (t <= ERR)
		return (ERR);
	if (t == list_len(list))
	{
		print_square(s);
		return (1);
	}
	pos = find_available(s, list, t);
	printf("pos = %d\n", pos);
	if (pos == ERR && t == 0)
		return (place_tetras(make_bigger_square(s, list), list, t));
	if (pos == ERR && t > 0)
	{
		++((find_tetra(list, t - 1))->position);
		reset_from(s, list, t, t - 1 + 'A');
		return (place_tetras(s, list, t - 1));
	}
	(find_tetra(list, t))->position = pos;
	insert_tetra(s, list, t);
	return (place_tetras(s, list, t + 1));
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
		print_coords(tetras);
		printf("list length : %d\n", list_len(tetras));
		side = smallest_square(list_len(tetras));
		set_side(tetras, side);
		if (!(result = ft_strnew(side * side)))
			printf("error\n");
		ft_memset(result, '.', side * side);
		//		printf("position : %d\n", find_available(result, side, tetras, 0));
		//		insert_tetra(result, side, tetras, 0);
		if (place_tetras(result, tetras, 0) == ERR)
			printf("error\n");
	}
	return (0);
}
