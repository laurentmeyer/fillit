#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "get_next_line.h"
#define ERR -1

static	t_buf	*ft_find_buffer(t_list **buffers, int fd)
{
	t_list		*new;
	int			r;

	new = *buffers;
	while (new != NULL)
	{
		if (new->content_size == (size_t)fd)
			return (new->content);
		new = new->next;
	}
	if ((new = ft_lstnew((t_buf *)malloc(sizeof(t_buf)), sizeof(t_buf))))
	{
		if ((r = read(fd, ((t_buf *)(new->content))->buf, BUFF_SIZE)) == ERR)
		{
			free(new);
			return (NULL);
		}
		ft_lstadd(buffers, new);
		((t_buf *)(new->content))->fd = fd;
		((t_buf *)(new->content))->iter = 0;
		((t_buf *)(new->content))->end = (r == BUFF_SIZE ? -1 : r);
		new->content_size = fd;
	}
	return (new ? new->content : NULL);
}

int			ft_refill(t_buf *b, int bytes)
{
	int		r;

	ft_memmove(b->buf, b->buf + bytes, BUFF_SIZE - bytes);
	if ((r = read(b->fd, b->buf + BUFF_SIZE - bytes, bytes)) == ERR)
		return (ERR);
	else if (r != bytes && b->end == -1)
		b->end = BUFF_SIZE - bytes + r;
	else if (r != bytes && b->end != -1)
		b->end -= bytes + r;
	return (0);
}

int			ft_append(char **adest, t_buf *b, int n, int reinit)
{
	char	*res;

	if (!(res = ft_strnew(b->iter * BUFF_SIZE + n))
			|| !(ft_memcpy(res, *adest, b->iter * BUFF_SIZE))
			|| !(ft_memcpy(res + b->iter * BUFF_SIZE, b->buf, n)))
		return (ERR);
	else
	{
		if (*adest)
			free(*adest);
		*adest = res;
		if (reinit)
			b->iter = 0;
		return (1);
	}
}

int			find_end(t_buf *b, char **line)
{
	char	*pos;

	if (b->end != -1 && (pos = ft_memchr(b->buf, '\n', b->end)) == NULL)
		return (ft_append(line, b, b->end, 1) == ERR ? ERR : 0);
	else if (b->end != -1 && pos != NULL)
	{
		if (ft_append(line, b, pos - b->buf, 1) == ERR)
			return (ERR);
		return (ft_refill(b, pos - b->buf + 1) == ERR ? ERR : 1);
	}
	else if (b->end == -1 && (pos = ft_memchr(b->buf, '\n', BUFF_SIZE)))
		return (ft_append(line, b, pos - b->buf, 1) == ERR
				|| ft_refill(b, pos - b->buf + 1) == ERR ? ERR : 1);
	else
	{
		if (ft_append(line, b, BUFF_SIZE, 0) == ERR
				|| ft_refill(b, BUFF_SIZE) == ERR)
			return (ERR);
		(b->iter)++;
		return (find_end(b, line));
	}
}

int			get_next_line(const int fd, char **line)
{
	static	t_list	*fdlist[1] = { NULL };
	t_buf			*buf;
	t_list			**tmp;
	t_list			*nxt;
	int				res;

	if (!line || fd == ERR || (buf = ft_find_buffer(fdlist, fd)) == NULL)
		return (ERR);
	*line = ft_strdup("");
	if ((res = find_end(buf, line)) == 0)
	{
		tmp = fdlist;
		while ((*tmp)->content_size != (size_t)fd)
			(*tmp) = (*tmp)->next;
		nxt = (*tmp)->next;
		free (*tmp);
		*tmp = nxt;
	}
	return (res);
}
