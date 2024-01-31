/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 12:33:07 by blax              #+#    #+#             */
/*   Updated: 2024/01/31 22:42:52 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void free_all(t_data *data)
{
    if (data)
    {
        free_tokens(data->token);
        free_nodes(data->node);
        free_data(data);
    }
}