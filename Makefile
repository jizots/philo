# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/03 16:30:18 by sotanaka          #+#    #+#              #
#    Updated: 2023/09/05 14:10:25 by sotanaka         ###   ########.fr        #
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
OBJS_DIR = objs/

OBJS = ${addprefix ${OBJS_DIR}, ${SRCS:%.c=%.o}}

all: ${OBJS_DIR} ${NAME}

${OBJS_DIR}:
	mkdir -p ${OBJS_DIR}

${OBJS_DIR}%.o: ${SRCS_DIR}%.c | ${OBJS_DIR}
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS}

clean: 
	rm -f ${OBJS}
	rmdir ${OBJS_DIR}

fclean: clean
	rm -f ${NAME}

re: fclean all