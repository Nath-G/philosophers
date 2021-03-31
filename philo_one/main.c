/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:18:35 by nagresel          #+#    #+#             */
/*   Updated: 2021/03/31 15:23:10 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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
	while (!data->is_finish)
	{
		if (!phi->is_start_sleeping)
			philo_eats(phi, data);
		philo_sleeps(phi, data);
		philo_thinks(phi, data);
	}
	return (NULL);
}

static int	launch_philo(t_prog_dt *data, t_param *param)
{
	int	i;

	i = 0;
	while (i < data->n_philo && param && data)
	{
		param[i].data = data;
		param[i].philo_dt = &data->philo[i];
		if (pthread_create(&(data->philo[i].thread), NULL, philo_life,
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
	if (!ft_time_initialisation(&data))
	{
		launch_philo(&data, param);
		death_checker(&data);
	}
	clean_philo(&data, param);
	return (0);
}
