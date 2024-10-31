/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 03:58:08 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/31 05:29:10 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_create_env_entry(char **entry, char *name, char *value)
{
	char	*temp;

	temp = ft_strjoin(name, "=");
	if (!temp)
		return (-1);
	*entry = ft_strjoin(temp, value);
	free(temp);
	if (!*entry)
		return (-1);
	return (0);
}

int	ft_update_env_entry(char *name, char *value, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, ft_strlen(name)) == 0
			&& envp[i][ft_strlen(name)] == '=')
		{
			free(envp[i]);
			if (ft_create_env_entry(&(envp[i]), name, value) == -1)
				return (-1);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_setenv(char *name, char *value, char ***envp)
{
	int		envp_len;
	char	**new_envp;
	int		i;

	if (ft_update_env_entry(name, value, *envp) == 0)
		return (0);
	i = 0;
	while ((*envp)[i])
		i++;
	envp_len = i;
	new_envp = malloc(sizeof(char *) * (envp_len + 2));
	if (!new_envp)
		return (-1);
	i = 0;
	while (i < envp_len)
	{
		new_envp[i] = (*envp)[i];
		i++;
	}
	if (ft_create_env_entry(&(new_envp[i]), name, value) == -1)
		return (-1);
	new_envp[i + 1] = NULL;
	free(*envp);
	*envp = new_envp;
	return (0);
}

int	shlvl_incrementation(t_shell *shell)
{
	char	*shlvl;
	int		n;

	if (!shell->envp)
		return (1);
	shlvl = ft_getenv(shell->envp, "SHLVL");
	if (!shlvl)
		n = 1;
	else
	{
		n = ft_atoi(shlvl);
		if (n < 0)
			n = 0;
		n++;
	}
	shlvl = ft_itoa(n);
	if (!shlvl)
		return (1);
	if (ft_setenv("SHLVL", shlvl, &shell->envp) == -1)
	{
		free(shlvl);
		return (1);
	}
	free(shlvl);
	return (0);
}
