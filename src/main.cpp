#include "MonitorDisplay.hpp"

int	main(int ac, char **av, char const **env)
{
  try
    {
      MonitorDisplay	*monitor = new MonitorDisplay(env);
      (void)ac;
      (void)av;
      monitor->displayModules();
      monitor->loopHandle();
    }
  catch (std::exception e)
    {
      std::cout << "Error: " << e.what() << std::endl;
      return (1);
    }
  return (0);
}
