/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:52:12 by mibernar          #+#    #+#             */
/*   Updated: 2022/12/05 11:55:24 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_fork_mss(t_seat *seat)
{
	pthread_mutex_lock(seat->message);
	seat->timestamp = get_time() - seat->start_time;
	printf("[%lld] %d %s\n", seat->timestamp, seat->id, "has taken a fork");
	printf("[%lld] %d %s\n", seat->timestamp, seat->id, "has taken a fork");
	pthread_mutex_unlock(seat->message);
}

int	take_fork(t_seat *seat)
{
	if (check_end(seat) == 1)
	{
		while (*seat->l_taken == 1 || *seat->r_taken == 1)
		{
			if (check_end(seat) == 0)
				return (0);
		}
		if (seat->id % 2 == 0)
		{
			pthread_mutex_lock(seat->right_fork);
			pthread_mutex_lock(seat->left_fork);
		}
		else
		{
			pthread_mutex_lock(seat->left_fork);
			pthread_mutex_lock(seat->right_fork);
		}
		*seat->l_taken = 1;
		*seat->r_taken = 1;
		print_fork_mss(seat);
		return (1);
	}
	return (0);
}

int	philo_eat(t_seat *seat)
{
	if (check_end(seat) == 1)
	{
		pthread_mutex_lock(seat->message);
		seat->timestamp = get_time() - seat->start_time;
		printf("[%lld] %d %s\n", seat->timestamp, seat->id, "is eating");
		seat->last_meal = seat->timestamp;
		seat->meals--;
		pthread_mutex_unlock(seat->message);
		usleep(seat->time_to_eat * 1000);
		pthread_mutex_unlock(seat->left_fork);
		*seat->l_taken = 0;
		usleep(1000);
		pthread_mutex_unlock(seat->right_fork);
		*seat->r_taken = 0;
		if (check_end(seat) == 1 && seat->bonus_arg == 1 && seat->meals == 0)
			return (0);
		return (1);
	}
	pthread_mutex_unlock(seat->right_fork);
	pthread_mutex_unlock(seat->left_fork);
	return (0);
}

int	philo_sleep(t_seat *seat)
{
	if (check_end(seat) == 1)
	{
		pthread_mutex_lock(seat->message);
		seat->timestamp = get_time() - seat->start_time;
		printf("[%lld] %d %s\n", seat->timestamp, seat->id, "is sleeping");
		pthread_mutex_unlock(seat->message);
		usleep(seat->time_to_sleep * 1000);
		return (1);
	}
	return (0);
}

int	philo_think(t_seat *seat)
{
	if (check_end(seat) == 1)
	{
		pthread_mutex_lock(seat->message);
		seat->timestamp = get_time() - seat->start_time;
		printf("[%lld] %d %s\n", seat->timestamp, seat->id, "is thinking");
		pthread_mutex_unlock(seat->message);
		return (1);
	}
	return (0);
}
