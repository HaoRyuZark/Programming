# Fedora

## Installation 

Use the GUI installer, no need for extra stuff. 

--- 

## Set up SSH

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

Go to **GitHub -> Settings -> SSH and GPG keys -> New SSH key**, and paste it there.

--- 

## Packages 

### Via dnf 

```bash 

sudo dnf install timeshift \
rust \
brave \ 
fastfetch \ 
fzf \  
ripgrep \ 
ghc 
kiwix-dektop \ 
lua \ 
starship \
tex-live-scheme-full \ 
vscode \
python3 \
kitty \
neovim \ 
libreoffice \ 
btop \ 
bleachbit \ 
docker \ 
julia\ 
git \
bat \ 
lsd \ 
java \ 
nodejs \ 
lua \ 
fd \ 
tldr \ 
ruby \ 
python3-pygame\ 
python3-numpy \ 
python3-matplotlib\ 
python3-hpandas \
clamav \ 
stow \ 
steam \ 
jupyterlab 
jupyternotebook \ 
```

### Via the Shop or Flatpack 

- PdfJumbler
- Logisim-evolution
- Flatseal
- draw.io
- Extension Manager
- Blanket
- Keypunch
- Archives
- Calligraphy
- DBeaver Community
- Binary
- Prism Launcher
- Zotero
- Graphs

```bash 
flatpak install flathub \
com.github.mgropp.PdfJumbler \
com.github.reds.LogisimEvolution \
com.github.tchx84.Flatseal \
com.jgraph.drawio.desktop \
com.mattjakeman.ExtensionManager \
com.rafaelmardojai.Blanket \
dev.bragefuglseth.Keypunch \
dev.geopjr.Archives \
dev.geopjr.Calligraphy \
io.dbeaver.DBeaverCommunity \
io.github.fizzyizzy05.binary \
org.prismlauncher.PrismLauncher \
org.zotero.Zotero \
se.sjoerd.Graphs \ 
io.github.alainm23.planify \ 

```

### Misce 

```bash 
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh \ 
rustup component add rust-analyzer \ 
```


### Pip 

```bash 

```

--- 

## RPM Fusion 

```bash 
sudo dnf install https://mirrors.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm https://mirrors.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm
```

--- 

## Security 

--- 

## Gnome Configuration 

- **Configuration** 

```bash 

# Backup 
dconf dump / > gnome-settings.dconf

# Load 
dconf load / < gnome-settings.dconf

```

- **Extensions** 

```bash 

# Backup 
cp -r ~/.local/share/gnome-shell/extensions ./extensions-backup

# Load 
cp -r extensions-backup ~/.local/share/gnome-shell/extensions/
```



--- 

## Work Setup

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


### Clone development respositories

- `mkdir Homo_Deus`
- `cd Homo_Deus`
- `git clone git@github.com:HaoRyuZark/Computer_Science_Compedium.git`
- `git clone git@github.com:HaoRyuZark/Mathematica_Compendium.git`
- `git clone git@github.com:HaoRyuZark/Programming.git`


### Set pdf viewer 

- `xdg-mime default org.pwmt.zathura.desktop application/pdf`

--- 

## Timeshift

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


