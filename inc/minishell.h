/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszklarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:07:39 by dszklarz          #+#    #+#             */
/*   Updated: 2021/11/10 09:57:55 by mlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H
# define PROMPT "minishell> "

/*includes*/

# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

/*structures*/

typedef struct s_comm {
	char	*line;
	char	**argv;
	int		pipe_in;
	int		pipe_out;
	int		*file_in;
	int		*file_out;
	int		redircount;
}	t_comm;

typedef struct s_chev {
	char	*path;
	char	*term;
	char	*nbrs;
	int		nbr;
}	t_chev;

typedef struct s_main {
	t_comm	*cline;
	t_chev	chev;
	char	*line;
	int		dchevcount;
	int		pipecount;
}	t_main;

/*checker*/

int		ft_check_cmd(char *str);
int		ft_check_echo(char *str);

/*parser*/

void	ft_read_chev(char *line, t_main *main);
int		ft_parser(t_main *main);

/*expander*/

char	*expand_variables(const char *str, const char **envp,
			const char **locals);

/*executor*/

void	ft_execute(void);

/*functions*/

char	*get_envp_val(const char *name, const char **envp);
char	**init_locals(void);
char	**init_envp(const char **envp);

/*errors*/

void	ft_freeshell(t_main *main);

/*utils*/

size_t	ft_strlen(const char *str);
void	ft_getcount(char *line, t_main *main);
size_t	get_envp_size(const char **envp);
void	ft_strcpy(char *dst, char *src);
void	ft_freetab(char **tab);
char	**ft_split(char *str, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_replace_str(const char *s, size_t start, size_t n, const char *sub);
char	*ft_strjoin(char *str, char *buff);
char	*ft_strdup(const char *s1);
char	*ft_getword(char *str);
char	*ft_tolower(char *str);
char	*ft_itoas(int nbr);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_spwordcount(char *str);
int		ft_isalnumx(char c);
int		ft_isspace(char c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_is_dchev(char *str, int n);
int		sort_envp(const char **envp);

/*erase*/

void	ft_showtab(char **tab);

#endif
