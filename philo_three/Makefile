
# NAME - COMPLIATOR - FLAGGS -LIBFT ****************************************** #
NAME	= philo_three
OS = $(shell uname)
CC	= gcc
CC_L	= clang
CFLAGS	= -Wall -Wextra -Werror -I./includes
RM	= rm -f
#-fsanitize=address

# SRCS *********************************************************************** #
SRCS	= main.c \

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
		#	make all -C ./lib/minilibx
		#	make all -C ./lib/libft

ifeq (${OS}, Darwin)
			$(CC) $(FLAGS) $(MLX) $(OBJS) -o $(NAME)
else
			$(CC_L) -lpthread $(FLAGS) -o $(NAME) $(OBJS) 

endif

all:		${NAME}

bonus:		${OBJS} ${OBJSBONUS}
			ar rc ${NAME} ${OBJS} ${OBJSBONUS} 

clean:
	#		make clean -C ./lib/minilibx 
	#		make clean -C ./lib/libft
			${RM} ${OBJS} ${OBJSBONUS}

fclean:		clean
		#	make fclean -C ./lib/libft
		#	make fclean -C ./lib/minilibx
			${RM} ${NAME}

re:			fclean all

.PHONY:	all clean fclean re
