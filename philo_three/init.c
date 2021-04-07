/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 18:01:48 by nagresel          #+#    #+#             */
/*   Updated: 2021/04/07 18:22:15 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	ft_init_sem(t_prog_dt *data)
{
	int	i;

	i = 0;
	sem_unlink("/fork");
	data->fork = sem_open("/fork", O_CREAT | O_TRUNC, S_IRWXU, data->n_philo);
	// sem_unlink("/meal_time");
	// data->meal_time = sem_open("/meal_time", O_CREAT | O_TRUNC
	// 	| O_RDWR, S_IRWXU, 1);
	sem_unlink("/finish_eaten");
	data->finish_eaten = sem_open("/finish_eaten", O_CREAT | O_TRUNC, S_IRWXU,
		data->n_philo);
	sem_unlink("/finish");
	data->finish = sem_open("/finish", O_CREAT | O_TRUNC
		| O_RDWR, S_IRWXU, 1);
	if (data->finish_eaten == SEM_FAILED || data->fork == SEM_FAILED //|| data->meal_time == SEM_FAILED 
		|| data->finish == SEM_FAILED)
	{
		ft_clean_sem(data);
		return (SEM_ERROR);
	}
	i = -1;
	if (data->n_meals != -1)
		while (++i < data->n_philo)
			sem_wait(data->finish_eaten);
	sem_wait(data->finish);
	return (0);
}

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
		data->philo[i].is_died = 0;
		sem_unlink(data->philo[i].name);
		data->philo[i].meal_time = sem_open(data->philo[i].name, O_CREAT | O_TRUNC
		| O_RDWR, S_IRWXU, 1);
		if ( data->philo[i].meal_time == SEM_FAILED)
		{
			ft_clean_sem(data);
			return (SEM_ERROR);
		}
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

static int	init_data(t_prog_dt *data)
{
	data->n_meals = -1;
	data->one_is_died = 0;
	data->is_finish = 0;
	data->time_to_die = data->time_to_die * ONE_MLSEC;
	data->time_to_eat = data->time_to_eat * ONE_MLSEC;
	data->time_to_sleep = data->time_to_sleep * ONE_MLSEC;
	return (0);
}

int			init_philo(t_prog_dt *data)
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
		i++;
	}
	if (!(data->time_start = malloc(sizeof(struct timeval))))
		return (ft_display_msg(MALLOC_ERROR));
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
	if (ft_init_sem(data))
		return (ft_display_msg(SEM_ERROR));
	return (0);
}
