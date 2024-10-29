/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 20:59:11 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/30 00:44:10 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_colors(void)
{
	char	**colors;

	colors = malloc(sizeof(char *) * 15);
	if (!colors)
		return (NULL);
	colors[0] = BOLD_COLOR_BLUE;
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
	colors[11] = COLOR_BLACK;
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
	char	**colors;

	colors = init_colors();
	if (!colors)
		return (NULL);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		current_dir = ft_strrchr(cwd, '/');
		if (current_dir != NULL)
			current_dir++;
		else
			current_dir = cwd;
		colored_prompt = ft_strjoin(colors[color % 14], current_dir);
		prompt = ft_strjoin(colored_prompt, " minishell> ");
		free(colored_prompt);
		colored_prompt = ft_strjoin(prompt, RESET_COLOR);
		free(prompt);
	}
	else
		colored_prompt = ft_strdup("minishell>");
	return (free(colors), colored_prompt);
}

char	*reading_line(int color)
{
	char	*line;
	char	*prompt;

	if (g_received_signal == 2 && rl_line_buffer == NULL)
	{
		line = readline("");
		g_received_signal = 0;
	}
	else
	{
		prompt = get_colored_prompt(color);
		line = readline(prompt);
		free(prompt);
		g_received_signal = 0;
	}
	if (line && *line)
		add_history(line);
	return (line);
}
