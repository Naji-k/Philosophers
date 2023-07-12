/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_inputs.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/11 19:28:38 by nakanoun      #+#    #+#                 */
/*   Updated: 2023/07/11 19:28:38 by nakanoun      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//check inputs if there is any characters

int	ft_is_all_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (1);
	}
	return (0);
}
int	check_inputs(int argc, char **argv)
{
	while ((argc - 1) > 1)
	{
		if (ft_is_all_digit(argv[argc - 1]) != 0)
		{
			printf("NO DIGIT\n");
			return (1);
		}
		argc--;
	}
	return (0);
}
