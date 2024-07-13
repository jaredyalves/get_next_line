NAME		:= libgnl.a
NAME_BONUS	:= $(patsubst %.a,%_bonus.a,$(NAME))

SRCDIR		:= src
OBJDIR		:= obj
INCDIR		:= include

SRCS		:= \
	$(SRCDIR)/get_next_line.c \
	$(SRCDIR)/get_next_line_utils.c \

SRCS_BONUS	:= \
	$(SRCDIR)/get_next_line_bonus.c \
	$(SRCDIR)/get_next_line_utils_bonus.c \

OBJS		:= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
OBJS_BONUS	:= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS_BONUS))
INCS		:= \
	$(INCDIR)/get_next_line.h \

INCS_BONUS	:= \
	$(INCDIR)/get_next_line_bonus.h \

CC			:= cc
INCLUDES	:= -I$(INCDIR)
CFLAGS		:= -O3 -Wall -Werror -Wextra $(INCLUDES)
LDFLAGS		:=

AR			:= ar
ARFLAGS		:= -rcs

RM			:= rm
RMFLAGS		:= -rf

.PHONY: all bonus clean fclean re

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

$(NAME_BONUS): $(OBJS_BONUS)
	$(AR) $(ARFLAGS) $(NAME_BONUS) $(OBJS_BONUS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(RMFLAGS) $(OBJDIR)

fclean: clean
	$(RM) $(RMFLAGS) $(NAME) $(NAME_BONUS)

re: fclean all
