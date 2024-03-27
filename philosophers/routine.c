#include "philo.h"

void eating(t_philo *philo)
{
    pthread_mutex_lock(&philo->l_fork);
    printf("%ld %d has taken a fork\n", get_time() - philo->start_time, philo->id);
    if (philo->philos_num == 1)
    {
        usleep(philo->phil_death_time * 1000);
        exit(0);
    }
    pthread_mutex_lock(&philo->r_fork);
    printf("%ld %d has taken a fork\n", get_time() - philo->start_time, philo->id);
    printf("%ld %d is eating\n", get_time() - philo->start_time, philo->id);
    philo->eating = 1;
    usleep(philo->phil_eat_time * 1000);
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->l_fork);
    pthread_mutex_unlock(&philo->r_fork);

}

void sleeping(t_philo *philo)
{
    printf("%ld %d is sleeping\n", get_time() - philo->start_time, philo->id);
    philo->eating = 0;
    usleep(philo->phil_sleep_time * 1000);
}

void thinking(t_philo *philo)
{
    printf("%ld %d is thinking\n", get_time() - philo->start_time, philo->id);
}

void *philo_life(void *philo)
{
    t_philo *p = (t_philo *)philo;

    while (1)
    {
        eating(p);
        p->eat_times--;
        if (p->eat_times == 0)
            break;
        sleeping(p);
        thinking(p);
    }
    return (NULL);
}