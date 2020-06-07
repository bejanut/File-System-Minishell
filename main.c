#include "file.h"


int main(void)
{
int test = 1, option, strings_number;
Directory *root, *currentD;
char buffer[100], *strings_vector[5];

do {
	fgets(buffer, 100, stdin);
	//the new line caracter "\n" is being removed from the string
	buffer[strlen(buffer)-1] = 0;
	strings_number = separation(buffer, strings_vector);
	option = translate(strings_vector[0]);

	switch (option) {
		case 1:{
			root = create_fs();
			currentD = root;
			break;
		}
		case 2: {

			delete_fs(root);
			test = 0;
			break;
		}
		case 3: {
			if (search_file(currentD->file_head,
			strings_vector[1]) == NULL) {
				file_list *new_file, *head;

				new_file = touch(strings_vector[1],
					strings_vector[2], currentD);
				head = currentD->file_head;
				newfile(&head, new_file);
				currentD->file_head = head;
			}
			break;
		}
		case 4: {
			if (search_dir(currentD->directory_head,
				strings_vector[1]) == NULL) {
				directory_list *new_director, *head;

				new_director = mkdir(strings_vector[1],
					currentD);
				head = currentD->directory_head;
				newdir(&head, new_director);
				currentD->directory_head = head;
			}
			break;
		}
		case 5: {
			file_list *aux_file;

			aux_file = currentD->file_head;
				while (aux_file != NULL) {
					printf("%s ",
						aux_file->file_data->name);
					aux_file = aux_file->next;
				}

			directory_list *aux_dir;

			aux_dir = currentD->directory_head;
				while (aux_dir != NULL) {
					printf("%s ",
						aux_dir->directory_data->name);
					aux_dir = aux_dir->next;
				}
			printf("\n");
			break;
		}
		case 6: {
			if (strcmp(currentD->name, "/"))
				pwd(currentD);
			else
				printf("/");
			printf("\n");
			break;
		}
		case 7: {
			if (strcmp(strings_vector[1], "..")) {
				directory_list *searched;
				Directory *new_director;

				searched = search_dir(currentD->directory_head,
					strings_vector[1]);
				if (searched != NULL) {
					new_director = searched->directory_data;
					currentD = new_director; }
				else
					printf(
						"Cannot move to '%s': No such directory!\n"
						, strings_vector[1]); }
			else
				currentD = currentD->parentDir;
			break;
		}
		case 8: {
			tree(currentD, 0);
			break;
		}
		case 9: {
			file_list *searched;

			searched = search_file(currentD->file_head,
				strings_vector[1]);
			if (searched)
				rm(searched);
			else
				printf("Cannot remove '%s': No such file!\n",
					strings_vector[1]);
			break;
		}
		case 10: {
			directory_list *searched;

			searched = search_dir(currentD->directory_head,
				strings_vector[1]);
			if (searched)
				rmdir(searched);
			else
				printf(
					"Cannot remove '%s': No such directory!\n"
					, strings_vector[1]);
			break;
		}
		case 11: {
			int max_depth, min_size, max_size;

			max_depth = atoi(strings_vector[1]);
			min_size = atoi(strings_vector[2]);
			max_size = atoi(strings_vector[3]);
			find(max_depth, min_size, max_size,
			 strings_vector[4], 0, currentD);
			printf("\n");
			break;
		}
		case 0: {

			//Case that can print a specific error message if needed
		}
	}
	clear_strings(strings_vector, strings_number);
} while (test);
}
