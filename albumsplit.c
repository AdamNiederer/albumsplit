/* Copyright 2015 Adam Niederer. Licensed under GNU GPL v3+
   I wrote this when I was new to c. Abandon hope, all ye who enter here. */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct song {
  char* startTime;
  char* songName;
};

int main(int argc, char** argv) {
  if(strcmp(argv[1], "--help") == 0 || argc != 3) {
    printf("albumsplit [list] [audio]\n");
    return 0;
  }
  
  int num = 0;
  size_t size = 256;
  FILE* f = fopen(argv[1], "r");
  char* line = malloc(sizeof(char) * 256);
  struct song* song = (struct song*)malloc(sizeof(struct song) * 64); // For those crazy 2-hour progressive albums
  
  for (int i = 0; i < 64; i++) {
    if(getline(&line, &size, f) == -1) break;
    printf("Read %s", line);

    song[i].songName = (char*) malloc(sizeof(char) * 128);
    song[i].startTime = (char*) malloc(sizeof(char) * 16);

    if((strchr(line, ':') - line) > 5) {
      if(sscanf(line, "%*[^A-Z] %[^0-9] %s", song[i].songName, song[i].startTime) != 2)
	printf("albumsplit: Scan Error: File should be formatted as [Number] [Name] [Time]");
    } else {
      if(sscanf(line, "%*s %[A-Z] %[^0-9]", song[i].startTime, song[i].songName) != 2)
	printf("albumsplit: Scan Error: File should be formatted as [Name] - [Time]");
    }
    num++;
  }


  for(int i = 0; i < num - 1; i++) {
    sprintf(line, "ffmpeg -i \"%s\" -ss %s -to %s -y -c:a copy -vn -b:a 256k \"%s.m4a\" > /dev/null", argv[2], song[i].startTime, song[i+1].startTime, song[i].songName); // Hacky, but whatever!
    printf("%s\n", line);
    system(line);
    free(song[i].startTime);
    free(song[i].songName);
  }
  free(song[num - 1].startTime);
  free(song[num - 1].songName);
  free(song);
  free(line);
}
