/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_getters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:22:11 by edesaint          #+#    #+#             */
/*   Updated: 2024/01/22 12:00:33 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token *get_end_token(t_data *data, t_token *token)
{
    if (!token)
        return (NULL);
    while (token && token->id != data->end)
        token = token->next;
    if (token && token->id == data->end)
        return (token);
    return (NULL);
}

t_token *get_first_token(t_data *data, t_node *node, t_token *token)
{
    if (!token)
        return (NULL);
    token = get_end_token(data, token);
    if (node->id > 0)
    {
        if (token->next && token->next->type_token == T_PIPE)
            token = token->next->next;
    }
    if (!token)
        return (NULL);
    return (token);
}

char *get_command(t_token *token)
{
    if (!token)
        return (NULL);
    if (token->type_token == T_COMMAND)
        return (token->str);
    return (NULL);
}

char *get_argument(t_data *data, t_token *token)
{
    if (!token)
        return (NULL);
    while (token && token->id <= data->end)
    {
        if (token->type_token == T_ARGUMENT)
            return (token->str);
        token = token->next;
    }
    return (NULL);
}