/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_args_for_export.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:37:44 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/27 18:58:00 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Carrement creer un nouveau t_arg ca sera plus simple.
// void	edit_args_for_export(t_arg *args)
// {
// 	while (args && args->next)
// 	{
// 		if (ft_strcmp(args->next->type, "double_quoted") == 0
// 			|| ft_strcmp(args->next->type, "single_quoted") == 0)
// 			args->content = ft_strjoin(args->content, args->next->content);
// 		args = args->next;
// 	}
// }

void	edit_args_for_export(t_arg *args)
{
	t_arg	*tmp;

	while (args && args->next)
	{
		if (ft_strcmp(args->next->type, "double_quoted") == 0
			|| ft_strcmp(args->next->type, "single_quoted") == 0)
		{
			tmp = args->next;
			args->content = ft_strjoin(args->content, tmp->content);
			args->next = tmp->next;
			free(tmp->content);
			free(tmp);
		}
		else
			args = args->next;
	}
}
