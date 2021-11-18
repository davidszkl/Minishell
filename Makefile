NAME	= minishell

SRCDIR	= src

SRCS	= $(shell find $(SRCDIR)/*.c)

OBJDIR	= obj

OBJS	= $(subst $(SRCDIR), $(OBJDIR), $(SRCS:.c=.o))

EXPORT = export

UNSET = unset

CD = cd

ECHO = echo

PWD = pwd

ENV = env

EXIT = exit

BINDIR = bin

ECHO_OBJS = $(addprefix $(OBJDIR)/, builtins/echo_main.o\
			ft_putstr_fd.o\
			ft_unset.o\
			utils.o\
			utils2.o\
			 utils3.o\
			 utils4.o\
			 utils5.o\
			 envp_utils.o\
			 ft_export.o\
			 ft_export_utils.o\
			 ft_export_utils_2.o\
			 ft_export_utils_3.o\
			 error.o\
			 ft_isalnum.o\
			 )


CD_OBJS = $(addprefix $(OBJDIR)/, builtins/cd_main.o\
		  	ft_exec.o\
		  	ft_exec_utils.o\
			ft_cd.o\
			find_command.o\
			ft_split.o\
			ft_putstr_fd.o\
			 ft_unset.o\
			 utils.o\
			 utils2.o\
			 utils3.o\
			 utils4.o\
			 utils5.o\
			 envp_utils.o\
			 ft_export.o\
			 ft_export_utils.o\
			 ft_export_utils_2.o\
			 ft_export_utils_3.o\
			 error.o\
			 ft_isalnum.o\
			 )

PWD_OBJS = $(addprefix $(OBJDIR)/, builtins/pwd_main.o\
			 ft_unset.o\
			 utils.o\
			ft_putstr_fd.o\
			 utils2.o\
			 utils3.o\
			 utils4.o\
			 utils5.o\
			 envp_utils.o\
			 ft_export.o\
			 ft_export_utils.o\
			 ft_export_utils_2.o\
			 ft_export_utils_3.o\
			 error.o\
			 ft_isalnum.o\
			 )

EXPORT_OBJS = $(addprefix $(OBJDIR)/, builtins/export_main.o\
			ft_export.o\
			envp_utils.o\
			ft_export_utils.o\
			ft_export_utils_2.o\
			ft_export_utils_3.o\
			utils.o\
			utils2.o\
			utils3.o\
			utils4.o\
			utils5.o\
			error.o\
			)

UNSET_OBJS = $(addprefix $(OBJDIR)/, builtins/unset_main.o\
			 ft_unset.o\
			 utils.o\
			 utils2.o\
			 utils3.o\
			 utils4.o\
			 utils5.o\
			 envp_utils.o\
			 ft_export.o\
			 ft_export_utils.o\
			 ft_export_utils_2.o\
			 ft_export_utils_3.o\
			 error.o\
			 ft_isalnum.o\
			 )

ENV_OBJS = $(addprefix $(OBJDIR)/, builtins/env_main.o\
		   	to_erase.o\
			 ft_unset.o\
			 utils.o\
			ft_putstr_fd.o\
			 utils2.o\
			 utils3.o\
			 utils4.o\
			 utils5.o\
			 envp_utils.o\
			 ft_export.o\
			 ft_export_utils.o\
			 ft_export_utils_2.o\
			 ft_export_utils_3.o\
			 error.o\
			 ft_isalnum.o\
			 )
EXIT_OBJS = $(addprefix $(OBJDIR)/, builtins/exit_main.o\
			ft_atoi.o\
			ft_exit.o\
			 ft_unset.o\
			 utils.o\
			ft_putstr_fd.o\
			 utils2.o\
			 utils3.o\
			 utils4.o\
			 utils5.o\
			 envp_utils.o\
			 ft_export.o\
			 ft_export_utils.o\
			 ft_export_utils_2.o\
			 ft_export_utils_3.o\
			 error.o\
			 ft_isalnum.o\
			 )

BUILTINS = $(addprefix $(BINDIR)/, $(ECHO)\
		   $(CD)\
		   $(PWD)\
		   $(EXPORT)\
		   $(UNSET)\
		   $(ENV)\
		   $(EXIT))

INCDIR	= inc

CC		= cc

RM		= rm -f

CFLAGS	= -Wall -Werror -Wextra -g

LIB		= -lreadline

all:	$(NAME) $(BINDIR) $(BUILTINS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/*.h
			$(CC) $(CFLAGS) -I$(INCDIR) -I/Users/$(USER)/.brew/opt/readline/include -c $< -o $@

$(OBJDIR)/builtins/%.o: $(SRCDIR)/builtins/%.c
			$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@           

$(BINDIR)/$(ECHO): $(ECHO_OBJS)
	$(CC) $(CFLAGS) -Iinc $^ -o $@

$(BINDIR)/$(CD): $(CD_OBJS)
	$(CC) $(CFLAGS) -Iinc $^ -o $@

$(BINDIR)/$(PWD): $(PWD_OBJS)
	$(CC) $(CFLAGS) -Iinc $^ -o $@

$(BINDIR)/$(EXPORT): $(EXPORT_OBJS)
	$(CC) $(CFLAGS) -Iinc $^ -o $@

$(BINDIR)/$(UNSET): $(UNSET_OBJS)
	$(CC) $(CFLAGS) -Iinc $^ -o $@

$(BINDIR)/$(ENV): $(ENV_OBJS)
	$(CC) $(CFLAGS) -Iinc $^ -o $@

$(BINDIR)/$(EXIT): $(EXIT_OBJS)
	$(CC) $(CFLAGS) -Iinc $^ -o $@

$(OBJDIR):
			mkdir -p $(OBJDIR)
			mkdir $(OBJDIR)/builtins
$(BINDIR):
	mkdir $(BINDIR)

$(NAME):        $(OBJDIR) $(OBJS)
			$(CC) $(CFLAGS) $(LIB) -L/Users/$(USER)/.brew/opt/readline/lib $(OBJS) -o $(NAME)

install:
			mkdir $(OBJDIR) $(SRCDIR) $(INCDIR) $(BINDIR)
			touch $(INCDIR)/$(NAME).h
			touch $(SRCDIR)/$(NAME).c
clean:
			$(RM) -r $(OBJDIR)

fclean:	clean
			$(RM) $(NAME)
			$(RM) -r $(BINDIR)

re:	fclean all

.PHONY:	all clean fclean re install
