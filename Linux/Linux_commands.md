# Linux Commands

## System & User Management

---

- `whoami`
  - **Function**: Displays the current logged-in user's username.
  - **Example Usage**: `whoami`

---

- `adduser [flags] <username>`
  - **Function**: Adds a new user account to the system.
  - **Flags**:
    - `--home <dir>`: Specify the home directory for the new user.
    - `--shell <shell>`: Set the login shell.
    - `--gecos <info>`: Set the GECOS field (full name, etc.).
    - `--disabled-password`: Create the user without a password.
  - **Parameters**:
    - `<username>` *(required)*: Name of the new user.
  - **Example Usage**: `sudo adduser john`

---

- `passwd [flags] [username]`
  - **Function**: Changes the password for a user account.
  - **Flags**:
    - `-l`: Lock the account (disable login).
    - `-u`: Unlock the account.
    - `-d`: Delete the password (allow passwordless login).
    - `-e`: Expire the password immediately, forcing a change on next login.
  - **Parameters**:
    - `[username]` *(optional)*: Target user; defaults to the current user.
  - **Example Usage**: `passwd john` / `sudo passwd -l john`

---

- `su [flags] [username]`
  - **Function**: Switches to another user account within the current session.
  - **Flags**:
    - `-` / `-l`: Start a login shell as the target user (loads full environment).
    - `-c <cmd>`: Run a single command as the target user.
    - `-s <shell>`: Use a specific shell instead of the default.
  - **Parameters**:
    - `[username]` *(optional)*: User to switch to; defaults to `root`.
  - **Example Usage**: `su - john` / `su -c "ls /root" root`

---

- `sudo [flags] <command>`
  - **Function**: Executes a command with superuser (or another user's) privileges.
  - **Flags**:
    - `-u <user>`: Run as this user instead of `root`.
    - `-i`: Start an interactive root login shell.
    - `-s`: Start a shell with elevated privileges.
    - `-l`: List allowed commands for the current user.
    - `-k`: Invalidate cached credentials (re-prompt for password next time).
  - **Parameters**:
    - `<command>` *(required)*: The command to execute with elevated privileges.
  - **Example Usage**: `sudo apt update` / `sudo -u www-data ls /var/www`

---

- `exit [n]`
  - **Function**: Exits the current shell session or script.
  - **Parameters**:
    - `[n]` *(optional)*: Exit status code to return (default: `0`).
  - **Example Usage**: `exit` / `exit 1`

---

## File & Directory Management

---

- `ls [flags] [path]`
  - **Function**: Lists files and directories.
  - **Flags**:
    - `-l`: Long format — shows permissions, owner, size, and date.
    - `-a`: Show all files, including hidden ones (starting with `.`).
    - `-h`: Human-readable file sizes (used with `-l`).
    - `-r`: Reverse sort order.
    - `-t`: Sort by modification time (newest first).
    - `-S`: Sort by file size (largest first).
    - `-R`: Recursively list subdirectories.
  - **Parameters**:
    - `[path]` *(optional)*: Directory to list; defaults to current directory.
  - **Example Usage**: `ls -lah /home` / `ls -lt`

---

- `pwd`
  - **Function**: Prints the absolute path of the current working directory.
  - **Example Usage**: `pwd`

---

- `cd [path]`
  - **Function**: Changes the current working directory.
  - **Parameters**:
    - `[path]` *(optional)*: Target directory. Use `..` to go up, `~` for home, `-` for the previous directory.
  - **Example Usage**: `cd /var/log` / `cd ..` / `cd -`

---

- `mkdir [flags] <dirname>`
  - **Function**: Creates one or more new directories.
  - **Flags**:
    - `-p`: Create parent directories as needed; no error if they already exist.
    - `-v`: Verbose — print each created directory.
    - `-m <mode>`: Set directory permissions (e.g., `755`).
  - **Parameters**:
    - `<dirname>` *(required)*: Name or path of the directory to create.
  - **Example Usage**: `mkdir -p ~/projects/my-app/src`

---

- `rmdir [flags] <dirname>`
  - **Function**: Removes an **empty** directory.
  - **Flags**:
    - `-p`: Remove parent directories if they also become empty.
    - `-v`: Verbose output.
  - **Parameters**:
    - `<dirname>` *(required)*: Directory to remove (must be empty).
  - **Example Usage**: `rmdir old_folder` / `rmdir -p a/b/c`

---

- `touch [flags] <filename>`
  - **Function**: Creates a new empty file or updates the access/modification timestamp of an existing file.
  - **Flags**:
    - `-a`: Change only the access time.
    - `-m`: Change only the modification time.
    - `-t <stamp>`: Set a specific timestamp in `[[CC]YY]MMDDhhmm[.ss]` format.
    - `-d <str>`: Use a human-readable date string (e.g., `"2024-01-01"`).
  - **Parameters**:
    - `<filename>` *(required)*: File to create or update.
  - **Example Usage**: `touch notes.txt` / `touch -t 202401011200 file.txt`

---

- `cp [flags] <source> <destination>`
  - **Function**: Copies files or directories.
  - **Flags**:
    - `-r` / `-R`: Recursively copy directories.
    - `-v`: Verbose — show files being copied.
    - `-i`: Prompt before overwriting existing files.
    - `-n`: Do not overwrite existing files.
    - `-p`: Preserve file attributes (timestamps, permissions, ownership).
    - `-u`: Copy only when source is newer than destination.
  - **Parameters**:
    - `<source>` *(required)*: File or directory to copy.
    - `<destination>` *(required)*: Target path or directory.
  - **Example Usage**: `cp -rv ~/docs /backup/` / `cp -i file.txt file_backup.txt`

---

- `mv [flags] <source> <destination>`
  - **Function**: Moves or renames files and directories.
  - **Flags**:
    - `-v`: Verbose — print what is being moved.
    - `-i`: Prompt before overwriting.
    - `-n`: Do not overwrite existing destination.
    - `-u`: Move only when source is newer than destination.
  - **Parameters**:
    - `<source>` *(required)*: Source file or directory.
    - `<destination>` *(required)*: Target path or new name.
  - **Example Usage**: `mv old.txt new.txt` / `mv -v ~/Downloads/*.pdf ~/Documents/`

---

- `rm [flags] <file>`
  - **Function**: Removes files or directories.
  - **Flags**:
    - `-r` / `-R`: Recursively remove directories and their contents.
    - `-f`: Force removal — ignore nonexistent files, no prompts.
    - `-i`: Prompt before every removal.
    - `-v`: Verbose — show what is being removed.
  - **Parameters**:
    - `<file>` *(required)*: File(s) or directory to remove.
  - **Example Usage**: `rm file.txt` / `rm -rf ./temp_dir`

---

- `ln [flags] <target> <link_name>`
  - **Function**: Creates a link (hard or symbolic) to a file or directory.
  - **Flags**:
    - `-s`: Create a **symbolic** (soft) link instead of a hard link.
    - `-f`: Remove existing destination file before creating the link.
    - `-v`: Verbose output.
    - `-n`: Treat destination as a normal file if it is a symlink to a directory.
  - **Parameters**:
    - `<target>` *(required)*: The original file or directory to point to.
    - `<link_name>` *(required)*: Name of the new link.
  - **Example Usage**: `ln -s /usr/local/bin/python3 ~/bin/python` / `ln file.txt hardlink.txt`

---

## File Viewing & Editing

---

- `cat [flags] [file...]`
  - **Function**: Concatenates and displays the contents of one or more files.
  - **Flags**:
    - `-n`: Number all output lines.
    - `-b`: Number non-empty output lines only.
    - `-A`: Show all non-printing characters (equivalent to `-vET`).
    - `-s`: Suppress repeated empty lines (squeeze blanks).
    - `-v`: Show non-printing characters.
  - **Parameters**:
    - `[file...]` *(optional)*: File(s) to display; reads from stdin if omitted.
  - **Example Usage**: `cat file.txt` / `cat -n script.sh` / `cat f1.txt f2.txt > combined.txt`

---

- `nano [flags] [file]`
  - **Function**: Opens a file in the Nano terminal text editor.
  - **Flags**:
    - `-w`: Disable long-line wrapping.
    - `-l`: Show line numbers.
    - `-c`: Constantly show cursor position.
    - `-i`: Auto-indent new lines.
    - `-B`: Create a backup of the file before editing.
  - **Parameters**:
    - `[file]` *(optional)*: File to open; creates a new file if it does not exist.
  - **Example Usage**: `nano ~/.bashrc` / `nano -l config.yaml`

---

- `vim [flags] [file]`
  - **Function**: Opens a file in the Vim text editor.
  - **Flags**:
    - `-R`: Open in read-only mode.
    - `+<n>`: Start at line `n`.
    - `-u <vimrc>`: Use a specific vimrc configuration file.
    - `-d <file2>`: Open in diff mode comparing two files.
  - **Parameters**:
    - `[file]` *(optional)*: File to open.
  - **Example Usage**: `vim ~/.vimrc` / `vim +42 log.txt` / `vim -R /etc/passwd`

---

- `less [flags] [file]`
  - **Function**: Views file content one page at a time with backward and forward navigation.
  - **Flags**:
    - `-N`: Show line numbers.
    - `-S`: Chop long lines instead of wrapping.
    - `-i`: Case-insensitive search.
    - `-F`: Quit automatically if content fits on one screen.
    - `-R`: Display raw ANSI color codes.
  - **Parameters**:
    - `[file]` *(optional)*: File to view; reads from stdin if omitted.
  - **Example Usage**: `less /var/log/syslog` / `command | less -N`

---

- `more [flags] [file]`
  - **Function**: Views file content one screen at a time (forward navigation only).
  - **Flags**:
    - `-d`: Display a help prompt instead of ringing the bell on error.
    - `-f`: Count logical lines instead of screen lines.
    - `-n <num>`: Set screen size to `num` lines.
  - **Parameters**:
    - `[file]` *(optional)*: File to view.
  - **Example Usage**: `more /etc/hosts`

---

- `head [flags] [file]`
  - **Function**: Displays the first lines of a file (default: 10).
  - **Flags**:
    - `-n <num>`: Show the first `num` lines.
    - `-c <num>`: Show the first `num` bytes.
    - `-q`: Suppress file name headers when reading multiple files.
    - `-v`: Always print file name headers.
  - **Parameters**:
    - `[file]` *(optional)*: File to read; reads from stdin if omitted.
  - **Example Usage**: `head -n 20 access.log` / `head -c 100 binary.bin`

---

- `tail [flags] [file]`
  - **Function**: Displays the last lines of a file (default: 10).
  - **Flags**:
    - `-n <num>`: Show the last `num` lines. Prefix with `+` to start from line `num`.
    - `-c <num>`: Show the last `num` bytes.
    - `-f`: Follow — keep displaying new lines as they are written (ideal for logs).
    - `-F`: Like `-f` but retries if the file is rotated or renamed.
    - `-q`: Suppress file name headers.
  - **Parameters**:
    - `[file]` *(optional)*: File to read.
  - **Example Usage**: `tail -n 50 syslog` / `tail -f /var/log/nginx/error.log`

---

## Search & Comparison

---

- `grep [flags] <pattern> [file...]`
  - **Function**: Searches for lines matching a pattern in files or stdin.
  - **Flags**:
    - `-r` / `-R`: Recursively search directories.
    - `-i`: Case-insensitive matching.
    - `-n`: Show line numbers of matches.
    - `-v`: Invert match — show lines that do **not** match.
    - `-l`: Print only file names containing matches.
    - `-c`: Print only the count of matching lines per file.
    - `-E`: Use extended regular expressions (ERE).
    - `-A <n>`: Print `n` lines **after** each match.
    - `-B <n>`: Print `n` lines **before** each match.
    - `-C <n>`: Print `n` lines before and after each match.
    - `--color`: Highlight matches in color.
  - **Parameters**:
    - `<pattern>` *(required)*: The string or regex to search for.
    - `[file...]` *(optional)*: File(s) to search; reads from stdin if omitted.
  - **Example Usage**: `grep -rn "TODO" ./src` / `grep -i "error" /var/log/syslog` / `command | grep -v "debug"`

---

- `awk [flags] '<program>' [file...]`
  - **Function**: Pattern-scanning and text-processing language; processes files line by line.
  - **Flags**:
    - `-F <sep>`: Set the field separator (e.g., `-F ':'` for colon-delimited files).
    - `-v <var=val>`: Assign a variable before execution.
    - `-f <script>`: Read the awk program from a file.
  - **Parameters**:
    - `<program>` *(required)*: Awk program string, e.g., `'{print $1}'`.
    - `[file...]` *(optional)*: Input file(s); reads from stdin if omitted.
  - **Example Usage**: `awk -F ':' '{print $1}' /etc/passwd` / `awk '{sum += $1} END {print sum}' data.txt`

---

- `find <path> [flags]`
  - **Function**: Searches for files and directories matching given criteria in a directory hierarchy.
  - **Flags**:
    - `-name <pattern>`: Match by name (case-sensitive).
    - `-iname <pattern>`: Match by name (case-insensitive).
    - `-type <t>`: Filter by type: `f` (file), `d` (directory), `l` (symlink).
    - `-size <n>`: Match by size (e.g., `+10M` = larger than 10 MB).
    - `-mtime <n>`: Match by modification time in days (e.g., `-7` = last 7 days).
    - `-maxdepth <n>`: Limit search depth.
    - `-exec <cmd> {} \;`: Execute a command on each result.
    - `-delete`: Delete matching files.
  - **Parameters**:
    - `<path>` *(required)*: Directory to search in.
  - **Example Usage**: `find . -name "*.log" -mtime +30 -delete` / `find /home -type f -size +100M`

---

- `locate [flags] <pattern>`
  - **Function**: Quickly finds files by name using a pre-built database (run `updatedb` to refresh).
  - **Flags**:
    - `-i`: Case-insensitive search.
    - `-l <n>`: Limit output to `n` results.
    - `-r <regex>`: Use a regex pattern.
    - `-c`: Print only the count of matched entries.
  - **Parameters**:
    - `<pattern>` *(required)*: Filename or pattern to search for.
  - **Example Usage**: `locate -i "readme.md"` / `locate -l 5 nginx.conf`

---

- `cmp [flags] <file1> <file2>`
  - **Function**: Compares two files byte by byte; reports the first difference found.
  - **Flags**:
    - `-l`: Print all differing bytes (offset and values).
    - `-s`: Silent mode — exit status only (0 = identical, 1 = different).
    - `-b`: Display differing bytes as printable characters.
  - **Parameters**:
    - `<file1>` *(required)*: First file.
    - `<file2>` *(required)*: Second file.
  - **Example Usage**: `cmp image_old.bin image_new.bin` / `cmp -s f1 f2 && echo "identical"`

---

- `diff [flags] <file1> <file2>`
  - **Function**: Displays line-by-line differences between two files.
  - **Flags**:
    - `-u`: Unified format (standard for patches — shows context lines).
    - `-c`: Context format.
    - `-i`: Ignore case differences.
    - `-r`: Recursively compare directories.
    - `-q`: Only report whether files differ (brief mode).
    - `-y`: Side-by-side comparison.
    - `--color`: Colorize output.
  - **Parameters**:
    - `<file1>` *(required)*: Original file.
    - `<file2>` *(required)*: Modified file.
  - **Example Usage**: `diff -u original.py modified.py > patch.diff` / `diff -rq dir1/ dir2/`

---

- `sort [flags] [file]`
  - **Function**: Sorts the lines of a text file.
  - **Flags**:
    - `-r`: Reverse the sort order.
    - `-n`: Numeric sort (instead of lexicographic).
    - `-k <n>`: Sort by the `n`-th field.
    - `-u`: Remove duplicate lines after sorting.
    - `-t <sep>`: Set field separator (used with `-k`).
    - `-f`: Fold lowercase to uppercase (case-insensitive sort).
    - `-h`: Human-numeric sort (handles `1K`, `2M`, etc.).
  - **Parameters**:
    - `[file]` *(optional)*: File to sort; reads from stdin if omitted.
  - **Example Usage**: `sort -rn scores.txt` / `sort -t ':' -k3 -n /etc/passwd`

---

## Process & System Information

---

- `kill [flags] <PID>`
  - **Function**: Sends a signal to a process by its PID (default signal: `SIGTERM`).
  - **Flags**:
    - `-9` / `-SIGKILL`: Force kill — immediately terminates the process.
    - `-15` / `-SIGTERM`: Graceful termination request (default).
    - `-l`: List all available signal names.
    - `-s <signal>`: Specify signal by name.
  - **Parameters**:
    - `<PID>` *(required)*: Process ID of the target process.
  - **Example Usage**: `kill 1234` / `kill -9 5678` / `kill -l`

---

- `killall [flags] <processname>`
  - **Function**: Sends a signal to all processes matching the given name.
  - **Flags**:
    - `-9` / `-SIGKILL`: Force kill all matching processes.
    - `-i`: Interactive — ask before killing each process.
    - `-v`: Verbose — report which processes were killed.
    - `-q`: Quiet — suppress "no process found" errors.
  - **Parameters**:
    - `<processname>` *(required)*: Name of the process to kill.
  - **Example Usage**: `killall firefox` / `killall -9 chrome`

---

- `jobs [flags]`
  - **Function**: Lists all jobs (processes) running in the current shell session.
  - **Flags**:
    - `-l`: Show PID in addition to job info.
    - `-p`: Show PIDs only.
    - `-r`: List only running jobs.
    - `-s`: List only stopped jobs.
  - **Example Usage**: `jobs -l`

---

- `bg [job_id]`
  - **Function**: Resumes a suspended job in the background.
  - **Parameters**:
    - `[job_id]` *(optional)*: Job number from `jobs`; defaults to the most recently suspended job.
  - **Example Usage**: `bg %1` / `bg`

---

- `fg [job_id]`
  - **Function**: Brings a background or suspended job to the foreground.
  - **Parameters**:
    - `[job_id]` *(optional)*: Job number from `jobs`; defaults to the most recent job.
  - **Example Usage**: `fg %2` / `fg`

---

- `history [flags] [n]`
  - **Function**: Displays or manages the command history of the current shell.
  - **Flags**:
    - `-c`: Clear the history list.
    - `-d <n>`: Delete the history entry at position `n`.
    - `-a`: Append new history lines to the history file.
    - `-w`: Write the current history list to the history file.
  - **Parameters**:
    - `[n]` *(optional)*: Show the last `n` history entries.
  - **Example Usage**: `history 20` / `history -c` / `!42` *(re-run command #42)*

---

- `uptime [flags]`
  - **Function**: Shows how long the system has been running, along with load averages.
  - **Flags**:
    - `-p`: Show uptime in a human-readable format (e.g., `up 2 hours, 5 minutes`).
    - `-s`: Show the date and time the system was last booted.
  - **Example Usage**: `uptime` / `uptime -p`

---

- `ps [flags]`
  - **Function**: Displays information about currently running processes.
  - **Flags**:
    - `aux`: Show all processes for all users with detailed info (most common combination).
    - `-e` / `-A`: Show all processes.
    - `-f`: Full-format listing (shows PPID and command arguments).
    - `-u <user>`: Show processes for a specific user.
    - `--sort=<key>`: Sort by a field (e.g., `--sort=-%cpu`).
  - **Example Usage**: `ps aux` / `ps aux | grep nginx` / `ps -u john`

---

## Miscellaneous

---

- `echo [flags] <text>`
  - **Function**: Prints text or variable values to the terminal.
  - **Flags**:
    - `-n`: Do not output a trailing newline.
    - `-e`: Enable interpretation of backslash escapes (e.g., `\n`, `\t`).
    - `-E`: Disable escape interpretation (default).
  - **Parameters**:
    - `<text>` *(required)*: Text or variable to print.
  - **Example Usage**: `echo "Hello, World!"` / `echo -e "Line1\nLine2"` / `echo $HOME`

---

- `tee [flags] [file...]`
  - **Function**: Reads from stdin and writes to both stdout and one or more files simultaneously.
  - **Flags**:
    - `-a`: Append to files instead of overwriting.
    - `-i`: Ignore interrupt signals.
  - **Parameters**:
    - `[file...]` *(optional)*: File(s) to write output to.
  - **Example Usage**: `ls -la | tee listing.txt` / `command | tee -a log.txt`

---

- `date [flags] [+format]`
  - **Function**: Displays or sets the system date and time.
  - **Flags**:
    - `-u`: Display time in UTC.
    - `-d <str>`: Display the time described by `str` (e.g., `"yesterday"`, `"next Friday"`).
    - `-s <str>`: Set the system date/time (requires root).
    - `-R`: Output date in RFC 2822 format.
  - **Parameters**:
    - `[+format]` *(optional)*: Custom output format (e.g., `+"%Y-%m-%d %H:%M:%S"`).
  - **Example Usage**: `date` / `date +"%Y-%m-%d"` / `date -d "tomorrow"`

---

- `alias [name='command']`
  - **Function**: Creates a shortcut (alias) for a command. Run `alias` alone to list all current aliases.
  - **Parameters**:
    - `[name='command']` *(optional)*: Alias name and the command it maps to. Omit to list all aliases.
  - **Example Usage**: `alias ll='ls -lah'` / `alias gs='git status'` / `alias`

---

- `unalias [flags] <name>`
  - **Function**: Removes one or more aliases.
  - **Flags**:
    - `-a`: Remove all defined aliases.
  - **Parameters**:
    - `<name>` *(required unless -a)*: Name of the alias to remove.
  - **Example Usage**: `unalias ll` / `unalias -a`

---

- `gio open <file>`
  - **Function**: Opens a file or URI using the appropriate default GNOME application.
  - **Parameters**:
    - `<file>` *(required)*: File path or URI to open.
  - **Example Usage**: `gio open document.pdf` / `gio open https://example.com`

---

- `xdg-open <file>`
  - **Function**: Opens a file or URL with the user's preferred application (desktop-environment agnostic).
  - **Parameters**:
    - `<file>` *(required)*: File path or URL to open.
  - **Example Usage**: `xdg-open ~/Pictures/photo.png` / `xdg-open https://example.com`

---

## Modern & Advanced Tools

---

- `ncdu [flags] [directory]`
  - **Function**: Interactive disk usage analyzer with a navigable ncurses interface.
  - **Flags**:
    - `-x`: Do not cross filesystem boundaries.
    - `-e`: Enable extended information (permissions, uid).
    - `-q`: Quiet mode (reduced UI refresh rate).
    - `--color <scheme>`: Set color scheme (`off` or `dark`).
  - **Parameters**:
    - `[directory]` *(optional)*: Directory to scan; defaults to current directory.
  - **Example Usage**: `ncdu /` / `ncdu -x /home`

---

- `duff [flags] [files/directories...]`
  - **Function**: Finds duplicate files in specified directories.
  - **Flags**:
    - `-r`: Recursively search directories.
    - `-e <level>`: Thoroughness level (`0`=size only, `1`=inode, `2`=content).
    - `-z`: Include zero-size files.
  - **Parameters**:
    - `[files/directories...]` *(required)*: Paths to check for duplicates.
  - **Example Usage**: `duff -r ~/Downloads`

---

- `rg [flags] <pattern> [path]`
  - **Function**: Recursively searches for a pattern in files (ripgrep — like `grep` but faster, respects `.gitignore`).
  - **Flags**:
    - `-i`: Case-insensitive search.
    - `-n`: Show line numbers (on by default).
    - `-l`: Print only file names with matches.
    - `-C <n>`: Show `n` context lines around each match.
    - `-t <type>`: Limit search to a file type (e.g., `py`, `js`).
    - `-g <glob>`: Include/exclude files matching a glob pattern.
    - `--no-ignore`: Don't respect `.gitignore` and similar files.
  - **Parameters**:
    - `<pattern>` *(required)*: String or regex to search for.
    - `[path]` *(optional)*: Directory or file to search; defaults to current directory.
  - **Example Usage**: `rg "TODO" ./src` / `rg -i "error" -t py` / `rg -l "import os"`

---

- `mosh [flags] [user@]<host>`
  - **Function**: Connects to a remote machine like SSH but with better support for roaming and unstable connections (uses UDP).
  - **Flags**:
    - `--port <n>`: UDP port to use.
    - `--ssh <cmd>`: SSH command to use for the initial connection.
    - `-p <range>`: UDP port range to use.
  - **Parameters**:
    - `[user@]` *(optional)*: Remote username.
    - `<host>` *(required)*: Remote hostname or IP address.
  - **Example Usage**: `mosh user@192.168.1.10` / `mosh --port 60001 user@server.com`

---

- `lshw [flags]`
  - **Function**: Lists detailed hardware configuration (CPU, RAM, storage, NIC, etc.).
  - **Flags**:
    - `-short`: Summary view of hardware classes.
    - `-html`: Output in HTML format.
    - `-json`: Output in JSON format.
    - `-class <name>`: Filter by hardware class (e.g., `cpu`, `memory`, `disk`).
    - `-businfo`: Show bus info for all devices.
  - **Example Usage**: `sudo lshw -short` / `sudo lshw -class disk`

---

- `mtr [flags] <host>`
  - **Function**: Combines `traceroute` and `ping` into a real-time network diagnostic tool.
  - **Flags**:
    - `-r`: Report mode (non-interactive, prints summary).
    - `-c <n>`: Number of pings to send.
    - `-n`: Disable DNS resolution (show IPs only).
    - `--tcp`: Use TCP instead of ICMP.
    - `--udp`: Use UDP probes.
  - **Parameters**:
    - `<host>` *(required)*: Hostname or IP to trace.
  - **Example Usage**: `mtr google.com` / `mtr -r -c 10 8.8.8.8`

---

- `fd [flags] [pattern] [path]`
  - **Function**: Simple, fast, and user-friendly alternative to `find`. Respects `.gitignore` by default.
  - **Flags**:
    - `-e <ext>`: Filter by file extension.
    - `-t <type>`: Filter by type: `f` (file), `d` (directory), `l` (symlink).
    - `-H`: Include hidden files in results.
    - `-I`: Do not respect `.gitignore`.
    - `-x <cmd>`: Execute a command on each result.
    - `--max-depth <n>`: Limit search depth.
  - **Parameters**:
    - `[pattern]` *(optional)*: Name pattern (regex or simple string).
    - `[path]` *(optional)*: Search root; defaults to current directory.
  - **Example Usage**: `fd ".log" /var` / `fd -e py -t f` / `fd -H "^\." ~`

---

- `fzf [flags]`
  - **Function**: Interactive fuzzy finder for any list of items (files, history, processes, etc.).
  - **Flags**:
    - `--preview <cmd>`: Show a preview window while selecting.
    - `-m`: Allow multi-select with Tab.
    - `--height <n>%`: Set height of the fzf window.
    - `--reverse`: Display list from top to bottom.
    - `-q <query>`: Start with an initial query string.
  - **Example Usage**: `fzf` / `find . | fzf --preview 'cat {}'` / `history | fzf`

---

- `ranger [directory]`
  - **Function**: Terminal-based file manager with Vim-style keybindings and file preview.
  - **Flags**:
    - `--choosefile=<f>`: Write the chosen file to file `f` on exit.
    - `--copy-config=<all|rc|...>`: Copy default config to `~/.config/ranger`.
  - **Parameters**:
    - `[directory]` *(optional)*: Directory to open; defaults to current directory.
  - **Example Usage**: `ranger` / `ranger ~/Downloads`

---

- `z [directory_substring]`
  - **Function**: Smarter `cd` — jumps to frequently visited directories using frecency-based fuzzy matching (zoxide / z.lua / autojump).
  - **Parameters**:
    - `[directory_substring]` *(required)*: Partial name or path of the target directory.
  - **Example Usage**: `z projects` / `z dow` *(jumps to `~/Downloads` if visited frequently)*

---

- `exa [flags] [path]`
  - **Function**: Modern replacement for `ls` with colors, icons, Git integration, and tree view.
  - **Flags**:
    - `-l`: Long format.
    - `-a`: Show hidden files.
    - `-T`: Tree view of the directory.
    - `--git`: Show Git status of files.
    - `-h` / `--header`: Add a header row.
    - `--icons`: Display file-type icons (requires a Nerd Font).
    - `-s <field>`: Sort by field (`name`, `size`, `modified`, etc.).
  - **Parameters**:
    - `[path]` *(optional)*: Directory to list; defaults to current directory.
  - **Example Usage**: `exa -lah --git` / `exa -T --level=2`

---

- `glances [flags]`
  - **Function**: Cross-platform, real-time system monitoring dashboard (CPU, RAM, disk, network, processes).
  - **Flags**:
    - `-w`: Run as a web server (accessible via browser).
    - `-c <host>`: Connect to a remote glances server.
    - `--export <exporter>`: Export stats (e.g., `csv`, `json`).
    - `-t <n>`: Refresh interval in seconds.
  - **Example Usage**: `glances` / `glances -w` / `glances -t 2`

---

- `iotop [flags]`
  - **Function**: Displays real-time I/O usage by processes (requires root).
  - **Flags**:
    - `-o`: Show only processes currently doing I/O.
    - `-a`: Accumulated I/O (total since start, not per-second rate).
    - `-d <n>`: Refresh interval in seconds.
    - `-p <PID>`: Monitor a specific PID.
    - `-u <user>`: Monitor processes of a specific user.
  - **Example Usage**: `sudo iotop -o` / `sudo iotop -a -d 2`

---

- `stat [flags] <file>`
  - **Function**: Displays detailed metadata about a file or directory (size, permissions, timestamps, inode).
  - **Flags**:
    - `-f`: Display filesystem status instead of file status.
    - `-L`: Follow symbolic links.
    - `-c <format>`: Use a custom output format string.
  - **Parameters**:
    - `<file>` *(required)*: File or directory to inspect.
  - **Example Usage**: `stat ~/.bashrc` / `stat -c "%n %s %y" file.txt`

---

- `dstat [flags]`
  - **Function**: Versatile, real-time resource statistics tool (combines vmstat, iostat, netstat, etc.).
  - **Flags**:
    - `-c`: CPU stats.
    - `-d`: Disk I/O stats.
    - `-n`: Network stats.
    - `-m`: Memory stats.
    - `-t`: Add a timestamp column.
    - `--output <file>`: Save stats to a CSV file.
  - **Example Usage**: `dstat -cdnm -t` / `dstat --output stats.csv`

---

- `watch [flags] <command>`
  - **Function**: Repeatedly runs a command at regular intervals and displays its output full-screen.
  - **Flags**:
    - `-n <sec>`: Interval in seconds (default: 2).
    - `-d`: Highlight differences between updates.
    - `-t`: Hide the header (title bar).
    - `-e`: Exit on command error.
  - **Parameters**:
    - `<command>` *(required)*: Command to execute repeatedly.
  - **Example Usage**: `watch -n 1 df -h` / `watch -d -n 2 "ls -lt /var/log"`

---

- `progress [flags]`
  - **Function**: Shows progress (throughput, ETA) of running coreutils commands like `cp`, `mv`, `dd`, `tar`.
  - **Flags**:
    - `-w`: Wait for a monitored process to appear if none is currently running.
    - `-m`: Monitor all instances of watched commands.
    - `-W`: Keep watching until all monitored processes finish.
  - **Example Usage**: `progress` / `progress -m` *(run in another terminal while `cp`/`mv` is active)*

---

- `dig [flags] [type] <domain>`
  - **Function**: DNS lookup tool — queries name servers for DNS records.
  - **Flags**:
    - `+short`: Print a terse answer.
    - `+noall +answer`: Show only the answer section.
    - `-x <ip>`: Reverse DNS lookup (IP to hostname).
    - `@<server>`: Query a specific DNS server.
  - **Parameters**:
    - `[type]` *(optional)*: Record type: `A`, `AAAA`, `MX`, `TXT`, `NS`, `CNAME` (default: `A`).
    - `<domain>` *(required)*: Domain to query.
  - **Example Usage**: `dig google.com` / `dig MX gmail.com` / `dig +short @8.8.8.8 example.com`

---

- `dog [flags] [type] <domain>`
  - **Function**: User-friendly DNS client with colorized output — a modern alternative to `dig`.
  - **Flags**:
    - `--short`: Show only record values.
    - `--json`: Output JSON.
    - `--tcp` / `--tls`: Use TCP or DNS-over-TLS.
    - `@<server>`: Query a specific DNS server.
  - **Parameters**:
    - `[type]` *(optional)*: Record type: `A`, `AAAA`, `MX`, `TXT`, etc.
    - `<domain>` *(required)*: Domain to query.
  - **Example Usage**: `dog example.com` / `dog MX gmail.com @8.8.8.8`

---

- `tcpdump [flags] [expression]`
  - **Function**: Captures and analyzes network packets in real time (requires root).
  - **Flags**:
    - `-i <iface>`: Specify network interface (e.g., `eth0`, `any`).
    - `-n`: Do not resolve hostnames.
    - `-v` / `-vv` / `-vvv`: Increasing verbosity.
    - `-w <file>`: Write raw packets to a `.pcap` file.
    - `-r <file>`: Read packets from a `.pcap` file.
    - `-c <n>`: Capture only `n` packets then stop.
  - **Parameters**:
    - `[expression]` *(optional)*: BPF filter expression (e.g., `port 80`, `host 192.168.1.1`).
  - **Example Usage**: `sudo tcpdump -i eth0 port 80` / `sudo tcpdump -w capture.pcap -c 100`

---

- `tshark [flags]`
  - **Function**: Terminal-based network protocol analyzer (Wireshark CLI).
  - **Flags**:
    - `-i <iface>`: Capture on specified interface.
    - `-r <file>`: Read a `.pcap` capture file.
    - `-w <file>`: Write captured packets to file.
    - `-Y <filter>`: Apply a Wireshark display filter (e.g., `http`, `tcp.port==443`).
    - `-T <format>`: Output format (`fields`, `json`, `text`, etc.).
  - **Example Usage**: `sudo tshark -i eth0 -Y "http"` / `tshark -r capture.pcap -T json`

---

- `termshark [flags]`
  - **Function**: Terminal UI for tshark — interactive packet capture viewer in the terminal.
  - **Flags**:
    - `-i <iface>`: Interface to capture on.
    - `-r <file>`: Open a `.pcap` file for inspection.
  - **Example Usage**: `sudo termshark -i eth0` / `termshark -r capture.pcap`

---

- `lsof [flags]`
  - **Function**: Lists open files and the processes that have them open (regular files, sockets, pipes).
  - **Flags**:
    - `-i [addr]`: Show network connections (optionally filter by port/protocol, e.g., `:8080`).
    - `-p <PID>`: Show files opened by a specific PID.
    - `-u <user>`: Show files opened by a specific user.
    - `+D <dir>`: Show all open files under a directory.
    - `-t`: Output PIDs only (useful for scripting).
  - **Example Usage**: `sudo lsof -i :8080` / `lsof -u john` / `lsof +D /var/log`

---

- `ipcalc <IP/netmask>`
  - **Function**: Calculates network information from an IP address and subnet mask (range, broadcast, prefix).
  - **Parameters**:
    - `<IP/netmask>` *(required)*: IP address with prefix or netmask (e.g., `192.168.1.0/24`).
  - **Example Usage**: `ipcalc 192.168.1.0/24` / `ipcalc 10.0.0.1/255.255.0.0`

---

- `wormhole send <file>`
  - **Function**: Securely transfers a file to another machine using a one-time human-readable code (Magic Wormhole protocol).
  - **Parameters**:
    - `<file>` *(required)*: File or directory to send.
  - **Example Usage**: `wormhole send archive.tar.gz` *(receiver runs `wormhole receive`)*

---

- `systemd-analyze [subcommand]`
  - **Function**: Analyzes systemd unit load times and boot performance.
  - **Parameters** (subcommands):
    - `blame`: List units sorted by initialization time.
    - `critical-chain`: Show the chain of units that delayed boot most.
    - `plot`: Output an SVG boot chart.
    - `time`: Show overall boot time split (firmware, loader, kernel, userspace).
  - **Example Usage**: `systemd-analyze blame` / `systemd-analyze critical-chain` / `systemd-analyze time`

---

- `procs [flags]`
  - **Function**: Modern, interactive replacement for `ps` with syntax highlighting and tree view.
  - **Flags**:
    - `--tree`: Show processes in a tree.
    - `--watch <n>`: Auto-refresh every `n` seconds.
    - `<keyword>`: Filter processes by name or PID (positional argument).
  - **Example Usage**: `procs` / `procs nginx` / `procs --tree`

---

- `lazydocker`
  - **Function**: Terminal UI for managing Docker containers, images, volumes, and networks interactively.
  - **Example Usage**: `lazydocker`

---

- `rsync [flags] <source> <destination>`
  - **Function**: Efficiently transfers and synchronizes files locally or over SSH, sending only changed data.
  - **Flags**:
    - `-a`: Archive mode — preserves permissions, timestamps, symlinks, owner, and group.
    - `-v`: Verbose output.
    - `-z`: Compress data during transfer.
    - `-P`: Show progress and keep partial files (`--partial --progress`).
    - `-n` / `--dry-run`: Simulate without making any changes.
    - `-e <cmd>`: Specify remote shell (e.g., `-e ssh`).
    - `--exclude <pattern>`: Exclude files matching a pattern.
    - `--delete`: Delete files in destination not present in source.
  - **Parameters**:
    - `<source>` *(required)*: Source directory or file.
    - `<destination>` *(required)*: Local path or `user@host:/path`.
  - **Example Usage**: `rsync -avzP ~/docs/ user@server:/backup/docs/` / `rsync -an --delete src/ dst/`

---

- `shred [flags] <file>`
  - **Function**: Overwrites a file multiple times to make data recovery much harder before deletion.
  - **Flags**:
    - `-n <n>`: Number of overwrite passes (default: 3).
    - `-v`: Verbose — show progress.
    - `-u`: Truncate and remove the file after shredding.
    - `-z`: Add a final overwrite with zeros to hide shredding.
  - **Parameters**:
    - `<file>` *(required)*: File to securely overwrite.
  - **Example Usage**: `shred -vuz -n 5 secret.txt`

---

- `jq [flags] <filter> [file]`
  - **Function**: Command-line JSON processor — parses, filters, transforms, and formats JSON data.
  - **Flags**:
    - `-r`: Raw output (don't quote strings).
    - `-c`: Compact output (single line per result).
    - `-e`: Set exit status based on output (false/null → exit 1).
    - `-s`: Slurp all inputs into a single array.
    - `-f <file>`: Read filter from a file.
  - **Parameters**:
    - `<filter>` *(required)*: jq filter expression (e.g., `.name`, `.items[]`, `.[] | select(.active)`).
    - `[file]` *(optional)*: JSON file to process; reads from stdin if omitted.
  - **Example Usage**: `cat data.json | jq '.users[].name'` / `curl -s api/endpoint | jq -r '.status'`

---

- `task [subcommand]`
  - **Function**: Command-line task and todo manager (Taskwarrior).
  - **Parameters** (subcommands):
    - `add <description>`: Add a new task.
    - `list` / `ls`: List pending tasks.
    - `done <id>`: Mark a task as complete.
    - `delete <id>`: Delete a task.
    - `modify <id>`: Modify a task's attributes.
  - **Example Usage**: `task add "Write project report" due:tomorrow` / `task list` / `task 3 done`

---

- `asciinema [subcommand]`
  - **Function**: Records and shares terminal sessions as lightweight text-based animations.
  - **Parameters** (subcommands):
    - `rec [file]`: Record a terminal session.
    - `play <file>`: Play back a recorded session.
    - `upload <file>`: Upload a recording to asciinema.org.
    - `auth`: Link local install to an asciinema.org account.
  - **Example Usage**: `asciinema rec demo.cast` / `asciinema play demo.cast`

---

- `ollama [subcommand] [model]`
  - **Function**: Runs large language models locally via a CLI interface.
  - **Parameters** (subcommands):
    - `run <model>`: Start an interactive chat with a model (downloads if not present).
    - `pull <model>`: Download a model.
    - `list`: List locally available models.
    - `rm <model>`: Remove a local model.
    - `serve`: Start the Ollama API server.
  - **Example Usage**: `ollama run llama3` / `ollama list` / `ollama pull mistral`
