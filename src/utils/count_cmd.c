/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:44:54 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/19 22:46:12 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmd(t_cmd *cmd)
{
	int	nbr_cmd;

	nbr_cmd = 0;
	while (cmd)
	{
		if (ft_strcmp(cmd->args->type, "command") == 0)
			nbr_cmd++;
		cmd = cmd->next;
	}
	return (nbr_cmd);
}
