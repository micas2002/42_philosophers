/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:02:25 by mibernar          #+#    #+#             */
/*   Updated: 2022/12/02 18:27:42 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	forks_loop(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < vars->nb_philo - 1)
	{
		vars->seats[i].left_fork = &vars->forks[i];
		vars->seats[i].right_fork = &vars->forks[i + 1];
	}
	vars->seats[i].left_fork = &vars->forks[i];
	vars->seats[i].right_fork = &vars->forks[0];
	i = -1;
	while (++i < vars->nb_philo - 1)
	{
		vars->seats[i].l_taken = &vars->f_taken[i];
		vars->seats[i].r_taken = &vars->f_taken[i + 1];
	}
	vars->seats[i].l_taken = &vars->f_taken[i];
	vars->seats[i].r_taken = &vars->f_taken[0];
}

int	prepare_forks(t_vars *vars)
{
	int	i;

	vars->forks = malloc(sizeof(t_mutex) * vars->nb_philo);
	vars->f_taken = malloc(sizeof(t_mutex) * vars->nb_philo);
	if (!vars->forks || !vars->forks)
		return (0);
	i = -1;
	while (++i < vars->nb_philo)
		pthread_mutex_init(&vars->forks[i], NULL);
	if (vars->nb_philo == 1)
		vars->seats[0].left_fork = &vars->forks[0];
	else
		forks_loop(vars);
	return (1);
}

void	seats_loop(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < vars->nb_philo)
	{
		vars->seats[i].id = i + 1;
		vars->seats[i].nb_philo = vars->nb_philo;
		vars->seats[i].time_to_die = vars->time_to_die;
		vars->seats[i].time_to_eat = vars->time_to_eat;
		vars->seats[i].time_to_sleep = vars->time_to_sleep;
		vars->seats[i].nb_eat = vars->nb_eat;
		vars->seats[i].mutex = vars->mutex;
		vars->seats[i].message = vars->message;
		vars->seats[i].died = vars->died;
		vars->seats[i].bonus_arg = vars->bonus_arg;
		vars->seats[i].timestamp = 0;
		vars->seats[i].last_meal = 0;
		vars->seats[i].meals = vars->nb_eat;
		vars->seats[i].mutual_info = vars;
	}
	vars->philo_died = 0;
}

int	prepare_seats(t_vars *vars)
{
	vars->seats = malloc(sizeof(t_seat) * vars->nb_philo + 1);
	if (!vars->seats)
		return (0);
	vars->mutex = malloc(sizeof(t_mutex));
	vars->message = malloc(sizeof(t_mutex));
	vars->died = malloc(sizeof(t_mutex));
	if (!vars->mutex || !vars->died || !vars->died)
		return (0);
	pthread_mutex_init(vars->mutex, NULL);
	pthread_mutex_init(vars->message, NULL);
	pthread_mutex_init(vars->died, NULL);
	seats_loop(vars);
	return (1);
}
