/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_semaphores.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 16:10:30 by nagresel          #+#    #+#             */
/*   Updated: 2021/04/20 17:42:34 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

// char	*ft_sem_name(char *sem_name, char *phi_name)
// {
// 	static char	name[13];
// 	int			len;
// 	int			i;
// 	int			j;

// 	len = ft_strlen(phi_name);
// 	i = 0;
// 	while (sem_name[i] || i < 8)
// 	{
// 		name[i] = sem_name[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (phi_name[j] && name[i + j] && (i + j) < 12)
// 	{
// 		name[i + j] = phi_name[j];
// 		j++;
// 	}
// 	name[i + j] = '\0';
// 	return (name);
// }

int	ft_init_sem_phi(char *sem_name, int phi, t_prog_dt	*data)
{
	sem_unlink(ft_sem_name(sem_name, data->philo[phi].name));
	data->philo[phi].meal_time = sem_open(ft_sem_name(sem_name,
		data->philo[phi].name), O_CREAT | O_TRUNC | O_RDWR, S_IRWXU, 1);
	if (data->philo[phi].meal_time == SEM_FAILED)
		return (SEM_ERROR);
	return (0);
}

int	init_data_sem(t_prog_dt *data)
{
	int	i;

	sem_unlink("/fork");
	data->fork = sem_open("/fork", O_CREAT | O_EXCL, O_RDWR, data->n_philo);
	sem_unlink("/finish_eaten");
	data->finish_eaten = sem_open("/finish_eaten", O_CREAT | O_EXCL, O_RDWR,
		data->n_philo);
	sem_unlink("/log_lck");
	data->log_lock = sem_open("/log_lck", O_CREAT | O_EXCL, O_RDWR, 1);
	if (data->log_lock == SEM_FAILED)
		return (SEM_ERROR);
	sem_unlink("\end_lck");
	data->end_lock = sem_open("\end_lck", O_CREAT | O_EXCL, O_RDWR, 1);
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
	// if (pthread_mutex_init(&data->end_lock, NULL))
	// 	return (ft_display_msg(MUTEX_ERROR));
	// pthread_mutex_lock(&data->end_lock);
	return (0);
}