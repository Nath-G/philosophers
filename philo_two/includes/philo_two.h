/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:08:21 by nagresel          #+#    #+#             */
/*   Updated: 2021/03/31 18:12:02 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

# define ONE_MLSEC 1000
# define ONE_MICROSEC 1000000
# define ARG_NB_ERROR -1
# define ARG_FORMAT_ERROR -2
# define ARG_VALUE_ERROR -3
# define MALLOC_ERROR -4
# define PTHREAD_ERROR -5
# define SEM_ERROR -6
# define TIME_ERROR -7
# define ARG_INIT_ERROR -8
# define DATA_INIT_ERROR -9

typedef struct		s_philo_dt
{
	char			*name;
	int				id;
	pthread_t		thread;
	struct timeval	*time_last_meal;
	int				meals_ate;
	int				is_start_sleeping;
}					t_philo_dt;

typedef struct		s_prog_dt
{
	int				n_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				n_meals;
	struct timeval	*time_start;
	t_philo_dt		*philo;
	int				one_is_died;
	int				is_finish;
	pthread_t		eats_thread;
	pthread_t		deaths_thread;
	sem_t			*finish_eaten;
	sem_t			*meal_time;
	sem_t			*fork;
}					t_prog_dt;

typedef struct		s_param
{
	t_prog_dt	*data;
	t_philo_dt	*philo_dt;
}					t_param;

/*
**----clean up----**
*/
void				clean_philo(t_prog_dt *data, t_param *param);
void				ft_clean_sem(t_prog_dt *data);

/*
**----initialisation----**
*/
int					init_prog(int ac, char **av, t_prog_dt *data);
int					init_philo(t_prog_dt *data);

/*
**----liffe actions----**
*/
int					philo_eats(t_philo_dt *phi, t_prog_dt *data);
int					philo_sleeps(t_philo_dt *phi, t_prog_dt *data);
int					philo_thinks(t_philo_dt *phi, t_prog_dt *data);

/*
**----log----**
*/
int					ft_display_msg(int msg_nb);
void				ft_display_log(long unsigned time_stamp, char *philo_name,
						char *msg);

/*
**----monitoring----**
*/
void				death_checker(t_prog_dt *data);
void				*eats_checker(void *data);
void				philo_killer(t_prog_dt *data);

/*
**----time----**
*/
int					ft_get_time(struct timeval *time);
unsigned long int	ft_get_time_diff(struct timeval *cur_time,
						struct timeval *time);
int					ft_time_initialisation(t_prog_dt *data);

/*
**----utils----**
*/
int					ft_check_argument_format(char **av);
int					ft_strlen(const char *str);
int					ft_write_msg(char *msg, int ret);
int					ft_atoui(char *str, unsigned int *nb);
int					ft_atoi(char *str, int *nb);
void				fill_nbr(int nbr, char *ptr);
void				fill_lunbr(long unsigned nbr, char *ptr);
char				*ft_strjoinfree(char *s1, const char *s2);

#endif
