/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefevre <mlefevre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:17:19 by mlefevre          #+#    #+#             */
/*   Updated: 2021/11/08 17:29:50 by mlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"
#include "expand_variables_args.h"

size_t	var_len(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && (ft_isdigit(s[i]) || ft_isalpha(s[i]) || s[i] == '_'))
		i++;
	return (i);
}

void	*free_4(void *a, void *b, void *c, void *d)
{
	free(a);
	free(b);
	free(c);
	free(d);
	return (0);
}

t_expand_variables_args	init_args(const char *str)
{
	t_expand_variables_args	args;

	args.s = ft_strdup(str);
	args.i = -1;
	args.is_in_quote = 0;
	return (args);
}
