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


void	print_square(t_square *sq)
{
	int	i;

	i = 0;
	while (sq->s[i])
	{
		if ((i + 1) % sq->side == 0)
			printf("%c\n", sq->s[i]);
		else
			printf("%c", sq->[i]);
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
	int		i;

	if ((fd = open(arg, O_RDONLY)) == -1 || !(line = ft_strnew(20)))
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
			return (i);
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

//int		list_len(t_tetra *list)
//{
//	int	i;
//
//	i = 0;
//	while (list)
//	{
//		++i;
//		list = list->next;
//	}
//	return (i);
//}

int		smallest_square(int t)
{
	int i;

	i = 0;
	while (i * i < PTS * t)
		++i;
	return (i);
}

//void	set_side(t_tetra *list, int side)
//{
//	while (list)
//	{
//		list->side = side;
//		list = list->next;
//	}
//}

t_tetra	*find_tetra(t_tetra *list, int t)
{
	while (list->number != t)
		list = list->next;
	return (list);
}

int		valid_position(char *s, t_tetra *list, int t)
{
	int		p;
	int		l;
	int		c;
	t_tetra	*tmp;
	int		side;

	tmp = find_tetra(list, t);
	side = tmp->side;
	l = tmp->position / side;
	c = tmp->position % side;
	p = 0;
	while (p < PTS)
	{
		if (tmp->pts[p][0] + l > side - 1
				|| tmp->pts[p][1] + c > side - 1
				|| s[(tmp->pts[p][0] + l) * side + tmp->pts[p][1] + c] != '.')
			return (0);
		++p;
	}
	return (1);
}

int		find_available(, t_tetra *list, int t)
{
	t_tetra *tmp;

//	ft_putstr("let's find ");
//	ft_putnbr(t);
//	ft_putstr("\n");
	tmp = find_tetra(list, t);
	while (tmp->position < tmp->side * tmp->side - 1)
	{
		if (valid_position(s, list, t))
			return (1);
		++(tmp->position);
	}
	return (ERR);
}

void	reset_from(t_square *sq, t_tetra *list, int pos, char letter)
{
	char *s;

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
//		list->position = 0;
		list = list->next;
	}
}

void	insert_tetra(t_square *sq, t_tetra *list, int t)
{
	int		p;
	t_tetra *tmp;
	char	*s;

	p = 0;
	tmp = find_tetra(list, t);
	s = sq->s;
	while (p < PTS)
	{
		s[tmp->position + tmp->pts[p][0] * tmp->side + tmp->pts[p][1]]
			= tmp->number + 'A';
		++p;
	}
}

//int		next_missing_tetra(char *s)
//{
//	char	max;
//
//	max = '.';
//	while (*s)
//	{
//		if (*s > max)
//			max = *s;
//		++s;
//	}
//	return (max == '.' ? 0 : max - 'A' + 1);
//}

int		make_bigger_square(t_square *sq)
{
	char	*tmp;

	free (sq->s);
	++(sq->side);
	if ((sq->s = ft_strnew(sq->side * sq->side)) == NULL)
		return (0);
	ft_memset(sq->s, '.', sq->side * sq->side);
	reset_from(sq, list, 0, 'A');
	return (1);
}

void		place_tetras(t_square *sq, t_tetra *list)
{
	int		pos;
	int		t;

	printf("====\n");
	print_square(s);
	print_coords(list);

	if ((pos = find_available(sq->s, list, (t = sq->placed))) == ERR && t == 0)
		if (!make_bigger_square(sq))
			return (ERR);													//exit ??!!
	else if (pos == ERR && t > 0)
	{
		++((find_tetra(list, t - 1))->position);
		reset_from(sq, list, t, t - 1 + 'A');
	}
	else
		insert_tetra(sq, list, t);
}

t_square	*new_square(int side)
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


int		main(int ac, char **av)
{
	t_tetra		*tetras;
	t_square	*sq;
	int			l;

	tetras = NULL;
	if (ac != 2)
		printf("usage ...\n");
	else if ((l = get_all_tetras(av[1], &tetras)) == ERR
			|| !(sq = smallest_square(list_len(tetras))))
		printf("error\n");
	else
	{
		find_same_tetras(tetras);
		print_coords(tetras);
		printf("list length : %d\n", l);
		while (sq->placed != l)
			place_tetras(sq, tetras);
		print_square(result);
	}
	return (0);
}
