/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_counter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:39:41 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/20 22:25:50 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipe(t_cmd *cmd)
{
	int	nbr_pipe;

	nbr_pipe = 0;
	while (cmd && ft_strcmp(cmd->args->type, "semicolon") == 0)
		cmd = cmd->next;
	{
		if (ft_strcmp(cmd->args->type, "pipe") == 0)
			nbr_pipe++;
		cmd = cmd->next;
	}
	return (nbr_pipe);
}
