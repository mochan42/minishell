/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:49:51 by mochan            #+#    #+#             */
/*   Updated: 2022/09/16 15:59:16 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// 'welcome' message
void init_shell()
{
	printf("\n\n\n\n******************"
	    "************************");
	printf("\n\n\n\t**** 42 MINISHELL ****");
	printf("\n\n\t-USE AT YOUR OWN RISK-");
	printf("\n\n\n\n*******************"
	    "***********************");
	char* username;
	username = getenv("USER");
	printf("\n\n\nUSER is: @%s", username);
	printf("\n");
}

// Function to print Current Directory.
void printDir()
{
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("\nDir: %s", cwd);
}


// Function to take input
int takeInput(char* str)
{
	char* buf;

	buf = readline("\n>>> ");
	if (ft_strlen(buf) != 0)
	{
		add_history(buf);
		strcpy(str, buf);
		//printf("%s", str);
		return 0;
	}
	else
	{
		return 1;
	}
}

int	main(void)
{
	char inputString[MAXCOM];

	init_shell();
	printDir();
	takeInput(inputString);
	return (0);
}
