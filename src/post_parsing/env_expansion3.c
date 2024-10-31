/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:32:31 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/31 13:32:45 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_empty_var_env(t_arg *curr_arg, int *i, int start)
{
	curr_arg->content[*i] = '$';
	*i = start;
}

void	handle_nonexistent_var(t_arg *curr_arg, int *i, int j)
{
	replace_env_var(curr_arg, *i, j, "");
	*i = *i;
}

void	handle_existing_var(t_arg *curr_arg, int *i, int j,
		const char *env_value)
{
	replace_env_var(curr_arg, *i, j, env_value);
	*i += ft_strlen(env_value) - 1;
}
