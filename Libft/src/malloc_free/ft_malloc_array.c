/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:10:02 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/31 06:26:59 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_malloc_array(size_t count, size_t element_size)
{
	void	**array;

	array = malloc(count * element_size);
	if (!array)
	{
		error_msg("Error: array malloc failed\n");
		exit(EXIT_FAILURE);
	}
	return (array);
}
