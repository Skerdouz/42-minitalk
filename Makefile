CLIENT_EXECUTABLE	=	client
SERVER_EXECUTABLE	=	server
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
INCLUDES	=	-Iinclude -Ilib/libft/include
LIBS		=	-Llib/libft -lft

#
#	COLORS
#
RESET = \033[0m
GREEN = \033[32;49m
RED = \033[31;49m
BLUE = \033[34;49m

#
# 	SRCS
#
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
	@make --no-print-directory -C lib/libft
	@echo "-------------------"
	@$(CC) $(CFLAGS) $(CLIENT_OBJS) $(LIBS) -o $(CLIENT_EXECUTABLE)
	@printf "$(GREEN)[Minitalk]\t$(CLIENT_EXECUTABLE) compiled✨$(RESET)\n"
	@$(CC) $(CFLAGS) $(SERVER_OBJS) $(LIBS) -o $(SERVER_EXECUTABLE)
	@printf "$(GREEN)[Minitalk]\t$(SERVER_EXECUTABLE) compiled✨$(RESET)\n"

clean:
	@make --no-print-directory clean -C lib/libft
	@files_deleted=0; \
	for obj in $(CLIENT_OBJS) $(SERVER_OBJS); do \
		if [ -f "$$obj" ]; then \
			rm -f "$$obj"; \
			files_deleted=1; \
		fi; \
	done; \
	if [ $$files_deleted -eq 1 ]; then \
		printf "$(RED)[Minitalk]\tBinary files deleted🗑️$(RESET)\n"; \
	fi

fclean:	clean
	@make --no-print-directory fclean -C lib/libft
	@files_deleted=0; \
	if [ -f "$(CLIENT_EXECUTABLE)" ]; then \
		rm -f $(CLIENT_EXECUTABLE); \
		files_deleted=1; \
	fi; \
	if [ -f "$(SERVER_EXECUTABLE)" ]; then \
		rm -f $(SERVER_EXECUTABLE); \
		files_deleted=1; \
	fi; \
	if [ $$files_deleted -eq 1 ]; then \
		printf "$(RED)[Minitalk]\tExecutables cleaned🗑️$(RESET)\n"; \
	fi
	@printf "\n"

re:		fclean all

.PHONY: all clean fclean re
