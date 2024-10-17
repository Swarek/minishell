NAME_EXEC = minishell_exec
NAME_PARSING = minishell_parsing

EXEC_DIR = exec
PARSING_DIR = parsing
OBJ_EXEC_DIR = obj_exec
OBJ_PARSING_DIR = obj_parsing
INC_DIR = includes

# Libft pour exec et parsing
LIBFT_EXEC_DIR = Libft
LIBFT_PARSING_DIR = libft
LIBFT_EXEC = $(LIBFT_EXEC_DIR)/libft.a
LIBFT_PARSING = $(LIBFT_PARSING_DIR)/libft.a

# Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
DEBUG_FLAGS = -g
RM = rm -f

# Includes
INCLUDES = -I$(INC_DIR) -I$(LIBFT_EXEC_DIR)/includes -I$(LIBFT_PARSING_DIR)/includes

# Sources et objets
SRCS_EXEC := $(wildcard $(EXEC_DIR)/*.c)
OBJS_EXEC = $(SRCS_EXEC:$(EXEC_DIR)/%.c=$(OBJ_EXEC_DIR)/%.o)

SRCS_PARSING := $(wildcard $(PARSING_DIR)/*.c)
OBJS_PARSING = $(SRCS_PARSING:$(PARSING_DIR)/%.c=$(OBJ_PARSING_DIR)/%.o)

# Targets
all: $(NAME_EXEC) $(NAME_PARSING)

$(NAME_EXEC): $(LIBFT_EXEC) $(OBJS_EXEC)
	$(CC) $(CFLAGS) $(OBJS_EXEC) -o $(NAME_EXEC) -L$(LIBFT_EXEC_DIR) -lft

$(NAME_PARSING): $(LIBFT_PARSING) $(OBJS_PARSING)
	$(CC) $(CFLAGS) $(OBJS_PARSING) -o $(NAME_PARSING) -L$(LIBFT_PARSING_DIR) -lft

# Compilation des objets pour exec
$(OBJ_EXEC_DIR)/%.o: $(EXEC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compilation des objets pour parsing
$(OBJ_PARSING_DIR)/%.o: $(PARSING_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compilation de libft pour exec
$(LIBFT_EXEC):
	make -C $(LIBFT_EXEC_DIR)

# Compilation de libft pour parsing
$(LIBFT_PARSING):
	make -C $(LIBFT_PARSING_DIR)

exec: $(NAME_EXEC)

parsing: $(NAME_PARSING)

# Clean et fclean
clean:
	$(RM) -r $(OBJ_EXEC_DIR) $(OBJ_PARSING_DIR)
	make -C $(LIBFT_EXEC_DIR) clean
	make -C $(LIBFT_PARSING_DIR) clean

fclean: clean
	$(RM) $(NAME_EXEC) $(NAME_PARSING)
	make -C $(LIBFT_EXEC_DIR) fclean
	make -C $(LIBFT_PARSING_DIR) fclean

# Rebuild tout
re: fclean all

# Mode debug
debug: CFLAGS += $(DEBUG_FLAGS)
debug: re

.PHONY: all clean fclean re debug exec parsing
