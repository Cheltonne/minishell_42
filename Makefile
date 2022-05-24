NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
FLAGS = -Llibft -lft -lreadline
RM = rm -f

# ****************************FILES******************************************* #

FILES = main \

LEXING_FILES =	lexer \
				quotes \
				env \
				expand \
				redir_scan \

EXEC_FILES = exec_utils_01 \
			 exec_utils_02 \

BUILTIN_FILES = cd \
				builtin \
				echo	\
				pwd		\
				env		\
				export	\
				unset	\
				exit	\

UTILS_FILES = utils_01 \
			  utils_02 \
			  utils_03 \
			  utils_04 \
			  free_utils_01 \
			  free_utils_02 \

ERROR_FILES = error_handling \

REDIR_FILES = pipe_utils_01 \
			  redirection_fcts \
			  redirection_utils \

SIG_FILES = signal \

GNL_FILES = get_next_line \
			get_next_line_utils \
			get_next_line_utils2 \

# *****************************DIRECTORIES************************************ #

LIBFT_DIR = libft/

GNL_DIR = gnl/

SRCS_DIR = srcs/

LEXING_DIR = $(addsuffix lexing/, $(SRCS_DIR))

EXEC_DIR = $(addsuffix exec/, $(SRCS_DIR))

BUILTIN_DIR = $(addsuffix builtin/, $(SRCS_DIR))

UTILS_DIR = $(addsuffix utils/, $(SRCS_DIR))

REDIR_DIR = $(addsuffix redirections/, $(SRCS_DIR))

SIG_DIR = $(addsuffix signal/, $(SRCS_DIR))

ERROR_DIR = $(addsuffix error_handling/, $(SRCS_DIR))

# *****************************ALL THE OTHER SHIT***************************** #

SRCS =	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES))) \
 		$(addprefix $(LEXING_DIR), $(addsuffix .c, $(LEXING_FILES))) \
 		$(addprefix $(EXEC_DIR), $(addsuffix .c, $(EXEC_FILES))) \
 		$(addprefix $(BUILTIN_DIR), $(addsuffix .c, $(BUILTIN_FILES))) \
 		$(addprefix $(UTILS_DIR), $(addsuffix .c, $(UTILS_FILES))) \
		$(addprefix $(SIG_DIR), $(addsuffix .c, $(SIG_FILES))) \
 		$(addprefix $(ERROR_DIR), $(addsuffix .c, $(ERROR_FILES))) \
		$(addprefix $(REDIR_DIR), $(addsuffix .c, $(REDIR_FILES))) \
		$(addprefix $(GNL_DIR), $(addsuffix .c, $(GNL_FILES))) \

OBJS =	$(addprefix $(SRCS_DIR), $(addsuffix .o, $(FILES))) \
 		$(addprefix $(LEXING_DIR), $(addsuffix .o, $(LEXING_FILES))) \
 		$(addprefix $(EXEC_DIR), $(addsuffix .o, $(EXEC_FILES))) \
 		$(addprefix $(BUILTIN_DIR), $(addsuffix .o, $(BUILTIN_FILES))) \
 		$(addprefix $(UTILS_DIR), $(addsuffix .o, $(UTILS_FILES))) \
		$(addprefix $(SIG_DIR), $(addsuffix .o, $(SIG_FILES))) \
 		$(addprefix $(ERROR_DIR), $(addsuffix .o, $(ERROR_FILES))) \
		$(addprefix $(REDIR_DIR), $(addsuffix .o, $(REDIR_FILES))) \
		$(addprefix $(GNL_DIR), $(addsuffix .o, $(GNL_FILES))) \

.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	echo "Building the object files and linking..."
	make -C libft
	$(CC) $(CFLAGS) -o $@ $^ $(FLAGS)
	echo "\033[0;32mall rule = DONE\033[0m"

all: $(NAME)

clean:
	echo "Getting rid of the object files..."
	make clean -C libft
	$(RM) $(OBJS)
	echo "\033[0;32mclean rule = DONE\033[0m"

fclean: clean
	echo "Removing the binary and archive files..."
	make fclean -C libft
	$(RM) $(NAME)
	echo "\033[0;32mfclean rule = DONE\033[0m"

re: clean all

.SILENT:

.PHONY: all clean fclean re
