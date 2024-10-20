/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_add_add_type_cmd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 11:34:35 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/20 15:09:11 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_and_add_type_cmd(t_arg *args, char **envp)
{
	t_arg	*tmp;

	tmp = args;
	while (tmp)
	{
		if (is_built_in(tmp) == 1)
			args->type = "command";
		else if (is_absolute_or_relative_path(tmp->content))
		{
			if (handle_absolute_or_relative_path(tmp->content) != NULL)
				args->type = "command";
		}
		else if (find_command_path(tmp->content, envp) != NULL)
			args->type = "command";
		tmp = tmp->next;
	}
}
