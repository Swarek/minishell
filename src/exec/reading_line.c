/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 20:59:11 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/31 03:21:29 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_colors(void)
{
	char	**colors;

	colors = malloc(sizeof(char *) * 14);
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
	colors[11] = BOLD_COLOR_PURPLE;
	colors[12] = BOLD_COLOR_CYAN;
	colors[13] = NULL;
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
	char			*line;
	char			*prompt;
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	if (g_received_signal == SIGINT && !(term.c_lflag & ICANON))
	{
		line = readline("");
	}
	else
	{
		prompt = get_colored_prompt(color);
		line = readline(prompt);
		free(prompt);
	}
	if (line && *line)
		add_history(line);
	return (line);
}
