//for x in {00..11}; do for y in {00..05}; do wget http://home.nith.no/~raakje/part_"$x"-"$y"; done; done
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define _X_Length 12
#define _Y_Length 6

typedef struct{
	char* line[_X_Length][_Y_Length][10];
}FileData;

FILE* OpenFile(int x, int y);
void PrintAscii(FileData *data);
void GetInfoFromFiles(FileData *data);

int main()
{	
	FileData data;
	GetInfoFromFiles(&data);
	PrintAscii(&data);		
	return 0;		
}

void GetInfoFromFiles(FileData *data){
	for(int y = 0; y < _Y_Length; y++){
		for (int x  = 0; x < _X_Length; x++){
			FILE* file = OpenFile(x,y);
			for (int lines = 0; lines < 10; lines++){
				data->line[x][y][lines] = calloc(1000, sizeof(char));
				fread (data->line[x][y][lines], sizeof(char), 10, file );
			}
			fclose(file);
		}
	}
}

void PrintAscii(FileData *data){
	//tegner ascii og ikke binary
	FILE* final = fopen("test6", "w");
	for(int y = 0; y < _Y_Length; y++){
		for (int lines = 0; lines < 10; lines++){
			for (int x = 0; x < _X_Length; x++){
				fputs (data->line[x][y][lines], final);
				free(data->line[x][y][lines]);
			}
		}
	}
	fclose(final);
}

FILE* OpenFile(int x, int y){
	char *filename = calloc(1000, sizeof(char));
	sprintf(filename, "part_%02i-%02i", x,y);
	FILE* file = fopen(filename,"rb");
	free(filename);
	return file;
}

