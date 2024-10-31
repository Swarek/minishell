/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 05:56:18 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/31 13:44:44 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	go_last_place(t_shell *shell)
{
	char	*oldpwd;

	oldpwd = ft_getenv(shell->envp, "OLDPWD");
	if (!oldpwd)
	{
		error_msg("cd: OLDPWD not set\n");
		shell->exit_status = 1;
		return (shell->exit_status);
	}
	if (chdir(oldpwd) == -1)
	{
		perror("cd");
		shell->exit_status = 1;
		return (shell->exit_status);
	}
	ft_printf("%s\n", oldpwd);
	return (0);
}

static int	go_home(t_shell *shell)
{
	char	*home;

	home = ft_getenv(shell->envp, "HOME");
	if (!home)
	{
		error_msg("cd: HOME not set\n");
		shell->exit_status = 1;
		return (shell->exit_status);
	}
	if (chdir(home) == -1)
	{
		perror("cd");
		shell->exit_status = 1;
		return (shell->exit_status);
	}
	return (0);
}

static int	end_cd(t_shell *shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("cd");
		shell->exit_status = 1;
		return (shell->exit_status);
	}
	setenv("OLDPWD", ft_getenv(shell->envp, "PWD"), 1);
	setenv("PWD", cwd, 1);
	return (free(cwd), shell->exit_status = 0, 0);
}

int	ft_cd(t_shell *shell)
{
	char	**arg;

	if (is_there_path(shell->envp) == 0 || is_there_pwd(shell->envp) == 0)
		return (error_msg("cd HOME not set\n"), shell->exit_status = 1, 1);
	arg = shell->cmds->cmd_arg_stdin;
	if (arg == NULL || arg[0] == NULL)
		return (0);
	if (arg[1] != NULL && arg[2] != NULL)
		return (error_msg("cd too many arguments\n"), shell->exit_status = 1, 1);
	if (!arg[1])
	{
		if (go_home(shell) != 0)
			return (shell->exit_status);
	}
	else if (arg[1][0] == '-' && arg[1][1] == '\0')
	{
		if (go_last_place(shell) != 0)
			return (shell->exit_status);
	}
	else
	{
		if (chdir(arg[1]) == -1)
			return (perror("cd"), shell->exit_status = 1, 1);
	}
	return (end_cd(shell));
}
