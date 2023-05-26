# Own ls command

The LS project is a simple program written in C that emulates the basic functionality of the "ls" command in Unix/Linux systems. The LS program allows listing files and directories in a specified directory, as well as displaying detailed information about files, such as permissions, size, owner, group, modification date, etc.

Compilation Instructions

Make sure you have a C compiler installed, such as gcc.

Download the C source file for the LS project.

In the directory where the source file is located, open a terminal and run the following command to compile the LS program: gcc ls.c -o ls.
After successful compilation, you can run the LS program by executing the following command: ./ls [options] [directory]

#Usage

<p>The LS program supports the following command-line options:</p>

<p>-l: Display detailed information about files and directories.</p>
<p>-R: Recursively list files and directories.</p>
<p>-a: Include hidden files and directories in the listing.</p>
<p>-h: Display file sizes in human-readable format.</p>
<p>-t: Sort files by modification time (most recent first).</p>
<p>-r: Reverse the order of the listing.</p>
<p>-s: Display file sizes in blocks.</p>
<p>By default, running the LS program without any options will list files and directories in the current directory.</p>

#Examples
<p>List files and directories in the current directory: ./ls</p>
<p>Display detailed information about files and directories in a specific directory: ./ls -l /path/to/directory</p>
<p>Recursively list files and directories, including hidden ones: ./ls -R -a</p>
<p>Sort files by modification time and display file sizes in human-readable format: ./ls -t -h</p>

<p>For more information and usage details, please refer to the comments in the source code of the LS program.</p>
