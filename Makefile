NAME	= minishell

SRCDIR	= src

SRCS	= $(shell find $(SRCDIR)/*.c)

OBJDIR	= obj

OBJS	= $(subst $(SRCDIR), $(OBJDIR), $(SRCS:.c=.o))

INCDIR	= inc

CC		= cc

RM		= rm -f

CFLAGS	= -Wall -Werror -Wextra -g

LIB		= -lreadline

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/*.h
			$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@
                
all:	$(NAME)

$(OBJDIR):
			mkdir -p $(OBJDIR) 

$(NAME):        $(OBJDIR) $(OBJS)
			$(CC) $(CFLAGS) $(LIB) $(OBJS) -o $(NAME)

install:
			mkdir $(OBJDIR) $(SRCDIR) $(INCDIR)
			touch $(INCDIR)/$(NAME).h
			touch $(SRCDIR)/$(NAME).c
clean:
			$(RM) -r $(OBJDIR)

fclean:	clean
			$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re install
