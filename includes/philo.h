/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:39:21 by mibernar          #+#    #+#             */
/*   Updated: 2022/12/02 17:37:38 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mutex;
typedef struct s_vars	t_vars;

typedef struct s_seat
{
	pthread_t	philo;
	int			id;
	int			nb_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nb_eat;
	int			bonus_arg;
	int			meals;
	t_mutex		*left_fork;
	int			*l_taken;
	int			*r_taken;
	t_mutex		*right_fork;
	long long	timestamp;
	long long	last_meal;
	long long	start_time;
	t_mutex		*mutex;
	t_mutex		*message;
	t_mutex		*died;
	t_vars		*mutual_info;
}t_seat;

typedef struct s_vars
{
	int			nb_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nb_eat;
	int			bonus_arg;
	int			*f_taken;
	int			philo_died;
	long long	start_time;
	t_seat		*seats;
	t_mutex		*forks;
	t_mutex		*mutex;
	t_mutex		*message;
	t_mutex		*died;
}t_vars;

//PHILO.C
int		init_vars(t_vars *vars, int argc, char **argv);
int		dinner(t_vars *vars);
void	*actions(void *arg);
int		check_end(t_seat *seat);
void	routine(t_seat *seat);

//TABLE.C
int		prepare_seats(t_vars *vars);
void	seats_loop(t_vars *vars);
int		prepare_forks(t_vars *vars);

//UTILS.C
int		ft_atoi(const char *str);
int		check_all_eat(t_seat *seat);
void	free_vars(t_vars *vaars);

//STATES.C
int		take_fork(t_seat *seat);
void	print_fork_mss(t_seat *seat);
int		philo_eat(t_seat *seat);
int		philo_sleep(t_seat *seat);
int		philo_think(t_seat *seat);

//TIME.C
long	get_time(void);

#endif
