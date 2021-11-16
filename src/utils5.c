/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszklarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 14:38:38 by dszklarz          #+#    #+#             */
/*   Updated: 2021/11/11 14:38:44 by dszklarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

// int	ft_isinquote_now(char *str, int index)
// {
// 	int	nqd[3];

// 	nqd[0] = -1;
// 	nqd[1] = 0;
// 	nqd[2] = 0;
// 	while (++nqd[0] < index)
// 	{
// 		if (str[nqd[0]] == '\'' && nqd[0]++ >= 0)
// 		{
// 			while (str[nqd[0]] && str[nqd[0]] != 39 && nqd[0]++ < index)
// 				nqd[1] = 1;
// 			if (str[nqd[0]] == 39)
// 				nqd[1] = 0;
// 		}
// 		else if (str[nqd[0]] == '"' && nqd[0]++ >= 0)
// 		{
// 			while (str[nqd[0]] && str[nqd[0]] != 34 && nqd[0]++ < index)
// 				nqd[2] = 1;
// 			if (str[nqd[0]] == 34)
// 				nqd[2] = 0;
// 		}
// 	}
// 	return (nqd[1] || nqd[2]);
// }

int	ft_isinquote_now(char *str, int index)
{
	int		b;
	int		i;

	b = 0;
	i = -1;
	while (++i <= index)
	{
		if (b != '"' && str[i] == '\'')
			while (str[++i] != '\'' && i <= index)
				b = '\'';
		if (i > index)
			return (b != 0);
		b = 0;
		if (b != '\'' && str[i] == '"')
			while (str[++i] != '"' && i <= index)
				b = '"';
		if (i > index)
			return (b != 0);
	}
	return (b != str[i - 1] && (b == '\'' || b == '"'));
}

int	ft_isquote(char c)
{
	if (c == 34)
		return (1);
	else if (c == 39)
		return (2);
	return (0);
}

int	ft_myfree(char *str)
{
	free(str);
	return (1);
}
