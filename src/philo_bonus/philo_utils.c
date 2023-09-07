/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:55:09 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/07 16:56:13 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

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
		return (philo_print_with_errno(GETTIMEOFDAY, -1));
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long	get_time_usec(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (philo_print_with_errno(GETTIMEOFDAY, -1));
	return (time.tv_sec * 1000000 + time.tv_usec);
}

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
