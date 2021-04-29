
# NAME - COMPLIATOR - FLAGGS -LIBFT ****************************************** #

NAME	= philo_three
CC		= clang
CFLAGS	= -Wall -Wextra -Werror -g3 -I./includes
RM		= rm -f

# SRCS *********************************************************************** #

SRCS	= main.c life_actions.c utils.c utils2.c init.c log.c clean.c \
		  monitor.c time.c init_semaphores.c

# OBJS *********************************************************************** #

OBJS	=	${SRCS:.c=.o}

# RULES ********************************************************************** #
 .c.o:
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	${OBJS}
			$(CC) -lpthread $(FLAGS) -o $(NAME) $(OBJS)

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re philo_three
