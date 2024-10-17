# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
DEBUGFLAGS	= -g
LIBFT		= ./Libft/libft.a

# Directories
SRC_DIR		= ./src
OBJ_DIR		= ./obj
INC_DIR		= ./includes

# Sources
SRC_FILES	= exec/ft_echo.c exec/main_exec.c exec/main_test.c exec/reading_line.c \
			  parsing/main.c parsing/parsing_main.c parsing/parsing_save_it.c parsing/parsing_utils.c \
			  utils/free_structs.c

MAIN_SRC	= main.c

SRCS		= $(addprefix $(SRC_DIR)/, $(SRC_FILES)) $(MAIN_SRC)

# Object files with directory structure included (to avoid name conflicts)
OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Name of the program
NAME		= minishell

# Includes
INCLUDES	= -I$(INC_DIR)

# Linker flags for readline
LDFLAGS		= -lreadline

# Phony targets
.PHONY: all clean fclean re debug

# Default rule
all: $(NAME)

# Link the program, adding the readline library
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)

# Compile object files, ensuring directory structure in obj/
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Debug rule
debug: CFLAGS += $(DEBUGFLAGS)
debug: re

# Clean object files
clean:
	rm -rf $(OBJ_DIR)

# Clean object files and the binary
fclean: clean
	rm -f $(NAME)

# Recompile everything
re: fclean all

# Compile libft
$(LIBFT):
	make -C ./Libft
