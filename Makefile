CC			=		clang

ARRC		=		ar rc

RANLIB		=		ranlib

NAME_LIB	=		libft.a

NAME		=		fillit

DIR_SRC_LIB	=		./lib/

DIR_SRC		=		./srcs/

OBJS_LIB	=		$(SRCS_LIB:.c=.o)

OBJS		=		$(SRCS:.c=.o)

CFLAGS		+=		-I./includes/
CFLAGS		+=		-Wall -Wextra -Werror

RM			=		rm -f

ECHO		=		printf

SRCS_LIB	=		$(DIR_SRC_LIB)ft_bzero.c					\
					$(DIR_SRC_LIB)ft_memcmp.c					\
					$(DIR_SRC_LIB)ft_memcpy.c					\
					$(DIR_SRC_LIB)ft_memmove.c					\
					$(DIR_SRC_LIB)ft_atoi.c						\
					$(DIR_SRC_LIB)ft_memchr.c					\
					$(DIR_SRC_LIB)ft_memset.c					\
					$(DIR_SRC_LIB)ft_strchr.c					\
					$(DIR_SRC_LIB)ft_strcmp.c					\
					$(DIR_SRC_LIB)ft_strlen.c					\
					$(DIR_SRC_LIB)ft_strncmp.c					\
					$(DIR_SRC_LIB)ft_tolower.c					\
					$(DIR_SRC_LIB)ft_toupper.c					\
					$(DIR_SRC_LIB)ft_strcat.c					\
					$(DIR_SRC_LIB)ft_strcpy.c					\
					$(DIR_SRC_LIB)ft_strdup.c					\
					$(DIR_SRC_LIB)ft_strlcat.c					\
					$(DIR_SRC_LIB)ft_strncat.c					\
					$(DIR_SRC_LIB)ft_strncpy.c					\
					$(DIR_SRC_LIB)ft_strnstr.c					\
					$(DIR_SRC_LIB)ft_strstr.c					\
					$(DIR_SRC_LIB)ft_isalnum.c					\
					$(DIR_SRC_LIB)ft_isalpha.c					\
					$(DIR_SRC_LIB)ft_isascii.c					\
					$(DIR_SRC_LIB)ft_isdigit.c					\
					$(DIR_SRC_LIB)ft_isprint.c					\
					$(DIR_SRC_LIB)ft_strrchr.c					\
					$(DIR_SRC_LIB)ft_memccpy.c					\
					$(DIR_SRC_LIB)ft_memalloc.c					\
					$(DIR_SRC_LIB)ft_memdel.c					\
					$(DIR_SRC_LIB)ft_strnew.c					\
					$(DIR_SRC_LIB)ft_strclr.c					\
					$(DIR_SRC_LIB)ft_strdel.c					\
					$(DIR_SRC_LIB)ft_striter.c					\
					$(DIR_SRC_LIB)ft_striteri.c					\
					$(DIR_SRC_LIB)ft_strmap.c					\
					$(DIR_SRC_LIB)ft_strmapi.c					\
					$(DIR_SRC_LIB)ft_strequ.c					\
					$(DIR_SRC_LIB)ft_strnequ.c					\
					$(DIR_SRC_LIB)ft_strsub.c					\
					$(DIR_SRC_LIB)ft_strjoin.c					\
					$(DIR_SRC_LIB)ft_strtrim.c					\
					$(DIR_SRC_LIB)ft_strsplit.c					\
					$(DIR_SRC_LIB)ft_putchar.c					\
					$(DIR_SRC_LIB)ft_putstr.c					\
					$(DIR_SRC_LIB)ft_putendl.c					\
					$(DIR_SRC_LIB)ft_itoa.c						\
					$(DIR_SRC_LIB)ft_putnbr.c					\
					$(DIR_SRC_LIB)ft_putchar_fd.c				\
					$(DIR_SRC_LIB)ft_putstr_fd.c				\
					$(DIR_SRC_LIB)ft_putendl_fd.c				\
					$(DIR_SRC_LIB)ft_putnbr_fd.c				\
					$(DIR_SRC_LIB)ft_lstdelone.c				\
					$(DIR_SRC_LIB)ft_lstnew.c					\
					$(DIR_SRC_LIB)ft_lstdel.c					\
					$(DIR_SRC_LIB)ft_lstadd.c					\
					$(DIR_SRC_LIB)ft_lstiter.c					\
					$(DIR_SRC_LIB)ft_lstmap.c					\
					$(DIR_SRC_LIB)ft_realloc.c					\
					$(DIR_SRC_LIB)ft_lstaddend.c				\
					$(DIR_SRC_LIB)ft_countiter.c				\
					$(DIR_SRC_LIB)ft_lstsize.c					\
					$(DIR_SRC_LIB)ft_lstat.c

SRCS		=		$(DIR_SRC)main.c							\
					$(DIR_SRC)lst_manage.c						\
					$(DIR_SRC)parsing.c							\
					$(DIR_SRC)parsing_2.c						\
					$(DIR_SRC)print.c							\
					$(DIR_SRC)square_manage.c					\
					$(DIR_SRC)tetra_manage.c


all			:		$(NAME)

$(NAME)		:		$(NAME_LIB) $(OBJS)
					@$(ECHO) "\033[33m[~~~~~ COMPILATION OK ~~~~~~]  \033[0m"
					@$(CC) -o $(NAME) $(NAME_LIB) $(OBJS) && $(ECHO) "\033[32m[OK]\n\033[0m" ||@$(ECHO) "\033[31m[KO]\n\033[0m"

$(NAME_LIB)	:		$(OBJS_LIB)
					@$(ECHO) "\033[35m[~~~~~ CREATION LIB ~~~~~~~~]  \033[0m"
					@$(ARRC) $(NAME_LIB) $(OBJS_LIB) && $(ECHO) "\033[32m[OK]\n\033[0m" || @$(ECHO) "\033[31m[KO]\n\033[0m"
					@$(ECHO) "\033[35m[~~~~~ RANLIB ~~~~~~~~~~~~~~]  \033[0m"
					@$(RANLIB) $(NAME_LIB) && $(ECHO) "\033[32m[OK]\n\033[0m" ||@$(ECHO) "\033[31m[KO]\n\033[0m"
					@$(ECHO) "\033[33m[~~~~~ LIB OK ~~~~~~~~~~~~~~]  [OK]\n\033[0m"

%.o			:		%.c
					@$(ECHO) "\033[36m[~~~~~ COMPILATION OBJ ~~~~~]  \033[0m"
					@$(CC) $(CFLAGS) -o $@ -c $< && $(ECHO) "\033[33;32m["$@"] \n\033[0m" || $(ECHO) "\033[31m["$@"] \n\033[0m"

clean		:
					@$(RM) $(OBJS_LIB) && $(ECHO) "\033[31m[~~~~~ SUPRESSION .O LIB ~~~]  [OK]\n\033[0m"
					@$(RM) $(OBJS) && $(ECHO) "\033[31m[~~~~~ SUPRESSION .O SRC ~~~]  [OK]\n\033[0m"

fclean		:		clean
					@$(RM) $(NAME_LIB) && $(ECHO) "\033[31m[~~~~~ SUPRESSION LIB ~~~~~~]  [OK]\n\033[0m"
					@$(RM) $(NAME) && $(ECHO) "\033[31m[~~~~~ SUPRESSION BINAIRE ~~]  [OK]\n\033[0m"

re			:		fclean all

.PHONY		:		all clean fclean re
