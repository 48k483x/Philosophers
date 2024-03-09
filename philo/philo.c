#include "philo.h"

int  exit_with_message(char *message, char **av)
{
  printf("%s\n", message);
  free_split(av);
  return (-1);
}

int av_len(char **av)
{
  int i;

  i = 0;
  while (av[i])
    i++;
  return (i); 
}

int main(int argc, char *argv[])
{
  char **av;
  int ac;
  int *tab;

  av = _parsed_arr(_parsed_av(argc, argv));
  ac = av_len(av);
  tab = av_to_tab(ac, av);
  if (!input_check(ac, av, tab))
    return (exit_with_message("Usage: ./philo [args]", av));
  int i = 0;
  while (i < ac)
  {
    printf("%d\n", tab[i]);
    i++;
  }
  free_split(av);
  free(tab);
}
