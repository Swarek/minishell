/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relative_absolute_path.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:11:50 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/18 10:49:39 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**build_new_cmd(char *path, char **cmd, int args_count)
{
	char	**new_cmd;
	int		j;

	new_cmd = malloc(sizeof(char *) * (args_count + 2));
	if (!new_cmd)
		return (NULL);
	new_cmd[0] = ft_strdup("/bin/sh");
	new_cmd[1] = ft_strdup(path);
	j = 1;
	while (j < args_count)
	{
		new_cmd[j + 1] = ft_strdup(cmd[j]);
		j++;
	}
	new_cmd[args_count + 1] = NULL;
	return (new_cmd);
}

int	execute_with_shell(char *path, char **cmd, char **envp, int args_count)
{
	char	**new_cmd;
	int		j;

	new_cmd = build_new_cmd(path, cmd, args_count);
	if (!new_cmd)
	{
		perror("malloc error");
		return (-1);
	}
	execve("/bin/sh", new_cmd, envp);
	perror("execve error");
	j = 0;
	while (new_cmd[j])
	{
		free(new_cmd[j]);
		j++;
	}
	free(new_cmd);
	return (-1);
}

int	is_absolute_or_relative_path(char *command)
{
	if (!command)
		return (0);
	return (command[0] == '/' || (command[0] == '.' && command[1] == '/')
		|| (command[0] == '.' && command[1] == '.' && command[2] == '/'));
}

char	*handle_absolute_or_relative_path(char *command)
{
	if (access(command, X_OK) == 0)
		return (ft_strdup(command));
	return (NULL);
}
