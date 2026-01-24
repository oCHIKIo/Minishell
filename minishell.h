/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:45:48 by bchiki            #+#    #+#             */
/*   Updated: 2025/08/02 15:54:00 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <signal.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

# define XERO_SUFFIX "@xero⚔ "

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC
}							t_token_type;

typedef enum e_check
{
	SUCCESS,
	FAIL
}							t_check;

typedef struct s_token
{
	char					*content;
	t_token_type			type;
	struct s_token			*next;
}							t_token;

typedef struct s_arg
{
	char					*content;
	struct s_arg			*next;
}							t_arg;

typedef struct s_redir
{
	char					*file;
	int						append_mode;
	int						fd;
	struct s_redir			*next;
}							t_redir;

typedef struct s_heredoc
{
	char					*delimiter;
	struct s_heredoc		*next;
}							t_heredoc;

typedef struct s_cmd
{
	t_arg					*args;
	t_redir					*input_redirs;
	t_redir					*output_redirs;
	t_heredoc				*heredocs;
	char					*heredoc_file;
	struct s_cmd			*next;
}							t_cmd;

typedef struct s_builtin
{
	char					*name;
	int						(*func)(char **, char ***);
}							t_builtin;

typedef struct s_join_vars
{
	int						len1;
	int						len2;
	int						i;
	char					*result;
}							t_join_vars;

typedef struct s_brace_parser
{
	int						start;
	int						end;
	char					*var_name;
	char					*var_value;
	char					*temp;
}							t_brace_parser;

typedef struct s_char_processor
{
	int						i;
	char					quote;
}							t_char_processor;

typedef struct s_extract
{
	char					*word;
	char					*temp;
	char					*part;
	int						start;
}							t_extract;

typedef struct s_redirect_check
{
	int						i;
	int						count;
	char					c;
}							t_redirect_check;

typedef struct s_export_handler
{
	char					*key;
	char					*equals_pos;
	int						is_valid;
}							t_export_handler;

typedef struct s_env_var_ctx
{
	char					*key;
	char					*value;
	int						is_append;
	int						count;
	char					**result;
}							t_env_var_ctx;

typedef struct s_pwd_ctx
{
	char					buffer[1024];
	char					*current_dir;
}							t_pwd_ctx;

typedef struct s_exec_state
{
	int						fd[2];
	int						in_fd;
	pid_t					pid;
	t_cmd					*current;
	int						status;
	int						exit_code;
	pid_t					last_pid;
}							t_exec_state;

typedef struct s_exec_external_state
{
	pid_t					pid;
	int						status;
	int						exit_code;
}							t_exec_external_state;

typedef struct s_exec_context
{
	char					**args;
	int						saved_stdin;
	int						saved_stdout;
	int						exit_code;
}							t_exec_context;

typedef struct s_builtin_context
{
	t_cmd					*cmd;
	char					**args;
	char					***envp;
	int						saved_stdin;
	int						saved_stdout;
}							t_builtin_context;

typedef struct s_external_context
{
	t_cmd					*cmd;
	char					**args;
	char					**envp;
	int						saved_stdin;
	int						saved_stdout;
}							t_external_context;

typedef struct s_saved_fds
{
	int						saved_stdin;
	int						saved_stdout;
}							t_saved_fds;

typedef struct s_heredoc_exec_context
{
	t_heredoc				*current;
	t_heredoc				*last_heredoc;
	char					*clean_delimiter;
	int						should_expand;
	int						pipe_fd[2];
	char					**envp;
}							t_heredoc_exec_context;

typedef struct s_hrdoc_prnt_cntx
{
	int						status;
	void					(*old_handler)(int);
	t_heredoc				*current;
	t_heredoc				*last_heredoc;
	int						pipe_fd[2];
}							t_hrdoc_prnt_cntx;

typedef struct s_heredoc_process_params
{
	t_heredoc				*current;
	t_heredoc				*last_heredoc;
	char					**envp;
	void					(*old_handler)(int);
	t_cmd					*cmd;
}							t_heredoc_process_params;

typedef struct s_heredoc_process_vars
{
	char					*clean_delimiter;
	int						should_expand;
	int						write_fd;
	char					*temp_file;
	pid_t					pid;
}							t_heredoc_process_vars;

typedef struct s_heredoc_parent_params
{
	pid_t					pid;
	int						write_fd;
	char					*temp_file;
	char					*clean_delimiter;
	void					(*old_handler)(int);
	t_cmd					*cmd;
}							t_heredoc_parent_params;

typedef struct s_heredoc_all_vars
{
	t_cmd					*cmd;
	t_heredoc				*current;
	t_heredoc				*last_heredoc;
	void					(*old_handler)(int);
}							t_heredoc_all_vars;

typedef struct s_heredoc_setup_params
{
	t_heredoc				*current;
	t_heredoc				*last_heredoc;
	char					**clean_delimiter;
	int						*should_expand;
	int						*write_fd;
	char					**temp_file;
}							t_heredoc_setup_params;

typedef struct s_heredoc_fork_params
{
	char					*clean_delimiter;
	int						should_expand;
	int						write_fd;
	char					*temp_file;
	t_cmd					*cmd;
	char					**envp;
}							t_heredoc_fork_params;

typedef struct s_execution_params
{
	char					***my_envp;
	t_token					*tokens;
	char					*input;
	int						*current_exit_status;
}							t_execution_params;

typedef struct e_validate_quotes
{
	int						j;
	int						single_quotes;
	int						double_quotes;
}							t_validate_quotes;

typedef struct e_crt_reduced_env
{
	char					**new_envp;
	int						i;
	int						new_i;
}							t_crt_reduced_env;

typedef struct e_hndl_rglr_vrible
{
	int						start;
	char					*var_name;
	char					*var_value;
	char					*temp;
}							t_hndl_rglr_vrible;

typedef struct e_prcs_single_cmd
{
	t_token					*tokens;
	t_cmd					*commands;
	t_execution_params		params;
	char					*trimmed;
}							t_prcs_single_cmd;

typedef struct e_update_existing_var
{
	char					**envp;
	char					*key;
	char					*value;
	int						is_append;
	int						index;
}							t_update_existing_var;

typedef struct s_rmv_qot_from_arg
{
	int						i;
	int						j;
	int						skip;
	int						len;
	char					quote;
	char					*result;
}							t_rmv_qot_from_arg;

typedef struct e_process_pipe_cmd
{
	t_cmd					*current_cmd;
	t_token					*start;
	t_token					*current;
}							t_process_pipe_cmd;

typedef struct e_remove_quotes
{
	char					*result;
	int						i;
	int						j;
	char					quote;
	int						len;
}							t_remove_quotes;

typedef struct s_escape_handler
{
	char					*content;
	int						i;
	char					quote;
	char					*result;
	int						*j;
}							t_escape_handler;
typedef struct s_apnd_to_exst_vlu
{
	char					*equals_pos;
	char					*old_value;
	char					*new_value;
	char					*new_entry;
	int						old_len;
	int						append_len;
}							t_apnd_to_exst_vlu;

typedef struct s_prcs_sgl_hrdc_node
{
	char					*clean_delimiter;
	int						should_expand;
	int						write_fd;
	char					*temp_file;
	t_heredoc_setup_params	setup_params;
	t_heredoc_fork_params	fork_params;
}							t_prcs_sgl_hrdc_node;

typedef struct s_exec_cmd_vars
{
	t_cmd					*current;
	int						has_pipe;
	int						exit_code;
}							t_exec_cmd_vars;

int							get_signal(void);
char						*read_input(void);
void						print_prompt(void);
void						set_signal(int sig);
void						setup_signals(void);
char						*create_prompt(void);
void						free_cmd(t_cmd *cmd);
char						*handle_absolute_path(char *cmd);
char						*get_user_input(void);
t_token						*tokenize(char *input);
void						free_args(char **args);
int							handle_fork_result_v2(pid_t pid,
								t_heredoc_fork_params *params);
int							is_absolute_or_relative_path(char *cmd);
void						free_envp(char **envp);
void						sigint_handler(int sig);
char						**copy_envp(char **envp);
void						print_xero_version(void);
void						setup_child_signals(void);
int							is_builtin(char *cmd_name);
void						free_arg_list(t_arg *args);
void						print_xero_developers(void);
void						ft_free_array(char **array);
t_check						word_is_builtin(char *word);
int							print_export_error(char *arg);
int							parse_export_arg(
								char *arg, char **key, char **value);
char						*trim_whitespace(char *str);
void						free_tokens(t_token *tokens);
t_cmd						*create_cmd(t_token *tokens);
int							validate_cmd(t_cmd *commands);
t_token_type				get_token_type(char *content);
int							is_builtin_pipeable(char *cmd);
char						*remove_export_quotes(char *str);
int							handle_redirections(t_cmd *cmd);
void						setup_interactive_signals(void);
t_check						validate_syntax(t_token *tokens);
t_check						its_redirection(t_token_type type);
int							should_expand_token(char *content);
char						*extract_word(char *input, int *i);
int							is_special_xero_command(char **args);
int							exit_status(int new_status, int set);
void						setup_parent_execution_signals(void);
char						**convert_args_to_array(t_arg *args);
char						*get_key_from_env_entry(char *entry);
t_check						validate_pipe_at_start(char *trimmed);
int							cd_builtin(char **args, char ***envp);
char						**initialize_environment(char **envp);
int							handle_single_export_arg(char *arg, char ***envp);
int							env_builtin(char **args, char ***envp);
int							pwd_builtin(char **args, char ***envp);
int							get_exit_status_from_signal(int signal);
int							echo_builtin(char **args, char ***envp);
int							exit_builtin(char **args, char ***envp);
int							unset_builtin(char **args, char ***envp);
int							execute_heredoc_fork(t_heredoc_fork_params *params);
int							setup_heredoc_processing(
								t_heredoc_setup_params *params);
char						**remove_env_var(char **envp, char *var);
void						execute_command(t_cmd *cmd, char **envp);
t_check						validate_operator_positions(char *input);
t_check						check_arithmetic_evaluation(char *input);
int							export_builtin(char **args, char ***envp);
char						*trim_input_spaces(char *input, int *len);
int							execute_builtin(char **args, char ***envp);
t_check						validate_redirect_count(char *trimmed, int len);
t_check						validate_operators_at_end(char *trimmed, int len);
t_token						*parse_and_expand_input(char *input,
								char **my_envp);
int							handle_input_redirect(t_cmd *cmd,
								t_token **current);
int							handle_heredoc_redirect(t_cmd *cmd,
								t_token **current);
int							its_valid_builtin(char *cmnd, t_token *start,
								t_token *end);
char						*ft_strjoin_three(const char *s1, const char *s2,
								const char *s3);
t_cmd						*create_and_validate_commands(t_token *tokens,
								int *current_exit_status);
char						**add_or_update_env_var(char **envp, char *key,
								char *value, int is_append);
char						*append_to_existing_value(char *existing_entry,
								char *key, char *append_value);
char						*handle_quotes_and_escapes(char *tilde_expanded,
								char **result, t_char_processor *proc);
int							execute_validated_commands(t_cmd *commands,
								t_execution_params *params);
int							handle_output_redirect(t_cmd *cmd,
								t_token **current, int append_mode);
char						**add_env_var(char **envp, char *key, char *value);
void						print_exported_vars(char **envp);
char						**create_new_envp_array(char **envp, int count);
void						free_envp_array(char **envp);
char						*create_env_entry(char *key, char *value);
char						*remove_quotes_from_arg(char *content);
void						add_input_redir(t_cmd *cmd, char *file);
char						*process_characters(char *tilde_expanded,
								char **envp, char *result);
int							handle_quote_start(char c, char *quote);
int							handle_quote_end(char c, char *quote);
int							handle_escape_sequence(t_escape_handler *params);
void						execve_external(char **args, char **envp);
char						*expand_variables(char *str, char **envp);
int							execute_external(char **args, char **envp);
void						expand_tokens(t_token *tokens, char **envp);
char						*find_command_in_path(char *cmd, char **envp);
char						*strip_quotes_from_delimiter(char *delimiter);
t_token						*create_token(char *content, t_token_type type);
char						*get_env_value_from_envp(char **envp, char *key);
int							setup_heredocs(t_heredoc *heredocs, char **envp);
t_heredoc					*find_last_heredoc(t_heredoc *heredocs);
int							setup_pipe_for_last(t_heredoc_exec_context *ctx);
void						handle_child_process(t_heredoc_exec_context *ctx);
int							handle_heredoc_parent_process(
								t_hrdoc_prnt_cntx *ctx);
int							finalize_pipe_setup(int pipe_fd[2]);
int							prepare_heredoc_delimiter(
								t_heredoc_exec_context *ctx);
int							handle_fork_error(t_heredoc_exec_context *ctx);
t_token						*tokenize_loop(char *input, t_token **tokens);
t_token						*process_word_token(char *input, int *i,
								t_token **tokens);
t_token						*process_redirect_token(char *input, int *i,
								t_token **tokens);
t_token						*process_pipe_token(char *input, int *i,
								t_token **tokens);
void						execute_builtin_in_pipe(char **args, char **envp);
void						validate_and_execute(char **args, int redir_result,
								char **envp, t_cmd *cmd);
char						*process_token_content(char *content, char **envp);
void						execute_single_command_no_pipe(t_cmd *cmd,
								char **envp);
t_check						validate_redirection(t_token *curr,
								t_token_type last_oper);
t_check						validate_final_command(t_token *cmd_start,
								t_token *current);
t_check						validate_command_start(t_token *current,
								t_token **cmd_start);
int							validate_input_syntax(char *input);
int							validate_operator_syntax(char *input);
int							validate_token_sequence(t_token *tokens);
int							skip_quoted_section(char *input, int *i);
int							check_parentheses(char *input, int i);
int							check_special_chars(char *input);
char						*ft_strjoin_with_newline(char *s1, char *s2);
int							validate_quote_syntax(char *str);
char						unclosed_quotes(char *str);
char						*trim_trailing_whitespace(char *str);
void						add_arg(t_cmd *cmd, char *content);
t_arg						*create_arg(char *content);
char						*extract_quoted_part(char *input, int *i);
void						append_single_char(char **result, char c);
void						handle_quotes(char c, char *quote);
int							validate_quotes(char *input);
char						*remove_quotes(char *content);
char						*expand_tilde_in_token(char *content, char **envp);
char						*handle_exit_status_expansion(char **result,
								int *i);
char						*handle_empty_braces(char **result, int *i);
void						token_add_back(t_token **tokens,
								t_token *new_token);
void						add_heredoc(t_cmd *cmd, char *delimiter);
int							handle_redirect(t_cmd *cmd, t_token *token,
								t_token **current);
void						add_output_redir(t_cmd *cmd, char *file,
								int append_mode);
void						skip_whitespace(char *input, int *i);
int							setup_append_redir(char *file);
int							setup_input_redir(t_redir *redir);
int							setup_output_redir(t_redir *redir);
int							should_expand_heredoc(char *original_delimiter);
int							run_builtin_commands(char **args, char ***envp);
int							handle_redirect_error(char c, int count);
int							is_numeric(char *str);
int							append_env_var(char **envp, char *key, char *value);
int							process_all_heredocs(t_cmd *commands, char **envp);
void						cleanup_and_exit(int exit_code, char ***envp);
int							validate_cd_args(char **args);
int							execute_cd_change(char **args, char ***envp);
int							execute_command_type(t_cmd *cmd,
								t_exec_context *ctx, char ***envp);
void						restore_fds(int saved_stdin, int saved_stdout);
int							execute_builtin_command(t_builtin_context *ctx);
int							execute_external_command(t_external_context *ctx);
void						execute_child_process(t_external_context *ctx);
int							handle_parent_process(pid_t pid);
void						setup_signals(void);
int							handle_child_process_exit(int status);
int							create_temp_heredoc_file(char **temp_file,
								int *write_fd);
t_heredoc					*find_last_heredoc_node(t_heredoc *heredocs);
int							build_temp_filename(char *temp_name, pid_t pid,
								int counter);
int							append_pid_to_name(char *temp_name, int len,
								pid_t pid);
int							append_counter_to_name(char *temp_name, int len,
								int counter);
int							convert_pid_to_string(char *pid_str, pid_t pid);
int							convert_counter_to_string(char *counter_str,
								int counter);
int							open_and_validate_input(char *filename);
int							open_output_file(t_redir *redir);
void						print_input_error(char *filename);
void						print_output_error(char *filename);
char						*build_full_path(const char *dir, const char *cmd);
int							wait_all(pid_t last_pid);
void						setup_parent(t_exec_state *st);
void						setup_input_redirection(t_exec_state *st);
int							handle_exit_status(int status);
int							setup_command_execution(t_cmd *cmd,
								t_exec_context *ctx, char **envp);
int							execute_pipeline(t_cmd *commands, char **envp,
								int current_exit_status);
int							execute_commands(t_cmd *commands, char ***envp,
								int current_exit_status);
t_check						validate_redirection_sequence(t_token *current,
								t_token_type *last_oper);
int							execute_single_command(t_cmd *cmd, char ***envp,
								int current_exit_status);
int							process_input_line(char *input, char ***my_envp,
								int *current_exit_status);
int							handle_empty_command(t_cmd *cmd, char **args,
								char **envp, int exit_code);
t_check						validate_pipe(t_token *current, t_token **cmd_start,
								t_token_type *last_oper);
int							setup_heredoc_input(t_cmd *cmd, int saved_stdin,
								int saved_stdout, char **args);
char						*handle_braced_variable(char *tilde_expanded,
								char **result, int *i, char **envp);
char						*handle_regular_variable(char *tilde_expanded,
								char **result, int *i, char **envp);
char						*handle_dollar_expansion(char *tilde_expanded,
								char **result, int *i, char **envp);
int							handle_heredoc_parent(pid_t pid, int write_fd,
								char *temp_file, char *clean_delimiter);
int							read_heredoc_child(int write_fd,
								char *clean_delimiter, int should_expand,
								char **envp);
int							handle_heredoc_child(int write_fd,
								char *clean_delimiter,
								int should_expand,
								char **envp);
void						initialize_heredoc_context(
								t_heredoc_exec_context *ctx,
								t_heredoc *heredocs, char **envp);

#endif
