/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 22:14:46 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/22 17:28:03 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	parent_process(t_shell *shell, pid_t pid)
// {
// 	shell->child_pids[shell->n_th_cmd] = pid;
// 	return (0);
// }

int	parent_process(t_shell *shell, pid_t pid)
{
	shell->child_pids[shell->n_th_cmd] = pid;
	// if (shell->n_th_cmd == 0)
	// 	close(shell->pipes[shell->n_th_cmd][1]);
	// else if (shell->n_th_cmd == shell->total_cmd_count - 1)
	// 	close(shell->pipes[shell->n_th_cmd - 1][0]);
	// else
	// 	close_both(shell->pipes[shell->n_th_cmd - 1][0], shell->pipes[shell->n_th_cmd][1]);
	return (0);
}

// This function will call to setup_redirection with dup2
// and call the execute function with the cmd and envp
// It will also close the pipes in the parent process
// This function need as arguments :
// - t_pipex *pipex, with all pipes malloced of len cmd_count -1 and inited,
//			cmd_count, infile, outfile and envp initialized
// - char **argv as : infile cmd1 cmd2 ... cmdN outfile
// - int cmd_index as the index of the command to execute
// void	child_process(t_pipex *pipex, int cmd_index)
// {
// 	int	j;

// 	if (setup_redirection(pipex, cmd_index) == -1)
// 	{
// 		cleanup(pipex, NULL, pipex->nbr_pipes);
// 		error_msg("Redirection failed\n");
// 		exit(1);
// 	}
// 	j = 0;
// 	while (j < pipex->nbr_pipes)
// 	{
// 		close(pipex->pipes[j][0]);
// 		close(pipex->pipes[j][1]);
// 		j++;
// 	}
// 	close(pipex->infile);
// 	close(pipex->outfile);
// 	if (do_the_execution(pipex->cmds->args, pipex->envp) == -1)
// 		exit(1);
// 	exit(0);
// }

void close_pipes(t_shell *shell)
{
	int i;

	for (i = 0; i < shell->total_cmd_count - 1; i++)
	{
		close(shell->pipes[i][0]); // Ferme l'extrémité de lecture du pipe
		close(shell->pipes[i][1]); // Ferme l'extrémité d'écriture du pipe
	}
}

// cd > test | cat, dans ce cas, cd est toujours dans un fork
// Donc tjr dans cette fonction on ouvre un fork pour les commandes
int	fork_process(t_shell *shell)
{
	pid_t	pid;

	// all_init(shell); // Il sortira le nombre de pipes a executer
	shell->infile = dup(STDIN);
	shell->outfile = dup(STDOUT);
	while (shell->cmds && ft_strcmp(shell->cmds->args->type, "semicolon") != 0)
	{
		pid = fork();
		if (pid == -1)
			return (error_msg("Fork failed\n"), -1);
		if (pid == 0)
		{
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
