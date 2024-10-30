/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 06:36:41 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/30 23:27:23 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char **env, char *name)
{
	int	i;
	int	j;

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
