/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:53:02 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/30 19:14:38 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_special_char(char *str, int i, t_arg **current_args)
{
	if (str[i] == '\'')
		return (save_it_single_quoted(str, i, current_args) + 1);
	if (str[i] == '"')
		return (save_it_double_quoted(str, i, current_args) + 1);
	else if (str[i] == '>')
		return (save_it_redir_right(str, i, current_args) + 1);
	else if (str[i] == '<')
		return (save_it_redir_left(str, i, current_args) + 1);
	else
		return (save_it_word(str, i, current_args) + 1);
}

int	parse_one_command(char *str, int i, t_arg **current_args, t_cmd **cmds)
{
	while (str[i] && str[i] != '|')
	{
		if (str[i] == ' ' || str[i] == '\t')
			i++;
		else
		{
			i = handle_special_char(str, i, current_args);
			if (i == -1)
				return (ft_printf("Odd number of quotes\n"), -1);
		}
	}
	add_command(cmds, current_args);
	return (i);
}

int	parse_it_2(char *str, t_cmd **cmds, int i, t_arg **current_args)
{
	t_arg	*pipe_arg;

	while (str[i])
	{
		i = parse_one_command(str, i, current_args, cmds);
		if (i == -1)
			return (-1);
		if (str[i] == '|')
		{
			*current_args = NULL;
			if (str[i + 1] == '|')
			{
				pipe_arg = create_arg("more-than_one_pipe", "error");
				if (!pipe_arg)
					return (-1);
				add_arg(current_args, pipe_arg);
				add_command(cmds, current_args);
				while (str[i] == '|')
					i++;
			}
			else
			{
				pipe_arg = create_arg("|", "pipe");
				if (!pipe_arg)
					return (-1);
				add_arg(current_args, pipe_arg);
				add_command(cmds, current_args);
				i++;
			}
		}
	}
	return (0);
}

int	parse_it(char *str, t_cmd **cmds)
{
	t_arg	*current_args;
	int		i;
	int		ret;

	current_args = NULL;
	i = 0;
	if (precheck(str) == 1)
		return (ft_printf("Error with parentheses\n"), -1);
	if (precheck(str) == 2)
		return (ft_printf("Error with pipe position\n"), -1);
	if (precheck(str) == 3)
		return (ft_printf("Incorrect filename\n"), -1);
	ret = parse_it_2(str, cmds, i, &current_args);
	// Si current_args contient encore des éléments non ajoutés à une commande
	if (current_args)
		free_args(current_args);
	return (ret);
}
