/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impair_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 01:06:59 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/23 01:21:09 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_d.h"

int	error_if_impair_single_quotes(t_cmd **cmds)
{
	t_cmd	*current_cmd;
	t_arg	*current_arg;
	int		nbq;
	int		i;

	nbq = 0;
	current_cmd = *cmds;
	while (current_cmd)
	{
		current_arg = current_cmd->args;
		while (current_arg)
		{
			i = 0;
			while (current_arg->content[i])
			{
				if (current_arg->content[i] == '\''
					&& (ft_strncmp(current_arg->type, "word", 4) == 0 || ft_strncmp(current_arg->type, "single_quoted", 13) == 0))
					nbq++;
				i++;
			}
			current_arg = current_arg->next;
		}
		current_cmd = current_cmd->next;
	}
	if (nbq % 2 != 0)
		return (-1);
	return (0);
}
