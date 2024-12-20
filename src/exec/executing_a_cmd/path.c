/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 22:32:29 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/31 13:33:14 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction auxiliaire pour créer le chemin complet de la commande
static char	*create_command_path(char *path, char *command)
{
	char	*temp;
	char	*full_path;

	if (path == NULL)
		return (NULL);
	if (path[ft_strlen(path) - 1] != '/')
	{
		temp = ft_strjoin(path, "/");
		if (!temp)
			return (error_msg("memory allocation error\n"), NULL);
	}
	else
	{
		temp = ft_strdup(path);
	}
	if (!temp)
		return (error_msg("memory allocation error\n"), NULL);
	full_path = ft_strjoin(temp, command);
	free(temp);
	return (full_path);
}

// Fonction auxiliaire pour vérifier l'accès au chemin de la commande
static char	*verify_command_access(t_shell *shell, char *path, char *command)
{
	char	*command_path;

	if (!path)
	{
		shell->exit_status = 127;
		return (NULL);
	}
	command_path = create_command_path(path, command);
	if (!command_path)
	{
		free(path);
		shell->exit_status = 12;
		return (NULL);
	}
	if (access(command_path, X_OK) == 0)
	{
		free(path);
		return (command_path);
	}
	if (access(command_path, F_OK) == 0)
		shell->exit_status = 126;
	else
		shell->exit_status = 127;
	free(command_path);
	return (free(path), NULL);
}

// Nouvelle fonction pour rechercher la commande dans PATH
static char	*search_in_path(t_shell *shell, char *command, char **paths)
{
	int		i;
	char	*command_path;

	i = 0;
	while (paths[i] != NULL)
	{
		command_path = verify_command_access(shell, ft_strdup(paths[i]),
				command);
		if (command_path)
			return (safe_free_all_strings(&paths), command_path);
		i++;
	}
	if (shell->exit_status == 12)
		return (error_msg("command not found\n"), NULL);
	if (shell->exit_status == 126)
		return (error_msg("Permission denied\n"), NULL);
	if (shell->exit_status == 127)
		return (error_msg("command not found\n"), NULL);
	return (NULL);
}

// Fonction pour trouver le chemin de la commande
char	*get_path_from_env(t_shell *shell, char *command, char **envp)
{
	char	**paths;
	char	*command_path;
	int		i;

	i = 0;
	while (envp[i] != NULL && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
	{
		error_msg("command not found\n");
		return (shell->exit_status = 127, NULL);
	}
	paths = ft_split(envp[i] + 5, ':');
	if (paths == NULL)
	{
		error_msg("memory allocation error\n");
		return (shell->exit_status = 12, NULL);
	}
	command_path = search_in_path(shell, command, paths);
	if (command_path)
		return (command_path);
	safe_free_all_strings(&paths);
	return (NULL);
}

char	*find_command_path(t_shell *shell, char *command, char **envp)
{
	if (!command || *command == '\0' || ft_str_is_whitespace(command)
		|| envp == NULL)
	{
		error_msg("command nost found\n");
		shell->exit_status = 127;
		return (NULL);
	}
	if (is_absolute_or_relative_path(command))
	{
		if (access(command, F_OK) == 0 && access(command, X_OK) != 0)
		{
			error_msg("Permission denied\n");
			shell->exit_status = 126;
			return (NULL);
		}
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
		error_msg("command notf found\n");
		shell->exit_status = 127;
		return (NULL);
	}
	return (get_path_from_env(shell, command, envp));
}
