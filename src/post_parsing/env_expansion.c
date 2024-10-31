/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 14:20:04 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/31 13:01:01 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_empty_var_env(t_arg *curr_arg, int *i, int start)
{
	curr_arg->content[*i] = '$';
	*i = start;
}

void	handle_nonexistent_var(t_arg *curr_arg, int *i, int j)
{
	replace_env_var(curr_arg, *i, j, "");
	*i = *i; // On ne décrémente plus l'index
}

void	handle_existing_var(t_arg *curr_arg, int *i, int j,
		const char *env_value)
{
	replace_env_var(curr_arg, *i, j, env_value);
	*i += ft_strlen(env_value) - 1;
}

void	process_standard_var_env(t_arg *curr_arg, int *i, int start, t_shell *s)
{
	char		var_name[512];
	const char	*env_value;
	int			j;

	if (!curr_arg->content[start] || curr_arg->content[start] == ' ')
	{
		handle_empty_var_env(curr_arg, i, start);
		return ;
	}
	j = get_var_name_end_env(curr_arg->content, start);
	if (j == start)
	{
		*i = start;
		return ;
	}
	ft_strlcpy(var_name, curr_arg->content + start, j - start + 1);
	env_value = ft_getenv(s->envp, var_name);
	if (env_value)
		handle_existing_var(curr_arg, i, j, env_value);
	else
		handle_nonexistent_var(curr_arg, i, j);
}

void	process_env_var(t_arg *current_arg, int *i, t_shell shell)
{
	int	start;

	start = *i + 1;
	if (!current_arg->content[start])
	{
		*i = start;
		return ;
	}
	if (current_arg->content[start] == '?')
	{
		handle_exit_status_for_env(current_arg, i, shell);
		return ;
	}
	process_standard_var_env(current_arg, i, start, &shell);
}

void	expand_env_vars(t_arg *current_arg, t_shell shell)
{
	int	i;

	i = 0;
	if (!current_arg->content)
		return ;
	while (current_arg->content[i])
	{
		if (current_arg->content[i] == '$' && (!current_arg->content[i + 1]
				|| current_arg->content[i + 1] == ' '))
		{
			i++;
			continue ;
		}
		else if (current_arg->content[i] == '$' && current_arg->content[i + 1]
			&& (current_arg->content[i + 1] == '?' || current_arg->content[i
				+ 1] == '_' || ft_isalnum(current_arg->content[i + 1])))
			process_env_var(current_arg, &i, shell);
		else
			i++;
	}
}

void	expand_env_vars_in_cmds_tab(t_cmd **cmds, t_shell shell)
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
				expand_env_vars(current_arg, shell);
			current_arg = current_arg->next;
		}
		current_cmd = current_cmd->next;
	}
}
