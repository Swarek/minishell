/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handling.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:37:52 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/31 06:29:05 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_HANDLING_H
# define FT_ERROR_HANDLING_H

# include "libft.h"

void	ft_assert(int condition, const char *msg);
int		error_msg(const char *msg);

#endif