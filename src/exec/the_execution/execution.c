/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 02:55:26 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/23 12:20:25 by mblanc           ###   ########.fr       */
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
		return (shell->exit_status = 127, NULL);
	if (is_absolute_or_relative_path(command))
	{
		if (access(command, F_OK) == 0 && access(command, X_OK) != 0)
			return (shell->exit_status = 126, NULL); // Fichier existe mais pas exécutable
		if (access(command, X_OK) == 0)
			return (ft_strdup(command)); // Fichier accessible et exécutable
		return (shell->exit_status = 127, NULL); // Fichier introuvable ou autre erreur
	}
	
	// Chercher dans les chemins du PATH
	i = 0;
	while (envp[i] != NULL && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (shell->exit_status = 127, NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (paths == NULL)
		return (shell->exit_status = 12, NULL);
	i = -1;
	while (paths[++i])
	{
		command_path = verify_a_path(shell, ft_strdup(paths[i]), command);
		if (command_path)
			return (safe_free_all_strings(&paths), command_path);
	}
	safe_free_all_strings(&paths);
	return (shell->exit_status = 127, NULL); // Commande introuvable
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
		setup_child_signals();
		dup2(shell->infile, STDIN_FILENO);
		dup2(shell->outfile, STDOUT_FILENO);
		if (do_the_execution(shell, shell->cmds, shell->envp) == -1)
			exit(1);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->exit_status = 128 + WTERMSIG(status);
		else
			shell->exit_status = 1;
	}
	return (0);
}

int	do_the_execution(t_shell *shell, t_cmd *cmd, char **envp)
{
	char	*path;
	int		nbr_args;

	if (!cmd || !cmd->args || !cmd->args->content)
	{
		perror("Command content is NULL");
		exit(127);
	}

	// Rechercher le chemin de la commande
	path = find_command_path(shell, cmd->args->content, envp);
	if (!path)
	{
		perror("execve error");
		exit(shell->exit_status);
	}
	// Vérifier les arguments de la commande
	if (!cmd->cmd_arg_stdin)
	{
		perror("Command arguments are NULL");
		free(path);
		exit(127);
	}

	// Tenter d'exécuter la commande avec execve
	nbr_args = count_arguments(cmd->cmd_arg_stdin);
	if (execve(path, cmd->cmd_arg_stdin, envp) == -1)
	{
		// Vérifier si l'erreur vient d'un problème de permissions
		if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
		{
			free(path);
			perror("execve error");
			exit(126); // Code 126 pour permission refusée
		}
		free(path);
		perror("execve error");
		exit(127); // Code 127 pour commande introuvable ou autre erreur
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
