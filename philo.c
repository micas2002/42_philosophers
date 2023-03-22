/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:39:24 by mibernar          #+#    #+#             */
/*   Updated: 2022/12/05 11:50:08 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_end(t_seat *seat)
{
	pthread_mutex_lock(seat->died);
	if (seat->mutual_info->philo_died == 1)
	{
		pthread_mutex_unlock(seat->died);
		return (0);
	}
	seat->timestamp = get_time() - seat->start_time;
	if ((seat->timestamp - seat->last_meal) > seat->time_to_die)
	{
		printf("[%lld] %d %s\n", seat->timestamp, seat->id, "has died");
		seat->mutual_info->philo_died = 1;
		pthread_mutex_unlock(seat->died);
		return (0);
	}
	pthread_mutex_unlock(seat->died);
	return (1);
}

void	routine(t_seat *seat)
{
	while (check_end(seat) == 1)
	{
		if (take_fork(seat) == 0)
			return ;
		if (philo_eat(seat) == 0)
			return ;
		if (philo_sleep(seat) == 0)
			return ;
		if (philo_think(seat) == 0)
			return ;
	}
}

void	*actions(void *arg)
{
	t_seat	*seat;

	seat = (t_seat *)arg;
	if (seat->nb_philo == 1)
	{
		philo_think(seat);
		while (check_end(seat) == 1)
			;
	}
	if (seat->id % 2)
	{
		philo_think(seat);
		usleep(150);
	}
	routine(seat);
	return (NULL);
}

int	dinner(t_vars *vars)
{
	int	i;

	i = -1;
	vars->start_time = get_time();
	while (++i < vars->nb_philo)
	{
		vars->seats[i].start_time = vars->start_time;
		if (pthread_create(&vars->seats[i].philo, NULL, &actions,
				&vars->seats[i]) != 0)
			return (0);
	}
	i = -1;
	while (++i < vars->nb_philo)
	{
		if (pthread_join(vars->seats[i].philo, NULL) != 0)
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	static t_vars	*vars;

	if (argc < 5 || argc > 6)
	{
		printf("INVALID INPUT\n");
		return (1);
	}
	vars = malloc(sizeof(t_vars));
	if (init_vars(vars, argc, argv) == 0)
		return (1);
	if (prepare_seats(vars) == 0 || prepare_forks(vars) == 0)
		return (1);
	if (dinner(vars) == 0)
		return (1);
	free_vars(vars);
	return (0);
}
