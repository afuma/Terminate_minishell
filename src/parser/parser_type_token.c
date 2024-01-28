/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_type_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:06:18 by blax              #+#    #+#             */
/*   Updated: 2024/01/28 18:19:34 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void update_token_type(t_token *token, bool *is_cmd, t_state cur_state)
{
	if (is_syntax_redir(token->str))
        token->type_token = what_redirection(token->str);
    else if (is_pipe(token->str, is_cmd))
        token->type_token = T_PIPE;
    else if (is_command(is_cmd, cur_state))
        token->type_token = T_COMMAND;
	else if (cur_state == T_FILE)
        token->type_token = T_FILE;
    else
        token->type_token = T_ARGUMENT;
}

void determine_next_token_type(t_state type_token, t_state *cur_state)
{
    if (is_type_redir(type_token))
        *cur_state = T_FILE;
    else
        *cur_state = T_NULL;
}

void determine_token_types(t_data *data)
{
    t_token *cur_token;
    t_state cur_state;
    bool is_cmd;

    is_cmd = false;
	cur_token = data->token;
	cur_state = T_NULL;
    while (cur_token != NULL)
	{
        if (cur_token->type_token == T_NULL)
        {
            update_token_type(cur_token, &is_cmd, cur_state);
            determine_next_token_type(cur_token->type_token, &cur_state);
        }
        cur_token = cur_token->next;
    }
}