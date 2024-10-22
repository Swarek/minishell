/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 22:14:46 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/22 04:30:11 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parent_process(t_shell *shell, pid_t pid)
{
	shell->child_pids[shell->n_th_cmd] = pid;
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

// This function will do all the forks and call the execute_child_process
// It will also close the pipes in the parent process
// This function need as arguments :
// - t_pipex *pipex, with all pipes malloced of len cmd_count -1 and inited,
//			cmd_count, infile, outfile and envp initialized
// - char **argv as : infile cmd1 cmd2 ... cmdN outfile
// - pid_t *child as malloced array of pid_t, of len cmd_count

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
			else if (a_pipe_is_coming(shell))
			{
				a_pipe_is_coming(shell);
			}
			else
			{
				ft_printf("Passage dans le else du fork_process\n");
				// single_cmd(shell);
			}
			// child_process(shell, cmd_index);
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
	return (0);
}
