# Linux Theory


## Philosophy 

The Unix-philosophy makes a heavy  emphasis on modularity for all of the individual components in an operating system. 
Those modules shoudl be independent yet able to work together. Another aspect, code should be keept simple and efficient.

--- 

## Startup Sequence 

1. Power on 
2. UEFI Firmware 
3. Power-On Self Test 
4. Bootloader 
5. Load kernel image. 
6. Initialize Kernel and root file-system. 
7. Initramfs (optional).
8. Load Device Drivers. 
9. Init system runs. 
10. Start services. 
11. Display manager starts.
12. User authentication. 
13. Start User Enviroment.
14. Start Display server.
15. Start desktop environment if available.

--- 

## Portable Operating System Interface (POSIX)

**POSIX** is a family of standards derived fomr the UNIX operating system designed to ensure compatibility across 
different versions of UNIS and its derivatives by setting rules for file reading and writing, command names, etc. 


--- 

## Init System

---

## Processes

**Processes** in Linux can be viewed using the commands `top`, `htop`, `btop` or any other variant. It will display a list like: 

```txt
top - 10:46:02 up 7 days, 22:32,  1 user,  load average: 4.20, 4.44, 2.85
Tasks: 368 total, 1 running, 366 sleep, 1 d-sleep, 0 stopped, 0 zombie
%Cpu(s): 17.5 us,  1.4 sy,  0.0 ni, 80.3 id,  0.2 wa,  0.5 hi,  0.2 si,  0.0 st 
MiB Mem :  31845.6 total,  14486.8 free,   6768.6 used,  11891.0 buff/cache     
MiB Swap:   8192.0 total,   8191.1 free,      0.9 used.  25077.0 avail Mem 

    PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND                
   3604 miguel    20   0   53.9g 784492 569128 S   2.7   2.4  51:11.70 brave                  
   2480 miguel    -2   0  817236  89584  64292 S   1.7   0.3  27:52.50 sway                   
 245931 miguel    20   0 1450.1g 102516  77424 S   1.7   0.3   0:00.05 brave                  
    445 root      20   0       0      0      0 S   1.0   0.0   3:05.98 btrfs-transaction      
   2713 miguel    20   0  412800  20864   8560 S   0.7   0.1   5:48.63 pipewire-pulse         
   4240 miguel    20   0   52.8g 105908  87664 S   0.7   0.3   6:35.74 brave                  
 238903 miguel    20   0  635348 112388  29244 S   0.7   0.3   1:36.33 nvim                   
 241651 miguel    20   0  605848  82232  14440 S   0.7   0.3   0:23.19 nvim                   
 244516 miguel    20   0 1448.2g 299416 146760 S   0.7   0.9   0:13.93 brave                  
     16 root      20   0       0      0      0 I   0.3   0.0   0:29.92 rcu_preempt            
   1083 root      20   0  776708  52776  51188 S   0.3   0.2   0:41.17 rsyslogd               
   2620 miguel    20   0  340960  16648   9104 S   0.3   0.1   3:49.15 pipewire               
   3665 miguel    20   0   52.7g  72552  49900 S   0.3   0.2   2:07.51 brave                  
 224779 miguel    20   0 2342992  65280  48304 S   0.3   0.2   0:16.67 waybar               
```



This list will give information about the process like: **id (PID)**, **memory usage**, **user**, etc.

We can end a process using the `kill` command plus the specified **id**.

--- 

## Enviroment variables 

Like in other operating systems, an enviroment is a varible which affects 
the way processes run for the specific enviroment.

Common use cases: 

- In Linux the variables can be printed using the the command `env`. 

- To see the value we can use the command `printvar`. Finally to modify we can use the command `export NAME=value`

- We can create enviroment variables for the current section by typing  `NAME=VALUE` in the shell.

- To create persistent enviroment variables we have to modify the `.bashrc` by adding 
`export NAME=value` and then source the file with the `source FILE` command. 

- To set a global env. variable we have to modify the file `vim /etc/environment` using the 
export syntax and then sourcing.

- To delete an environment variables we can use the command `unset NAME`

### PATH

The `PATH` variable is an environment variable containing an ordered list of paths that Linux will search for executables when running a command/binary. 
Using these paths means that we don’t have to specify an absolute path when running a binary.

   - To modify the path both locally we have to create an `.profile` file using the export 
      syntax and for the global approach it is very similar but we create the the file in `/etc/profile.d/varname.sh`.

   - For a non-persistent modification we can use `PATH=$PATH:/path/to/program` + `export PATH`.

   - We can also modify it in the `.bashrc` by putting in our `PATH=$PATH:/path/to/program`.
---

## File Descriptor

A **file descriptor (FD)** is a low-level integer handle used by an operating system to uniquely identify an open file or input/output (I/O) resource. File descriptors are central to how operating systems like Unix, Linux, and macOS manage I/O operations, including files, pipes, and sockets.

### Key Characteristics:

* **Integer Identifier**: File descriptors are represented by non-negative integers (e.g., `0`, `1`, `2`).
* **Resource Handle**: Each FD refers to an open I/O resource, such as a file, socket, or device.
* **Process-specific**: FDs are unique within a process and are maintained by the process’s file descriptor table.

### Standard File Descriptors:

By default, every process starts with three open file descriptors:

| FD | Name     | Description     |
| -- | -------- | --------------- |
| 0  | `stdin`  | Standard input  |
| 1  | `stdout` | Standard output |
| 2  | `stderr` | Standard error  |

--- 

## Types of File Systems in Linux and Their Differences

- **ext2 (Second Extended Filesystem)**
  - No journaling
  - Good for flash drives

- **ext3 (Third Extended Filesystem)**
  - Journaling enabled (improved reliability)
  - Backward compatible with ext2

- **ext4 (Fourth Extended Filesystem)**
  - Most widely used
  - Supports large files and volumes
  - Journaling + extents for better performance

- **XFS**
  - High-performance journaling file system
  - Good for large files and parallel I/O

- **Btrfs (B-tree File System)**
  - Copy-on-write, snapshots, self-healing
  - Advanced features, but still maturing

- **FAT32 / exFAT**
  - File Allocation Table
  - Compatibility with Windows systems
  - No journaling
  - Optimized for high-capacity USB flash drives

- **NTFS (New Technology File System)**
  - Proprietary Microsoft file system
  - Supported via drivers (read/write)
  - Supports Journaling, file permissions and encryption.

---

## What is an Inode and How It Is Used

- An **inode** (index node) is a data structure on a filesystem that stores metadata about a file:

  - File type
  - Permissions
  - Owner/group
  - Size
  - Timestamps
  - Pointers to data blocks

- Every file has an inode (except for symbolic links in some filesystems).

- The inode number is used by the OS to identify files, not the filename.

---

## The Unix Philosophy

- **Do one thing and do it well**
- **Work together**: Tools should interact with each other through standard interfaces (e.g., stdin/stdout).
- **Handle text streams**: Treat everything as a stream of text.

This philosophy promotes simplicity, modularity, and composability.

---

## What is a File?

- A file is an abstract collection of data stored on disk.
- In Unix/Linux, **everything is a file**:

  * Regular files
  * Directories
  * Devices (`/dev`)
  * Pipes
  * Sockets
  * Symbolic links

---

## How Unix Uses Files

- **File Descriptors**: Integer handles for files (`0=stdin`, `1=stdout`, `2=stderr`)
- **Permissions and Ownership**:

  * Read (r), Write (w), Execute (x)
  * User, Group, Others
- **Processes interact with files through system calls**: `open()`, `read()`, `write()`, `close()`
- Devices and IPC mechanisms are accessed like files
- **Symlinks**: Short for symbolic link is a special type of file that points to another file or directory. It is 
like a pointer. They are useful to for example manage all dotfiles from one place

---

## Important Directories and Their Functions


| Directory | Function                                           |
|:--------- |:-------------------------------------------------- |
| `/`       | Root directory                                     |
| `/bin`    | Essential user binaries (e.g., ls, cp)             |
| `/sbin`   | System binaries (e.g., fsck, reboot)               |
| `/boot`   | Containg everything related to booting the system  |
| `/etc`    | Configuration files for system wide applications   |
| `/dev`    | Device files                                       |
| `/proc`   | Process and kernel info (virtual filesystem)       |
| `/sys`    | Kernel and hardware interface (virtual filesystem) |
| `/tmp`    | Temporary files for applications                                   |
| `/var`    | Variable data (logs, spool files)                  |
| `/usr`    | (Unix System Resources) Secondary hierarchy for user-space programs and data     |
| `/home`   | User home directories                              |
| `/lib`    | Essential shared libraries for dynamic linking, etc. Also kernel modules can be found                       |
| `/opt`    | Optional/add-on software pckgs. Can add your own   |
| `/mnt`    | Mount point for temporary mounts                   |
| `/media`  | Mount point for removable media                    |
| `/root`   | For the root user                                  |
| `/run`    | Temp filesystem for temporal runtime information   |
| `/srv`    | If the computer is a service(server) the files for users will be stored here                    |
| `/sys`    | Acts as a dynamic interface between the kernel and the hardware  |

---

## Disk Partitions

- **Partition**: A division of a storage device that acts as a separate logical unit

- **Types**:

  * Primary (up to 4)
  * Extended (contains logical partitions)
  * Logical (within extended)

- **Tools**:

  * `fdisk` / `parted`: Manage partitions
  * `lsblk`, `blkid`: View block devices
  * `mount` / `umount`: Attach/detach partitions

- **Partition table types**:

  * **MBR (Master Boot Record)**
  * **GPT (GUID Partition Table)** - newer, supports more partitions

---

## systemctl

`systemctl` is the primary tool used to examine and control the `systemd` system and service manager on Linux systems. 

Essential commands:

- **Start a service**  `sudo systemctl start <service-name>`

- **Stop a service** `sudo systemctl stop <service-name>`

- **Restart a service** `sudo systemctl restart <service-name>`

- **Enable a service** `sudo systemctl enable <service-name>`

- **Disable a service** `sudo systemctl disable <service-name>`

- **Check status of a service** `systemctl status <service-name>`

- **List all active services** `systemctl list-units --type=service`

---

## Desktop Environments

A desktop environment is a collection of applications and libraries that provide a graphical user interface (GUI) for interacting with the operating system.

Common desktop environments for Linux include:

- **GNOME**: Modern, user-friendly, and widely used (e.g., Ubuntu)
- **KDE Plasma**: Highly customizable and feature-rich (e.g., Kubuntu)
- **XFCE**: Lightweight and fast, ideal for older hardware (e.g., Xubuntu)
- **LXDE/LXQt**: Extremely lightweight, minimal resource usage (e.g., Lubuntu)
- **Cinnamon**: Traditional desktop experience with modern features (e.g., Linux Mint)
- **MATE**: Fork of GNOME 2, classic desktop experience (e.g., Ubuntu MATE)

--- 

## Window Managers & Compositors

A window manager is a system software that controls the placement and appearance of windows within a graphical user interface (GUI). It 
is responsible for managing the layout, behavior, and interactions of application windows on the screen.

A compositor is a system software that provides advanced graphical effects, such as transparency, shadows, and animations, by combining multiple window 
buffers into a single image before displaying it on the screen. Some window managers include built-in compositors, while others rely on external compositors.

