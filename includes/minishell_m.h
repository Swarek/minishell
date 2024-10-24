/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_m.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:22:47 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/24 08:32:34 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_M_H
# define MINISHELL_M_H

# define OUTPUT_REDIRECTION 0
# define APPEND_REDIRECTION 1

typedef struct s_env
{
	char	*line;
	char	*name;
	char	*value;
	int		declared;
	struct s_env	*next;
}	t_env;
typedef struct s_shell
{
	int		last_exit_status;	// To save the exit status ($?) to exit	// Nbr of cmd in the list
	int		exit_status;	// To save the exit status ($?) to exit	// Nbr of cmd in the list
	char	**envp;			// Environment
	t_cmd	*cmds;			// List of cmds
	// Redirections :
	int		total_cmd_count;// Nbr total de cmd
	int		nbr_pipes;		// Nbr total of pipes
	int		infile;			// infile de la commande actuelle
	int		outfile;		// outfile de la commande actuelle
	int		input_pipe;		// If the input is a pipe. 0 if no, 1 if yes
	int		there_is_redir_out; // 0 if no, 1 if yes
	int		n_th_cmd;		// The xth command in the list
	int		**pipes;		// Les pipes (fd[2])
	pid_t	*child_pids;	// ID des processus enfants
}	t_shell;


// Build-in functions
int		ft_pwd(t_shell *shell);
int		ft_echo(t_shell *shell);
int		ft_cd(t_shell *shell);
int		ft_export(t_arg *args, char ***envp);
void	ft_env(char **envp, t_shell *shell);
void	ft_unset(t_arg *args, char ***env);
int		ft_exit(t_shell *shell, t_arg *args);

char	*reading_line(int color);
int		exec_it(t_shell *shell);
int		is_built_in(char **args);
int		is_built_in_t_args(t_arg *args);
int		execute_built_in(t_shell *shell, char **cmd_arg_stdin, char ***envp);
int		do_the_execution(t_shell *shell, t_cmd *cmd, char **envp);
int	handling_pipes(t_shell *shell);
int		execute_solo(t_shell *shell);
int		execution(t_shell *shell);
int		count_pipe(t_cmd *cmd);
char	*find_command_path(t_shell *shell, char *command, char **envp);
int	setup_file_redirections(t_shell *shell);
void	find_and_add_type_cmd(t_arg *args, char **envp);
int		is_redir(t_arg *arg);
int	cut_the_cmd_plus_args(t_cmd *cmd);
void	initiates_type_cmd(t_shell *shell);
int	a_pipe_is_coming(t_shell *shell);
void close_pipes(t_shell *shell);
void clean_all(t_shell *shell);
int	starting_one_cmd(t_shell *shell);
void	find_arg_add_type_cmd(t_shell *shell, t_arg *args);
int	handle_pipe_without_out_redirection(t_shell *shell);

// for envp
t_env   *create_t_env(char **envp);
t_env   *add_node(t_env *head, t_env *new_node);
t_env   *create_node(char *env_line);
char    *get_env_value(char *env_line);
char    *get_env_name(char *env_line);

// Functions Pipex

// Leaks, closes and errors
void	wait_and_cleanup(t_shell *shell);
void	close_both(int to_close1, int to_close2);
void	cleanup(t_shell *shell, char **cmd);

// Here_doc
int		here_doc_management(char *limiter);
int		handle_here_doc(int *argc, char **argv);

// Processes
int		parent_process(t_shell *shell, pid_t pid);
int		handle_io_redirections(t_shell *shell);

// Inits
int		init_pipes(t_shell *shell);
int		init_child_pids(t_shell *shell);
int		init_cmds(t_shell *shell, char **av);
int		init_shell_structure(t_shell *shell);
int		all_init(t_shell *shell);

// Execution
int		do_the_execution(t_shell *shell, t_cmd *cmd, char **envp);
int		is_absolute_or_relative_path(char *command);
char	*handle_absolute_or_relative_path(char *command);
int		execute_with_shell(char *path, char **cmd, char **envp, int cmd_count);
char	**remove_quotes(char **cmd);
char	**special_split(const char *s, char delimiter);

// No bonus
int	fork_process(t_shell *shell);

#endif
