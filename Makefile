# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/31 14:29:47 by hubourge          #+#    #+#              #
#    Updated: 2025/01/06 18:03:41 by hubourge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX			= gcc

# -Wpadded now if a structure is padded, it will be detected
# -Wall -Wextra -Werror
# strace a.out
CFLAGS		=  -Wall -Wextra -Werror -fPIC -g
INCLUDE		= -I includes

LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

OBJ_DIR		= obj

SRC			=	srcs/malloc/malloc.c \
				srcs/malloc/allocation.c \
				srcs/malloc/init.c \
				srcs/free/free.c \
				srcs/show_alloc_mem/show_alloc_mem.c \
				srcs/show_alloc_mem/show_alloc_debug.c \
				srcs/utils/align.c \
				srcs/utils/find_address.c \

OBJ			= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

SRC_TEST	= $(SRC) \
			srcs/main.c
				
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
	@ $(CXX) $(CFLAGS) ${INCLUDE} -c $< -o $@

libft_malloc_$(HOSTTYPE).so: $(OBJ)
	@ echo "$(YELLOW)Compiling objects...$(NC)"
	@ echo "$(YELLOW)Creating libft_malloc_$(HOSTTYPE).so...$(NC)"
	@ $(CXX) $(CFLAGS) ${INCLUDE} -shared -o $@ $(OBJ)

test: fclean $(LIBFT) $(OBJ_TEST)
	@ echo "$(YELLOW)Compiling objects...$(NC)"
	@ $(CXX) $(CFLAGS) ${INCLUDE} -o test $(OBJ_TEST) -L$(LIBFT_DIR) -lft
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
	@ rm -rf $(OBJ) $(OBJ_TEST) obj test
	@ make -sC $(LIBFT_DIR) clean
	@ echo "$(YELLOW)Cleaning completed$(NC)\n"

fclean: clean
	@ rm -rf libft_malloc.so libft_malloc_$(HOSTTYPE).so a.out
	@ make -sC $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re test