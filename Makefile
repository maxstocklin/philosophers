# Compilation setting
NAME	=	philo

FLAGS	=	-Wall -Wextra -Werror -g3 -fsanitize=thread
LDFLAGS =	-fsanitize=thread
CC		=	gcc
RM		= 	rm -rf 
AR		=	ar rcs

MKDIR	= 	mkdir -p

# Variables
COLOR			= \033
WHITE			= $(COLOR)[97m
CYAN			= $(COLOR)[96m
GREEN			= $(COLOR)[32m
BLUE			= $(COLOR)[34m
RED 			= $(COLOR)[31m
YELLOW			= $(COLOR)[33m
MAGENTA 		= $(COLOR)[35m
BOLD			= $(COLOR)[1m
RESET			= $(COLOR)[0m
RESET_BOLD		= $(COLOR)[21m


# Directories
PROJECT_DIR		= 	sources/
HEADERS_DIR 	= 	headers/

OBJS_DIR 		= 	objects/

# Sources
SRC_HEADER		=	philo.h
SRC_FILES		=	main.c \
					threads.c \
					check.c

SRCS			=	$(addprefix $(PROJECT_DIR),$(SRC_FILES))

# Objects
OBJ				=	$(SRCS:.c=.o)
OBJS			=	$(addprefix $(OBJS_DIR),$(OBJ))
HEADERS			=	$(addprefix $(HEADERS_DIR),$(SRC_HEADER))

$(OBJS_DIR)$(PROJECT_DIR)%.o : $(PROJECT_DIR)%.c $(HEADERS)
	@mkdir -p $(OBJS_DIR)$(PROJECT_DIR)
	@$(CC) $(FLAGS) -o $(@) -c $(<)
     
# Compilation
all:		$(NAME) asciiart

$(NAME):	$(OBJS)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(^) -o $(@)
	@echo "                                                                                                                                                                          "
	@echo "$(GREEN)████████████████████████████████████████████      PHILO OK	█████████████████████████████████████████████$(RESET)"
	@echo ""

# Remove
clean:
	@$(RM) $(OBJS)
	@$(RM) $(OBJS_DIR)
	@echo "$(GREEN)[$(WHITE)INFO$(GREEN)] DELETE $(BOLD)ALL OBJS FILE =>\n\t $(WHITE)$(OBJS:.o=.o\n\t)"
	@echo "$(GREEN)[$(WHITE)INFO$(GREEN)] CLEAN FINISH !$(RESET)"

fclean:		clean
	@$(RM) $(NAME)
	@echo "$(GREEN)[$(WHITE)INFO$(GREEN)] DELETE $(BOLD)PROGRAMME =>\n\t $(WHITE)$(NAME)"
	@echo "$(GREEN)[$(WHITE)INFO$(GREEN)] FCLEAN FINISH !$(RESET)"

re:			fclean all

.PHONY:		all fclean clean re

norm:
		norminette
		@echo "                                                                                     "
		@echo "$(GREEN)████████████████████████████████████████████   NORMINETTE OK	█████████████████████████████████████████████$(RESET)"
		@echo "                                                                                     "

# ASCII ART SISI
asciiart:
	@echo "$(RED)                                                                             "
	@echo "                                                                                     "
	@echo "                                                                                     "

	@echo "		  ██████╗ ██╗  ██╗██╗██╗      ██████╗ ███████╗ ██████╗ ██████╗ ██╗  ██╗███████╗██████╗ ███████╗    				"
	@echo "		  ██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██║  ██║██╔════╝██╔══██╗██╔════╝    				"
	@echo "		  ██████╔╝███████║██║██║     ██║   ██║███████╗██║   ██║██████╔╝███████║█████╗  ██████╔╝███████╗    				"
	@echo "		  ██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║██║   ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗╚════██║    				"
	@echo "		  ██║     ██║  ██║██║███████╗╚██████╔╝███████║╚██████╔╝██║     ██║  ██║███████╗██║  ██║███████║    				"
	@echo "		  ╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝    				"
	@echo "	 	                                                                                     "
	@echo "		                                                                                     "
	@echo "		      ██████╗ ██╗   ██╗    ███╗   ███╗███████╗████████╗ ██████╗  ██████╗██╗  ██╗██╗     ██╗"
	@echo "		      ██╔══██╗╚██╗ ██╔╝    ████╗ ████║██╔════╝╚══██╔══╝██╔═══██╗██╔════╝██║ ██╔╝██║     ██║"
	@echo "		      ██████╔╝ ╚████╔╝     ██╔████╔██║███████╗   ██║   ██║   ██║██║     █████╔╝ ██║     ██║"
	@echo "		      ██╔══██╗  ╚██╔╝      ██║╚██╔╝██║╚════██║   ██║   ██║   ██║██║     ██╔═██╗ ██║     ██║"
	@echo "		      ██████╔╝   ██║       ██║ ╚═╝ ██║███████║   ██║   ╚██████╔╝╚██████╗██║  ██╗███████╗██║"
	@echo "		      ╚═════╝    ╚═╝       ╚═╝     ╚═╝╚══════╝   ╚═╝    ╚═════╝  ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝"
	@echo "                                                                                     "
	@echo "                                                                                     "
	@echo "                                                                             $(RESET)"

