# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/31 14:29:47 by hubourge          #+#    #+#              #
#    Updated: 2025/01/06 16:33:15 by hubourge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -fPIC -g

NAME = libft.a

SRC = mandatory/ft_atoi.c \
		mandatory/ft_bzero.c \
		mandatory/ft_calloc.c \
		mandatory/ft_isascii.c \
		mandatory/ft_isalnum.c \
		mandatory/ft_isalpha.c \
		mandatory/ft_split.c \
		mandatory/ft_isdigit.c \
		mandatory/ft_isprint.c \
		mandatory/ft_itoa.c \
		mandatory/ft_strlcat.c \
		mandatory/ft_memchr.c \
		mandatory/ft_memcmp.c \
		mandatory/ft_memset.c \
		mandatory/ft_strchr.c \
		mandatory/ft_strdup.c \
		mandatory/ft_strlcpy.c \
		mandatory/ft_strlen.c \
		mandatory/ft_strtrim.c \
		mandatory/ft_strncmp.c \
		mandatory/ft_striteri.c \
		mandatory/ft_putnbr_fd.c \
		mandatory/ft_memmove.c \
		mandatory/ft_strnstr.c \
		mandatory/ft_strrchr.c \
		mandatory/ft_tolower.c \
		mandatory/ft_toupper.c \
		mandatory/ft_putchar_fd.c \
		mandatory/ft_putendl_fd.c \
		mandatory/ft_putstr_fd.c \
		mandatory/ft_strjoin.c \
		mandatory/ft_substr.c \
		mandatory/ft_memcpy.c \
		mandatory/ft_strmapi.c \
		mandatory/ft_putnbr_base_fd.c \
		bonus/ft_lstnew_bonus.c \
		bonus/ft_lstadd_front_bonus.c \
		bonus/ft_lstsize_bonus.c \
		bonus/ft_lstlast_bonus.c \
		bonus/ft_lstadd_back_bonus.c \
		bonus/ft_lstdelone_bonus.c \
		bonus/ft_lstclear_bonus.c \
		bonus/ft_lstiter_bonus.c \
		bonus/ft_lstmap_bonus.c \
		ft_printf/ft_printf.c \
		ft_printf/ft_put.c \
		ft_printf/ft_putnbr_base.c \
		ft_printf/ft_address.c \
		ft_printf/ft_check.c \

OBJ = ${SRC:.c=.o}

.c.o : 
	${CC} ${CFLAGS} -c $< -o $@

$(NAME) : ${OBJ}
	@ ar -rc  $(NAME) ${OBJ}

all : $(NAME)

clean :
	@ rm -f ${OBJ}

fclean : clean
	@ rm -f ${NAME}

re : fclean all

.PHONY : all clean fclean re

