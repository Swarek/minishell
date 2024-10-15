NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

# Chemins
PARSING_DIR = parsing/
LIBFT_DIR = libft/
INCLUDES = -I. -I$(LIBFT_DIR)

# Fichiers sources
SRCS = $(wildcard $(PARSING_DIR)*.c)
OBJS = $(SRCS:.c=.o)

# Libft
LIBFT = $(LIBFT_DIR)libft.a

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBFT)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re