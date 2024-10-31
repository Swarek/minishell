/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_there_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 02:35:04 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/31 02:49:47 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_there_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' &&
			env[i][2] == 'T' && env[i][3] == 'H' && env[i][4] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	is_there_pwd(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'W' &&
			env[i][2] == 'D' && env[i][3] == '=')
			return (1);
		i++;
	}
	return (0);
}
