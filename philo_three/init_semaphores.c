/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_semaphores.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 16:10:30 by nagresel          #+#    #+#             */
/*   Updated: 2021/05/04 12:14:37 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
	while (i < data->n_phi / 2)
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

int	init_data_sem(t_prog_dt *dt)
{
	int	i;

	sem_unlink("/fork");
	dt->fork = sem_open("/fork", O_CREAT | O_EXCL, 0777, dt->n_phi / 2);
	sem_unlink("/end_eat");
	dt->finish_eaten = sem_open("/end_eat", O_CREAT | O_EXCL, 0777, dt->n_phi);
	sem_unlink("/log_lck");
	dt->log_lock = sem_open("/log_lck", O_CREAT | O_EXCL, 0777, 1);
	sem_unlink("/end_lck");
	dt->end_lock = sem_open("/end_lck", O_CREAT | O_EXCL, 0777, 1);
	sem_unlink("/dth_lck");
	dt->death_lock = sem_open("/dth_lck", O_CREAT | O_EXCL, 0777, 1);
	if (dt->end_lock == SEM_FAILED || dt->log_lock == SEM_FAILED
		|| dt->fork == SEM_FAILED || dt->finish_eaten == SEM_FAILED
		|| dt->death_lock == SEM_FAILED)
	{
		ft_clean_sem(dt);
		return (SEM_ERROR);
	}
	i = -1;
	if (dt->n_meals != -1)
		while (++i < dt->n_phi)
			sem_wait(dt->finish_eaten);
	sem_wait(dt->end_lock);
	return (0);
}
