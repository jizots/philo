/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:46:36 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/29 21:12:39 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_args		args;
	int			status;
	pthread_t	*thread;

	status = philo_analys_argv(ac, av, &args);
	if (status != 0)
		return (status);
	status = philo_create_philo(&thread, args.num_of_philo);
	if (status != 0)
		return (printf("Error: malloc\n"));
}