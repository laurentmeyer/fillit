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

	i = 0;
	while (pos[i + 1][0] != -1)
	{
		j = i + 1;
		while (pos[j][0] != -1)
		{
			if (pos[i][0] != pos[j][0] && equal_tetras(c[i], c[j]))
				pos[j][0] = pos[i][0];
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

int		place_if_possible(int t[PTS][CDS], int origin, char *s, int side)
{
	int	available;
	int	p;
	int	l;
	int c;

	printf("pouet\n");
	available = 1;
	p = 0;
	while (p < PTS)
	{
		if ((l = t[p][0] + origin / side) >= side
				|| (c = t[p][1] + origin % side) >= side
				|| s[l * side + c] != EMPTY)
			available = 0;
		++p;
	}
	if (!available)
		return (0);
	p = 0;
	while (p < PTS)
	{
		s[origin + side * t[p][0] + t[p][1]] = TAKEN;
		++p;
	}
	printf("s = %s", s);
	return (1);
}

int		valid_pos(int c[MAX][PTS][CDS], int pos[MAX + 1][2], char *s, int side)
{
	int	i;

	ft_memset(s, EMPTY, side * side);
	i = 0;
	while (pos[i][0] != -1)
	{
		if (!place_if_possible(c[pos[i][0]], pos[i][1], s, side))
			return (0);
		++i;
	}
	return (1);
}

int		increment_pos(int pos[MAX + 1][2], int p, int side)
{
	int	i;
	int	j;
	int	same;

	printf("===========\n");
	printf("side = %d\n", side);
	print_pos(pos);
	if (pos[p][1] < side * side - PTS - 1)
	{
		++(pos[p][1]);
		i = p + 1;
		while (pos[i][0] != -1)
		{
			same = 0;
			j = 0;
			while (j < i)
				if (pos[i][0] == pos[j++][0])
					same = j - 1;
			pos[i][1] = same ? pos[same][1] + 1 : i - 1 - p;
			++i;
		}
		return (p);
	}
	return (p == 0 ? ERR : increment_pos(pos, p - 1, side));
}

char	*make_bigger_square(char *s, int side)
{
	free (s);
	if ((s = ft_strnew((side + 1) * (side + 1))) == NULL)
		return (NULL);
	return (s);
}

int		recur_pos(int c[MAX][PTS][CDS], int pos[MAX + 1][2], char *s, int side)
{
	int p;

	p = 0;
	while (pos[p][0] != -1) 
		++p;
	--p;
	while (!valid_pos(c, pos, s, side))
		if (increment_pos(pos, p, side) == -1)
		{
			printf("============================================================================================================================================================\n");
			if ((s = make_bigger_square(s, side)) == NULL)
				return (ERR);
			++side;
			init_pos(pos, p + 1);
			return (recur_pos(c, pos, s, side));
		}
	return (1);
}

void	make_str(int c[MAX][PTS][CDS], int pos[MAX + 1][2], char *s, int side)
{
	int t;
	int	p;

	ft_memset(s, EMPTY, side * side);
	t = 0;
	while (pos[t][0] != -1)
	{
		p = 0;
		while (p < PTS)
		{
			s[pos[t][1] + c[pos[t][1]][p][0] * side + c[pos[t][1]][p][1]] = t + 'A';
			++p;
		}
		++t;
	}
}



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
		printf("valid : %d\n", valid_pos(coords, pos, result, side));
		if (recur_pos(coords, pos, result, side) == -1)
			printf("error\n");
		print_pos(pos);
		make_str(coords, pos, result, side);
		print_square(result);
	}
	return (0);
}
