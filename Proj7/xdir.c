#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFSIZE 50

int rdir(char *path, int *switches, int t);

int main(int argc, char *argv[]) {
	const char tab[] = "    ";
	int switches[] = {0,0,0}; /*-lar*/
	char *path;
	char *type;
	int i = 1;

	struct stat statbuf;
	struct dirent *dirp;
	DIR *dp;
	char buf[BUFSIZE];
	
	if (argc > 5) {
		perror("wrong number of arguments");
		return -1;
	} else {
		while(i < argc){
			if(strcmp(argv[i], "-l") == 0)
				switches[0] = 1;
			else if(strcmp(argv[i], "-a") == 0)
				switches[1] = 1;
			else if(strcmp(argv[i], "-r") == 0)
				switches[2] = 1;
			else
				path = argv[i];
			i++;
		}
		if(path == NULL){
			perror("directory not found");
			return -1;
		}
	}

	if (stat(path, &statbuf) != 0) {
		perror("stat error");
		return -1;
	}
	if (switches[2] == 0){
		if (S_ISDIR(statbuf.st_mode)) {
			if ((dp = opendir(path))) {
				int n = snprintf(buf, BUFSIZE, "%s%s\n", path, ":" );
				write(STDOUT_FILENO, buf, n);
				while ((dirp = readdir(dp)) != NULL) {
					if (switches[1] == 0 && strncmp(dirp->d_name, ".", 1) == 0)
						continue;
					if (switches[0] != 0) {
						char *temp = (char*) malloc(strlen(path)+strlen(dirp->d_name)+2);
						strcat(temp, path);
						strcat(temp, "/");
						strcat(temp, dirp->d_name);
						temp[strlen(temp)] = '\0';
						if (stat(temp, &statbuf) != 0)
							perror("file not found");
						if (S_ISREG(statbuf.st_mode))
							type = "F";
						if (S_ISDIR(statbuf.st_mode)){
							type = "D";
						}
						if (S_ISLNK(statbuf.st_mode))
							type = "L";
						if (S_ISFIFO(statbuf.st_mode))
							type = "P";
						n = snprintf(buf, BUFSIZE,"%s%s %s %d %s %d %s\n", tab, dirp->d_name, type, (int)statbuf.st_blocks, "blks", (int)statbuf.st_size, "bytes");
						free(temp);
					} else
						n = snprintf(buf, BUFSIZE, "%s%s\n", tab, dirp->d_name);
					write(STDOUT_FILENO, buf, n);
				}
			} else 
				perror("cannot open directory");
		} else 
			perror("not a directory");
	} else
		rdir(path, switches,1);
	
	return 0;
}

/* extra credit */
int rdir(char *path, int *switches, int t){
	const char tab[] = "    ";
	int i;
	char *type;
	struct stat statbuf;
	struct dirent *dirp;
	DIR *dp;
	char buf[BUFSIZE];

	if (stat(path, &statbuf) != 0) {
		perror("stat error");
		return -1;
	}
	
	if (S_ISDIR(statbuf.st_mode)) {
		if ((dp = opendir(path))) {
			int n = snprintf(buf, BUFSIZE, "%s%s\n", path, ":" );
			write(STDOUT_FILENO, buf, n);
			while ((dirp = readdir(dp)) != NULL) {
				if (strncmp(dirp->d_name, ".", 1) == 0){
					if (switches[1] == 0 && strncmp(dirp->d_name, ".", 1) == 0)
						continue;
				}
				char *temp = (char*) calloc(1, strlen(path)+strlen(dirp->d_name)+2);
				strcat(temp, path);
				strcat(temp, "/");
				strcat(temp, dirp->d_name);
				if (stat(temp, &statbuf) != 0) {
					perror("file not found");
					return -1;
				}
				if (S_ISDIR(statbuf.st_mode)){
					rdir(temp, switches, t+1);
				} else {
					if (switches[0] != 0) {
						if (S_ISREG(statbuf.st_mode))
							type = "F";
						if (S_ISLNK(statbuf.st_mode))
							type = "L";
						if (S_ISFIFO(statbuf.st_mode))
							type = "P";
						n = snprintf(buf, BUFSIZE,"%s%s %s %d %s %d %s\n", tab, dirp->d_name, type, (int)statbuf.st_blocks, "blks", (int)statbuf.st_size, "bytes");
					} else
						n = snprintf(buf, BUFSIZE, "%s%s\n", tab, dirp->d_name);
					char *out = (char *) calloc(1, BUFSIZE);
					write(STDOUT_FILENO, buf, n);
				}
				free(temp);
			}
		} else 
			perror("cannot open directory");
	} else 
		perror("not a directory");
	closedir(dp);
	return 0;
}
