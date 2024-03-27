# ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <time.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>


/*  Structs  */
typedef struct s_philo
{
	pthread_t philo;
	int tid;
	int	philo_count;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int eat_count;
	int last_eat;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *print;
}   t_philo;


/*  Errors Exit  */
int  exit_with_message(char *message, char **av);

/*  Split Utils  */
char	**ft_split(char const *s, char c);
char	*alloc(const char *s, char c);
int	count_strings(char const *s, char c);
void	free_split(char **split);

/* _atoi Utils */
int _atoi(char *s);
int _is_digit(char c);
int check(char *s);

/*  Input Check  */
bool    input_check(int ac, char **av, int *tab);
bool	integer_check(int *tab, int ac);

/*  Parsing Utils  */
char				***_parsed_av(int ac, char **av);
int					_parsed_array_num(char ***tab);
char				**_parsed_arr(char ***tab);
void				free_triple_array(char ***tab);

/* av to tab */
int	*av_to_tab(int ac, char **av);

#endif // PHILOS_H