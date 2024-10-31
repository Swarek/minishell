/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_basic_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 04:13:52 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/31 05:32:12 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction principale pour créer l'environnement de base
int	init_env_vars(t_shell *shell, char *pwd_value)
{
	int	ret;

	ret = ft_setenv("PWD", pwd_value, &(shell->envp));
	if (ret == -1)
		return (-1);
	ret = ft_setenv("SHLVL", "1", &(shell->envp));
	if (ret == -1)
		return (-1);
	ret = ft_setenv("_", "/usr/bin/env", &(shell->envp));
	if (ret == -1)
		return (-1);
	return (0);
}

int	create_basic_env(t_shell *shell)
{
	char	cwd[PATH_MAX];
	char	*pwd_value;
	int		ret;

	shell->envp = malloc(sizeof(char *));
	if (!shell->envp)
		return (-1);
	shell->envp[0] = NULL;
	if (!getcwd(cwd, sizeof(cwd)))
	{
		free(shell->envp);
		return (-1);
	}
	pwd_value = ft_strdup(cwd);
	if (!pwd_value)
	{
		free(shell->envp);
		return (-1);
	}
	ret = init_env_vars(shell, pwd_value);
	free(pwd_value);
	if (ret == -1)
		return (free(shell->envp), -1);
	return (0);
}
