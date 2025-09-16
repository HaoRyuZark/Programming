# Arch Linux Setup

Documentatiion for seeting up Arch Linux with the necessary tools and configurations for development.

## Installation 

1. Download the latest Arch Linux ISO from the [official website](https://archlinux.org/download/).

2. Create a bootable USB drive using tools like `Fedora Media Writer`.

3. Boot from the USB drive and select the Arch Linux installation option.

4. You can just follow the installation guide on the [Arch Wiki](https://wiki.archlinux.org/title/Installation_guide) to set up your system. But we will 
provide a some own ownsteps here.

### Custom Installation Steps

1. **Load Keys if needed:** `loadkeys de-latin1` for German

2. **Increase Font:** `setfont ter-132b` or `setfont -d`

3. **Connect to the internet**: Ensure the network interface is listed and enable with `ip link` 
For wireless connections run: `iwctl` and then run the following commands insede `[idw]#`in order:

- `device list`
- `device name set-property Powered on`
- `adapter adapter set-property Powered on`
- `station name scan`
- `station name get-networks`
- `station name connect SSID`
- `station name connect-hidden SSID`
-  Press `Crl + d` to quit

For direct connections you can skip and type: `- $ iwctl --passphrase passphrase station name connect SSID`
And to disconnect if needed: `[iwd]# station device disconnect`

4. **Update the system clock:* `timedatectl`

5. **Partion the disks using fdisk:** Identify the hardrive using `lsblk` then run the following commands in order:

- `fdisk /dev/your_drive_name`
- `p` Prints the partitions
- `g` Gives us an empty partition table 
- `n` Creates a new partition - `Enter` - `Enter` - `+1G` - `Y` if prompted
- `n` Creates a new partition - `Enter` - `Enter` - `+4G` - `Y` if prompted
- `n` Creates a new partition - `Enter` - `Enter` - `Enter` - `Y` if prompted

**Optional** because we are going to format them manually anyway

- `t` Mark a partition with a type - `2` - `82` For the swap type 
- `t` Mark a partition with a type - `3` - `48` For the linux file system type
- `t` Mark a partition with a type - `1` - `1` For the boot type

**Finally**

- `w` Write and quit

In case you messed up you can use `d` to delete a partition or `q` to quit without saving and start again.

6. **Format the partitions:**

Type the following commands to format the partition. I recommend using `ext4` or 
`btrfs` for the filesystem. Type the actual name o your partition in the following commands

- `mkfs.btrfs /dev/nvme0n1p3/`
- `mkfs.fat -F 32 /dev/nvme0n1p1/`
- `mkfs.swap /dev/nvme0n1p2/`
 
7. **Mount the filesystem:**

- `mount /dev/nvme0n1p3 /mnt`
- `mkdir -p /mnt/boot/efi`
- `mount /dev/nvme0n1p1 /mnt/boot/efi`
- `swapon /dev/nvme0n1p2`

8. **Install Essentials Packages:**

- `pacstrap /mnt base linux linux-firmware sof-firmware base-devel grub efibootmgr vim nano networkmanager ly dunst`

If asked for some audio dependency choose `pulse`

9. **Fstab**

- `genfstab /mnt > /mnt/etc/fstab`

10. **Chroot**

Enter the installed system 

- `arch-chroot /mnt`

11. **Time**

Run inside arch:

- `ln -sf /usr/share/zoneinfo/Europe/Berlin /etc/localtime`
- `hwclock --systohc`


12. **Localization**

Run inside arch:

- `vim /etc/locale.gen` Uncomment `en_US.UTF-8 UTF-8` for english and write changes 
- `locale-gen`
- `vim /etc/locale.conf` Type `LANG=en_US.UTF-8` for english and write changes 
- `vim /etc/vconsole.conf` Type`KEYMAP=us` for english and write changes 

13. **Host Name**

Choose an epic name for the computer

- `vim /etc/hostname` Type `Father` or some epic name.

14. **Root Password**

Run `passwd` and type a safe root password

15. **User plus sudo**

Creating user in the group wheel

- `useradd -m -G wheel -s /bin/bash migu`
- `passwd migu`

Sudo:

- `EDITOR=vim visudo` - Then Uncomment the line: `%wheel ALL=(ALL) ALL` and save

16. **Enbling core services**

- `systemctl enable NetworkManager`
- `systemctl enable ly.service`

17. **Bootloader**

- `grub-install /dev/nvme0n1`
- `grub-mkconfig -o /boot/grub/grub.cfg`

18. **Reboot**

- `exit`
- `umount -a`
- `reboot`

If everything was done correctly you sould have a working installation.

---

## Post Install

### Connecto to the internet via Wifi

List nearby Wi-Fi networks:

- `nmcli device wifi list`

Connect to a Wi-Fi network:

- `nmcli device wifi connect SSID_or_BSSID password password`

Alternatively a GUI can be used via the command 

- `nmtui` 

---

### Install SSH Agent

- `sudo pacman -S sshagent`
- `sudo systemctl enable sshd.service`

---

### Install a browser

- `sudo pacman -S firefox`

---

### Set up a firewall

- `sudo pacman -S ufw`
- `sudo systemctl enable ufw.service`

---

### Set up Basic Graphics with sway

- `sudo pacman -S sway`
- Reboot or run `sway`

---

### Set up SSH

#### Check if you already have an SSH key

- `ls ~/.ssh`

Look for files like `id_rsa` and `id_rsa.pub`. If they exist, skip to step 1.4.

#### 1.1 Generate a new SSH key

- `ssh-keygen -t ed25519 -C "your_email@example.com" `

> When prompted, press **Enter** to accept the default file location. You can add a passphrase for extra security (optional).

#### 1.2 Start the SSH agent

- `eval "$(ssh-agent -s)"`

#### 1.3 Add your key to the SSH agent

- `ssh-add ~/.ssh/id_ed25519`

#### 1.4 Add your SSH key to GitHub

Copy the public key:

- `cat ~/.ssh/id_ed25519.pub`

Go to **GitHub → Settings → SSH and GPG keys → New SSH key**, and paste it there.

---

### Install the Packages by copying the following command:

- `sudo pacman -S texlive fastetch 7zip make kitty neovim python pip stow npm python 
   wl-clippboard wofi xorg-wayland luarocks linux-lts lua wayland 
   nodejs waybar rust jdk-open-jdk htop man-db man-pages openssh git yazi vi zathura zathura-pdf-poppler
   julia noto-fonts noto-fonts-emoji noto-fonts-cjk ttf-linux-libertine wget ruby composer php
   xdotool biber wget pipewire pipewire-alsa pipewire-pulse wireplumber pavucontrol lm_sensors btop
   clamav sxiv bleachbit reflector jupyterlab jupyter-notebook python-numpy python-pandas python-matplotlib python-pygame
   tk nm-connection-editor iwd modemmanager usb_modeswitch timeshift tmux otf-font-awesome
   fzf bat lsd tldr lazygit swayidle thunar autotiling starship python-scikit-learn docker`

---

### Setup yay

- `git clone https://aur.archlinux.org/yay.git`
- `cd yay/`
- `cd makepkg -si`

--- 

### Install Extra Packages

- `yay -S brave-bin` - `Enter` - `Enter`
- `yay -S ripgrep`
- `yay -S fd`
- `yay -S visual-studio-code-bin`
- `sudo npm install -g neovim`
- `sudo pacman -S python-neovim`
- `sudo pacman -S python-pylatexenc`
- `gem install neovim`
- `sudo npm install -g regex`
- `npm install -g tree-sitter-cli`

---

### GTK and Qt Themes 

- **Setting up the Qt env var:** write `QT_QPA_PLATFORMTHEME="qt5ct"` with `sudo vim /etc/environment `
- **Instaling Qt Themes:** `sudo pacman -S breeze` 

--- 

### ClamAV

- Initial Configuration:

* `clamconf -g freshclam.conf > freshclam.conf`
* `clamconf -g clamd.conf > clamd.conf`
* `clamconf -g clamav-milter.conf > clamav-milter.conf`

- Follow the steps on the wiki for the rest of the config: [ClamAV Arch](https://wiki.archlinux.org/title/ClamAV)

- Update database: `freshclam`
 
---

### None-ls 

Run inside neovim

- `MasonInstall erb-lint`
- `MasonInstall prettier`
- `MasonInstall stylua`
- `MasonInstall rubocop`

---

### Sensors 

To setup the sensors run the command 

`sensors-detect` then type `YES` for all safe operations. 

To see the data type `sensors`

---

### Clone Configuration repositories

For everything related to a 'Rice' clone the repositories or setup own configurations. One option is to 
clone the necessary repositories from github or use stow.

- `git clone git@github.com:HaoRyuZark/dotfiles.git` 
- `cd dotfiles`
- `stow */`

#### Functionality

1. To add files to stow use create a mirror of the original struture from the home directory to that file. 

2. Copy the file or directory to stow 

3. Run `stow --adopt .` inside the dotfiles directory

---

### Devdocs 

To have offline documentation run 

- `sudo docker run --name devdocs -d -p 9292:9292 ghcr.io/freecodecamp/devdocs:latest`

---

### systemctl For enabling key Packages

#### Basic `systemctl` Commands

`systemctl` is the primary tool used to examine and control the `systemd` system and service manager on Linux systems. Here are some essential commands:

- **Start a service**  `sudo systemctl start <service-name>`

- **Stop a service** `sudo systemctl stop <service-name>`

- **Restart a service** `sudo systemctl restart <service-name>`

- **Enable a service** `sudo systemctl enable <service-name>`

- **Disable a service** `sudo systemctl disable <service-name>`

- **Check status of a service** `systemctl status <service-name>`

- **List all active services** `systemctl list-units --type=service`

---

### Audio 

- `systemctl --user enable --now pipewire pipewire-pulse wireplumber`

---

### Set pdf viewer 

- `xdg-mime default org.pwmt.zathura.desktop application/pdf`

--- 

### Docker 

- `sudo systemctl enable docker.service`

---

### Clone development respositories

- `mkdir Homo_Deus`
- `cd Homo_Deus`
- `git clone git@github.com:HaoRyuZark/Computer_Science_Compedium.git`
- `git clone git@github.com:HaoRyuZark/Mathematica_Compendium.git`
- `git clone git@github.com:HaoRyuZark/Programming.git`

--- 

### University Stuff

Download the Mathematics folder from Google Drive to obtain books and worksheets.


### Second Hardrive 

Use the same procedure like when during the installtion consisting of: 

- Identifying
- Paritioning
- Formating 
- Mounting 

The difference is that this time we want to add it to `fstab` to mount automatically when booting

- Get the UUID with `lsblk -f`
- Open and edit the `/etc/fstab` and add the line `UUID=id /mnt/... file_system_type permisions(defaults) dump_option (0)  policy_option (0)`

### Timeshift

#### Setup via GUI 

To open, use `sudo -E timeshift-gtk` (Not the best way TODO)
1. Select the type of snapshots
2. Select your second storage device 
3. Schedule the snapshot 
4. Select the users: `root` and `yourself`, ... 
5. Skip the filter and click ok 

#### Usage CLI 

- **Check config:** `sudo timeshift --check`
- **Snapshot type:** `sudo timeshift --rsync` or `sudo timeshift --btrfs`
- **Storage Location:** `sudo timeshift --rsync --snapshot-device /dev/disk_to_use` or
  `sudo timeshift --rsync --snapshot-device /mnt/disk_to_use`
- **Create a snapshot:** `sudo timeshift --create --comments "Something" --tags D`
- **See snapshots:** `sudo timeshift --list`
- **Restore system:** `sudo timeshift --restore` then type the identifier of the target
- **Delete snapshot:** `sudo timeshift --delete` then type  the identifier of the target
- **Delete specific snapshot:** `sudo timeshift --delete --snapshot 'date' `
- **Delete snapshots:** `sudo timeshift --delete-all `
- **Scheduleling:** `sudo timeshift --schedule --type_of_schedule num`

--- 

### Maintenance 

- **Clear Cache:** `sudo yay -Scc` and `sudo pacman -Scc`
- **Update database** `sudo yay -Syy`
- **Update:** `sudo yay -Syu`
- **Clean unwanted dependencies:** `yay -Yc`
- **Clean orphan packages:** `sudo pacman -Rns $(pacman -Qtdq)`
- **Free Disk Space:** Use `Bleachbit` or type `du -sh path` to see the disk usage of some directory and 
`rm -rf path/` to remove. Be carefull to not important directories.
- **Cleaning Logs of the Journal directory:** Use `journalctl` to activate the vacuum option. 
`sudo journalctl --vacuum-time=2weeks`
- **Update the mirror list:** `sudo reflector -c COUNTRY -a 6 --sort rate --save /etc/pacman.d/mirrorlist `

--- 

## Command ip link 

In linux the `ip link` command will return three device names 

- `lo` for the loop back device 
- `Ethernet Plug` 
- `Ẁifi card`

--- 

## Image viewer

- `sxiv path_to_the_image`

--- 

## Pacman and Yay

Pacman was used for almost all examples, but Yay can also be used.

* **Installing packages**:
  `pacman -S package_name1 package_name2 ...`

* **Installing groups**:
  `pacman -S gnome`

* **Removing packages**:
  `pacman -R gnome`

* **Removing packages with dependencies**:
  `pacman -Rs gnome`

* **Updating the official packages**:
  `pacman -Syu`

* **Updating the official and unofficial packages**:
  `yay -Syu`

* **Searching for a package in the official repos**:
  `pacman -Ss package_name`

* **Searching for a package in AUR (yay)**:
  `yay -Ss package_name`

* **Viewing installed packages**:
  `pacman -Q`

* **Viewing explicitly installed packages**:
  `pacman -Qe`

* **Viewing dependencies of a package**:
  `pacman -Qi package_name`

* **Cleaning the package cache (remove all except the latest version)**:
  `pacman -Sc`

* **Cleaning the package cache completely**:
  `pacman -Scc`

* **Installing a local package file (.pkg.tar.zst)**:
  `pacman -U ./package_file.pkg.tar.zst`

* **Reinstalling a package**:
  `pacman -S package_name`

* **Removing orphaned packages**:
  `pacman -Rns $(pacman -Qtdq)`

* **Editing and building packages from AUR with yay**:
  `yay -G aur_package_name && cd aur_package_name && makepkg -si`

* **Eliminate Orphan Packages**:
  `sudo pacman -Qdtq | sudo pacman -Rns -`

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
| `/sys`    | Acts as a dynamic interface between the kernel and the hardware  |

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



