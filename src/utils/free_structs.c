/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 00:41:46 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/18 01:52:18 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_args(t_arg *args)
{
	t_arg	*tmp;

	while (args)
	{
		tmp = args;
		args = args->next;
		free(tmp->content);
		free(tmp->type);
		free(tmp);
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd;
		free_args(cmd->args);
		cmd = cmd->next;
		free(tmp);
	}
}
