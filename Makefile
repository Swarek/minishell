# Compiler and flags
CC			= cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -I./Libft/includes
DEBUGFLAGS	= -g
LIBFT		= ./Libft/libft.a

# Directories
SRC_DIR		= ./src
OBJ_DIR		= ./.obj
INC_DIR		= ./includes

# Sources
SRC_FILES	=	src/exec/all_execution/redirections_gestion/here_doc_management.c \
				src/exec/all_execution/redirections_gestion/handle_io_redirections.c \
				src/exec/all_execution/redirections_gestion/name_files_here_doc.c \
				src/exec/all_execution/redirections_gestion/setup_pipe_redirections.c \
				src/exec/all_execution/pipes_process.c \
				src/exec/all_execution/solo_cmd.c \
				src/exec/all_execution/start_exec.c \
				src/exec/builtin/ft_env.c \
				src/exec/builtin/ft_pwd.c \
				src/exec/builtin/doing_built_in.c \
				src/exec/builtin/ft_cd.c \
				src/exec/builtin/ft_echo.c \
				src/exec/builtin/ft_exit.c \
				src/exec/builtin/ft_export.c \
				src/exec/builtin/ft_export_extracts.c \
				src/exec/builtin/ft_export_utils.c \
				src/exec/builtin/ft_unset.c \
				src/exec/executing_a_cmd/relative_absolute_path.c \
				src/exec/executing_a_cmd/execution.c \
				src/exec/executing_a_cmd/path.c \
				src/exec/reading_line.c \
				src/parsing/pre_check.c \
				src/parsing/parsing_main.c \
				src/parsing/parsing_save_it.c \
				src/parsing/parsing_utils.c \
				src/post_parsing/check_filename.c \
				src/post_parsing/subsequent.c \
				src/post_parsing/check_parentheses.c \
				src/post_parsing/env_expansion.c \
				src/post_parsing/env_expansion2.c \
				src/post_parsing/env_expansion3.c \
				src/post_parsing/replace_exit_status.c \
				src/post_parsing/words_to_file.c \
				src/utils/count_cmds.c \
				src/utils/cut_the_cmd_plus_arg.c \
				src/utils/is_redir.c \
				src/utils/pipe_counter.c \
				src/utils/print_args.c \
				src/utils/find_add_add_type_cmd.c \
				src/utils/ft_getenv.c \
				src/utils/is_real_cmd_in_cmds.c \
				src/utils/main_init.c \
				src/utils/other.c \
				src/utils/t_env_utils.c \
				src/utils/edit_args_for_export.c \
				src/main/main3.c \
				src/main/main2.c \
				src/clean/wait_and_cleanup_pipes.c \
				src/clean/clean_all.c \
				src/clean/clean_all2.c \
				src/inits/all_init_for_pipes_cmds.c \
				src/exec/all_execution/redirections_gestion/expand_for_here_doc.c \
				src/signals.c \
				src/signals2.c \
				src/utils/is_there_path.c \
				src/utils/shlvl.c \
				src/utils/create_basic_env.c \
				src/exec/executing_a_cmd/path_without_error_msg.c

MAIN_SRC	= main.c

SRCS		= $(SRC_FILES) $(MAIN_SRC)

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
