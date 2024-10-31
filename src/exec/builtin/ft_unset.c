/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:00:31 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/31 02:33:35 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_arg *args, char ***env, t_shell *shell)
{
	int		j;
	size_t	len;
	int		error_flag;

	args = args->next;
	error_flag = 0;
	while (args)
	{
		if (!is_valid_identifier(args->content))
		{
			error_msg("unset: not a valid identifier\n");
			shell->exit_status = 1;
			error_flag = 1;
			args = args->next;
			continue ;
		}
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
	if (!error_flag)
		shell->exit_status = 0;
}
