#include <dirent.h>
#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

void l_option(struct dirent *entry) {
  struct stat file_info;
  if (stat(entry->d_name, &file_info) == 1) {
    fprintf(stderr, "Error while reading information, about file");
  }

  // Type of file
  printf((S_ISDIR(file_info.st_mode)) ? "d" : "-");
  // Owner persmission access
  printf((file_info.st_mode & S_IRUSR) ? "r" : "-"); // read
  printf((file_info.st_mode & S_IWUSR) ? "w" : "-"); // write
  printf((file_info.st_mode & S_IXUSR) ? "x" : "-"); // execute/search
  // Group permission access
  printf((file_info.st_mode & S_IRGRP) ? "r" : "-"); // read
  printf((file_info.st_mode & S_IWGRP) ? "w" : "-"); // write
  printf((file_info.st_mode & S_IXGRP) ? "x" : "-"); // execute/search
  // Others permission access
  printf((file_info.st_mode & S_IROTH) ? "r" : "-"); // read
  printf((file_info.st_mode & S_IWOTH) ? "w" : "-"); // write
  printf((file_info.st_mode & S_IXOTH) ? "x" : "-"); // execute/search

  // Number of hard links
  printf(" %ld", file_info.st_nlink);

  // Owner and group
  struct passwd *owner_info = getpwuid(file_info.st_uid);
  struct group *group_info = getgrgid(file_info.st_gid);
  printf(" %s %s", owner_info->pw_name, group_info->gr_name);

  // File size
  printf(" %ld", file_info.st_size);

  // Last modified time
  char time_buffer[80];
  strftime(time_buffer, sizeof(time_buffer), "%b %d %H:%M",
           localtime(&file_info.st_mtime));
  printf(" %s", time_buffer);

  // Name of file
  printf(" \033[1;32m%s\n\033[0m\n", entry->d_name);
}

int main(int argc, char *argv[]) {
  DIR *pDIR;
  struct dirent *pDirEnt;
  pDIR = opendir(".");
  if (pDIR == NULL) {
    fprintf(stderr, "%s %d: opendir() failed (%s)\n", __FILE__, __LINE__,
            strerror(errno));
    exit(-1);
  }

  if (argc > 1 && strcmp(argv[1], "-l") == 0) {
    pDirEnt = readdir(pDIR);
    while (pDirEnt != NULL) {
      l_option(pDirEnt);
      pDirEnt = readdir(pDIR);
    }
  } else {
    pDirEnt = readdir(pDIR);
    while (pDirEnt != NULL) {
      printf("%s\n", pDirEnt->d_name);
      pDirEnt = readdir(pDIR);
    }
  }
  closedir(pDIR);
  return 0;
}