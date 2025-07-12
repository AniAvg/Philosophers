/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:36:05 by anavagya          #+#    #+#             */
/*   Updated: 2025/07/12 17:44:59 by anavagya         ###   ########.fr       */
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
	pthread_t		*thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int		philo_num;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		eat_count;
	int		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_mutex;

	// int		*num_array;
	t_philo	*philo;

}	t_data;

// validation.c
int		ft_strlen(char *str);
int		ft_atoi(const char *str);
int		validation(int argc, char *argv);

// main.c
void	init(t_philo *philo, t_data *data, char **argv);
void	*philosopher(void *arg);

#endif
