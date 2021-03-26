/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 18:01:48 by nagresel          #+#    #+#             */
/*   Updated: 2021/03/26 15:58:17 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	ft_init_philo_data(t_prog_dt *data)
{
	int i;

	i = 0;
	while (i < data->n_philo)
	{
		if (i != 0)
			data->philo[i].right_fork = &data->philo[i - 1].left_fork;
		data->philo[i].id = i + 1;
		fill_nbr(data->philo[i].id, data->philo[i].name);
		data->philo[i].meals_ate = 0;
		data->philo[i].is_start_sleeping = 0;
		i++;
	}
	data->philo[0].right_fork = &data->philo[i - 1].left_fork;
	i = 0;
	while (i < data->n_philo)
	{
		if ((i % 2))
			data->philo[i].is_start_sleeping = 1;
		i++;
	}
	return (0);
}

static int	check_argument_format(char **av)
{
	int i;
	int j;

	i = 1;
	j = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	init_data(t_prog_dt *data)
{
	data->n_meals = -1;
	data->one_is_died = 0;
	data->is_finish = 0;
	data->time_to_die = data->time_to_die *1000;
	data->time_to_eat = data->time_to_eat *1000;
	data->time_to_sleep = data->time_to_sleep *1000;
	return (0);
}

int		init_philo(t_prog_dt *data)
{
	int i;

	i = 0;
	while (i < data->n_philo)
	{
		if (!(data->philo[i].name = malloc(sizeof(char) * 10)))
			return (ft_display_msg(MALLOC_ERROR));
		if (!(data->philo[i].time_last_meal =
					malloc(sizeof(struct timeval))))
			return (ft_display_msg(MALLOC_ERROR));
		if (pthread_mutex_init(&data->philo[i].left_fork, NULL))
			return (ft_display_msg(MUTEX_ERROR));
		if (pthread_mutex_init(&data->philo[i].finish_eaten, NULL))
			return (ft_display_msg(MUTEX_ERROR));
		if (pthread_mutex_init(&data->philo[i].meal_time, NULL))
			return (ft_display_msg(MUTEX_ERROR));
		pthread_mutex_lock(&data->philo[i].finish_eaten);
		i++;
	}
	if (!(data->time_start = malloc(sizeof(struct timeval))))
		return (ft_display_msg(MALLOC_ERROR));
	if (ft_init_philo_data(data))
		return (ft_display_msg(TIME_ERROR));
	return (0);
}

int		init_prog(int ac, char **av, t_prog_dt *data)
{
	if (ac != 5 && ac != 6)
		return (ft_display_msg(ARG_NB_ERROR));
	if (check_argument_format(av))
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
	return (0);
}
