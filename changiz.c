#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int init_func(int argc, char *const argv[]);
int configs(int argc, char *const argv[]);

void print_command(int argc, char *const argv[])
{
    for (int i = 0; i < argc; i++)
    {
        fprintf(stdout, "%s ", argv[i]);
    }
    fprintf(stdout, "\n");
}

int init_func(int argc, char *const argv[])
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        return 1;
    }
    FILE *file_name = fopen("global_config_user_name", "r");
    FILE *file_email = fopen("global_config_user_email", "r");
    if ((file_name == NULL) && (file_email == NULL))
    {
        fprintf(stderr, "Error no user.name exists!\n");
        fprintf(stderr, "Error no user.email exists!");
        return 1;
    }
    else if ((file_name == NULL) && (file_email != NULL))
    {
        fprintf(stderr, "Error no user.name exists!");
        return 1;
    }
    else if ((file_name != NULL) && (file_email == NULL))
    {
        fprintf(stderr, "Error no user.email exists!");
        return 1;
    }
    else
    {
        char tmp_cwd[1024];
        bool exists = false;
        struct dirent *entry;
        do
        {
            DIR *dir = opendir(".");
            if (dir == NULL)
            {
                fprintf(stderr, "Error opening current directory");
                return 1;
            }
            while ((entry = readdir(dir)) != NULL)
            {
                if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".changiz") == 0)
                {
                    exists = true;
                }
            }
            closedir(dir);

            if (getcwd(tmp_cwd, sizeof(tmp_cwd)) == NULL)
            {
                return 1;
            }

            if (strcmp(tmp_cwd, "/") != 0)
            {
                if (chdir("..") != 0)
                {
                    return 1;
                }
            }

        } while (strcmp(tmp_cwd, "/") != 0);

        if (chdir(cwd) != 0)
        {
            return 1;
        }

        if (!exists)
        {
            if (mkdir(".changiz", 0755) != 0)
            {
                return 1;
            }
        }
        else
        {
            fprintf(stderr, "changiz repository has already initialized");
        }
    }
    return 0;
}

int configs(int argc, char *const argv[])
{
    FILE *file_rn_name = fopen("right_now_config_user_name", "w");
    FILE *file_rn_email = fopen("right_now_config_user_name", "w");
    if (strcmp(argv[2], "-global") == 0)
    {
        FILE *file_name = fopen("global_config_user_name", "w");
        FILE *file_email = fopen("global_config_user_name", "w");
        if (strcmp(argv[3], "user.name") == 0)
        {
            fprintf(file_rn_name,"%s", argv[4]);
            fprintf(file_name,"%s", argv[4]);
            return 1;
        }
        else if (strcmp(argv[3], "user.email") == 0)
        {
            fprintf(file_rn_email,"%s", argv[4]);
            fprintf(file_email,"%s", argv[4]);
            return 1;
        }
    }
    else if (strcmp(argv[2], "user.name") == 0)
    {
        fprintf(file_rn_name,"%s", argv[3]);
        return 1;
    }
    else if (strcmp(argv[2], "user.email") == 0){
        fprintf(file_rn_email,"%s", argv[3]);
        return 1;
    }
    return 0;
}

// int create_configs(char *username, char *email)
//{
//     FILE *file = fopen(".changiz/config", "w");
//     if (file == NULL)
//     {
//         return 1;
//     }
//
//     fprintf(file, "username: %s\n", username);
//     fprintf(file, "email: %s\n", email);
//     fprintf(file, "last_commit_ID: %d\n", 0);
//     fprintf(file, "current_commit_ID: %d\n", 0);
//     fprintf(file, "branch: %s", "master");
//
//     fclose(file);
// if (mkdir(".changiz/commits", 0755) != 0){
//     return 1;}

//
// if (mkdir(".changiz/files", 0755) != 0)
//    {return 1;}
//
// file = fopen(".changiz/staging", "w");
// fclose(file);
//
// file = fopen(".changiz/tracks", "w");
// fclose(file);

// return 0;
// }

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        fprintf(stdout, "please enter a valid command");
        return 1;
    }
    print_command(argc, argv);

    if (strcmp(argv[1], "init") == 0)
    {
        return init_func(argc, argv);
    }
    else if (strcmp(argv[1], "config") == 0)
    {
        return configs(argc, argv);
    }
    // else if (strcmp(argv[1], "add") == 0)
    //{
    //     return run_add(argc, argv);
    // }
    // else if (strcmp(argv[1], "reset") == 0)
    //{
    //     return run_reset(argc, argv);
    // }
    // else if (strcmp(argv[1], "commit") == 0)
    //{
    //     return run_commit(argc, argv);
    // }
    // else if (strcmp(argv[1], "checkout") == 0)
    //{
    //     return run_checkout(argc, argv);
    // }
}