/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszklarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:07:39 by dszklarz          #+#    #+#             */
/*   Updated: 2021/11/04 12:10:05 by dszklarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H
# define PROMPT "minishell>"

/*includes*/

# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>

/*structures*/

typedef struct s_comm {
	char	*comm;
	char	**args;
}	t_comm;

/*lexer*/

/*parser*/

int		ft_parser(char *line);

/*expander*/

/*executor*/

/*functions*/

/*errors*/

/*utils*/

char	**ft_split(char *str);
void	ft_strcpy(char *dst, char *src);
void	ft_freetab(char **tab);
int		ft_strlen(char *str);

#endif
