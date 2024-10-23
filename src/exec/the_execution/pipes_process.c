/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 22:14:46 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/23 21:27:11 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parent_process(t_shell *shell, pid_t pid)
{
	shell->child_pids[shell->n_th_cmd] = pid;
	return (0);
}

void close_pipes(t_shell *shell)
{
	int i;

	i = 0;
	while (i < shell->total_cmd_count - 1)
	{
		close(shell->pipes[i][0]);
		close(shell->pipes[i][1]);
		i++;
	}
}

int	fork_process(t_shell *shell)
{
	pid_t	pid;

	shell->infile = dup(STDIN);
	shell->outfile = dup(STDOUT);
	while (shell->cmds)
	{
		pid = fork();
		if (pid == -1)
			return (error_msg("Fork failed\n"), -1);
		if (pid == 0)
		{
			setup_child_signals();
			shell->there_is_redir_out = setup_file_redirections(shell);
			if (shell->there_is_redir_out < 0)
				return(error_msg("Error setup redirection\n"));
			cut_the_cmd_plus_args(shell->cmds);
			if (shell->there_is_redir_out)
			{
				dup2(shell->infile, STDIN_FILENO);
				dup2(shell->outfile, STDOUT_FILENO);
				execute_solo_in_pipe(shell);
			}
			else
			{
				handling_pipes(shell);
			}
		}
		else
			parent_process(shell, pid);
		shell->n_th_cmd++;
		if (shell->cmds->args)
		{
    		while (shell->cmds && ft_strcmp(shell->cmds->args->type, "pipe") != 0)
        		shell->cmds = shell->cmds->next; // Move until a pipe is found
    		if (shell->cmds)
        	shell->cmds = shell->cmds->next; // Move to the next command
		}
    	else
        	break; // Exit if there are no more commands
	}
	close_pipes(shell);
	return (0);
}
