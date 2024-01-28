/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:11:36 by edesaint          #+#    #+#             */
/*   Updated: 2024/01/22 21:58:08 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_stick_token set_type_lstick(t_data *data)
{
    if (data->start > 0)
        return (ft_type_char(data->str[--data->start]));
    return (S_NULL);
}

t_token *init_token(void)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->id = 0;
    token->type_token = T_NULL;
    token->str = NULL;
    token->type_str = S_NULL;
    token->type_rstick = S_NULL;
    token->type_lstick = S_NULL;
    token->is_space = false;
    token->next = NULL;

    return (token);
}

t_token *create_token(t_data *data, int end, int len)
{
    t_token *token;

    token = init_token();
    if (!token)
        return (NULL);
    token->id = data->nb_tokens;
    token->type_token = T_NULL;
    token->str = ft_substr(data->str, (unsigned int) data->start, (size_t) len);
    token->type_str = ft_type_char(data->str[--end]);
    token->type_rstick = ft_type_char(data->str[++end]);
    token->type_lstick = set_type_lstick(data);
    token->is_space = data->is_space;
    
    return (token);
}

bool add_token(t_data *data, int end, int len)
{
    t_token *new_token;

    new_token = create_token(data, end, len);
    if (!new_token)
        return (false);
    if (!data->token)
        data->token = new_token;
    else
        ft_token_add_back(&data->token, new_token);
    return (true);
}