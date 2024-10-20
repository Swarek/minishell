/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 23:04:23 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/20 16:04:00 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// typedef struct s_arg
// {
// 	char		*content;
// 	char		*type;
// 	struct s_arg *next;
// }				t_arg;

// typedef struct s_cmd
// {
//     t_arg *args;
//     struct s_cmd *next;
// } t_cmd;

// typedef struct s_pipex
// {
// 	int		**pipes;
// 	int		cmd_count;
// 	int		nbr_pipes;
// 	int		infile;
// 	int		outfile;
// 	char	**envp;
// 	t_cmd	*cmds;
// }	t_pipex;

// typedef struct s_shell
// {
// 	int		last_exit_status;	// To save the exit status ($?) to exit	// Nbr of cmd in the list
// 	char	**envp;			// Environment
// 	t_cmd	*cmds;			// List of cmds
// 	t_arg	*args;			// Liste of args of a cmd (including the cmd)
// 	// Redirections :
// 	int		total_cmd_count;// Nbr total de cmd
// 	int		nbr_pipes;		// Nbr total of pipes
// 	int		infile;			// infile de la commande actuelle
// 	int		outfile;		// outfile de la commande actuelle
// 	int		**pipes;		// Les pipes (fd[2])
// 	pid_t	*child_pids;	// ID des processus enfants
// }	t_shell;


// Enfaite meme avec les pipes j'utiliserai ca mais avec les std differents
int	single_cmd(t_shell *shell)
{
	int	return_value;

	while (ft_strcmp(shell->cmds->args->type, "command") != 0)
		shell->cmds->args = shell->cmds->args->next;
	if (is_built_in(shell->cmds->args))
	{
		return_value = execute_built_in(shell->cmds->args, &shell->envp);
		return (return_value);
	}
	else
	{
		return_value = execute_solo(shell);
		return (return_value);
	}
}

int	exec_it(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell == NULL || shell->cmds == NULL || shell->cmds->args == NULL)
		return (-1);
	// if (setup_file_redirections(shell) == -1) // Attention ca se fera dans la boucle
	// 	return(error_msg("OHH L'ERREUR\n"));  // Et si ca fail il faudra juste que s'il y a un pipe apres on lui envoie NULL
	find_and_add_type_cmd(shell->cmds->args, shell->envp);
	all_init(shell);
	cut_the_cmd_plus_args(shell->cmds);
	// print_all_commands(shell->cmds);
	// single_cmd(shell);
	// while (i < shell->total_cmd_count)
	// {
	// 	if (single_cmd(shell) == -1)
	// 		return (-1);
		// shell->cmds = shell->cmds->next;
	// 	i++;
	// }
	// single_cmd(shell);
	return (0);
}

// L'image Exemple (Ce qui marchait mais etait mal range)
// int	old_exec_it(t_shell *shell)
// {
// 	t_pipex	pipex;
// 	int the_stdin;
// 	int the_stdout;

// 	if (shell == NULL || shell->cmds == NULL || shell->cmds->args == NULL)
// 		return (-1);
// 	shell->args = shell->cmds->args;
// 	the_stdin = dup(STDIN_FILENO);
// 	the_stdout = dup(STDOUT_FILENO);
// 	pipex.cmd_count = count_real_cmd(shell);
// 	if (pipex.cmd_count == 0)
// 		return (ft_printf("Not a cmd\n"), 0);
// 	try_all_redirection(shell->cmds, &pipex);
// 	if (len_cmd(shell->cmds) == 1 || count_pipe(shell->cmds) == 0)
// 		return (single_cmd(shell, the_stdin, the_stdout));
// 	if (all_init(&pipex, shell->envp) == -1)
// 		return (-1);
// 	pipex.cmds = shell->cmds;
// 	fork_process(&pipex);
// 	wait_and_cleanup(&pipex);
// 	return (0);
// }
