/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:18:35 by nagresel          #+#    #+#             */
/*   Updated: 2021/04/21 18:13:13 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static void	*philo_life(void *param)
{
	int			i;
	t_philo_dt	*phi;
	t_param		*tmp;
	t_prog_dt	*data;

	tmp = (t_param *)param;
	data = tmp->data;
	phi = tmp->philo_dt;
	i = 0;
//	printf("oups 1\n");
	// if (pthread_create((&(phi->death_thread)), NULL, death_checker, data) < 0)
	// {
	// 	printf("liffe spread mort phi %s = %lu\n", phi->name, phi->death_thread);
	// 	ft_display_msg(PTHREAD_ERROR);
	// 	return (NULL);
	// }
	//printf("liffe phi %s = %lu\n", phi->name, phi->death_thread);
 
	while (!data->is_finish)
	{
	//	printf("beguin routine phi %s\n",phi->name);
		
		philo_eats(phi, data);
		philo_sleeps(phi, data);
		philo_thinks(phi, data);
	}
	return (NULL);
}

static void	*philo_life_bis(void *param)
{
	int			i;
	t_philo_dt	*phi;
	t_param		*tmp;
	t_prog_dt	*data;

	tmp = (t_param *)param;
	data = tmp->data;
	phi = tmp->philo_dt;
	i = 0;
	//printf("oups bis\n");
	// if (pthread_create(&(phi->death_thread), NULL, death_checker, data) < 0)
	// {
	// 	printf("liffe bis spread mort phi %s = %lu\n", (phi->name), (phi->death_thread));
	// 	ft_display_msg(PTHREAD_ERROR);
	// 	return (NULL);
	// }
	//printf("liffe  bis phi %s = %lu\n", phi->name, phi->death_thread);
	while (!data->is_finish)
	{
	//	printf("beguin routine bis phi %s\n",phi->name);
		philo_sleeps(phi, data);
		philo_thinks(phi, data);
		philo_eats(phi, data);
	}
	return (NULL);
}

static int	launch_philo(t_prog_dt *data, t_param *param)
{
	int	i;

	if (gettimeofday(data->time_start, NULL))
		return (ft_display_msg(TIME_ERROR));
	i = -1;
	while (++i < data->n_philo)
		ft_get_time(data->philo[i].time_last_meal);
	i = 0;
	while (i < data->n_philo && param && data)
	{
		param[i].data = data;
		param[i].philo_dt = &data->philo[i];
		if (ft_init_sem_phi("/ml_time", i, data))
			return (ft_display_msg(SEM_ERROR));
		if (!data->philo[i].is_start_sleeping)
			if (pthread_create(&(data->philo[i].thread), NULL, philo_life,
				&param[i]) < 0)
				return (ft_display_msg(PTHREAD_ERROR));
		if (data->philo[i].is_start_sleeping)
			if (pthread_create(&(data->philo[i].thread), NULL, philo_life_bis,
				&param[i]) < 0)
				return (ft_display_msg(PTHREAD_ERROR));
		i++;
	}
	return (0);
}

int			main(int ac, char **av)
{
	t_prog_dt	data;
	t_param		*param;

	if (init_prog(ac, av, &data))
		return (1);
	if (!(param = (t_param *)malloc(sizeof(t_param) * data.n_philo)))
	{
		clean_philo(&data, param);
		return (ft_display_msg(MALLOC_ERROR));
	}
	if (init_philo(&data))
	{
		clean_philo(&data, param);
		return (1);
	}
	if (data.n_meals != -1)
		if (pthread_create((&data.eats_thread), NULL, eats_checker, &data) < 0)
			return (ft_display_msg(PTHREAD_ERROR));
	if (!launch_philo(&data, param))
		if (pthread_create(&(data.deaths_thread), NULL, death_checker, &data) < 0)
	{
		// printf("liffe bis spread mort phi %s = %lu\n", (phi->name), (phi->death_thread));
		return (ft_display_msg(PTHREAD_ERROR));
		// ft_display_msg(PTHREAD_ERROR);
		// return (NULL);
	}
	
	if (sem_wait(data.end_lock))
		return (1);
	clean_philo(&data, param);
	return (0);
}
