/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:01:20 by edesaint          #+#    #+#             */
/*   Updated: 2024/01/28 13:48:54 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool is_quote(char c)
{
    return (c == '\'' || c == '"');
}

bool is_space(char c)
{
     return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

bool is_double_symbol(t_data *data, int i, char c)
{
    return (data->str[i] == c && data->str[++i] == c);
}