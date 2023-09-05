/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:55:09 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/05 12:56:48 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_destory_mutex(pthread_mutex_t *forks, int num_of_mutex)
{
	int	i;

	i = 0;
	while (i < num_of_mutex)
	{
		pthread_mutex_destroy(&(forks[i]));
		i++;
	}
	free (forks);
}

int	str_cmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (philo_print_thread_error(GETTIMEOFDAY, -1));
	return (((time.tv_sec % 1000) * 1000) + (time.tv_usec / 1000));
}
