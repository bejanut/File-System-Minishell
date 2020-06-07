#include "file.h"
//function used for separating the command options in different strings
char *create_string(char *original)
{
	char *allocation;

	allocation = (char *)malloc(strlen(original)+1);
	strcpy(allocation, original);
	return allocation;
}
int separation(char *buffer, char **output)
{	int spaces = 0;
	//testing for "create" and "delete", which don't have options
	if (strncmp("create", buffer, 6) && strncmp("delete", buffer, 6)) {
		char *temporary;
		int iterator = 0;

		temporary = strtok(buffer, " ");

		while (temporary != NULL && iterator < 5) {
			output[iterator] = create_string(temporary);
			iterator++;
			spaces++;
			temporary = strtok(NULL, " ");
		}
	} else {
		output[0] = create_string(buffer);
		spaces++;
	}
	return spaces;
}
//function used to free the memorry allocated for the strings
void clear_strings(char **separation, int max_number)
{	int iterator;

	for (iterator = 0; iterator < max_number; iterator++)
		if (separation[iterator] != NULL)
			free(separation[iterator]);
}
//function that returns a specific integer for a given command
int translate(char *function)
{	if (!strcmp(function, "create fs"))
		return 1;
	if (!strcmp(function, "delete fs"))
		return 2;
	if (!strcmp(function, "touch"))
		return 3;
	if (!strcmp(function, "mkdir"))
		return 4;
	if (!strcmp(function, "ls"))
		return 5;
	if (!strcmp(function, "pwd"))
		return 6;
	if (!strcmp(function, "cd"))
		return 7;
	if (!strcmp(function, "tree"))
		return 8;
	if (!strcmp(function, "rm"))
		return 9;
	if (!strcmp(function, "rmdir"))
		return 10;
	if (!strcmp(function, "find"))
		return 11;
	return 0; }
//creates the root of the files system
Directory *create_fs(void)
{	Directory *root;

	root = (Directory *) malloc(sizeof(Directory));
	root->name =  create_string("/");

	root->file_head = NULL;
	root->directory_head = NULL;
	root->parentDir = NULL;

	return root;
}
//deletes the root of the files system
void delete_fs(Directory *root)
{	free(root->name);
	free(root); }
//function that returns a list node variable completed with file data
file_list *touch(char *filename, char *content, Directory *parent)
{	file_list *newfile;

	newfile = (file_list *) calloc(1, sizeof(file_list));
	newfile->file_data = (File *) calloc(1, sizeof(File));

	newfile->file_data->name = create_string(filename);
	newfile->file_data->data = create_string(content);
	newfile->file_data->size = strlen(newfile->file_data->data);
	newfile->file_data->dir = parent;

	return newfile; }
//function that ties the list node in the corect possion
//(keeps the elements sorted)
void newfile(file_list **file_head, file_list *new_file)
{	if (*file_head == NULL)
	{
		new_file->next = NULL;
		new_file->prev = NULL;
		*file_head = new_file; }
	else {
		file_list *aux;

		aux = *file_head;
		if (strcmp(aux->file_data->name,
		new_file->file_data->name) > 0) {
			new_file->prev = NULL;
			new_file->next = aux;
			aux->prev = new_file;
			*file_head = new_file; }
		else {
			if (aux->next == NULL) {
				new_file->prev = aux;
				new_file->next = NULL;
				aux->next = new_file; }
			else {
				while (aux->next != NULL) {
					if (strcmp(aux->next->file_data->name,
						new_file->file_data->name) <= 0)
						aux = aux->next;
					else
						break;
				}

				if (aux->next == NULL) {
					aux->next = new_file;
					new_file->prev = aux;
					new_file->next = NULL; }
				else {
					new_file->prev = aux;
					new_file->next = aux->next;
					aux->next->prev = new_file;
					aux->next = new_file; }
			}
		}
	}
}
//function that returns a list node variable completed with directory data
directory_list *mkdir(char *directoryname, struct Directory *parentDir)
{
	directory_list *new_director;

	new_director = (directory_list *) malloc(sizeof(directory_list));
	new_director->directory_data = (Directory *) malloc(sizeof(Directory));

	new_director->directory_data->name = create_string(directoryname);
	new_director->directory_data->file_head = NULL;
	new_director->directory_data->directory_head = NULL;
	new_director->directory_data->parentDir = parentDir;

	return new_director;
}
//function that ties the list node in the corect possion
//(keeps the elements sorted)
void newdir(directory_list **directory_head, directory_list *new_director)
{
	if (*directory_head == NULL) {
		new_director->next = NULL;
		new_director->prev = NULL;
		*directory_head = new_director; }
	else {
		directory_list *aux;

		aux = *directory_head;
		if (strcmp(aux->directory_data->name,
new_director->directory_data->name) > 0) {
			new_director->prev = NULL;
			new_director->next = aux;
			aux->prev = new_director;
			*directory_head = new_director; }
		else {
			if (aux->next == NULL) {
				new_director->prev = aux;
				new_director->next = NULL;
				aux->next = new_director; }
			else {
				while (aux->next != NULL) {
					if (strcmp(
					aux->next->directory_data->name,
					new_director->directory_data->name)
						<= 0)
						aux = aux->next;
					else
						break;
				}

				if (aux->next == NULL) {
					aux->next = new_director;
					new_director->prev = aux;
					new_director->next = NULL; }
				else {
					new_director->prev = aux;
					new_director->next = aux->next;
					aux->next->prev = new_director;
					aux->next = new_director; }
			}
		}
	}
}
//serches for a specific node, using a directory name
//returns the adress of the node, if found and NULL if not
directory_list *search_dir(directory_list *head, char *name)
{
	directory_list *aux;

	aux = head;
	while (aux != NULL) {
		if (strcmp(aux->directory_data->name, name))
			aux = aux->next;
		else
			break;
	}
	return aux;
}
//same as search_dir but used for searching for a file
file_list *search_file(file_list *head, char *name)
{
	file_list *aux;

	aux = head;
	while (aux != NULL) {
		if (strcmp(aux->file_data->name, name))
			aux = aux->next;
		else
			break;
	}
	return aux;
}
//goes back to the root directory recursively and then prints
//all the the name of the directories it went throgh
void pwd(Directory *current)
{
	if (strcmp(current->name, "/")) {
		pwd(current->parentDir);
		printf("/%s", current->name);
	}
}
//prints all files and for every directory it's called recursivley
void tree(Directory *current, int depth)
{
	file_list *aux_file;
	//depth is used to print a specific number of spaces depending
	//on the depth of a directory
	ident(depth);
	depth++;
	printf("%s\n", current->name);

	aux_file = current->file_head;

	while (aux_file != NULL) {
		ident(depth);
		printf("%s\n", aux_file->file_data->name);
		aux_file = aux_file->next;
	}

	directory_list *aux_dir;

	aux_dir = current->directory_head;
	//the function is called for every directory
		while (aux_dir != NULL) {
			tree(aux_dir->directory_data, depth);
			aux_dir = aux_dir->next;
		}
}

void ident(int depth)
{
	int i;

	for (i = 0; i < depth; i++)
		printf("    ");
}
//removes a specific list node(rm_file) frees its memory
//and changes the list head if necessary
void rm(file_list *rm_file)
{
	file_list *aux;

	if (rm_file->prev != NULL) {
		if (rm_file->next != NULL)
			rm_file->next->prev = rm_file->prev; }
	else {
		if (rm_file->next != NULL)
			rm_file->next->prev = NULL;
		aux = rm_file->next;
		rm_file->file_data->dir->file_head = aux;
		free(rm_file->file_data->name);
		free(rm_file->file_data->data);
		free(rm_file->file_data);
		free(rm_file);
		return;
	}

	if (rm_file->next != NULL) {
		if (rm_file->prev != NULL)
			rm_file->prev->next = rm_file->next; }
	else {
		if (rm_file->prev != NULL)
			rm_file->prev->next = NULL;
		free(rm_file->file_data->name);
		free(rm_file->file_data->data);
		free(rm_file->file_data);
		free(rm_file);
		return; }

	free(rm_file->file_data->name);
	free(rm_file->file_data->data);
	free(rm_file->file_data);
	free(rm_file);
}
//frees the memory for all the files and subdirectories of a directory,
//deleting it in the end
void rmdir(directory_list *rm_director)
{
	file_list *aux_file;

	aux_file = rm_director->directory_data->file_head;
	if (aux_file != NULL) {
		while (aux_file->next != NULL)
			rm(aux_file->next);
		rm(aux_file);
	}
	directory_list *aux_dir;

	aux_dir = rm_director->directory_data->directory_head;
	if (aux_dir != NULL) {
		while (aux_dir->next != NULL)
			rmdir(aux_dir->next);
		rmdir(aux_dir);
	}
	cleardir(rm_director);
}
/*removes a list node from the list and frees it's memory*/
void cleardir(directory_list *rm_director)
{
	directory_list *aux;

	if (rm_director->prev != NULL) {
		if (rm_director->next != NULL)
			rm_director->next->prev = rm_director->prev; }
	else {
		if (rm_director->next != NULL)
			rm_director->next->prev = NULL;

		Directory *parent = rm_director->directory_data->parentDir;

		aux = rm_director->next;
		free(rm_director->directory_data->name);
		free(rm_director->directory_data);
		free(rm_director);
		parent->directory_head = aux;
		return;
	}

	if (rm_director->next != NULL) {
		if (rm_director->prev != NULL)
			rm_director->prev->next = rm_director->next; }
	else {
		if (rm_director->prev != NULL)
			rm_director->prev->next = NULL;
		free(rm_director->directory_data->name);
		free(rm_director->directory_data);
		free(rm_director);
		return;
	}

	free(rm_director->directory_data->name);
	free(rm_director->directory_data);
	free(rm_director);
}

void find(int max_depth, int min_size, int max_size,
	char *subcontent, int level, Directory *currentD)
{
	file_list *aux_file;

	aux_file = currentD->file_head;
	while (aux_file != NULL) {
		if (aux_file->file_data->size >= min_size &&
		aux_file->file_data->size <= max_size &&
		strstr(aux_file->file_data->data, subcontent) != NULL)
			printf("%s ", aux_file->file_data->name);
		aux_file = aux_file->next;
	}
	if (level < max_depth) {
		directory_list *aux_dir;

		aux_dir = currentD->directory_head;
		while (aux_dir != NULL) {
			find(max_depth, min_size, max_size, subcontent,
				level + 1, aux_dir->directory_data);
			aux_dir = aux_dir->next;
		}
	}
}
