#ifndef __FILE_H__
#define __FILE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct directory_list;
struct file_head;

typedef struct Directory {
    // The name of the directory
char *name;

struct file_list *file_head;

struct directory_list *directory_head;
    // The parent directory of the current directory
    // (NULL for the root directory)
struct Directory *parentDir;
} Directory;

// DO NOT MODIFY THIS STRUCTURE
typedef struct File {
    // The name of the file
char *name;

    // The size of the file
int size;

    // The content of the file
char *data;

    // The directory in which the file is located
Directory *dir;
} File;

typedef struct file_list {

struct File *file_data;

struct file_list *next;

struct file_list *prev;

} file_list;

typedef struct directory_list {

struct Directory *directory_data;

struct directory_list *next;

struct directory_list *prev;

} directory_list;

int separation(char *buffer, char **output);
void clear_strings(char **separation, int max_number);
int translate(char *function);
Directory *create_fs(void);
void delete_fs(Directory *root);
file_list *touch(char *filename, char *content, Directory *parent);
directory_list *mkdir(char *directoryname, struct Directory *parentDir);
void newdir(directory_list **directory_head, directory_list *new_director);
void newfile(file_list **file_head, file_list *new_file);
directory_list *search_dir(directory_list *head, char *name);
file_list *search_file(file_list *head, char *name);
void pwd(Directory *current);
void tree(Directory *current, int depth);
void ident(int depth);
void rm(file_list *rm_file);
void rmdir(directory_list *rm_director);
void cleardir(directory_list *rm_director);
void find(int max_depth, int min_size, int max_size,
char *subcontent, int level, Directory *currentD);

#endif /* __FILE_H__ */
