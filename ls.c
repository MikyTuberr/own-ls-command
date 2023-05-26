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

// Function to display detailed information about a file/directory
void l_option(const char *path, struct dirent *entry) {
  char full_path[512];
  //(char* str, size_t size, const char* format, first %s,  second %s)
  snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

  struct stat file_info;
  if (stat(full_path, &file_info) == -1) {
    fprintf(stderr, "Error while reading information about file");
    return;
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
  char time_buffer[80];
  strftime(time_buffer, sizeof(time_buffer), "%b %d %H:%M",
           localtime(&file_info.st_mtime));
  printf(" %s", time_buffer);

  // Name of file
  printf(" \033[1;32m%s\n\033[0m", entry->d_name);
}

// Function to recursively print the contents of a directory
void R_option(const char *path) {
  DIR *dir;
  struct dirent *entry;

  dir = opendir(path);
  if (dir == NULL) {
    fprintf(stderr, "opendir() failed for directory '%s' (%s)\n", path,
            strerror(errno));
    return;
  }

  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
      char full_path[512];
      snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
      printf("%s\n", full_path);
      if (entry->d_type == DT_DIR) {
        // If it's a directory, recursively call print_directory_contents
        R_option(full_path);
      }

      // l_option(path, entry);
    }
  }

  closedir(dir);
}

int main(int argc, char *argv[]) {
  const char *path;
  
  if (argc > 1 && strcmp(argv[1], "-l") == 0) {
    if (argc == 3) {
      path = argv[2];
    } else {
      path = ".";
    }
    l_option(path, NULL);
  } else if (argc > 1 && strcmp(argv[1], "-R") == 0) {
    if (argc == 3) {
      path = argv[2];
    } else {
      path = ".";
    }
    R_option(path);
  } else {
    fprintf(stderr, "Invalid command line options\n");
    fprintf(stderr, "Usage: %s [-l|-R] [directory]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  return 0;
}
