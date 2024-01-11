NAME		=	pipex

CC			=	cc

FLAG		=	-Wall -Wextra -Werror -g3

LIBFT_PATH	=	./libft/

LIBFT_FILE	=	libft.a

LIBFT_LIB	=	$(addprefix $(LIBFT_PATH), $(LIBFT_FILE))

SRC			=	pipex.c \
				pipex_utils.c 

INC_DIR		=	./

OBJ			=	$(SRC:.c=.o)

.c.o:
	$(CC) $(FLAG) -I $(INC_DIR) -c $< -o $@

all: lib $(NAME) 

lib:
	@echo "\033[0;33m\nCOMPILING $(LIBFT_PATH)\n"
	@make -C $(LIBFT_PATH)
	@echo "\033[1;32mLIBFT_lib created\n"

$(NAME): $(OBJ)
	@echo "\033[0;33m\nCOMPILING pipex...\n"
	$(CC) $(OBJ) $(LIBFT_LIB) -o $(NAME)
	@echo "\033[1;32m./pipex created\n"

clean:
	@echo "\033[0;31mDeleting Obj file in $(LIBFT_PATH)...\n"
	@make clean -sC $(LIBFT_PATH)
	@rm -f $(OBJ) $(OBJB)
	@echo "\033[1;32mDone\n"

fclean: clean
	@echo "\033[0;31mDeleting pipex executable..."
	@rm -f $(NAME) pipex
	@make fclean -C $(LIBFT_PATH)
	@echo "\033[1;32mDone\n"

re: fclean all

.PHONY: all clean fclean re bonus