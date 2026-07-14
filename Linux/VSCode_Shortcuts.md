# VSCode 

> **Setup notes:** Vim extension active. Many default Vim `Ctrl+*` overrides have been **disabled** — standard VSCode bindings take 
priority for most `Ctrl` combos. 

---

## Navigation & Quick Access

| Shortcut | Action | Notes |
|---|---|---|
| `Ctrl+P` | Quick Open file | Vim override disabled — works as VSCode |
| `Ctrl+Shift+P` / `F1` | Command Palette | |
| `Ctrl+G` | Go to Line | |
| `Ctrl+T` | Go to Symbol in Workspace | |
| `Ctrl+Shift+O` | Go to Symbol in File | |
| `Ctrl+R` | Open Recent | |
| `Ctrl+Shift+E` | Focus Explorer | |
| `Ctrl+Shift+F` | Focus Search | |
| `Ctrl+P Enter @` | Searches by Components in the current file | |
| `Ctrl+Shift+G` | Focus Source Control | |
| `Ctrl+Shift+D` | Focus Debug | |
| `Ctrl+Shift+X` | Focus Extensions | |
| `Ctrl+0` | Focus Side Bar | |
| `Ctrl+1/2/3...` | Focus Editor Group 1/2/3... | |
| `F6` / `Shift+F6` | Focus Next / Previous Part | |

---

## File Operations

| Shortcut | Action | Notes |
|---|---|---|
| `Ctrl+N` | New File (Explorer) | Custom — works when Explorer focused |
| `Ctrl+Shift+N` | New Folder (Explorer) | Custom — works when Explorer focused |
| `Ctrl+O` | Open File | Vim override disabled |
| `Ctrl+S` | Save | Vim override disabled |
| `Ctrl+Shift+S` | Save As | |
| `Ctrl+K S` | Save Without Formatting | |
| `Ctrl+K Ctrl+O` | Open Folder | |
| `Ctrl+W` | Close Editor | Vim override disabled — back to VSCode |

---

## Editing

| Shortcut | Action | Notes |
|---|---|---|
| `Ctrl+C` | Copy | Vim override disabled |
| `Ctrl+X` | Cut | Vim override disabled |
| `Ctrl+V` | Paste | Vim override disabled |
| `Ctrl+A` | Select All | Vim override disabled |
| `Ctrl+Z` | Undo | |
| `Ctrl+Y` / `Ctrl+Shift+Z` | Redo | |
| `Ctrl+/` | Toggle Line Comment | |
| `Ctrl+Shift+A` | Toggle Block Comment | |
| `Alt+Up/Down` | Move Line Up/Down | |
| `Ctrl+Shift+Alt+Up/Down` | Copy Line Up/Down | |
| `Ctrl+Shift+K` | Delete Line | |
| `Ctrl+Enter` | Insert Line Below | |
| `Ctrl+Shift+Enter` | Insert Line Above | |
| `Ctrl+]` / `Ctrl+[` | Indent / Outdent Line | |
| `Ctrl+Shift+I` | Format Document | |
| `Ctrl+K Ctrl+F` | Format Selection | |
| `Alt+Z` | Toggle Word Wrap | |
| `Ctrl+D` | Add Selection to Next Find Match | |
| `Ctrl+Shift+L` | Select All Occurrences of Find Match | |
| `Ctrl+F2` | Change All Occurrences | |

---

## Multi-Cursor & Selection

| Shortcut | Action | Notes |
|---|---|---|
| `Ctrl+Shift+Up` / `Shift+Alt+Up` | Add Cursor Above | |
| `Ctrl+Shift+Down` / `Shift+Alt+Down` | Add Cursor Below | |
| `Shift+Alt+I` | Add Cursors to End of Each Line Selected | |
| `Ctrl+U` | Undo Last Cursor | |
| `Shift+Alt+Left/Right` | Shrink / Expand Selection | |
| `Ctrl+L` | Select Entire Line | |

---

## Search & Replace

| Shortcut | Action | Notes |
|---|---|---|
| `Ctrl+F` | Find in File | Vim override disabled |
| `Ctrl+H` | Find & Replace in File | |
| `Ctrl+Shift+F` | Find in Files (Search Panel) | |
| `Ctrl+Shift+H` | Replace in Files | |
| `F3` / `Shift+F3` | Next / Previous Find Result | |
| `Alt+Enter` | Select All Matches | |
| `Alt+C` | Toggle Case Sensitive (in Find) | |
| `Alt+W` | Toggle Whole Word (in Find) | |
| `Alt+R` | Toggle Regex (in Find) | |

---

## Code Intelligence

| Shortcut | Action | Notes |
|---|---|---|
| `F12` | Go to Definition | |
| `Ctrl+F12` | Go to Implementation | |
| `Shift+F12` | Find All References | |
| `Shift+Alt+F12` | Find References (References View) | |
| `Ctrl+K F12` | Open Definition to Side | |
| `Ctrl+Shift+F10` | Peek Definition | |
| `F2` | Rename Symbol | |
| `Ctrl+.` | Quick Fix / Code Action | |
| `Ctrl+Shift+R` | Refactor | |
| `Ctrl+Space` | Trigger Suggest | |
| `Ctrl+Shift+Space` | Trigger Parameter Hints | |
| `Ctrl+K Ctrl+I` | Show Hover | |
| `Shift+Alt+F12` | Go to References | |

---

## Navigation (Back/Forward & Errors)

| Shortcut | Action | Notes |
|---|---|---|
| `Ctrl+Alt+-` | Navigate Back | |
| `Ctrl+Shift+-` | Navigate Forward | |
| `F8` | Next Error/Warning | |
| `Shift+F8` | Previous Error/Warning | |
| `Alt+F8` | Next Error in File | |
| `Shift+Alt+F8` | Previous Error in File | |
| `Ctrl+Shift+M` | Toggle Problems Panel | |

---

## Editor Layout & Tabs

| Shortcut | Action | Notes |
|---|---|---|
| `Ctrl+\\` | Split Editor (Right) | |
| `Ctrl+K Ctrl+\\` | Split Editor (Down/Orthogonal) | |
| `Ctrl+W` | Close Editor / Group | Vim override disabled |
| `Ctrl+K W` | Close All Editors in Group | |
| `Ctrl+K Ctrl+W` | Close All Editors | |
| `Ctrl+Shift+T` | Reopen Closed Editor | |
| `Ctrl+PageDown/PageUp` | Next / Previous Editor | |
| `Ctrl+Tab` | Quick Open Previous Editor | |
| `Ctrl+Shift+Tab` | Quick Open Least Recently Used Editor | |
| `Alt+1-9` | Open Editor at Index | |
| `Ctrl+K Enter` | Keep (Pin) Editor | |
| `Ctrl+K Shift+Enter` | Pin / Unpin Editor | |
| `Ctrl+K Ctrl+Up/Down/Left/Right` | Move Focus Between Editor Groups | |

---

## Sidebar & Panels

| Shortcut | Action | Notes |
|---|---|---|
| `Ctrl+B` | Toggle Sidebar | Vim override disabled — works as VSCode |
| `Ctrl+J` | Toggle Panel (Bottom) | |
| `Ctrl+Alt+B` | Toggle Secondary Sidebar | Latex build override removed |
| `Ctrl+K Z` | Zen Mode | |
| `Ctrl+Shift+Y` | Toggle Debug Console | |
| `Ctrl+\`` | Toggle Terminal | |
| `Ctrl+Shift+\`` | New Terminal | |
| `Super + Ctrl + -> or <-` | Resize workbench |
| `Super + Ctrl + up or down` | Resize terminal |

---

## Terminal

| Shortcut | Action | Notes |
|---|---|---|
| `Ctrl+\`` | Toggle Integrated Terminal | |
| `Ctrl+Shift+\`` | New Terminal | |
| `Ctrl+Shift+5` | Split Terminal | |
| `Ctrl+Shift+C` | Copy Terminal Selection | |
| `Ctrl+Shift+V` | Paste into Terminal | |
| `Ctrl+PageDown/PageUp` | Next / Previous Terminal | |
| `Ctrl+F` | Find in Terminal | |
| `Ctrl+-> or <-` | Move between words in the terminal | |


---

## Folding

| Shortcut | Action | Notes |
|---|---|---|
| `Ctrl+Shift+[` | Fold Region | |
| `Ctrl+Shift+]` | Unfold Region | |
| `Ctrl+K Ctrl+0` | Fold All | |
| `Ctrl+K Ctrl+J` | Unfold All | |
| `Ctrl+K Ctrl+1-7` | Fold to Level 1–7 | |
| `Ctrl+K Ctrl+L` | Toggle Fold | |

---

## Debugging

| Shortcut | Action | Notes |
|---|---|---|
| `F5` | Start / Continue | |
| `Ctrl+F5` | Run Without Debugging | |
| `Shift+F5` | Stop | |
| `Ctrl+Shift+F5` | Restart | |
| `F9` | Toggle Breakpoint | |
| `F10` | Step Over | |
| `F11` | Step Into | |
| `Shift+F11` | Step Out | |

---

## Git / Source Control

| Shortcut | Action | Notes |
|---|---|---|
| `Ctrl+Shift+G` | Open Source Control | |
| `Ctrl+Enter` | Commit (SCM input focused) | |
| `Alt+F5` / `Shift+Alt+F5` | Next / Previous Change (diff) | |

---

## Copilot / AI

| Shortcut | Action | Notes |
|---|---|---|
| `Ctrl+Alt+I` | Open Copilot Chat | |
| `Ctrl+I` | Inline Chat (in editor) | |
| `Ctrl+Enter` | Submit with Codebase | |

---

## Vim Mode Reference (Active)

> Vim extension is enabled. The following **Ctrl overrides have been DISABLED** — these keys behave as standard VSCode, not Vim:
>
> `Ctrl+W`, `Ctrl+B`, `Ctrl+K`, `Ctrl+O`, `Ctrl+A`, `Ctrl+C`, `Ctrl+V`, `Ctrl+X`, `Ctrl+P`, `Ctrl+S`, `Ctrl+F`

| Vim Shortcut | Action | Mode |
|---|---|---|
| `j/k/h/l` | Move Down/Up/Left/Right | Normal |
| `w/b/e` | Word Forward / Back / End | Normal |
| `gg` / `G` | Go to Top / Bottom | Normal |
| `dd` | Delete Line | Normal |
| `yy` | Yank (Copy) Line | Normal |
| `p / P` | Paste After / Before | Normal |
| `u` / `Ctrl+R` | Undo / Redo | Normal |
| `i / I` | Insert at cursor / line start | Normal |
| `a / A` | Append at cursor / line end | Normal |
| `o / O` | New line below / above | Normal |
| `v / V` | Visual / Visual Line | Normal |
| `Ctrl+V` | Visual Block | Normal — **NOTE: disabled as VSCode paste** |
| `/` | Search forward | Normal |
| `n / N` | Next / Previous search result | Normal |
| `ci" / ci(` | Change inside quotes/parens | Normal |
| `%` | Jump to matching bracket | Normal |
| `:w` | Save (via command line) | Normal |
| `:q` | Quit/Close editor | Normal |
| `Escape` | Return to Normal Mode | Insert/Visual |

---

## Emulating These Bindings Elsewhere

| Editor | Notes |
|---|---|
| **Neovim/Vim** | Use the same Vim bindings natively. Map `<C-p>` → file picker (telescope), `<C-s>` → save, `<C-f>` → find, `<C-b>` → sidebar/explorer toggle |
| **JetBrains IDEs** | Install IdeaVim. Most `Ctrl+*` actions map 1:1. Use `Ctrl+Shift+A` (Find Action) as Command Palette equivalent |
| **Zed** | Vim mode available. `Ctrl+P` → file picker, `Ctrl+Shift+P` → commands. Most bindings overlap |
| **Emacs** | Install evil-mode for Vim layer. Remap `C-p`, `C-s`, etc. as needed |
| **Sublime Text** | Vintage mode for Vim. `Ctrl+P` file picker identical |

--- 

## Tasks 

We can run **task** in VSCode which let us run scripts and commands in the terminal. We can create a task by creating a `tasks.json` file in the `.vscode` folder.

```json 
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "echo",
            "type": "shell",
            "command": "echo Hello"
        }
    ]
}
```