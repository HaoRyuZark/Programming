# Git

## Commits, Brances and HEAD 

- **Commits** are the units of storage whic are snapshots of the working directory with an identifer of type hash. 
- **Branches** are just pointer to a commit hash. Mostly at the end of a chain.
- **HEAD** Is a pointer to the current branch. If you checkout to a commit then the HEAD becomes detached because it is not pointer to any  branch.

## Setup and Configuration

### Set up SSH key (only needed once per machine)

#### Check if you already have an SSH key

```bash
ls ~/.ssh
```
Look for files like `id_rsa` and `id_rsa.pub`. If they exist, skip to step 1.4.

#### 1.1 Generate a new SSH key
```bash
ssh-keygen -t ed25519 -C "your_email@example.com"
```
> When prompted, press **Enter** to accept the default file location. You can add a passphrase for extra security (optional).

#### 1.2 Start the SSH agent
```bash
eval "$(ssh-agent -s)"
```

#### 1.3 Add your key to the SSH agent
```bash
ssh-add ~/.ssh/id_ed25519
```

#### 1.4 Add your SSH key to GitHub

Copy the public key:
```bash
cat ~/.ssh/id_ed25519.pub
```

Go to **GitHub -> Settings -> SSH and GPG keys -> New SSH key**, and paste it there.

#### 1.5 Test your connection

```bash
ssh -T git@github.com
```
If successful, you'll see a message like:
> Hi `username`! You've successfully authenticated.


- `git config --global user.name "Your Name"` – Set your name
- `git config --global user.email "your.email@example.com"` – Set your email
- `git config --global color.ui auto` – Enable colored output
- `git config --list` – List all configured settings

## Creating and Cloning Repositories

- `git init` – Initialize a new Git repository
- `git clone <repo_url>` – Clone an existing repository

## Basic Commands

- `git status` – Show the status of changes
- `git log --stat` = Shows which files were modified and how many lines changed
- `git log -p` = Shows which files were modified with the modifications
- `git add <file>` – Stage a file for commit
- `git add .` – Stage all changes
- `git commit -m "message"` – Commit staged changes
- `git commit --amend` – Edit the last commit
- `git log` – Show commit history
- `git log --oneline --graph` – Show a compact commit history

## Branching and Merging

- `git branch` – List branches
- `git branch <branch_name>` – Create a new branch
- `git checkout <branch_name>` – Switch to a branch
- `git checkout -b <branch_name>` – Create and switch to a new branch
- `git merge <branch_name>` – Merges a branch into the current branch you are in
- `git branch -d <branch_name>` – Delete a branch
- `git branch -D <branch_name>` – Force delete a branch
- `git rebase <branch_name>` – Puts the changes of another branch on top of the current branch 

## Working with Remotes

- `git remote -v` – List remotes
- `git remote add origin <repo_url>` – Add a remote repository
- `git fetch origin` – Fetch changes from remote
- `git pull origin <branch>` – Pull changes from remote branch (fetch + merge)
- `git push origin <branch>` – Push changes to remote branch
- `git push -u origin <branch>` – Push and set upstream branch
- `git remote remove <name>` – Remove a remote

## Stashing Changes

- `git stash` – Stash current changes
- `git stash list` – List stashed changes
- `git stash apply` – Apply the latest stash
- `git stash pop` – Apply and remove the latest stash
- `git stash drop` – Remove the latest stash

## Resetting and Reverting

- `git checkout <commit>` – Visit old commits. Due to the detached HEAD no changes should be made because they will get lost.
- `git reset <file>` – Unstage a file
- `git reset --hard <commit>` – Reset to a specific commit (deletes changes)
- `git reset --soft <commit>` – Reset to a commit but keep changes staged and the working directory unchanged.
- `git reset --mixed <commit>` – Reset to a commmit, clears statging and the working directory remeains unchanged (default)
- `git revert <commit>` – Create a new commit that undoes a previous commit.

## Tagging

- `git tag` – List all tags
- `git tag -a v1.0 -m "Version 1.0"` – Create an annotated tag
- `git push origin --tags` – Push tags to remote

## Undoing Changes

- `git checkout -- <file>` – Discard changes in a file
- `git restore <file>` – Restore a file to the last commit
- `git reflog` – View history of HEAD changes
- `git branch recovery <commit>` if when doing changes things went wrong, with `reflog` plus this command we can resolve our errors
- `git cherry-pick <commit>` – Apply a specific commit from another branch

## Miscellaneous

- `git diff` – Show changes between commits and working directory
- `git blame <file>` – Show who modified each line in a file
- `git show <commit>` – Show details of a commit
- `git rm <file>` – Remove a file from Git

---

## Create a remote GitHub repo (manually)

Go to [GitHub](https://github.com/new) and create a new repository **without** initializing with a README (since we already have one locally).

---

## Link local repo to GitHub (via SSH)

```bash
git remote add origin git@github.com:your-username/your-repo.git
```

---

## Push to GitHub

```bash
git push -u origin main
```
> If your default branch is `master`, replace `main` with `master`.

---


