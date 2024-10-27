/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 19:03:54 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/27 19:06:34 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmd(t_cmd *cmd)
{
	int		nbr_cmd;
	t_arg	*arg;

	nbr_cmd = 0;
	while (cmd)
	{
		arg = cmd->args;
		while (arg)
		{
			if (ft_strcmp(arg->type, "command") == 0)
			{
				nbr_cmd++;
				break ;
			}
			arg = arg->next;
		}
		cmd = cmd->next;
	}
	return (nbr_cmd);
}
