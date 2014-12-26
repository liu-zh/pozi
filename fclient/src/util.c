#include "../include/util.h"
#include "../include/polist.h"
/****************************/
int last_index_of(char* src, const char* dest, int destlen, char a) {
	int i = destlen;
	int j = 0;
	for (; i >= 0; i--)
		if (*(dest + i) == '/')
			break;
	while ((*(src + (j++)) = *(dest + ++i)) != '\0')
		;
}

/*****************/
void analyze_config(const char* configpath, config_linklist* clist) {
	FILE *file;
	if (!(file = fopen(configpath, "r"))) {
		printf("open the config file error %s\n", strerror(errno));
		exit(-2);
	}
	char key[20];
	char value[30];
	char ch;
	int i = 0, j = 0;
	int kov = 1;
	int waste = 0;
	while ((ch = fgetc(file)) != EOF) {
		if (ch == '#')
			waste = 1;
		if (waste) {
			if (ch != '\n')
				continue;
		}
		if (ch == '\n') {
			waste = 0;
			if (!(strcmp(key, "") == 0 || strcmp(value, "") == 0)) {
				struct node_value nv;
				strcpy(nv.key, key);
				strcpy(nv.value, value);
				insert(clist, &nv);
			}
			memset(key, '\0', sizeof(key));
			memset(value, '\0', sizeof(value));

			kov = 1;
			i = j = 0;
			continue;
		}
		if (ch == '=') {
			kov = 0;
			continue;
		};
		if (kov)
			*(key + i++) = ch;
		else
			*(value + j++) = ch;
	}
	fclose(file);

}
/*******************************/
int obtain_file_list(struct dir_list_node* head, const char* dirpath) {
//printf("prevconcat %s\n",dirpath);
	char namebuf[512];
	DIR* dir;
	if (!(dir = opendir(dirpath))) {
		printf("open the directory failed!  %s %s\n", strerror(errno), dirpath);
		return 0;
	}
	struct dirent * dent;
	while ((dent = readdir(dir))) {
		if (!strcmp(dent->d_name, ".") || !strcmp(dent->d_name, ".."))
			continue;
//printf("---------------------- %s\n",dent->d_name);
		if (dent->d_type == 8) {
			// printf("---------------------- %s\n",dent->d_name);
			memset(namebuf, '\0', sizeof(namebuf));
			sprintf(namebuf, "%s/%s", dirpath, dent->d_name);
			// printf("%s/%s\n",dirpath,dent->d_name);
			insertDir(head, namebuf);
			//return;
		} else if (dent->d_type == 4) {
			memset(namebuf, '\0', sizeof(namebuf));
			sprintf(namebuf, "%s/%s", dirpath, dent->d_name);
			//printf("%s--%s\n",dirpath,dent->d_name);
			obtain_file_list(head, namebuf);
		}

	}
	closedir(dir);
}
/****************************/
int recurve_scan_dir(struct dir_list_node* head, const char* dirpath) {
	char namebuf[256];
	getcwd(namebuf, 256);
	printf("current dir %s\n", namebuf);
	if (chdir(dirpath)) {
		printf("directory name: %s\n", dirpath);
		printf("change directory error %s\n", strerror(errno));
		return 0;
	}
	DIR *dir;
	if (!(dir = opendir(dirpath))) {
		printf("open the directory failed!  %s %s\n", strerror(errno), dirpath);
		return 0;
	}
	struct dirent * dent;
	while ((dent = readdir(dir))) {
		if (!strcmp(dent->d_name, ".") || !strcmp(dent->d_name, ".."))
			continue;
		if (dent->d_type == 8) {
			memset(namebuf, '\0', sizeof(namebuf));
			printf("file: %s\n", dent->d_name);
		} else if (dent->d_type == 4) {
			recurve_scan_dir(head, dent->d_name);
		}
	}
	closedir(dir);
	return 1;
}
