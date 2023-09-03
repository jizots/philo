/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start_party.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 20:27:44 by hotph             #+#    #+#             */
/*   Updated: 2023/09/03 16:43:42 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	pick_up_fork(int flag, pthread_mutex_t *fork_left, pthread_mutex_t *fork_right, t_param *param)
{
	int	status;

	if (flag == 0)
	{
		status = pthread_mutex_lock(fork_left);
		if (status != 0)
			return (philo_print_thread_error(MUTEX_LOCK, status));
		status = philo_print_state(&(param->print_mutex), param->no_philo, PICK_UP);
		if (status != 0)
			return (status);
		status = pthread_mutex_lock(fork_right);
		if (status != 0)
			return (philo_print_thread_error(MUTEX_LOCK, status));
		status = philo_print_state(&(param->print_mutex), param->no_philo, PICK_UP);
		if (status != 0)
			return (status);
	}
	else
	{
		status = pthread_mutex_lock(fork_right);
		if (status != 0)
			return (philo_print_thread_error(MUTEX_LOCK, status));
		status = philo_print_state(&(param->print_mutex), param->no_philo, PICK_UP);
		if (status != 0)
			return (status);
		status = pthread_mutex_lock(fork_left);
		if (status != 0)
			return (philo_print_thread_error(MUTEX_LOCK, status));
		status = philo_print_state(&(param->print_mutex), param->no_philo, PICK_UP);
		if (status != 0)
			return (status);
	}
	return (0);
}

static int	drop_off_fork(pthread_mutex_t *fork_left, pthread_mutex_t *fork_right)
{
	int	status;

	status = pthread_mutex_unlock(fork_left);
	if (status != 0)
		return (philo_print_thread_error(MUTEX_UNLOCK, status));
	status = pthread_mutex_unlock(fork_right);
	if (status != 0)
		return (philo_print_thread_error(MUTEX_UNLOCK, status));
	return (0);
}

int	philo_start_party(t_param *param)
{
	int				status;
	// struct timeval	time;

	while (1)
	{
		if (param->no_philo % 2 == 0)
			status = pick_up_fork(0, param->fork_left, param->fork_right ,param);
		else
			status = pick_up_fork(1, param->fork_left, param->fork_right, param);
		if (status != 0)
			return (status);//add recieve error & do something
		status = philo_print_state(&(param->print_mutex), param->no_philo, EAT);
		if (status != 0)
			return (status);
		usleep(param->time_to_eat * 1000);
		status = drop_off_fork(param->fork_left, param->fork_right);
		if (status != 0)
			return (status);//add recieve error & do something
		status = philo_print_state(&(param->print_mutex), param->no_philo, SLEEP);
		if (status != 0)
			return (status);
		usleep(param->time_to_sleep * 1000);
		status = philo_print_state(&(param->print_mutex), param->no_philo, THINK);
		if (status != 0)
			return (status);
	}	
	return (0);
}
