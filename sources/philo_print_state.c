/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:14:07 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/03 16:58:08 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_print_incorrect_argv(int flag)
{
	if (flag == NOT_ENOUGH_AV)
		printf("Error: Not enough arguments\n");
	else if (flag == TOO_MANY_AV)
		printf("Error: Too many arguments\n");
	else if (flag == INVALID_MATRIX || flag == INCLUDE_MINUS)
		printf("Error: Number's must with in 0 to 2147483647\n");
	return (flag);
}

int	philo_print_init_error(int flag)
{
	if (flag == MALLOC_ERROR)
		printf("Error: malloc\n");
	else if (flag == MUTEX_ERROR)
		printf("Error: mutex\n");
	else if (flag == THREAD_ERROR)
		printf("Error: thread\n");
	return (flag);
}

//want to use strerror...(printf("Error: %s\n", strerror(error_no));)
int	philo_print_thread_error(int flag, int error_no)
{
	if (flag == MUTEX_LOCK)
		printf("Error: mutex_lock, errno: %d\n", error_no);
	else if (flag == MUTEX_UNLOCK)
		printf("Error: mutex_unlock, errno: %d\n", error_no);
	else if (flag == GETTIMEOFDAY)
		printf("Error: gettimeofday, errno: %d\n", error_no);
	else if (flag == THREAD_JOIN)
		printf("Error: thread_join, errno: %d\n", error_no);
	return (flag);
}

int	philo_print_state(pthread_mutex_t *print, int no_philo, int flag)
{
	static int		flag_dead;
	int 			status;
	struct timeval	time;
	struct timezone	timezone;

	status = pthread_mutex_lock(print);
	if (status != 0)
		return (philo_print_thread_error(MUTEX_LOCK, status));
	if (gettimeofday(&time, &timezone) == -1)
		return (philo_print_thread_error(GETTIMEOFDAY, errno));
	if (flag == EAT)
		printf("%d %d is eating\n", time.tv_usec, no_philo);
	else if (flag == SLEEP)
		printf("%d %d is sleeping\n", time.tv_usec, no_philo);
	else if (flag == THINK)
		printf("%d %d is thinking\n", time.tv_usec, no_philo);
	else if (flag == DEAD)
	{
		printf("%d %d died\n", time.tv_usec, no_philo);
		flag_dead = 1;
	}
	else if (flag == PICK_UP)
		printf("%d %d has taken a fork\n", time.tv_usec, no_philo);
	status = pthread_mutex_unlock(print);
	if (status != 0)
		return (philo_print_thread_error(MUTEX_UNLOCK, status));
	return (0);
}
