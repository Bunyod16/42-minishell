#include "./minishell.h"
#include <stdio.h> 
#include <sys/stat.h>
#include <stdlib.h>

void	free_mem(t_shell_info *info)
{
	int		i;
	int		j;

	if (info->outfile != 0)
		free(info->outfile);
	if (info->infile != 0)
		free(info->infile);
	if (info->here_doc != 0)
		free(info->here_doc);
	i = 0;
	while (i <= info->cmd_num)
	{
		j = 0;
		while(info->simple_commands[i].argv && info->simple_commands[i].argv[j])
		{
			free(info->simple_commands[i].argv[j]);
			j++;
		}
		free(info->simple_commands[i].argv);
		i++;
	}
	free(info->simple_commands);
}

int checkIfFileExists(const char* filename)
{
    struct stat buffer;
    int exist = stat(filename,&buffer);

    if (exist == 0 && buffer.st_mode == 33261 )
        return 1;
    else  
        return 0;
}

void	free_pp(char **str)
{
	unsigned int	i;

	i = 0;
	while (str[i] && *str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}