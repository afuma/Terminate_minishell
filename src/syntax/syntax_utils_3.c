/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 22:32:16 by edesaint          #+#    #+#             */
/*   Updated: 2024/01/28 13:49:19 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool is_begin_by_pipe(t_token *token)
{
    return (token->id == 0 && token->type_token == T_PIPE);
}

bool is_end_by_pipe(t_token *token)
{
    token = ft_token_last(token);
    return (token->type_token == T_PIPE);
}

bool check_redir(t_token *token)
{
    if (is_redir(token->type_token))
    {
        token = token->next;
        if (!token)
            return (false);
        if (is_redir(token->type_token))
            return (false);
        if (token->type_token == T_PIPE)
            return (false);
    }
    return (true);
}

bool is_valid_redir(t_token *token)
{
    while (token)
    {
        if (!check_redir(token))
            return (false);
        token = token->next;
    }
    return (true);
}