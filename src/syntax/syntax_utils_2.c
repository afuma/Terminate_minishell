/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:38:36 by edesaint          #+#    #+#             */
/*   Updated: 2024/01/22 12:14:49 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool is_closed_quotes(t_data *data)
{
    int i;

    i = 0;
    while (data->str[i])
    {
        update_is_quote(data, data->str[i]);
        i++;
    }
    if (!data->str[i] && data->in_quote)
        return (false);
    return (true);
}

void update_is_quote(t_data *data, char letter)
{
    if (is_quote(letter) && !data->in_quote)
    {
        data->type_quote = letter;
        data->in_quote = 1;
    }
    else if (is_quote(letter) && data->in_quote)
    {
        if (letter == data->type_quote)
        {
            data->type_quote = '\0';
            data->in_quote = 0;
        }
    }
}