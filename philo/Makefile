# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nakanoun <nakanoun@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/06/22 23:25:48 by nakanoun      #+#    #+#                  #
#    Updated: 2023/06/22 23:25:48 by nakanoun      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	:= philo
CFLAGS	:= -Wall -Wextra -Werror #-g -fsanitize=thread 

#Directories
OBJ_DIR	:= obj

HEADERS	:= -I include
SRCS	:= $(shell find ./src -iname "*.c")
OBJS	:= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all	:	$(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<

$(NAME):	$(OBJS)
	@$(CC) $(CFLAGS) $(HEADERS) $(OBJS) -o $(NAME)
	@printf "Compiled ./philo executable succesfully.\n"

clean :
	@rm -rf $(OBJ_DIR)
	@printf "Removed .o files successfully.\n"

fclean : clean
	rm -rf $(NAME)
	@printf "Removed $(NAME) executable successfully.\n"

re : fclean all

.PHONY: all clean fclean re
	