/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefevre <mlefevre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 12:34:04 by mlefevre          #+#    #+#             */
/*   Updated: 2021/11/17 13:04:03 by mlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putstr_fd(const char *s, int fd);

static int	is_nl_param(const char *s)
{
	return (s[0] == '-' && s[1] == 'n' && s[2] == 0);
}

int	main(int argc, char **argv)
{
	int	nl;

	nl = 1;
	while (*++argv)
	{
		if (is_nl_param(*argv))
		{
			nl = 0;
			continue ;
		}
		ft_putstr_fd(*argv, 1);
		if (argv[1])
			ft_putstr_fd(" ", 1);
	}
	if (nl)
		ft_putstr_fd("\n", 1);
	return (0);
}
