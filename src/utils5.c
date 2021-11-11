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
	int	nqtdqt[3];

	nqtdqt[0] = -1;
	nqtdqt[1] = 0;
	nqtdqt[2] = 0;
	while (++nqtdqt[0] < index)
	{
		if (str[nqtdqt[0]] == 39)
		{
			nqtdqt[1] = 1;
			while (str[nqtdqt[0]] && str[nqtdqt[0]] != 39)
				nqtdqt[0]++;
			if (str[nqtdqt[0]] == 39)
				nqtdqt[1] = 0;
		}
		else if (str[nqtdqt[0]] == 34)
		{
			nqtdqt[2] = 1;
			while (str[nqtdqt[0]] && str[nqtdqt[0]] != 39)
				nqtdqt[0]++;
			if (str[nqtdqt[0]] == 39)
				nqtdqt[2] = 0;
		}
	}
	return (nqtdqt[1] || nqtdqt[2]);
}
