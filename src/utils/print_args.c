/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:00:37 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/20 11:40:31 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_args(t_arg *args)
{
	printf("[");
	while (args)
	{
		printf("%s", args->content);
		if (args->next)
			printf(", ");
		args = args->next;
	}
	printf("]");
}
