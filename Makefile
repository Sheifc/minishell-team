
LIBFT_DIR		= libft/
LIBS			= -lft -lreadline

NAME			= minishell

CC				= gcc
CFLAGS			= -Wall -Werror -Wextra -Iincludes -g #-fsanitize=address
#LDFLAGS         = -fsanitize=address
RM				= rm -rf

SRC_DIR			= src/
EXEC_DIR		= $(SRC_DIR)executor/
PARSER_DIR		= $(SRC_DIR)parser/
OBJ_DIR			= obj/
OBJ_EXEC_DIR	= $(OBJ_DIR)executor/
OBJ_PARSER_DIR	= $(OBJ_DIR)parser/

FILES_EXEC		= exec_main.c exec_builtins.c exec_utils.c \
				free.c list_utils.c key_value.c \
				echo.c pwd.c cd.c env.c  exit.c \
				export.c unset.c executor.c path.c \
				error.c printing.c \

FILES_PARSER	= test.c

SRC_EXEC 		= $(addprefix $(EXEC_DIR),$(FILES_EXEC))
SRC_PARSER 		= $(addprefix $(PARSER_DIR),$(FILES_PARSER))
SRC 			= $(SRC_EXEC) $(SRC_PARSER)
OBJ_EXEC 		= $(SRC_EXEC:$(EXEC_DIR)%.c=$(OBJ_EXEC_DIR)%.o)
OBJ_PARSER 		= $(SRC_PARSER:$(PARSER_DIR)%.c=$(OBJ_PARSER_DIR)%.o)
OBJ_SRC 		= $(OBJ_EXEC) $(OBJ_PARSER)

vpath %.c $(SRC_DIR) $(EXEC_DIR) $(PARSER_DIR)

$(OBJ_EXEC_DIR)%.o: $(EXEC_DIR)%.c
	@mkdir -p $(OBJ_EXEC_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PARSER_DIR)%.o: $(PARSER_DIR)%.c
	@mkdir -p $(OBJ_PARSER_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ_SRC)
	@$(MAKE) -s all bonus printf gnl -C $(LIBFT_DIR)
	$(CC) $(OBJ_SRC) -L $(LIBFT_DIR) $(LIBS) $(LDFLAGS) -o $@

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re