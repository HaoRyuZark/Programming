# Vim Cheatsheet

## Modes 

- **Normal Mode:** Navigation
- **Insert Mode:** Modify 
- **Visual Mode:** Select
- **Command Mode:** Commands

## Navigation

- h → Move left
- l → Move right
- j → Move down
- k → Move up
- w → Jump to the start of the next word
- e → Jump to the end of the current/next word
- b → Jump to the start of the previous word
- gg → Go to the beginning of the file
- G → Go to the end of the file
- 0 → Move to the beginning of the line
- ^ → Move to the first non-blank character of the line
- $ → Move to the end of the line
- H → Move to the top of the screen
- M → Move to the middle of the screen
- L → Move to the bottom of the screen
- Ctrl-d → Scroll down half a screen
- Ctrl-u → Scroll up half a screen
- Ctrl-f → Scroll down a full screen
- Ctrl-b → Scroll up a full screen
- zz → Center current line in the screen
- zt → Move the current line to the top of the screen
- zb → Move the current line to the bottom of the screen
- nG → Go to line number n

## Copy, Cut, Paste

- yy → Yank (copy) the current line
- nyy → Yank n lines
- y$ → Yank from the cursor to the end of the line
- yw → Yank a word
- yG → Yank from the cursor to the end of the file
- p → Paste after the cursor
- P → Paste before the cursor
- dd → Delete (cut) the current line
- ndd → Delete (cut) n lines
- d$ → Delete from cursor to the end of the line
- dw → Delete a word
- dG → Delete from the cursor to the end of the file
- D → Delete from cursor to end of the line (same as d$)
- x → Delete (cut) a single character
- X → Delete (cut) a character before the cursor

## Delete Without Yanking

- _d → Delete without saving to register (e.g., _dd deletes a line without yanking)
- "__d → Another way to delete without yanking

## Undo and Redo

- u → Undo last change
- Ctrl-r → Redo last undone change

## Search

- /pattern → Search forward for pattern
- ?pattern → Search backward for pattern
- n → Repeat last search forward
- N → Repeat last search backward
- * → Search forward for the word under cursor
- \# → Search backward for the word under cursor

## Search and Replace

- :%s/old/new/g → Replace all occurrences of "old" with "new" in the entire file
- :s/old/new/g → Replace all occurrences of "old" with "new" in the current line
- :%s/old/new/gc → Replace all occurrences with confirmation
- :5,10s/old/new/g → Replace occurrences in lines 5-10

## Splits (Windows)

- :sp → Split window horizontally
- :vsp → Split window vertically
- Ctrl-w w → Switch between splits
- Ctrl-w h → Move to left split
- Ctrl-w l → Move to right split
- Ctrl-w j → Move to lower split
- Ctrl-w k → Move to upper split
- Ctrl-w = → Equalize split sizes
- Ctrl-w q → Close current split
- Ctrl-w o → Close all other splits

## Open Terminal

- :terminal → Open a terminal window
- Ctrl-w N → Switch to Normal mode inside the terminal
- Ctrl-\ Ctrl-n → Exit terminal insert mode
- exit → Exit the terminal

## Multiple Line Input

- o → Insert a new line below the cursor
- O → Insert a new line above the cursor
- i → Insert at the cursor position
- I → Insert at the beginning of the line
- a → Append after the cursor
- A → Append at the end of the line
- :start,end normal command → Execute normal mode commands on multiple lines (e.g., :1,10 normal I# comments lines 1-10)

## Visual Mode

- v → Start visual mode (character-wise selection)
- V → Start visual line mode (line-wise selection)
- Ctrl-v → Start visual block mode
- y → Yank selection
- d → Delete selection
- > → Indent selection
- < → Unindent selection
- = → Auto-format selection

## Tabs

- :tabnew → Open a new tab
- gt → Go to next tab
- gT → Go to previous tab
- :tabn → Go to next tab
- :tabp → Go to previous tab
- :tabclose → Close current tab
- :tabonly → Close all other tabs

## Marks and Jumps

- m{a-z} → Mark current position with a letter (e.g., ma)
- \'a → Jump to the line of mark a
- \`a → Jump to the exact position of mark a
- Ctrl-o → Jump to the older cursor position
- Ctrl-i → Jump to the newer cursor position

## Registers (Clipboard)

- "ayy → Yank line into register a
- "ap → Paste from register a
- "+y → Yank to system clipboard
- "+p → Paste from system clipboard

## Indentation

- \>\> → Indent current line
- << → Unindent current line
- = → Auto-indent current line
- V= → Auto-indent a selected block
- gg=G → Auto-indent entire file

## Miscellaneous

- . → Repeat the last command
- J → Join lines
- :w → Save file
- :q → Quit
- :q! → Quit without saving
- :wq → Save and quit
- ZZ → Save and quit
- ZQ → Quit without saving
- :e filename → Open a file
- :r filename → Insert the contents of another file
- :!command → Execute a shell command (e.g., :!ls)
- :set number → Show line numbers
- :set relativenumber → Show relative line numbers
- :set nohlsearch → Remove search highlight
- :help user manual | only -> open the manual in fullscreen
- Ctr + ] to go to the hovered selection
- Ctr + O to exit the section
- :Tutor -> starts the tutor
- :Explore -> see files and directories. Press enter to go to the target



Here's a Markdown file that documents **[lazy.nvim](https://github.com/folke/lazy.nvim)** — a fast, modern plugin manager for **Neovim**. It includes sections on what Lazy is, how to install and use it, the structure of the config, and common commands.

---

# lazy.nvim — Modern Plugin Manager for Neovim

[lazy.nvim](https://github.com/folke/lazy.nvim) is a **modern, fast, and feature-rich** plugin manager for Neovim (>= 0.8). It supports lazy-loading, event-driven plugin loading, performance profiling, and more.

---

## Installation

You can install `lazy.nvim` by cloning it into the `~/.config/nvim/lazy` directory or using the following command:

```lua
-- ~/.config/nvim/init.lua or ~/.config/nvim/lua/init.lua

-- Bootstrap lazy.nvim
local lazypath = vim.fn.stdpath("data") .. "/lazy/lazy.nvim"
if not vim.loop.fs_stat(lazypath) then
  vim.fn.system({
    "git", "clone", "--filter=blob:none",
    "https://github.com/folke/lazy.nvim.git",
    "--branch=stable", -- latest stable release
    lazypath,
  })
end
vim.opt.rtp:prepend(lazypath)

-- Load your plugins
require("lazy").setup("plugins") -- 'plugins' is the module with your plugin list
````

---

## 📁 Plugin Configuration Structure

The plugin list is usually stored in `lua/plugins/` as separate Lua files or a single file.

Example structure:

```
~/.config/nvim/
├── init.lua
└── lua/
├── plugins/
│   ├── init.lua     <-- calls `lazy.setup()`
│   ├── lsp.lua
│   ├── treesitter.lua
│   └── telescope.lua
```

Each file in `lua/plugins/` returns a plugin spec or a list of specs:

```lua
-- lua/plugins/telescope.lua
return {
  {
    "nvim-telescope/telescope.nvim",
    dependencies = { "nvim-lua/plenary.nvim" },
    cmd = "Telescope",
    keys = {
      { "<leader>ff", "<cmd>Telescope find_files<cr>", desc = "Find Files" },
    },
    config = function()
      require("telescope").setup()
    end,
  },
}
```

---

## 🚀 Usage

### Adding Plugins

Add plugin specs to a file inside `lua/plugins/`:

```lua
-- lua/plugins/lualine.lua
return {
  {
    "nvim-lualine/lualine.nvim",
    config = function()
      require("lualine").setup()
    end,
    event = "VimEnter", -- lazy-load on startup event
  }
}
```

### Lazy Loading Options

You can use many triggers to lazy-load plugins:

* `event` — e.g., `"BufRead"`, `"InsertEnter"`
* `cmd` — plugin loads on command
* `keys` — loads on keypress
* `ft` — loads on filetype
* `dependencies` — plugin dependencies

---

## Common Commands

Once `lazy.nvim` is set up, use the following commands in Neovim:

| Command         | Description                   |
| --------------- | ----------------------------- |
| `:Lazy`         | Open Lazy's UI dashboard      |
| `:Lazy install` | Install plugins               |
| `:Lazy update`  | Update plugins                |
| `:Lazy sync`    | Install + clean + update      |
| `:Lazy clean`   | Remove unused plugins         |
| `:Lazy restore` | Restore plugins from lockfile |
| `:Lazy profile` | Show startup time profiling   |
| `:Lazy log`     | Show plugin load logs         |

---

## Tips

* Use `config = function()` to configure plugins.
* Use `opts = {}` to pass options directly to plugins that support `opts`.
* For large setups, split plugins across multiple files under `lua/plugins/`.
* Run `:Lazy profile` to optimize your config.

---

## Example Plugin Spec

```lua
-- lua/plugins/example.lua
return {
  {
    "lewis6991/gitsigns.nvim",
    event = "BufReadPre",
    opts = {
      signs = {
        add = { text = "+" },
        change = { text = "~" },
        delete = { text = "_" },
      },
    },
  },
}
```

---








