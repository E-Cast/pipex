NAME = pipex

# >------------------------------< directories
SRC_DIR := src/
OBJ_DIR := .cache/
BIN_DIR := bin/

# >------------------------------< files
SRCS := $(wildcard $(SRC_DIR)*.c)
OBJS := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

# >------------------------------< compilation
CC := gcc
CFLAGS := -Wall -Wextra -g

# >------------------------------< rules
all: $(NAME)

$(NAME): $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)$(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(BIN_DIR)

re: fclean all

.PHONY: all clean fclean re