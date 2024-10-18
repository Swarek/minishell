/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:34:51 by dmathis           #+#    #+#             */
/*   Updated: 2024/09/14 15:51:56 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_d.h"

int handle_special_char(char *str, int i, t_arg **current_args)
{
    if (str[i] == '\'' || str[i] == '\"')
        return(save_it_quoted(str, i, current_args) + 1);
    else if (str[i] == ';')
        return (save_it_semicolon(i, current_args) + 1);
    else
        return(save_it_word(str, i, current_args) + 1);
}

int parse_one_command(char *str, int i, t_arg **current_args, t_cmd **cmds)
{
    while (str[i] && str[i] != '|' && str[i] != '>' && str[i] != '<')
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
    t_arg 	*current_args;
    int 	i;
    
	current_args = NULL;
	i = 0;
    while (str[i])
	{
        i = parse_one_command(str, i, &current_args, cmds);
        if (i == -1)
            return -1;
        if (str[i] == '|')
        {
            add_arg(&current_args, create_arg("|", "pipe"));
            add_command(cmds, &current_args);
            i++;
        }
        else if (str[i] == '>' && str[i + 1] =='>')
        {
            add_arg(&current_args, create_arg(">>", "double_redir_right"));
            add_command(cmds, &current_args);
            i = i + 2;
        }
        else if (str[i] == '>')
        {
            add_arg(&current_args, create_arg(">", "redir_right"));
            add_command(cmds, &current_args);
            i++;
        }
        else if (str[i] == '<')
        {
            add_arg(&current_args, create_arg("<", "redir_left"));
            add_command(cmds, &current_args);
            i++;
        }
	}
    return 0;
}