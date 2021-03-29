
# NAME - COMPLIATOR - FLAGGS -LIBFT ****************************************** #
NAME	= philo_one
OS 	= $(shell uname)
CC	= gcc
CC_L	= clang
CFLAGS	= -Wall -Wextra -Werror -g3 -I./includes
RM	= rm -f
#-fsanitize=address

# SRCS *********************************************************************** #
SRCS	= main.c life_actions.c utils.c utils2.c init.c log.c clean.c \
		monitor.c 

# OBJS *********************************************************************** #

OBJS	=	${SRCS:.c=.o}


# RULES ********************************************************************** #
.c.o:

ifeq (${OS}, Darwin)
	$(CC) $(CFLAGS) -c $< -o $@

else
	$(CC_L) $(CFLAGS) -c $< -o $@
endif

$(NAME):	${OBJS}

ifeq (${OS}, Darwin)
		$(CC) -lpdthread $(FLAGS) $(OBJS) -o $(NAME)
else
		$(CC_L) -lpthread $(FLAGS) -o $(NAME) $(OBJS) 

endif

all:		${NAME}

bonus:		${OBJS} ${OBJSBONUS}
		ar rc ${NAME} ${OBJS} ${OBJSBONUS} 

clean:
		${RM} ${OBJS} ${OBJSBONUS}

fclean:		clean
		${RM} ${NAME}

re:		fclean all

.PHONY:	all clean fclean re
