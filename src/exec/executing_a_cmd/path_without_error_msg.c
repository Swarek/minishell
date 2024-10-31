/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_without_error_msg.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 22:32:29 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/31 07:51:50 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction auxiliaire pour créer le chemin complet de la commande
static char	*n_create_command_path(char *path, char *command)
{
	char	*temp;
	char	*full_path;

	if (path == NULL)
		return (NULL);
	if (path[ft_strlen(path) - 1] != '/')
	{
		temp = ft_strjoin(path, "/");
		if (!temp)
			return (NULL);
	}
	else
	{
		temp = ft_strdup(path);
	}
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, command);
	free(temp);
	return (full_path);
}

// Fonction auxiliaire pour vérifier l'accès au chemin de la commande
static char	*n_verify_command_access(t_shell *shell, char *path, char *command)
{
	char	*command_path;

	if (!path)
	{
		shell->exit_status = 127;
		return (NULL);
	}
	command_path = n_create_command_path(path, command);
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
static char	*n_search_in_path(t_shell *shell, char *command, char **paths)
{
	int		i;
	char	*command_path;

	i = 0;
	while (paths[i] != NULL)
	{
		command_path = n_verify_command_access(shell, ft_strdup(paths[i]),
				command);
		if (command_path)
		{
			safe_free_all_strings(&paths);
			return (command_path);
		}
		i++;
	}
	return (NULL);
}

// Fonction pour trouver le chemin de la commande
char	*n_get_path_from_env(t_shell *shell, char *command, char **envp)
{
	char	**paths;
	char	*command_path;
	int		i;

	i = 0;
	while (envp[i] != NULL && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (shell->exit_status = 127, NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (paths == NULL)
		return (shell->exit_status = 12, NULL);
	command_path = n_search_in_path(shell, command, paths);
	if (command_path)
		return (command_path);
	safe_free_all_strings(&paths);
	return (NULL);
}

char	*n_find_command_path(t_shell *shell, char *command, char **envp)
{
	if (!command || *command == '\0' || ft_str_is_whitespace(command)
		|| envp == NULL)
	{
		shell->exit_status = 127;
		return (NULL);
	}
	if (is_absolute_or_relative_path(command))
	{
		if (access(command, F_OK) == 0 && access(command, X_OK) != 0)
		{
			shell->exit_status = 126;
			return (NULL);
		}
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
		shell->exit_status = 127;
		return (NULL);
	}
	return (n_get_path_from_env(shell, command, envp));
}
