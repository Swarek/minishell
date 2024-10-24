/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:57:08 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/24 03:52:16 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_args(t_arg *args)
{
    t_arg *current_arg;
    t_arg *next_arg;

    current_arg = args;
    while (current_arg)
    {
        next_arg = current_arg->next;
        ft_safe_free((void**)&(current_arg->content));
        if (current_arg->type && 
            (strcmp(current_arg->type, "command") != 0 &&
             strcmp(current_arg->type, "file") != 0 &&
             strcmp(current_arg->type, "redir_right") != 0 &&
             strcmp(current_arg->type, "double_redir_right") != 0 &&
             strcmp(current_arg->type, "redir_left") != 0 &&
             strcmp(current_arg->type, "double_redir_left") != 0 &&
             strcmp(current_arg->type, "here_doc") != 0 &&
             strcmp(current_arg->type, "pipe") != 0 &&
             strcmp(current_arg->type, "semicolon") != 0))
        {
            ft_safe_free((void**)&(current_arg->type));
        }
        ft_safe_free((void**)&current_arg); // Free the t_arg node
        current_arg = next_arg;
    }
}

void safe_free_cmds(t_cmd *cmds)
{
    t_cmd *current_cmd;
    t_cmd *next_cmd;

    current_cmd = cmds;
    while (current_cmd)
    {
        next_cmd = current_cmd->next;
        if (current_cmd->args)
            free_args(current_cmd->args);
        if (current_cmd->cmd_arg_stdin)
            safe_free_all_strings(&(current_cmd->cmd_arg_stdin));
        ft_safe_free((void**)&current_cmd);
        current_cmd = next_cmd;
    }
}

void free_pipes(int **pipes, int nbr_pipes)
{
    int i;

    if (!pipes)
        return;
    for (i = 0; i < nbr_pipes; i++)
    {
        ft_safe_free((void**)&(pipes[i]));
    }
    ft_safe_free((void**)&pipes);
}

void clean_all(t_shell *shell)
{
    if (!shell)
        return;
    if (shell->envp)
        safe_free_all_strings(&(shell->envp));
    if (shell->cmds)
        safe_free_cmds(shell->cmds);
    if (shell->pipes)
        free_pipes(shell->pipes, shell->nbr_pipes);
    ft_safe_free((void**)&(shell->child_pids));
    ft_safe_free((void**)&shell);
}
