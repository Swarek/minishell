/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:32:54 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/18 10:01:58 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int	error_msg(const char *msg)
// {
// 	if (msg)
// 	{
// 		write(2, BOLD_COLOR_RED, 8);
// 		write(2, "Error\n", 6);
// 		while (*msg)
// 		{
// 			write(2, msg, 1);
// 			msg++;
// 		}
// 		write(2, RESET_COLOR, 4);
// 	}
// 	return (-1);
// }

int	error_msg(const char *msg)
{
    write(2, "minishell: ", 11);
    write(2, msg, ft_strlen(msg));
	return (0);
}
