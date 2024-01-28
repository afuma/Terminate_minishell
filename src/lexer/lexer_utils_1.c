/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 11:50:34 by edesaint          #+#    #+#             */
/*   Updated: 2024/01/22 21:44:02 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int set_len(t_data *data, int end)
{
    int len;
    
    len = end - data->start;
    if (len <= 0)
        return (-1);
    return (len);
}

bool skip_spaces(t_data *data, int *i)
{
    int tmp_i;

    tmp_i = *i;
    while (data->str[*i] && is_space(data->str[*i]))
        (*i)++;
    if (*i > tmp_i)
        return (true);
    return (false);
}

bool is_empty_quotes(t_data *data, int *i)
{
    if (is_double_symbol(data, *i, '\'') || \
        is_double_symbol(data, *i, '"'))
    {
        *i = *i + 2;
        return (true);
    }
    return (false);
}