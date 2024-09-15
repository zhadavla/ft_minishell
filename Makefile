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

# Calculate total number of source files for the progress bar
TOTAL_FILES := $(shell find $(SRC_DIR) -name '*.c' | wc -l)
COMPILED_FILES = 0

# Define the progress bar length
PROGRESS_BAR_LENGTH = 50

# ANSI color codes for colorizing the progress bar
COLOR_RESET = \033[0m
COLOR_GREEN = \033[1;32m
COLOR_RED = \033[1;31m

all: libft42 $(NAME)

libft42:
	@$(MAKE) -C libft --silent  # Suppress entering/leaving messages

OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:$(SRC_DIR)/%.c=%.o))

# Function to update the progress bar with colors
define progress_bar
	@$(eval PROGRESS=$(shell echo $$(($(COMPILED_FILES) * $(PROGRESS_BAR_LENGTH) / $(TOTAL_FILES)))))
	@$(eval SPACES=$(shell echo $$(($(PROGRESS_BAR_LENGTH) - $(PROGRESS)))))
	@echo -ne "\r["
	@printf "$(COLOR_GREEN)%0.s#$(COLOR_RESET)" `seq 1 $(PROGRESS)`
	@printf "$(COLOR_RED)%0.s $(COLOR_RESET)" `seq 1 $(SPACES)`
	@echo -ne "]"
endef

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(eval COMPILED_FILES=$(shell echo $$(($$(echo $(COMPILED_FILES)) + 1))))
	@gcc $(CFLAGS) -I $(MY_HEADER) -c $< -o $@
	$(call progress_bar)

$(NAME): $(OBJECTS)
	@gcc $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBFLAGS)
	@echo -ne "\r$(COLOR_GREEN)[##################################################]$(COLOR_RESET) Compilation complete!\n"

$(OBJ_DIR):
	@mkdir -p $(dir $(OBJECTS))   # Create subdirectories in OBJ_DIR

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) fclean -C libft --silent

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
