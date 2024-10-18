/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_args_to_argv.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:52:48 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/18 10:56:42 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**convert_args_to_argv(t_arg *args)
{
	char	**argv;
	int		i;
	int		arg_count;

	arg_count = count_arguments(args);
	argv = malloc((arg_count + 1) * sizeof(char *));
	if (!argv)
		return (NULL);
	i = 0;
	while (args)
	{
		argv[i] = args->content;
		args = args->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}
