/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:18:35 by nagresel          #+#    #+#             */
/*   Updated: 2021/04/07 19:39:58 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	philo_life(t_param *param, t_philo_dt *phi)
{
	int			i;
	t_prog_dt	*data;
	pthread_t	death_thread;

	data = param->data;
	death_thread = 0;
	if (pthread_create(&(death_thread), NULL, death_checker, param) < 0)
			return (ft_display_msg(PTHREAD_ERROR));//essayer de mettre le thread dans la structure et ajouter le join dans le clean
	pthread_detach(death_thread);
	i = 0;
	while (!data->is_finish)
	{
		if (!phi->is_start_sleeping)
			philo_eats(phi, data);
		philo_sleeps(phi, data);
		philo_thinks(phi, data);
	}
	printf("thread philo %s\n", phi->name);
	return (0);
}

static int	launch_philo(t_prog_dt *data)
{
	int	i;
	t_param		*param;
	if (!(param = (t_param *)malloc(sizeof(t_param) * data->n_philo)))
	{
		clean_philo(data);
		return (ft_display_msg(MALLOC_ERROR));
	}
	if (gettimeofday(data->time_start, NULL))
		return (ft_display_msg(TIME_ERROR));
	i = 0;
	param->data = data;
	while (i < data->n_philo && param && data)
	{
		ft_get_time(data->philo[i].time_last_meal);
		param->philo_dt = &(data->philo[i]);
		data->philo[i].pid = fork();
		if (data->philo[i].pid == 0)
			philo_life(param, &(data->philo[i]));
		i++;
	}
	free(param);
	return (0);
}

int			main(int ac, char **av)
{
	t_prog_dt	data;

	if (init_prog(ac, av, &data))
		return (1);
	if (init_philo(&data))
	{
		clean_philo(&data);
		return (1);
	}
	monitor(&data);
	launch_philo(&data);
	sem_wait(data.finish);
	clean_philo(&data);
	return (0);
}
