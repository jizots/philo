/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:46:36 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/06 11:43:21 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

void	init_param(t_param *param)
{
	param->num_of_philo = 0;
	param->time_to_die = 0;
	param->time_to_eat = 0;
	param->time_to_sleep = 0;
	param->num_of_must_eat = -1;
}

int	main(int ac, char *av[])
{
	t_param		param;
	t_philo		*philo;
	t_monitor	*mnt;
	int			status;

	init_param(&param);
	status = philo_analys_argv(ac, av, &param);
	if (status != 0)
		return (status);

	return (0);
}

__attribute__((destructor))
static void	destructor(void)
{
	system("leaks -q philo");
}
