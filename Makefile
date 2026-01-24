NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -I./libft -I./execution/builtins -I./parsing -I./execution/operators
LDFLAGS = -L./libft -lft -lreadline
RM = rm -f

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = main.c \
       xero/xero_info.c \
       execution/builtins/echo.c \
       execution/builtins/cd/cd_1.c \
       execution/builtins/cd/cd_2.c \
       execution/builtins/pwd.c \
       execution/builtins/env.c \
       execution/builtins/exit.c \
       execution/builtins/export/export_1.c \
       execution/builtins/export/export_2.c \
       execution/builtins/export/export_3.c \
       execution/builtins/export/export_4.c \
       execution/builtins/export/export_5.c \
       execution/builtins/export/export_6.c \
       execution/builtins/unset/unset_1.c \
       execution/builtins/unset/unset_2.c \
       execution/execute_cmd_utils/execute_cmd_utils_1.c \
       execution/execute_cmd_utils/execute_cmd_utils_2.c \
       execution/execute_cmd_utils/execute_cmd_utils_3.c \
       execution/execute_cmd_utils/execute_cmd_utils_4.c \
       execution/operators/in_out_redir/in_out_redir_1.c \
       execution/operators/in_out_redir/in_out_redir_2.c \
       execution/operators/append.c \
       execution/operators/heredoc/heredoc_1.c \
       execution/operators/heredoc/heredoc_2.c \
       execution/operators/heredoc/heredoc_3.c \
       execution/operators/heredoc/heredoc_4.c \
       execution/operators/heredoc/heredoc_5.c \
       execution/operators/heredoc/heredoc_6.c \
       execution/operators/heredoc/heredoc_7.c \
       execution/operators/heredoc/heredoc_8.c \
       execution/operators/pipe/pipe_1.c \
       execution/operators/pipe/pipe_2.c \
       execution/operators/pipe/pipe_3.c \
       execution/operators/operators_utils/operators_utils_1.c \
       execution/operators/operators_utils/operators_utils_2.c \
       execution/operators/operators_utils/operators_utils_3.c \
       execution/operators/operators_utils/operators_utils_4.c \
       execution/operators/operators_utils/operators_utils_5.c \
       parsing/create_cmd/create_cmd_1.c \
       parsing/create_cmd/create_cmd_2.c \
       parsing/create_cmd/create_cmd_3.c \
       parsing/create_cmd/create_cmd_4.c \
       parsing/create_cmd/create_cmd_5.c \
       parsing/expand_tokens/expand_tokens_1.c \
       parsing/expand_tokens/expand_tokens_2.c \
       parsing/expand_tokens/expand_tokens_3.c \
       parsing/expand_tokens/expand_tokens_4.c \
       parsing/expand_tokens/expand_tokens_5.c \
       parsing/free/free_1.c \
       parsing/free/free_2.c \
       parsing/input_processing/input_processing_1.c \
       parsing/input_processing/input_processing_2.c \
       parsing/read_input/read_input_1.c \
       parsing/read_input/read_input_2.c \
       parsing/read_input/read_input_3.c \
       parsing/signals/signals_1.c \
       parsing/signals/signals_2.c \
       parsing/tokenize/tokenize_1.c \
       parsing/tokenize/tokenize_2.c \
       parsing/tokenize/tokenize_3.c \
       parsing/tokenize/tokenize_4.c \
       parsing/tokenize/tokenize_5.c \
       parsing/tokenize/tokenize_6.c \
       parsing/validate_cmd/validate_cmd_1.c \
       parsing/validate_cmd/validate_cmd_2.c \
       parsing/validate_cmd/validate_cmd_3.c \
       parsing/validate_cmd/validate_cmd_4.c \
       parsing/validate_cmd/validate_cmd_5.c \
       tools/tools_1.c \
       tools/tools_2.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
