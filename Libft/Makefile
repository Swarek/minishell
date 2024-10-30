# Variables
NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIE -Iincludes
SRC_DIR = src
SRCS =	src/array/ft_split.c \
		src/array/ft_strchr.c \
		src/array/ft_strcmp.c \
		src/array/ft_strcpy.c \
		src/array/ft_strdup.c \
		src/array/ft_striteri.c \
		src/array/ft_strjoin.c \
		src/array/ft_strlcat.c \
		src/array/ft_strlcpy.c \
		src/array/ft_strlen.c \
		src/array/ft_strmapi.c \
		src/array/ft_strncmp.c \
		src/array/ft_strnstr.c \
		src/array/ft_strrchr.c \
		src/array/ft_strtrim.c \
		src/array/ft_substr.c \
		src/array_of_strings/duplicate_string_array.c \
		src/array_of_strings/free_array_iter_error.c \
		src/array_of_strings/get_2d_array_length.c \
		src/array_of_strings/searching_char.c \
		src/conversions/ft_atoi.c \
		src/conversions/ft_atoi_base.c \
		src/conversions/ft_itoa.c \
		src/error_handling/error_msg.c \
		src/error_handling/ft_assert.c \
		src/error_handling/ft_error_msg.c \
		src/files/get_next_line.c \
		src/files/get_next_line_utils.c \
		src/files/get_next_line_utils2.c \
		src/linked_lists/ft_lstadd_back_bonus.c \
		src/linked_lists/ft_lstadd_front_bonus.c \
		src/linked_lists/ft_lstclear_bonus.c \
		src/linked_lists/ft_lstdelone_bonus.c \
		src/linked_lists/ft_lstdup.c \
		src/linked_lists/ft_lstfind.c \
		src/linked_lists/ft_lstinsert.c \
		src/linked_lists/ft_lstiter_bonus.c \
		src/linked_lists/ft_lstlast_bonus.c \
		src/linked_lists/ft_lstmap_bonus.c \
		src/linked_lists/ft_lstmap_inplace.c \
		src/linked_lists/ft_lstmerge.c \
		src/linked_lists/ft_lstnew_bonus.c \
		src/linked_lists/ft_lstremove_at.c \
		src/linked_lists/ft_lstreverse.c \
		src/linked_lists/ft_lstsize_bonus.c \
		src/malloc_free/ft_2dclear.c \
		src/malloc_free/ft_calloc.c \
		src/malloc_free/ft_check_malloc.c \
		src/malloc_free/ft_malloc_array.c \
		src/malloc_free/ft_realloc.c \
		src/malloc_free/ft_safe_calloc.c \
		src/malloc_free/ft_safe_free.c \
		src/malloc_free/ft_safe_malloc.c \
		src/malloc_free/safe_free_all_strings.c \
		src/memory_management/ft_bzero.c \
		src/memory_management/ft_memchr.c \
		src/memory_management/ft_memcmp.c \
		src/memory_management/ft_memcpy.c \
		src/memory_management/ft_memdup.c \
		src/memory_management/ft_memmove.c \
		src/memory_management/ft_memset.c \
		src/printing/ft_print_array.c \
		src/printing/ft_printf.c \
		src/printing/ft_putchar.c \
		src/printing/ft_putchar_fd.c \
		src/printing/ft_putendl_fd.c \
		src/printing/ft_putint.c \
		src/printing/ft_putnbr.c \
		src/printing/ft_putnbr_base.c \
		src/printing/ft_putnbr_fd.c \
		src/printing/ft_putnbr_unsigned.c \
		src/printing/ft_putstr.c \
		src/printing/ft_putstr_fd.c \
		src/printing/print_tlist.c \
		src/utils/ft_isalnum.c \
		src/utils/ft_isalpha.c \
		src/utils/ft_isascii.c \
		src/utils/ft_isdigit.c \
		src/utils/ft_isprint.c \
		src/utils/ft_str_is_whitespace.c \
		src/utils/ft_tolower.c \
		src/utils/ft_toupper.c \
		src/utils/remove_newline.c

OBJS = $(SRCS:.c=.o)
AR = ar rcs

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

bonus: $(OBJS)
	$(AR) $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

# Compilation
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re bonus
