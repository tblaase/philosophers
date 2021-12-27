/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:10:08 by tblaase           #+#    #+#             */
/*   Updated: 2021/12/27 17:29:59 by tblaase          ###   ########.fr       */
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
		check = pthread_mutex_init(&input->forks[i++], NULL);
	if (check != 0)
	{
		printf("Error when initialising forks\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	free_forks(void)
{
	t_input	*input;
	int		i;
	int		check;

	i = 0;
	check = 0;
	input = get_input();
	while (i < input->n_philos && check == 0)
		check = pthread_mutex_destroy(&input->forks[i++]);
	if (check != 0)
	{
		printf("Error when freeing forks\n");
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
				return (EXIT_FAILURE); // add ft_free_philos with exit_status here
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

int	routine(t_philo *philo)
{
	t_input	*input;
	long	start_time;
	long	now_time;
	int		eat;

	input = get_input();
	while ((input->n_must_eat[0] == true && eat < input->n_must_eat[1]) || eat < INT_MAX)
	{
		start_time = get_time();
		while ((start_time - now_time) < input->tt_die)
		{
			now_time = get_time();
			if (pthread_mutex_lock(philo->fork_l) && pthread_mutex_lock(philo->fork_r)) // take a look at how to actually check if a mutex is locked
				break ;
		}
		if ((start_time - now_time) >= input->tt_die)
			death_routine(philo);
		else
		{
			// eat
			// unlock
			// sleep
		}
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_input	*input;
	t_philo	**philos;

	if (argc < 5 || argc > 6)
	{
		printf("Wrong input!\nplease use like './philo\
		number_of_philosophers time_to_die time_to_eat time_to_sleep\
		[number_of_times_each_philosoppher_must_eat]'\n");
		return (EXIT_FAILURE);
	}
	input = set_input(argv);
	if (input == NULL)
		return (EXIT_FAILURE);
	else
	{
		philos = init_philos(input);
		if (philos == NULL || philos[0] == NULL)
		{
			printf("Error while creating philosophers\n");
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
