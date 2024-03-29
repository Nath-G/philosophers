/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 18:01:48 by nagresel          #+#    #+#             */
/*   Updated: 2021/05/06 12:46:02 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int	ft_init_philo_data(t_prog_dt *data)
{
	int i;

	i = -1;
	while (++i < data->n_philo)
	{
		data->philo[i].id = i + 1;
		fill_nbr(data->philo[i].id, data->philo[i].name);
		data->philo[i].meals_ate = 0;
		data->philo[i].is_start_sleeping = 0;
		data->philo[i].time_last_meal->tv_sec = 0;
		data->philo[i].time_last_meal->tv_usec = 0;
	}
	i = -1;
	while (++i < data->n_philo)
		if ((i % 2))
			data->philo[i].is_start_sleeping = 1;
	if (init_queue_fork_sem(data))
		return (ft_display_msg(SEM_ERROR));
	i = -1;
	while (++i < data->n_philo)
		if (init_ml_time_phi_sem("/ml_time", i, data))
			return (ft_display_msg(SEM_ERROR));
	return (0);
}

static int	init_data(t_prog_dt *data)
{
	data->n_meals = -1;
	data->one_is_died = 0;
	data->is_finish = 0;
	data->time_to_die = data->time_to_die * ONE_MLSEC;
	data->time_to_eat = data->time_to_eat * ONE_MLSEC;
	data->time_to_sleep = data->time_to_sleep * ONE_MLSEC;
	if (!(data->queue_forks = malloc(sizeof(sem_t *) *
			(data->n_philo / 2))))
		return (ft_display_msg(MALLOC_ERROR));
	if (!(data->time_start = malloc(sizeof(struct timeval))))
		return (ft_display_msg(MALLOC_ERROR));
	data->time_start->tv_sec = 0;
	data->time_start->tv_usec = 0;
	data->eats_thread = 0;
	data->deaths_thread = 0;
	return (0);
}

int			init_philo(t_prog_dt *data)
{
	int i;

	i = -1;
	while (++i < data->n_philo)
	{
		if (!(data->philo[i].name = malloc(sizeof(char) * 10)))
			return (ft_display_msg(MALLOC_ERROR));
		if (!(data->philo[i].time_last_meal =
				malloc(sizeof(struct timeval))))
			return (ft_display_msg(MALLOC_ERROR));
		data->philo[i].thread = 0;
	}
	if (ft_init_philo_data(data))
		return (ft_display_msg(DATA_INIT_ERROR));
	return (0);
}

int			init_prog(int ac, char **av, t_prog_dt *data)
{
	if (ac != 5 && ac != 6)
		return (ft_display_msg(ARG_NB_ERROR));
	if (ft_check_argument_format(av))
		return (ft_display_msg(ARG_FORMAT_ERROR));
	if (ft_atoi(av[1], &data->n_philo))
		return (ft_display_msg(ARG_FORMAT_ERROR));
	if (ft_atoui(av[2], &data->time_to_die))
		return (ft_display_msg(ARG_INIT_ERROR));
	if (ft_atoui(av[3], &data->time_to_eat))
		return (ft_display_msg(ARG_INIT_ERROR));
	if (ft_atoui(av[4], &data->time_to_sleep))
		return (ft_display_msg(ARG_INIT_ERROR));
	if (init_data(data))
		return (ARG_INIT_ERROR);
	if (ac == 6)
		if (ft_atoi(av[5], &data->n_meals) || data->n_meals < 1)
			return (ft_display_msg(ARG_VALUE_ERROR));
	if (data->n_philo < 2)
		return (ft_display_msg(ARG_VALUE_ERROR));
	if (!(data->philo = (t_philo_dt *)malloc(sizeof(t_philo_dt) *
			(data->n_philo))))
		return (ft_display_msg(MALLOC_ERROR));
	if (init_data_sem(data))
		return (ft_display_msg(SEM_ERROR));
	return (0);
}
