/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_args.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefevre <mlefevre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:17:36 by mlefevre          #+#    #+#             */
/*   Updated: 2021/11/08 17:08:00 by mlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_VARIABLES_ARGS_H
# define EXPAND_VARIABLES_ARGS_H

typedef struct s_expand_variables_2_args
{
	char	*tmp1;
	char	*tmp2;
	char	*t;

}	t_expand_variables_2_args;

typedef struct s_expand_variables_args
{
	int		is_in_quote;
	size_t	i;
	char	*s;

}	t_expand_variables_args;

int						ft_isdigit(int c);
int						ft_isalpha(int c);
size_t					ft_strlen(const char *s);
size_t					var_len(const char *s);
void					*free_4(void *a, void *b, void *c, void *d);
char					*ft_strdup(const char *s);
t_expand_variables_args	init_args(const char *str);

#endif
