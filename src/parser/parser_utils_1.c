/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:04:32 by blax              #+#    #+#             */
/*   Updated: 2024/01/28 18:19:35 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool is_command(bool *is_cmd, t_state cur_state)
{
	if (cur_state != T_NULL)
		return (false);
   	if (!*is_cmd)
	{
		*is_cmd = true;
		return (true);
	}
	return (false);
}

bool is_pipe(char *str, bool *is_cmd)
{
    if (ft_strcmp(str, "|") == 0)
	{
		*is_cmd = false;
		return (true);
	}
	return (false);
}

t_state what_redirection(char *str)
{
	if (ft_strcmp(str, ">") == 0)
		return (T_REDIR_OUT);
	else if (ft_strcmp(str, "<") == 0)
		return (T_REDIR_IN);
	else if (ft_strcmp(str, ">>") == 0)
		return (T_REDIR_APPEND);
	else if (ft_strcmp(str, "<<") == 0)
		return (T_REDIR_HEREDOC);
	return (T_NULL);
}

bool is_type_redir(t_state type_token)
{
	return (
		type_token == T_REDIR_IN || \
		type_token == T_REDIR_OUT || \
		type_token == T_REDIR_APPEND || \
		type_token == T_REDIR_HEREDOC
	);
}