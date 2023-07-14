/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:55:18 by ouakrad           #+#    #+#             */
/*   Updated: 2023/07/14 16:33:56 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_executing.h"

/*
echo "hello"
------------------------
name="ouissal"
echo "My name is $name"
------------------------
echo "This text will be saved in a file." > file.txt
------------------------
echo "$(cat file.txt)"
------------------------
echo "$(pwd)"

*/
/*
cmd =====> args[0 ]= echo
args = -n
file = fd;
*/

int	newline_checker(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i] == '\0' && str[i - 1] == 'n')
		return (1);
	return (0);
}

void	my_echo(char **args)
{
	int	i;
	int	new_line;
	int	flag;

	i = 1;
	flag = 0;
	new_line = 1;
	while (args[i])
	{
		while (args[i] && newline_checker(args[i]) == 1 && flag == 0)
		{
			i++;
			new_line = 0;
		}
		flag = 1;
		if(args[i])
			printf("%s", args[i]);
		if (args[++i])
			printf(" ");
	}
	if (new_line)
		printf("\n");
}