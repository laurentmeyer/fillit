#ifndef FILLIT_H
# define FILLIT_H
# define MAX 26
# define LINES 4
# define LENGTH 4
# define PTS 4
# define CDS 2
# define ERR -1
# define EMPTY '.'
# define TAKEN '#'

typedef	struct			s_tetra
{
	int					pts[PTS][CDS];
	int					number;
	int					position;
	struct	s_tetra		*same;
	struct	s_tetra		*next;
}						t_tetra;

typedef	struct			s_square
{
	char				*s;
	int					placed;
	int					side;
}						t_square;

#endif
