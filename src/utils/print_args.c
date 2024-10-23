/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:00:37 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/23 03:15:14 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_args(t_arg *args)
{
	printf("[");
	while (args)
	{
		printf("content : '%s', type : '%s'", args->content, args->type);
		if (args->next)
			printf(", ");
		args = args->next;
	}
	printf("]");
}
