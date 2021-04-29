/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:39:18 by nagresl           #+#    #+#             */
/*   Updated: 2021/04/28 20:46:28 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	ft_clean_sem_phi(char *sem_name, int phi, t_prog_dt *data)
{
	sem_close(data->philo[phi].meal_time);
	sem_unlink(ft_sem_name(sem_name, data->philo[phi].name));
}

void		ft_post_sem(t_prog_dt *dt)
{
	int i;

	i = -1;
	while (++i < dt->n_philo)
		sem_post(dt->fork);
	if (dt->n_meals != -1)
	{
		i = -1;
		while (++i < dt->n_philo)
			sem_post(dt->finish_eaten);
	}
	i = -1;
	while (++i < dt->n_philo)
	{
		sem_post(dt->philo[i].meal_time);
		sem_post(dt->log_lock);
		sem_post(dt->death_lock);
	}
}

void		ft_clean_sem(t_prog_dt *data)
{
	int i;

	i = -1;
	while (++i < data->n_philo)
		ft_clean_sem_phi("/ml_time", i, data);
	i = 0;
	while (i < data->n_philo)
	{
		sem_close(data->queue_forks[i]);
		sem_unlink(ft_sem_name("queue_f", data->philo[i].name));
		i++;
	}
	sem_close(data->fork);
	sem_close(data->finish_eaten);
	sem_close(data->log_lock);
	sem_close(data->end_lock);
	sem_close(data->death_lock);
	sem_unlink("/fork");
	sem_unlink("/end_eat");
	sem_unlink("/log_lck");
	sem_unlink("/end_lck");
	sem_unlink("/dth_lck");
}

void		philo_killer(t_prog_dt *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
		pthread_join(data->philo[i].death_thread, NULL);
	i = -1;
	while (++i < data->n_philo)
	{
		if (&data->philo[i])
			kill(data->philo[i].pid, SIGKILL);
	}
	ft_post_sem(data);
	if (data->n_meals != -1)
		pthread_join(data->eats_thread, NULL);
}

int			clean_philo(t_prog_dt *data)
{
	int			i;

	i = 0;
	data->one_is_died = 1;
	data->is_finish = 1;
	philo_killer(data);
	ft_clean_sem(data);
	while (i < data->n_philo)
	{
		if (data->philo[i].name)
			free(data->philo[i].name);
		if (data->philo[i].time_last_meal)
			free(data->philo[i].time_last_meal);
		i++;
	}
	if (data->queue_forks)
		free(data->queue_forks);
	if (data->time_start)
		free(data->time_start);
	if (data->philo)
		free(data->philo);
	return (0);
}
