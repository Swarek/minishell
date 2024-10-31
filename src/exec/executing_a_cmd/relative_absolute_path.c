/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relative_absolute_path.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:11:50 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/31 07:54:09 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_absolute_or_relative_path(char *command)
{
	if (!command)
		return (0);
	return (command[0] == '/' || (command[0] == '.' && command[1] == '/')
		|| (command[0] == '.' && command[1] == '.' && command[2] == '/'));
}

char	*handle_paths(char *command)
{
	if (access(command, X_OK) == 0)
		return (ft_strdup(command));
	return (NULL);
}
