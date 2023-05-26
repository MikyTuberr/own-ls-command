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

#define PATH_SIZE 512
#define TIME_SIZE 80

// Function to display detailed information about a file/directory
void l_option(const char *path) {
  DIR *pDIR;
  struct dirent *pDirEnt;

  pDIR = opendir(path);
  if (pDIR == NULL) {
    fprintf(stderr, "opendir() failed for directory '%s' (%s)\n", path,
            strerror(errno));
    exit(EXIT_FAILURE);
  }

  int total = 0; // Variable which contains files size
  char full_path[PATH_SIZE];

  // Get the size of files
  while ((pDirEnt = readdir(pDIR)) != NULL) {
    if (strcmp(pDirEnt->d_name, ".") != 0 && strcmp(pDirEnt->d_name, "..") != 0 
    && pDirEnt->d_name[0] != '.') {
      char full_path[PATH_SIZE];
      snprintf(full_path, sizeof(full_path), "%s/%s", path, pDirEnt->d_name);

      struct stat file_info;
      if (stat(full_path, &file_info) == -1) {
        fprintf(stderr, "Error while reading information about file");
        exit(EXIT_FAILURE);
      }

      total += file_info.st_blocks;
    }
  }

  printf("Total %d\n", (total/2));

   // Go back to beggining of catalog
  rewinddir(pDIR);

  while ((pDirEnt = readdir(pDIR)) != NULL) {
    if(pDirEnt->d_name[0] != '.') {
      //(char* str, size_t size, const char* format, first %s,  second %s)
      snprintf(full_path, sizeof(full_path), "%s/%s", path, pDirEnt->d_name);

      struct stat file_info;
      if (stat(full_path, &file_info) == -1) {
        fprintf(stderr, "Error while reading information about file");
        exit(EXIT_FAILURE);
      }

      // Type of file
      printf((S_ISDIR(file_info.st_mode)) ? "d" : "-");
      // Owner permission access
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
      char time_buffer[TIME_SIZE];
      strftime(time_buffer, sizeof(time_buffer), "%b %d %H:%M",
              localtime(&file_info.st_mtime));
      printf(" %s", time_buffer);

      // Name of content
      if(S_ISDIR(file_info.st_mode)) {
        printf(" \033[42m%s\033[0m\n", pDirEnt->d_name);
      }
      else {
        printf(" \033[1;32m%s\n\033[0m", pDirEnt->d_name);
      }
    }
  }
  closedir(pDIR);
}

// Function to recursively print the contents of a directory
void R_option(const char *path) {
  DIR *pDIR;
  struct dirent *pDirEnt;
  char recursion_path[PATH_SIZE];

  pDIR = opendir(path);
  if (pDIR == NULL) {
    fprintf(stderr, "opendir() failed for directory '%s' (%s)\n", path,
            strerror(errno));
    exit(EXIT_FAILURE);
  }

  memset(recursion_path, 0, sizeof(recursion_path));
  strcat(recursion_path, path);

  printf("%s:\n", recursion_path);

  while ((pDirEnt = readdir(pDIR)) != NULL) {
    if (strcmp(pDirEnt->d_name, ".") != 0 && strcmp(pDirEnt->d_name, "..") != 0 &&
    pDirEnt->d_name[0] != '.') {
      char full_path[PATH_SIZE];
      snprintf(full_path, sizeof(full_path), "%s/%s", path, pDirEnt->d_name);

      struct stat file_info;
      if (stat(full_path, &file_info) == -1) {
        fprintf(stderr, "Error while reading information about file");
        exit(EXIT_FAILURE);
      }
      
      // Check if it is catalog or regular file
      if(S_ISDIR(file_info.st_mode)) {
        printf("\033[42m%s\033[0m  ", pDirEnt->d_name);
        strcat(recursion_path, "/");
        strcat(recursion_path, pDirEnt->d_name);
        printf("\n");
        printf("\n");
      }
      else {
        printf("\033[1;32m%s  \033[0m", pDirEnt->d_name);
      }

      // Check if directory is catalog
      if (pDirEnt->d_type == DT_DIR) {
        // If it's a directory, recursively call print_directory_contents
        R_option(full_path);
      }
    }
  }
  closedir(pDIR);
}

// Function to print contents of directory
void default_option(const char *path) {
  DIR *pDIR;
    struct dirent *pDirEnt;
    pDIR = opendir(path);
    if (pDIR == NULL) {
      fprintf(stderr, "opendir() failed for directory '%s' (%s)\n", path,
              strerror(errno));
      exit(EXIT_FAILURE);
    }
    pDirEnt = readdir(pDIR);
    while (pDirEnt != NULL) {
      char full_path[PATH_SIZE];
      snprintf(full_path, sizeof(full_path), "%s/%s", path, pDirEnt->d_name);

      struct stat file_info;
      if (stat(full_path, &file_info) == -1) {
        fprintf(stderr, "Error while reading information about file");
        exit(EXIT_FAILURE);
      }

      if(pDirEnt->d_name[0] != '.') {
        // Check if it is catalog or regular file
        if(S_ISDIR(file_info.st_mode)) {
          printf("\033[42m%s\033[0m  ", pDirEnt->d_name);
        }
        else {
          printf("\033[1;32m%s  \033[0m", pDirEnt->d_name);
        }
      }
      pDirEnt = readdir(pDIR);
    }
    printf("\n");
    closedir(pDIR);
}

int main(int argc, char *argv[]) {
  const char *path;
  
  if (argc > 1 && strcmp(argv[1], "-l") == 0) {
    if (argc == 3) {
      path = argv[2];
    } 
    else {
      path = ".";
    }
    l_option(path);
  } 
  else if (argc > 1 && strcmp(argv[1], "-R") == 0) {
    if (argc == 3) {
      path = argv[2];
    } 
    else {
      path = ".";
    }
    R_option(path);
    printf("\n");
  } 
  else if (argc > 1) {
    fprintf(stderr, "Invalid command line options\n");
    fprintf(stderr, "Usage: %s [-l|-R] [directory]\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  else {
     path = ".";
     default_option(path);
  }

  return 0;
}
