#ifndef GET_NEXT_LINE
# define GET_NEXT_LINE

# define BUFF_SIZE 32

typedef	struct		s_buf
{
	int				fd;
	int				end;
	int				iter;
	char			buf[BUFF_SIZE];
}					t_buf;

int		get_next_line(const int fd, char **line);

#endif
