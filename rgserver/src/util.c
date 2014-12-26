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
