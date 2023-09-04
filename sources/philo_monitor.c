/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:56:07 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/04 19:07:30 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	culc_time(int num_of_philo, int time_to_die, t_monitor *monitor, pthread_mutex_t *print_mutex)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < num_of_philo)
		{
// printf("last_time_eat: %ld\n", monitor[i]->last_time_eat);
			if ((get_time() - monitor[i].last_time_eat) >= time_to_die)
			{
				philo_print_state(print_mutex, monitor[i].id_philo, DEAD);
				return (1);
			}
			i++;
		}
	}
	return (0);
}

int	philo_monitor(t_param *param, t_monitor *monitor)
{
	int	status;
	int	i;

	status = culc_time(param->num_of_philo, param->time_to_die, monitor ,&(param->print_mutex));
	if (status != 0)
	{
		i = 0;
		while (i < param->num_of_philo)
		{
			pthread_detach(param->thread[i]);
			i++;
		}
		return (status);
	}
	return (0);
}
