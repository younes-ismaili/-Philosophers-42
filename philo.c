/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 11:34:21 by yismaili          #+#    #+#             */
/*   Updated: 2022/05/13 18:25:25 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *ptr)
{	
	int			i;
	t_philo		*philo;
	pthread_t	thread;
	philo = (t_philo *)ptr;
	i = 0;
	philo->time_to_kill = philo->data->get_t + philo->data->time_to_die;
	pthread_create(&thread, NULL, &ft_check, philo);
	pthread_detach(thread);
	while (i < philo->data->number_of_philo || philo->time_to_kill > get_time())
	{
		philo_activities(philo);
		i++;
	}
	return (NULL);
}

void *ft_check(void *ptr)
{
	t_philo		*philo;
	philo = (t_philo *)ptr;

	while (1)
	{
		if (philo->time_to_kill <= get_time() && philo->count_eat <= philo->data->number_must_eat)
		{
			get_message("died", philo->philo_id, philo->data, KRED);
			pthread_mutex_lock(&philo->data->mut_write);
			philo->data->st = 1;
		}
		else 
		{
			philo->data->count_philo++;
		}
	}
	return (NULL);
}

t_philo   *init_args(int ac, char **av, t_data	*data)
{
	t_philo	*philo;
	int		i;

	if (!data)
		return (0);
	data->get_t = get_time();
	data->count_philo = 0;
	data->st = 0;
	data->number_of_philo =  ft_atoi(av[1]); 
	philo = malloc(sizeof(t_philo) * data->number_of_philo);
	if (!philo)
		return (0);
	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_init(&philo[i].fork, NULL);
		i++;
	}
	i = 0;
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->number_must_eat = 1;
	if (ac == 6)
		data->number_must_eat = ft_atoi(av[5]);
	if (data->number_of_philo <= 0 || data->number_of_philo > 200 || data->number_must_eat <= 0)
		ft_die("ArgumentError\n");
	init_philo(philo, data);
	while (i < data->number_of_philo )
	{
		if (pthread_create(&philo[i].th_philo, NULL, routine, &philo[i]) != 0)
			ft_die("Failed to create thread");
		usleep(100);
		i++;
	}
	i = 0;
	while (i < data->number_of_philo)
		pthread_detach(philo[i++].th_philo);
	while(data->st == 0)
	{
		if (data->count_philo == data->number_of_philo)
			break;
	}
	// i = 0;
	// while (i < data->number_of_philo)
	// 	pthread_mutex_destroy(&philo[i++].fork);
	// pthread_mutex_destroy(&data->mut_write);
	return (philo);
}

void init_philo(t_philo *philo, t_data *data)
{
	int i;

	i = 0;
	while (i < data->number_of_philo)
	 {
		philo[i].philo_id = i + 1;
		philo[i].data = data;
		 if (i == (data->number_of_philo - 1))
	 	 	philo[i].right_fork = &philo[0].fork;
		 else
		 	philo[i].right_fork = &philo[i + 1].fork;
		i++;
	}
}
 int 	ft_die(char *str)
 {
	printf("%s\n", str);	
	 exit(1);
 }
