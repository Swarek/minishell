/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 20:59:11 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/18 09:46:01 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_colors(void)
{
	char	**colors;

	colors = malloc(sizeof(char *) * 15);
	if (!colors)
		return (NULL);
	colors[0] = COLOR_BLACK;
	colors[1] = COLOR_RED;
	colors[2] = COLOR_GREEN;
	colors[3] = COLOR_YELLOW;
	colors[4] = COLOR_BLUE;
	colors[5] = COLOR_PURPLE;
	colors[6] = COLOR_CYAN;
	colors[7] = COLOR_WHITE;
	colors[8] = BOLD_COLOR_RED;
	colors[9] = BOLD_COLOR_GREEN;
	colors[10] = BOLD_COLOR_YELLOW;
	colors[11] = BOLD_COLOR_BLUE;
	colors[12] = BOLD_COLOR_PURPLE;
	colors[13] = BOLD_COLOR_CYAN;
	colors[14] = NULL;
	return (colors);
}

static char	*get_colored_prompt(int color)
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
char	*reading_line(int color)
{
	char	*line;
	char	*prompt;

	prompt = get_colored_prompt(color);
	line = readline(prompt);
	if (line && *line)
		add_history(line);
	free(prompt);
	return (line);
}
