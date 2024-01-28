/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 21:17:52 by edesaint          #+#    #+#             */
/*   Updated: 2024/01/28 15:13:25 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool is_redir(t_state type)
{
    return (
        (type == T_REDIR_IN)
        || (type == T_REDIR_OUT)
        || (type == T_REDIR_APPEND)
        || (type == T_REDIR_HEREDOC)
    );
}

bool is_file_redir(t_token *token)
{
    if (!token || !token->next)
        return (false);
    if (is_redir(token->type_token) && token->next->type_token == T_FILE)
        return (true);
    return (false);
}

char *get_name_redir(t_token *token)
{
    if (!token->next)
        return (NULL);
    if (token->next && token->next->type_token == T_FILE)
        return (token->next->str);
    return (NULL);
}