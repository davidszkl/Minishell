/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszklarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:07:39 by dszklarz          #+#    #+#             */
/*   Updated: 2021/11/15 17:21:49 by mlefevre         ###   ########.fr       */
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
# include <fcntl.h>

/*structures*/

typedef struct s_file {
	char	*name;
	int		flags;
	int		fd;
}	t_file;

typedef struct s_comm {
	t_file	*file_in;
	t_file	*file_out;
	pid_t	pid;
	char	**argv;
	char	*line;
	int		rin;
	int		rout;
	int		pipe[2];
}	t_comm;

typedef struct s_chev {
	char	*path;
	char	*nbrs;
	int		nbr;
}	t_chev;

typedef struct s_main {
	t_comm	*cline;
	t_chev	chev;
	char	**envp;
	char	**locals;
	char	*line;
	char	*temp;
	int		dchevcount;
	int		pipecount;
}	t_main;

/*checker*/

int		ft_check_echo(char *str);
int		ft_check_cmd(char *str);

/*parser*/

int		ft_read_chev(t_main *main);
int		ft_read_lpipe(t_main *main);
int		ft_parser(t_main *main);
int		ft_fillstruct(t_main *main);

/*expander*/

char	*expand_variables(const char *str, char **envp, char **locals);

/*executor*/

void	ft_execute(void);

/*functions*/

char	**init_envp(char **envp);
char	**init_locals(void);
char	*ft_remquotestr(char *str);
int		ft_remquote(t_main *main);
int		ft_getcount(t_main *main);

/*errors*/

int		ft_freeshell(t_main *main);
int		ft_freeshell2(t_main *main);
int		ft_freeshell3(t_main *main);
int		ft_myfreemain(t_main *main);
int		ft_myfree(char *str);

/*utils*/

size_t	ft_strlen(const char *str);
size_t	get_envp_size(char **envp);
char	**ft_splitq(char *str, char c);
char	*ft_replace_str(const char *s, size_t start, size_t n, const char *sub);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
char	*ft_getword(char *str, int n);
char	*ft_tolower(char *str);
char	*ft_itoas(int nbr);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_putendl_fd(char	*str, int fd);
void	ft_strcpy(char *dst, char *src);
void	ft_freetab(char **tab);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isinquote_now(char *str, int index);
int		ft_spwordcount(char *str, int n);
int		ft_isalnumx(char *str, int n);
int		ft_is_dchev(char *str, int n);
int		ft_check_chevpipe(char	*str);
int		ft_is_chev(char *str, int n);
int		ft_isinquote(char *str);
int		sort_envp(char **envp);
int		ft_isquote(char c);
int		ft_isspace(char c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);

/*erase*/

void	ft_showtab(char **tab);

/*TESTS*/

//>< salut >< hello <<a ||><< au revoi coucou <<b <<c <   
//salut << hello >> | C | < > < > <| A| F|A |FA AR AR >AR? G>?R AR|S 
//ARS A>R? < < <A ?R ?AGR> GAR |R|> 
//s << c"|"c
//salut << coucou | echo <<     bon"|"jour "|" |"|" salut << hello
//"echo"
//""

#endif
