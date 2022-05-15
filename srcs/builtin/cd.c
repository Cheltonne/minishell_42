#include "../../minishell.h"

int    check_path(char *path)
{
    void        *dir;
    struct stat    st;

    // le fichier existe 0 prb vas y
    ft_bzero(&st, sizeof(struct stat));
    dir = opendir(path);
    if (dir)
    {
        closedir(dir);
        return (0);
    }
    // le fucguer existe pas
    closedir(dir);
    ft_putstr_fd("cd: ", 2);
    ft_putstr_fd(path, 2);
    ft_putstr_fd(" ", 2);
    // les differentes raisons possibles
    if (stat(path, &st) == -1)
        ft_putstr_fd("no such file or directory\n", 2);
    else if (S_ISDIR(st.st_mode))
        ft_putstr_fd("permission denied\n", 2);
    else
        ft_putstr_fd("not a directory\n", 2);
    return (1);
}

int    go_home(void)
{
    char    *path;

    path = getenv("HOME");
    if (!path)
    {
        ft_putstr_fd("cd: HOME not set\n", 2);
        return (0);
    }
    chdir(path);
    // free(path);
    return (0);
}

void update_cd(t_data *data)
{
    char *name[3];

    name[0] = ft_strdup("export");
    name[1] = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
    name[2] = ft_strdup("\0");
    export_cmd(data, name);
    // printf("je passe par la");
}

int    cd_cmd(t_data *data, char **args)
{
    // case trop d'args
    int i;

    i = 0;
    while (args[i])
        i++;
    if (i >= 3)
    {
        ft_putstr_fd("cd : too many args\n", 2);
        return (0);
    }
    // case cd tout seul cd ~
    if (!args[1] || args[1][0] == '~')
        return (go_home());
    if (check_path(args[1]))
        return (0);
    update_cd(data);
    chdir(args[1]);
    return (0);
}