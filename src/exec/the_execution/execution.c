/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 02:55:26 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/22 18:57:01 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*verify_a_path(t_shell *shell, char *path, char *command)
{
	char	*command_path;
	char	*temp;

	if (!path)
		return (shell->exit_status = 127, NULL);
	if (path[ft_strlen(path) - 1] != '/')
	{
		temp = ft_strjoin(path, "/");
		if (!temp)
			return (free(path), shell->exit_status = 12, NULL);
		command_path = ft_strjoin(temp, command);
		if (command_path == NULL)
			return (free(path), free(temp), shell->exit_status = 12, NULL);
		free(temp);
	}
	else
		command_path = ft_strjoin(path, command);
	if (command_path == NULL)
		return (free(path), shell->exit_status = 12, NULL);
	free(path);
	if (access(command_path, X_OK) == 0)
		return (command_path);
	if (access(command_path, F_OK) == 0)
		shell->exit_status = 126;
	else
		shell->exit_status = 127;
	free(command_path);
	return (NULL);
}

char	*find_command_path(t_shell *shell, char *command, char **envp)
{
	int		i;
	char	**paths;
	char	*command_path;

	if (!command || *command == '\0' || ft_str_is_whitespace(command))
		return (NULL);
	if (is_absolute_or_relative_path(command))
		return (handle_absolute_or_relative_path(command));
	i = 0;
	while (envp[i] != NULL && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (paths == NULL)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		command_path = verify_a_path(shell, ft_strdup(paths[i]), command);
		if (command_path)
			return (safe_free_all_strings(&paths), command_path);
	}
	safe_free_all_strings(&paths);
	return (shell->exit_status = 127, NULL);
}

int	execute_solo(t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		error_msg("Fork failed\n");
		shell->exit_status = 1;
		return (-1);
	}
	if (pid == 0)
	{
		dup2(shell->infile, STDIN_FILENO);
		dup2(shell->outfile, STDOUT_FILENO);
		if (do_the_execution(shell, shell->cmds, shell->envp) == -1)
			exit(1);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (status % 256 == 0) // Vérifie si les bits de poids faible sont à 0
			shell->exit_status = status / 256; // Récupère le code de sortie normal
		else
			shell->exit_status = 128 + status; // Récupère le signal qui a tué le processus
	}
	return (0);
}

int	do_the_execution(t_shell *shell, t_cmd *cmd, char **envp)
{
	char	*path;
	int		nbr_args;
	int		access_result;

	path = find_command_path(shell, cmd->args->content, envp);
	if (!path)
		return (-1);
	nbr_args = count_arguments(cmd->cmd_arg_stdin);
	if (execve(path, cmd->cmd_arg_stdin, envp) == -1)
	{
		access_result = access(path, X_OK);
		if (access_result == 0)
			execute_with_shell(path, cmd->cmd_arg_stdin, envp, nbr_args);
		else
			perror("execve error");
		free(path);
		error_msg("Command execution failed\n");
		return (-1);
	}
	free(path);
	return (0);
}

// int	execute(char *argv, char **envp)
// {
// 	char	**cmd;
// 	char	*path;

// 	cmd = special_split(argv, ' ');
// 	if (!cmd || are_strings_white_spaces(cmd) == 1)
// 	{
// 		error_msg("Command split failed\n");
// 		return (-1);
// 	}
// 	cmd = remove_quotes(cmd);
// 	if (!cmd || !cmd[0] || ft_strcmp(cmd[0], " ") == 0)
// 	{
// 		safe_free_all_strings(&cmd);
// 		error_msg("Empty command\n");
// 		return (-1);
// 	}
// 	path = find_command_path(cmd[0], envp);
// 	if (!path)
// 	{
// 		error_msg("Command not found\n");
// 		safe_free_all_strings(&cmd);
// 		return (-1);
// 	}
// 	if (execve(path, cmd, envp) == -1)
// 	{
// 		error_msg("Command execution failed\n");
// 		safe_free_all_strings(&cmd);
// 		return (-1);
// 	}
// 	return (0);
// }
