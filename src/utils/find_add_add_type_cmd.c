/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_add_add_type_cmd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 11:34:35 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/24 05:05:27 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void find_arg_add_type_cmd(t_shell *shell, t_arg *args)
{
    t_arg *tmp;
    char *path;

    tmp = args;
    while (tmp)
    {
        if (strcmp(tmp->type, "file") == 0)
        {
            tmp = tmp->next;
            continue;
        }
        if (is_built_in_t_args(tmp) == 1)
        {
            tmp->type = "command";
        }
        else if (is_absolute_or_relative_path(tmp->content))
        {
            path = handle_absolute_or_relative_path(tmp->content);
            if (path != NULL)
            {
                tmp->type = "command";
                free(path);
            }
        }
        else
        {
            path = find_command_path(shell, tmp->content, shell->envp);
            if (path != NULL)
            {
                tmp->type = "command";
                free(path); // Libérer la chaîne allouée
            }
			else
            {
                if (path)
                    free(path);
			}
        }
        tmp = tmp->next;
    }
}


