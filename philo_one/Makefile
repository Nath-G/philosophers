
# NAME - COMPLIATOR - FLAGGS -LIBFT ****************************************** #
NAME	= philo_one
OS = $(shell uname)
CC	= gcc
CC_L	= clang
CFLAGS	= -Wall -Wextra -Werror -I./includes
RM	= rm -f
#-fsanitize=address

# SRCS *********************************************************************** #
SRCS	= philo_one.c \

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
			make all -C ./lib/minilibx
			make all -C ./lib/libft

ifeq (${OS}, Darwin)
			$(CC) $(FLAGS) $(MLX) $(OBJS) -I./lib/libft/libft.a -o $(NAME)
else
			$(CC_L) -o $(NAME) $(OBJS) -L./lib/minilibx -lmlx ./lib/libft/libft.a $(MLX_L)

endif

all:		${NAME}

bonus:		${OBJS} ${OBJSBONUS}
			ar rc ${NAME} ${OBJS} ${OBJSBONUS} 

clean:
			make clean -C ./lib/minilibx 
			make clean -C ./lib/libft
			${RM} ${OBJS} ${OBJSBONUS}

fclean:		clean
			make fclean -C ./lib/libft
			make fclean -C ./lib/minilibx
			${RM} ${NAME}

re:			fclean all

.PHONY:	all libft.a clean fclean re libmlx.a