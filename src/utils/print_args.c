/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:00:37 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/31 13:46:04 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_args(t_arg *args)
{
	ft_printf("[");
	while (args)
	{
		ft_printf("content : '%s', type : '%s'", args->content, args->type);
		if (args->next)
			ft_printf(", ");
		args = args->next;
	}
	ft_printf("]");
}
