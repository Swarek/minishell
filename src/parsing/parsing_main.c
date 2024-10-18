/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:34:51 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/18 01:47:51 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_special_char(char *str, int i, t_arg **current_args)
{
    if (str[i] == '\'' || str[i] == '\"')
        return(save_it_quoted(str, i, current_args) + 1);
    else if (str[i] == ';')
        return (save_it_semicolon(i, current_args) + 1);
    else if (str[i] == '>')
        return (save_it_redir_right(str, i, current_args) + 1);
    else if (str[i] == '<')
        return(save_it_redir_left(i, current_args) + 1);
    else
        return(save_it_word(str, i, current_args) + 1);
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
                return (-1);
        }
    }
    add_command(cmds, current_args);
    return (i);
}

int parse_it(char *str, t_cmd **cmds)
{
	t_arg	*current_args;
	int		i;

	current_args = NULL;
	i = 0;
	while (str[i])
	{
		i = parse_one_command(str, i, &current_args, cmds);
		if (i == -1)
			return (-1);
		if (str[i] == '|')
		{
			add_arg(&current_args, create_arg("|", "pipe"));
			i++;
		}
	}
	return 0;
}
