/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:56:07 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/03 16:57:22 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_monitor(t_param *param)
{
	int	i;
	int	status;

	i = 0;
	while (1)
	{
		status = pthread_join((param->thread)[i], NULL);
		if (status != 0)
			return (philo_print_thread_error(THREAD_JOIN, status));
		i++;
		if (i == param->num_of_philo)
			i = 0;
	}
	return (0);
}