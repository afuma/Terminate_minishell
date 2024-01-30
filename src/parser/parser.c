/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:33:24 by blax              #+#    #+#             */
/*   Updated: 2024/01/29 19:23:07 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void parser(t_data *data)
{
    // parse_quote_tokens(data);
    init_nodes(data);
    // fill_heredoc(data);
    fill_nodes(data);
}