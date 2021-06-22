static int	open_fd(int ac, t_data *data)
{
	int		error;

	error = 0;
	data->fd[0] = open(data->av[1], O_RDONLY);
	if (data->fd[0] <= 0)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(data->av[1], 2);
		ft_putchar_fd('\n', 2);
		error++;
	}
	data->fd[1] = open(data->av[ac - 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (data->fd[1] <= 0)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(data->av[ac - 1], 2);
		ft_putchar_fd('\n', 2);
		error++;
	}
	return (error);
}

t_data	*init_data(int ac, char **av, char **env)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->path = NULL;
	data->env = env;
	data->av = av;
	data->len = ac - 3;
	data->pipefd = (int *)malloc(sizeof(int) * (2 * data->len));
	if (!data->pipefd)
	{
		free(data);
		return (NULL);
	}
	if (open_fd(ac, data))
	{
		free(data->pipefd);
		free(data);
		return (NULL);
	}
	return (data);
}
