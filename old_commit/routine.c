#include "philo.h"

void eating(t_philo *philo)
{
    pthread_mutex_lock(philo->r_fork);
    print(philo, "has taken a fork");
    if (philo->philos_num == 1)
    {
        usleep(philo->phil_eat_time * 1000);
        pthread_mutex_unlock(philo->r_fork);
        return ;
    }
    pthread_mutex_lock(philo->l_fork);
    print(philo, "has taken a fork");
    philo->eating = 1;
    print(philo, "is eating");
    pthread_mutex_lock(philo->meal_lock);
    philo->last_meal = get_time();
    philo->eat_times++;
    pthread_mutex_unlock(philo->meal_lock);
    usleep(philo->phil_eat_time * 1000);
    philo->eating = 0;
    pthread_mutex_unlock(philo->r_fork);
    pthread_mutex_unlock(philo->l_fork);
}

void sleeping(t_philo *philo)
{
    print(philo, "is sleeping");
    usleep(philo->phil_sleep_time * 1000);
}

void thinking(t_philo *philo)
{
    print(philo, "is thinking");
}

void *philo_life(void *philo)
{
    t_philo *p = (t_philo *)philo;
    if (p->id % 2 == 0)
        usleep(1 * 1000);
    while (1)
    {
        eating(p);
        sleeping(p);
        thinking(p);
        // if (p->eat_times == 0)
        //     break;
    }
    return (NULL);
}