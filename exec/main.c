/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:09:52 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/17 22:54:35 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_m.h"

int	exec_it(t_cmd *cmds)
{
	(void)cmds;
	return(0);
}

int	test_minishell()
{
	char	*line;
	t_cmd	*cmds;

	cmds = NULL;
	while (1)
	{
		line = reading_line();
		ft_printf("Here is the line : %s\n", line);
		if (parse_it(line, &cmds) != 0)
			return (free(line), -1);
		free(line);
		exec_it(cmds);
	}
	return (0);
}

// int	main(void)
// {
// 	return (test_minishell());
// }