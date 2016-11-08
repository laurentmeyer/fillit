/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmenzagh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 17:25:42 by hmenzagh          #+#    #+#             */
/*   Updated: 2016/11/08 17:26:55 by hmenzagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct	s_tetra
{
	int					pts[PTS][CDS];
	int					number;
	int					position;
	struct s_tetra		*same;
	struct s_tetra		*next;
}				t_tetra;
typedef struct	s_square
{
	char				*s;
	int					placed;
	int					side;
}				t_square;
void			find_same_tetras(t_tetra *list);
t_tetra			*newtetra(char *s, int num);
t_tetra			*push_tetra(t_tetra **alist, char *line);
t_tetra			*find_tetra(t_tetra *list, int t);
void			reset_from(t_square *sq, t_tetra *list, int pos, char letter);
void			same_tetras(t_tetra *list);
int				equal_tetras(t_tetra *a, t_tetra *b);
int				get_all_tetras(char *arg, t_tetra **alist);
void			normalize_points(int t[PTS][CDS]);
int				count_occurences(char *s, char c);
int				verify_tetra(char *buf);
void			print_square(t_square *sq);
int				make_bigger_square(t_square *sq, t_tetra *list);
int				smallest_square(int t);
t_square		*new_square(int side);
int				valid_position(t_square *sq, t_tetra *list);
int				find_available(t_square *sq, t_tetra *list);
void			insert_tetra(t_square *sq, t_tetra *list);
void			place_tetras(t_square *sq, t_tetra *list);
#endif
