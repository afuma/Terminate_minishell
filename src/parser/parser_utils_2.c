/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 08:56:42 by blax              #+#    #+#             */
/*   Updated: 2024/01/24 15:27:12 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool in_node(t_data *data, t_token *token)
{
    return (token->id >= data->start && token->id <= data->end);
}

int compt_args(t_data *data)
{
    t_token *token;
    int i;

    i = 0;
    token = data->token;
    if (token == NULL)
        return (-1);
    while (token != NULL)
    {
        if (in_node(data, token))
        {
            if (token->type_token == T_ARGUMENT || token->type_token == T_COMMAND)
                i++;
        }
        token = token->next;
    }
    return (i);
}

int compt_nodes(t_data *data)
{
    t_token *token;
    int i;

    token = data->token;
    if (token == NULL)
        return (-1);
    i = 1;
    while (token != NULL)
    {
        if (token->type_token == T_PIPE)
            i++;
        token = token->next;
    }
    return (i);
}