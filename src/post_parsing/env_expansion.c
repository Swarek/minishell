/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 14:20:04 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/28 21:08:24 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_env_var(t_arg *current_arg, int start, int end,
		const char *value)
{
	size_t	old_len;
	size_t	val_len;
	size_t	new_len;
	char	*new_str;

	old_len = ft_strlen(current_arg->content);
	val_len = ft_strlen(value);
	new_len = old_len - (end - start) + val_len;
	new_str = malloc(new_len + 1);
	if (!new_str)
		return ;
	ft_strlcpy(new_str, current_arg->content, start + 1);
	ft_strlcpy(new_str + start, value, val_len + 1);
	ft_strlcpy(new_str + start + val_len, current_arg->content + end, old_len
		- end + 1);
	free(current_arg->content);
	current_arg->content = new_str;
}

void	process_env_var(t_arg *current_arg, int *i)
{
	int			start;
	int			j;
	char		*status_str;
	char		var_name[512];
	const char	*env_value;

	start = *i + 1;
	if (!current_arg->content[start])
	{
		*i = start;
		return ;
	}
	if (current_arg->content[start] == '?')
	{
		status_str = ft_itoa(g_last_exit_status);
		if (!status_str)
			return ;
		replace_env_var(current_arg, *i, start + 1, status_str);
		*i += ft_strlen(status_str) - 1;
		free(status_str);
		return ;
	}
	j = start;
	while (current_arg->content[j] && (current_arg->content[j] == '_'
			|| (current_arg->content[j] >= 'a'
				&& current_arg->content[j] <= 'z')
			|| (current_arg->content[j] >= 'A'
				&& current_arg->content[j] <= 'Z')
			|| (current_arg->content[j] >= '0'
				&& current_arg->content[j] <= '9')))
		j++;
	if (j == start)
	{
		*i = start;
		return ;
	}
	ft_strlcpy(var_name, current_arg->content + start, j - start + 1);
	env_value = getenv(var_name);
	if (env_value)
	{
		replace_env_var(current_arg, *i, j, env_value);
		*i += ft_strlen(env_value) - 1;
	}
	else
		*i = j - 1;
}

void	expand_env_vars(t_arg *current_arg)
{
	int	i;

	i = 0;
	if (!current_arg->content)
		return ;
	while (current_arg->content[i])
	{
		if (current_arg->content[i] == '$' && current_arg->content[i + 1]
			&& (current_arg->content[i + 1] == '?' || current_arg->content[i
				+ 1] == '_' || ft_isalnum(current_arg->content[i + 1])))
		{
			process_env_var(current_arg, &i);
		}
		else
		{
			i++;
		}
	}
}

void	expand_env_vars_in_cmds_tab(t_cmd **cmds)
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
				expand_env_vars(current_arg);
			current_arg = current_arg->next;
		}
		current_cmd = current_cmd->next;
	}
}
