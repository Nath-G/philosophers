/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:27:33 by nagresel          #+#    #+#             */
/*   Updated: 2021/04/16 14:20:22 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int	take_forks(t_philo_dt *phi, t_prog_dt *dt)
{
	long unsigned int	time_stamp;
	struct timeval		cur_time;

	if (sem_wait(dt->fork))
		return (1);
	if (sem_wait(dt->fork))
		return (1);
	ft_get_time(&cur_time);
	if (!dt->is_finish)
	{
		time_stamp = ft_get_time_diff(&cur_time, dt->time_start);
		ft_display_log((time_stamp / ONE_MLSEC), phi->name,
			" has taken a fork\n");
	}
	if (!dt->is_finish)
		ft_display_log((time_stamp / ONE_MLSEC), phi->name,
			" has taken a fork\n");
	return (0);
}

int			philo_eats(t_philo_dt *phi, t_prog_dt *dt)
{
	struct timeval	cur_time;
	long unsigned	time_stamp;

	take_forks(phi, dt);
	if (sem_wait(phi->meal_time))
		return (1);
	ft_get_time(phi->time_last_meal);
	ft_get_time(&cur_time);
	time_stamp = ft_get_time_diff(&cur_time, dt->time_start);
	if (!dt->is_finish)
		ft_display_log((time_stamp / ONE_MLSEC), phi->name, " is eating\n");
	if (sem_post(phi->meal_time))
		return (1);
	ft_get_time(&cur_time);
	usleep(dt->time_to_eat - ft_get_time_diff(&cur_time, phi->time_last_meal));
	phi->meals_ate++;
	if (phi->meals_ate == dt->n_meals)// && !dt->is_finish)
		if (sem_post(dt->finish_eaten))
			return (1);
	if (sem_post(dt->fork))
		return (1);
	if (sem_post(dt->fork))
		return (1);
	return (0);
}

int			philo_sleeps(t_philo_dt *phi, t_prog_dt *dt)
{
	struct timeval	cur_time;
	long unsigned	time_stamp;

	if (phi->is_start_sleeping)
		phi->is_start_sleeping = 0;
	ft_get_time(&cur_time);
	if (!dt->is_finish)
	{
		time_stamp = ft_get_time_diff(&cur_time, dt->time_start);
		ft_display_log((time_stamp / ONE_MLSEC), phi->name, " is sleeping\n");
		usleep(dt->time_to_sleep);
	}
	return (0);
}

int			philo_thinks(t_philo_dt *phi, t_prog_dt *dt)
{
	struct timeval	cur_time;
	long unsigned	time_stamp;

	ft_get_time(&cur_time);
	if (!dt->is_finish)
	{
		time_stamp = ft_get_time_diff(&cur_time, dt->time_start);
		ft_display_log((time_stamp / ONE_MLSEC), phi->name, " is thinking\n");
	}
	return (0);
}
