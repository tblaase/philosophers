/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:02:48 by tblaase           #+#    #+#             */
/*   Updated: 2021/12/28 16:39:50 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/philo.h"

static int	init_forks(t_input *input)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (i < input->n_philos && check == 0)
		check = pthread_mutex_init(input->forks[i++], NULL);
	if (check != 0)
	{
		printf("Error when initialising forks\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

t_philo	**init_philos(t_input *input)
{
	t_philo	**philos;
	int		i;

	if (init_forks(input) == EXIT_FAILURE)
		return (NULL);
	philos = ft_calloc(input->n_philos, sizeof(philos));
	if (philos == NULL)
		return (NULL);
	else
	{
		i = 0;
		while (i < input->n_philos)
		{
			philos[i] = ft_calloc(1, sizeof(philos[i]));
			philos[i]->fork_r = input->forks[i];
			if (philos[i] == NULL)
				return (NULL); // add ft_free_philos with exit_status here
			philos[i]->philo_n = i + 1;
			if (i == 0)
				philos[i]->fork_l = input->forks[input->n_philos - 1];
			else
				philos[i]->fork_l = input->forks[i - 1];
			i++;
		}
	}
	return (philos);
}
