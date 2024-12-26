# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hubourge <hubourge@student.42angouleme.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/31 14:29:47 by hubourge          #+#    #+#              #
#    Updated: 2024/12/23 20:00:17 by hubourge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc
# -Wpadded now if a structure is padded, it will be detected
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDE		= -I includes

LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

OBJ_DIR		= obj

SRC			= srcs/malloc/malloc.c \
				srcs/malloc/init.c \
				srcs/show_alloc_mem/show_alloc_mem.c \

OBJ			= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

SRC_TEST	= $(SRC) srcs/main.c
OBJ_TEST	= $(addprefix $(OBJ_DIR)/, $(SRC_TEST:.c=.o))

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

YELLOW		=\033[0;33m
BIBlue		=\033[1;94m
NC			=\033[0m

all: $(LIBFT) libft_malloc_$(HOSTTYPE).so
	@ ln -sf libft_malloc_$(HOSTTYPE).so libft_malloc.so
	@ echo "$(BIBlue)"
	@ echo "                 _ _            "
	@ echo "                | | |           "
	@ echo " _ __ ___   __ _| | | ___   ___ "
	@ echo "| '_ \` _ \ / _\` | | |/ _ \ / __|"
	@ echo "| | | | | | (_| | | | (_) | (__ "
	@ echo "|_| |_| |_|\__,_|_|_|\___/ \___|"
	@ echo "$(NC)"

$(LIBFT):
	@ echo "$(YELLOW)Compiling libft...$(NC)"	
	@ make -sC $(LIBFT_DIR)

$(OBJ_DIR)/%.o: %.c
	@ mkdir -p $(@D)
	@ $(CC) $(CFLAGS) ${INCLUDE} -c $< -o $@

libft_malloc_$(HOSTTYPE).so: $(OBJ)
	@ echo "$(YELLOW)Compiling objects...$(NC)"
	@ echo "$(YELLOW)Creating libft_malloc_$(HOSTTYPE).so...$(NC)"
	@ $(CC) $(CFLAGS) ${INCLUDE} -shared -o $@ $(OBJ)

test: fclean $(LIBFT) $(OBJ_TEST)
	@ echo "$(YELLOW)Compiling objects...$(NC)"
	@ $(CC) $(CFLAGS) ${INCLUDE} -o test $(OBJ_TEST) -L$(LIBFT_DIR) -lft
	@ echo "$(BIBlue)"
	@ echo "                 _ _            "
	@ echo "                | | |           "
	@ echo " _ __ ___   __ _| | | ___   ___ "
	@ echo "| '_ \` _ \ / _\` | | |/ _ \ / __|"
	@ echo "| | | | | | (_| | | | (_) | (__ "
	@ echo "|_| |_| |_|\__,_|_|_|\___/ \___|"
	@ echo "$(NC)"

clean:
	@ echo "$(YELLOW)Cleaning in progress...$(NC)"
	@ rm -f $(OBJ) $(OBJ_TEST) libft_malloc_$(HOSTTYPE).so test
	@ make -sC $(LIBFT_DIR) clean
	@ echo "$(YELLOW)Cleaning completed$(NC)\n"

fclean: clean
	@ rm -rf libft_malloc.so obj
	@ make -sC $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re test