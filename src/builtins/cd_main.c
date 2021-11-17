/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefevre <mlefevre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 10:49:20 by mlefevre          #+#    #+#             */
/*   Updated: 2021/11/17 13:30:21 by mlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_cd(char ***envp, char **argv);
char	**init_envp(char **envp);
void	*exec_perror(const char *str);

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	envp = init_envp(envp);
	if (!envp)
		return ((int)exec_perror("init_envp") + 1);
	return (ft_cd(&envp, argv));
}
