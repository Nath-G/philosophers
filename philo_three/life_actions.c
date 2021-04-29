/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:27:33 by nagresel          #+#    #+#             */
/*   Updated: 2021/04/28 19:52:46 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	log_fork(t_philo_dt *phi, t_prog_dt *dt)
{
	struct timeval	cur_time;
	long unsigned	time_stamp;

	if (ft_get_time(&cur_time))
		return (ft_display_msg(TIME_ERROR));
	time_stamp = ft_get_time_diff(&cur_time, dt->time_start);
	if (!dt->is_finish)
		ft_display_log((time_stamp / ONE_MLSEC), phi->name,
			" has taken a fork\n", dt);
	if (!dt->is_finish)
		ft_display_log((time_stamp / ONE_MLSEC), phi->name,
			" has taken a fork\n", dt);
	return (0);
}

static int	take_forks(t_philo_dt *phi, t_prog_dt *dt)
{
	int	i;
	int	ret;

	i = 1;
	while (i < (dt->n_philo / 2))
	{
		if (sem_wait(dt->queue_forks[i]) != 0)
			return (ft_display_msg(SEM_ERROR));
		sem_post(dt->queue_forks[i - 1]);
		i++;
	}
	if (sem_wait(dt->fork) == 0)
	{
		sem_post(dt->queue_forks[i - 1]);
		if ((ret = log_fork(phi, dt)))
			return (ret);
	}
	else
		return (ft_display_msg(SEM_ERROR));
	return (0);
}

int			philo_eats(t_philo_dt *phi, t_prog_dt *dt)
{
	struct timeval	cur_time;
	long unsigned	time_stamp;

	if (take_forks(phi, dt))
		return (1);
	sem_wait(phi->meal_time);
	ft_get_time(phi->time_last_meal);
	ft_get_time(&cur_time);
	time_stamp = ft_get_time_diff(&cur_time, dt->time_start);
	if (!dt->is_finish)
		ft_display_log((time_stamp / ONE_MLSEC), phi->name,
			" is eating\n", dt);
	sem_post(phi->meal_time);
	usleep(dt->time_to_eat);
	phi->meals_ate++;
	if (phi->meals_ate == dt->n_meals)
		sem_post(dt->finish_eaten);
	sem_post(dt->fork);
	sem_post(dt->fork);
	return (0);
}

int			philo_sleeps(t_philo_dt *phi, t_prog_dt *dt)
{
	struct timeval	cur_time;
	long unsigned	time_stamp;

	ft_get_time(&cur_time);
	time_stamp = ft_get_time_diff(&cur_time, dt->time_start);
	if (!dt->is_finish)
		ft_display_log((time_stamp / ONE_MLSEC), phi->name,
			" is sleeping\n", dt);
	usleep(dt->time_to_sleep);
	return (0);
}

int			philo_thinks(t_philo_dt *phi, t_prog_dt *dt)
{
	struct timeval	cur_time;
	long unsigned	time_stamp;

	ft_get_time(&cur_time);
	time_stamp = ft_get_time_diff(&cur_time, dt->time_start);
	if (!dt->is_finish)
		ft_display_log((time_stamp / ONE_MLSEC), phi->name,
			" is thinking\n", dt);
	return (0);
}
