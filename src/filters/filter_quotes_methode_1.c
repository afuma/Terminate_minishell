/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_quotes_methode_1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:10:16 by blax              #+#    #+#             */
/*   Updated: 2024/01/25 19:13:59 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// implementer ces deux fonctions avec d'autres
// (s'il y a une chaine avant ou apres, pouvoir les concatener)
bool filter_quotes(char *str)
{
    if (ft_strchr_bool(str, '\''))
        remove_quotes(str, '\'');
    else if (ft_strchr_bool(str, '\"'))
        remove_quotes(str, '"');
}

void remove_quotes(char *input, char type_quote)
{
    size_t len;

    len = ft_strlen(input);
    if (len >= 2 && input[0] == type_quote && input[len - 1] == type_quote)
    {
        ft_memmove(input, input + 1, len - 2);
        input[len - 2] = '\0';
    }
}