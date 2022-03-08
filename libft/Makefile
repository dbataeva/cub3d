# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchromos <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/15 14:13:02 by cchromos          #+#    #+#              #
#    Updated: 2020/11/15 14:13:09 by cchromos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 	libft.a

SRCS	= 	ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memccpy.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strlen.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strnstr.c \
			ft_strncmp.c \
			ft_atoi.c \
			ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_split.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c

OBJS	= 	$(SRCS:.c=.o)

SRCS_B	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS_B	= ft_lstnew.o ft_lstadd_front.o ft_lstsize.o ft_lstlast.o ft_lstadd_back.o ft_lstdelone.o ft_lstclear.o ft_lstiter.o ft_lstmap.o

CC		= gcc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

all:	${NAME}

$(NAME): 	${OBJS} libft.h
			${CC} ${FLAGS} -c ${SRCS}
			ar rc ${NAME} ${OBJS}
			ranlib ${NAME}
		 
clean:
		${RM} ${OBJS} 
		${RM} ${OBJS_B}

fclean:		clean
			${RM} ${NAME}

re:		fclean all

bonus:	all
		${CC} ${FLAGS} -c ${SRCS_B}
		ar rc ${NAME} ${OBJS_B}
		ranlib ${NAME}

.PHONY:		all clean fclean re
