#include "../../includes/minishell.h"

// cd - no directory specified: go to home directory
// cd - directory specified: go to that directory
// cd .. - go to parent directory one step back
// cd . - go to current directory
// cd ../path/to/dir

/**
 * implementation of cd command
*/

int ft_cd(t_minishell *minishell)
{

    
    char *tmp = NULL;
    
    if (minishell->oldpwd == NULL)
        minishell->oldpwd = getcwd(NULL, 0);
    if (minishell->cmd_node->cmd_full[1] == NULL)
    {
        free(minishell->oldpwd); 
        minishell->oldpwd = getcwd(NULL, 0);
        if (chdir(getenv("HOME")) == -1)
            return (4);
    
    }
    else
    {  
        if (!ft_strncmp(minishell->cmd_node->cmd_full[1], "-", 2))
        {
            chdir(getenv("OLDPWD"));
        }
        else
        {
            free(minishell->oldpwd); 
            minishell->oldpwd = getcwd(NULL, 0);
            if (chdir(minishell->cmd_node->cmd_full[1]) == -1)
            {
                return (4);
                // // fprintf(stderr, C_RED "cd: %s: No such file or directory\n" C_RESET, minishell->cmd_node->cmd_full[1]);
            }
        }
    }
    // // fprintf(stderr, C_GREEN "old pwd: %s\n" C_RESET, minishell->oldpwd);
    // // fprintf(stderr, C_GREEN "new pwd: %s\n" C_RESET, getcwd(NULL, 0));
    return (0);
}

// typedef struct s_path
// {
//     char *path;
//     struct s_path  *next;
// }   t_path;

// /**
//  * new node for t_path
// */

// t_path *new_cd_node(char *path)
// {
//     t_path *new_node;
//     new_node = (t_path *)malloc(sizeof(t_path));
//     if (!new_node)
//         return (NULL);
//     new_node->next = NULL;
//     new_node->path = path;
//     return (new_node);
// }

// static void	t_add_cd_node(t_path **head, t_path *new)
// {
// 	t_path	*tmp;
// 	if (!*head)
// 	{
// 		*head = new;
// 		return ;
// 	}
// 	tmp = *head;
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	tmp->next = new;
// }

// static void remove_last_node(t_path **head)
// {
//     t_path *tmp;
//     t_path *prev;
//     tmp = *head;
//     prev = NULL;
//     while (tmp->next)
//     {
//         prev = tmp;
//         tmp = tmp->next;
//     }
//     prev->next = NULL;
//     free(tmp);
// }

// void ft_cd(t_minishell *minishell)
// {
//     t_path *p;
//     char *final_path;
//     char **split_cwd;
//     char **split_path;
//     char *home_dir;
//     char *cwd;

//     p = malloc(sizeof(t_path));
//     home_dir = getenv("HOME");
//     final_path = NULL;
//     cwd = getcwd(NULL, 0);
//     p->path = NULL;
//     p->next = NULL;
    
//     if (minishell->cmd_node->cmd_full[1] == NULL)
//     {
//         // fprintf(stderr, C_RED "cd: PATH not set going to home directory\n" C_RESET);
//         final_path = ft_strdup(home_dir);
//     }
    
    // else if (ft_strnstr(minishell->cmd_node->cmd_full[1], "..", 2) != NULL)
    // {
    //     split_cwd = ft_split(cwd, '/');
    //     split_path = ft_split(minishell->cmd_node->cmd_full[1], '/');
    //     p = new_cd_node(split_cwd[0]);
    //     for (int i = 1; split_cwd[i]; i++)
    //     {
    //         t_add_cd_node(&p, new_cd_node(split_cwd[i]));
    //     }
    //     // int i = 0;
    //     // while(p)
    //     // {
    //     //     // fprintf(stderr, "split_cwd[%d]: %s\n", i, split_cwd[i]);
    //     //     // fprintf(stderr, "p->path[%d]: %s\n", i, p->path);
    //     //     i++;
    //     //     p = p->next;
    //     // }
    //     // for (int i = 0; split_path[i]; i++)
    //     // {
    //     //     // fprintf(stderr, "split_path[%d]: %s\n", i, split_path[i]);
    //     // }
    //     int i = 0;
    //     while (split_path[i])
    //     {
    //         if (ft_strncmp(split_path[i], "..", 2) == 0)
    //             remove_last_node(&p);
    //         else
    //             t_add_cd_node(&p, new_cd_node(split_path[i]));
    //         i++;
    //     }
    //     i = 0;
    //     final_path = ft_strdup("/");
    //     while (p)
    //     {
    //         p->path = ft_strjoin(p->path, "/");
    //         final_path = ft_strjoin(final_path, p->path);
    //         // fprintf(stderr, "p->path[%d]: %s\n", i, p->path);
    //         i++;
    //         p = p->next;
    //     }
    //     // fprintf(stderr, C_GREEN "final_path: %s\n" C_RESET, final_path);
    // }
    // else
    // {
    //     final_path = ft_strdup(minishell->cmd_node->cmd_full[1]);
    //     // fprintf(stderr, C_RED "HELLO\n" C_RESET);
    //     // fprintf(stderr, C_GREEN "final_path: %s\n" C_RESET, final_path);
    // }

    // if (chdir(minishell->cmd_node->cmd_full[1]) == -1)
    //     // fprintf(stderr, C_RED "cd: %s: No such file or directory\n" C_RESET, final_path);
    // else 
    //     // fprintf(stderr, C_GREEN "new pwd: %s\n" C_RESET, getcwd(NULL, 0));
// }

// cwd: current directory /nfs/homes/mnurlybe/42Cursus/minishell/minishell2009_last
// cmd_full[1]: ../../minitalk/../minishell