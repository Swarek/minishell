/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_pipe_is_coming.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:41:49 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/22 04:52:05 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int setup_redirection(t_shell *shell)
{
	// Première commande
	if (shell->n_th_cmd == 0)
	{
		if (dup2(shell->infile, STDIN_FILENO) == -1
			|| dup2(shell->pipes[shell->n_th_cmd][1], STDOUT_FILENO) == -1)
			return (-1);
	}
	// Dernière commande
	else if (shell->n_th_cmd == shell->total_cmd_count - 1)
	{
		if (dup2(shell->pipes[shell->n_th_cmd - 1][0], STDIN_FILENO) == -1
			|| dup2(shell->outfile, STDOUT_FILENO) == -1)
			return (-1);
	}
	// Commandes intermédiaires
	else
	{
		if (dup2(shell->pipes[shell->n_th_cmd - 1][0], STDIN_FILENO) == -1
			|| dup2(shell->pipes[shell->n_th_cmd][1], STDOUT_FILENO) == -1)
			return (-1);
	}
	
	// IMPORTANT : Ne ferme pas les pipes ici, fais-le après la création de tous les processus
	
	return (0);
}


// return 1 if a pipe is coming, 0 otherwise
int	a_pipe_is_coming(t_shell *shell)
{
	t_cmd *cmd;

	cmd = shell->cmds;
	setup_redirection(shell);
	close_pipes(shell);
	execute_solo_in_pipe(shell);
	return (0);
}
