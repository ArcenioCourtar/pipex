CC			:= cc
NAME		:= libft.a
OBJFILES	:= \
	ft_atoi.o \
	ft_bzero.o \
	ft_calloc.o \
	ft_isalnum.o \
	ft_isalpha.o \
	ft_isascii.o \
	ft_isdigit.o \
	ft_isprint.o \
	ft_itoa.o \
	ft_memchr.o \
	ft_memcmp.o \
	ft_memcpy.o \
	ft_memmove.o \
	ft_memset.o \
	ft_putchar_fd.o \
	ft_putendl_fd.o \
	ft_putnbr_fd.o \
	ft_putstr_fd.o \
	ft_split.o \
	ft_strchr.o \
	ft_strdup.o \
	ft_striteri.o \
	ft_strjoin.o \
	ft_strlcat.o \
	ft_strlcpy.o \
	ft_strlen.o \
	ft_strmapi.o \
	ft_strncmp.o \
	ft_strnstr.o \
	ft_strrchr.o \
	ft_strtrim.o \
	ft_substr.o \
	ft_tolower.o \
	ft_toupper.o
OBJBONUS	:= \
	ft_lstsize.o \
	ft_lstnew.o \
	ft_lstlast.o \
	ft_lstclear.o \
	ft_lstiter.o \
	ft_lstadd_front.o \
	ft_lstadd_back.o \
	ft_lstdelone.o \
	ft_lstmap.o
OBJAFTER	:= \
	ft_isspace.o \
	ft_atol.o \
	ft_printf.o
HEADERFILE	:= libft.h
CFLAGS		:= -Wall -Werror -Wextra

# The files in OBJAFTER were added after libft's completion.

ALL_OBJ := $(OBJFILES) $(OBJBONUS) $(OBJAFTER)
# Commented out the flag since I want to add the bonus by default from now on
# ifdef COMP_BONUS
# ALL_OBJ := $(OBJFILES) $(OBJBONUS) $(OBJAFTER)
# else
# ALL_OBJ := $(OBJFILES)
# endif

all: $(NAME)

$(NAME): $(ALL_OBJ)
	ar -rcs $@ $^

ft_%.o: ft_%.c $(HEADERFILE)
	$(CC) -c $(CFLAGS) -o $@ $<

re: fclean all

clean:
	rm -f $(ALL_OBJ)

fclean:
	rm -f $(ALL_OBJ) $(NAME)

bonus:
	@$(MAKE)

# Ensures that these commands run even if there's a file
# with the same name is in the folder.
# Not needed for all, and re? ?_?
.PHONY: clean fclean bonus re all