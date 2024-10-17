NAME_EXEC = minishell_exec
NAME_PARSING = minishell_parsing

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

# Chemins
PARSING_DIR = parsing/
EXEC_DIR = exec/
LIBFT_DIR = libft/
INCLUDES = -I. -I$(LIBFT_DIR)

# Fichiers sources
SRCS_PARSING = $(wildcard $(PARSING_DIR)*.c)
SRCS_EXEC = $(wildcard $(EXEC_DIR)*.c)
OBJS_PARSING = $(SRCS_PARSING:.c=.o)
OBJS_EXEC = $(SRCS_EXEC:.c=.o)

# Libft
LIBFT = $(LIBFT_DIR)libft.a

all: $(LIBFT) $(NAME_EXEC) $(NAME_PARSING)

$(NAME_EXEC): $(OBJS_EXEC)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBFT)

$(NAME_PARSING): $(OBJS_PARSING)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBFT)

exec: $(LIBFT) $(NAME_EXEC)

parsing: $(LIBFT) $(NAME_PARSING)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS_EXEC) $(OBJS_PARSING)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME_EXEC) $(NAME_PARSING)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re exec parsing
