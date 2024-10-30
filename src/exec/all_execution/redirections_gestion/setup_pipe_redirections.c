/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipe_redirections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:41:49 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/30 18:21:37 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	first_pipe_redirections(t_shell *shell)
{
	if (shell->there_is_redir_in == 0)
	{
		if (dup2(shell->infile, STDIN_FILENO) == -1)
			return (-1);
	}
	if (shell->there_is_redir_out == 0)
	{
		if (dup2(shell->pipes[shell->n_th_cmd][1], STDOUT_FILENO) == -1)
			return (-1);
	}
	return (0);
}

int	last_pipe_redirections(t_shell *shell)
{
	if (shell->there_is_redir_in == 0)
	{
		if (dup2(shell->pipes[shell->n_th_cmd - 1][0], STDIN_FILENO) == -1)
			return (-1);
	}
	if (shell->there_is_redir_out == 0)
	{
		if (dup2(shell->outfile, STDOUT_FILENO) == -1)
			return (-1);
	}
	return (0);
}

int	middle_pipe_redirections(t_shell *shell)
{
	if (shell->there_is_redir_in == 0)
	{
		if (dup2(shell->pipes[shell->n_th_cmd - 1][0], STDIN_FILENO) == -1)
			return (-1);
	}
	if (shell->there_is_redir_out == 0)
	{
		if (dup2(shell->pipes[shell->n_th_cmd][1], STDOUT_FILENO) == -1)
			return (-1);
	}
	return (0);
}

int	setup_pipe_redirections(t_shell *shell)
{
	if (shell->n_th_cmd == 0)
		first_pipe_redirections(shell);
	else if (shell->n_th_cmd == shell->total_cmd_count - 1)
		last_pipe_redirections(shell);
	else
		middle_pipe_redirections(shell);
	return (0);
}
