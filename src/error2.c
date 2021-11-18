/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszklarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:37:24 by dszklarz          #+#    #+#             */
/*   Updated: 2021/11/18 11:37:25 by dszklarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

int ft_parse_error(t_main *main)
{
    char    *str;
    int     n;

    n = 0;
    str = main->line;
    while (str[n])
    {
        str = main->line;
        if (str[n] == '|' && !ft_isinquote_now(str, n++))
            if (str[n] && str[n] == '|')
                return (write(1, "minishell: parse error near `||'\n", 33));
        if (ft_is_chev(str, n) && str[n + 1] && str[n + 1] == '|')
            main->line = ft_replace_str(str, n + 1, ft_strlen(str) - n, &str[n + 2]);
        n++;
    }
    return (0);
}