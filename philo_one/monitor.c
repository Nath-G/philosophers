/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:18:40 by nagresel          #+#    #+#             */
/*   Updated: 2021/03/25 14:52:55 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

// Pour chaque philosophers nommé philosopher : 
// tant que philospher n'a pas manger tous les repas : attendre
//Pour chaque philosophers nommé philosopher
//    tant que philospher n'a pas manger tout les repas ou qu'il y ai un mort
 //       attendr


// 1. on créer autant de mutex que de philos, nommé philo_[id]_finish_eaten ([id] étant son identifiant)
// 2. On lock tout ces mutexes quelques part, idéalement à la création du philosopher (dans leur thread respectif)
// 3. Dans ton thread principal, au lieu de faire une boucle qui dépend de philo[i].meals, on essaie de lock tout les philo_[id]_finish_eaten
// Étant donné qu'ils sont déjà lock, le thread pincipale va être bloqué ici car il ne peut pas les vérouiller tant qu'ils sont déjà vérouiller 
// 4. Dans chaque phisolopher, une fois qu'ils ont fini de manger, on unlock leur philo_[id]_finish_eaten.
// Attention à ne pas les délock plusieurs fois
// sauf que comme ça attend bêtement qu'un philo a fini de manger, il ne va pas pouvoir checker en parallèle si un autre philo est mort
// Simplement, la solution serait:
// - Faire un nouveau mutex locké nommé "finish"
// - Faire un nouveau thread monitor_deaths que tout les phisolopher sont encore en vie, on si le temps à expirer, afficher le message de mort et délock "finish"
// - Faire un nouveau thread monitor_eats (si échéant), qui va monitorer les repas comme expliqué avant, et délock "finish" une fois les repas finis
// et dans le main (/le thread principale) du coup:
// - on attend sur "finish" en essayant de le lock
// l'avantage de faire tout ça maintenant, c'est que ton code pour philo_three et philo_two serait quasi le même que philo_one
// 	pthread_lock(&dt->finish);

void	*eats_checker(void *data_philo)
{
	t_prog_dt	*data;
	int			i;

	data = (t_prog_dt *)data_philo;
	i = 0;	
	while (i < data->n_philo && !data->one_is_died)
	{
    	pthread_mutex_lock(&data->philo[i].finish_eaten);//&& !data->one_is_died)// || !data->one_is_died)
    	++i;
	}
	data->is_finish = 1;
	if (!data->one_is_died)
		printf("meals are striked ! \n");//est-ce que je met un message d'erreur?
//	pthread_mutex_unlock(&data->finish);
	return (NULL);
}


void	death_checker(t_prog_dt *dt)
{
	int					i;
	t_philo_dt			*phi;
	unsigned long int	time_stamp;
	struct timeval		cur_time;
	
	i = 0;
	phi = dt->philo;
	while (!dt->is_finish)
	{
		pthread_mutex_lock(&(phi[i].meal_time));
		ft_get_time(&cur_time);
		time_stamp = ft_get_time_diff(&cur_time, phi[i].time_last_meal);
		if ((time_stamp) > dt->time_to_die)
		{
			dt->is_finish = 1;
			dt->one_is_died = 1;
			time_stamp = ft_get_time_diff(&cur_time, dt->time_start);
			ft_display_log((time_stamp / 1000), phi[i].name, " dead\n");
		}
		pthread_mutex_unlock(&(phi[i].meal_time));
		++i;
		if (i == dt->n_philo)
			i = 0;
	}
	if (dt->n_meals != -1)
	{
		i = 0;
		while (i < dt->n_philo)
		{
			if (dt->philo[i].meals_ate < dt->n_meals)
				pthread_mutex_unlock(&(phi[i].finish_eaten));
			i++;
		}
	}
}
