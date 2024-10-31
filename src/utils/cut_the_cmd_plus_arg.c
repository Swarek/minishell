/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_the_cmd_plus_arg.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:11:30 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/31 03:17:07 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_arguments_for_t_arg(t_arg *args)
{
	int	count;

	count = 0;
	while (args)
	{
		count++;
		args = args->next;
	}
	return (count);
}

// Including the cmd
int	how_many_args(t_arg *args)
{
	int	count;

	count = 0;
	while (args && ft_strcmp(args->type, "command") != 0)
		args = args->next;
	if (args == NULL)
		return (0);
	while (args && is_redir(args) == 0)
	{
		count++;
		args = args->next;
	}
	return (count);
}

int	fill_cmd_plus_args(t_arg **current, char **cmd_plus_args)
{
	int	i;

	i = 0;
	while (*current && is_redir(*current) == 0)
	{
		cmd_plus_args[i] = ft_strdup((*current)->content);
		if (!cmd_plus_args[i])
		{
			while (--i >= 0)
				free(cmd_plus_args[i]);
			return (-1);
		}
		i++;
		*current = (*current)->next;
	}
	cmd_plus_args[i] = NULL;
	return (0);
}

int	cut_the_cmd_plus_args(t_cmd *cmd)
{
	t_arg	*current;
	char	**cmd_plus_args;

	current = cmd->args;
	cmd_plus_args = malloc(sizeof(char *) * (how_many_args(current) + 1));
	if (!cmd_plus_args)
		return (-1);
	while (current && ft_strcmp(current->type, "command") != 0)
		current = current->next;
	if (!current)
	{
		free(cmd_plus_args);
		return (-1);
	}
	if (fill_cmd_plus_args(&current, cmd_plus_args) == -1)
	{
		free(cmd_plus_args);
		return (-1);
	}
	cmd->cmd_arg_stdin = cmd_plus_args;
	return (0);
}
