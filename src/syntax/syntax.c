/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:48:38 by edesaint          #+#    #+#             */
/*   Updated: 2024/01/26 11:51:41 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool verif_syntax(t_token *token)
{
    if (!token)
        return (true);
    if (is_begin_by_pipe(token))
        return (false);
    if (is_end_by_pipe(token))
        return (false);
    if (!is_valid_redir(token))
        return (false);
    return (true);
}