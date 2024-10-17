/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 20:59:11 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/17 21:32:35 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_colored_prompt(void)
{
	char	cwd[PATH_MAX];
	char	*current_dir;
	char	*colored_prompt;
	char	*prompt;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		current_dir = strrchr(cwd, '/');
		if (current_dir != NULL)
			current_dir++;
		else
			current_dir = cwd;
		colored_prompt = ft_strjoin(COLOR_GREEN, current_dir);
		prompt = ft_strjoin(colored_prompt, COLOR_PURPLE);
		free(colored_prompt);
		colored_prompt = ft_strjoin(prompt, " minishell> ");
		free(prompt);
		prompt = ft_strjoin(colored_prompt, RESET_COLOR);
		free(colored_prompt);
	}
	else
		prompt = ft_strdup("minishell> ");
	return (prompt);
}

// Main function to read the line
char	*reading_line(void)
{
	char	*line;
	char	*prompt;

	prompt = get_colored_prompt();
	line = readline(prompt);
	free(prompt);
	return (line);
}
