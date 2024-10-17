/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:09:52 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/18 01:54:09 by mblanc           ###   ########.fr       */
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
		free(line);
		exec_it(cmds);
		free_cmd(cmds);
		cmds = NULL;
	}
	return (0);
}
