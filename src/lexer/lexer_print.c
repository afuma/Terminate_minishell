/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 08:55:05 by blax              #+#    #+#             */
/*   Updated: 2024/01/23 12:10:59 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Fonction pour afficher le contenu de tous les tokens
void print_tokens(t_token *tokens)
{
    while (tokens != NULL)
	{
        printf("Token %d:\n", tokens->id);
        printf("Token->str: %s\n", tokens->str);
        printf("Token->type_str: %s\n", transform_enum_quote(tokens->type_str));
        printf("Token->type_rstick: %s\n", transform_enum_quote(tokens->type_rstick));
        printf("Token->type_lstick: %s\n", transform_enum_quote(tokens->type_lstick));
        printf("Token->is_space: %i\n", tokens->is_space);
        printf("Token->type_token: %s\n", transform_enum_type_token(tokens->type_token));
        // printf("Token->current: %p\n", tokens);
        // printf("Token->next: %p\n", tokens->next);
        printf("\n");
        tokens = tokens->next;
    }
	// printf("Token: %p\n", tokens);
}