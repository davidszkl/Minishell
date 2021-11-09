/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszklarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:13:23 by dszklarz          #+#    #+#             */
/*   Updated: 2021/11/09 15:13:25 by dszklarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

int	ft_is_dchev(char *str, int n)
{
	if (n == 0)
	{
		if (str[n] == '<' && str[n + 1] == '<')
			return (1);
		else if (str[n] == '>' && str[n + 1] == '>')
			return (2);
	}
	if (n > 0)
	{
		if (str[n - 1] != '<' && str[n] == '<' && str[n + 1] == '<')
			return (1);
		if (str[n - 1] != '>' && str[n] == '>' && str[n + 1] == '>')
			return (2);
	}
	if (n == 0)
	{
		if (str[n] == '<' && str[n + 1] == '<')
			return (1);
		else if (str[n] == '>' && str[n + 1] == '>')
			return (2);
	}
	return (0);
}
