/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xero_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 04:49:44 by bchiki            #+#    #+#             */
/*   Updated: 2025/07/31 12:06:58 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_xero_version(void)
{
	printf("\n╭─────────────────────────────────────────────────────────╮\n");
	printf("│                                                         │\n");
	printf("│    ⚡ XERO v1.0.0 ⚡                                    │\n");
	printf("│    (Stay tuned for exciting updates ahead!)             │\n");
	printf("│    © 2025 CHIKI Badreddine & Alae Ben Dris Alami        │\n");
	printf("│                                                         │\n");
	printf("╰─────────────────────────────────────────────────────────╯\n\n");
}

static	void	print_xero_developers_content(void)
{
	printf("\n╔═════════════════════════════"
		"══════════════════════════════════╗\n");
	printf("║                               "
		"                                ║\n");
	printf("║                ██╗  ██╗███████╗"
		"██████╗  ██████╗               ║\n");
	printf("║                ╚██╗██╔╝██╔════╝"
		"██╔══██╗██╔═══██╗              ║\n");
	printf("║                 ╚███╔╝ █████╗  "
		"██████╔╝██║   ██║              ║\n");
	printf("║                 ██╔██╗ ██╔══╝  "
		"██╔══██╗██║   ██║              ║\n");
	printf("║                ██╔╝ ██╗███████╗"
		"██║  ██║╚██████╔╝              ║\n");
	printf("║                ╚═╝  ╚═╝╚══════╝"
		"╚═╝  ╚═╝ ╚═════╝               ║\n");
}

void	print_xero_developers(void)
{
	print_xero_developers_content();
	printf("║                                "
		"                               ║\n");
	printf("║   ╔═════════════════════════════"
		"══════════════════════════╗   ║\n");
	printf("║   ║  CHIKI Badreddine    ⚔︎ Lead "
		"Parser & Core Architect   ║   ║\n");
	printf("║   ║  Alae Ben Dris Alami ⚔︎ Execu"
		"tion Engine Specialist    ║   ║\n");
	printf("║   ╚═════════════════════════════"
		"══════════════════════════╝   ║\n");
	printf("║                                 "
		"                              ║\n");
	printf("║        Thank you for choosing Xe"
		"ro.                           ║\n");
	printf("║        We're committed to contin"
		"uous improvement —            ║\n");
	printf("║        stay tuned for v1.1 and b"
		"eyond.                        ║\n");
	printf("║                                  "
		"                             ║\n");
	printf("╚══════════════════════════════════"
		"═════════════════════════════╝\n\n");
}

int	is_special_xero_command(char **args)
{
	if (!args || !args[0] || ft_strcmp(args[0], "xero") != 0)
		return (0);
	if (args[1] && ft_strcmp(args[1], "--version") == 0 && !args[2])
		return (1);
	if (args[1] && ft_strcmp(args[1], "--devs") == 0 && !args[2])
		return (1);
	return (0);
}
