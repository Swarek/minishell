/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 14:48:26 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/31 03:16:49 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(t_arg *arg)
{
	if (ft_strcmp(arg->type, "redir_right") == 0)
		return (1);
	if (ft_strcmp(arg->type, "double_redir_right") == 0)
		return (1);
	if (ft_strcmp(arg->type, "redir_left") == 0)
		return (1);
	if (ft_strcmp(arg->type, "double_redir_left") == 0)
		return (1);
	return (0);
}
