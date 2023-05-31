# Own ls command
The LS project is a simple program written in C, that emulates the basic functionality of the "ls" command in Unix/Linux systems. 
The LS program allows listing files and directories in a specified directory, as well as displaying detailed information about files, such as permissions, size, owner, group, modification date, etc.
## Compilation Instructions
Make sure you have a C compiler installed, such as gcc.

Download the C source file for the LS project.

In the directory where the source file is located, open a terminal and run the following command to compile the LS program: gcc ls.c -o ls.
After successful compilation, you can run the LS program by executing the following command: ./ls [options] [directory]
## Usage
```
The LS program supports the following command-line options:

-l: Display detailed information about files and directories.
-R: Recursively list files and directories.
-a: Include hidden files and directories in the listing.
-h: Display file sizes in human-readable format.
-s: Display file sizes in blocks.

By default, running the LS program without any options will list files and directories in the current directory.
```
## Examples

#### List files and directories in the current directory:</p>
```
./ls
```
#### Display detailed information about files and directories in a specific directory: 
```
./ls -l /path/to/directory
```
### Recursively list files and directories, including hidden ones: 
```
./ls -R -a
```
### Sort files by modification time and display file sizes in human-readable format: 
```
./ls -t -h
```
## Author
MikyTuberr / Piotr

Email: pio1342@gmail.com
## Bug Reports
please contact pio1342@gmail.com to report any bugs errors, or typos.
## More information
For more information and usage details, please refer to the comments in the source code of the LS program.
