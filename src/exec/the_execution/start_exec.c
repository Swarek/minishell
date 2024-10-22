/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 23:04:23 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/22 17:09:01 by mblanc           ###   ########.fr       */
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
	if (is_built_in(shell->cmds->cmd_arg_stdin))
	{
		return_value = execute_built_in(shell, shell->cmds->cmd_arg_stdin, &shell->envp);
		return (return_value);
	}
	else
	{
		return_value = execute_solo(shell);
		return (return_value);
	}
}

int	one_cmd(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell == NULL || shell->cmds == NULL || shell->cmds->args == NULL)
		return (-1);
	if (setup_file_redirections(shell) == -1) // Attention ca se fera dans la boucle
		return(error_msg("OHH L'ERREUR\n"));  // Et si ca fail il faudra juste que s'il y a un pipe apres on lui envoie NULL
	all_init(shell);
	cut_the_cmd_plus_args(shell->cmds);
	// print_all_commands(shell->cmds);
	single_cmd(shell);
	return (0);
}

int	exec_it(t_shell *shell)
{
	if (shell == NULL || shell->cmds == NULL || shell->cmds->args == NULL)
		return (-1);
	initiates_type_cmd(shell);
	if (shell->total_cmd_count == 1) // Plus tard plutot faire une verif que ya pas de pipes
		return (setup_file_redirections(shell), one_cmd(shell)); // Comme ca au lieu de one_cmd c'est "no_pipe_cmd" et on gere si ya plusieurs ;
	else if (shell->total_cmd_count > 1)
	{
		all_init(shell);
		fork_process(shell);
		wait_and_cleanup(shell);
	}
	// ft_printf("shell->total_cmd_count : %d\n", shell->total_cmd_count);
	// print_all_commands(shell->cmds);
	return (0);
}
