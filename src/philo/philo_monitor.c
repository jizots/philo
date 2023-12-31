/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:56:07 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/16 12:42:34 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_num_full(bool which)
{
	static int	num_of_full;

	if (which == true)
		return (num_of_full);
	else
		num_of_full += 1;
	return (0);
}

static bool	is_all_philo_full(t_param *param, t_monitor *monitor, int i)
{
	if (param->num_of_must_eat != -1)
	{
		pthread_mutex_lock(&(param->full));
		if (get_num_full(true) == param->num_of_philo)
		{
			pthread_mutex_unlock(&(param->full));
			philo_print_state(&(param->print_mutex), monitor[i].id_philo, FULL);
			return (true);
		}
		pthread_mutex_unlock(&(param->full));
	}
	return (false);
}

static int	culc_time(t_param *param, t_monitor *monitor)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < param->num_of_philo)
		{
			if (is_all_philo_full(param, monitor, i) == true)
				return (0);
			pthread_mutex_lock(&(param->get_time));
			if ((get_time() - monitor[i].last_time_eat) > param->time_to_die)
			{
				pthread_mutex_unlock(&(param->get_time));
				philo_print_state(&(param->print_mutex), monitor[i].id_philo,
					DEAD);
				return (1);
			}
			pthread_mutex_unlock(&(param->get_time));
			i++;
		}
	}
	return (0);
}

int	philo_monitor(t_param *param, t_monitor *monitor)
{
	int	status;
	int	i;

	status = culc_time(param, monitor);
	i = 0;
	while (i < param->num_of_philo)
	{
		pthread_detach(param->thread[i]);
		i++;
	}
	return (philo_free(param, monitor, status));
}
