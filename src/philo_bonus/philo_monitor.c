/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 13:26:31 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/16 18:13:30 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

static bool	is_philo_full(t_monitor *mnt)
{
	if (mnt->num_of_must_eat != -1)
	{
		sem_wait(mnt->times_eat);
		if (mnt->num_of_eat == mnt->num_of_must_eat)
		{
			sem_post(mnt->times_eat);
			philo_print_state(mnt->print_sem, mnt->id_philo, FULL);
			return (true);
		}
		sem_post(mnt->times_eat);
	}
	return (false);
}

static int	philo_monitor(t_monitor *mnt)
{
	int	status;

	while (1)
	{
		if (is_philo_full(mnt) == true)
		{
			status = philo_drop_forks(mnt->forks, mnt->cordinator);
			free(mnt->last_time_eat);
			if (status != 0)
				exit (status);
			exit (0);
		}
		if (sem_wait(mnt->get_time) == -1)
			philo_print_basic_error(SEM_ERROR);
		if ((get_time() - *(mnt->last_time_eat)) > mnt->time_to_die)
		{
			sem_post(mnt->get_time);
			philo_print_state(mnt->print_sem, mnt->id_philo, DEAD);
		}
		sem_post(mnt->get_time);
	}
	return (0);
}

int	philo_create_monitor_thread(t_monitor *mnt)
{
	int	status;

	status = pthread_create(&(mnt->monitor_death), NULL,
			(void *)philo_monitor, (void *)mnt);
	if (status != 0)
		return (philo_print_with_errno(THREAD_ERROR, status));
	return (0);
}
