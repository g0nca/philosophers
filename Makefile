# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/26 11:42:21 by ggomes-v          #+#    #+#              #
#    Updated: 2025/09/26 15:44:35 by ggomes-v         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######################
## MAKE FILE BASICS ##
######################

NAME = philosophers
CC = cc 
CFLAGS = -Wall -Wextra -Werror

PHILO_SRCS := srcs/main.c \
				srcs/init_table.c \
				srcs/util.c \

PHILO_OBJS := $(PHILO_SRCS:.c=.o)

%.o: %.c
	@$(CC) -g $(CFLAGS) -c $< -o $@ -I./

######################
## MAKE FILE COLORS ##
######################


CLR_RMV         := \033[0m
RED                 := \033[1;31m
GREEN           := \033[1;32m
YELLOW          := \033[1;33m
BLUE            := \033[1;34m
CYAN            := \033[1;36m

######################
## MAKE FILE CONFIG ##
######################

all: $(NAME)

$(NAME):${PHILO_OBJS}
	@echo "$(GREEN)Linux Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
	$(CC) -o $(NAME) $(PHILO_OBJS) -pthread -g
	@echo "$(GREEN)$(NAME) Created ✔️ $(CLR_RMV)"

clean:
		@rm -f $(PHILO_OBJS)
		@echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)PHILO_OBJS ✔️"

fclean: clean
		@rm -f $(NAME)
		@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re: fclean all

.PHONY: all clean fclean re