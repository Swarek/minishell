/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_args_for_export.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:37:44 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/30 19:22:39 by dmathis          ###   ########.fr       */
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
	char	*new_content;

	while (args && args->next)
	{
		if (ft_strcmp(args->next->type, "double_quoted") == 0
			|| ft_strcmp(args->next->type, "single_quoted") == 0)
		{
			tmp = args->next;
			new_content = ft_strjoin(args->content, tmp->content);
			if (new_content) // Si le join a réussi
			{
				free(args->content); // On libère l'ancien content
				args->content = new_content;
				args->next = tmp->next;
				free(tmp->content);
				free(tmp);
			}
			else
				args = args->next; // En cas d'échec, on continue
		}
		else
			args = args->next;
	}
}
