NAME = minishell

SRC_DIR = src
BONUS_DIR = bonus

# Recursively find all .c files in SRC_DIR and its subdirectories
SOURCES = $(shell find $(SRC_DIR) -name '*.c')

CFLAGS = -Wall -Wextra -Werror
FSANITIZE = -g3 -fsanitize=address
LIBFLAGS = -L./libft -lft -lm -lreadline $(FSANITIZE)
MY_HEADER = ./includes/

OBJ_DIR = obj


all:  libft42 $(NAME)

libft42:
	make -C libft
	
OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:$(SRC_DIR)/%.c=%.o))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@gcc $(CFLAGS) -I $(MY_HEADER) -c $< -o $@
	@echo -n "Compiling src... $<\r"

$(NAME): $(OBJECTS)
	@gcc $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBFLAGS)

$(OBJ_DIR):
	@mkdir -p $(dir $(OBJECTS))   # Create subdirectories in OBJ_DIR


clean:
	@rm -rf $(OBJ_DIR)
	@make fclean -C libft

fclean: clean
	@rm -f $(NAME)

re: fclean all


.PHONY: all clean fclean re



