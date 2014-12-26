#include <stdio.h>  
#include <dirent.h>  
#include <string.h>  
  
void List(char *path)  
{  
    struct dirent *ent = NULL;  
    DIR *pDir;  
    if((pDir = opendir(path)) != NULL)  
    {  
        while(NULL != (ent = readdir(pDir)))  
        {  
            if(ent->d_type == 8)                 // d_type：8-文件，4-目录  
                printf("File:\t%s\n", ent->d_name);  
            else if(ent->d_name[0] != '.')  
            {  
                printf("\n[Dir]:\t%s\n", ent->d_name);  
                List(ent->d_name);                   // 递归遍历子目录  
                printf("返回[%s]\n\n", ent->d_name);  
            }  
        }  
        closedir(pDir);  
    }  
    else  
        printf("Open Dir-[%s] failed.\n", path);  
}  
  
int main()   
{           
    char path[] = "/home/hadoop";  
    List(path);  
  
    return 0;   
}  
