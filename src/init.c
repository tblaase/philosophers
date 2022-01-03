/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:02:48 by tblaase           #+#    #+#             */
/*   Updated: 2022/01/03 20:31:07 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/philo.h"

static int	init_forks(t_input *input, t_philo **philos)
{
	int				i;
	int				check;
	pthread_mutex_t	fork;

	i = 0;
	check = 0;
	(void)input;
	while (philos[i] != NULL && check == 0)
	{
		check = pthread_mutex_init(&fork, NULL);
		philos[i++]->fork_r = &fork;
	}
	if (check != 0)
	{
		printf("Error when initialising forks\n");
		return (EXIT_FAILURE);
	}
	philos[0]->fork_l = philos[--i]->fork_r;
	while (i > 0)
	{
		philos[i]->fork_l = philos[i - 1]->fork_r;
		i--;
	}
	return (EXIT_SUCCESS);
}

t_philo	**init_philos(bool init)
{
	static t_philo	**philos;
	int				i;
	t_input			*input;

	if (init == false)
		return (philos);
	input = get_input();
	// input->forks = ft_calloc(1, sizeof(pthread_mutex_t **));
	// if (init_forks(input) == EXIT_FAILURE)
	// 	return (NULL);
	philos = ft_calloc(input->n_philos + 1, sizeof(t_philo *));
	if (philos == NULL)
		return (NULL);
	// else
	// {
	i = 0;
	while (i < input->n_philos)
	{
		philos[i] = ft_calloc(1, sizeof(t_philo));
		if (philos[i] == NULL)
		{
			free_philos();
			return (NULL);
		}
		// philos[i]->fork_r = input->forks[i];
		philos[i]->philo_n = i + 1;
		// if (i == 0)
		// 	philos[i]->fork_l = input->forks[input->n_philos - 1];
		// else
		// 	philos[i]->fork_l = input->forks[i - 1];
		i++;
	}
	if (init_forks(input, philos) == EXIT_FAILURE)
	{
		free_philos(); // change it to return NULL to save some lines
		return (NULL);
	}
	// }
	return (philos);
}

t_philo **get_philos(void)
{
	return (init_philos(false));
}