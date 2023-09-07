# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/03 16:30:18 by sotanaka          #+#    #+#              #
#    Updated: 2023/09/07 19:38:05 by sotanaka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
BNAME = bonus_philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -I${INCLUDES_DIR} -pthread

SRCS = main.c philo_analys_argv.c philo_create_mutex.c philo_create_philo.c\
		philo_start_party.c philo_print_state.c philo_monitor.c philo_utils.c\
		atoi_intmax.c ft_isdigit.c\

BSRCS = main.c philo_analys_argv.c philo_create_semaphore.c philo_create_philo.c\
		philo_start_party.c philo_print_state.c philo_monitor.c philo_utils.c\
		philo_destroy.c\
		atoi_intmax.c ft_isdigit.c\

SRCS_DIR = src/philo/
BSRCS_DIR = src/philo_bonus/
INCLUDES_DIR = includes/
OBJS_DIR = objs/
BOBJS_DIR = bobjs/

OBJS = ${addprefix ${OBJS_DIR}, ${SRCS:%.c=%.o}}
BOBJS = ${addprefix ${BOBJS_DIR}, ${BSRCS:%.c=%.o}}

bonus:
	$(eval NAME := $(BNAME))
	$(eval SRCS_DIR := $(BSRCS_DIR))
	$(eval OBJS_DIR := $(BOBJS_DIR))
	$(eval OBJS := $(BOBJS))
	$(MAKE) all

all: ${OBJS_DIR} ${NAME}

${OBJS_DIR}:
	mkdir -p ${OBJS_DIR}

${OBJS_DIR}%.o: ${SRCS_DIR}%.c | ${OBJS_DIR}
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS}

clean: 
	rm -f ${OBJS}
	rmdir ${OBJS_DIR} 2>/dev/null || true
	rm -f ${BOBJS}
	rmdir ${BOBJS_DIR} 2>/dev/null || true

fclean: clean
	rm -f ${NAME}
	rm -f ${BNAME}

re: fclean all
