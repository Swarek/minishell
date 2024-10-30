/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_to_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 00:36:43 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/30 23:31:36 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	type_to_file_in_args1(t_cmd **cmds)
{
	t_cmd	*current_cmd;
	t_arg	*current_arg;

	current_cmd = *cmds;
	while (current_cmd)
	{
		current_arg = current_cmd->args;
		while (current_arg)
		{
			if (ft_strncmp(current_arg->type, "redir_right", 11) == 0
				|| ft_strncmp(current_arg->type, "double_redir_right", 18) == 0
				|| ft_strncmp(current_arg->type, "redir_left", 10) == 0
				|| ft_strncmp(current_arg->type, "double_redir_left", 17) == 0)
			{
				if (current_arg->next)
					current_arg->next->type = "file";
			}
			current_arg = current_arg->next;
		}
		current_cmd = current_cmd->next;
	}
}
