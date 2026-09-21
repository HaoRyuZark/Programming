# Set up SSH

Quick guide on how to setup ssh.

--- 

## Check if you already have an SSH key

- `ls ~/.ssh`

Look for files like `id_rsa` and `id_rsa.pub`. If they exist, skip to step 1.4.

## 1.1 Generate a new SSH key

- `ssh-keygen -t ed25519 -C "your_email@example.com" `

> When prompted, press **Enter** to accept the default file location. You can add a passphrase for extra security (optional).

## 1.2 Start the SSH agent

- `eval "$(ssh-agent -s)"`

## 1.3 Add your key to the SSH agent

- `ssh-add ~/.ssh/id_ed25519`

#### 1.4 Add your SSH key to GitHub

Copy the public key:

- `cat ~/.ssh/id_ed25519.pub`

Go to **GitHub -> Settings -> SSH and GPG keys -> New SSH key**, and paste it there.

---

