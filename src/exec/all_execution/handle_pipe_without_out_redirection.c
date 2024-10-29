/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe_without_out_redirection.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:41:49 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/28 20:34:56 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int setup_pipe_redirections(t_shell *shell)
{
	// Première commande
	if (shell->n_th_cmd == 0)
	{
		if (dup2(shell->infile, STDIN_FILENO) == -1)
			return (-1);
		if (shell->there_is_redir_out == 0)
		{
			if (dup2(shell->pipes[shell->n_th_cmd][1], STDOUT_FILENO) == -1)
				return (-1);
		}
	}
	// Dernière commande
	else if (shell->n_th_cmd == shell->total_cmd_count - 1)
	{
		if (dup2(shell->pipes[shell->n_th_cmd - 1][0], STDIN_FILENO) == -1)
			return (-1);
		if (shell->there_is_redir_out == 0)
		{
			if (dup2(shell->outfile, STDOUT_FILENO) == -1)
				return (-1);
		}
			
	}
	// Commandes intermédiaires
	else
	{
		if (dup2(shell->pipes[shell->n_th_cmd - 1][0], STDIN_FILENO) == -1)
			return (-1);
		if (shell->there_is_redir_out == 0)
		{
			if (dup2(shell->pipes[shell->n_th_cmd][1], STDOUT_FILENO) == -1)
				return (-1);
		}
	}	
	return (0);
}


// return 1 if a pipe is coming, 0 otherwise
int	handle_pipe_without_out_redirection(t_shell *shell)
{
	t_cmd *cmd;

	cmd = shell->cmds;
	// print_all_commands(shell->cmds);
	setup_pipe_redirections(shell);
	close_pipes(shell);
	return (0);
}
