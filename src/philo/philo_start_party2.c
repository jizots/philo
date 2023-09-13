/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start_party2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:50:28 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/13 17:18:30 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	usleep_precisely(int microseconds)
{
	long	start_time;
	long	current_time;

	start_time = get_time_usec();
	current_time = start_time;
	while (current_time - start_time < microseconds)
	{
		usleep(30);
		current_time = get_time_usec();
	}
}

void	is_teetime(int eat, int sleep)
{
	if (eat >= sleep)
	{
		usleep((eat - sleep) * 1000);
		usleep(100);
	}
}
