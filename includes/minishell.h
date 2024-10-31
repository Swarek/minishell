/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:22:47 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/31 06:48:02 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define OUTPUT_REDIRECTION 0
# define APPEND_REDIRECTION 1

# include "libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <termios.h>

# define STDIN 0
# define STDOUT 1
# define PATH_MAX 4096

// Structures

typedef struct s_arg
{
	char						*content;
	char						*type;
	struct s_arg				*next;
}								t_arg;

typedef struct s_cmd
{
	t_arg						*args;
	char						**cmd_arg_stdin;
	struct s_cmd				*next;
}								t_cmd;

typedef struct s_exclude
{
	int							indices[1000];
	int							count;
	int							start;
	int							end;
}								t_exclude;

typedef struct s_env
{
	char						*line;
	char						*name;
	char						*value;
	int							declared;
	struct s_env				*next;
}								t_env;

typedef struct s_shell
{
	int							exit_status;
	char						**envp;
	t_cmd						*cmds;
	int							total_cmd_count;
	int							nbr_pipes;
	int							infile;
	int							outfile;
	int							input_pipe;
	int							there_is_redir_out;
	int							there_is_redir_in;
	int							n_th_cmd;
	int							**pipes;
	pid_t						*child_pids;
	int							in_child_process;
	int							nth_here_doc;
}								t_shell;

extern volatile sig_atomic_t	g_received_signal;

// 		Parsing

// parsing_main.c

int								handle_special_char(char *str, int i,
									t_arg **current_args);
int								parse_one_command(char *str, int i,
									t_arg **current_args, t_cmd **cmds);
int								parse_it(char *str, t_cmd **cmds);

// parsing_save_it.c

int								save_it_redir_right(char *str, int i,
									t_arg **args);
int								save_it_redir_left(char *str, int i,
									t_arg **args);
int								save_it_word(char *str, int i, t_arg **args);
int								save_it_double_quoted(char *str, int i,
									t_arg **args);
int								save_it_single_quoted(char *str, int i,
									t_arg **args);
int								save_it_unfinished(char *str, int i,
									t_arg **args);

// parsing_utils.c

t_arg							*create_arg(char *content, const char *type);
void							add_arg(t_arg **head, t_arg *new_arg);
void							add_command(t_cmd **cmds, t_arg **current_args);

void							print_args(t_arg *args);

void							expand_env_vars_in_cmds_tab(t_cmd **cmds,
									t_shell shell);
void							expand_env_vars(t_arg *current_arg,
									t_shell shell);
void							replace_env_var(t_arg *current_arg, int start,
									int end, const char *value);

char							*copy_string_exclude(const char *source,
									int start, int end, t_exclude *excl);
int								should_skip(int idx, t_exclude *excl);
int								calc_len(int start, int end, t_exclude *excl);

// Pre-check

int								precheck(char *input);
int								check_pipe_position(char *input);
int								is_valid_char(char str);

// Post-check
int								type_to_file_in_args1(t_cmd **cmds);
void							type_to_file_in_args2(t_arg *current_arg);

int								error_if_subsequent_commands(t_cmd **cmds);
int								error_in_filename(t_cmd **cmds);
int								error_if_unclosed_parentheses(t_cmd **cmds);
void							replace_exit_status(t_arg *current_arg,
									t_shell *shell);
void							replace_exit_status_in_cmds_tab(t_cmd **cmds,
									t_shell *shell);
int								check_file_name(char *input);
int								get_var_name_end_env(const char *content,
									int start);
void							handle_exit_status_for_env(t_arg *current_arg,
									int *i, t_shell shell);

// Utils
void							print_command(t_cmd *cmd);
void							print_all_commands(t_cmd *cmds);
void							my_print_command(t_arg *args);
void							free_cmd(t_cmd *cmd);
int								len_cmd(t_cmd *cmd);
int								count_arguments(char **args);
int								count_arguments_for_t_arg(t_arg *args);
char							**convert_args_to_argv(t_arg *args);
void							print_args(t_arg *args);
void							find_and_add_type_cmd(t_arg *args, char **envp);
void							setup_child_signals(void);
void							edit_args_for_export(t_arg *args);
int								count_cmd(t_cmd *cmd);
char							*name_files_here_doc(int nbr);
int								is_a_here_doc_in_the_cmd(t_cmd *cmd);
int								delete_all_temp_files(int total_here_doc);
int								expand_in_here_doc25(char *file_name,
									int exit_status);
char							*ft_getenv(char **env, char *name);
int								is_real_cmd_in_cmds(t_cmd *cmds);
int								setup_pipe_redirections(t_shell *shell);
void							print_command(t_cmd *cmd);
void							print_all_commands(t_cmd *cmds);
void							my_print_command(t_arg *args);
void							free_cmd(t_cmd *cmd);
int								len_cmd(t_cmd *cmd);
int								count_arguments(char **args);
int								count_arguments_for_t_arg(t_arg *args);
char							**convert_args_to_argv(t_arg *args);
void							print_args(t_arg *args);
void							find_and_add_type_cmd(t_arg *args, char **envp);
void							setup_child_signals(void);
void							edit_args_for_export(t_arg *args);
int								count_cmd(t_cmd *cmd);
char							*name_files_here_doc(int nbr);
int								is_a_here_doc_in_the_cmd(t_cmd *cmd);
int								delete_all_temp_files(int total_here_doc);
int								expand_in_here_doc25(char *file_name,
									int exit_status);
char							*ft_getenv(char **env, char *name);
int								is_real_cmd_in_cmds(t_cmd *cmds);
t_env							*find_no_na(t_env *env, const char *name);
char							*replace_in_charstar(char **str,
									t_shell *shell);
char							*ft_getcwd(char *buf, int size, char **env);
int								is_there_path(char **env);
int								is_there_pwd(char **env);
int								shlvl_incrementation(t_shell *shell);
int								create_basic_env(t_shell *shell);
int								ft_setenv(char *name, char *value,
									char ***envp);

// Build-in functions
int								ft_pwd(t_shell *shell);
int								ft_echo(t_shell *shell);
int								ft_cd(t_shell *shell);
int								ft_export(t_arg *args, char ***envp,
									t_shell *shell);
void							ft_env(char **envp, t_shell *shell);
void							ft_unset(t_arg *args, char ***env,
									t_shell *shell);
int								ft_exit(t_shell *shell, t_arg *args);

char							*reading_line(int color);
int								exec_it(t_shell *shell);
int								is_built_in(char **args);
int								is_built_in_t_args(t_arg *args);
int								execute_built_in(t_shell *shell,
									char **cmd_arg_stdin, char ***envp);
int								do_the_execution(t_shell *shell, t_cmd *cmd,
									char **envp);
int								handling_pipes(t_shell *shell);
int								execute_solo(t_shell *shell);
int								execution(t_shell *shell);
int								count_pipe(t_cmd *cmd);
char							*find_command_path(t_shell *shell,
									char *command, char **envp);
int								setup_file_redirections(t_shell *shell);
void							find_and_add_type_cmd(t_arg *args, char **envp);
int								is_redir(t_arg *arg);
int								cut_the_cmd_plus_args(t_cmd *cmd);
int								a_pipe_is_coming(t_shell *shell);
void							close_pipes(t_shell *shell);
void							clean_all(t_shell *shell);
int								starting_one_cmd(t_shell *shell);
void							find_arg_add_type_cmd(t_shell *shell,
									t_arg *args);
char							*reading_line(int color);
int								exec_it(t_shell *shell);
int								is_built_in(char **args);
int								is_built_in_t_args(t_arg *args);
int								execute_built_in(t_shell *shell,
									char **cmd_arg_stdin, char ***envp);
int								do_the_execution(t_shell *shell, t_cmd *cmd,
									char **envp);
int								handling_pipes(t_shell *shell);
int								execute_solo(t_shell *shell);
int								execution(t_shell *shell);
int								count_pipe(t_cmd *cmd);
char							*find_command_path(t_shell *shell,
									char *command, char **envp);
int								setup_file_redirections(t_shell *shell);
void							find_and_add_type_cmd(t_arg *args, char **envp);
int								is_redir(t_arg *arg);
int								cut_the_cmd_plus_args(t_cmd *cmd);
int								a_pipe_is_coming(t_shell *shell);
void							close_pipes(t_shell *shell);
void							clean_all(t_shell *shell);
int								starting_one_cmd(t_shell *shell);
void							find_arg_add_type_cmd(t_shell *shell,
									t_arg *args);
char							*n_find_command_path(t_shell *shell,
									char *command, char **envp);
char							*n_get_path_from_env(t_shell *shell,
									char *command, char **envp);

// for envp
t_env							*create_t_env(char **envp);
t_env							*add_node(t_env *head, t_env *new_node);
t_env							*create_node(char *env_line);
char							*get_env_value(char *env_line);
char							*get_env_name(char *env_line);
int								len_env(t_env *env);
int								is_valid_identifier(char *str);
t_env							*find_no_na(t_env *env, const char *name);
void							free_env(t_env *env);
t_env							*find_smallest_undeclared(t_env *env);
char							*extract_value(const char *content);
char							*extract_name(const char *content);

// Functions Pipex

// Leaks, closes and errors
void							wait_and_cleanup(t_shell *shell);
void							close_both(int to_close1, int to_close2);
void							cleanup(t_shell *shell, char **cmd);

// Here_doc
int								here_doc_management(char *limiter,
									char *name_file, t_shell *shell);
int								handle_here_doc(t_shell *shell);

// Processes
int								parent_process(t_shell *shell, pid_t pid);
int								handle_io_redirections(t_shell *shell);

// Inits
int								init_shell_structure(t_shell *shell);
int								all_init_for_pipes_cmds(t_shell *shell);
int								init_shell_structure(t_shell *shell);
int								all_init(t_shell *shell);

// Execution
int								do_the_execution(t_shell *shell, t_cmd *cmd,
									char **envp);
int								is_absolute_or_relative_path(char *command);
char							*handle_paths(char *command);
int								execute_with_shell(char *path, char **cmd,
									char **envp, int cmd_count);
char							**remove_quotes(char **cmd);
char							**special_split(const char *s, char delimiter);

// No bonus
int								pipes_process(t_shell *shell);
int								fork_process(t_shell *shell);

// Free
void							free_args(t_arg *args);
void							clean_up_for_error_init(t_shell *shell,
									int nbr_pipes);
void							free_cmd_arg_stdin(char **cmd_arg_stdin);
void							safe_free_cmds(t_cmd *cmds);
void							end_clean(t_shell *shell);
void							free_pipes(int **pipes, int nbr_pipes);

// Signals
void							setup_signals(void);
void							handle_ctrl_d(char *line, t_shell *shell);

// Other
void							str_arg_in_null(t_cmd *cmd);

// Mains

t_shell							*init_struct_shell(char **envp);
void							handle_received_signal_in_main(t_shell *shell);
int								main1(char **envp, t_shell **shell);
int								main2(char *line, t_cmd **cmds, t_shell *shell);
int								main3(t_cmd **cmds, t_shell *shell);
int								main7(char *line, t_cmd **cmds, t_shell *shell,
									int *color);
int								main6(char **line, t_shell *shell, int color);
void							main5(t_cmd **cmds, t_shell *shell);
int								main4(t_cmd **cmds, t_shell *shell);
void							initialize_shell_values(t_shell *shell);

#endif
