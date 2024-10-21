/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 01:43:02 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/21 02:36:24 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_d.h"
#include <stdio.h>

void	remove_backslashs_in_words3(char **str, int index)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(*str);
	new_str = malloc(len);
	if (!new_str)
		return ;
	ft_strlcpy(new_str, *str, index + 1);
	ft_strlcpy(new_str + index, *str + index + 1, len - index);
	free(*str);
	*str = new_str;
}

void	remove_backslashs_in_words2(t_arg *current_arg)
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

void	remove_backslashs_in_words(t_cmd **cmds)
{
	t_cmd	*current_cmd;
	t_arg	*current_arg;

	current_cmd = *cmds;
	while (current_cmd)
	{
		current_arg = current_cmd->args;
		while (current_arg)
		{
			if (ft_strncmp(current_arg->type, "word", 4) == 0)
				remove_backslashs_in_words2(current_arg);
			current_arg = current_arg->next;
		}
		current_cmd = current_cmd->next;
	}
}
