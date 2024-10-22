/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_to_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 00:36:43 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/22 00:56:45 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	type_to_file_in_args2(t_arg *current_arg)
{
	int	i;

	i = 0;
	while (current_arg->content[i])
	{
		if (current_arg->content[i] == '\\' && current_arg->content[i + 1]
			&& (current_arg->content[i + 1] == '|' || current_arg->content[i
				+ 1] == '>'))
			remove_backslashs_in_words3(&(current_arg->content), i);
		else if (current_arg->content[i] == '\\' && current_arg->content[i + 1]
			&& (current_arg->content[i + 1] == '<' || current_arg->content[i
				+ 1] == '&'))
			remove_backslashs_in_words3(&(current_arg->content), i);
		else if (current_arg->content[i] == '\\' && current_arg->content[i + 1]
			&& current_arg->content[i + 1] == ';')
			remove_backslashs_in_words3(&(current_arg->content), i);
		else
			i++;
	}
}

void	type_to_file_in_args1(t_cmd **cmds)
{
	t_cmd	*current_cmd;
	t_arg	*current_arg;
	int		flag;

	flag = 0;
	current_cmd = *cmds;
	while (current_cmd)
	{
		current_arg = current_cmd->args;
		while (current_arg)
		{
			if (ft_strncmp(current_arg->type, "redir_right", 11) == 0)
				flag = 1;
			current_arg = current_arg->next;
			if (flag == 1)
				current_arg->type = "file";
			flag = 0;
		}
		current_cmd = current_cmd->next;
	}
}

