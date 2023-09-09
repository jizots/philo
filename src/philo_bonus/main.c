/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:46:36 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/09 12:40:08 by hotph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

/*May depend on environment.
 If program was terminated by signal, opened sem data will remain memory.
 And, if sem_post dose not complete before signal, 
 sem_wait of new program can't seccess at all.*/
static void	init_program(void)
{
	sem_unlink("forks");
	sem_unlink("cordinator");
	sem_unlink("print_sem");
}

int	main(int ac, char *av[])
{
	t_param		param;
	int			status;

	init_program();
	status = philo_analys_argv(ac, av, &param);
	if (status != 0)
		return (status);
	status = philo_create_semaphore(&param);
	if (status != 0)
		return (status);
	status = philo_create_philo(&param);
	if (status != 0)
	{
		philo_destroy_semaphore(&param);
		return (status);
	}
	return (0);
}

// __attribute__((destructor))
// static void	destructor(void)
// {
// 	system("leaks -q philo");
// }
