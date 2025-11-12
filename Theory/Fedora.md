# Fedora Setup

Documentatiion for seeting up Fedora Linux with the necessary tools and configurations for development.

## Installation 

Just use the graphical installer.

--- 

## Post Install

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

- `sudo dnf install texlive-scheme-full fastetch kitty neovim stow npm 
   luarocks lua nodejs rust htop yazi zathura ruby php btop
   clamav bleachbit jupyterlab jupyter-notebook zathura-pdf-poppler timeshift
   fzf bat lsd tldr lazygit docker pyright
   lua-language-server bash-language-server postgresql clang ghc julia gnome-tweaks`

---

### Install Extra Packages

- `sudo npm install -g neovim`
- `sudo pacman -S python-neovim`
- `sudo pacman -S python-pylatexenc`
- `gem install neovim`
- `sudo pip install matplotlib scikit-learn pygame`
- `sudo npm install -g regex`
- `npm install -g tree-sitter-cli`
- `rustup component add rust-analyzer`
- `sudo rpm --import https://packages.microsoft.com/keys/microsoft.asc 
   echo -e "[code]\nname=Visual Studio Code\nbaseurl=https://packages.microsoft.com/yumrepos/vscode\nenabled=1\nautorefresh=1\ntype=rpm-md\ngpgcheck=1\ngpgkey=https://packages.microsoft.com/keys/microsoft.asc" | sudo tee /etc/yum.repos.d/vscode.repo > /dev/null`
- `pip install pyright`
- `cargo install --git https://github.com/latex-lsp/texlab`
- `curl -I https://pkg.julialang.org`
- `sudo npm i -g sql-language-server`
- `sudo dnf install lua-language-server`

---

### Set Up RPM 

- `sudo dnf install https://download1.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm https://download1.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm `

### Neovim

Maintenance 

- Delete Everything: `rm -rf ~/.local/share/nvim/*`

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

### Clone development respositories

- `mkdir Homo_Deus`
- `cd Homo_Deus`
- `git clone git@github.com:HaoRyuZark/Computer_Science_Compedium.git`
- `git clone git@github.com:HaoRyuZark/Mathematica_Compendium.git`
- `git clone git@github.com:HaoRyuZark/Programming.git`

--- 

### Copilot in Neovim 

To set up copilot run 

- `Lazy load copilot.vim`
- `Copilot setup` and proceed to authenticate

### University Stuff

Download the Mathematics folder from Google Drive to obtain books and worksheets.

--- 

### Load Extensions 

`dconf load /org/gnome/shell/extensions/ < ~/dotfiles/gnome_extensions.txt`

--- 

