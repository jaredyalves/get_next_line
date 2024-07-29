NAME			:=	libgnl.a
NAME_BONUS		:=	$(patsubst %.a,%_bonus.a,$(NAME))

SRCDIR			:=	src
OBJDIR			:=	obj
LIBDIR			:=	lib
INCDIR			:=	include

SRCS			:=
SRCS			+=	$(SRCDIR)/get_next_line.c
SRCS			+=	$(SRCDIR)/get_next_line_utils.c
SRCS_BONUS		:=
SRCS_BONUS		+=	$(SRCDIR)/get_next_line_bonus.c
SRCS_BONUS		+=	$(SRCDIR)/get_next_line_utils_bonus.c
OBJS			:=	$(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
OBJS_BONUS		:=	$(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS_BONUS))
INCS			:=	$(INCDIR)/get_next_line.h
INCS_BONUS		:=	$(INCDIR)/get_next_line_bonus.h

CC				:=	/bin/cc
INCLUDES		:=	-I$(INCDIR)
CFLAGS			:=	-O3 -Wall -Werror -Wextra $(INCLUDES)
LDFLAGS			:=

AR				:=	/bin/ar
ARFLAGS			:=	-rcs

RM				:=	/bin/rm
RMFLAGS			:=	-rf

COLOR_RESET		:=	\033[0m
COLOR_CLEAN		:=	\033[0;33m
COLOR_COMPILE	:=	\033[0;32m
COLOR_LINK		:=	\033[0;34m

.PHONY: all bonus clean fclean re

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJS)
	@printf "$(COLOR_LINK)Creating archive $@...$(COLOR_RESET)\n"
	@$(AR) $(ARFLAGS) $@ $(OBJS)

$(NAME_BONUS): $(OBJS_BONUS)
	@printf "$(COLOR_LINK)Creating bonus archive $@...$(COLOR_RESET)\n"
	@$(AR) $(ARFLAGS) $(NAME_BONUS) $(OBJS_BONUS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCS) $(INCS_BONUS)
	@mkdir -p $(dir $@)
	@printf "$(COLOR_COMPILE)Compiling $<...$(COLOR_RESET)\n"
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@printf "$(COLOR_CLEAN)Cleaning up...$(COLOR_RESET)\n"
	@$(RM) $(RMFLAGS) $(OBJDIR)

fclean: clean
	@printf "$(COLOR_CLEAN)Removing $(NAME) and $(NAME_BONUS)...$(COLOR_RESET)\n"
	@$(RM) $(RMFLAGS) $(NAME) $(NAME_BONUS)

re: fclean all
