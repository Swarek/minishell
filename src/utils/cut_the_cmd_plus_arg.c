/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_the_cmd_plus_arg.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:11:30 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/24 03:46:59 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Including the cmd
int how_many_args(t_arg *args)
{
    int count;

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

// Démarrer à l'endroit où il y a "command" puis continuer jusqu'à trouver
// un < << > >> ou NULL
int cut_the_cmd_plus_args(t_cmd *cmd)
{
    t_arg *current;
    char **cmd_plus_args;
    int i;

    current = cmd->args;
    cmd_plus_args = malloc(sizeof(char *) * (how_many_args(current) + 1));
    if (cmd_plus_args == NULL)
        return (-1);
    i = 0;
    while (current && ft_strcmp(current->type, "command") != 0)
        current = current->next;
    if (current == NULL)
    {
        free(cmd_plus_args); // Libérer la mémoire allouée
        return (-1);
    }
    while (current && is_redir(current) == 0)
    {
        cmd_plus_args[i++] = current->content;
        current = current->next;
    }
    cmd_plus_args[i] = NULL;
    cmd->cmd_arg_stdin = cmd_plus_args;
    return (0);
}
