/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:18:35 by nagresel          #+#    #+#             */
/*   Updated: 2021/04/16 13:47:09 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int	ft_init_sem_phi(char *sem_name, int phi, t_prog_dt	*data)
{
	sem_unlink(sem_name);
	data->philo[phi].meal_time = sem_open(sem_name, O_CREAT | O_TRUNC
	| O_RDWR, S_IRWXU, 1);
	if (data->philo[phi].meal_time == SEM_FAILED)
		return (SEM_ERROR);
	return (0);
}
// static void	ft_clean_sem_phi(char *sem_name, int phi, t_prog_dt	*data)
// {
// 	sem_close(data->philo[phi].meal_time);
// 	sem_unlink(sem_name);
// }
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

	if (gettimeofday(data->time_start, NULL))
		return (ft_display_msg(TIME_ERROR));
	i = -1;
	while (++i < data->n_philo)
		ft_get_time(data->philo[i].time_last_meal);
	i = 0;
	while (i < data->n_philo && param && data)
	{
	//	printf("ok0 phi %s\n", data->philo[i].name);
		if (ft_init_sem_phi("/meal_time", i, data))
			return (ft_display_msg(SEM_ERROR));
	//	printf("ok1 phi %s\n", data->philo[i].name);
		param[i].data = data;
	//	printf("ok2 phi %s\n", data->philo[i].name);
		param[i].philo_dt = &data->philo[i];
	//	printf("ok3 phi %s\n", data->philo[i].name);
		if (pthread_create(&(data->philo[i].thread), NULL, philo_life,
				&param[i]) < 0)
			return (ft_display_msg(PTHREAD_ERROR));
		i++;
	}
	//close sem
//	printf("ok7 phi %s\n", data->philo[i].name);
//	i = 0;
	// while(i < data->n_philo)
	// {
	// 	ft_clean_sem_phi("/meal_time", i, data);
	// 	i++;
	// }
//	printf("ok8 phi %s\n", data->philo[i].name);
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
		death_checker(&data);
	clean_philo(&data, param);
	return (0);
}
