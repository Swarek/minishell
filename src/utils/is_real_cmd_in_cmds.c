/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_real_cmd_in_cmds.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 07:09:10 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/29 07:09:54 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_real_cmd_in_cmds(t_cmd *cmds)
{
	t_arg	*arg;

	while (cmds)
	{
		arg = cmds->args;
		while (arg)
		{
			if (ft_strcmp(arg->type, "command") == 0)
				return (1);
			arg = arg->next;
		}
		cmds = cmds->next;
	}
	return (0);
}
