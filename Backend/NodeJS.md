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
  "name": "my-app",                 // package name (must be unique in npm registry)
  "version": "1.0.0", 
  "description": "A sample app",
  "main": "index.js",               // entry point
  "type": "module",                 // use ES6 modules (import/export)
  "scripts": {                      // npm scripts
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

## Node Commands

```bash
# Run a script
node script.js

# Run a script with automatic restart on file changes
npx nodemon script.js
```

--- 

## Node.js Modules

In Node.js, a **module** is a reusable piece of code that can be imported and used in other parts of your application. 
Node.js has a built-in module system based on the CommonJS specification.

- Common JS modules use the `require()` function to import modules and the `module.exports` object to export them.
- ES6 modules use the `import` and `export` syntax, which is more modern and widely adopted in the JavaScript ecosystem.

To export our own modules we can use the `module.exports` object or the `exports` shorthand. 

```js
// math.js
function add(a, b) {
  return a + b;
}

function subtract(a, b) {
  return a - b;
}

module.exports = { add, subtract }; // or module.exports =  add; for a single export
```
In the modern ES6 syntax we can use the `export` keyword:

```js
// math.js
export function add(a, b) {
  return a + b;
}
export function subtract(a, b) {
  return a - b;
}

//default export
export default function multiply(a, b) {
  return a * b;
}
```

--- 

## HTTP (http)

This a module used to create a web server and handle HTTP requests and responses. There are multiple frameworks built on top of this module, like **Express.js**.

Simple example of a HTTP server using the built-in `http` module:


```js
import http from "http";

const server = http.createServer((req, res) => {

  res.writeHead(200, {"Content-Type": "text/plain"});
  res.end("<h1>Hello, World!</h1>");
});

server.listen(3000, () => {
  console.log("Server running at http://localhost:3000/");
});
```

### The Request Object

The `req` object represents the incoming HTTP request and has properties for the request query string, parameters, body, HTTP headers, and more.

Commonly used properties and methods of the `req` object:

- `req.url`: the URL of the request.

- `req.method`: the HTTP method of the request (e.g., GET, POST).

- `req.headers`: the HTTP headers of the request.

- `req.on('data', callback)`: listen for incoming data chunks (for POST requests).

- `req.on('end', callback)`: listen for the end of the request data.

- `req.query`: an object containing the query string parameters (if using a framework like Express). 

- `res.writeHead(statusCode, headers)`: sets the HTTP status code and response headers.

- `res.write(body)`: writes data to the response body (can be called multiple times before `res.end()`).
  - `body` can be a string, Buffer, or any other data type that can be converted to a string.

- `res.end(body)`: sends the response body and ends the response.


```js

const server = http.createServer(((req, res) => {

  // Routing based on request method and URL
  if (req.method === "GET" && req.url === "/") {

    res.writeHead(200, { "Content-Type": "text/html" });
    res.end("<h1>Hello, World!</h1>");
  }

  // The routing can be handled with a switch statement or a routing library like Express.js for more complex applications.

}));
```


### Server Methods

- `http.createServer((req, res) => { ... })`: creates an HTTP server instance. It also starts the event loop and begins accepting incoming connections.
  - `req`: the incoming request object.
  - `res`: the outgoing response object.

- `server.listen(port, () => { ... })`: starts the server and listens on the specified port and executes the callback when the server is ready.

- `server.close(() => { ... })`: stops the server from accepting new connections and executes the callback when the server is closed.

- `server.on('event', callback)`: listens for server events (e.g., 'request', 'connection', 'close').

--- 

## URL Module (url)

The `url` module provides utilities for URL resolution and parsing. It can be used to parse URLs, format URLs, and resolve relative URLs.

- `url.parse(urlString, parseQueryString, slashesDenoteHost)`: parses a URL string into an object.

- `url.format(urlObject)`: formats a URL object into a URL string.

- `url.resolve(from, to)`: resolves a target URL relative to a base URL.

- `url.fileURLToPath(url)`: converts a file URL to a file path (useful for ES6 modules).  

- `url.pathToFileURL(path)`: converts a file path to a file URL.


```js
import url from "url";

// Getting the current file and directory paths in ES6 modules
const __filename = url.fileURLToPath(import.meta.url);
const __dirname  = url.fileURLToPath(new URL(".", import.meta.url));

// Better with path 
const __dirname = path.dirname(__filename);

// Returns an object with the following properties: href, protocol, host, hostname, port, pathname, search, query, hash
url.parse("https://example.com/path?name=John&age=30#section");

// Formats a URL object into a URL string
url.format({
  protocol: "https",
  hostname: "example.com",
  pathname: "/path",
  query: { name: "John", age: 30 },
  hash: "#section"
});

// Resolves a target URL relative to a base URL
url.resolve("https://example.com/path/", "../newpath"); // "https://example.com/newpath"

// Converts a file URL to a file path
url.fileURLToPath("file:///C:/path/to/file.txt"); // "C:\\path\\to\\file.txt"

```

--- 

## Path Module (path)

The `path` module provides utilities for working with file and directory paths. It can be used to manipulate file paths, join paths, 
resolve absolute paths, and extract path components.

- `path.join(...paths)`: joins multiple path segments into a single path.

- `path.resolve(...paths)`: resolves a sequence of paths into an absolute path.

- `path.basename(path)`: returns the last portion of a path.

- `path.dirname(path)`: returns the directory name of a path.

- `path.extname(path)`: returns the extension of the path.

- `path.parse(path)`: returns an object with the root, dir, base, ext, and name of the path.

- `path.dirname(path)`: returns the directory name of a path.

- `path.relative(from, to)`: returns the relative path from one path to another.

```js 
const path = require("path");
// Path utilities
path.join("src", "utils", "helper.js"); // "src/utils/helper.js"

path.resolve("./file.txt");             // absolute path

path.basename("/foo/bar/file.txt");     // "file.txt"

path.dirname("/foo/bar/file.txt");      // "/foo/bar"

path.extname("file.txt");               // ".txt"

path.parse("/foo/bar/file.txt");        // { root: '/', dir: '/foo/bar', base: 'file.txt', ext: '.txt', name: 'file' }
```

--- 

## File System (fs) 

This module provides an API for interacting with the file system in a manner closely modeled around standard POSIX functions.

- `fs.readFileSync(path, options)`: reads a file synchronously (blocking).

- `fs.readFile(path, options, callback)`: reads a file asynchronously (non-blocking).

- `fs.writeFileSync(path, data, options)`: writes data to a file synchronously (blocking).

- `fs.writeFile(path, data, options, callback)`: writes data to a file asynchronously (non-blocking).

- `fs.appendFileSync(path, data, options)`: appends data to a file synchronously (blocking).

- `fs.appendFile(path, data, options, callback)`: appends data to a file asynchronously (non-blocking).

- `fs.mkdirSync(path, options)`: creates a directory synchronously (blocking).

- `fs.mkdir(path, options, callback)`: creates a directory asynchronously (non-blocking).

- `fs.readdirSync(path, options)`: reads the contents of a directory synchronously (blocking).

- `fs.readdir(path, options, callback)`: reads the contents of a directory asynchronously (non-blocking).

- `fs.existsSync(path)`: checks if a file or directory exists synchronously (blocking).

- `fs.existsSync("file.txt")`: checks if a file exists synchronously (blocking).

- `fs.statSync("file.txt").size`: gets the file size in bytes synchronously (blocking).

- `fs.unlinkSync("file.txt")`: deletes a file synchronously (blocking).

- `fs.renameSync("old.txt", "new.txt")`: renames or moves a file synchronously (blocking).

```js
const fs   = require("fs");

// Synchronous (blocking — simple scripts only)
const data = fs.readFileSync("file.txt", "utf-8");

fs.writeFileSync("output.txt", "Hello!\n");
fs.appendFileSync("log.txt", "New entry\n");

// Asynchronous with callbacks
fs.readFile("file.txt", "utf-8", (err, data) => {
  if (err) throw err;
  console.log(data);
});
```

We can also use the promised-based API for the `fs` module, which is available in Node.js 10 and later. 
This allows us to use `async/await` syntax for file operations, making the code cleaner and easier to read.

```js
// Asynchronous with promises (modern — prefer this)
const fsp = require("fs/promises");

async function readAndWrite() {
  const content = await fsp.readFile("input.txt", "utf-8");
  const lines   = content.split("\n").filter(Boolean);
  await fsp.writeFile("output.txt", lines.join("\n"));
}
```

--- 

## Process Arguments

- `process.argv` is an array containing the command-line arguments passed when the Node.js process was launched.

- `process.env` is an object containing the user environment variables.
  - `env.PORT` is commonly used to specify the port number for a web server.
  - `env.NODE_ENV` is commonly used to specify the environment (e.g., "development", "production").
  - `env.PATH` is commonly used to specify the system path for executable files.

- `process.exit(code)` is a method to terminate the Node.js process with an exit code.

- `process.stdin` is a readable stream for standard input, allowing you to read user input from the console.


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

--- 

## Custom Router

Here an example of a simple custom router implementation in Node:

```js 
let url     = require("url");
let process = require("process");
let http    = require("http");
let fs      = require("fs");

let PORT = process.env.PORT || 3000; // getting the from the environment variables or defaulting to 3000

// Create the HTTP server and handle incoming requests
let server = http.createServer((req, res) => {

  let method = req.method;
  let parsedUrl = url.parse(req.url, true);

  switch (method) {
    case "GET":    handleGet(req, res, parsedUrl);      break;
    case "POST":   handlePost(req, res, parsedUrl);     break;
    case "PUT":    handlePut(req, res, parsedUrl);      break;
    case "PATCH":  handlePatch(req, res, parsedUrl);    break;
    case "DELETE": handleDelete(req, res, parsedUrl);   break;
    default:       handleNotFound(req, res, parsedUrl); break;
  }
})

// Start the server and listen on the specified port
server.listen(PORT, () => {
  console.log(`Server running at http://localhost:${PORT}/`);
});

function handleGet(req, res, parsedUrl) {

  if (req.url === "/") {
    res.writeHead(200, { "Content-Type": "text/plain" });
    res.end(fs.readFileSync("index.html", "utf-8"));
  } else if (req.url === "/api/users") {
    res.writeHead(200, { "Content-Type": "application/json" });
    res.end(JSON.stringify({ users: ["Alice", "Bob", "Charlie"] }));
  } else {
    handleNotFound(req, res, parsedUrl);
  } 
}

// You can implement the logic for the other functions
```

--- 

## Middleware

**Middleware** is a function that has access to the request object (`req`), the response object (`res`), and 
the next function in the application’s request-response cycle. 

Middleware functions can perform tasks such as executing code, modifying the request and response objects, ending the request-response cycle, or calling the next 
middleware function. It is basically a wrapper around the actual logic of the route handler.

- `func_name_middleware(req, res, next)`: a middleware function that takes three parameters: `req`, `res`, and `next`.
  - `req`: the request object.
  - `res`: the response object.
  - `next`: a function that, when called, passes control to the next middleware function in the stack.

```js
function logger(req, res, next) {
  console.log(`${req.method} ${req.url}`);
  next(); // Call the next middleware function
}

let server = http.createServer((req, res) => {

  let method = req.method;
  let parsedUrl = url.parse(req.url, true);

  // Use the logger middleware to log the request method and URL
  logger(req, res, () => {
    switch (method) {
      case "GET":    handleGet(req, res, parsedUrl);      break;
      case "POST":   handlePost(req, res, parsedUrl);     break;
      case "PUT":    handlePut(req, res, parsedUrl);      break;
      case "PATCH":  handlePatch(req, res, parsedUrl);    break;
      case "DELETE": handleDelete(req, res, parsedUrl);   break;
      default:       handleNotFound(req, res, parsedUrl); break;
    }
  });
});

```

--- 

## User Input From The Console

In node, we can use the built-in `readline` module to read user input from the console. 
This module provides an interface for reading data from a readable stream (such as `process.stdin`) one line at a time.

- `readline.createInterface(options)`: creates a new readline interface instance. The `options` object can specify the input and output streams.
  - `options.input`: the readable stream to read from (e.g., `process.stdin`).
  - `options.output`: the writable stream to write to (e.g., `process.stdout`).
  - `options.prompt`: the prompt string to display when waiting for input.

- `rl.question(query, callback)`: displays a query to the user and waits for input. The input is passed to the callback function.

- `rl.close()`: closes the readline interface, releasing the input and output streams.

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

## Crypto (crypto)

This a module which provides functionality for cryptography.

- `crypto.createHash(algorithm)`: creates a hash object that can be used to generate hash digests using the specified algorithm (e.g., "sha256", "md5").

- `crypto.createHmac(algorithm, key)`: creates an HMAC (Hash-based Message Authentication Code) object using the specified algorithm and secret key.

- `crypto.randomBytes(size, callback)`: generates cryptographically strong pseudo-random data of the specified size in bytes. 
- If a callback is provided, it will be called with the generated data; otherwise, it returns a Buffer.

- `crypto.scryptSync(password, salt, keylen)`: derives a key from a password and salt using the scrypt key derivation function.

- `crypto.createCipheriv(algorithm, key, iv)`: creates a cipher object for encryption using the specified algorithm, key, and initialization vector (IV).

- `crypto.encryptiv(algorithm, key, iv)`: creates a decipher object for decryption using the specified algorithm, key, and initialization vector (IV).

- `crypto.sign(algorithm, data, key)`: generates a digital signature for the given data using the specified algorithm and private key.

- `crypto.verify(algorithm, data, key, signature)`: verifies a digital signature for the given data using the specified algorithm and public key.

- `crypto.generateKeyPair(type, options, callback)`: generates a public-private key pair of the specified type (e.g., "rsa", "ec") and options.

- `crypto.generateKeyPairSync(type, options)`: generates a public-private key pair of the specified type and options synchronously.

```js 
const { createHash } = require('crypto');

function hash(input) {
    return createHash('sha256').update(input).digest('hex');
}

const { scryptSync, randomBytes } = require('crypto');

function getSalt(bytes, format) { 
    return randomBytes(bytes).toString(format);
}

function hash(input, salt, bytes, format) {
    return scryptSync(input, salt, bytes).toString(format);
}
```

--- 

## Express.js 

**Express.js** is a minimal and flexible Node.js web application framework which provides features for building API and web applications using the HTTP module.
It simplifies the process of handling requests, routing, middleware, and more.

Basic functions include:

- `app.listen(port, callback)`: starts the server and listens on the specified port.

- `app.get(path, callback)`: defines a route for GET requests to the specified path.

- `app.post(path, callback)`: defines a route for POST requests to the specified path.

- `app.put(path, callback)`: defines a route for PUT requests to the specified path.

- `app.delete(path, callback)`: defines a route for DELETE requests to the specified path.

- `app.use(middleware)`: adds a middleware function to the application.

- `express.static(root, options)`: serves static files from the specified root directory.

- `express.json()`: built-in middleware to parse incoming JSON request bodies.

- `express.urlencoded(options)`: built-in middleware to parse incoming URL-encoded request bodies.

Example:

```js
import express from "express";
// or
const express = require("express");
const app = express();

app.use(express.static("public")); // Middleware to serve static files

app.listen(3000, () => {
  console.log("Server running at http://localhost:3000/");
})

app.get("/", (req, res) => {
  res.send("<h1>Hello, World!</h1>");
});

app.get("/api/users", (req, res) => {
  res.json({ users: ["Alice", "Bob", "Charlie"] });
});

app.post("/api/users", (req, res) => {
 
  storeInDatabase(req.body); // Store the user data in the database
  res.json({ message: "User created" });
});

function storeInDatabase(data) {
  // Simulate storing data in a database
  console.log("Storing data:", data);
}
```

### Request & Response Objects 

The `req` and `res` objects are our interfaces to handle incoming and outgoing data. 

- `req.params`: an object containing route parameters (e.g., `/users/:id`).

- `req.query`: an object containing query string parameters (e.g., `/search?query=term`).

- `req.body`: an object containing the request body (for POST/PUT requests, requires body-parsing middleware).

- `req.headers`: an object containing the HTTP headers of the request.

- `req.method`: the HTTP method of the request (e.g., GET, POST).

- `res.status(code)`: sets the HTTP status code for the response.

- `res.send(body)`: sends a response body (can be a string, Buffer, or object).

- `res.json(object)`: sends a JSON response.

- `res.sendFile(path)`: sends a file as the response.

- `res.redirect(url)`: redirects the client to a different URL.

```js 
const express = require("express");
const app = express();

app.use(express.static("public")); // Serve static files from the "public" directory

app.get("/", (req, res) => {
  console.log(`Received a GET request to /: ${req.method} ${req.url}`);
  res.send("<h1>Hello, World!</h1>");
});

app.get("/api/users/:id", (req, res) => {
  const userId = parseInt(req.params.id);
  res.json({ user: { id: userId, name: "Alice" } });
  res.status(200).send(`User ID: ${userId}`);
});
```
### Query Parameters

**Query parameters** are a way to pass additional information to the server in the URL of a GET request.
The syntax for query parameters is `?key1=value1&key2=value2`, where each key-value pair is separated by an ampersand (`&`).
In Express, query parameters can be accessed via `req.query`. For example:

```js
app.get("/search", (req, res) => {
  const query = req.query.query;
  res.send(`You searched for: ${query}`);
});
```

### Middleware

Express provides a set of middleware functions that can be used to handle requests and responses. We can then 
instead of wrapping our functions as callbacks, use the `app.use()`  syntax to register middleware functions that will be executed for every request.

```js
// Example of a simple logging middleware
const logger = (req, res, next) => {
  console.log(`${req.method} ${req.url}`);
  next(); // Call the next middleware function
};

// Using the middleware for all routes
app.use(logger); 

// Using only on a specific route
app.get("/api/users", logger, (req, res) => {
  res.json({ users: ["Alice", "Bob", "Charlie"] });
});
```

Commonly, a middleware folder is created to store all the middleware functions, and they are imported and used in the main application file.

```js
// middleware/logger.js
const logger = (req, res, next) => {
  console.log(`${req.method} ${req.url}`);
  next(); // Call the next middleware function
};
module.exports = logger;
```

### Routing

**Routing** is the process of defining how an application responds to a client request to a particular endpoint, which is a URI (or path) 
and a specific HTTP request method (GET, POST, etc.). Express provides a simple router to define routes and handle requests. We can now 
define a file for each resource inside the `routes/` folder. ```js

To create dynamic parameters in the route, we can use the colon `:` syntax. For example, to define a route for getting a user by ID, we can use `/users/:id`, where `:id` is a dynamic parameter that will match any value in that position of the URL.

```txt
api/users/:id/:page
```

Define inside the `routes/` folder a file `resourceName.js` for each resource. For example, for users:

```js
// users.js
const express = require("express");
const router = express.Router();

router.get("/:id", (req, res) => {
  const userId = parseInt(req.params.id);
  res.json({ user: { id: userId, name: "Alice" } });
});

router.post("/", (req, res) => {
  // Handle user creation
  res.json({ message: "User created" });
});

router.put("/:id", (req, res) => {
  const userId = parseInt(req.params.id);
  // Handle user update
  res.json({ message: `User ${userId} updated` });
});

router.delete("/:id", (req, res) => {
  const userId = parseInt(req.params.id);
  // Handle user deletion
  res.json({ message: `User ${userId} deleted` });
});

export default router;
module.exports = router;
```

Then in the main `app.js` file, we can import and use the router:

```js
const express = require("express");
const app = express();
const userRouter = require("./routes/users"); 

// Middleware to parse JSON request bodies
app.use(express.json());                         // Middleware to parse JSON request bodies
app.use(express.urlencoded({ extended: true })); // Middleware to parse URL-encoded request bodies

// Mount the user routers
app.use("/api/users", userRouter); 
// ... other routers can be mounted similarly

app.listen(3000, () => {
  console.log("Server running at http://localhost:3000/");
});
```

Alternatively, for repeated routes, we can use

- `router.route(path)`: this chains multiple HTTP methods for the same route, making the code cleaner and more organized.
    - path: the route path (e.g., `/:id`).

```js
// routes/users.js
const express = require("express");
const router = express.Router();

import { getUserById, updateUser, deleteUser } from "../controllers/userController.js";

router.route("/:id")
  .get(getUserById)
  .put(updateUser)
  .delete(deleteUser);

module.exports = router;
```

- `router.param(name, callback)`: this is a middleware that is triggered when a route parameter is present in the URL. It can be used to validate or preprocess the parameter before reaching the route handler.
    - name: the name of the route parameter (e.g., `id`).
    - callback: a function that takes three arguments: `req`, `res`, and `next`. It can modify the request object or perform validation.

```js
// routes/users.js
const express = require("express");
const router = express.Router();

router.param("id", (req, res, next, id) => {
  const userId = parseInt(id);
  if (isNaN(userId)) {
    return res.status(400).json({ error: "Invalid user ID" });
  }
  req.userId = userId; // Store the parsed user ID in the request object
  next(); // Call the next middleware or route handler
});

module.exports = router;
```

### Controllers 

**Controllers** are responsible for handling the business logic of the application. They receive requests from the routes, process them, and 
return responses. They are not mandatory, but they help keep the code organized and maintainable. 

Returning to the previous example, we can create a `controllers/` folder and define a `userController.js` file:

```js
// controllers/userController.js
const getUserById = (req, res) => {
  const userId = parseInt(req.params.id);
  res.json({ user: { id: userId, name: "Alice" } });
};

const createUser = (req, res) => {
  // Handle user creation
  res.json({ message: "User created" });
};

const updateUser = (req, res) => {
  const userId = parseInt(req.params.id);
  // Handle user update
  res.json({ message: `User ${userId} updated` });
};

export default { getUserById, createUser, updateUser };
```

Now in the router file, we can import the controller functions and use them:

```js
// routes/users.js
const express = require("express");
const router = express.Router();
const userController = require("../controllers/userController");

router.get("/:id", userController.getUserById);
router.post("/", userController.createUser);
router.put("/:id", userController.updateUser);

module.exports = router;
```

And finally in the main `app.js` file, we can mount the router as before:

```js
const express = require("express");
const app = express();
const userRouter = require("./routes/users");

app.use(express.json());

app.use("/api/users", userRouter);  

app.listen(3000, () => {
  console.log("Server running at http://localhost:3000/");
});
```

## Template Engines (Mustache.js)

The goal of a **template engine** is to separate the HTML from the Node.js-code. They allows 
us to create dynamic HTML pages by embedding variables and logic into the HTML templates.

Example with **Mustache.js**:

```js 
const express = require("express");
const mustacheExpress = require("mustache-express");  
const app = express();

app.engine("mustache", mustacheExpress());

app.set("view engine", "mustache");
app.set("views", __dirname + "/views");

app.get("/", (req, res) => {
  res.render("index", { title: "Hello, World!", message: "Welcome to my website!" });
}); 

```

- `app.engine(ext, callback)`: registers a template engine with the specified file extension and callback function.

- `app.set("view engine", ext)`: sets the default template engine for rendering views.

- `app.set("views", path)`: sets the directory where the view templates are located.

- `res.render(view, options)`: renders a view template with the specified options and sends the rendered HTML as the response.

- `res.render(view, options, callback)`: renders a view template with the specified options and calls the callback function with the rendered HTML.

We declare our **views** folder and inside it we create our **.mustache** files. For example, we can create a `index.mustache` file:

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>{{title}}</title>
</head>
<body>
    <h1>{{message}}</h1>
</body>
</html>
```

Template-engine specific syntax is used to embed variables, declare dynamic content, and add logic into the HTML templates.

### Mustache Example

Mustache.js is a logic-less template engine, meaning it does not support complex logic or control structures.
It also supports partials, which are reusable templates that can be included in other templates.

```html
<!-- views/index.mustache -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>{{title}}</title>
</head>
<body>
    <h1>{{message}}</h1>
</body>
</html>
```

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

Using express, we can achieve this behavior via 

```js 
res.cookie('name', 'value' [, options])
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




