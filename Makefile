NAME		= server client
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Iinclude
OBJ_DIR		= obj

SRC_SERVER	= server.c utils.c
SRC_CLIENT	= client.c utils.c

OBJ_SERVER	= $(SRC_SERVER:%.c=$(OBJ_DIR)/%.o)
OBJ_CLIENT	= $(SRC_CLIENT:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

server: $(OBJ_SERVER)
	$(CC) $(CFLAGS) -o $@ $^

client: $(OBJ_CLIENT)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
