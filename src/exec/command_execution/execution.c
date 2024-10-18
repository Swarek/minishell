/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 02:55:26 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/18 17:34:44 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*verify_a_path(char *path, char *command)
{
	char	*command_path;
	char	*temp;

	if (!path)
		return (NULL);
	if (path[ft_strlen(path) - 1] != '/')
	{
		temp = ft_strjoin(path, "/");
		if (!temp)
			return (free(path), NULL);
		command_path = ft_strjoin(temp, command);
		free(temp);
	}
	else
		command_path = ft_strjoin(path, command);
	if (command_path == NULL)
		return (free(path), NULL);
	free(path);
	if (access(command_path, X_OK) == 0)
		return (command_path);
	free(command_path);
	return (NULL);
}

static char	*find_command_path(char *command, char **envp)
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
		command_path = verify_a_path(ft_strdup(paths[i]), command);
		if (command_path)
			return (safe_free_all_strings(&paths), command_path);
	}
	safe_free_all_strings(&paths);
	return (NULL);
}

int	execute_solo(t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		error_msg("Fork failed\n");
		return (-1);
	}
	if (pid == 0)
	{
		if (do_the_execution(shell->args, shell->envp) == -1)
			exit(1);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->last_exit_status = WEXITSTATUS(status);
	}
	return (0);
}

int	do_the_execution(t_arg *args, char **envp)
{
	char	**cmd;
	char	*path;
	int		nbr_args;
	int		access_result;

	path = find_command_path(args->content, envp);
	if (!path)
		return (-1);
	nbr_args = count_arguments(args);
	cmd = convert_args_to_argv(args);
	if (execve(path, cmd, envp) == -1)
	{
		access_result = access(path, X_OK);
		if (access_result == 0)
			execute_with_shell(path, cmd, envp, nbr_args);
		else
			perror("execve error");
		free(path);
		error_msg("Command execution failed\n");
		safe_free_all_strings(&cmd);
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
