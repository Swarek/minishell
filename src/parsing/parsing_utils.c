/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 02:33:25 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/28 20:38:50 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arg	*create_arg(char *content, const char *type)
{
	t_arg	*new;

	new = malloc(sizeof(t_arg));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	if (!new->content)
	{
		free(new);
		return (NULL);
	}
	if (ft_strcmp(type, "word") == 0 || ft_strcmp(type, "pipe") == 0
		|| ft_strcmp(type, "command") == 0 || ft_strcmp(type, "file") == 0
		|| ft_strcmp(type, "redir_right") == 0 || ft_strcmp(type,
			"redir_left") == 0)
		new->type = (char *)type;
	else
		new->type = ft_strdup(type);
	new->next = NULL;
	return (new);
}

void	add_arg(t_arg **head, t_arg *new_arg)
{
	t_arg	*current;

	if (!*head)
	{
		*head = new_arg;
	}
	else
	{
		current = *head;
		while (current->next)
		{
			current = current->next;
		}
		current->next = new_arg;
	}
}

void	add_command(t_cmd **cmds, t_arg **current_args)
{
	t_cmd	*new_cmd;
	t_cmd	*last_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	new_cmd->args = *current_args;
	new_cmd->next = NULL;
	if (!*cmds)
		*cmds = new_cmd;
	else
	{
		last_cmd = *cmds;
		while (last_cmd->next)
			last_cmd = last_cmd->next;
		last_cmd->next = new_cmd;
	}
	*current_args = NULL;
}
