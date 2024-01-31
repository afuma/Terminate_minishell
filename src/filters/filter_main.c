/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 21:57:05 by edesaint          #+#    #+#             */
/*   Updated: 2024/01/31 19:27:08 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool pass_on_filters(t_data *data)
{
    if (!data->token)
        return (true);
    if (!process_tokens(data, &filter_quotes))
        return (false);
    ft_token_iter(data, &filter_concatenate);
    if (!process_tokens(data, &filter_authorized_word))
        return (false);
    if (!process_tokens(data, &filter_affectation))
        return (false);
    ft_token_iter_expander(data, &expand_string);
    return (true);
}