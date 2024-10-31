/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 22:14:46 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/31 07:56:56 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parent_process(t_shell *shell, pid_t pid)
{
	if (shell->infile > STDIN)
		close(shell->infile);
	if (shell->outfile > STDOUT)
		close(shell->outfile);
	shell->child_pids[shell->n_th_cmd] = pid;
	return (0);
}

void	close_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->total_cmd_count - 1)
	{
		close(shell->pipes[i][0]);
		close(shell->pipes[i][1]);
		i++;
	}
}

void	child_process(t_shell *shell)
{
	setup_child_signals();
	if (handle_io_redirections(shell) == -1)
		exit(EXIT_FAILURE);
	if (shell->there_is_redir_out < 0)
	{
		error_msg("Error setup redirection\n");
		exit(EXIT_FAILURE);
	}
	cut_the_cmd_plus_args(shell->cmds);
	if (shell->there_is_redir_out)
		dup2(shell->outfile, STDOUT_FILENO);
	if (shell->there_is_redir_in)
		dup2(shell->infile, STDIN_FILENO);
	setup_pipe_redirections(shell);
	close_pipes(shell);
	if (shell->infile > STDIN)
		close(shell->infile);
	if (shell->outfile > STDOUT)
		close(shell->outfile);
	if (do_the_execution(shell, shell->cmds, shell->envp) == -1)
		exit(1);
}

int	advance_to_next_command(t_shell *shell)
{
	if (shell->cmds->args)
	{
		while (shell->cmds && ft_strcmp(shell->cmds->args->type, "pipe") != 0)
			shell->cmds = shell->cmds->next;
		if (shell->cmds)
			shell->cmds = shell->cmds->next;
	}
	else
		return (-1);
	return (0);
}

int	pipes_process(t_shell *shell)
{
	pid_t	pid;

	shell->infile = dup(STDIN);
	shell->outfile = dup(STDOUT);
	while (shell->cmds)
	{
		pid = fork();
		if (pid == -1)
			return (perror("minishell: fork"), -1);
		if (pid == 0)
		{
			child_process(shell);
		}
		else
			parent_process(shell, pid);
		shell->n_th_cmd++;
		if (advance_to_next_command(shell) == -1)
			break ;
		if (is_a_here_doc_in_the_cmd(shell->cmds))
			shell->nth_here_doc++;
	}
	close_pipes(shell);
	return (0);
}
