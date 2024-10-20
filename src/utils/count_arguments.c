/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:48:04 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/20 19:14:39 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This function counts the number of arguments, including the cmd
int	count_arguments(char **args)
{
	int	nbr_args;

	nbr_args = 0;
	while (args[nbr_args])
		nbr_args++;
	return (nbr_args);
}
