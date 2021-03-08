/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 18:01:48 by nagresel          #+#    #+#             */
/*   Updated: 2021/03/08 09:46:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	check_argument_format(char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if(av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static void	init_data(char **av, t_prog_dt *data)
{
	data->n_philo = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->n_meals = -1;
	data->is_last_meal_eaten = 0;
//	data->x_is_dead = -1;
	data->is_one_philo_dead = 0;
	ft_atoui(av[2], &data->time_to_die);
	ft_atoui(av[3], &data->time_to_eat);
	ft_atoui(av[4], &data->time_to_sleep);
}

int		init_philo(t_prog_dt *data)
{
	int			i;

	i = 0;
	while (i < data->n_philo)
	{
		if (!(data->philo[i].name = malloc(sizeof(char) * 10)))
			return (MALLOC_ERROR);
		if (!(data->philo[i].time_last_meal = malloc(sizeof(struct timeval))))
			return (MALLOC_ERROR);
		if (!(data->philo[i].time_start = malloc(sizeof(struct timeval))))
			return (MALLOC_ERROR);
		if (pthread_mutex_init(&data->philo[i].left_fork, NULL)) //!(i = 0) && ...dans la condition
			return (MUTEX_ERROR);
		if (pthread_mutex_init(&data->philo[i].meals, NULL)) //!(i = 0) && ...dans la condition
			return (MUTEX_ERROR);
		i++;
	}
	i = 0;
	while (i < data->n_philo)
	{
		if (i != 0)
			data->philo[i].right_fork = &data->philo[i - 1].left_fork;
		data->philo[i].id = i + 1;
		fill_nbr(data->philo[i].id, data->philo[i].name);
		data->philo[i].meals_ate = 0;
		data->philo[i].is_dead = 0;
		data->philo[i].time_to_die = data->time_to_die;
		data->philo[i].time_to_eat = data->time_to_eat;
		data->philo[i].time_to_sleep = data->time_to_sleep;
		i++;
	}
	data->philo[0].right_fork = &data->philo[i - 1].left_fork;
	if (!(data->time_start = malloc(sizeof(struct timeval))))
		return (MALLOC_ERROR);
	if (gettimeofday(data->time_start, NULL))
	{
		//	clean and free
		return (ft_display_msg(TIME_ERROR));
		exit(1);
	}
	return (0);
}

int		init_prog(int ac, char **av, t_prog_dt *data)
{
	init_data(av, data);
	if (ac != 5 && ac != 6)
		return (ft_display_msg(ARG_NB_ERROR));
	if (check_argument_format(av))
		return (ft_display_msg(ARG_FORMAT_ERROR));	
	if (ft_atoi(av[1], &data->n_philo))
		return (ft_display_msg(ARG_FORMAT_ERROR));
	if (data->n_philo < 2)
		return (ft_display_msg(ARG_VALUE_ERROR));
	// ft_atoui(av[2], &data->time_to_die);
	// ft_atoui(av[3], &data->time_to_eat);
	// ft_atoui(av[4], &data->time_to_sleep);
	if (ac == 6)
	{
		if (ft_atoi(av[5], &data->n_meals))
			return (ft_display_msg(ARG_VALUE_ERROR));
		if (data->n_meals < 1)
		return (ft_display_msg(ARG_VALUE_ERROR));
	}
	if (!(data->philo = (t_philo_dt *)malloc(sizeof(t_philo_dt) * (data->n_philo))))
		return (MALLOC_ERROR);
	//ajouter des vérification sur les valeurs de la mort qui doit être sup à la vie...
	if (pthread_mutex_init(&data->died, NULL)) //!(i = 0) && ...dans la condition
		return (MUTEX_ERROR);
	if (pthread_mutex_init(&data->meals, NULL)) //!(i = 0) && ...dans la condition
		return (MUTEX_ERROR);
	return (0);
}
