/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 06:28:11 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/20 06:31:00 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Le but ici est de parcourir toutes les commandes et de verifier si il y a des here_doc
// On les executera tous et on creera un fichier temporaire pour chacun
// On remplacera le arg du here_doc qui dit le nom du EOF par le nom du fichier temporaire
// Ensuite a voir si on stock dans un tableau les noms des fichiers temporaires pour les supprimer a la fin
// Ou si juste pour les supprimer a la fin on parcours les commandes et on supprime les fichiers temporaires.

// int	verif_here_doc(t_cmd *cmd)
// {
// 	void (*f)(t_cmd *cmd);
// }
