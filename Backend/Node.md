# Node JS

**Node JS** is a JavaScript runtime with the purpose of allowing JavaScript to run in the backend.
It uses an **even-driven** architecture with a single thread and the well-known event-loop.

Instead of lunching a new thread or process per connection an even-loop is used with an **event-queue** and the heavy-work 
is delegated to OS in a callback using a C++ thread-pool.

There are also alternative methods of using the thread-pool to launch the Node instance.

---- 

## npm

**npm** is the package manager for JavaScript and Node.js. It installs packages from the npm registry.

```bash
# Initialize a new project
npm init          # interactive wizard
npm init -y       # auto-accept all defaults

# Installing packages
npm install lodash            # production dependency
npm install --save-dev jest   # dev dependency (testing, build tools)
npm install -g typescript     # global (available as CLI command)
npm install                   # install all deps from package.json

# Removing
npm uninstall lodash

# Running scripts (defined in package.json)
npm run start
npm run build
npm run test
npm test          # shorthand for `npm run test`

# Viewing
npm list                 # installed packages (local)
npm list -g --depth=0    # global packages
npm outdated             # check for updates
npm update               # update all packages

# Registry and publishing
npm login
npm publish
npm version patch  # bump version: 1.0.0 → 1.0.1
npm version minor  # bump version: 1.0.0 → 1.1.0
npm version major  # bump version: 1.0.0 → 2.0.0
```

**`package.json`** — project manifest:

```json

{
  "name": "my-app",
  "version": "1.0.0",
  "description": "A sample app",
  "main": "index.js",
  "scripts": {
    "start": "node index.js",
    "dev": "nodemon index.js",
    "build": "tsc",
    "test": "jest"
  },
  "dependencies": {
    "express": "^4.18.2"
  },
  "devDependencies": {
    "jest": "^29.0.0",
    "typescript": "^5.0.0"
  },
  "engines": {
    "node": ">=18.0.0"
  }
}
```

**Version specifiers:**
- `^1.2.3` — compatible with `1.x.x` (most common)
- `~1.2.3` — compatible with `1.2.x`
- `1.2.3`  — exact version
- `*`      — any version (dangerous)

**`package-lock.json`** — locks exact resolved versions; commit to version control for reproducible installs.


### Importing Dependencies

**Old**:

```js 
let express = requiere('express')
```

**New**:

```js 
import { express } from { "express" }
import { express } from "express"
```

--- 

## HTTP 




--- 

## File System (Node.js)

```js
const fs   = require("fs");
const path = require("path");

// Synchronous (blocking — simple scripts only)
const data = fs.readFileSync("file.txt", "utf-8");
fs.writeFileSync("output.txt", "Hello!\n");
fs.appendFileSync("log.txt", "New entry\n");

// Asynchronous with callbacks
fs.readFile("file.txt", "utf-8", (err, data) => {
  if (err) throw err;
  console.log(data);
});

// Asynchronous with promises (modern — prefer this)
const fsp = require("fs/promises");

async function readAndWrite() {
  const content = await fsp.readFile("input.txt", "utf-8");
  const lines   = content.split("\n").filter(Boolean);
  await fsp.writeFile("output.txt", lines.join("\n"));
}

// Directory operations
fs.mkdirSync("new-folder", { recursive: true });
const entries = fs.readdirSync("./");        // list directory
fs.existsSync("file.txt");                   // check existence
fs.statSync("file.txt").size;                // file size in bytes
fs.unlinkSync("file.txt");                   // delete file
fs.renameSync("old.txt", "new.txt");         // rename / move

// Path utilities
path.join("src", "utils", "helper.js"); // "src/utils/helper.js"
path.resolve("./file.txt");             // absolute path
path.basename("/foo/bar/file.txt");     // "file.txt"
path.dirname("/foo/bar/file.txt");      // "/foo/bar"
path.extname("file.txt");               // ".txt"
path.parse("/foo/bar/file.txt");
// { root: '/', dir: '/foo/bar', base: 'file.txt', ext: '.txt', name: 'file' }
```

--- 

## Process Arguments (Node.js)

```js
// node script.js arg1 arg2 --flag
process.argv;         // ["node", "/path/script.js", "arg1", "arg2", "--flag"]
process.argv.slice(2); // ["arg1", "arg2", "--flag"] — actual user args

// Parsing named arguments manually
const args = process.argv.slice(2);
const flags = {};
for (let i = 0; i < args.length; i++) {
  if (args[i].startsWith("--")) {
    const key = args[i].slice(2);
    flags[key] = args[i + 1]?.startsWith("--") ? true : args[++i];
  }
}
// node script.js --name Alice --verbose
// flags = { name: "Alice", verbose: true }

// Environment variables
const port = process.env.PORT || 3000;
const env  = process.env.NODE_ENV || "development";

// Exit
process.exit(0);  // success
process.exit(1);  // error
```


### User Input From The Console (Node.js)

```js
// readline — built-in module
const readline = require("readline");

const rl = readline.createInterface({
  input:  process.stdin,
  output: process.stdout
});

// Single question
rl.question("What is your name? ", (answer) => {
  console.log(`Hello, ${answer}!`);
  rl.close();
});

// Async/await wrapper — much cleaner
function ask(question) {
  return new Promise((resolve) => {
    rl.question(question, resolve);
  });
}

async function main() {
  const name = await ask("Name: ");
  const age  = await ask("Age: ");
  console.log(`Hello ${name}, you are ${age} years old.`);
  rl.close();
}
main();
```

--- 

## Express 

### Request Handling 

### Routing


---

## Template Engines (Mustache.js)

The goal of a **template engine** is to separate the HTML from the Node.js-code. 

--- 


## Cookies & Sessions

A main problem about NodeJS is that variables and state in general gets lost once the script terminates; 
to solve this problem we use so called **cookies** and **sessions** to store this data across scripts inside 
the headers of our HTTP request and responses.

> Cookies store information on the client side, while sessions do it for the server side

**Cookie Example**: 

```http 
HTTP/1.1 200 OK
Content-type: text/html
Set-Cookie: name=value
Set-Cookie: foo=bar; Expires=Wed, 09 Jun 2021 10:18:14 GMT
...
```

Using express, we can achive this behavior via 

```js 
res.cookie('name', 'value' [‚ options])
```

Example: 

```js
res.cookie('rememberme', '1',
{ expires: new Date(Date.now() + 900000),
path: '/' })
```

**Session Example**:

```js 
app.use(session({
    secret: 'ilovenode',
    cookie: { secure: true,
    domain:'yourdomain.com'},
  }
})
```


---- 

## Websockets


--- 


## Sequelize.js

--- 




