# Dadbod

## Using vim-dadbod and vim-dadbod-ui

The **vim-dadbod** plugin by [Tim Pope](https://github.com/tpope) enables powerful, database-aware workflows inside Vim or Neovim. Combined with **[vim-dadbod-ui](https://github.com/kristijanhusak/vim-dadbod-ui)**, it provides an intuitive interface for exploring databases, running queries, and inspecting results — all from within your editor.

---

### Connecting to a Database

You can connect to any supported database by specifying a connection string:

```
:DB [adapter]://[user[:password]@][host][:port]/[database]
```

**Examples:**

```vim
:DB mysql://root@localhost/employees
:DB postgresql://user:secret@localhost:5432/inventory
:DB sqlite:./mydata.sqlite
```

Dadbod supports multiple drivers including PostgreSQL, MySQL, SQLite, and others through your system’s native CLI clients.

---

### Exploring with Dadbod UI

Once you have a connection configured, the **Dadbod UI** (`vim-dadbod-ui`) provides a visual interface for managing your databases.

Open it using:

```vim
:DBUI
```

This launches a sidebar-like view showing your database connections, schemas, and tables. From there you can:

| Action  | Description                                         |
| ------- | --------------------------------------------------- |
| `Enter` | Expand or collapse a node (e.g., schemas or tables) |
| `o`     | Open a table or view definition                     |
| `S`     | Switch between saved connections                    |
| `R`     | Refresh the database tree                           |
| `q`     | Close the DBUI window                               |

---

### Viewing and Running Queries

Within Dadbod UI or a `.sql` buffer, you can open query buffers and execute SQL directly.

**To open a new query window:**

```
:DBUIFindBuffer
```

or simply open a new SQL file and connect it via:

```
:DB [connection_name]
```

**To execute queries:**

```vim
:DBExec
```

* Executes the entire buffer if nothing is selected.
* Executes only the selected SQL if used in visual mode (`:'<,'>DBExec`).
* Results are displayed in a split window below the query.

---

### Managing Connections in DBUI

You can define multiple connections and switch between them easily:

* **Add a connection:**

  ```
  :DBUIAddConnection
  ```

* **Rename a connection:**

  ```
  :DBUIRenameBuffer
  ```

* **Delete or refresh connections:**
  Navigate to a connection in `:DBUI` and use the commands shown in the status line.

Dadbod UI can also automatically read connection details from environment variables or `.env` files if you use `vim-dotenv`.

---

### Pro Tips

* Use `:DBUI` as a database explorer and `:DBExec` for interactive SQL execution.
* For larger queries, keep results in a vertical split using:

  ```vim
  :vertical DBExec
  ```
* Combine `vim-dadbod-ui` with `vim-dadbod-completion` to get SQL autocompletion in query buffers.
* Results are temporary — if you close the results window, you can rerun the query anytime.

---




