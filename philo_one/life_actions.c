/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:27:33 by nagresel          #+#    #+#             */
/*   Updated: 2021/02/23 19:22:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	take_fork(pthread_mutex_t *fork, char *phi_name,
				struct timeval *time_start)
{
	long unsigned int	time_stamp;
	struct timeval		cur_time;

	pthread_mutex_lock(fork);
	ft_get_time(&cur_time);
	time_stamp = (cur_time.tv_sec - time_start->tv_sec) * 1000000
				+ (cur_time.tv_usec - time_start->tv_usec);
	ft_display_log((time_stamp / 1000), phi_name, " has taken a fork\n");
}

int		philo_eats(t_philo_dt *phi, t_prog_dt *dt)
{
	struct timeval	cur_time;
	long unsigned	time_stamp;

	take_fork(&phi->left_fork, phi->name, dt->time_start);
	take_fork(&phi->right_fork, phi->name, dt->time_start);
	ft_get_time(&cur_time);
	time_stamp = (cur_time.tv_sec - dt->time_start->tv_sec) * 1000000
				+ (cur_time.tv_usec - dt->time_start->tv_usec);
	ft_display_log((time_stamp / 1000), phi->name, " is eating\n");
	usleep(dt->time_to_eat * ONE_MILLISEC);
	pthread_mutex_unlock(&phi->left_fork);
	pthread_mutex_unlock(&phi->right_fork);
	if (gettimeofday(phi->time_last_meal, NULL))
	{
		//clean nd free
		ft_display_msg(TIME_ERROR);
		exit (1);
	}
	return (0);
}

int		philo_sleeps(t_philo_dt *phi, t_prog_dt *dt)
{
	struct timeval	cur_time;
	long unsigned	time_stamp;


	ft_get_time(&cur_time);
	time_stamp = (cur_time.tv_sec - dt->time_start->tv_sec) * 1000000
				+ (cur_time.tv_usec - dt->time_start->tv_usec);
	ft_display_log((time_stamp / 1000), phi->name, " is sleeping\n");
	usleep(dt->time_to_sleep * ONE_MILLISEC);
	return (0);
}

int		philo_thinks(t_philo_dt *phi, t_prog_dt *dt)
{
	struct timeval	cur_time;
	long unsigned	time_stamp;


	ft_get_time(&cur_time);
	time_stamp = (cur_time.tv_sec - dt->time_start->tv_sec) * 1000000
		+ (cur_time.tv_usec - dt->time_start->tv_usec);
	ft_display_log((time_stamp / 1000), phi->name, " is thinking\n");
	//usleep(100);
	return (0);
}
