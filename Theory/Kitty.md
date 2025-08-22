# Kitty Terminal - Keyboard Shortcuts

Kitty is a fast, GPU-based terminal emulator with powerful features. Here’s a list of its most useful keyboard shortcuts.

---

## 🔧 General

| Shortcut                   | Action                                 |
|---------------------------|----------------------------------------|
| `Ctrl + Shift + Enter`    | Launch a new kitty window              |
| `Ctrl + Shift + Space`    | Launch a new kitty overlay             |
| `Ctrl + Shift + Q`        | Quit the current kitty window          |
| `Ctrl + Shift + N`        | Set window/tab title                   |

---

## 🗂️ Tabs

| Shortcut                   | Action                                 |
|---------------------------|----------------------------------------|
| `Ctrl + Shift + T`        | New tab                                |
| `Ctrl + Shift + W`        | Close current tab                      |
| `Ctrl + Shift + Left/Right` | Move to previous/next tab             |
| `Ctrl + Shift + [` or `]` | Switch tabs left/right                 |

---

## 🪟 Windows (Splits)

| Shortcut                   | Action                                 |
|---------------------------|----------------------------------------|
| `Ctrl + Shift + Enter`    | New window (split horizontally)        |
| `Ctrl + Shift + \`        | New window (split vertically)          |
| `Ctrl + Shift + X`        | Close current window (split)           |
| `Ctrl + Shift + Arrow Keys` | Move focus to another window         |
| `Ctrl + Shift + =/-`      | Increase/decrease window size          |

---

## 🧭 Navigation

| Shortcut                   | Action                                 |
|---------------------------|----------------------------------------|
| `Ctrl + Shift + F`        | Find text (search)                     |
| `Ctrl + Shift + Up/Down`  | Scroll up/down one line                |
| `Ctrl + Shift + PageUp/PageDown` | Scroll by full screen            |

---

## 📋 Copy & Paste

| Shortcut                   | Action                                 |
|---------------------------|----------------------------------------|
| `Ctrl + Shift + C`        | Copy selected text                     |
| `Ctrl + Shift + V`        | Paste clipboard content                |

---

## ⚙️ Configuration

Kitty shortcuts can be customized in its config file:

```bash
~/.config/kitty/kitty.conf
````

For example, to remap copy and paste:

```conf
map ctrl+shift+c copy_to_clipboard
map ctrl+shift+v paste_from_clipboard
```

---

## 📚 More Resources

* [Kitty Docs](https://sw.kovidgoyal.net/kitty/)
* `kitty --help`
* `kitty +kitten help`

---

```

