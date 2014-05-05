# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jponcele <jponcele@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/27 12:29:52 by jponcele          #+#    #+#              #
#    Updated: 2014/05/02 15:03:56 by jponcele         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_script

DIRSRC = ./srcs/
DIROBJ = ./obj/

SRC = ft_script.c\
	  ft_script_err.c\
	  ft_script_init.c\
	  ft_script_term.c\
	  ptyfork.c\
	  ptyopen.c\
	  get_shell.c

OBJ = $(SRC:.c=.o)

DIROBJS = $(addprefix $(DIROBJ), $(OBJ))

LFT = -L ./libft/ -lft

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

HEAD = -I ./includes -I ./libft/includes/

all: $(NAME)

$(NAME): $(DIROBJS)
	@$(MAKE) -C ./libft
	@printf 'Compiling ./%s binaries : [\033[32mDONE\033[0m]\n' '$(NAME)'
	@$(CC) $(CFLAGS) -o $@ $^ $(HEAD) $(LFT) $(LTERM)
	@printf 'Compiling ./%s : [\033[32mDONE\033[0m]\n' '$(NAME)'

$(DIROBJ)%.o: $(DIRSRC)%.c
	@mkdir -p obj
	@$(CC) $(CFLAGS) -c $^ $(HEAD) -o $@

clean:
	@rm -rf $(DIROBJ)
	@printf 'Clean %s : [\033[32mDONE\033[0m]\n' '$(NAME)'
	@$(MAKE) clean -C ./libft

fclean: clean
	@$(RM) $(RFLAGS) $(NAME)
	@printf 'Fclean %s : [\033[32mDONE\033[0m]\n' '$(NAME)'
	@$(MAKE) fclean -C ./libft

re : fclean all

.PHONY: all clean fclean re
