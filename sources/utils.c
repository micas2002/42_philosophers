/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:00:01 by mibernar          #+#    #+#             */
/*   Updated: 2022/12/05 12:43:28 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	x;
	int	a;
	int	sinal;

	sinal = 1;
	a = 0;
	x = 0;
	while (str[x] != '\0' && (str[x] == ' ' || str[x] == 12
			|| str[x] == 10 || str[x] == 13 || str[x] == 9 || str[x] == 11))
		x++;
	while (str[x] != '\0' && (str[x] == 43 || str[x] == 45))
	{
		if (str[x + 1] == '+' || str[x + 1] == '-')
			return (0);
		else if (str[x] == '-')
			sinal *= -1;
		x++;
	}
	while (str[x] > 47 && str[x] < 58)
	{
		a = (str[x] - '0') + (a * 10);
		x++;
	}
	return (a * sinal);
}

int	init_vars(t_vars *vars, int argc, char **argv)
{
	vars->bonus_arg = 0;
	vars->nb_philo = ft_atoi(argv[1]);
	vars->time_to_die = ft_atoi(argv[2]);
	vars->time_to_eat = ft_atoi(argv[3]);
	vars->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		vars->nb_eat = ft_atoi(argv[5]);
		vars->bonus_arg = 1;
	}
	if (vars->bonus_arg == 1)
	{
		if (vars->nb_philo < 1 || vars->time_to_die < 1 || vars->time_to_eat < 1
			|| vars->time_to_sleep < 1 || vars->nb_eat < 1)
			return (0);
	}
	else
	{
		if (vars->nb_philo < 1 || vars->time_to_die < 1
			|| vars->time_to_eat < 1 || vars->time_to_sleep < 1)
			return (0);
	}
	return (1);
}

void	free_vars(t_vars *vars)
{
	free(vars->f_taken);
	free(vars->seats);
	pthread_mutex_destroy(vars->forks);
	pthread_mutex_destroy(vars->mutex);
	pthread_mutex_destroy(vars->message);
	pthread_mutex_destroy(vars->died);
	free(vars->forks);
	free(vars->mutex);
	free(vars->message);
	free(vars->died);
	free(vars);
}
