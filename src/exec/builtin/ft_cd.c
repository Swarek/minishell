/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 05:56:18 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/28 21:36:51 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static int	go_last_place(t_shell *shell)
{
	char	*oldpwd;

	oldpwd = getenv("OLDPWD");
	if (!oldpwd)
	{
		error_msg("cd: OLDPWD not set\n");
		shell->exit_status = 1; // Erreur spécifique si OLDPWD n'est pas défini
		return (shell->exit_status);
	}
	if (chdir(oldpwd) == -1)
	{
		perror("cd");
		shell->exit_status = 1; // Erreur si chdir échoue
		return (shell->exit_status);
	}
	ft_printf("%s\n", oldpwd);
	return (0);
}

static int	go_home(t_shell *shell)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
	{
		fprintf(stderr, "cd: HOME not set\n");
		shell->exit_status = 1; // Erreur spécifique si HOME n'est pas défini
		return (shell->exit_status);
	}
	if (chdir(home) == -1)
	{
		perror("cd");
		shell->exit_status = 1; // Erreur si chdir échoue
		return (shell->exit_status);
	}
	return (0);
}

int	ft_cd(t_shell *shell)
{
	char	**arg;
	char	*cwd;

	arg = shell->cmds->cmd_arg_stdin;
	if (arg[2] != NULL)
	{
		error_msg("cd: too many arguments\n");
		shell->exit_status = 1; // Trop d'arguments
		return (shell->exit_status);
	}

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
		{
			perror("cd");
			shell->exit_status = 1; // Erreur si chdir échoue
			return (shell->exit_status);
		}
	}

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("cd");
		shell->exit_status = 1;
		return (shell->exit_status);
	}

	setenv("OLDPWD", getenv("PWD"), 1);
	setenv("PWD", cwd, 1);
	free(cwd);
	shell->exit_status = 0;
	return (0);
}

