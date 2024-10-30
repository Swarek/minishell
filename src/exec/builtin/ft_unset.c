/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:00:31 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/30 17:43:10 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_arg *args, char ***env)
{
	int		j;
	size_t	len;

	args = args->next;
	while (args)
	{
		j = 0;
		len = ft_strlen(args->content);
		while ((*env)[j])
		{
			if (ft_strncmp((*env)[j], args->content, len) == 0
				&& (*env)[j][len] == '=')
			{
				free((*env)[j]);
				while ((*env)[j])
				{
					(*env)[j] = (*env)[j + 1];
					j++;
				}
				break ;
			}
			j++;
		}
		args = args->next;
	}
}
