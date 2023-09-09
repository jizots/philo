/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:14:07 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/09 10:11:28 by hotph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

int	philo_print_incorrect_argv(int flag)
{
	if (flag == NOT_ENOUGH_AV)
		printf("Error: Not enough arguments\n");
	else if (flag == TOO_MANY_AV)
		printf("Error: Too many arguments\n");
	else if (flag == INVALID_MATRIX || flag == INCLUDE_MINUS)
		printf("Error: Number's must with in 0 to 2147483647\n");
	else if (flag == ZERO_PHILO)
		printf("Error: Number of philosophers must be greater than 0\n");
	else if (flag == ZERO_MUST_EAT)
		printf("Must eat zero: All philosopher are already full\n");
	return (flag);
}

int	philo_print_basic_error(int flag)
{
	if (flag == SEM_ERROR)
		printf("Error: sem: errno %d\n", errno);
	else if (flag == MALLOC_ERROR)
		printf("Error: malloc: errno %d\n", errno);
	else if (flag == FORK_ERROR)
		printf("Error: fork: errno %d\n", errno);
	else if (flag == GETTIMEOFDAY)
		printf("Error: gettimeofday: errno %d\n", errno);
	else if (flag == KILL_ERROR)
		printf("Error: kill: errno %d\n", errno);
	else if (flag == WAIT_ERROR)
		printf("Error: wait: errno %d\n", errno);
	return (flag);
}

int	philo_print_with_errno(int flag, int error_no)
{
	if (flag == THREAD_ERROR)
		printf("Error: thread join: errno %d\n", error_no);
	return (flag);
}

void	print_state(int id_philo, int flag)
{
	long	time;

	if (flag == EAT)
	{
		time = get_time();
		printf("%ld %3d has taken a fork\n", time, id_philo);
		printf("%ld %3d is eating\n", time, id_philo);
	}
	else if (flag == SLEEP)
		printf("%ld %3d is sleeping\n", get_time(), id_philo);
	else if (flag == THINK)
		printf("%ld %3d is thinking\n", get_time(), id_philo);
	else if (flag == DEAD)
		printf("%ld %3d died\n", get_time(), id_philo);
	else if (flag == PICK_UP)
		printf("%ld %3d has taken a fork\n", get_time(), id_philo);
	else if (flag == FULL)
		printf("%ld %3d is full\n", get_time(), id_philo);
}

int	philo_print_state(sem_t *print, int id_philo, int flag)
{
	int	status;

	status = sem_wait(print);
	if (status != 0)
		return (philo_print_basic_error(SEM_ERROR));
	print_state(id_philo, flag);
	if (flag == DEAD)
		exit (DEAD);
	status = sem_post(print);
	if (status != 0)
		return (philo_print_basic_error(SEM_ERROR));
	return (0);
}
