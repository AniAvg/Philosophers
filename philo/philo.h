/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:36:05 by anavagya          #+#    #+#             */
/*   Updated: 2025/07/17 18:02:29 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

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
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				start_time;
	pthread_t		philo_is_dead;
	pthread_mutex_t	sleep;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_mutex;
	// int		*num_array;
	t_philo			*philo;
}	t_data;

// utils.c
void	print_status(t_philo *philo, char *msg);
long	get_time_in_ms(void);

// validation.c
int		ft_atoi(const char *str);
//int		ft_strlen(char *str);
int		validation(int argc, char *argv);

// main.c
void	init(t_philo *philo, t_data *data, char **argv);
void	creating_threads(t_data *data);
void	pick_up_forks(t_philo *philo, t_data *data);
void	philo_eat(t_philo *philo);
void	put_down_forks(t_philo *philo, t_data *data, long ms);
void	philo_sleep(t_philo *philo, long ms);
void	philo_think(t_philo *philo, long ms);
void	*philosopher(void *arg);

#endif
