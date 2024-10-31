/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 06:36:41 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/31 13:47:38 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char **env, char *name)
{
	int	i;
	int	j;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		j = 0;
		while (name[j] && env[i][j] && name[j] == env[i][j])
			j++;
		if (name[j] == '\0' && env[i][j] == '=')
			return (&env[i][j + 1]);
		i++;
	}
	return (NULL);
}

char	*ft_getcwd(char *buf, int size, char **env)
{
	int	i;
	int	len;

	if (!env)
		return (NULL);
	i = 0;
	len = 3;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'W' &&
			env[i][2] == 'D' && env[i][3] == '=')
		{
			if (buf && size > 0)
			{
				if ((int)ft_strlen(env[i] + len + 1) < size)
				{
					ft_strcpy(buf, env[i] + len + 1);
					return (buf);
				}
			}
			return (NULL);
		}
		i++;
	}
	return (NULL);
}
