#include "minishell.h"

t_arg *create_arg(char *content, char *type)
{
    t_arg *new = malloc(sizeof(t_arg));
    if (!new) return NULL;
    new->content = ft_strdup(content);
    new->type = ft_strdup(type);
    new->next = NULL;
    return new;
}

void add_arg(t_arg **head, t_arg *new_arg)
{    
    if (!*head)
    {
        *head = new_arg;
    }
    else
    {
        t_arg *current = *head;
        while (current->next) {
            current = current->next;
        }
        current->next = new_arg;
    }
}

void free_cmds(t_cmd *cmds)
{
    while (cmds) {
        t_cmd *next_cmd = cmds->next;
        t_arg *args = cmds->args;
        while (args) {
            t_arg *next_arg = args->next;
            free(args->content);
            free(args->type);
            free(args);
            args = next_arg;
        }
        free(cmds);
        cmds = next_cmd;
    }
}

void add_command(t_cmd **cmds, t_arg **current_args) 
{
    t_cmd *new_cmd = malloc(sizeof(t_cmd));
    new_cmd->args = *current_args;
    new_cmd->next = NULL;
    
    if (!*cmds) {
        *cmds = new_cmd;
    } else {
        t_cmd *last_cmd = *cmds;
        while (last_cmd->next) last_cmd = last_cmd->next;
        last_cmd->next = new_cmd;
    }
    *current_args = NULL;
}
