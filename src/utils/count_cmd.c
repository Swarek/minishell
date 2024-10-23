/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:44:54 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/23 05:04:28 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmd(t_cmd *cmd)
{
	int	nbr_cmd;
	t_arg	*tmp;

	nbr_cmd = 0;
	while (cmd)
	{
		tmp = cmd->args;
		while (tmp != NULL)
		{
			if (ft_strcmp(tmp->type, "command") == 0)
			{
				nbr_cmd++;
				break ;
			}
			tmp = tmp->next;
		}
		cmd = cmd->next;
	}
	return (nbr_cmd);
}
