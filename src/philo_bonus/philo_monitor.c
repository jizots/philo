/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 13:26:31 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/08 13:54:41 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

static bool	is_philo_full(t_monitor *mnt)
{
	if (mnt->num_of_must_eat != -1)
	{
		if (mnt->num_of_eat == mnt->num_of_must_eat)
		{
			philo_print_state(mnt->print_sem, mnt->id_philo, FULL);
			return (true);
		}
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
			if (status != 0)
				exit (status);
			exit (0);
		}
		if ((get_time() - mnt->last_time_eat) > mnt->time_to_die)
			philo_print_state(mnt->print_sem, mnt->id_philo, DEAD);
	}
	return (0);
}

int	philo_create_monitor_thread(t_monitor *mnt)
{
	int	status;

	status = pthread_create(&mnt->monitor_death, NULL,
			(void *)philo_monitor, (void *)mnt);
	if (status != 0)
		return (philo_print_with_errno(THREAD_ERROR, status));
	return (0);
}
