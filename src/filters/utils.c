/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:36:42 by edesaint          #+#    #+#             */
/*   Updated: 2024/01/26 11:01:22 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// X 
// ne devrais plus etre utile car on gere les doubles quotes en amont mais on peut toujours y faire reference
// si besoin avec le type_token->rstick/lstick
// bool is_empty_token(t_token *token)
// {
// 	if (!token)
// 		return (true);
// 	if (token && token->str[0] == '\0'
// 		&& (token->type_str == S_QUOTE
// 		|| token->type_str == D_QUOTE))
// 	{
// 		return (true);
// 	}
// 	return (false);
// }

// if (token->type_token == T_COMMAND && token->rstick_token == is_quote(token->str))
