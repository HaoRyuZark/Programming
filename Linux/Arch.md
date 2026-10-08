# Arch Set-Up

Installation and set-up guide for **Arch Linux**.

--- 

## Installation Of Arch

1. Download the latest Arch Linux ISO from the [official website](https://archlinux.org/download/).

2. Create a bootable USB drive using tools like `Fedora Media Writer`.

If you are a masochist, then proceed to use the terminal:

  - run `lsblk` to identify the name of the USB-device.

  - `sudo dd bs=4M if=~/Downloads/archlinux-2XXX.XX.XX-86_64.iso of=/dev/your_device_name status=progress`

3. Boot from the USB drive and select the Arch Linux installation option.

4. You can just follow the installation guide on the [Arch Wiki](https://wiki.archlinux.org/title/Installation_guide) to set up your system. But we will 
provide a some own steps here.

### Custom Installation Steps

1. **Load Keys if needed:** `loadkeys de-latin1` for German if you are not using a US-keyboard.

2. **Increase Font:** `setfont ter-132b` or `setfont -d`.

3. **Connect to the internet**: Ensure the network interface is listed and enable with `ip link` 
For wireless connections run: `iwctl` and then run the following commands inside `[idw]#`in order:

  - `device list`: will tell you the name of your device.
  - `device <name> set-property Powered on`
  - `adapter <adapter> set-property Powered on`
  - `station <name> scan`
  - `station <name> get-networks`
  - `station <name> connect SSID`
  - `station <name> connect-hidden SSID`
  -  Press `Crl + d` to quit

For direct connections you can skip and type: `- $ iwctl --passphrase passphrase station <name> connect SSID`
And to disconnect if needed: `[iwd]# station device disconnect`

4. **Update the system clock:** `timedatectl`

5. **Partion the disks using fdisk:** Identify the hard-drive using `lsblk` then run the following commands in order (note that I am skiping the prompts):

  - `fdisk /dev/your_drive_name`.
  - `p` Prints the partitions.
  - `g` Gives us an empty partition table.
  - `n` Creates a new partition - `Enter` - `Enter` - `+1G` - `Y` if prompted.
  - `n` Creates a new partition - `Enter` - `Enter` - `+4G` - `Y` if prompted.
  - `n` Creates a new partition - `Enter` - `Enter` - `Enter` - `Y` if prompted.

- **Optional** because we are going to format them manually anyway

  - `t` Mark a partition with a type - `2` - `82` For the swap type 
  - `t` Mark a partition with a type - `3` - `48` For the linux file system type
  - `t` Mark a partition with a type - `1` - `1` For the boot type

- **Finally**

  - `w` Write and quit

In case you messed up you can use `d` to delete a partition or `q` to quit without saving and start again.

6. **Format the partitions:**

Type the following commands to format the partition. I recommend using `ext4` or `btrfs` for the file-system. Type the actual name of 
your partition in the following commands

  - `mkfs.btrfs /dev/nvme0n1p3/`
  - `mkfs.fat -F 32 /dev/nvme0n1p1/`
  - `mkfs.swap /dev/nvme0n1p2/`
 
7. **Mount the file-system:**

  - `mount /dev/nvme0n1p3 /mnt`
  - `mkdir -p /mnt/boot/efi`
  - `mount /dev/nvme0n1p1 /mnt/boot/efi`
  - `swapon /dev/nvme0n1p2`

8. **Install Essentials Packages:**

  - `pacstrap /mnt base linux linux-firmware sof-firmware base-devel grub efibootmgr vim nano networkmanager ly dunst`

If asked for some audio dependency choose `pulse`.

9. **Fstab**

  - `genfstab /mnt > /mnt/etc/fstab`

10. **Chroot**: Enter the installed system 

  - `arch-chroot /mnt`

11. **Time**

Run inside arch:

  - `ln -sf /usr/share/zoneinfo/Europe/Berlin /etc/localtime`
  - `hwclock --systohc`


12. **Localization**

Run inside arch:

  - `vim /etc/locale.gen` uncomment `en_US.UTF-8 UTF-8` for English and write changes 
  - `locale-gen`
  - `vim /etc/locale.conf` Type `LANG=en_US.UTF-8` for English and write changes 
  - `vim /etc/vconsole.conf` Type`KEYMAP=us` for English and write changes 

13. **Host Name**

Choose an epic name for the computer

  - `vim /etc/hostname` Type `Father` or some epic name.

14. **Root Password**

Run `passwd` and type a safe root password.

15. **User plus sudo**

Creating user in the group wheel

  - `useradd -m -G wheel -s /bin/bash migu`
  - `passwd migu`: to set a password.

sudo:

  - `EDITOR=vim visudo` - Then Uncomment the line: `%wheel ALL=(ALL) ALL` and save

16. **Enabling core services**

  - `systemctl enable NetworkManager`
  - `systemctl enable ly@ttyX.service`

17. **Bootloader**

  - `grub-install /dev/nvme0n1`
  - `grub-mkconfig -o /boot/grub/grub.cfg`

18. **Reboot**

  - `exit`
  - `umount -a`
  - `reboot`

If everything was done correctly you should have a working installation.

---

## Post Arch Install

### Connecto to the internet via Wifi

List nearby Wi-Fi networks:

- `nmcli device wifi list`

Connect to a Wi-Fi network:

- `nmcli device wifi connect SSID_or_BSSID password password`

Alternatively a GUI can be used via the command 

- `nmtui` 

### Install SSH Agent

- `sudo pacman -S sshagent`
- `sudo systemctl enable sshd.service`

### Install a browser

- `sudo pacman -S firefox`

### Set up a firewall

- `sudo pacman -S ufw`
- `sudo systemctl enable ufw.service`

### Set up Basic Graphics with sway

- `sudo pacman -S sway`
- Reboot or run `sway`

---
## Pacman and Yay

[`pacman`](https://wiki.archlinux.org/title/Pacman) is the package manager used by Arch Linux and is the primary tool for installing, removing, querying, 
and updating packages from the official Arch Linux repositories.

[`yay`](https://github.com/Jguer/yay) is an AUR helper that provides a similar interface to `pacman` while also allowing packages from the 
**Arch User Repository (AUR)** to be searched, built, installed, and updated.


### Pacman Command Structure

Most `pacman` commands follow this structure:

```bash
pacman [options] [package(s)]
```

The most important operation flags are:


| Flag | Long form    | Function                                          |
| ---- | ------------ | ------------------------------------------------- |
| `-S` | `--sync`     | Install or synchronize packages from repositories |
| `-R` | `--remove`   | Remove installed packages                         |
| `-Q` | `--query`    | Query the local package database                  |
| `-F` | `--files`    | Query which package owns a file                   |
| `-U` | `--upgrade`  | Install/upgrade from a local package file or URL  |
| `-D` | `--database` | Modify/query package database information         |


Several options can be combined. For example:

```bash
pacman -Syu
```

is equivalent to:

```text
-S   Synchronize with repositories
-y   Refresh repository databases
-u   Upgrade installed packages
```


### Installing Packages

Install one or more packages from the official repositories:

```bash
sudo pacman -S package_name
sudo pacman -S package_name1 package_name2 package_name3
```

* `-S` / `--sync`: synchronize and install packages.
* Multiple packages can be specified in the same command.
* `sudo` is required because packages are installed system-wide.

### Installing a Package Group

Some software is distributed as a **package group**, which contains multiple related packages.

```bash
sudo pacman -S gnome
```

Pacman may display the packages belonging to the group and ask which ones should be installed.

You can search for available groups with:

```bash
pacman -Sg
```

or search for groups matching a name:

```bash
pacman -Sg | grep gnome
```

### Removing Packages

Remove a package:

```bash
sudo pacman -R package_name
```

`-R` / `--remove` removes the specified package but does not automatically remove its dependencies.

To remove the package and dependencies that are no longer required:

```bash
sudo pacman -Rs package_name
```

* `-s` / `--recursive`: removes dependencies that are no longer required by any other explicitly installed package.

For example:

```bash
sudo pacman -Rs gnome
```

Use recursive removal carefully because it can remove packages that were installed as dependencies.

To additionally remove configuration files associated with the package:

```bash
sudo pacman -Rns package_name
```

* `-n` / `--nosave`: removes backup configuration files instead of saving them as `.pacsave` files.

### Updating the System

Refresh the package databases and upgrade all installed packages:

```bash
sudo pacman -Syu
```

The flags mean:

* `-S` / `--sync`: synchronize packages with the repositories.
* `-y` / `--refresh`: download fresh package database information.
* `-u` / `--sysupgrade`: upgrade all installed packages that have newer versions available.

This is the standard command for performing a full Arch Linux system upgrade.

> **Important:** Avoid performing partial upgrades such as installing packages with an outdated package database. Arch Linux is designed around full system upgrades.

With `yay`:

```bash
yay -Syu
```

This can upgrade packages from both the official repositories and the AUR.

### Searching for Packages

Search the official repositories:

```bash
pacman -Ss package_name
```

* `-S`: operate on repository packages.
* `-s` / `--search`: search package names and descriptions.

Example:

```bash
pacman -Ss neovim
```

Search the AUR and official repositories using `yay`:

```bash
yay -Ss package_name
```

Because `yay` also queries the AUR, this can return packages that are not available in the official Arch repositories.

### Viewing Installed Packages

List all installed packages:

```bash
pacman -Q
```

* `-Q` / `--query`: query the local package database.

List packages that were explicitly installed by the user:

```bash
pacman -Qe
```

* `-e` / `--explicit`: show explicitly installed packages.

List packages that were installed as dependencies:

```bash
pacman -Qd
```

* `-d` / `--deps`: show packages installed as dependencies.

List orphaned packages:

```bash
pacman -Qdt
```

* `-d`: packages installed as dependencies.
* `-t` / `--unrequired`: packages that are no longer required by another package.

To obtain only the package names:

```bash
pacman -Qdtq
```

The additional `-q` / `--quiet` suppresses extra information and prints only package names.

### Inspecting a Package

Display detailed information about an installed package:

```bash
pacman -Qi package_name
```

This can show information such as:

* package name
* version
* architecture
* installation date
* installation reason
* dependencies
* optional dependencies
* package size
* description

To inspect a package that is available in the repositories but not installed:

```bash
pacman -Si package_name
```

* `-i` / `--info`: display detailed package information.

### Finding Which Package Owns a File

To determine which installed package owns a file:

```bash
pacman -Qo /path/to/file
```

* `-Q`: query the local package database.
* `-o` / `--owns`: determine which package owns a file.

Example:

```bash
pacman -Qo /usr/bin/bash
```

To search the **repository file databases** for a file that is not necessarily installed:

```bash
pacman -Fy
pacman -F /usr/bin/example
```

`-F` operates on the package file database rather than the installed-package database.

### Viewing Package Files

List all files installed by a package:

```bash
pacman -Ql package_name
```

* `-l` / `--list`: list files owned by the package.

For example:

```bash
pacman -Ql bash
```

### Cleaning the Package Cache

Pacman stores downloaded package files in:

```text
/var/cache/pacman/pkg/
```

Remove cached packages except for versions currently installed:

```bash
sudo pacman -Sc
```

* `-c` / `--clean`: clean the package cache.
* Running it once generally removes cached packages that are no longer installed.

To remove **all** cached package files:

```bash
sudo pacman -Scc
```

* `-c` twice performs a more aggressive cache cleanup.

### Installing a Local Package

Install a locally downloaded package:

```bash
sudo pacman -U ./package_file.pkg.tar.zst
```

* `-U` / `--upgrade`: install or upgrade a package from a local file or URL.

For example:

```bash
sudo pacman -U ./example-1.0-1-x86_64.pkg.tar.zst
```

The `.pkg.tar.zst` extension is the standard package format used by Arch Linux.

### Reinstalling a Package

A package can be reinstalled using:

```bash
sudo pacman -S package_name
```

If the package is already installed, pacman normally asks whether it should be reinstalled.

For example:

```bash
sudo pacman -S bash
```

This is useful if files belonging to an installed package have become corrupted or were accidentally deleted.

### Removing Orphaned Packages

First, list orphaned packages:

```bash
pacman -Qdt
```

If the list is correct, remove them:

```bash
sudo pacman -Rns $(pacman -Qdtq)
```

Here:

* `pacman -Qdtq` produces the names of orphaned packages.
* `$(...)` passes those package names to the `pacman -Rns` command.
* `-R` removes the packages.
* `-n` removes associated backup configuration files.
* `-s` removes dependencies that become unnecessary.

An alternative that avoids command substitution is:

```bash
sudo pacman -Qdtq | sudo pacman -Rns -
```

The `-` tells pacman to read package names from standard input.

---

## Yay

`yay` is an AUR helper. It supports many of the same commands and flags as pacman.

For example:

```bash
yay -S package_name
```

can install either an official repository package or an AUR package.

### Installing an AUR Package

```bash
yay -S aur_package_name
```

`yay` downloads the package's PKGBUILD, builds it, and installs the resulting package.

Unlike official repository packages, AUR packages are generally built locally from build instructions maintained by AUR contributors.

You should therefore inspect AUR packages and their PKGBUILDs before installing software you do not trust.

### Searching the AUR

```bash
yay -Ss package_name
```

Searches for matching packages in the repositories and AUR.

For example:

```bash
yay -Ss visual-studio-code
```

### Updating Official and AUR Packages

```bash
yay -Syu
```

This performs a full system upgrade and can update both:

1. packages from the official Arch repositories
2. packages installed from the AUR

This is one of the main reasons to use `yay` as a convenience tool.

### Downloading an AUR Package Without Installing It

Use:

```bash
yay -G aur_package_name
```

* `-G` / `--getpkgbuild`: download the PKGBUILD and related files for an AUR package.

For example:

```bash
yay -G some-package
cd some-package
```

You can then inspect the files:

```bash
less PKGBUILD
```

and build/install the package manually:

```bash
makepkg -si
```

Here:

* `makepkg`: builds an Arch package from a `PKGBUILD`.
* `-s` / `--syncdeps`: automatically install missing dependencies.
* `-i` / `--install`: install the package after building it.

This gives you more control than simply running:

```bash
yay -S some-package
```


## Pacman Mirror Selection

Arch Linux downloads packages from **mirrors**, which are servers that host copies of the official Arch repositories.

The configured mirrors are normally listed in:

```text
/etc/pacman.d/mirrorlist
```

A mirror entry looks approximately like:

```text
Server = https://mirror.example.org/archlinux/$repo/os/$arch
```

The variables are replaced automatically:

* `$repo` → repository name, such as `core` or `extra`
* `$arch` → system architecture, normally `x86_64`

### Checking the Current Mirror List

```bash
cat /etc/pacman.d/mirrorlist
```

The order of the mirrors matters. Pacman will generally try the configured servers in order.

### Selecting Fast Mirrors

Arch provides tools for generating a mirror list. A commonly used tool is `reflector`.

Install it with:

```bash
sudo pacman -S reflector
```

For example, to generate a mirror list using HTTPS mirrors from Germany:

```bash
sudo reflector --country Germany --protocol https --latest 10 --sort rate --save /etc/pacman.d/mirrorlist
```

The important options are:

* `--country Germany`: restrict mirrors to Germany.
* `--protocol https`: only use HTTPS mirrors.
* `--latest 10`: select the 10 most recently synchronized mirrors.
* `--sort rate`: sort mirrors by download rate.
* `--save`: write the resulting list to the specified file.

You can also use multiple countries:

```bash
sudo reflector \
    --country Germany,Netherlands,France \
    --protocol https \
    --latest 20 \
    --sort rate \
    --save /etc/pacman.d/mirrorlist
```

After changing the mirror list, refresh the package databases:

```bash
sudo pacman -Syy
```


### Useful Reflector Options


| Option         | Function                                  |
| -------------- | ----------------------------------------- |
| `--country`    | Select mirrors from one or more countries |
| `--protocol`   | Restrict mirrors to HTTP/HTTPS/RSYNC      |
| `--latest`     | Select mirrors synchronized recently      |
| `--sort rate`  | Sort by measured download speed           |
| `--sort age`   | Sort by mirror synchronization age        |
| `--sort score` | Sort using Reflector's score              |
| `--save`       | Save the generated list to a file         |
| `--verbose`    | Display additional information            |


A practical configuration for a German Arch installation could therefore be:

```bash
sudo reflector \
    --country Germany \
    --protocol https \
    --latest 20 \
    --sort rate \
    --save /etc/pacman.d/mirrorlist
```


## Common Pacman Flags

The following flags are useful to remember:

| Flag | Meaning                                                 | Example                       |
| ---- | ------------------------------------------------------- | ----------------------------- |
| `-S` | Synchronize/install repository packages                 | `pacman -S git`               |
| `-R` | Remove packages                                         | `pacman -R git`               |
| `-Q` | Query installed packages                                | `pacman -Q`                   |
| `-U` | Install local package                                   | `pacman -U ./pkg.pkg.tar.zst` |
| `-y` | Refresh package databases                               | `pacman -Sy`                  |
| `-u` | Upgrade installed packages                              | `pacman -Su`                  |
| `-s` | Recursive dependencies / search, depending on operation | `pacman -Rs pkg`              |
| `-n` | Do not save backup configuration files                  | `pacman -Rn pkg`              |
| `-q` | Quiet output                                            | `pacman -Qq`                  |
| `-i` | Display detailed information                            | `pacman -Qi pkg`              |
| `-c` | Clean package cache                                     | `pacman -Sc`                  |
| `-d` | Dependency-related query/removal option                 | `pacman -Qd`                  |
| `-e` | Explicitly installed packages                           | `pacman -Qe`                  |
| `-t` | Unrequired packages                                     | `pacman -Qt`                  |
| `-o` | Find package owning a file                              | `pacman -Qo file`             |

  

---

## Install the Packages by copying the following command:

```bash
sudo pacman -Syu --needed \
  texlive biber texlab fastfetch 7zip make kitty neovim vi \
  python python-pip stow npm nodejs \
  wl-clipboard wofi xorg-xwayland wayland waybar swayidle swaync swayimg imv \
  luarocks lua lua-language-server linux-lts \
  rust jdk-openjdk go ruby php composer clang ghc cabal-install julia \
  htop btop man-db man-pages openssh git yazi \
  zathura zathura-pdf-poppler \
  noto-fonts noto-fonts-emoji noto-fonts-cjk otf-libertinus otf-font-awesome \
  wget xdotool \
  pipewire pipewire-alsa pipewire-pulse wireplumber pavucontrol \
  lm_sensors clamav nsxiv bleachbit reflector pacman-contrib timeshift \
  jupyterlab jupyter-notebook python-numpy python-pandas python-matplotlib \
  python-pygame python-scikit-learn tk \
  nm-connection-editor network-manager-applet iwd modemmanager usb_modeswitch \
  tmux fzf bat lsd tldr lazygit thunar autotiling starship \
  docker kubectl pyright bash-language-server postgresql \
  wine w3m polkit lxqt-policykit seahorse pkgconf openssl \ 
  prettier
```

### Typesetting

- **biber**: bibliography backend for BibLaTeX
- **texlab**: LaTeX language server
- **otf-libertinus**: Libertinus serif font, successor to Linux Libertine

### Terminal and shell tools

- **fastfetch**: system info display (neofetch replacement)
- **kitty**: GPU-accelerated terminal emulator
- **tmux**: terminal multiplexer
- **starship**: fast customizable shell prompt
- **fzf**: fuzzy finder
- **bat**: `cat` with syntax highlighting
- **lsd**: modern `ls` with icons and colors
- **tldr**: simplified command-line examples
- **htop**: interactive process viewer
- **btop**: fancier resource monitor
- **yazi**: terminal file manager
- **w3m**: text-based web browser
- **utftex** (AUR): renders LaTeX math as Unicode text
- **7zip**: `7z` archiver
- **stow**: symlink manager for dotfiles

### Editor

- **neovim**: modern Vim
- **vi**: minimal POSIX vi fallback

### Build and languages

- **make**: build automation
- **pkgconf**: compiler flag lookup for libraries
- **openssl**: TLS and crypto library and CLI
- **clang**: C/C++ compiler and LLVM tooling
- **rust**: Rust compiler and cargo
- **go**: Go compiler and toolchain
- **python**: Python interpreter
- **python-pip**: Python package installer
- **nodejs**: JavaScript runtime
- **npm**: Node package manager
- **lua**: Lua interpreter
- **luarocks**: Lua package manager
- **ruby**: Ruby interpreter
- **php**: PHP interpreter
- **composer**: PHP dependency manager
- **jdk-openjdk**: Java development kit
- **ghc**: Haskell compiler
- **cabal-install**: Haskell build and package tool
- **julia**: Julia language for scientific computing
- **tk**: Tk GUI toolkit (needed by Python's tkinter and matplotlib)

### Language servers

- **pyright**: Python type checker and LSP
- **lua-language-server**: Lua LSP
- **bash-language-server**: Bash LSP

### Formatters 

- **prettier**: code formatter for JavaScript, TypeScript, HTML, CSS, and more.

### Data science and Python libraries

- **jupyterlab**: notebook IDE
- **jupyter-notebook**: classic notebook interface
- **python-numpy**: numerical arrays
- **python-pandas**: dataframes
- **python-matplotlib**: plotting
- **python-scikit-learn**: machine learning
- **python-pygame**: 2D game library
- **miniconda3** (AUR): conda environment and package manager

### Wayland desktop

- **wayland**: display protocol library
- **xorg-xwayland**: runs X11 apps under Wayland
- **wofi**: app launcher
- **waybar**: status bar
- **swayidle**: idle management (lock/suspend timers)
- **swaync**: notification daemon and control center
- **wl-clipboard**: `wl-copy`/`wl-paste` clipboard tools
- **autotiling**: automatic split direction for Sway/i3
- **xdotool**: X11 input automation (only affects XWayland apps)
- **thunar**: GUI file manager
- **imv**: Wayland image viewer
- **swayimg**: lightweight image viewer
- **nsxiv**: X11 image viewer (drop it if imv/swayimg are enough)
- **zathura**: minimal document viewer
- **zathura-pdf-poppler**: PDF backend for zathura

### Fonts

- **noto-fonts**: broad Latin/Greek/Cyrillic coverage
- **noto-fonts-emoji**: emoji
- **noto-fonts-cjk**: Chinese/Japanese/Korean
- **otf-font-awesome**: icon font used by waybar and similar

### Audio

- **pipewire**: audio/video server
- **pipewire-alsa**: ALSA compatibility layer
- **pipewire-pulse**: PulseAudio compatibility layer
- **wireplumber**: PipeWire session manager
- **pavucontrol**: volume control GUI

### Networking

- **iwd**: Intel's wireless daemon
- **nm-connection-editor**: NetworkManager connection GUI
- **network-manager-applet**: tray applet with wifi password prompts
- **modemmanager**: mobile broadband modem support
- **usb_modeswitch**: switches USB modems out of storage mode
- **openssh**: SSH client and server
- **wget**: file downloader

### System and maintenance

- **linux-lts**: long-term-support kernel, a fallback
- **man-db**: man page viewer
- **man-pages**: Linux man pages
- **lm_sensors**: hardware temperature and fan sensors
- **timeshift**: system snapshots and restore
- **reflector**: updates the mirror list
- **pacman-contrib**: extras like `paccache` and `checkupdates`
- **downgrade** (AUR): roll back packages to older versions
- **bleachbit**: disk cleaner
- **clamav**: antivirus
- **polkit**: privilege-escalation framework
- **lxqt-policykit**: polkit authentication agent (GUI password prompts)
- **seahorse**: GNOME keyring and password manager GUI

### Dev services and containers

- **git**: version control
- **lazygit**: terminal UI for git
- **docker**: container engine (run `sudo systemctl enable --now docker` and add yourself to the `docker` group)
- **kubectl**: Kubernetes CLI
- **postgresql**: database server (needs `initdb` before first start)
- **wine**: runs Windows applications

- Some packages (`pipewire`, `jack`, fonts) can trigger interactive provider prompts. If the command stops to ask, just press Enter for the default.

---

## Setup yay

- `git clone https://aur.archlinux.org/yay.git`
- `cd yay/`
- `cd makepkg -si`

 ```bash
yay -S utftex miniconda3 downgrade
```


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
- `yay -S sql-language-server`
- `yay -S asm-lsp`
- `rustup component add rust-analyzer`
- `yay -S tex-fmt`
- `cargo install --git https://github.com/itsjunetime/tdf.git`
- `sudo npm install -g @angular/cli`

--- 

## Clone Configuration repositories

For everything related to a 'Rice' clone the repositories or setup own configurations. One option is to 
clone the necessary repositories from github or use stow.

- `git clone git@github.com:HaoRyuZark/dotfiles.git` 
- `cd dotfiles`
- `stow */`

### Stow Functionality

- **First Setup**: `stow -D */` to remove the stow links and `stow */` to create the stow links.

- **Adding files to stow and updating**:

  1. To add files to stow use create a mirror of the original struture from the home directory to that file. 

  2. Copy the file or directory to stow 

  3. Run `stow --adopt .` inside the dotfiles directory
 
---

## Vim Provider 

Run 

```py
pip install --user pynvim` or `pip3 install --user pynvim
```

to install the python provider for neovim. Else there will be an error in the `checkhealth` command of neovim.

--- 

## GTK and Qt Themes 

- **Setting up the Qt env var:** write `QT_QPA_PLATFORMTHEME="qt5ct"` with `sudo vim /etc/environment `
- **Instaling Qt Themes:** `sudo pacman -S breeze` 

--- 

## Maintenance 

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

## Timeshift

### Setup via GUI 

To open, use `sudo -E timeshift-gtk` (Not the best way TODO)

1. Select the type of snapshots

2. Select your second storage device 

3. Schedule the snapshot 

4. Select the users: `root` and `yourself`, ... 

5. Skip the filter and click ok 

### Usage CLI 

- **Check config:** `sudo timeshift --check`

- **Snapshot type:** `sudo timeshift --rsync` or `sudo timeshift --btrfs`

- **Storage Location:** `sudo timeshift --rsync --snapshot-device /dev/disk_to_use` or `sudo timeshift --rsync --snapshot-device /mnt/disk_to_use`

- **Create a snapshot:** `sudo timeshift --create --comments "Something" --tags D`

- **See snapshots:** `sudo timeshift --list`

- **Restore system:** `sudo timeshift --restore` then type the identifier of the target

- **Delete snapshot:** `sudo timeshift --delete` then type  the identifier of the target

- **Delete specific snapshot:** `sudo timeshift --delete --snapshot 'date' `

- **Delete snapshots:** `sudo timeshift --delete-all `

- **Scheduleling:** `sudo timeshift --schedule --type_of_schedule num`

--- 

## Sensors 

To setup the sensors run the command 

`sensors-detect` then type `YES` for all safe operations. 

To see the data type `sensors`

--- 
 
## ClamAV

- Initial Configuration:

- `clamconf -g freshclam.conf > freshclam.conf`
- `clamconf -g clamd.conf > clamd.conf`
- `clamconf -g clamav-milter.conf > clamav-milter.conf`

#### clamd.conf

```conf

##
## Example config file for the Clam AV daemon
## Please read the clamd.conf(5) manual before editing this file.
##


# Comment or remove the line below.
#Example

# Uncomment this option to enable logging.
# LogFile must be writable for the user running daemon.
# A full path is required.
# Default: disabled
LogFile /var/log/clamav/clamd.log

# By default the log file is locked for writing - the lock protects against
# running clamd multiple times (if want to run another clamd, please
# copy the configuration file, change the LogFile variable, and run
# the daemon with --config-file option).
# This option disables log file locking.
# Default: no
#LogFileUnlock yes

# Maximum size of the log file.
# Value of 0 disables the limit.
# You may use 'M' or 'm' for megabytes (1M = 1m = 1048576 bytes)
# and 'K' or 'k' for kilobytes (1K = 1k = 1024 bytes). To specify the size
# in bytes just don't use modifiers. If LogFileMaxSize is enabled, log
# rotation (the LogRotate option) will always be enabled.
# Default: 1M
#LogFileMaxSize 2M

# Log time with each message.
# Default: no
LogTime yes

DetectPUA yes
HeuristicAlerts yes
ScanPE yes
ScanELF yes
ScanOLE2 yes
ScanPDF yes
ScanSWF yes
ScanXMLDOCS yes
ScanHWP3 yes
ScanOneNote yes
ScanMail yes
ScanHTML yes
ScanArchive yes
Bytecode yes
AlertBrokenExecutables yes
AlertBrokenMedia yes
AlertEncrypted yes
AlertEncryptedArchive yes
AlertEncryptedDoc yes
AlertOLE2Macros yes
AlertPartitionIntersection yes

# Also log clean files. Useful in debugging but drastically increases the
# log size.
# Default: no
#LogClean yes

# Use system logger (can work together with LogFile).
# Default: no
#LogSyslog yes

# Specify the type of syslog messages - please refer to 'man syslog'
# for facility names.
# Default: LOG_LOCAL6
#LogFacility LOG_MAIL

# Enable verbose logging.
# Default: no
#LogVerbose yes

# Enable log rotation. Always enabled when LogFileMaxSize is enabled.
# Default: no
#LogRotate yes

# Enable Prelude output.
# Default: no
#PreludeEnable yes
#
# Set the name of the analyzer used by prelude-admin.
# Default: ClamAV
#PreludeAnalyzerName ClamAV

# Log additional information about the infected file, such as its
# size and hash, together with the virus name.
ExtendedDetectionInfo yes

# This option allows you to save a process identifier of the listening
# daemon.
# This file will be owned by root, as long as clamd was started by root.
# It is recommended that the directory where this file is stored is
# also owned by root to keep other users from tampering with it.
# Default: disabled
PidFile /run/clamav/clamd.pid

# Optional path to the global temporary directory.
# Default: system specific (usually /tmp or /var/tmp).
TemporaryDirectory /tmp

# Path to the database directory.
# Default: hardcoded (depends on installation options)
#DatabaseDirectory /var/lib/clamav

# Only load the official signatures published by the ClamAV project.
# Default: no
#OfficialDatabaseOnly no

# Return with a nonzero error code if the virus database is older than
# the specified number of days.
# Default: -1
#FailIfCvdOlderThan 7

# The daemon can work in local mode, network mode or both.
# Due to security reasons we recommend the local mode.

# Path to a local socket file the daemon will listen on.
# Default: disabled (must be specified by a user)
LocalSocket /run/clamav/clamd.ctl
LocalSocket /run/clamav/clamd.ctl

# Sets the group ownership on the unix socket.
# Default: disabled (the primary group of the user running clamd)
#LocalSocketGroup virusgroup

# Sets the permissions on the unix socket to the specified mode.
# Default: disabled (socket is world accessible)
#LocalSocketMode 660

# Remove stale socket after unclean shutdown.
# Default: yes
#FixStaleSocket no

# TCP port address.
# Default: no
#TCPSocket 3310

# TCP address.
# By default we bind to INADDR_ANY, probably not wise.
# Enable the following to provide some degree of protection
# from the outside world. This option can be specified multiple
# times if you want to listen on multiple IPs. IPv6 is now supported.
# Default: no
#TCPAddr localhost

# Maximum length the queue of pending connections may grow to.
# Default: 200
#MaxConnectionQueueLength 30

# Clamd uses FTP-like protocol to receive data from remote clients.
# If you are using clamav-milter to balance load between remote clamd daemons
# on firewall servers you may need to tune the options below.

# Close the connection when the data size limit is exceeded.
# The value should match your MTA's limit for a maximum attachment size.
# Default: 100M
#StreamMaxLength 25M

# Limit port range.
# Default: 1024
#StreamMinPort 30000
# Default: 2048
#StreamMaxPort 32000

# Maximum number of threads running at the same time.
# Default: 10
#MaxThreads 20

# Waiting for data from a client socket will timeout after this time (seconds).
# Default: 120
#ReadTimeout 300

# This option specifies the time (in seconds) after which clamd should
# timeout if a client doesn't provide any initial command after connecting.
# Default: 30
#CommandReadTimeout 30

# This option specifies how long to wait (in milliseconds) if the send buffer
# is full.
# Keep this value low to prevent clamd hanging.
#
# Default: 500
#SendBufTimeout 200

# Maximum number of queued items (including those being processed by
# MaxThreads threads).
# It is recommended to have this value at least twice MaxThreads if possible.
# WARNING: you shouldn't increase this too much to avoid running out  of file
# descriptors, the following condition should hold:
# MaxThreads*MaxRecursion + (MaxQueue - MaxThreads) + 6< RLIMIT_NOFILE (usual
# max is 1024).
#
# Default: 100
#MaxQueue 200

# Waiting for a new job will timeout after this time (seconds).
# Default: 30
#IdleTimeout 60

# Don't scan files and directories matching regex
# This directive can be used multiple times
# Default: scan all
#ExcludePath ^/proc/
#ExcludePath ^/sys/

# Maximum depth directories are scanned at.
# Default: 15
#MaxDirectoryRecursion 20

# Follow directory symlinks.
# Default: no
#FollowDirectorySymlinks yes

# Follow regular file symlinks.
# Default: no
#FollowFileSymlinks yes

# Scan files and directories on other filesystems.
# Default: yes
#CrossFilesystems no

# Perform a database check.
# Default: 600 (10 min)
#SelfCheck 600

# Enable non-blocking (multi-threaded/concurrent) database reloads.
# This feature will temporarily load a second scanning engine while scanning
# continues using the first engine. Once loaded, the new engine takes over.
# The old engine is removed as soon as all scans using the old engine have
# completed.
# This feature requires more RAM, so this option is provided in case users are
# willing to block scans during reload in exchange for lower RAM requirements.
# Default: yes
#ConcurrentDatabaseReload no

# Execute a command when virus is found.
# Use the following environment variables to identify the file and virus names:
# - $CLAM_VIRUSEVENT_FILENAME
# - $CLAM_VIRUSEVENT_VIRUSNAME
# In the command string, '%v' will also be replaced with the virus name.
# Note: The '%f' filename format character has been disabled and will no longer
# be replaced with the file name, due to command injection security concerns.
# Use the 'CLAM_VIRUSEVENT_FILENAME' environment variable instead.
# For the same reason, you should NOT use the environment variables in the
# command directly, but should use it carefully from your executed script.
# Default: no
#VirusEvent /opt/send_virus_alert_sms.sh

# Run as another user (clamd must be started by root for this option to work)
# Default: don't drop privileges
User clamav

# Stop daemon when libclamav reports out of memory condition.
#ExitOnOOM yes

# Don't fork into background.
# Default: no
#Foreground yes

# Enable debug messages in libclamav.
# Default: no
#Debug yes

# Do not remove temporary files (for debug purposes).
# Default: no
#LeaveTemporaryFiles yes

# Record metadata about the file being scanned.
# Scan metadata is useful for file analysis purposes and for debugging scan behavior.
# The JSON metadata will be printed after the scan is complete if Debug is enabled.
# A metadata.json file will be written to the scan temp directory if LeaveTemporaryFiles is enabled.
# Default: no
#GenerateMetadataJson yes

# Permit use of the ALLMATCHSCAN command. If set to no, clamd will reject
# any ALLMATCHSCAN command as invalid.
# Default: yes
#AllowAllMatchScan no

# Detect Possibly Unwanted Applications.
# Default: no
#DetectPUA yes

# Exclude a specific PUA category. This directive can be used multiple times.
# See https://github.com/vrtadmin/clamav-faq/blob/master/faq/faq-pua.md for
# the complete list of PUA categories.
# Default: Load all categories (if DetectPUA is activated)
#ExcludePUA NetTool
#ExcludePUA PWTool

# Only include a specific PUA category. This directive can be used multiple
# times.
# Default: Load all categories (if DetectPUA is activated)
#IncludePUA Spy
#IncludePUA Scanner
#IncludePUA RAT

# This option causes memory or nested map scans to dump the content to disk.
# If you turn on this option, more data is written to disk and is available
# when the LeaveTemporaryFiles option is enabled.
#ForceToDisk yes

# This option allows you to disable the caching feature of the engine. By
# default, the engine will store an MD5 in a cache of any files that are
# not flagged as virus or that hit limits checks. Disabling the cache will
# have a negative performance impact on large scans.
# Default: no
#DisableCache yes

# This option allows you to set the number of entries the cache can store.
# The value should be a square number or will be rounded up to the nearest
# square number.
#CacheSize 65536

# In some cases (eg. complex malware, exploits in graphic files, and others),
# ClamAV uses special algorithms to detect abnormal patterns and behaviors that
# may be malicious.  This option enables alerting on such heuristically
# detected potential threats.
# Default: yes
#HeuristicAlerts no

# Allow heuristic alerts to take precedence.
# When enabled, if a heuristic scan (such as phishingScan) detects
# a possible virus/phish it will stop scan immediately. Recommended, saves CPU
# scan-time.
# When disabled, virus/phish detected by heuristic scans will be reported only
# at the end of a scan. If an archive contains both a heuristically detected
# virus/phish, and a real malware, the real malware will be reported
#
# Keep this disabled if you intend to handle "Heuristics.*" viruses
# differently from "real" malware.
# If a non-heuristically-detected virus (signature-based) is found first,
# the scan is interrupted immediately, regardless of this config option.
#
# Default: no
#HeuristicScanPrecedence yes


##
## Heuristic Alerts
##

# With this option clamav will try to detect broken executables (both PE and
# ELF) and alert on them with the Broken.Executable heuristic signature.
# Default: no
#AlertBrokenExecutables yes

# With this option clamav will try to detect broken media file (JPEG,
# TIFF, PNG, GIF) and alert on them with a Broken.Media heuristic signature.
# Default: no
#AlertBrokenMedia yes

# Alert on encrypted archives _and_ documents with heuristic signature
# (encrypted .zip, .7zip, .rar, .pdf).
# Default: no
#AlertEncrypted yes

# Alert on encrypted archives with heuristic signature (encrypted .zip, .7zip,
# .rar).
# Default: no
#AlertEncryptedArchive yes

# Alert on encrypted archives with heuristic signature (encrypted .pdf).
# Default: no
#AlertEncryptedDoc yes

# With this option enabled OLE2 files containing VBA macros, which were not
# detected by signatures will be marked as "Heuristics.OLE2.ContainsMacros".
# Default: no
#AlertOLE2Macros yes

# Alert on SSL mismatches in URLs, even if the URL isn't in the database.
# This can lead to false positives.
# Default: no
#AlertPhishingSSLMismatch yes

# Alert on cloaked URLs, even if URL isn't in database.
# This can lead to false positives.
# Default: no
#AlertPhishingCloak yes

# Alert on raw DMG image files containing partition intersections
# Default: no
#AlertPartitionIntersection yes


##
## Executable files
##

# PE stands for Portable Executable - it's an executable file format used
# in all 32 and 64-bit versions of Windows operating systems. This option
# allows ClamAV to perform a deeper analysis of executable files and it's also
# required for decompression of popular executable packers such as UPX, FSG,
# and Petite. If you turn off this option, the original files will still be
# scanned, but without additional processing.
# Default: yes
#ScanPE no

# Certain PE files contain an authenticode signature. By default, we check
# the signature chain in the PE file against a database of trusted and
# revoked certificates if the file being scanned is marked as a virus.
# If any certificate in the chain validates against any trusted root, but
# does not match any revoked certificate, the file is marked as trusted.
# If the file does match a revoked certificate, the file is marked as virus.
# The following setting completely turns off authenticode verification.
# Default: no
#DisableCertCheck yes

# Executable and Linking Format is a standard format for UN*X executables.
# This option allows you to control the scanning of ELF files.
# If you turn off this option, the original files will still be scanned, but
# without additional processing.
# Default: yes
#ScanELF no


##
## Documents
##

# This option enables scanning of OLE2 files, such as Microsoft Office
# documents and .msi files.
# If you turn off this option, the original files will still be scanned, but
# without additional processing.
# Default: yes
#ScanOLE2 no

# This option enables scanning within PDF files.
# If you turn off this option, the original files will still be scanned, but
# without decoding and additional processing.
# Default: yes
#ScanPDF no

# This option enables scanning within SWF files.
# If you turn off this option, the original files will still be scanned, but
# without decoding and additional processing.
# Default: yes
#ScanSWF no

# This option enables scanning xml-based document files supported by libclamav.
# If you turn off this option, the original files will still be scanned, but
# without additional processing.
# Default: yes
#ScanXMLDOCS no

# This option enables scanning of HWP3 files.
# If you turn off this option, the original files will still be scanned, but
# without additional processing.
# Default: yes
#ScanHWP3 no

# This option enables scanning of OneNote files.
# If you turn off this option, the original files will still be scanned, but
# without additional processing.
# Default: yes
#ScanOneNote no


##
## Other file types
##

# This option enables scanning of image (graphics).
# If you turn off this option, the original files will still be scanned, but
# without additional processing.
# Default: yes
#ScanImage no

# This option enables detection by calculating a fuzzy hash of image (graphics)
# files.
# Signatures using image fuzzy hashes typically match files and documents by
# identifying images embedded or attached to those files.
# If you turn off this option, then some files may no longer be detected.
# Default: yes
#ScanImageFuzzyHash no


##
## Mail files
##

# Enable internal e-mail scanner.
# If you turn off this option, the original files will still be scanned, but
# without parsing individual messages/attachments.
# Default: yes
#ScanMail no

# Scan RFC1341 messages split over many emails.
# You will need to periodically clean up $TemporaryDirectory/clamav-partial
# directory.
# WARNING: This option may open your system to a DoS attack.
#	   Never use it on loaded servers.
# Default: no
#ScanPartialMessages yes

# With this option enabled ClamAV will try to detect phishing attempts by using
# HTML.Phishing and Email.Phishing NDB signatures.
# Default: yes
#PhishingSignatures no

# With this option enabled ClamAV will try to detect phishing attempts by
# analyzing URLs found in emails using WDB and PDB signature databases.
# Default: yes
#PhishingScanURLs no


##
## Data Loss Prevention (DLP)
##

# Enable the DLP module
# Default: No
#StructuredDataDetection yes

# This option sets the lowest number of Credit Card numbers found in a file
# to generate a detect.
# Default: 3
#StructuredMinCreditCardCount 5

# With this option enabled the DLP module will search for valid Credit Card
# numbers only. Debit and Private Label cards will not be searched.
# Default: no
#StructuredCCOnly yes

# This option sets the lowest number of Social Security Numbers found
# in a file to generate a detect.
# Default: 3
#StructuredMinSSNCount 5

# With this option enabled the DLP module will search for valid
# SSNs formatted as xxx-yy-zzzz
# Default: yes
#StructuredSSNFormatNormal no

# With this option enabled the DLP module will search for valid
# SSNs formatted as xxxyyzzzz
# Default: no
#StructuredSSNFormatStripped yes


##
## HTML
##

# Perform HTML normalisation and decryption of MS Script Encoder code.
# Default: yes
# If you turn off this option, the original files will still be scanned, but
# without additional processing.
#ScanHTML no


##
## Archives
##

# ClamAV can scan within archives and compressed files.
# If you turn off this option, the original files will still be scanned, but
# without unpacking and additional processing.
# Default: yes
#ScanArchive no


##
## Limits
##

# The options below protect your system against Denial of Service attacks
# using archive bombs.

# This option sets the maximum amount of time to a scan may take.
# In this version, this field only affects the scan time of ZIP archives.
# Value of 0 disables the limit.
# Note: disabling this limit or setting it too high may result allow scanning
# of certain files to lock up the scanning process/threads resulting in a
# Denial of Service.
# Time is in milliseconds.
# Default: 120000
#MaxScanTime 300000

# This option sets the maximum amount of data to be scanned for each input
# file. Archives and other containers are recursively extracted and scanned
# up to this value.
# Value of 0 disables the limit
# Note: disabling this limit or setting it too high may result in severe damage
# to the system.
# Default: 400M
#MaxScanSize 1000M

# Files larger than this limit won't be scanned. Affects the input file itself
# as well as files contained inside it (when the input file is an archive, a
# document or some other kind of container).
# Value of 0 disables the limit.
# Note: disabling this limit or setting it too high may result in severe damage
# to the system.
# Technical design limitations prevent ClamAV from scanning files greater than
# 2 GB at this time.
# Default: 100M
#MaxFileSize 400M

# Nested archives are scanned recursively, e.g. if a Zip archive contains a RAR
# file, all files within it will also be scanned. This options specifies how
# deeply the process should be continued.
# Note: setting this limit too high may result in severe damage to the system.
# Default: 17
#MaxRecursion 10

# Number of files to be scanned within an archive, a document, or any other
# container file.
# Value of 0 disables the limit.
# Note: disabling this limit or setting it too high may result in severe damage
# to the system.
# Default: 10000
#MaxFiles 15000

# Maximum size of a file to check for embedded PE. Files larger than this value
# will skip the additional analysis step.
# Note: disabling this limit or setting it too high may result in severe damage
# to the system.
# Default: 40M
#MaxEmbeddedPE 100M

# Maximum size of a HTML file to normalize. HTML files larger than this value
# will not be normalized or scanned.
# Note: disabling this limit or setting it too high may result in severe damage
# to the system.
# Default: 40M
#MaxHTMLNormalize 100M

# Maximum size of a normalized HTML file to scan. HTML files larger than this
# value after normalization will not be scanned.
# Note: disabling this limit or setting it too high may result in severe damage
# to the system.
# Default: 8M
#MaxHTMLNoTags 16M

# Maximum size of a script file to normalize. Script content larger than this
# value will not be normalized or scanned.
# Note: disabling this limit or setting it too high may result in severe damage
# to the system.
# Default: 20M
#MaxScriptNormalize 50M

# Maximum size of a ZIP file to reanalyze type recognition. ZIP files larger
# than this value will skip the step to potentially reanalyze as PE.
# Note: disabling this limit or setting it too high may result in severe damage
# to the system.
# Default: 1M
#MaxZipTypeRcg 1M

# This option sets the maximum number of partitions of a raw disk image to be
# scanned.
# Raw disk images with more partitions than this value will have up to
# the value number partitions scanned. Negative values are not allowed.
# Note: setting this limit too high may result in severe damage or impact
# performance.
# Default: 50
#MaxPartitions 128

# This option sets the maximum number of icons within a PE to be scanned.
# PE files with more icons than this value will have up to the value number
# icons scanned.
# Negative values are not allowed.
# WARNING: setting this limit too high may result in severe damage or impact
# performance.
# Default: 100
#MaxIconsPE 200

# This option sets the maximum recursive calls for HWP3 parsing during
# scanning. HWP3 files using more than this limit will be terminated and
# alert the user.
# Scans will be unable to scan any HWP3 attachments if the recursive limit
# is reached.
# Negative values are not allowed.
# WARNING: setting this limit too high may result in severe damage or impact
# performance.
# Default: 16
#MaxRecHWP3 16

# This option sets the maximum calls to the PCRE match function during
# an instance of regex matching.
# Instances using more than this limit will be terminated and alert the user
# but the scan will continue.
# For more information on match_limit, see the PCRE documentation.
# Negative values are not allowed.
# WARNING: setting this limit too high may severely impact performance.
# Default: 100000
#PCREMatchLimit 20000

# This option sets the maximum recursive calls to the PCRE match function
# during an instance of regex matching.
# Instances using more than this limit will be terminated and alert the user
# but the scan will continue.
# For more information on match_limit_recursion, see the PCRE documentation.
# Negative values are not allowed and values > PCREMatchLimit are superfluous.
# WARNING: setting this limit too high may severely impact performance.
# Default: 2000
#PCRERecMatchLimit 10000

# This option sets the maximum filesize for which PCRE subsigs will be
# executed. Files exceeding this limit will not have PCRE subsigs executed
# unless a subsig is encompassed to a smaller buffer.
# Negative values are not allowed.
# Setting this value to zero disables the limit.
# WARNING: setting this limit too high or disabling it may severely impact
# performance.
# Default: 100M
#PCREMaxFileSize 400M

# When AlertExceedsMax is set, files exceeding the MaxFileSize, MaxScanSize, or
# MaxRecursion limit will be flagged with the virus name starting with
# "Heuristics.Limits.Exceeded".
# Default: no
#AlertExceedsMax yes

##
## On-access Scan Settings
##

# Don't scan files larger than OnAccessMaxFileSize
# Value of 0 disables the limit.
# Default: 5M
#OnAccessMaxFileSize 10M

# Max number of scanning threads to allocate to the OnAccess thread pool at
# startup. These threads are the ones responsible for creating a connection
# with the daemon and kicking off scanning after an event has been processed.
# To prevent clamonacc from consuming all clamd's resources keep this lower
# than clamd's max threads.
# Default: 5
#OnAccessMaxThreads 10

# Max amount of time (in milliseconds) that the OnAccess client should spend
# for every connect, send, and receive attempt when communicating with clamd
# via curl.
# Default: 5000 (5 seconds)
# OnAccessCurlTimeout 10000

# Toggles dynamic directory determination. Allows for recursively watching
# include paths.
# Default: no
#OnAccessDisableDDD yes

# Set the include paths (all files inside them will be scanned). You can have
# multiple OnAccessIncludePath directives but each directory must be added
# in a separate line.
# Default: disabled
OnAccessIncludePath /home
#OnAccessIncludePath /students

# Set the exclude paths. All subdirectories are also excluded.
# Default: disabled
#OnAccessExcludePath /home/user

# Modifies fanotify blocking behaviour when handling permission events.
# If off, fanotify will only notify if the file scanned is a virus,
# and not perform any blocking.
# Default: no
OnAccessPrevention no

# When using prevention, if this option is turned on, any errors that occur
# during scanning will result in the event attempt being denied. This could
# potentially lead to unwanted system behaviour with certain configurations,
# so the client defaults this to off and prefers allowing access events in
# case of scan or connection error.
# Default: no
#OnAccessDenyOnError yes

# Toggles extra scanning and notifications when a file or directory is
# created or moved.
# Requires the  DDD system to kick-off extra scans.
# Default: no
OnAccessExtraScanning yes

# Set the  mount point to be scanned. The mount point specified, or the mount
# point containing the specified directory will be watched. If any directories
# are specified, this option will preempt (disable and ignore all options
# related to) the DDD system. This option will result in verdicts only.
# Note that prevention is explicitly disallowed to prevent common, fatal
# misconfigurations. (e.g. watching "/" with prevention on and no exclusions
# made on vital system directories)
# It can be used multiple times.
# Default: disabled
OnAccessMountPath /
#OnAccessMountPath /home/user

# With this option you can exclude the root UID (0). Processes run under
# root with be able to access all files without triggering scans or
# permission denied events.
# Note that if clamd cannot check the uid of the process that generated an
# on-access scan event (e.g., because OnAccessPrevention was not enabled, and
# the process already exited), clamd will perform a scan.  Thus, setting
# OnAccessExcludeRootUID is not *guaranteed* to prevent every access by the
# root user from triggering a scan (unless OnAccessPrevention is enabled).
# Default: no
#OnAccessExcludeRootUID no

# With this option you can exclude specific UIDs. Processes with these UIDs
# will be able to access all files without triggering scans or permission
# denied events.
# This option can be used multiple times (one per line).
# Using a value of 0 on any line will disable this option entirely.
# To exclude the root UID (0) please enable the OnAccessExcludeRootUID
# option.
# Also note that if clamd cannot check the uid of the process that generated an
# on-access scan event (e.g., because OnAccessPrevention was not enabled, and
# the process already exited), clamd will perform a scan.  Thus, setting
# OnAccessExcludeUID is not *guaranteed* to prevent every access by the
# specified uid from triggering a scan (unless OnAccessPrevention is enabled).
# Default: disabled
#OnAccessExcludeUID -1

# This option allows exclusions via user names when using the on-access
# scanning client. It can be used multiple times.
# It has the same potential race condition limitations of the
# OnAccessExcludeUID option.
# Default: disabled
OnAccessExcludeUname clamav

# Number of times the OnAccess client will retry a failed scan due to
# connection problems (or other issues).
# Default: 0
#OnAccessRetryAttempts 3

##
## Bytecode
##

# With this option enabled ClamAV will load bytecode from the database.
# It is highly recommended you keep this option on, otherwise you'll miss
# detections for many new viruses.
# Default: yes
#Bytecode no

# Set bytecode security level.
# Possible values:
#   None -      No security at all, meant for debugging.
#               DO NOT USE THIS ON PRODUCTION SYSTEMS.
#               This value is only available if clamav was built
#               with --enable-debug!
#   TrustSigned - Trust bytecode loaded from signed .c[lv]d files, insert
#               runtime safety checks for bytecode loaded from other sources.
#   Paranoid -  Don't trust any bytecode, insert runtime checks for all.
# Recommended: TrustSigned, because bytecode in .cvd files already has these
# checks.
# Note that by default only signed bytecode is loaded, currently you can only
# load unsigned bytecode in --enable-debug mode.
#
# Default: TrustSigned
#BytecodeSecurity TrustSigned

# Allow loading bytecode from outside digitally signed .c[lv]d files.
# **Caution**: You should NEVER run bytecode signatures from untrusted sources.
# Doing so may result in arbitrary code execution.
# Default: no
#BytecodeUnsigned yes

# Set bytecode timeout in milliseconds.
#
# Default: 10000
# bytecodetimeout 1000
VirusEvent /etc/clamav/virus-event.bash
```

- Create the file: `/etc/sudoers.d/clamav` and add this line

```
clamav ALL=(ALL) NOPASSWD: SETENV: /usr/bin/notify-send

```

- Create the file if it does not exists `/etc/clamav/virus-event.bash` and write 

```bash 
#!/bin/bash
PATH=/usr/bin
ALERT="Signature detected by clamav: $CLAM_VIRUSEVENT_VIRUSNAME in $CLAM_VIRUSEVENT_FILENAME"

# Send an alert to all graphical users.
for ADDRESS in /run/user/*; do
    USERID=${ADDRESS#/run/user/}
    /usr/bin/sudo -u "#$USERID" DBUS_SESSION_BUS_ADDRESS="unix:path=$ADDRESS/bus" PATH=${PATH} \
        /usr/bin/notify-send -u critical -i dialog-warning "Virus found!" "$ALERT"
done
```

- Finally edit the `clamav-clamonacc.service` by writting in the section 
for edits. Run `sudo systemctl edit clamav-clamonacc.service` to edit

```conf
[Service]
ExecStart=
ExecStart=/usr/sbin/clamonacc -F --fdpass --log=/var/log/clamav/clamonacc.log
```

Now restart the `clamav-clamonacc.service` using `systemctl`.


- Update database: `freshclam`
 
 ---

## Audio 

- `systemctl --user enable --now pipewire pipewire-pulse wireplumber`

---

## Set pdf viewer 

- `xdg-mime default org.pwmt.zathura.desktop application/pdf`

--- 

## Docker 

- `sudo systemctl enable docker.service`

---

## Second Hardrive 

Use the same procedure like when during the installation consisting of: 

- Identifying
- Paritioning
- Formating 
- Mounting 

The difference is that this time we want to add it to `fstab` to mount automatically when booting

- Get the UUID with `lsblk -f`
- Open and edit the `/etc/fstab` and add the line `UUID=id /mnt/... file_system_type permisions(defaults) dump_option (0)  policy_option (0)`


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

