/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_and_cleanup_pipes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 02:49:55 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/31 07:08:10 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_and_cleanup(t_shell *shell)
{
	int	i;
	int	status;

	i = 0;
	while (i < shell->total_cmd_count)
	{
		if (waitpid(shell->child_pids[i], &status, 0) == -1)
			shell->exit_status = 1;
		else if (i == shell->total_cmd_count - 1)
		{
			if (WIFEXITED(status))
				shell->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->exit_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	cleanup(shell, NULL);
	if (shell->infile != -1)
		close(shell->infile);
	if (shell->outfile != -1)
		close(shell->outfile);
}

void	cleanup(t_shell *shell, char **cmd)
{
	int	i;

	i = 0;
	while (i < shell->nbr_pipes)
	{
		if (shell->pipes[i])
		{
			close(shell->pipes[i][0]);
			close(shell->pipes[i][1]);
			free(shell->pipes[i]);
		}
		i++;
	}
	free(shell->pipes);
	shell->pipes = NULL;
	if (shell->infile != -1)
		close(shell->infile);
	if (cmd)
		safe_free_all_strings(&cmd);
	if (shell->outfile != -1)
		close(shell->outfile);
	if (shell->child_pids)
		ft_safe_free((void **)&(shell->child_pids));
}
