/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:00:37 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/18 20:00:50 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_args(t_arg *args)
{
	while (args)
	{
		ft_printf("Content : %s, Type : %s\n", args->content, args->type);
		args = args->next;
	}
}
