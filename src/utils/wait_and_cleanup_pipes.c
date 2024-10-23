/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_and_cleanup_pipes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 02:49:55 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/23 09:55:38 by mblanc           ###   ########.fr       */
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
		{
			error_msg("Waitpid failed\n");
			shell->exit_status = 1;
		}
		else if (i == shell->total_cmd_count - 1)
		{
			if (WIFEXITED(status))
			{
				shell->exit_status = WEXITSTATUS(status);
				ft_printf("shell->exit_status = %d\n", shell->exit_status);
			}
			else if (WIFSIGNALED(status))
			{
				shell->exit_status = 128 + WTERMSIG(status);
				ft_printf("shell->exit_status = %d\n", shell->exit_status);
			}
		}
		i++;
	}
	ft_printf("shell->exit_status = %d\n", shell->exit_status);
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
		free(shell->child_pids);
}
