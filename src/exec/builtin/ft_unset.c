/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:00:31 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/31 03:40:06 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_error(t_arg *args, t_shell *shell, int *error_flag)
{
	if (!is_valid_identifier(args->content))
	{
		error_msg("unset: not a valid identifier\n");
		shell->exit_status = 1;
		*error_flag = 1;
	}
}

void	ft_unset_remove(char ***env, size_t len, char *content)
{
	int	j;

	j = 0;
	while ((*env)[j])
	{
		if (ft_strncmp((*env)[j], content, len) == 0 && (*env)[j][len] == '=')
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
}

void	ft_unset(t_arg *args, char ***env, t_shell *shell)
{
	int		error_flag;
	size_t	len;

	args = args->next;
	error_flag = 0;
	while (args)
	{
		ft_unset_error(args, shell, &error_flag);
		if (error_flag)
		{
			args = args->next;
			continue ;
		}
		len = ft_strlen(args->content);
		ft_unset_remove(env, len, args->content);
		args = args->next;
	}
	if (!error_flag)
		shell->exit_status = 0;
}

