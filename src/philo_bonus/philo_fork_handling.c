/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork_handling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:43:22 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/08 13:50:17 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

int	philo_drop_forks(sem_t *forks, sem_t *cordinator)
{
	if (sem_post(forks) != 0)
		return (philo_print_basic_error(SEM_ERROR));
	if (sem_post(forks) != 0)
		return (philo_print_basic_error(SEM_ERROR));
	if (sem_post(cordinator) != 0)
		return (philo_print_basic_error(SEM_ERROR));
	return (0);
}
