/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 02:55:26 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/31 13:45:50 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction pour exécuter la commande
static void	execute_command(t_shell *shell, t_cmd *cmd, char *path)
{
	if (execve(path, cmd->cmd_arg_stdin, shell->envp) == -1)
	{
		if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
		{
			free(path);
			error_msg("error");
			exit(126);
		}
		free(path);
		perror("execve error");
		exit(126);
	}
}

// Fonction auxiliaire pour préparer l'exécution
static char	*prepare_execution(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	if (!cmd || !cmd->args || !cmd->args->content)
	{
		error_msg("Command content is NULL\n");
		exit(127);
	}
	if (is_real_cmd_in_cmds(cmd) == 0 || !cmd->cmd_arg_stdin)
	{
		error_msg("command not found\n");
		exit(127);
	}
	path = find_command_path(shell, cmd->cmd_arg_stdin[0], shell->envp);
	if (!path)
	{
		error_msg("execve error");
		exit(shell->exit_status);
	}
	if (!cmd->cmd_arg_stdin)
	{
		error_msg("command arguments are NULL\n");
		free(path);
		exit(127);
	}
	return (path);
}

// Fonction principale pour effectuer l'exécution
int	do_the_execution(t_shell *shell, t_cmd *cmd, char **envp)
{
	char	*path;

	(void)envp;
	path = prepare_execution(shell, cmd);
	execute_command(shell, cmd, path);
	free(path);
	return (0);
}

void	child_process_execute_solo(t_shell *shell)
{
	setup_child_signals();
	dup2(shell->infile, STDIN_FILENO);
	dup2(shell->outfile, STDOUT_FILENO);
	if (shell->infile > STDIN)
		close(shell->infile);
	if (shell->outfile > STDOUT)
		close(shell->outfile);
	if (do_the_execution(shell, shell->cmds, shell->envp) == -1)
		exit(1);
}

// Fonction pour exécuter une commande seule
int	execute_solo(t_shell *shell)
{
	pid_t	pid;
	int		status;

	status = -1;
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (shell->exit_status = 1, -1);
	}
	if (pid == 0)
		child_process_execute_solo(shell);
	else
	{
		waitpid(pid, &status, 0);
		if (status == -1)
			return (0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->exit_status = 128 + WTERMSIG(status);
		else
			shell->exit_status = 1;
	}
	return (0);
}
