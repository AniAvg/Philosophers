/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:36:05 by anavagya          #+#    #+#             */
/*   Updated: 2025/07/28 15:11:28 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meal_count;
	long			last_meal;
	int				left_fork;
	int				right_fork;
	pthread_t		thread;
	pthread_mutex_t	meal_time_mutex;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				philo_num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat_count;
	long			start_time;
	int				somebody_died;
	pthread_t		philo_is_dead;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	t_philo			*philo;
}	t_data;

// utils.c
void	print_status(t_philo *philo, char *msg);
long	get_time_in_ms(void);

// validation.c
int		ft_strlen(char *str);
int		is_digit(int argc, char **argv);
int		ft_atoi(const char *str);
int		validation(int argc, char **argv);

// init.c
void	init_philo(t_data *data);
void	init(t_data *data, char **argv);

// simulation.c
void	*philosopher(void *arg);

// simulation_utils.c
void	pick_up_forks(t_philo *philo, t_data *data);
void	philo_eat(t_philo *philo);
void	put_down_forks(t_philo *philo, t_data *data);
void	philo_sleep(t_philo *philo, long ms);
void	philo_think(t_philo *philo, long ms);

// main.c
void	*if_sb_is_dead(void *arg);
void	creating_threads(t_data *data);

#endif
