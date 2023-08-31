/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:52:19 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/31 20:07:23 by hotph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*-------includes-------*/
/*memset, printf, malloc, free, write, usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy,
pthread_mutex_lock, pthread_mutex_unlock*/
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

/*-------define-------*/
/*don't use global variables*/
# define NOT_ENOUGH_AV 1
# define TOO_MANY_AV 2
# define INVALID_MATRIX 3
# define INCLUDE_MINUS 4

/*-------typedef-------*/
typedef struct s_args
{
	int		num_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_of_must_eat;
}	t_args;

/*-------prototype-------*/
//analys_argv
int		philo_analys_argv(int ac, char *av[], t_args *args);
int		ft_isdigit(int c);
int		atoi_intmax(const char *str);
int		str_cmp(const char *s1, const char *s2);
//create_philo
int		philo_create_philo(pthread_t **thread, int num_of_philo);
//run_philo
int		philo_pick_up_fork();
int		philo_culc_time();
int		philo_print_incorrect_argv(int flag);
int		philo_print_state();
int		philo_destroy();

#endif