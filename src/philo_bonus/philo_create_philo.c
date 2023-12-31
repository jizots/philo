/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create_philo.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:31:40 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/08 14:42:06 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

static void	remove_pid(pid_t *pid, int num_of_philo, int pid_removal)
{
	int		i;

	i = 0;
	while (i < num_of_philo)
	{
		if (pid[i] == pid_removal)
			pid[i] = 0;
		i++;
	}
}

static int	wait_full(t_param *param)
{
	int	i;
	int	status;
	int	exited;

	i = 0;
	while (i < param->num_of_philo)
	{
		status = wait(&exited);
		if (status == -1)
		{
			philo_print_basic_error(WAIT_ERROR);
			break ;
		}
		remove_pid(param->pid, param->num_of_philo, status);
		if (WIFEXITED(exited) && WEXITSTATUS(exited) == 0)
			i++;
		else
			break ;
	}
	if (i == param->num_of_philo)
		printf("All philosophers are full\n");
	else
		return (kill_remain_philo(param->pid, param->num_of_philo));
	return (0);
}

static int	wait_death_someone(t_param *param)
{
	int	status;
	int	exited;

	status = wait(&exited);
	if (status == -1)
		(philo_print_basic_error(WAIT_ERROR));
	remove_pid(param->pid, param->num_of_philo, status);
	if (!WIFEXITED(exited))
		;
	return (kill_remain_philo(param->pid, param->num_of_philo));
}

static int	at_parent(t_param *param)
{
	int	status;

	if (param->num_of_must_eat != -1)
	{
		status = wait_full(param);
		free(param->pid);
	}
	else
	{
		status = wait_death_someone(param);
		free(param->pid);
	}
	return (status);
}

int	philo_create_philo(t_param *param)
{
	int		i;

	param->pid = malloc(sizeof(pid_t) * param->num_of_philo);
	if (param->pid == NULL)
		return (philo_print_basic_error(MALLOC_ERROR));
	i = 0;
	while (i < param->num_of_philo)
	{
		param->pid[i] = fork();
		if (param->pid[i] < 0)
		{
			free(param->pid);
			return (philo_print_basic_error(FORK_ERROR));
		}
		else if (param->pid[i] == 0)
			philo_start_party(param, i + 1);
		i++;
	}
	return (at_parent(param));
}
