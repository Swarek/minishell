/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_pipe_is_coming.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:41:49 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/22 04:31:34 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_redirection(t_shell *shell)
{
	if (shell->n_th_cmd == 0)
	{
		if (dup2(shell->infile, STDIN_FILENO) == -1
			|| dup2(shell->pipes[shell->n_th_cmd][1], STDOUT_FILENO) == -1) // Pour tous les premiers dup2 (les entree), en gros c'est cense viser
			return (-1);											// pipex->pipes[shell->n_th_cmd - 1][0], mais si la precedente commande
																	// avait deja une redirection de son stdout, le pipe prendra en in rien (a voir comment faire)
	}
	else if (shell->n_th_cmd == shell->total_cmd_count - 1)
	{
		if (dup2(shell->pipes[shell->n_th_cmd - 1][0], STDIN_FILENO) == -1
			|| dup2(shell->outfile, STDOUT_FILENO) == -1)
			return (-1);
	}
	else
	{
		if (dup2(shell->pipes[shell->n_th_cmd - 1][0], STDIN_FILENO) == -1
			|| dup2(shell->pipes[shell->n_th_cmd][1], STDOUT_FILENO) == -1)
			return (-1);
	}
	return (0);
}

// return 1 if a pipe is coming, 0 otherwise
int	a_pipe_is_coming(t_shell *shell)
{
	t_cmd *cmd;

	cmd = shell->cmds;
	setup_redirection(shell);
	execute_solo_in_pipe(shell);
	return (0);
}
