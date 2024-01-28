/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:08:04 by blax              #+#    #+#             */
/*   Updated: 2024/01/26 16:44:34 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool process_syntax(t_data *data, int *i)
{
    if (!is_syntax(data->str[*i]))
        return (false);
    if (is_syntax_char(data->str[*i]))
    {
        if (is_double_symbol(data, *i, '>') || \
            is_double_symbol(data, *i, '<'))
        {
            (*i)++;
        }
        (*i)++;
    }
    return (true);
}

// // methode 1 (quote n'est pas un delimiter)
// bool process_string(t_data *data, int *i)
// {
//     char c;
    
//     c = data->str[*i];
//     if (is_space(c) || is_syntax_char(c))
//         return (false);
//     while (c && !is_space(c) && !is_syntax_char(c))
//     {
//         (*i)++;
//         c = data->str[*i];
//     }
//     return (true);
// }

// methode 2 (quote est un delimiteur)
bool process_string(t_data *data, int *i)
{
    char c;
    
    c = data->str[*i];
    if (is_syntax(c))
        return (false);
    while (c && !is_syntax(c))
    {
        (*i)++;
        c = data->str[*i];
    }
    return (true);
}


/* Traite une séquence de guillemets dans la chaîne de caractères de 'data'. */
bool process_quote(t_data *data, int *i)
{
    char type_quote;

    if (!data->str[*i])
        return (false);
    if (!is_quote(data->str[*i]))
        return (false);
    type_quote = data->str[*i];
    (*i)++;
    while (data->str[*i])
    {
        if (data->str[*i] && is_quote(data->str[*i]))
        {
            if (data->str[*i] == type_quote)
            {
                (*i)++;
                return (true);
            }
        }
        (*i)++;
    }
    return (true);
}

// voir peut etre si il y a besoin de connaitre le nombre de double quotes d'affiler, alors 
// rajouter un attribut a la structure data et incrementer dans ft_lexer
/* Analyse la chaîne de caractères 'str' et remplit 'data' avec les tokens. */
bool ft_lexer(t_data *data)
{
    int i;
    int len_str;
    
    i = 0;
    while (data->str[i])
    {
        if (skip_spaces(data, &i))
            data->is_space = true;
        data->start = i;
        if (!is_empty_quotes(data, &i))
        {
            if (!process_quote(data, &i))
                if (!process_string(data, &i))
                    process_syntax(data, &i);
            len_str = set_len(data, i);
            if (len_str == -1)
                return (false);
            add_token(data, i, len_str);
            data->is_space = false;
        }
        data->nb_tokens++;
    }
    return (true);
}