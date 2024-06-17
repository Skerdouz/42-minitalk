NAME		=	test
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
INCLUDES	=	-Iinclude -Ilib/libft/include
LIBS		=	-Llib/libft -lft

# files
SRC_DIR		=	src/
SRC_FILES	=	main client server

SRCS 	=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))


OBJS	=	$(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME):$(OBJS)
	@make -C lib/libft
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "Minitalk|	compiled ✅"

all:	$(NAME)

clean:
	@make clean -C lib/libft
	@rm -f $(OBJS)
	@echo "Minitalk|	Cleaned ✅"

fclean:	clean
	@make fclean -C lib/libft
	@rm -f $(NAME)
	@echo "Minitalk|	Executable cleaned ✅"

re:		fclean all

.PHONY: all clean fclean re