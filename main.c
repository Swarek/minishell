/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:09:52 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/17 23:17:47 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	t_cmd	*cmds;

	cmds = NULL;
	while (1)
	{
		line = reading_line();
		// ft_printf("Here is the line : %s\n", line);
		if (parse_it(line, &cmds) != 0)
			return (free(line), -1);
		// ft_printf("Here is the command : %s\n", cmds->args->content);
		// if (cmds->args->next != NULL)
		// 	ft_printf("And the arg : %s\n", cmds->args->next->content);
		free(line);
		exec_it(cmds);
	}
	return (0);
}
