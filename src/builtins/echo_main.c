/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefevre <mlefevre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 12:34:04 by mlefevre          #+#    #+#             */
/*   Updated: 2021/11/18 09:49:50 by mlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ft_putstr_fd(const char *s, int fd);

static int	is_nl_param(const char *s)
{
	return (s[0] == '-' && s[1] == 'n' && s[2] == 0);
}

int	main(int argc, char **argv)
{
	size_t	i;
	int		nl;

	(void)argc;
	i = 0;
	nl = 1;
	while (argv[++i])
	{
		if (is_nl_param(argv[i]))
		{
			nl = 0;
			continue ;
		}
		if (i > 1)
			ft_putstr_fd(" ", 1);
		ft_putstr_fd(argv[i], 1);
	}
	if (nl)
		ft_putstr_fd("\n", 1);
	return (0);
}
