/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_semaphores.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 16:10:30 by nagresel          #+#    #+#             */
/*   Updated: 2021/05/06 14:22:34 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	init_ml_time_phi_sem(char *sem_name, int phi, t_prog_dt *data)
{
	sem_unlink(ft_sem_name(sem_name, data->philo[phi].name));
	data->philo[phi].meal_time = sem_open(ft_sem_name(sem_name,
		data->philo[phi].name), O_CREAT | O_EXCL, 0777, 1);
	if (data->philo[phi].meal_time == SEM_FAILED)
		return (SEM_ERROR);
	return (0);
}

int	init_queue_fork_sem(t_prog_dt *data)
{
	int	i;

	i = 0;
	while (i < (data->n_philo / 2))
	{
		sem_unlink(ft_sem_name("/queue_f", data->philo[i].name));
		data->queue_forks[i] = sem_open(ft_sem_name("/queue_f",
			data->philo[i].name), O_CREAT | O_EXCL, 0777, 1);
		if (data->queue_forks[i] == SEM_FAILED)
			return (SEM_ERROR);
		i++;
	}
	return (0);
}

int	init_data_sem(t_prog_dt *data)
{
	int	i;

	sem_unlink("/fork");
	data->fork = sem_open("/fork", O_CREAT | O_EXCL, 0777, (data->n_philo / 2));
	sem_unlink("/end_eat");
	data->finish_eaten = sem_open("/end_eat", O_CREAT | O_EXCL, 0777,
		data->n_philo);
	sem_unlink("/log_lck");
	data->log_lock = sem_open("/log_lck", O_CREAT | O_EXCL, 0777, 1);
	sem_unlink("/end_lck");
	data->end_lock = sem_open("/end_lck", O_CREAT | O_EXCL, 0777, 1);
	if (data->end_lock == SEM_FAILED || data->log_lock == SEM_FAILED
		|| data->fork == SEM_FAILED || data->finish_eaten == SEM_FAILED)
	{
		ft_clean_sem(data);
		return (SEM_ERROR);
	}
	i = -1;
	if (data->n_meals != -1)
		while (++i < data->n_philo)
			sem_wait(data->finish_eaten);
	sem_wait(data->end_lock);
	return (0);
}
