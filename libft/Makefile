NAME	= libft.a
SRCS	= ft_atoi.c\
    ft_bzero.c\
    ft_isalnum.c\
    ft_isalpha.c\
    ft_isascii.c\
    ft_isdigit.c\
    ft_isprint.c\
    ft_memchr.c\
    ft_memcmp.c\
    ft_memcpy.c\
    ft_memmove.c\
    ft_memset.c\
    ft_strchr.c\
    ft_strlcat.c\
    ft_strlcpy.c\
    ft_strncmp.c\
    ft_strnstr.c\
    ft_strrchr.c\
    ft_tolower.c\
    ft_toupper.c\
    ft_strdup.c
OBJECTS	= $(SRCS:.c=.o)
INCS	= includes
RM	= rm -rf
CC	= gcc
CFLAGS	= -Wall -Wextra -Werror
AR = ar crs

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

all:	${NAME}

${NAME}: ${OBJECTS}
	$(AR) $@ $^

$clean :
			rm -f ${OBJECTS}

fclean :	clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
