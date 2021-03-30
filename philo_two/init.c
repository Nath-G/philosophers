/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 18:01:48 by nagresel          #+#    #+#             */
/*   Updated: 2021/03/30 18:48:45 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int	ft_init_philo_data(t_prog_dt *data)
{
	int i;

	i = 0;
	while (i < data->n_philo)
	{
		data->philo[i].id = i + 1;
		fill_nbr(data->philo[i].id, data->philo[i].name);
		data->philo[i].meals_ate = 0;
		data->philo[i].is_start_sleeping = 0;
		i++;
	}
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
	data->time_to_die = data->time_to_die * 1000;
	data->time_to_eat = data->time_to_eat * 1000;
	data->time_to_sleep = data->time_to_sleep * 1000;
	return (0);
}

int			init_philo(t_prog_dt *data)
{
	int i;
	sem_unlink("/fork");
	data->fork = sem_open("/fork", O_CREAT, S_IRWXU, data->n_philo);
	if (data->fork == SEM_FAILED)
		return(ft_display_msg(SEM_ERROR));
	sem_unlink("/meal_time");
	data->meal_time = sem_open("/meal_time", O_CREAT | O_TRUNC | O_RDWR, S_IRWXU, 1);
	if (data->meal_time == SEM_FAILED)
		return(ft_display_msg(SEM_ERROR));
	sem_unlink("/finish_eaten");
	data->finish_eaten = sem_open("/finish_eaten", O_CREAT, S_IRWXU, data->n_philo);
	if (data->finish_eaten == SEM_FAILED)
		return(ft_display_msg(SEM_ERROR));
	i = 0;
	while (i < data->n_philo)
	{
		if (!(data->philo[i].name = malloc(sizeof(char) * 10)))
			return (ft_display_msg(MALLOC_ERROR));
		if (!(data->philo[i].time_last_meal =
				malloc(sizeof(struct timeval))))
			return (ft_display_msg(MALLOC_ERROR));
		if (data->n_meals != -1)
			sem_wait(data->finish_eaten);
		i++;
	}
	if (!(data->time_start = malloc(sizeof(struct timeval))))
		return (ft_display_msg(MALLOC_ERROR));
	if (ft_init_philo_data(data))
		return (ft_display_msg(TIME_ERROR));
	return (0);
}

int			init_prog(int ac, char **av, t_prog_dt *data)
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
