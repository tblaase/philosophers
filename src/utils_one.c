/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:58:34 by tblaase           #+#    #+#             */
/*   Updated: 2021/12/27 16:20:52 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/philo.h"

/**
 * @brief  recreation of systems atol function
 * @note   has no error handling, if no long long found 0 is returned
 * @param  *str: the string to convert
 * @retval the long long converted from the input
 */
long long	ft_atol(char *str)
{
	int			c;
	int			i;
	long long	x;

	i = 0;
	c = 1;
	x = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			c = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		x = x * 10 + (str[i] - 48);
		i++;
	}
	return (x * c);
}

/**
 * @brief  recreation of the systems calloc
 * @note
 * @param  nelem: number of elements
 * @param  elsize: the size of each element
 * @retval the pointer to the allocated memory or NULL if allocation failed
 */
void	*ft_calloc(size_t nelem, size_t elsize)
{
	char			*ptr;
	unsigned int	i;

	i = 0;
	ptr = (char *)malloc(nelem * elsize);
	if (!ptr)
		return (NULL);
	while (i < nelem * elsize)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
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
		|| input->tt_eat < 0 || input->tt_eat > INT_MAX \
		|| input->tt_sleep < 0 || input->tt_sleep > INT_MAX \
		|| (input->n_must_eat[0] == true && (input->n_must_eat[1] <= 0 \
		|| input->n_must_eat[1] > INT_MAX)))
	{
		printf("all numbers have to be positive integers\
		\nnumber_of_philos and time_to_die and n_must_eat can't be 0\n");
		free(input);
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
	input = ft_calloc(1, sizeof(input));
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
