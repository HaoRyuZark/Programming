# Vim Cheatsheets

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



