/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:09:52 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/18 09:40:49 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Test Damien
// int	main(void)
// {
// 	void;
// }

// Test main Mathis

// int main(void)
// {
// 	// Initialisation des commandes
// 	t_cmd *cmds = NULL;
// 	t_arg *current_args = NULL;

// 	// Test : Commande avec pipe "echo hello | grep h"

// 	// Première commande : "echo hello"
// 	add_arg(&current_args, create_arg("cd" "~"));  // Commande
// 	// add_arg(&current_args, create_arg("hello", "arg"));     // Argument
// 	add_command(&cmds, &current_args);                     // Ajouter la commande à la liste

// 	// Commande intermédiaire : "|"
// 	add_arg(&current_args, create_arg("|", "pipe"));        // Le pipe
// 	add_command(&cmds, &current_args);                     // Ajouter le pipe à la liste

// 	// Deuxième commande : "grep h"
// 	add_arg(&current_args, create_arg("grep", "command"));  // Commande
// 	add_arg(&current_args, create_arg("h", "arg"));         // Argument
// 	add_command(&cmds, &current_args);                     // Ajouter la commande à la liste

// 	// Appeler ta fonction exec_it
// 	exec_it(cmds);

// 	// Libérer la mémoire
// 	free_cmds(cmds);
// 	return 0;
// }

int	main(void)
{
	char	*line;
	t_cmd	*cmds;
	int		color;

	cmds = NULL;
	color = 0;
	while (1)
	{
		line = reading_line(color);
		// ft_printf("Here is the line : %s\n", line);
		if (parse_it(line, &cmds) != 0)
			return (free(line), -1);
		free(line);
		exec_it(cmds);
		free_cmd(cmds);
		cmds = NULL;
		color++;
	}
	return (0);
}
