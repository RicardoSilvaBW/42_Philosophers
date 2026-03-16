NAME	= philo

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -I includes
LDFLAGS	= -lpthread

SRCS	=	src/main.c \
			src/parsing.c \
			src/init.c \
			src/time.c \
			src/utils.c \
			src/actions.c \
			src/routine.c \
			src/monitor.c

OBJS	= $(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

src/%.o:	src/%.c
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
