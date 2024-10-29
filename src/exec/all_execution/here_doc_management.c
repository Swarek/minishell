/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 04:54:57 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/29 01:30:13 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	write_to_temp(int fd, char *line)
{
	if (write(fd, line, ft_strlen(line)) == -1)
		return (error_msg("Problem writing to temp.txt"),
			free(line), close(fd), -1);
	if (write(fd, "\n", 1) == -1)
		return (error_msg("Problem writing newline to temp.txt"),
			free(line), close(fd), -1);
	return (0);
}

int	here_doc_management(char *limiter)
{
	int		fd;
	char	*line;
	size_t	len;

	fd = open("temp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (error_msg("Problem opening temp.txt"));
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			break ;
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (ft_strcmp(line, limiter) == 0 || len == 0)
			break ;
		if (write_to_temp(fd, line) == -1)
			return (-1);
		free(line);
	}
	free(line);
	close(fd);
	return (0);
}
