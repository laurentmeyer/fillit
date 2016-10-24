#include "fillit.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#define MAX 26
#define LINES 4
#define LENGTH 4
#define PTS 4
#define CDS 2
#define ERR -1
#define EMPTY '.'
#define TAKEN '#'

void	print_coords(int coords[MAX][PTS][CDS], int n)
{
	int p;
	int i;

	i = 0;
	while (i < n)
	{
		p = 0;
		while (p < PTS)
		{
			printf("(%d, %d)", coords[i][p][0], coords[i][p][1]);
			p++;
		}
		printf("\n");
		++i;
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

void	set_pt_coords(int *point, int line, int col)
{
	point[0] = line;
	point[1] = col;
	return ;
}

int		get_next_tetra(int fd, char **buf, int coords[MAX][PTS][CDS], int n)
{
	int		l;
	int		c;
	int		g;
	int		p;

	l = 0;
	p = 0;
	while (l < LINES)
	{
		if ((g = get_next_line(fd, buf)) == ERR || ft_strlen(*buf) != LENGTH)
			return (ERR);
		c = 0;
		while (c < LENGTH)
		{
			if ((*buf)[c] == '.')
				++c;
			else if ((*buf)[c] != '#' || p >= PTS)
				return (ERR);
			else
				set_pt_coords(coords[n][p++], l, c++);
		}
		++l;
	}
	return (g);
}

int		get_all_tetras(char *arg, int coords[MAX][PTS][CDS])
{
	char	*line;
	int		n;
	int		fd;
	int		g;

	line = ft_strdup("");
	if ((fd = open(arg, O_RDONLY)) == -1)
	{
		printf("error reading");
		return (ERR);
	}
	//	printf("fd = %d\n", fd);
	n = 0;
	while (42)
	{
		if ((g = get_next_tetra(fd, &line, coords, n++)) == ERR)
			return (ERR);
		if (get_next_line(fd, &line) == 0)
			return (n);
		else if (ft_strcmp("", line))
			return (ERR);
	}
}

void	normalize_tetras(int c[MAX][PTS][CDS], int n)
{
	int	i;
	int p;

	i = 0;
	while (i < n)
	{
		while (c[i][0][0] > 0 && c[i][1][0] > 0
				&& c[i][2][0] > 0 && c[i][3][0] > 0)
		{
			p = 0;
			while (p < PTS)
				--c[i][p++][0];
		}
		while (c[i][0][1] > 0 && c[i][1][1] > 0
				&& c[i][2][1] > 0 && c[i][3][1] > 0)
		{
			p = 0;
			while (p < PTS)
				--c[i][p++][1];
		}
		++i;
	}
}

int		ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

int		points_distance(int a[2], int b[2])
{
	return (ft_abs(a[0] - b[0]) + ft_abs(a[1] - b[1]));
}

int		verify_tetras(int c[MAX][PTS][CDS], int n)
{
	int	i;
	int	p;
	int q;
	int	isolated;

	i = 0;
	while (i < n)
	{
		p = 0;
		while (p < PTS)
		{
			isolated = 1;
			q = 0;
			while (q < PTS)
				if (q++ != p && points_distance(c[i][p], c[i][q - 1]) == 1)
					isolated = 0;
			if (isolated)
				return (ERR);
			++p;
		}
		++i;
	}
	return (1);
}

int		smallest_square(int t)
{
	int i;

	i = 0;
	while (i * i < PTS * t)
		++i;
	return (i);
}

int			equal_tetras(int a[PTS][CDS], int b[PTS][CDS])
{
	int	p;
	int	equal;

	p = 0;
	equal = 1;
	while (p < PTS)
	{
		if (a[p][0] != b[p][0] || a[p][1] != b[p][1])
			equal = 0;
		++p;
	}
	return (equal);
}

void		find_same_tetras(int pos[MAX + 1][2], int c[MAX][PTS][CDS])
{
	int	i;
	int	j;

	i = 1;
	while (pos[i][0] != -1)
	{
		j = 0;
		while (j < i)
		{
			if (equal_tetras(c[i], c[j]))
				pos[i][0] = j;
			++j;
		}
		++i;
	}
}

void		init_pos(int pos[MAX + 1][2], int t)
{
	int	i;

	i = 0;
	while (i < t)
	{
		pos[i][0] = i;
		pos[i][1] = i;
		++i;
	}
	while (i < MAX)
	{
		pos[i][0] = -1;
		pos[i][1] = -1;
		++i;
	}
}

void	print_pos(int pos[MAX + 1][2])
{
	int	i;

	i = 0;
	while (pos[i][0] != -1)
	{
		printf("tetra : %c || position : %d\n", pos[i][0] + 'A', pos[i][1]);
		++i;
	}
}

char	*make_bigger_square(char *s, int side)
{
	free (s);
	if ((s = ft_strnew((side + 1) * (side + 1))) == NULL)
		return (NULL);
	return (s);
}

//int		next_tetra(char *s)
//{
//	int	i;
//	int	res;
//
//	while (s[i])
//	{
//		if (s[i] == 

void	remove_tetras(char *s, int n)
{
	int	i;

	while (s[i])
	{
		if (s[i] - 'A' >= n)
			s[i] = '.';
		++i;
	}
}
int		is_available_square(char *s, int side, int c[CDS], int ref[CDS])
{
	if (c[0] + ref[0] > side - 1
			|| c[1] + ref[1] > side - 1
			|| *(s + (c[0] + ref[0]) * side + c[1] + ref[1]) != '.')
		return (0);
	return (1);
}

int		find_available(char *s, int start, int c[MAX][PTS][CDS], int t)
{
	int	ref[2];
	int	p;
	int	side;
	int	found;

	side = ft_sq_root(ft_strlen(s));
//	printf("side = %d\n", side);
	ref[0] = start / side;
	ref[1] = start % side;
	while (ref[0] < side)
	{
		while (ref[1] < side)
		{
			p = 0;
			found = 1;
			while (p++ < PTS)
				if (!is_available_square(s, side, c[t][p - 1], ref))
					found = 0;
			if (found == 1)
				return (ref[0] * side + ref[1]);
			++ref[1];
		}
		ref[1] = 0;
		++ref[0];
	}
	return (ERR);
}

int		place_tetras(int c[MAX][PTS][CDS], int pos[MAX + 1][2], char *s, int n)
{
	int	side;
	int start;

	if (pos[n][0] == -1)
		return (1);
	remove_tetras(s, n);
	side = ft_sq_root(ft_strlen(s));
	start = 
	


/*	pos[0] indicates the previous similar tetra. If tetra B and F are identical
	then pos[5][0] = 1.*/
int		main(int ac, char **av)
{
	int		coords[MAX][PTS][CDS];
	int		pos[MAX + 1][2];
	int		t;
	int		side;
	char	*result;


	if (ac != 2)
		printf("usage ...\n");
	if ((t = get_all_tetras(av[1], coords)) == ERR
			|| verify_tetras(coords, t) == ERR)
		printf("error\n");
	else
	{
		normalize_tetras(coords, t);
		print_coords(coords, t);
		init_pos(pos, t);
		find_same_tetras(pos, coords);
		print_pos(pos);
		side = smallest_square(t);
		if (!(result = ft_strnew(side * side)))
			printf("error\n");
	}
	return (0);
}
