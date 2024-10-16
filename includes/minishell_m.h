/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_m.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:22:47 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/18 18:32:27 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_M_H
# define MINISHELL_M_H

# include "minishell.h"

# define OUTPUT_REDIRECTION 0
# define APPEND_REDIRECTION 1
typedef struct s_shell
{
	int		last_exit_status;	// To save the exit status ($?) to exit
	int		cmd_count;		// Nbr of cmd in the list
	char	**envp;			// Environnemen
	t_cmd	*cmds;			// List of cmds
	t_arg	*args;			// Liste of args of a cmd (including the cmd)
}	t_shell;

typedef struct s_pipex
{
	int		**pipes;
	int		cmd_count;
	int		nbr_pipes;
	int		infile;
	int		outfile;
	char	**envp;
	int		fd[2];
	t_cmd	*cmds;
	pid_t	*child_pids;
}	t_pipex;

// Build-in functions
int		ft_pwd(void);
int		ft_echo(t_arg *args);
int		ft_cd(t_arg *args);
int		ft_export(t_arg *args, char ***envp);
void	ft_env(char **envp);
void	ft_unset(t_arg *args, char ***env);
int		ft_exit(t_arg *args);

char	*reading_line(int color);
int		ft_echo(t_arg *args);
int		exec_it(t_shell *shell);
int		is_built_in(t_arg *args);
int		execute_built_in(t_arg *args, char ***envp);
int		do_the_execution(t_arg *args, char **envp);
int		execute_solo(t_shell *shell);
int		execution(t_shell *shell);

// Functions Pipex

// Leaks, closes and errors
void	wait_and_cleanup(t_pipex *pipex);
void	close_both(int to_close1, int to_close2);
void	cleanup(t_pipex *pipex, char **cmd, int max_pipes);

// Here_doc
int		here_doc_management(char *limiter);
int		handle_here_doc(int *argc, char **argv);

// Processes
int		fork_process(t_pipex *pipex);
void	child_process(t_pipex *pipex, int cmd_index);
int		parent_process(t_pipex *pipex, pid_t pid, int cmd_index);
int		setup_redirection(t_pipex *pipex, int cmd_index);

// Inits
int		init_pipes(t_pipex *pipex);
int		init_child_pids(t_pipex *pipex);
int		init_cmds(t_pipex *pipex, char **av);
int		init_pipex_structure(t_pipex *pipex, char **env);
int		all_init(t_pipex *pipex, char **env);
int		opening_files(t_pipex *pipex, char *infile, char *outfile, int output_mode);

// Execution
int		do_the_execution(t_arg *args, char **envp);
int		is_absolute_or_relative_path(char *command);
char	*handle_absolute_or_relative_path(char *command);
int		execute_with_shell(char *path, char **cmd, char **envp, int cmd_count);
char	**remove_quotes(char **cmd);
char	**special_split(const char *s, char delimiter);

// No bonus
int		fork_process(t_pipex *pipex);
void	process_pipe(t_pipex *pipex, char *cmd1, char *cmd2);

#endif