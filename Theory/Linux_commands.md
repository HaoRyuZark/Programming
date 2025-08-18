#System & User Management Commands

-whoami
    Usage: whoami
    Function: Displays the current user’s username.

-adduser
    Usage: sudo adduser username
    Function: Adds a new user to the system.

-passwd
    Usage: passwd username
    Function: Changes the password for a user.

-su
    Usage: su username
    Function: Switches the current user to another user.

-sudo
    Usage: sudo command
    Function: Executes a command with superuser privileges.

-exit
    Usage: exit
    Function: Exits the current session or shell.

#File & Directory Management

-ls
    Usage: ls, ls -l, ls -a
    Function: Lists files in the current directory.

-pwd
    Usage: pwd
    Function: Prints the current working directory.

-cd
    Usage: cd path, cd .., cd
    Function: Changes the current directory.

-mkdir
    Usage: mkdir directoryname
    Function: Creates a new directory.

-rmdir
    Usage: rmdir directoryname
    Function: Removes an empty directory.

-touch
    Usage: touch filename
    Function: Creates a new file or updates its timestamp.

-cp
    Usage: cp file destination
    Function: Copies files and directories.

-mv
    Usage: mv file destination
    Function: Moves or renames files and directories.

-rm
    Usage: rm file, rm -r directory
    Function: Removes files or directories.

-ln
    Usage: ln -s file link
    Function: Creates a symbolic link to a file.

#File Viewing & Editing

-cat
    Usage: cat filename
    Function: Displays the content of files.

-nano
    sage: nano filename
    Function: Opens a file in the Nano text editor.

-vim
    Usage: vim filename
    Function: Opens a file in the Vim text editor.

-less
    Usage: less filename
    Function: Views the content of a file one page at a time.

-more
    Usage: more filename
    Function: Similar to less, but only allows forward navigation.

-head
    Usage: head filename
    Function: Displays the first few lines of a file.

-tail
    Usage: tail filename
    Function: Displays the last few lines of a file.

#Search & Comparison

-grep
    Usage: grep pattern file
    Function: Searches for patterns in files.

-awk
    Usage: awk pattern file
    Function: A versatile text-processing command.

-find
    Usage: find directory -name filename
    Function: Searches for files in a directory hierarchy.

-locate
    Usage: locate filename
    Function: Quickly finds a file using an indexed database.

-cmp
    Usage: cmp file1 file2
    Function: Compares two files byte by byte.

-diff
    Usage: diff file1 file2
    Function: Displays the differences between two files.

-sort
    Usage: sort filename
    Function: Sorts the lines of a file.

#Process & System Information

-kill
    Usage: kill PID
    Function: Terminates a process by its PID.

killall
    Usage: killall processname
    Function: Kills all processes by name.

-jobs
    Usage: jobs
    Function: Lists background jobs.

-bg
    Usage: bg jobID
    Function: Resumes a job in the background.

-fg
    Usage: fg jobID
    Function: Brings a background job to the foreground.

-history
    Usage: history
    Function: Displays the command history.

-uptime
    Usage: uptime
    Function: Shows system uptime and load average.

#Miscellaneous

-echo
    Usage: echo 'text'
    Function: Prints text to the terminal.

-tee
    Usage: command | tee file
    Function: Saves command output to a file while displaying it.

-date
    Usage: date
    Function: Displays the current date and time.

-uptime
    Usage: uptime
    Function: Displays how long the system has been running.

-alias
    Usage: alias name='command' or alias  
    Function: Creates a shortcut for a command or if only written alias it lists all aliases.

-unalias
    Usage: unalias name
    Function eliminates the alias

-gio open
    Usage: gio open fileName.xxx
    Function: opens the file in the corresponding viewer
    
-xdg-open
   Usage: xdg-open fileName.pdf
   Function: opens the file in the corresponding viewer

- ncdu  
  Usage: ncdu [options] [directory]  
  Function: Displays disk usage of directories in a navigable interface

- duff  
  Usage: duff [options] [directories/files]  
  Function: Finds duplicate files in directories

- rg (ripGrep)  
  Usage: rg [pattern] [path]  
  Function: Recursively searches for patterns in files, like grep but faster

- mosh  
  Usage: mosh [user@]host  
  Function: Connects to remote machines over SSH with better support for roaming and disconnection

- lshw  
  Usage: lshw [options]  
  Function: Lists detailed hardware configuration information

- mtr  
  Usage: mtr [host]  
  Function: Combines traceroute and ping for real-time network diagnostics

- fd  
  Usage: fd [pattern] [path]  
  Function: Simple, fast alternative to `find`

- fzf  
  Usage: fzf  
  Function: Interactive fuzzy finder for the command line

- ranger  
  Usage: ranger [directory]  
  Function: Terminal-based file manager with VI keybindings

- zoxide (or z)  
  Usage: z [directory substring]  
  Function: Smarter cd command that remembers frequently used directories

- exa  
  Usage: exa [options] [path]  
  Function: Modern replacement for `ls` with more features and better formatting

- glances  
  Usage: glances  
  Function: Cross-platform system monitor in the terminal

- iotop  
  Usage: sudo iotop  
  Function: Shows I/O usage by processes

- stat  
  Usage: stat [file]  
  Function: Displays detailed information about a file or directory

- dstat  
  Usage: dstat [options]  
  Function: Versatile resource statistics tool

- watch  
  Usage: watch [command]  
  Function: Periodically runs a command and shows its output

- progress  
  Usage: progress  
  Function: Displays progress of core utilities like cp, mv, dd

- dig  
  Usage: dig [domain]  
  Function: DNS lookup tool for querying name servers

- dog  
  Usage: dog [domain]  
  Function: User-friendly alternative to `dig` with colorized output

- tcpdump  
  Usage: sudo tcpdump [options]  
  Function: Captures network packets for analysis

- tshark  
  Usage: tshark [options]  
  Function: Terminal-based network protocol analyzer (Wireshark CLI)

- termshark  
  Usage: termshark -i [interface]  
  Function: Terminal UI for tshark packet captures

- lsof  
  Usage: lsof [options]  
  Function: Lists open files and the processes using them

- ipcalc  
  Usage: ipcalc [IP/netmask]  
  Function: Calculates IP information (subnet, broadcast, etc.)

- wormhole  
  Usage: wormhole send [file]  
  Function: Securely transfers files using a code

- systemd-analyze blame  
  Usage: systemd-analyze blame  
  Function: Shows how long each systemd unit took to initialize

- systemd-analyze critical-chain  
  Usage: systemd-analyze critical-chain  
  Function: Visualizes boot-up order and timing of systemd units

- ps  
  Usage: ps [options]  
  Function: Displays currently running processes

- procs  
  Usage: procs  
  Function: Enhanced replacement for ps with better formatting

- lazydocker  
  Usage: lazydocker  
  Function: Terminal UI for managing Docker containers and images

- rsync  
  Usage: rsync [options] source destination  
  Function: Efficiently syncs files and directories locally or remotely

- rm  
  Usage: rm [options] [file(s)]  
  Function: Deletes files or directories

- shred  
  Usage: shred [options] file  
  Function: Overwrites a file to make data recovery harder

- moreutils (ts, errno, ifdata, vidir, vip, unp)  
  Usage: varies per tool  
  Function: Collection of useful Unix utilities (timestamp, error lookup, network stats, file editors, unpacker)

- jq  
  Usage: jq [filter] [file]  
  Function: Parses, filters, and formats JSON data

- taskwarrior  
  Usage: task [command]  
  Function: Command-line task and todo manager

- asciinema (asc)  
  Usage: asciinema [command]  
  Function: Records and shares terminal sessions as text

- fabric  
  Usage: fab [task]  
  Function: Python tool for automating SSH-based deployments

- ollama  
  Usage: ollama run [model]  
  Function: Runs large language models locally via a CLI

