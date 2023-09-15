NAME = minishell

SRC_DIR = src
BONUS_DIR = bonus

# Recursively find all .c files in SRC_DIR and its subdirectories
SOURCES = $(shell find $(SRC_DIR) -name '*.c')

# CFLAGS = -Wall -Wextra -Werror
LIBFLAGS = -L./libft -lft -lm -lreadline -g -fsanitize=address
MY_HEADER = ./includes/

OBJ_DIR = obj

OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:$(SRC_DIR)/%.c=%.o))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@gcc $(CFLAGS) -I $(MY_HEADER) -c $< -o $@
	@echo -n "Compiling src... $<\r"

$(NAME): $(OBJECTS)
	@gcc $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBFLAGS)

$(OBJ_DIR):
	@mkdir -p $(dir $(OBJECTS))   # Create subdirectories in OBJ_DIR

all: libft $(NAME)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

libft:
	make -C libft

.PHONY: all clean fclean re


