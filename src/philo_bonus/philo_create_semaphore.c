/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create_semaphore.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:23:56 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/06 13:56:33 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

int	philo_create_semaphore(t_param *param)
{
	param->forks = sem_open("forks", 
		O_CREAT, S_IRUSR | S_IWUSR, param->num_of_philo);
	if (param->forks == SEM_FAILED)
		return (philo_print_basic_error(SEM_ERROR));
	param->print_sem = sem_open("print_sem", 
		O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (param->print_sem == SEM_FAILED)
	{
		sem_close_and_unlink(param->forks, "forks");
		return (philo_print_basic_error(SEM_ERROR));
	}
}
