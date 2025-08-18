
# Linux Theory

---

## Enviroment variables 

Like in other operating systems, an enviroment variable is user defined varible which affects 
the way processes run for the specific enviroment.

In Linux the variables can be printed using the the command `env`. To see the value we can use the 
command `printvar`. Finally to modify we can use the command `export NAME=value`

To create persistent enviroment variables we have to modify the `.bashrc` by adding 
`export NAME=value` and then source the file with the `source FILE` command. 

To set a global env. variable we have to modify the file `vim /etc/environment` using the 
export syntax and then sourcing.

To delete an environment variables we can use the command `unset NAME`

The PATH variable is an environment variable containing an ordered list of paths that Linux will search for executables when running a command. Using these paths means that we don’t have to specify an absolute path when running a command.

To modify the path both locally we have to create an `.profile` file using the export 
syntax and for the global approach it is very similar but we create the the file in `/etc/profile.d/varname.sh`

---

## Types of File Systems in Linux and Their Differences

* **ext2 (Second Extended Filesystem)**

  * No journaling
  * Good for flash drives

* **ext3 (Third Extended Filesystem)**

  * Journaling enabled (improved reliability)
  * Backward compatible with ext2

* **ext4 (Fourth Extended Filesystem)**

  * Most widely used
  * Supports large files and volumes
  * Journaling + extents for better performance

* **XFS**

  * High-performance journaling file system
  * Good for large files and parallel I/O

* **Btrfs (B-tree File System)**

  * Copy-on-write, snapshots, self-healing
  * Advanced features, but still maturing

* **FAT32 / exFAT**

  * File Allocation Table
  * Compatibility with Windows systems
  * No journaling

* **NTFS**

  * New Technology File System
  * Proprietary Microsoft file system
  * Supported via drivers (read/write)

---


## What is an Inode and How It Is Used

* An **inode** (index node) is a data structure on a filesystem that stores metadata about a file:

  * File type
  * Permissions
  * Owner/group
  * Size
  * Timestamps
  * Pointers to data blocks

* Every file has an inode (except for symbolic links in some filesystems).

* The inode number is used by the OS to identify files, not the filename.

---

## The Unix Philosophy

* **Do one thing and do it well**
* **Work together**: Tools should interact with each other through standard interfaces (e.g., stdin/stdout).
* **Handle text streams**: Treat everything as a stream of text.

This philosophy promotes simplicity, modularity, and composability.

---

## What is a File?

* A file is an abstract collection of data stored on disk.
* In Unix/Linux, **everything is a file**:

  * Regular files
  * Directories
  * Devices (`/dev`)
  * Pipes
  * Sockets
  * Symbolic links

---

## How Unix Uses Files

* **File Descriptors**: Integer handles for files (`0=stdin`, `1=stdout`, `2=stderr`)
* **Permissions and Ownership**:

  * Read (r), Write (w), Execute (x)
  * User, Group, Others
* **Processes interact with files through system calls**: `open()`, `read()`, `write()`, `close()`
* Devices and IPC mechanisms are accessed like files
* **Symlinks**: Short for symbolic link is a special type of file that points to another file or directory. It is 
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
| `/tmp`    | Temporary files                                    |
| `/var`    | Variable data (logs, spool files)                  |
| `/usr`    | Secondary hierarchy for user programs and data     |
| `/home`   | User home directories                              |
| `/lib`    | Essential shared libraries                         |
| `/opt`    | Optional/add-on software pckgs. Can add your own   |
| `/mnt`    | Mount point for temporary mounts                   |
| `/media`  | Mount point for removable media                    |
| `/root`   | For the root user                                  |
| `/run`    | Temp filesystem for temporal runtime information   |
| `/srv`    | If the computer is a service(server) the files for users will be stored here                    |

---

## Disk Partitions

* **Partition**: A division of a storage device that acts as a separate logical unit

* **Types**:

  * Primary (up to 4)
  * Extended (contains logical partitions)
  * Logical (within extended)

* **Tools**:

  * `fdisk` / `parted`: Manage partitions
  * `lsblk`, `blkid`: View block devices
  * `mount` / `umount`: Attach/detach partitions

* **Partition table types**:

  * **MBR (Master Boot Record)**
  * **GPT (GUID Partition Table)** - newer, supports more partitions

---


