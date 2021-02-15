#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

//#define check_readed if(readed> && readed<2){printf("Weird stupid shenanigans happened while reading file. Exiting\n");exit(0);}
#define check_readed if(readed==0){if(!do_xml){exit(0);}else{printf("</xml>\n");exit(0);}}

int main(int argc, char *argv[]){
FILE *fp;
int strip=0;
int do_count=0;
int do_length=0;
int do_xml=0;
if(argc==1){
	printf("Dumps strings stored in .o01 string files used by some Qualcomm Brew applications.\nUsage: reado01 -o <file>\nUse --help for help\n");
	exit(0);
}
int path=0;
for(int i=1;i<argc;i++){
	if(!strcmp(argv[i],"--help")){
		printf("Usage: reado01 [options] -o <file>\nOptions:\n-o: File to open\n-s: Only strip text. Doesn't print anything else but the strings or the world will explode!\n-c: Count number of strings\n-l: Sum total string lengths\n-xml: dump as xml format\n");
		exit(0);
	}
	if(!strcmp(argv[i],"-o")){
		if(!(i+1>argc)){
			path=i+1;
			i++;
		}
	}
	if(!strcmp(argv[i],"-s")){
		strip=1;
	}
	if(!strcmp(argv[i],"-c")){
		do_count=1;
	}
	if(!strcmp(argv[i],"-l")){
		do_length=1;
	}
	if(!strcmp(argv[i],"-xml")){
		do_xml=1;
	}
}
fp=fopen(argv[path],"r");
if(fp==NULL){ //Gotta Learn how to survive null pointers. Thats how you develop character!
	perror(argv[path]);
	exit(0);
}
if(path==0){
printf("No file specified\n");
exit(0);
}
int32_t buffer[]={0,0};
char *string_buffer; //puts string here.
int readed=0;
readed=fread(buffer,sizeof(int32_t),2,fp);
check_readed //mmm... macros...
if(!do_xml || !strip){
	printf("Number of strings:%i\n",buffer[0]);
	printf("Total length of strings combined:%i\n",buffer[1]);
}
int count=1;
int total_size=0;
if(do_xml){
	printf("<?xml version=\"1.0\">\n<mao/>\n");
}
while(1){
	readed=fread(buffer,sizeof(int32_t),2,fp);
	check_readed
	if(!do_xml){
		if(!strip){
			printf("String id %i\n",buffer[0]);
			printf("String length %i\n",buffer[1]);
			if(do_count){
				printf("String number %i\n",count);
				count++;
			}
			if(do_length){
				total_size+=buffer[1];
				printf("Sum of string lengths: %i\n",total_size);
			}
		}
	}else{
		printf("<string id=\"%i\">",buffer[0]);
	}
	string_buffer=malloc(sizeof(char)*buffer[1]);
	fread(string_buffer,sizeof(char),buffer[1],fp);
	if(!do_xml){
		if(!strip){
		printf("String: %s\n",string_buffer);
		}else{
		fwrite(string_buffer,sizeof(char),buffer[1],stdout);
		}
	}else{
		printf("%s%c</string>\n",string_buffer,0x00);
	}
	free(string_buffer);
}
}
