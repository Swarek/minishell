/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 01:53:59 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/29 02:02:09 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_char_for_env(char c)
{
	if (c == '_')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	handle_exit_status_for_env(t_arg *current_arg, int *i, t_shell shell)
{
	char	*status_str;
	int		start;

	start = *i + 1;
	status_str = ft_itoa(shell.last_exit_status);
	if (!status_str)
		return ;
	replace_env_var(current_arg, *i, start + 1, status_str);
	*i += ft_strlen(status_str) - 1;
	free(status_str);
}

int	get_var_name_end_env(const char *content, int start)
{
	int	j;

	j = start;
	while (content[j] && is_valid_char_for_env(content[j]))
		j++;
	return (j);
}

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
