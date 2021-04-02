/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:18:35 by nagresel          #+#    #+#             */
/*   Updated: 2021/04/02 12:34:31 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	*philo_life(t_param *param, t_philo_dt *phi)
{
	int			i;
//	t_philo_dt	*phi;
//	t_param		*tmp;
	t_prog_dt	*data;

//	tmp = (t_param *)param;
	data = param->data;
//	phi = tmp->philo_dt;
	i = 0;
	while (1)
	{
		if (!phi->is_start_sleeping)
			philo_eats(phi, data);
		philo_sleeps(phi, data);
		philo_thinks(phi, data);
	}
	return (NULL);
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
	i = -1;
	while (++i < data->n_philo)
		ft_get_time(data->philo[i].time_last_meal);
	i = 0;
	param->data = data;
	while (i < data->n_philo && param && data)
	{
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
	if (data.n_meals != -1)
		if (pthread_create((&data.eats_thread), NULL, eats_checker, &data) < 0)
			return (ft_display_msg(PTHREAD_ERROR));
	if (!launch_philo(&data))
		death_checker(&data);
	clean_philo(&data);
	return (0);
}
