#include "philo.h"

bool exit_error(char *s)
{
    printf("%s\n", s);
    return (false);
}

int main(int ac, char **av)
{
    t_args args;
    t_philo philos[PHILOS_MAX];
    pthread_mutex_t forks[PHILOS_MAX];

    if (!init_args(&args, av, ac))
        return (1);
    init_forks(forks, philos);
    if (!init_philos(&args, philos, forks))
        return (1);
    // for(int i = 0; i < args.philos_num; i++)
    //     print_philo(philos[i]);
}
