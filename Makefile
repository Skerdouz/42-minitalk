CLIENT_EXECUTABLE	=	client
SERVER_EXECUTABLE	=	server
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g3
INCLUDES	=	-Iinclude -Ilib/libft/include
LIBS		=	-Llib/libft -lft

# files
SRC_DIR		=	src/
CLIENT_FILES	=	client
SERVER_FILES	=	server

CLIENT_SRCS 	=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(CLIENT_FILES)))
SERVER_SRCS 	=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SERVER_FILES)))

CLIENT_OBJS	=	$(CLIENT_SRCS:.c=.o)
SERVER_OBJS	=	$(SERVER_SRCS:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: comp

comp: $(CLIENT_OBJS) $(SERVER_OBJS)
	@make -C lib/libft
	@$(CC) $(CFLAGS) $(CLIENT_OBJS) $(LIBS) -o $(CLIENT_EXECUTABLE)
	@echo "Minitalk|	client compiled ✅"
	@$(CC) $(CFLAGS) $(SERVER_OBJS) $(LIBS) -o $(SERVER_EXECUTABLE)
	@echo "Minitalk|	server compiled ✅"

clean:
	@make clean -C lib/libft
	@rm -f $(CLIENT_OBJS)
	@rm -f $(SERVER_OBJS)
	@echo "Minitalk|	Cleaned ✅"

fclean:	clean
	@make fclean -C lib/libft
	@rm -f $(CLIENT_EXECUTABLE)
	@rm -f $(SERVER_EXECUTABLE)
	@echo "Minitalk|	Executable cleaned ✅"

re:		fclean all

.PHONY: all clean fclean re
