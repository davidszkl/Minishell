NAME	= minishell

SRCDIR	= src

SRCS	= $(shell find $(SRCDIR)/*.c)

OBJDIR	= obj

OBJS	= $(subst $(SRCDIR), $(OBJDIR), $(SRCS:.c=.o))

EXPORT = export

UNSET = unset

BINDIR = bin

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
			error.o\
			)

UNSET_OBJS = $(addprefix $(OBJDIR)/, builtins/unset_main.o\
			 ft_unset.o\
			 utils.o\
			 utils2.o\
			 utils3.o\
			 utils4.o\
			 envp_utils.o\
			 ft_export.o\
			 ft_export_utils.o\
			 ft_export_utils_2.o\
			 ft_export_utils_3.o\
			 error.o\
			 ft_isalnum.o\
			 )

BUILTINS = $(addprefix $(BINDIR)/, $(EXPORT) $(UNSET))

INCDIR	= inc

CC		= cc

RM		= rm -f

CFLAGS	= -Wall -Werror -Wextra -g

LIB		= -lreadline

all:	$(NAME) $(BINDIR) $(BUILTINS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/*.h
			$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR)/builtins/%.o: $(SRCDIR)/builtins/%.c
			$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@           

$(BINDIR)/$(EXPORT): $(EXPORT_OBJS)
	$(CC) $(CFLAGS) -Iinc $^ -o $@

$(BINDIR)/$(UNSET): $(UNSET_OBJS)
	$(CC) $(CFLAGS) -Iinc $^ -o $@

$(OBJDIR):
			mkdir -p $(OBJDIR)
			mkdir $(OBJDIR)/builtins
$(BINDIR):
	mkdir $(BINDIR)

$(NAME):        $(OBJDIR) $(OBJS)
			$(CC) $(CFLAGS) $(LIB) $(OBJS) -o $(NAME)

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
