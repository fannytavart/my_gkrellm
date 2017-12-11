NAME		 = my_gkrellm

CC		 = g++
CPPFLAGS	+= -Wall -Wextra
CPPFLAGS	+= -std=c++11 -lncurses -Iinclude/
CPPFLAGS	+= -Werror

MODULES_DIR	 = modules/
MODULES_FILES	 = ModuleDateTime.cpp		\
		   ModuleRAM.cpp		\
		   ModuleCPU.cpp		\
		   ModuleNames.cpp		\
		   ModuleNetwork.cpp		\
		   ModuleOS.cpp
MODULES		 = $(addprefix $(MODULES_DIR), $(MODULES_FILES))

SRCS_DIR	 = src/
SRCS_FILES	 = AModuleText.cpp	\
		   IMonitorDisplay.cpp	\
		   IMonitorModule.cpp	\
		   MonitorDisplay.cpp	\
		   ModuleElem.cpp	\
		   main.cpp		\
		   $(MODULES)
SRCS		 = $(addprefix $(SRCS_DIR), $(SRCS_FILES))

OBJS		 = $(SRCS:.cpp=.o)

RM		 = rm -f


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) -lncurses

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
