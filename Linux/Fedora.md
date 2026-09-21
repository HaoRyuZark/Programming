# Fedora Linux Setup
--- 

## Installation 

Boot from your USB and follow the installation wizard. 

---  

## Post Install Fedora 

-*Fedora** has a GUI for the installation in which you can chose the defaults for the installation so it is way less complicated than 
Arch. Chose what makes sense for the machine. And then turn of the computer while also removing the USB-stick to reboot from fedora.

> Be sure to allow third-party repositories in the installation step, else you will need to do it manually.

> TODO: I need to check if git is already pre-installed on fedora.

### System Update And Reboot

Run `sudo dnf update` to then reboot again. 

### Set-Up SSH

Follow the instructions in [SHH](./SHH_Setup.md).

### Set up Scripts 

After having a proper shh and git setup proceed to clone the repository `dotfiles` inside your home folder.

Then run: 

```bash 
stow --adopt .
```

This will setup the necessary folders for the different configurations.

Inside this folder there are scripts which can be used for the set-up of GNOME and the installation of the necessary 
packages.

```bash 
bash set_up.sh
```

This will prompt you for your password and also install all of the necessary packages for development.

> Note that `set_up.sh` wil do a lot of the heavy lifting which comes in the following steps. I 
> recommend at least reading the next steps to know what is happening under the hood.

### restore.sh

This script is made to set-up the both the GNOME-settings and the work-spaces. Of the projects.

---  

## Install the Packages by copying the following command:

- `sudo pacman -S texlive fastetch 7zip make kitty neovim python pip stow npm python 
   wl-clippboard wofi xorg-wayland luarocks linux-lts lua wayland 
   nodejs waybar rust jdk-open-jdk htop man-db man-pages openssh git yazi vi zathura zathura-pdf-poppler
   julia noto-fonts noto-fonts-emoji noto-fonts-cjk ttf-linux-libertine wget ruby composer php
   xdotool biber wget pipewire pipewire-alsa pipewire-pulse wireplumber pavucontrol lm_sensors btop
   clamav sxiv bleachbit reflector jupyterlab jupyter-notebook python-numpy python-pandas python-matplotlib python-pygame
   tk nm-connection-editor iwd modemmanager usb_modeswitch timeshift tmux otf-font-awesome
   fzf bat lsd tldr lazygit swayidle thunar autotiling starship python-scikit-learn docker pyright
   lua-language-server bash-language-server texlab postgresql clang pacman-contrib ghc cabal-install
   julia nm-connection-editor wine utftex xdotool w3m w3m-img conda kubernetes polkit go composer pkgconf openssl imv swayimg 
   lxqt-policykit nm-applet postgresql seahorse swaync`

-*Packet plus purpose:**

- texlive
- fastetch 
- 7zip
- make
- kitty 
- neovim 
- python 
- pip 
- stow 
- npm 
- python   
- wl-clippboard 
- wofi 
- xorg-wayland 
- luarocks 
- linux-lts 
- lua 
- wayland 
- nodejs 
- waybar 
- rust 
- jdk-open-jdk 
- htop 
- man-db 
- man-pages 
- openssh 
- git 
- yazi 
- vi 
- zathura 
- zathura-pdf-poppler
- julia 
- noto-fonts
- noto-fonts-emoji 
- noto-fonts-cjk 
- ttf-linux-libertine 
- wget 
- ruby 
- composer 
- php
- xdotool 
- biber
- pipewire 
- pipewire-alsa 
- pipewire-pulse 
- wireplumber 
- pavucontrol 
- lm_sensors 
- btop
- clamav 
- sxiv 
- bleachbit 
- reflector 
- jupyterlab 
- jupyter-notebook 
- python-numpy 
- python-pandas 
- python-matplotlib 
- python-pygame
- tk 
- nm-connection-editor 
- iwd 
- modemmanager 
- usb_modeswitch 
- timeshift 
- tmux 
- otf-font-awesome
- fzf 
- bat 
- lsd 
- tldr 
- lazygit 
- swayidle 
- thunar 
- autotiling 
- starship 
- python-scikit-learn 
- docker pyright
- lua-language-server 
- bash-language-server 
- texlab 
- postgresql 
- clang 
- pacman-contrib 
- ghc 
- cabal-install
- julia 
- nm-connection-editor 
- wine
- utftex
- xdotool
- w3m w3m-img
- conda
- kubernetes
- polkit
- `go`: GoLang with its tool-chain.
- composer
- pkgconf openssl
- imv
- `swayimg`: lightweight image viewer 
- `lxqt-policykit`: polkit 
- `nm-applet`: password prompt for wifi.
- `seahorse`:
- `swaync`: notification daemon for sway
 

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

#### Stow Functionality

- **First Setup**: `stow -D */` to remove the stow links and `stow */` to create the stow links.

- **Adding files to stow and updating**:

  1. To add files to stow use create a mirror of the original struture from the home directory to that file. 

  2. Copy the file or directory to stow 

  3. Run `stow --adopt .` inside the dotfiles directory
 
--- 

## Autotiling

Inside the `dotfiles/script` you will find the autotiling script with which you will do the following: 

```bash 
chmod +x $HOME/dotfiles/scripts/autotiling

sudo cp $HOME/dotfiles/scripts/autotiling /usr/bin/
```

with this you have a working autotiling functionality for sway.

--- 

## Random Wallpapers 

To activate the script to swtich between wallpapers run: 

```bash 
chmod +x $HOME/dotfiles/scripts/random-wallpaper.sh
```

> If you put your wallpapers in another location, you will need to edit the script.

--- 

## dnf Packet Manager

`dnf` is Fedora's primary package manager. It manages packages from configured RPM repositories and handles dependency resolution, installation, 
removal, updates, and repository management.

- `dnf [global-options] <command> [arguments]`

  - **Function**: Manages RPM packages and software repositories on Fedora and other RPM-based distributions.
  - **Common Commands**:

    - `install`: Install one or more packages.
    - `remove`: Remove one or more packages.
    - `upgrade`: Upgrade installed packages.
    - `update`: Alias for `upgrade` on modern DNF versions.
    - `search`: Search package names and descriptions.
    - `info`: Display detailed package information.
    - `list`: List installed, available, or all packages.
    - `provides`: Find which package provides a particular file or capability.
    - `reinstall`: Reinstall an already installed package.
    - `downgrade`: Downgrade a package to an older available version.
    - `autoremove`: Remove packages that were installed as dependencies but are no longer required.
    - `history`: Display and manage package transactions.
    - `clean`: Remove cached package and repository data.
    - `check`: Check for dependency problems.
    - `repoquery`: Query packages from enabled repositories.
  - **Example Usage**: `sudo dnf install vim`

- `dnf install [flags] <package>...`

  - **Function**: Installs one or more packages and their required dependencies.
  - **Flags**:

    - `-y`: Automatically answer yes to confirmation prompts.
    - `--allowerasing`: Allow DNF to remove installed packages to resolve dependency conflicts.
    - `--best`: Attempt to install the highest available package version.
    - `--no-best`: Allow installation of an older version if the newest version cannot be installed.
    - `--downloadonly`: Download packages without installing them.
  - **Parameters**:

    - `<package>` *(required)*: Name, version, or package specification to install.
  - **Example Usage**:

    - `sudo dnf install firefox`
    - `sudo dnf install gcc gcc-c++ make`
    - `sudo dnf install --downloadonly kernel`

- `dnf remove [flags] <package>...`

  - **Function**: Removes installed packages and dependencies that are no longer required.
  - **Flags**:

    - `-y`: Automatically confirm the removal.
    - `--noautoremove`: Do not automatically remove dependencies that are no longer required.
  - **Parameters**:

    - `<package>` *(required)*: Package to remove.
  - **Example Usage**: `sudo dnf remove firefox`

- `dnf upgrade [flags] [package]...`

  - **Function**: Updates installed packages to newer available versions.
  - **Flags**:

    - `-y`: Automatically confirm the upgrade.
    - `--refresh`: Refresh repository metadata before checking for updates.
    - `--exclude=<package>`: Exclude a package from the transaction.
  - **Parameters**:

    - `[package]` *(optional)*: Specific package to upgrade. If omitted, all installed packages are considered.
  - **Example Usage**:

    - `sudo dnf upgrade`
    - `sudo dnf upgrade --refresh`
    - `sudo dnf upgrade firefox`

- `dnf update`

  - **Function**: Updates installed packages. On modern DNF versions, this is effectively an alias for `dnf upgrade`.
  - **Example Usage**: `sudo dnf update`

- `dnf search <term>`

  - **Function**: Searches enabled repositories for packages matching a name or description.
  - **Parameters**:

    - `<term>` *(required)*: Search term.
  - **Example Usage**: `dnf search text editor`

- `dnf info <package>`

  - **Function**: Displays detailed information about a package.
  - **Parameters**:

    - `<package>` *(required)*: Package name.
  - **Example Usage**: `dnf info neovim`

- `dnf list [flags] [package]`

  - **Function**: Lists installed and available packages.
  - **Flags**:

    - `--installed`: Show installed packages.
    - `--available`: Show packages available for installation.
    - `--updates`: Show packages with available updates.
    - `--all`: Show both installed and available packages.
  - **Example Usage**:

    - `dnf list --installed`
    - `dnf list --updates`
    - `dnf list --installed neovim`

- `dnf provides <path-or-capability>`

  - **Function**: Determines which package provides a particular file or capability.
  - **Parameters**:

    - `<path-or-capability>` *(required)*: File path, command, library, or capability to search for.
  - **Example Usage**:

    - `dnf provides /usr/bin/nvim`
    - `dnf provides '*/libssl.so*'`

- `dnf reinstall <package>`

  - **Function**: Reinstalls an installed package, replacing its files with fresh copies.
  - **Parameters**:

    - `<package>` *(required)*: Package to reinstall.
  - **Example Usage**: `sudo dnf reinstall bash`

- `dnf downgrade <package>`

  - **Function**: Attempts to install an older available version of a package.
  - **Parameters**:

    - `<package>` *(required)*: Package to downgrade.
  - **Example Usage**: `sudo dnf downgrade firefox`

- `dnf autoremove`

  - **Function**: Removes packages installed as dependencies that are no longer needed.
  - **Example Usage**: `sudo dnf autoremove`

- `dnf history [command]`

  - **Function**: Displays previous package transactions and can be used to inspect or undo transactions.
  - **Commands**:

    - `list`: List previous transactions.
    - `info <id>`: Show details about a transaction.
    - `undo <id>`: Attempt to reverse a transaction.
    - `redo <id>`: Repeat a previous transaction.
  - **Example Usage**:

    - `sudo dnf history`
    - `sudo dnf history info 15`
    - `sudo dnf history undo 15`

- `dnf clean <command>`

  - **Function**: Removes cached repository metadata and downloaded package data.
  - **Commands**:

    - `packages`: Remove cached packages.
    - `metadata`: Remove cached repository metadata.
    - `all`: Remove all cached data.
  - **Example Usage**: `sudo dnf clean all`

- `dnf check`

  - **Function**: Checks the local package database for dependency problems.
  - **Example Usage**: `sudo dnf check`

- `dnf repolist [flags]`

  - **Function**: Displays configured software repositories.
  - **Flags**:

    - `--enabled`: Show enabled repositories.
    - `--disabled`: Show disabled repositories.
    - `--all`: Show enabled and disabled repositories.
  - **Example Usage**:

    - `dnf repolist`
    - `dnf repolist --all`

- `dnf config-manager`

  - **Function**: Manages DNF repository configuration. Availability and syntax can depend on the installed DNF version and Fedora tooling.
  - **Common Operations**:

    - Enable a repository.
    - Disable a repository.
    - Add or modify repository configuration.
  - **Example Usage**: `sudo dnf config-manager --set-enabled <repository>`

--- 

## Flatpak

`flatpak` is a package-management and application-distribution system primarily designed for desktop applications. Unlike DNF, Flatpak applications run inside 
a sandbox and generally use their own runtime and dependency environment.

- `flatpak [global-options] <command> [arguments]`

  - **Function**: Manages Flatpak applications, runtimes, repositories, permissions, and updates.
  - **Common Commands**:

    - `install`: Install an application or runtime.
    - `uninstall`: Remove an application or runtime.
    - `update`: Update installed applications and runtimes.
    - `search`: Search configured remotes.
    - `list`: List installed applications and runtimes.
    - `info`: Display application or runtime information.
    - `run`: Launch an application.
    - `remote-list`: List configured repositories.
    - `remote-add`: Add a repository.
    - `remote-delete`: Remove a repository.
    - `override`: Modify sandbox permissions.
    - `repair`: Repair the local Flatpak installation.
  - **Example Usage**: `flatpak search firefox`

- `flatpak search <term>`

  - **Function**: Searches configured Flatpak repositories for applications and runtimes.
  - **Parameters**:

    - `<term>` *(required)*: Search term.
  - **Example Usage**: `flatpak search firefox`

- `flatpak install [flags] <remote> <application>`

  - **Function**: Installs a Flatpak application or runtime.
  - **Flags**:

    - `-u`: Install for the current user rather than system-wide.
    - `--user`: Explicitly install for the current user.
    - `-y`: Automatically confirm installation.
  - **Parameters**:

    - `<remote>`: Flatpak repository from which the package should be installed.
    - `<application>`: Application or runtime ID.
  - **Example Usage**:

    - `flatpak install flathub org.mozilla.firefox`
    - `flatpak install --user flathub org.mozilla.firefox`

- `flatpak uninstall [flags] <application>`

  - **Function**: Removes a Flatpak application or runtime.
  - **Flags**:

    - `--user`: Operate on the per-user installation.
    - `--delete-data`: Remove the application's user data as well.
    - `--unused`: Remove unused runtimes and extensions.
  - **Parameters**:

    - `<application>` *(required)*: Application ID.
  - **Example Usage**:

    - `flatpak uninstall org.mozilla.firefox`
    - `flatpak uninstall --delete-data org.mozilla.firefox`
    - `flatpak uninstall --unused`

- `flatpak update [application]`

  - **Function**: Updates installed Flatpak applications and runtimes.
  - **Parameters**:

    - `[application]` *(optional)*: Specific application to update.
  - **Example Usage**:

    - `flatpak update`
    - `flatpak update org.mozilla.firefox`

- `flatpak list [flags]`

  - **Function**: Lists installed Flatpak applications and runtimes.
  - **Flags**:

    - `--app`: Show applications only.
    - `--runtime`: Show runtimes only.
    - `--user`: Show user-installed objects.
    - `--system`: Show system-installed objects.
  - **Example Usage**:

    - `flatpak list`
    - `flatpak list --app`
    - `flatpak list --runtime`

- `flatpak info <application>`

  - **Function**: Displays detailed information about an installed application or runtime.
  - **Parameters**:

    - `<application>` *(required)*: Application ID.
  - **Example Usage**: `flatpak info org.mozilla.firefox`

- `flatpak run <application>`

  - **Function**: Launches a Flatpak application.
  - **Parameters**:

    - `<application>` *(required)*: Application ID.
  - **Example Usage**: `flatpak run org.mozilla.firefox`

- `flatpak remote-list`

  - **Function**: Lists configured Flatpak repositories (remotes).
  - **Example Usage**: `flatpak remote-list`

- `flatpak remote-add [flags] <name> <url>`

  - **Function**: Adds a Flatpak repository.
  - **Flags**:

    - `--if-not-exists`: Do nothing if the remote already exists.
    - `--user`: Add the remote for the current user only.
  - **Parameters**:

    - `<name>`: Local name assigned to the remote.
    - `<url>`: Repository URL or `.flatpakrepo` source.
  - **Example Usage**: `flatpak remote-add --if-not-exists flathub <repository-url>`

- `flatpak override [flags] <application>`

  - **Function**: Changes the sandbox permissions granted to an application.
  - **Common Options**:

    - `--filesystem=<path>`: Grant access to a filesystem location.
    - `--device=<device>`: Grant access to a device.
    - `--share=<type>`: Grant access to a shared resource such as network or IPC.
    - `--socket=<type>`: Grant access to a specific socket.
    - `--show`: Display current overrides.
    - `--reset`: Reset overrides to their defaults.
  - **Example Usage**:

    - `flatpak override --show org.mozilla.firefox`
    - `flatpak override --filesystem=home org.mozilla.firefox`

- `flatpak repair [flags]`

  - **Function**: Repairs the local Flatpak installation by checking and fixing invalid or incomplete objects.
  - **Flags**:

    - `--user`: Repair the per-user installation.
    - `--system`: Repair the system installation.
  - **Example Usage**: `sudo flatpak repair`

--- 

## Maintenance 

- **Remove orphan packages**: `sudo dnf autoremove`.

- **Remove unnecessary files**: Use `Bleachbit`. 

- **Update system**: `sudo dnf upgrade --refresh`. 

- **Check for services failung**: `sudo systenctk --failed`.

- **Check for errors in the log-files**: `sudo journalctl -p 3 -xb`.

- **Delete Old Logs**: `sudo journalctl --vacum-time=2weeks`.

- **Clean the cache**: `sudo dnf clean all`.

- **Uninstall unused flatpak-packages**`flatpak uninstall --unsused`.

- **Upgrade the system**: run: 

```bash 
dnf system-upgrade # to check 

sudo dnf system-upgrade download --refresh --releasever=X # to perform the update

sudo dnf system-upgrade reboot # to reboot into the upgraded system
```
 
--- 

