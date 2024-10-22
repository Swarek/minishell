/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 05:56:18 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/20 20:58:06 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	go_last_place(void)
{
	char	*oldpwd;

	oldpwd = getenv("OLDPWD");
	if (!oldpwd)
		return (error_msg("cd: OLDPWD not set\n"));
	if (chdir(oldpwd) == -1)
		return (error_msg("cd"));
	ft_printf("%s\n", oldpwd);
	return (0);
}

static int	go_home(void)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
	{
		fprintf(stderr, "cd: HOME not set\n");
		return (1);
	}
	if (chdir(home) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	ft_cd(t_shell *shell)
{
	char	**arg;
	char	*cwd;

	if (shell->cmds->cmd_arg_stdin[2] != NULL)
		return (error_msg("too much parameters\n"), -1);
	arg = shell->cmds->cmd_arg_stdin;
	if (!(arg[1]))
	{
		if (go_home() != 0)
			return (-1);
	}
	else if (arg[1][0] == '-' && arg[1][1] == '\0')
	{
		if (go_last_place() != 0)
			return (-1);
	}
	else
	{
		if (chdir(arg[1]) == -1)
			return (perror("cd"), -1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("cd"), -1);
	setenv("OLDPWD", getenv("PWD"), 1);
	setenv("PWD", cwd, 1);
	free(cwd);
	return (0);
}
