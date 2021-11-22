/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszklarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:37:24 by dszklarz          #+#    #+#             */
/*   Updated: 2021/11/22 13:45:21 by mlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

int	ft_parse_error(t_main *main)
{
	char	*str;
	int		n;

	n = 0;
	str = main->line;
	while (str[n])
	{
		str = main->line;
		if (ft_is_chev(str, n++))
		{
			if (str[n] && str[n] == '|' && str[n + 1]
				&& ft_is_chev(str, n - 1) == 4)
				main->line = ft_replace_str(str, n, ft_strlen(str) - n - 1,
						&str[n + 1]);
			else
			{
				while (ft_isspace(str[n]) || (ft_is_chev(str, n - 1) > 0
						&& ft_is_chev(str, n - 1) < 2))
					n++;
				if (str[n] == '|')
					return (1);
			}
		}
	}
	return (0);
}

int	ft_tabcheck(t_main *main)
{
	int	n;
	int	j;

	n = 0;
	j = 0;
	while (main->cline[n].argv[j])
	{
		if (ft_is_chev(main->cline[n].argv[j], 0)
			&& (!main->cline[n].argv[j + 1]
				|| ft_is_chev(main->cline[n].argv[j + 1], 0)))
			return (1);
		j++;
	}
	return (0);
}

void	ft_freefiles(t_main *main, int n)
{
	int	j;

	j = 0;
	while (j < main->cline[n].rin)
		free(main->cline[n].file_in[j++].name);
	j = 0;
	while (j < main->cline[n].rout)
		free(main->cline[n].file_out[j++].name);
}

int	ft_dpipe_check(t_main *main)
{
	int	count;
	int	n;

	count = 0;
	n = 0;
	while (main->line[n])
	{
		if (main->line[n++] == '|' && !ft_isinquote_now(main->line, n - 1))
			while (main->line[n] && count++ >= 0)
				if (!ft_isspace(main->line[n++]))
					break ;
		if (main->line[n - 1] == '|' && count == 1)
		{
			ft_putstr_fd("minishell: binary operand '||' not supported\n", 2);
			return (1);
		}
		else if (main->line[n - 1] == '|' && count)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token \
`|'\n", 2);
			return (1);
		}
	}
	return (0);
}

int	ft_syntax_check(t_main *main, int n, int j)
{
	while (main->cline[n].line)
	{
		j = 0;
		while (main->cline[n].argv[j])
		{
			if (ft_is_chev(main->cline[n].argv[j], 0))
			{
				if (!main->cline[n].argv[j + 1]
					|| ft_is_chev(main->cline[n].argv[j + 1], 0))
				{
					ft_putstr_fd("minishell: syntax error near unexpected token \
`", 2);
					if (!main->cline[n].argv[j + 1])
						ft_putstr_fd("newline", 2);
					else
						ft_putstr_fd(main->cline[n].argv[j + 1], 2);
					ft_putstr_fd("'\n", 2);
					main->error = 1;
					return (1);
				}
			}
			j++;
		}
		n++;
	}
	return (0);
}
