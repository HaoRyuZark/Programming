# tmux Cheat Sheet

## Starting and Exiting tmux
- `tmux` – Start a new session
- `tmux new -s <session_name>` – Start a new session with a name
- `tmux attach -t <session_name>` – Attach to an existing session
- `tmux detach` – Detach from the current session
- `tmux list-sessions` – List active sessions
- `tmux kill-session -t <session_name>` – Kill a specific session
- `tmux kill-server` – Kill all sessions

## Session Management
- `Ctrl-b d` – Detach from a session
- `tmux rename-session -t <old_name> <new_name>` – Rename a session

## Window Management
- `Ctrl-b c` – Create a new window
- `Ctrl-b w` – List windows
- `Ctrl-b n` – Next window
- `Ctrl-b p` – Previous window
- `Ctrl-b 0-9` – Switch to window 0-9
- `Ctrl-b ,` – Rename current window
- `Ctrl-b &` – Close current window

## Pane Management
- `Ctrl-b %` – Split pane vertically
- `Ctrl-b "` – Split pane horizontally
- `Ctrl-b o` – Switch to the next pane
- `Ctrl-b ;` – Toggle between last active panes
- `Ctrl-b x` – Close the current pane
- `Ctrl-b z` – Toggle pane zoom

## Pane Resizing
- `Ctrl-b <arrow>` – Resize pane (default keys: `Ctrl-b` then `Up`, `Down`, `Left`, `Right`)
- `Ctrl-b {` – Swap pane left
- `Ctrl-b }` – Swap pane right

## Copy and Paste Mode
- `Ctrl-b [` – Enter copy mode
- `Space` – Start selection
- `Enter` – Copy selection
- `Ctrl-b ]` – Paste selection

## Miscellaneous
- `Ctrl-b ?` – Show key bindings
- `Ctrl-b t` – Show time in the status bar
- `Ctrl-b d` – Detach from tmux session
- `tmux source-file ~/.tmux.conf` – Reload tmux configuration

This cheat sheet covers the essential commands for working with tmux efficiently!


