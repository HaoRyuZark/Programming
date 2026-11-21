# Fedora Set-Up

Installation and set-up guide for **Fedora Linux**. The package list and structure mirror the [Arch guide](./Arch.md), translated to
`dnf` and Fedora package names.

---

## Choosing an Edition

Fedora ships several images. For a developer machine running a tiling WM (sway), the default **Workstation** is not the best option:
it comes with a full GNOME desktop and many apps you will replace anyway.

| Image                         | What you get                                                        | Good for                                              |
| ----------------------------- | ------------------------------------------------------------------- | ----------------------------------------------------- |
| **Workstation**               | GNOME plus a curated app set, graphical installer, works right away | People who want GNOME and nothing to configure         |
| **Everything (netinstall)**   | Small ISO that downloads exactly the package set you pick           | Developers: pick sway, KDE, or a bare system plus dev groups |
| **Minimal (via Everything)**  | Bare system: kernel, systemd, dnf, NetworkManager, no GUI           | The "Arch way": build the system up package by package |
| **Sway Spin**                 | Pre-configured sway desktop                                         | A ready sway system without the netinstall step        |

What these images share:

- **Filesystem:** btrfs with `zstd` compression and the subvolumes `root` and `home` (**not** `@`/`@home`, see [Timeshift](#timeshift-and-snapshots)).
- **Swap:** `zram` (compressed swap in RAM), so no swap partition is needed.
- **Firewall:** `firewalld` is enabled by default.
- **Audio:** PipeWire is the default.
- **Microcode:** installed automatically (`microcode_ctl`, `amd-ucode-firmware`), nothing to do.
- **Bootloader:** GRUB with BLS entries. Kernels add their own boot entries, so you **never** need `grub-mkconfig` after a kernel update.

My recommendation: **Everything** with the *Sway Desktop* or *Custom Operating System* plus development groups. Use **Minimal** if you want
full control the way Arch gives it.

---

## Creating the USB

1. Download the ISO:
   - Workstation: [fedoraproject.org/workstation](https://fedoraproject.org/workstation/download)
   - Everything netinstall: [fedoraproject.org/misc](https://fedoraproject.org/misc/#everything) (section *Everything*)
   - Sway Spin: [fedoraproject.org/spins/sway](https://fedoraproject.org/spins/sway/download)

2. Create a bootable USB drive with `Fedora Media Writer`.

If you are a masochist, then proceed to use the terminal:

  - run `lsblk` to identify the name of the USB-device.
  - `sudo dd bs=4M if=~/Downloads/Fedora-XXX.iso of=/dev/your_device_name status=progress oflag=sync`

3. Boot from the USB drive. Make sure you pick the **UEFI** entry of the USB drive in your firmware.

---

## Installation: Fedora Workstation

Boot from your USB, choose *Install to Hard Drive* and follow the wizard. The defaults are good: btrfs, automatic partitioning, zram.

> Enable **third-party repositories** in the setup step after the first boot (it enables Flathub, Google Chrome, NVIDIA, Steam).
> Otherwise you must enable Flathub and RPM Fusion yourself, see [Third-party Repositories](#third-party-repositories).

Then continue with [Post Install](#post-install).

---

## Installation: Fedora Everything (recommended for developers)

The **Everything** netinstall ISO is small (~800 MB) and downloads packages during installation, so you need internet access
(ethernet is easiest; Wi-Fi can be configured in the *Network & Host Name* screen).

The installer (Anaconda) has a hub with several screens. Go through them in this order:

1. **Keyboard / Language Support:** add `German (de-latin1)` if you do not use a US keyboard.

2. **Time & Date:** pick `Europe/Berlin`, enable *Network Time*.

3. **Network & Host Name:** turn on your connection and set an epic host name, e.g. `Father`.

4. **Installation Destination:** select the disk.
   - *Automatic* gives you the Fedora defaults (EFI partition, `/boot`, btrfs with `root`/`home` subvolumes, zram). This is fine.
   - *Custom* (or *Advanced Custom / Blivet-GUI*) if you want your own layout, e.g. `@`/`@home` subvolumes for Timeshift's btrfs mode:
     - `/boot/efi` 1 GiB, EFI System Partition
     - `/boot` 1 GiB, ext4
     - btrfs volume for the rest with subvolumes `@` mounted at `/` and `@home` mounted at `/home`
   - Check *Encrypt my data* for LUKS disk encryption (recommended on laptops).

5. **Software Selection:** this is the important screen. Pick a **Base Environment** on the left and **Additional software** on the right:

   | Base Environment                    | Use it for                                              |
   | ----------------------------------- | ------------------------------------------------------- |
   | **Sway Desktop**                    | Ready sway setup (sway, waybar, foot, sddm, ...)        |
   | **Fedora Custom Operating System**  | Bare base system (this is the [Minimal](#installation-fedora-minimal) path) |
   | KDE Plasma Workspaces / Xfce / i3   | Other desktops                                          |
   | Development and Creative Workstation | Workstation with extra dev and creative tools           |

   Useful **add-ons** for development:

   - `Development Tools`: git, make, patch, diff tools (similar to Arch's `base-devel`)
   - `C Development Tools and Libraries`: gcc, g++, gdb, autotools
   - `Container Management`: podman, buildah, skopeo
   - `RPM Development Tools`: only if you want to build RPMs

6. **Root Account:** leave root **disabled** (recommended) and use sudo.

7. **User Creation:** create your user (`migu`) and check *Make this user administrator* (adds it to the `wheel` group, so
   `sudo` works right away; no `visudo` needed).

8. **Begin Installation**, then reboot and remove the USB drive.

If you picked the *Sway Desktop*, log in through `sddm` and choose the sway session. Then continue with [Post Install](#post-install).

---

## Installation: Fedora Minimal

There is no separate x86_64 "Minimal" ISO: a minimal Fedora is the **Everything** ISO with the
**Fedora Custom Operating System** base environment (older releases called it *Minimal Install*) and **no** add-ons.
You end up on a TTY with a bare system, the same starting point as Arch after the first reboot, but with a working
bootloader, users, locale and network already configured by the installer.

> For VMs and ARM boards Fedora also offers raw `Minimal` disk images on [fedoraproject.org/misc](https://fedoraproject.org/misc/).

### Steps

1. Follow the [Everything installation](#installation-fedora-everything-recommended-for-developers) steps and pick
**Fedora Custom Operating System** in *Software Selection* without any add-ons.

2. Reboot and log in on the TTY.

3. **Connect to the internet** (only needed if not configured in the installer). On a laptop make sure Wi-Fi support is installed:

  - `sudo dnf install NetworkManager-wifi NetworkManager-tui` (if the Wi-Fi card is not listed at all, connect ethernet first)
  - `nmcli device wifi list`
  - `nmcli device wifi connect SSID_or_BSSID password password`
  - or use the TUI: `nmtui`

Verify the connection with `ping fedoraproject.org`.

4. **Update:** `sudo dnf upgrade --refresh`

5. **Install a graphical session.** Two options:

  - **Full sway environment** (sddm, waybar, foot, swaylock, ...):

    ```bash
    sudo dnf install @sway-desktop-environment
    ```

  - **Hand-picked** (closest to the Arch guide, uses `ly` like on Arch):

    ```bash
    sudo dnf install sway foot ly swaylock swayidle waybar wofi xorg-x11-server-Xwayland \
      polkit lxqt-policykit pipewire pipewire-pulseaudio wireplumber \
      google-noto-sans-fonts google-noto-color-emoji-fonts \
      xdg-desktop-portal-wlr xdg-user-dirs firefox
    sudo systemctl enable ly@tty2.service
    ```

6. **Boot into the graphical target:**

  - `sudo systemctl set-default graphical.target`
  - `sudo reboot`

7. **Development base** (equivalent of Arch's `base-devel`):

  - `sudo dnf install @development-tools @c-development`

Now continue with [Post Install](#post-install) like on the other editions.

---

## Post Install

### System Update and Reboot

```bash
sudo dnf upgrade --refresh
sudo reboot
```

### Speed up dnf

Edit `/etc/dnf/dnf.conf` with `sudo vim /etc/dnf/dnf.conf` and add under `[main]`:

```ini
max_parallel_downloads=10
```

(`dnf` is `dnf5` since Fedora 41. It already picks fast mirrors by itself, so `fastestmirror` is not needed.)

### Connect to the internet via Wi-Fi

- `nmcli device wifi list`
- `nmcli device wifi connect SSID_or_BSSID password password`
- or the TUI: `nmtui`

### Third-party Repositories

**RPM Fusion** provides codecs, NVIDIA drivers and software Fedora cannot ship:

```bash
sudo dnf install \
  https://mirrors.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm \
  https://mirrors.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm
```

Full multimedia codecs (replaces the patent-free `ffmpeg-free`):

```bash
sudo dnf swap ffmpeg-free ffmpeg --allowerasing
```

**Flathub** (already enabled if you allowed third-party repositories):

```bash
flatpak remote-add --if-not-exists flathub https://dl.flathub.org/repo/flathub.flatpakrepo
```

**COPR** repositories are Fedora's closest equivalent to the AUR: community repositories built on Fedora's infrastructure.
Like the AUR, they are **not** reviewed by Fedora, so only enable projects you trust:

```bash
sudo dnf copr enable atim/starship
sudo dnf copr enable lihaohong/yazi
sudo dnf copr enable atim/lazygit
```

### Set-Up SSH

`openssh` is preinstalled. Follow the instructions in [SSH](./SHH_Setup.md) to create a key and add it to GitHub:

- `ssh-keygen -t ed25519`
- `cat ~/.ssh/id_ed25519.pub`
- `sudo systemctl enable --now sshd.service` **only** if you want to log into this machine remotely.

### Git

Usually preinstalled. If not (Minimal): `sudo dnf install git`.

### Firewall

`firewalld` is enabled by default. See the [Firewall](#firewall) section below.

### Sway on Workstation

If you installed Workstation and want sway next to GNOME:

```bash
sudo dnf install sway foot swaylock swayidle waybar wofi
```

Log out, select *Sway* in the gear menu of GDM and log in.

---

## Install the Packages by copying the following command:

The packages from Fedora's own repos plus the COPRs enabled above (`starship`, `yazi`, `lazygit`). `--skip-unavailable`
keeps the transaction going if a name changes between releases; read the output to see what was skipped.

```bash
sudo dnf install --skip-unavailable \
  @development-tools @c-development \
  texlive-scheme-full biber fastfetch 7zip make kitty neovim vim-minimal \
  python3 python3-pip python3-devel pipx stow nodejs nodejs-npm \
  wl-clipboard wofi xorg-x11-server-Xwayland waybar swayidle swaylock SwayNotificationCenter swayimg imv \
  grim slurp brightnessctl \
  luarocks lua \
  rust cargo rust-analyzer java-latest-openjdk-devel golang gopls ruby ruby-devel php composer \
  clang clang-tools-extra cmake gdb ghc cabal-install julia \
  htop btop man-db man-pages openssh git yazi ripgrep fd-find \
  zathura zathura-pdf-poppler \
  google-noto-sans-fonts google-noto-color-emoji-fonts google-noto-sans-cjk-fonts \
  alerque-libertinus-fonts fontawesome-fonts-all \
  wget2-wget xdotool libnotify \
  pipewire pipewire-pulseaudio pipewire-jack-audio-connection-kit wireplumber pavucontrol \
  lm_sensors clamav clamav-freshclam clamd sxiv bleachbit timeshift cronie \
  jupyterlab python3-notebook python3-numpy python3-pandas python3-matplotlib \
  python3-pygame python3-scikit-learn python3-tkinter python3-neovim tree-sitter-cli \
  nm-connection-editor network-manager-applet NetworkManager-tui NetworkManager-wifi ModemManager usb_modeswitch \
  tmux fzf bat lsd tldr lazygit Thunar starship zoxide \
  xdg-desktop-portal-wlr xdg-desktop-portal-gtk xdg-user-dirs qt5ct qt6ct \
  moby-engine docker-compose podman kubernetes1.37-client nodejs-bash-language-server \
  postgresql-server postgresql-contrib \
  wine w3m w3m-img polkit lxqt-policykit seahorse gnome-keyring pkgconf openssl openssl-devel \
  bluez bluez-tools blueman
```

After the installation finishes, enable the services:

```bash
sudo systemctl enable --now bluetooth.service crond.service
xdg-user-dirs-update
```

Notes:

- Fedora's names differ from Arch (`python3-*` instead of `python-*`, `golang`, `fd-find`, `Thunar`, `SwayNotificationCenter`, ...).
  When in doubt: `dnf search name` or `dnf provides /usr/bin/command`.
- **No `linux-lts`:** Fedora has no LTS kernel package. Instead it keeps the last **3** kernels (`installonly_limit=3` in
  `/etc/dnf/dnf.conf`) and you can boot an older one from the GRUB menu if an update breaks something.
- The cron daemon is called `crond.service` on Fedora (package `cronie`).
- Do **not** install or enable `iwd`: NetworkManager uses `wpa_supplicant` by default and the two would fight over the Wi-Fi card.
- `rust` + `cargo` (from dnf) and `rustup` conflict in `PATH`. This list uses the dnf packages. If you prefer `rustup`, install
  it with `sudo dnf install rustup`, run `rustup-init`, then `rustup component add rust-analyzer`, and drop `rust cargo rust-analyzer`.
- `kubernetes1.37-client` provides `kubectl`. The version is part of the name, check `dnf search kubernetes` for the current one.
- `texlive-scheme-full` is several GB. `texlive-scheme-medium` plus `texlive-collection-latexextra` is a lighter alternative.
- Never install `pulseaudio`: `pipewire-pulseaudio` replaces it.

### Bluetooth

- **bluez**: the Linux bluetooth stack (`bluetooth.service`), provides `bluetoothctl`.
- **bluez-tools**: extra CLI tools (`bt-device`, `bt-adapter`, ...).
- **blueman**: GTK based bluetooth manager.

### Typesetting

- **texlive-scheme-full**: the complete TeX Live distribution (same as Arch's `texlive` group)
- **biber**: bibliography backend for BibLaTeX
- **alerque-libertinus-fonts**: Libertinus serif font, successor to Linux Libertine (TeX Live also ships it for LaTeX)

### Terminal and shell tools

- **fastfetch**: system info display (neofetch replacement)
- **kitty**: GPU-accelerated terminal emulator
- **tmux**: terminal multiplexer
- **starship** (COPR): fast customizable shell prompt
- **fzf**: fuzzy finder
- **bat**: `cat` with syntax highlighting
- **lsd**: modern `ls` with icons and colors
- **zoxide**: smarter `cd` that remembers directories
- **tldr**: simplified command-line examples
- **ripgrep**: fast recursive grep (`rg`)
- **fd-find**: fast `find` alternative (the command is `fd`)
- **htop**: interactive process viewer
- **btop**: fancier resource monitor
- **yazi** (COPR): terminal file manager
- **w3m** / **w3m-img**: text-based web browser with image support
- **7zip**: `7z` archiver
- **stow**: symlink manager for dotfiles

### Editor

- **neovim**: modern Vim
- **vim-minimal**: provides `vi` (normally preinstalled)

### Build and languages

- **@development-tools**: git, make, patch, diff, ... (Fedora's `base-devel`)
- **@c-development**: gcc, g++, gdb, autotools, ...
- **make**: build automation
- **cmake**: build system generator
- **gdb**: GNU debugger
- **pkgconf**: compiler flag lookup for libraries
- **openssl** / **openssl-devel**: TLS and crypto CLI plus headers (needed to build many Rust/Python crates)
- **clang** / **clang-tools-extra**: C/C++ compiler, `clangd` LSP and `clang-format`
- **rust** / **cargo**: Rust compiler and package manager
- **rust-analyzer**: Rust LSP
- **golang**: Go compiler and toolchain
- **gopls**: Go LSP
- **python3**: Python interpreter
- **python3-pip**: Python package installer
- **python3-devel**: Python headers for native extensions
- **pipx**: installs Python CLI tools into isolated environments
- **nodejs**: JavaScript runtime
- **nodejs-npm**: Node package manager
- **lua**: Lua interpreter
- **luarocks**: Lua package manager
- **ruby** / **ruby-devel**: Ruby interpreter and headers (needed for `gem install neovim`)
- **php**: PHP interpreter
- **composer**: PHP dependency manager
- **java-latest-openjdk-devel**: Java development kit
- **ghc**: Haskell compiler
- **cabal-install**: Haskell build and package tool
- **julia**: Julia language for scientific computing
- **python3-tkinter**: Tk GUI toolkit (needed by tkinter and matplotlib)

### Language servers

- **rust-analyzer**: Rust LSP
- **gopls**: Go LSP
- **clangd** (in `clang-tools-extra`): C/C++ LSP
- **nodejs-bash-language-server**: Bash LSP
- **pyright**, **lua-language-server**, **texlab**: not in the Fedora repos, see [Install Extra Packages](#install-extra-packages)

### Data science and Python libraries

- **jupyterlab**: notebook IDE
- **python3-notebook**: classic notebook interface
- **python3-numpy**: numerical arrays
- **python3-pandas**: dataframes
- **python3-matplotlib**: plotting
- **python3-scikit-learn**: machine learning
- **python3-pygame**: 2D game library
- **python3-neovim**: Python provider for neovim (`pynvim`)
- **tree-sitter-cli**: tree-sitter parser generator (used by nvim-treesitter)

### Wayland desktop

- **xorg-x11-server-Xwayland**: runs X11 apps under Wayland
- **wofi**: app launcher
- **waybar**: status bar
- **swayidle**: idle management (lock/suspend timers)
- **swaylock**: screen locker
- **SwayNotificationCenter**: notification daemon and control center (`swaync`)
- **wl-clipboard**: `wl-copy`/`wl-paste` clipboard tools
- **grim** / **slurp**: screenshots (`grim -g "$(slurp)"`)
- **brightnessctl**: screen brightness from the keyboard
- **xdotool**: X11 input automation (only affects XWayland apps)
- **Thunar**: GUI file manager
- **imv**: Wayland image viewer
- **swayimg**: lightweight image viewer
- **sxiv**: X11 image viewer (Fedora has no `nsxiv`; drop it if imv/swayimg are enough)
- **zathura**: minimal document viewer
- **zathura-pdf-poppler**: PDF backend for zathura
- **xdg-desktop-portal-wlr**: screen sharing on wlroots compositors (sway)
- **xdg-desktop-portal-gtk**: file picker and other portals for Flatpak apps
- **xdg-user-dirs**: creates `~/Downloads`, `~/Documents`, ...
- **libnotify**: provides `notify-send`
- **qt5ct** / **qt6ct**: Qt theme configuration (needed for `QT_QPA_PLATFORMTHEME`)

### Fonts

- **google-noto-sans-fonts**: broad Latin/Greek/Cyrillic coverage
- **google-noto-color-emoji-fonts**: emoji
- **google-noto-sans-cjk-fonts**: Chinese/Japanese/Korean
- **fontawesome-fonts-all**: icon font used by waybar and similar

### Audio

- **pipewire**: audio/video server (default on Fedora)
- **pipewire-pulseaudio**: PulseAudio compatibility layer
- **pipewire-jack-audio-connection-kit**: JACK compatibility layer
- **wireplumber**: PipeWire session manager
- **pavucontrol**: volume control GUI

### Networking

- **NetworkManager-wifi**: Wi-Fi support for NetworkManager (missing on Minimal installs)
- **NetworkManager-tui**: provides `nmtui`
- **nm-connection-editor**: NetworkManager connection GUI
- **network-manager-applet**: tray applet (`nm-applet`) with Wi-Fi password prompts
- **ModemManager**: mobile broadband modem support
- **usb_modeswitch**: switches USB modems out of storage mode
- **openssh**: SSH client and server
- **wget2-wget**: provides the `wget` command (Fedora replaced `wget` with `wget2`)

### System and maintenance

- **man-db** / **man-pages**: man pages
- **lm_sensors**: hardware temperature and fan sensors
- **timeshift**: system snapshots and restore
- **cronie**: cron daemon (`crond.service`), required for Timeshift's scheduled snapshots
- **bleachbit**: disk cleaner
- **clamav** / **clamav-freshclam** / **clamd**: antivirus, signature updater and daemon
- **polkit**: privilege-escalation framework
- **lxqt-policykit**: polkit authentication agent (GUI password prompts in sway)
- **seahorse**: keyring and password manager GUI
- **gnome-keyring**: the keyring daemon seahorse manages

### Dev services and containers

- **git**: version control
- **lazygit** (COPR): terminal UI for git
- **podman**: daemonless, rootless Docker alternative (preinstalled on Fedora, `alias docker=podman` works for most things)
- **moby-engine**: Docker engine as packaged by Fedora (see the [Docker](#docker) section)
- **docker-compose**: multi-container definitions (`docker compose`)
- **kubernetes1.37-client**: `kubectl`, the Kubernetes CLI
- **postgresql-server** / **postgresql-contrib**: database server and extensions (needs `initdb` before first start, see [PostgreSQL](#postgresql))
- **wine**: runs Windows applications

---

### Install Extra Packages

Third-party RPM repositories (Brave and VS Code ship their own repos, Fedora's equivalent of `brave-bin` and `visual-studio-code-bin` on the AUR):

```bash
# Brave
sudo dnf config-manager addrepo --from-repofile=https://brave-browser-rpm-release.s3.brave.com/brave-browser.repo
sudo dnf install brave-browser

# VS Code
sudo rpm --import https://packages.microsoft.com/keys/microsoft.asc
echo -e "[code]\nname=Visual Studio Code\nbaseurl=https://packages.microsoft.com/yumrepos/vscode\nenabled=1\ngpgcheck=1\ngpgkey=https://packages.microsoft.com/keys/microsoft.asc" | sudo tee /etc/yum.repos.d/vscode.repo > /dev/null
sudo dnf install code
```

Language-specific packages (things Fedora does not package):

- `sudo npm install -g neovim pyright prettier`
- `sudo npm install -g sql-language-server`
- `sudo npm install -g @angular/cli`
- `gem install neovim` (installs into `~/.local/share/gem`; add its `bin` directory to your `PATH` if neovim's `checkhealth` complains)
- `pip install --user pylatexenc` (Fedora does not block `pip --user` like Arch does)
- `pipx install autotiling` (alternative to the script in the dotfiles, see [Autotiling](#autotiling))
- `cargo install --locked tex-fmt`
- `cargo install --locked --git https://github.com/latex-lsp/texlab texlab`
- `cargo install --locked asm-lsp`
- `cargo install --git https://github.com/itsjunetime/tdf.git`
- `lua-language-server`: install it through `:Mason` in neovim (simplest), there is no Fedora package.
- `miniconda`: download the installer from [anaconda.com](https://www.anaconda.com/docs/getting-started/miniconda/install) and run it with `bash`.
- `utftex`: not packaged, build [libtexprintf](https://github.com/bartp5/libtexprintf) from source.
- Claude Code (for the claude code integration in neovim): `curl -fsSL https://claude.ai/install.sh | bash`
(native installer, no `sudo` needed) or `sudo npm install -g @anthropic-ai/claude-code`

Everything installed by `cargo` lands in `~/.cargo/bin`, add it to your `PATH`.

---

## Clone Configuration repositories

For everything related to a 'Rice' clone the repositories or set up own configurations.

- `git clone git@github.com:HaoRyuZark/dotfiles.git ~/dotfiles` (needs an SSH key added to GitHub, see [Set-Up SSH](#set-up-ssh))
or `git clone https://github.com/HaoRyuZark/dotfiles.git ~/dotfiles` (no key needed, but you cannot push)
- `cd ~/dotfiles`
- `stow .`

The Fedora dotfiles use a **flat** layout (`.bashrc`, `.config/`, ... directly at the top of the repo), so the whole repo is
one stow package and you run `stow .` (the Arch dotfiles use one directory per package and `stow */`).

### Stow

**Stow** creates symlinks in the parent directory (`~`) that mirror the structure of the folder where you run it.

- **Create Symlinks**: `stow .` inside `~/dotfiles`. The original files must not exist in the target location, otherwise stow
aborts with a conflict. Delete or move them first (e.g. the default `~/.bashrc`).

- **Remove Symlinks**: `stow -D .`

- **Re-create Symlinks**: `stow -R .` (useful after adding files)

- **Adding files to stow and updating**:

  1. Create a mirror of the original structure from the home directory to that file inside `~/dotfiles`.

  2. Copy the file or directory into it.

  3. Run `stow --adopt .` inside the dotfiles directory. **Careful:** `--adopt` moves the files currently in `~` into the repo,
  overwriting the repo's version. Check `git diff` afterwards and `git checkout .` if you want to keep the repo's version.

### Set-up Scripts

The dotfiles contain scripts in `~/dotfiles/scripts/restore/` for the setup of GNOME, Flatpak apps and the workspaces.
They use relative paths, so run them from that directory:

```bash
cd ~/dotfiles/scripts/restore
bash set_up.sh     # installs the packages
bash restore.sh    # runs restore_gnome_and_flatpak.sh and restore_workspaces.sh
```

- `set_up.sh`: should install the packages from [the package list](#install-the-packages-by-copying-the-following-command).
- `restore_gnome_and_flatpak.sh`: loads the GNOME extension settings with `dconf` and reinstalls the Flatpak apps. The extensions
themselves (`~/dotfiles/gnome/extensions.txt`) must be installed by hand, there is no CLI for it.
- `restore_workspaces.sh`: creates `~/Homo_Deus` and clones the project repositories (needs SSH).

> Read the steps below even if you use the scripts, so you know what is happening under the hood.

---

## Autotiling

Fedora does not package `autotiling`. Either install it with `pipx install autotiling` or use the script from the dotfiles:

```bash
chmod +x ~/dotfiles/scripts/autotiling
sudo cp ~/dotfiles/scripts/autotiling /usr/local/bin/
```

(`/usr/local/bin` instead of `/usr/bin`: files in `/usr/bin` belong to dnf and may be overwritten.) Then add
`exec_always autotiling` to the sway config.

---

## Random Wallpapers

To activate the script to switch between wallpapers run:

```bash
chmod +x ~/dotfiles/scripts/random-wallpaper.sh
```

> If you put your wallpapers in another location, you will need to edit the script.

---

## dnf Package Manager

`dnf` is Fedora's package manager (since Fedora 41 it is `dnf5`). It manages packages from configured RPM repositories and handles
dependency resolution, installation, removal, updates, and repository management.

### Quick Reference (pacman → dnf)

| Task                              | Arch                       | Fedora                                  |
| --------------------------------- | -------------------------- | --------------------------------------- |
| Full system upgrade               | `pacman -Syu`              | `dnf upgrade --refresh`                 |
| Install                           | `pacman -S pkg`            | `dnf install pkg`                       |
| Remove (+ unused deps)            | `pacman -Rs pkg`           | `dnf remove pkg`                        |
| Remove orphans                    | `pacman -Rns $(pacman -Qdtq)` | `dnf autoremove`                     |
| Search                            | `pacman -Ss term`          | `dnf search term`                       |
| Package info                      | `pacman -Si pkg`           | `dnf info pkg`                          |
| List installed                    | `pacman -Q`                | `dnf list --installed`                  |
| Explicitly installed              | `pacman -Qe`               | `dnf repoquery --userinstalled`         |
| Which package owns a file         | `pacman -Qo /path`         | `rpm -qf /path`                         |
| Which package provides a file     | `pacman -F file`           | `dnf provides file`                     |
| Files of a package                | `pacman -Ql pkg`           | `rpm -ql pkg` / `dnf repoquery -l pkg`  |
| Install a local package           | `pacman -U file.pkg.tar.zst` | `dnf install ./file.rpm`              |
| Clean cache                       | `pacman -Scc`              | `dnf clean all`                         |
| Package groups                    | `pacman -Sg`               | `dnf group list` / `dnf install @group` |
| AUR                               | `yay -S pkg`               | `dnf copr enable user/project` + `dnf install pkg` |
| Undo the last transaction         | *(not possible)*           | `dnf history undo last`                 |

### Commands

- `dnf [global-options] <command> [arguments]`

  - **Function**: Manages RPM packages and software repositories on Fedora and other RPM-based distributions.

  - **Common Commands**:
    - `install`: Install one or more packages.
    - `remove`: Remove one or more packages.
    - `upgrade`: Upgrade installed packages.
    - `update`: Alias for `upgrade`.
    - `search`: Search package names and descriptions.
    - `info`: Display detailed package information.
    - `list`: List installed, available, or all packages.
    - `provides`: Find which package provides a particular file or capability.
    - `reinstall`: Reinstall an already installed package.
    - `downgrade`: Downgrade a package to an older available version.
    - `swap`: Replace one package with another in a single transaction.
    - `autoremove`: Remove packages that were installed as dependencies but are no longer required.
    - `history`: Display and manage package transactions.
    - `clean`: Remove cached package and repository data.
    - `check`: Check for dependency problems.
    - `repoquery`: Query packages from enabled repositories.
    - `group`: Manage package groups (`@group` works with `install`/`remove` too).
    - `copr`: Enable and disable COPR repositories.

  - **Example Usage**: `sudo dnf install vim`

- `dnf install [flags] <package>...`

  - **Function**: Installs one or more packages and their required dependencies.

  - **Flags**:
    - `-y`: Automatically answer yes to confirmation prompts.
    - `--allowerasing`: Allow DNF to remove installed packages to resolve dependency conflicts.
    - `--skip-unavailable`: Skip packages that do not exist instead of aborting.
    - `--best`: Attempt to install the highest available package version.
    - `--no-best`: Allow installation of an older version if the newest version cannot be installed.
    - `--downloadonly`: Download packages without installing them.

  - **Parameters**:
    - `<package>` *(required)*: Name, version, group (`@name`), local file (`./file.rpm`) or URL.

  - **Example Usage**:
    - `sudo dnf install firefox`
    - `sudo dnf install gcc gcc-c++ make`
    - `sudo dnf install @development-tools`
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

- `dnf search <term>`

  - **Function**: Searches enabled repositories for packages matching a name or description.

  - **Example Usage**: `dnf search text editor`

- `dnf info <package>`

  - **Function**: Displays detailed information about a package.

  - **Example Usage**: `dnf info neovim`

- `dnf list [flags] [package]`

  - **Function**: Lists installed and available packages.

  - **Flags**:
    - `--installed`: Show installed packages.
    - `--available`: Show packages available for installation.
    - `--upgrades`: Show packages with available updates.

  - **Example Usage**:
    - `dnf list --installed`
    - `dnf list --upgrades`
    - `dnf list --installed neovim`

- `dnf provides <path-or-capability>`

  - **Function**: Determines which package provides a particular file or capability.

  - **Example Usage**:
    - `dnf provides /usr/bin/nvim`
    - `dnf provides '*/libssl.so*'`

- `dnf reinstall <package>`

  - **Function**: Reinstalls an installed package, replacing its files with fresh copies.

  - **Example Usage**: `sudo dnf reinstall bash`

- `dnf downgrade <package>`

  - **Function**: Attempts to install an older available version of a package (Fedora's version of Arch's `downgrade`).

  - **Example Usage**: `sudo dnf downgrade firefox`

- `dnf swap <old> <new>`

  - **Function**: Removes one package and installs another in one transaction.

  - **Example Usage**: `sudo dnf swap ffmpeg-free ffmpeg --allowerasing`

- `dnf autoremove`

  - **Function**: Removes packages installed as dependencies that are no longer needed.

  - **Example Usage**: `sudo dnf autoremove`

- `dnf history [command]`

  - **Function**: Displays previous package transactions and can be used to inspect or undo transactions.

  - **Commands**:
    - `list`: List previous transactions.
    - `info <id>`: Show details about a transaction.
    - `undo <id>`: Attempt to reverse a transaction (`undo last` for the most recent one).
    - `redo <id>`: Repeat a previous transaction.

  - **Example Usage**:
    - `dnf history list`
    - `dnf history info 15`
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

  - **Function**: Manages DNF repository configuration (dnf5 syntax).

  - **Common Operations**:
    - `addrepo --from-repofile=<url>`: Add a repository from a `.repo` file.
    - `setopt <repo>.enabled=1`: Enable a repository.
    - `setopt <repo>.enabled=0`: Disable a repository.

  - **Example Usage**: `sudo dnf config-manager setopt fedora-cisco-openh264.enabled=1`

- `dnf copr <command> <user/project>`

  - **Function**: Manages COPR community repositories.

  - **Commands**:
    - `enable`: Add the repository.
    - `disable`: Disable it (keeps the `.repo` file).
    - `remove`: Remove it completely.
    - `list`: List enabled COPRs.

  - **Example Usage**: `sudo dnf copr enable atim/starship`

- `rpm`

  - **Function**: The low-level package tool under dnf. Useful for queries on installed packages.

  - **Example Usage**:
    - `rpm -qa | grep kernel`: List installed packages matching a name.
    - `rpm -qf /usr/bin/bash`: Which package owns a file.
    - `rpm -ql bash`: Files of an installed package.
    - `rpm -qi bash`: Information about an installed package.

---

## Flatpak

`flatpak` is a package-management and application-distribution system primarily designed for desktop applications. Unlike DNF, Flatpak applications run inside
a sandbox and generally use their own runtime and dependency environment.

Flatpak applications are not updated by `dnf upgrade`; run `flatpak update` as well.

Install and set up (preinstalled on Workstation, needed on Minimal):

```bash
sudo dnf install flatpak
flatpak remote-add --if-not-exists flathub https://dl.flathub.org/repo/flathub.flatpakrepo
```

### Commands

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

- `flatpak install [flags] <remote> <application>`

  - **Function**: Installs a Flatpak application or runtime.

  - **Flags**:
    - `--user`: Install for the current user rather than system-wide.
    - `-y`: Automatically confirm installation.

  - **Example Usage**:
    - `flatpak install flathub org.mozilla.firefox`
    - `flatpak install --user flathub org.mozilla.firefox`

- `flatpak uninstall [flags] <application>`

  - **Function**: Removes a Flatpak application or runtime.

  - **Flags**:
    - `--user`: Operate on the per-user installation.
    - `--delete-data`: Remove the application's user data as well.
    - `--unused`: Remove unused runtimes and extensions.

  - **Example Usage**:
    - `flatpak uninstall org.mozilla.firefox`
    - `flatpak uninstall --delete-data org.mozilla.firefox`
    - `flatpak uninstall --unused`

- `flatpak update [application]`

  - **Function**: Updates installed Flatpak applications and runtimes.

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
    - `flatpak list --app`
    - `flatpak list --app --columns=application > ~/dotfiles/flatpak/flatpak.txt` (back up the app list for the restore script)

- `flatpak info <application>`

  - **Function**: Displays detailed information about an installed application or runtime.

  - **Example Usage**: `flatpak info org.mozilla.firefox`

- `flatpak run <application>`

  - **Function**: Launches a Flatpak application.

  - **Example Usage**: `flatpak run org.mozilla.firefox`

- `flatpak remote-list`

  - **Function**: Lists configured Flatpak repositories (remotes).

  - **Example Usage**: `flatpak remote-list`

- `flatpak remote-add [flags] <name> <url>`

  - **Function**: Adds a Flatpak repository.

  - **Flags**:
    - `--if-not-exists`: Do nothing if the remote already exists.
    - `--user`: Add the remote for the current user only.

  - **Example Usage**: `flatpak remote-add --if-not-exists flathub https://dl.flathub.org/repo/flathub.flatpakrepo`

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
    - `flatpak override --user --filesystem=home org.mozilla.firefox`

- `flatpak repair [flags]`

  - **Function**: Repairs the local Flatpak installation by checking and fixing invalid or incomplete objects.

  - **Flags**:
    - `--user`: Repair the per-user installation.
    - `--system`: Repair the system installation.

  - **Example Usage**: `sudo flatpak repair`

---

## Vim Provider

The python provider for neovim is the `python3-neovim` package (already in the package list). Else there will be an error
in the `checkhealth` command of neovim.

```bash
sudo dnf install python3-neovim
```

For the Node and Ruby providers: `sudo npm install -g neovim` and `gem install neovim`.

---

## GTK and Qt Themes

- **Requirements:** `qt5ct` and `qt6ct` (already in the package list)
- **Setting up the Qt env var:** write `QT_QPA_PLATFORMTHEME=qt5ct` with `sudo vim /etc/environment` (qt6ct reads the same value for Qt 6 apps), then log out and in again
- **Installing Qt Themes:** `sudo dnf install plasma-breeze` (or `breeze-gtk` for GTK) then select it in `qt5ct` and `qt6ct`
- **GTK themes:** use `gnome-tweaks` on GNOME; on sway edit `~/.config/gtk-3.0/settings.ini` or run `gsettings set org.gnome.desktop.interface gtk-theme <theme>`. The GTK settings live in `~/.config/gtk-3.0` and `~/.config/gtk-4.0` (part of the dotfiles).

---

## Maintenance

- **Update system:** `sudo dnf upgrade --refresh` and `flatpak update`.

- **Update npm packages:** `sudo npm install npm@latest -g`.

- **Update rust toolchain:** `rustup update`.

- **Remove orphan packages:** `sudo dnf autoremove`.

- **Clean the cache:** `sudo dnf clean all`.

- **Uninstall unused flatpak packages:** `flatpak uninstall --unused`.

- **Remove unnecessary files:** Use `Bleachbit`, or `du -sh path` to see the disk usage of a directory and `rm -rf path/` to remove.
Be careful not to delete important directories.

- **Check for failing services:** `systemctl --failed`.

- **Check for errors in the log files:** `sudo journalctl -p 3 -xb`.

- **Delete old logs:** `sudo journalctl --vacuum-time=2weeks`.

- **Firmware updates:** `fwupdmgr refresh && fwupdmgr update` (BIOS, SSD, dock firmware via LVFS).

- **After a kernel update:** nothing to do. Fedora's GRUB uses BLS entries, so no `grub-mkconfig` is needed.

- **Upgrade to a new Fedora release** (every ~6 months, supported releases get ~13 months of updates):

```bash
sudo dnf upgrade --refresh                                   # fully update the current release first
sudo dnf system-upgrade download --releasever=XX             # XX = the next release number
sudo dnf offline reboot                                      # reboot and install the upgrade
```

After the upgrade: `sudo dnf autoremove` and, optionally, `sudo dnf distro-sync` to sync packages with the new release.
On Workstation you can also upgrade from GNOME Software.

---

## Timeshift and Snapshots

Requirements:

- **Scheduled snapshots** need a cron daemon: `cronie` (in the package list) with `sudo systemctl enable --now crond.service`.
- **btrfs mode** needs the Ubuntu-style subvolumes `@` and `@home`. Fedora's default layout uses `root` and `home`, so
  **Timeshift's btrfs mode does not work on a default Fedora install**. Options:
  - use Timeshift in **rsync mode** (works everywhere, ideally to a second drive), or
  - use **Snapper** (Fedora's native btrfs snapshot tool, works with the default layout), or
  - create `@`/`@home` yourself in the custom partitioning step of the installer (see [Everything](#installation-fedora-everything-recommended-for-developers)).

### Snapper (btrfs alternative)

```bash
sudo dnf install snapper btrfs-assistant
sudo snapper -c root create-config /
sudo snapper -c home create-config /home
sudo systemctl enable --now snapper-timeline.timer snapper-cleanup.timer
```

- Automatic pre/post snapshots around dnf transactions: `python3-dnf-plugin-snapper` only works with the old dnf4. With dnf5 use
  `libdnf5-plugin-actions` and an actions file that calls `snapper` (see `man libdnf5-actions`), or take a manual snapshot before
  big updates: `sudo snapper -c root create -d "before upgrade"`.
- `btrfs-assistant` is a GUI to browse, compare and restore snapshots.
- `snapper -c root list` lists snapshots, `sudo snapper -c root undochange <from>..<to>` reverts changes.

### Timeshift Setup via GUI

To open, run `timeshift-launcher` (or pick Timeshift in `wofi`). It asks for the root password through polkit, so the
polkit agent (`lxqt-policykit`) must be running in your sway session (e.g. `exec lxqt-policykit-agent` in the sway config).

1. Select the type of snapshots (rsync on a default Fedora install)

2. Select your second storage device

3. Schedule the snapshot

4. Select the users: `root` and `yourself`, ...

5. Skip the filter and click ok

### Timeshift Usage CLI

- **Check config:** `sudo timeshift --check`

- **Snapshot type:** `sudo timeshift --rsync` or `sudo timeshift --btrfs`

- **Storage Location:** `sudo timeshift --rsync --snapshot-device /dev/disk_to_use`

- **Create a snapshot:** `sudo timeshift --create --comments "Something" --tags D`

- **See snapshots:** `sudo timeshift --list`

- **Restore system:** `sudo timeshift --restore` then type the identifier of the target

- **Delete snapshot:** `sudo timeshift --delete` then type the identifier of the target

- **Delete specific snapshot:** `sudo timeshift --delete --snapshot 'date'`

- **Delete snapshots:** `sudo timeshift --delete-all`

- **Scheduling:** there is no CLI flag for it. Set the schedule in the GUI (Settings - Schedule) or edit
`/etc/timeshift/timeshift.json` (`schedule_daily`, `count_daily`, ...). Requires `crond` to be running.

---

## Sensors

To set up the sensors run the command

`sudo sensors-detect` then type `YES` for all safe operations.

To see the data type `sensors`.

---

## ClamAV

Fedora splits ClamAV into several packages and uses different paths and service names than Arch:

| Item              | Arch                          | Fedora                                   |
| ----------------- | ----------------------------- | ---------------------------------------- |
| Daemon config     | `/etc/clamav/clamd.conf`      | `/etc/clamd.d/scan.conf`                 |
| Updater config    | `/etc/clamav/freshclam.conf`  | `/etc/freshclam.conf`                    |
| Daemon service    | `clamav-daemon.service`       | `clamd@scan.service`                     |
| Updater service   | `clamav-freshclam.service`    | `clamav-freshclam.service`               |
| On-access service | `clamav-clamonacc.service`    | `clamav-clamonacc.service`               |

- If `/etc/clamd.d/scan.conf` does not exist, copy the template: `sudo cp /usr/share/doc/clamd/clamd.conf /etc/clamd.d/scan.conf`.
- Edit it with `sudo vim /etc/clamd.d/scan.conf` and apply the same options as in the [Arch clamd.conf](./Arch.md#clamdconf)
(`LogFile`, `LocalSocket`, `OnAccessIncludePath /home`, `OnAccessPrevention no`, `VirusEvent`, ...). Comment out the `Example` line.
Keep the `LocalSocket` path and `User` that Fedora's file uses (`/run/clamd.scan/clamd.sock`, user `clamscan`).
- The virus alert script and sudoers rule from the Arch guide work the same; put the script at `/etc/clamd.d/virus-event.bash`
and use `clamscan` instead of `clamav` as the user in the sudoers file.
- **SELinux:** Fedora runs SELinux in enforcing mode. Allow ClamAV to scan the whole system with:

```bash
sudo setsebool -P antivirus_can_scan_system 1
```

- Download the virus database **first** (`clamd` refuses to start without it), then enable the services in this order:

```bash
sudo freshclam
sudo systemctl enable --now clamav-freshclam.service
sudo systemctl enable --now clamd@scan.service
sudo systemctl enable --now clamav-clamonacc.service
```

After changing the config later, restart with `sudo systemctl restart clamd@scan clamav-clamonacc`.

---

## Audio

PipeWire, pipewire-pulse and WirePlumber are the default on Fedora and start automatically on login.
If audio does not work, check them with:

- `systemctl --user status pipewire pipewire-pulse wireplumber`
- `systemctl --user enable --now pipewire pipewire-pulse wireplumber` if they are not running
- `pactl info` should show `Server Name: PulseAudio (on PipeWire ...)`

---

## Set pdf viewer

- `xdg-mime default org.pwmt.zathura.desktop application/pdf`

---

## Docker

Fedora ships **Podman** by default, a rootless, daemonless Docker replacement with the same CLI (`podman run ...`).
For most things `alias docker=podman` is enough, and `podman compose` uses `docker-compose` under the hood.

For the real Docker engine use Fedora's `moby-engine` (in the package list):

- `sudo systemctl enable --now docker.service`
- `sudo usermod -aG docker $USER` then log out and in again to use `docker` without `sudo`
- Test with `docker run hello-world`

> Docker's official `docker-ce` packages are an alternative (repo at `https://download.docker.com/linux/fedora/docker-ce.repo`),
> but they conflict with `moby-engine`, install only one of them.

> **Note:** Docker writes its own firewall rules. Ports published with `-p` are reachable from the network **even if firewalld
> does not allow them**. Bind to localhost (`-p 127.0.0.1:8080:80`) for services that should stay local.

**Toolbox / Distrobox:** `toolbox create` (preinstalled on Workstation) and `distrobox` give you a mutable container with your home
directory mounted, useful to try packages or other distros without touching the host.

---

## PostgreSQL

```bash
sudo postgresql-setup --initdb
sudo systemctl enable --now postgresql.service
sudo -u postgres createuser --superuser $USER
createdb $USER
```

---

## Second Hard Drive

Use the same procedure as during an Arch installation:

- Identifying (`lsblk`)
- Partitioning (`sudo fdisk /dev/sdX`)
- Formatting (`sudo mkfs.ext4 /dev/sdX1` or `sudo mkfs.btrfs /dev/sdX1`)
- Mounting

Then add it to `fstab` to mount automatically when booting:

- Get the UUID with `lsblk -f`
- Create the mount point: `sudo mkdir -p /mnt/data`
- Open and edit `/etc/fstab` and add the line `UUID=id /mnt/... file_system_type options dump_option(0) fsck_order(2)`, e.g.:

```text
UUID=xxxx-xxxx  /mnt/data  ext4  defaults,nofail  0  2
```

`nofail` keeps the system booting if the drive is missing or broken. Test the entry without rebooting with
`sudo systemctl daemon-reload && sudo mount -a`.

If a service cannot access the drive, it is usually SELinux: `sudo restorecon -Rv /mnt/data`.

---

## systemctl

`systemctl` is the primary tool used to examine and control the `systemd` system and service manager on Linux systems.

Essential commands:

- **Start a service:** `sudo systemctl start <service-name>`

- **Stop a service:** `sudo systemctl stop <service-name>`

- **Restart a service:** `sudo systemctl restart <service-name>`

- **Enable a service:** `sudo systemctl enable <service-name>` (`--now` also starts it)

- **Disable a service:** `sudo systemctl disable <service-name>`

- **Check status of a service:** `systemctl status <service-name>`

- **List all active services:** `systemctl list-units --type=service`

- **List failed services:** `systemctl --failed`

---

## Printers

Workstation already includes CUPS. On Minimal/Everything:

```bash
sudo dnf install cups system-config-printer
sudo systemctl enable --now cups
```

For network printer auto-discovery also install Avahi:

```bash
sudo dnf install avahi nss-mdns
sudo systemctl enable --now avahi-daemon
```

---

## Firewall

Fedora uses **firewalld** (enabled by default), not `ufw`. It works with **zones**; Workstation uses the permissive
`FedoraWorkstation` zone (ports 1025-65535 open), other editions use `public`.

```bash
sudo firewall-cmd --state                         # running?
sudo firewall-cmd --get-active-zones              # which zone is in use
sudo firewall-cmd --list-all                      # rules of the active zone
```

Make it stricter (like the Arch `ufw` setup: deny incoming, allow outgoing, allow ssh):

```bash
sudo firewall-cmd --set-default-zone=public
sudo firewall-cmd --permanent --add-service=ssh   # only if you need sshd
sudo firewall-cmd --reload
```

Open a port: `sudo firewall-cmd --permanent --add-port=8080/tcp && sudo firewall-cmd --reload`.

For a GUI: `sudo dnf install firewall-config`.

---

## SELinux

Fedora runs SELinux in **enforcing** mode. It is the most common source of "permission denied" errors that do not make sense.
Do **not** disable it; find the cause instead:

- `getenforce`: shows the current mode.
- `sudo ausearch -m AVC -ts recent`: shows recent denials.
- `sudo dnf install setroubleshoot` then `sudo sealert -a /var/log/audit/audit.log` explains denials and suggests fixes.
- `sudo restorecon -Rv /path`: resets file labels (fixes files moved/copied from elsewhere).
- `sudo setenforce 0`: temporarily permissive until reboot, **only** to test whether SELinux is the cause.

---

## Power Management for Laptops

Fedora uses `tuned` with `tuned-ppd` (the `power-profiles-daemon` replacement) by default, which is usually enough:
`powerprofilesctl set power-saver`.

For more control use TLP instead. It conflicts with tuned/power-profiles-daemon, so remove them:

```bash
sudo dnf remove tuned tuned-ppd
sudo dnf install tlp tlp-rdw
sudo systemctl enable --now tlp
sudo systemctl enable NetworkManager-dispatcher.service
sudo systemctl mask systemd-rfkill.service systemd-rfkill.socket
```

Check with `sudo tlp-stat -b`.

---

## Trouble Shooting

### Common Issues

- **Slow boot:** check with `systemd-analyze blame` and `systemd-analyze critical-chain`, then `systemctl status <service-name>`
and `journalctl -u <service-name>`.

- **An update broke something:** `dnf history list`, then `sudo dnf history undo <id>`. For a broken kernel, pick an older one in the GRUB menu.

- **Idle waiting for keyboard input after locked screen (swaylock):** usually the fingerprint PAM module. Check with:

```bash
cat /etc/pam.d/swaylock
authselect current          # look for "with-fingerprint"
```

If `with-fingerprint` is enabled, run:

```bash
sudo authselect disable-feature with-fingerprint
```

### Broken System

If the system does not boot, boot a Fedora live USB, unlock/mount the root subvolume and chroot into it:

```bash
sudo mount -o subvol=root /dev/nvme0n1pX /mnt        # btrfs root subvolume
sudo mount /dev/nvme0n1pY /mnt/boot                  # /boot partition
sudo mount /dev/nvme0n1pZ /mnt/boot/efi              # EFI partition
for d in dev proc sys run; do sudo mount --rbind /$d /mnt/$d; done
sudo chroot /mnt
```

Inside you can fix packages with `dnf`, then run `exit` and `reboot`. If you use Snapper or Timeshift, restoring a
snapshot is usually faster.
