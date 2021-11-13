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

int	ft_isquote(char *str)
{
	int	n;
	int	quote;
	int	dquote;

	n = 0;
	quote = 0;
	dquote = 0;
	while (str[n])
	{
		if (str[n] == 39)
			quote = !quote;
		else if (str[n] == 34)
			dquote = !dquote;
		n++;
	}
	if (quote || dquote)
		return (1);
	return (0);
}

int	ft_isquote_now(char *str, int index)
{
	int	nqd[3];

	nqd[0] = -1;
	nqd[1] = 0;
	nqd[2] = 0;
	while (++nqd[0] < index + 1)
	{
		if (str[nqd[0]] == 39 && nqd[0]++)
		{
			nqd[1] = 1;
			while (str[nqd[0]] && str[nqd[0]] != 39 && nqd[0] < index)
				nqd[0]++;
			if (str[nqd[0]] == 39)
				nqd[1] = 0;
		}
		else if (str[nqd[0]] == 34 && nqd[0]++)
		{
			nqd[2] = 1;
			while (str[nqd[0]] && str[nqd[0]] != 34 && nqd[0] < index)
				nqd[0]++;
			if (str[nqd[0]] == 34)
				nqd[2] = 0;
		}
	}
	return (nqd[1] || nqd[2]);
}
