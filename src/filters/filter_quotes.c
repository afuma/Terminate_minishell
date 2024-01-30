/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:10:16 by blax              #+#    #+#             */
/*   Updated: 2024/01/29 14:39:35 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool remove_quotes(char *input, char type_quote)
{
    size_t len;

    len = ft_strlen(input);
    if (len == 0)
        return (true);
    if (len >= 2 && input[0] == type_quote && input[len - 1] == type_quote)
    {
        ft_memmove(input, input + 1, len - 2);
        input[len - 2] = '\0';
    }
    return (true);
}

bool filter_quotes(char *str)
{
    remove_quotes(str, '\'');
    remove_quotes(str, '"');
    return (true);
}