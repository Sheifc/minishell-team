# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/02 13:51:00 by sheferna          #+#    #+#              #
#    Updated: 2024/04/02 13:39:07 by sheferna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 				= libft.a
CC 					= gcc
CFLAGS 				= -Wall -Werror -Wextra -Iincludes
RM					= rm -rf
AR					= ar rcs

SRC_DIR 			= src/
OBJ_DIR				= obj/

SRC_DIR_BONUS        = src_bonus/
OBJ_DIR_BONUS        = obj_bonus/

SRC_DIR_PRINTF		= src_printf/
OBJ_DIR_PRINTF		= obj_printf/

SRC_DIR_GNL			= src_gnl/
OBJ_DIR_GNL			= obj_gnl/

FILES_SRC 			= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
					ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
    				ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
					ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c\
					ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
					ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
					ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
					ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
					ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
					ft_atol.c ft_isspace.c ft_strtok.c ft_free_matrix.c \

FILES_BONUS 		= ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
					ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
					ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c \

FILES_PRINTF 		= ft_printf.c ft_printf_utils.c \

FILES_GNL 			= get_next_line_bonus.c get_next_line_utils_bonus.c \

SRC 				= $(addprefix $(SRC_DIR),$(FILES_SRC))
OBJ_SRC 			= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

SRC_BONUS 			= $(addprefix $(SRC_DIR_BONUS),$(FILES_BONUS))
OBJ_BONUS 			= $(SRC_BONUS:$(SRC_DIR_BONUS)%.c=$(OBJ_DIR_BONUS)%.o)

SRC_PRINTF 			= $(addprefix $(SRC_DIR_PRINTF),$(FILES_PRINTF))
OBJ_PRINTF 			= $(SRC_PRINTF:$(SRC_DIR_PRINTF)%.c=$(OBJ_DIR_PRINTF)%.o)

SRC_GNL 			= $(addprefix $(SRC_DIR_GNL),$(FILES_GNL))
OBJ_GNL 			= $(SRC_GNL:$(SRC_DIR_GNL)%.c=$(OBJ_DIR_GNL)%.o)

vpath %.c $(SRC_DIR) $(SRC_DIR_BONUS) $(SRC_DIR_PRINTF) $(SRC_DIR_GNL)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_BONUS)%.o: $(SRC_DIR_BONUS)%.c
	@mkdir -p $(OBJ_DIR_BONUS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_PRINTF)%.o: $(SRC_DIR_PRINTF)%.c
	@mkdir -p $(OBJ_DIR_PRINTF)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_GNL)%.o: $(SRC_DIR_GNL)%.c
	@mkdir -p $(OBJ_DIR_GNL)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ_SRC)
	$(AR) $(NAME) $(OBJ_SRC)

bonus: $(OBJ_SRC) $(OBJ_BONUS)
	$(AR) $(NAME) $(OBJ_SRC) $(OBJ_BONUS)

printf: $(OBJ_SRC) $(OBJ_PRINTF)
	$(AR) $(NAME) $(OBJ_SRC) $(OBJ_PRINTF)

gnl: $(OBJ_SRC) $(OBJ_GNL)
	$(AR) $(NAME) $(OBJ_SRC) $(OBJ_GNL)

clean:
	@$(RM) $(OBJ_DIR) $(OBJ_DIR_BONUS) $(OBJ_DIR_PRINTF) $(OBJ_DIR_GNL)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus printf gnl