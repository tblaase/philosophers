/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:26:02 by tblaase           #+#    #+#             */
/*   Updated: 2022/01/17 20:28:55 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/philo.h"

/**
 * @brief  checks if argv is only integers
 * @note
 * @param  **argv: argv from main
 * @retval true if only numbers found, false if not
 */
static bool	check_argv(char **argv, t_input *input)
{
	int		i;
	int		j;

	i = 1;
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j] != '\0' && ft_isdigit(argv[i][j]) == true)
			j++;
		if (argv[i++][j] != '\0')
			return (false);
	}
	input->n_philos = ft_atol(argv[1]);
	input->tt_die = ft_atol(argv[2]);
	input->tt_eat = ft_atol(argv[3]);
	input->tt_sleep = ft_atol(argv[4]);
	if (argv[5])
	{
		input->n_must_eat[0] = true;
		input->n_must_eat[1] = ft_atol(argv[5]);
	}
	else
		input->n_must_eat[0] = false;
	return (true);
}

/**
 * @brief  checks if input is valid
 * @note   prints error message explaining what is allowed when sth wrong
 * 		   will free input if something went wrong
 * @param  *input: the static input struct
 * @retval pointer to input or NULL if sth wrong
 */
static t_input	*check_input(t_input *input)
{
	if (input->n_philos <= 0 || input->n_philos > INT_MAX \
		|| input->tt_die <= 0 || input->tt_die > INT_MAX \
		|| input->tt_eat <= 0 || input->tt_eat > INT_MAX \
		|| input->tt_sleep <= 0 || input->tt_sleep > INT_MAX \
		|| (input->n_must_eat[0] == true && (input->n_must_eat[1] <= 0 \
		|| input->n_must_eat[1] > INT_MAX)))
	{
		printf("all numbers have to be positive integers but not 0\n");
		free_input();
		return (NULL);
	}
	return (input);
}

/**
 * @brief  sets the input struct from reading argv
 * @note   the *input is a static and can be accessed by get_input
 * @param  **argv: the argv from main
 * @retval pointer to the input struct or NULL if allocation failed
 */
t_input	*set_input(char **argv)
{
	static t_input	*input;

	if (argv == NULL)
		return (input);
	input = ft_calloc(1, sizeof(t_input));
	if (input == NULL)
		return (NULL);
	if (check_argv(argv, input) == false)
	{
		printf("only integers as input allowed\n");
		return (NULL);
	}
	if (input_help() == EXIT_FAILURE)
		return (NULL);
	pthread_mutex_init(input->print_lock, NULL);
	pthread_mutex_init(input->death_lock, NULL);
	pthread_mutex_init(input->wait_lock, NULL);
	input = check_input(input);
	return (input);
}

/**
 * @brief  can access the static of set_input
 * @note
 * @retval pointer stored in the static of set_input
 */
t_input	*get_input(void)
{
	return (set_input(NULL));
}
