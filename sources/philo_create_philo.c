/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create_philo.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:07:06 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/29 21:25:26 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		philo_create_philo(pthread_t **thread, int num_of_philo)
{
	int	i;
	int	status;

	i = 0;
	*thread = malloc(sizeof(pthread_t) * num_of_philo);
	if (*thread == NULL)
		return (1);
	while (i < num_of_philo)
	{
		status = pthread_create(&(*thread)[i], NULL, philo_pick_up_fork, NULL);
		if (status != 0)
		{
			free (*thread);
			return (print_base_errno(status));
		}
		i++;
	}
	return (0);
}
