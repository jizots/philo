/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start_party.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:19:26 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/16 17:25:29 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

static void	init_monitor(t_monitor *mnt, t_param *param, int id_philo)
{
	mnt->id_philo = id_philo;
	mnt->time_to_die = param->time_to_die;
	mnt->num_of_eat = 0;
	mnt->num_of_must_eat = param->num_of_must_eat;
	mnt->forks = param->forks;
	mnt->cordinator = param->cordinator;
	mnt->print_sem = param->print_sem;
	mnt->get_time = param->get_time;
	mnt->times_eat = param->times_eat;
	mnt->last_time_eat = malloc(sizeof(long) * 1);
	if (mnt->last_time_eat == NULL)
		exit (philo_print_basic_error(MALLOC_ERROR));
	*(mnt->last_time_eat) = get_time();
}

static int	pick_forks(t_param *param, t_monitor *mnt)
{
	if (sem_wait(param->cordinator) == -1)
		return (philo_print_basic_error(SEM_ERROR));
	if (sem_wait(param->forks) == -1)
		return (philo_print_basic_error(SEM_ERROR));
	philo_print_state(param->print_sem, mnt->id_philo, PICK_UP);
	if (sem_wait(param->forks) == -1)
		return (philo_print_basic_error(SEM_ERROR));
	if (sem_wait(mnt->get_time) == -1)
		return (philo_print_basic_error(SEM_ERROR));
	*(mnt->last_time_eat) = get_time();
	if (sem_post(mnt->get_time) == -1)
		return (philo_print_basic_error(SEM_ERROR));
	return (0);
}

static void	p_eat(t_param *param, t_monitor *mnt)
{
	philo_print_state(param->print_sem, mnt->id_philo, EAT);
	usleep_precisely(param->time_to_eat * 1000);
}

static int	p_sleep(t_param *param, t_monitor *mnt)
{
	int	status;

	status = philo_drop_forks(param->forks, param->cordinator);
	if (status != 0)
		return (status);
	if (sem_wait(mnt->times_eat) == -1)
		return (philo_print_basic_error(SEM_ERROR));
	mnt->num_of_eat += 1;
	if (sem_post(mnt->times_eat) == -1)
		return (philo_print_basic_error(SEM_ERROR));
	philo_print_state(param->print_sem, mnt->id_philo, SLEEP);
	usleep_precisely(param->time_to_sleep * 1000);
	return (0);
}

int	philo_start_party(t_param *param, int id_philo)
{
	t_monitor	mnt;
	int			status;

	init_monitor(&mnt, param, id_philo);
	if (philo_create_monitor_thread(&mnt) != 0)
	{
		free(mnt.last_time_eat);
		exit (THREAD_ERROR);
	}
	while (1)
	{
		status = pick_forks(param, &mnt);
		if (status != 0)
			break ;
		p_eat(param, &mnt);
		status = p_sleep(param, &mnt);
		if (status != 0)
			break ;
		philo_print_state(param->print_sem, mnt.id_philo, THINK);
	}
	free(mnt.last_time_eat);
	exit (status);
}
