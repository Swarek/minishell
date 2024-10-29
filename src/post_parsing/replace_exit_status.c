/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_exit_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 02:09:57 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/29 01:57:46 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_exit_status(t_arg *current_arg, int *i, t_shell *shell)
{
	char	*status_str;
	char	*new_str;
	size_t	old_len;
	size_t	new_len;

	status_str = ft_itoa(shell->exit_status);
	if (!status_str)
		return ;
	old_len = ft_strlen(current_arg->content);
	new_len = old_len - 2 + ft_strlen(status_str);
	new_str = malloc(new_len + 1);
	if (!new_str)
	{
		free(status_str);
		return ;
	}
	ft_strlcpy(new_str, current_arg->content, *i + 1);
	ft_strlcpy(new_str + *i, status_str, ft_strlen(status_str) + 1);
	ft_strlcpy(new_str + *i + ft_strlen(status_str), current_arg->content + *i
		+ 2, old_len - *i - 1);
	*i += ft_strlen(status_str) - 1;
	free(current_arg->content);
	free(status_str);
	current_arg->content = new_str;
}

void	replace_exit_status(t_arg *current_arg, int dolls, t_shell *shell)
{
	int	i;

	if (!current_arg->content)
		return ;
	i = 0;
	while (current_arg->content[i])
	{
		if (current_arg->content[i++] == '$')
			dolls++;
	}
	while (dolls > 0)
	{
		i = 0;
		while (current_arg->content && current_arg->content[i])
		{
			if (current_arg->content[i] == '$' && current_arg->content[i
					+ 1] == '?')
			{
				process_exit_status(current_arg, &i, shell);
				dolls--;
			}
			else
				i++;
		}
	}
}

void	replace_exit_status_in_cmds_tab(t_cmd **cmds, t_shell *shell)
{
	t_cmd	*current_cmd;
	t_arg	*current_arg;

	current_cmd = *cmds;
	while (current_cmd)
	{
		current_arg = current_cmd->args;
		while (current_arg)
		{
			if (ft_strncmp(current_arg->type, "word", 4) == 0
				|| ft_strncmp(current_arg->type, "double_quoted", 13) == 0)
				replace_exit_status(current_arg, 0, shell);
			current_arg = current_arg->next;
		}
		current_cmd = current_cmd->next;
	}
}
