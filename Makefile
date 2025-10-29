# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/26 11:42:21 by ggomes-v          #+#    #+#              #
#    Updated: 2025/10/29 11:33:50 by ggomes-v         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######################
## MAKE FILE BASICS ##
######################

NAME        = philosophers
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
OBJ_DIR     = obj

PHILO_SRCS  := srcs/main.c \
               srcs/init_table.c \
               srcs/util.c \
			   srcs/philosophing.c \
			   srcs/philosophing_utils.c \
			   srcs/philos_monitor.c \
			   srcs/check_args.c
PHILO_OBJS  := $(PHILO_SRCS:srcs/%.c=$(OBJ_DIR)/%.o)

######################
## MAKE FILE COLORS ##
######################

CLR_RMV     := \033[0m
RED         := \033[1;31m
GREEN       := \033[1;32m
YELLOW      := \033[1;33m
CYAN        := \033[1;36m

######################
## MAKE RULES ##
######################

all: $(NAME)

$(OBJ_DIR)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	@$(CC) -g $(CFLAGS) -c $< -o $@ -I./
	@echo "$(CYAN)Compiled$(CLR_RMV): $<"

$(NAME): $(PHILO_OBJS)
	@echo "$(GREEN)Linux Compilation$(CLR_RMV) of $(YELLOW)$(NAME)$(CLR_RMV)..."
	@$(CC) $(PHILO_OBJS) -pthread -o $(NAME)
	@echo "$(GREEN)$(NAME) Created ✔️$(CLR_RMV)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Deleted object files and folder $(CYAN)$(OBJ_DIR)/$(CLR_RMV) ✔️"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)Deleted binary $(CYAN)$(NAME)$(CLR_RMV) ✔️"

re: fclean all

.PHONY: all clean fclean re
