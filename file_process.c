#include "./file_process.h"

int append_to_file(char* filename,  char* content){

	char file_n[128];
	//strcpy(file_n,"./bf_ibe_data/");
	strcpy(file_n, filename);
	//sprintf(file_n + strlen(file_n),"%d",num);
//	strcpy(file_n + strlen(file_n),".txt");

	printf("filename = %s\n",file_n);

  	FILE* fp = fopen(file_n,"a+");
	fprintf(fp,"%s\n",content);

	fclose(fp);
	return 0;
}
