NAME = pipex

# >------------------------------< directories
SRC_DIR := src/
OBJ_DIR := .cache/

# >------------------------------< files
SRCS := $(wildcard $(SRC_DIR)*.c)
# SRCS := fd.c pipex.c split_string.c utility.c
OBJS := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

# >------------------------------< compilation
CC := gcc
CFLAGS := -Wall -Wextra -g

# >------------------------------< rules
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(BIN_DIR)

re: fclean all

.PHONY: all clean fclean re