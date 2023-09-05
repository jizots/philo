# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/03 16:30:18 by sotanaka          #+#    #+#              #
#    Updated: 2023/09/05 12:56:58 by sotanaka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -I${INCLUDES_DIR} -pthread

SRCS = main.c philo_analys_argv.c philo_create_mutex.c philo_create_philo.c\
		philo_start_party.c philo_print_state.c philo_monitor.c philo_utils.c\
		atoi_intmax.c ft_isdigit.c\

SRCS_DIR = sources/
INCLUDES_DIR = includes/

OBJS = ${addprefix ${SRCS_DIR}, ${SRCS:%.c=%.o}}

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS}

clean: 
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all