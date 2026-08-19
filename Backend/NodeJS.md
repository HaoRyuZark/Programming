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

If declared inside the same folder:

```js 
import express from "express";

const app = express();
const router1 = express.Router();
const router2 = express.Router();

app.use("/users", router1);
app.use("/products", router2);

//...
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

## Template Engines 

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

Example with **EJS**:

```js
const express = require("express");
const ejs = require("ejs");
const app = express();

app.set("view engine", "ejs");
app.set("views", __dirname + "/views"); 
app.get("/", (req, res) => {
  res.render("index", { title: "Hello, World!", message: "Welcome to my website!" });
});
```

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title><%= title %></title>
</head>
<body>
    <h1><%= message %></h1>
</body>
</html>
```


Template-engine specific syntax is used to embed variables, declare dynamic content, and add logic into the HTML templates.

--- 

## Cookies & Sessions

Cookies store small pieces of data on the **client**; sessions store data on the **server** keyed by a session ID sent in a cookie.

```bash
npm install cookie-parser express-session
```

### Cookies (`cookie-parser`)

- `cookieParser(secret, options)`: middleware that parses `Cookie` headers into `req.cookies` and `req.signedCookies`.
  - `secret`: string or array used to sign cookies (enables tamper detection).

- `res.cookie(name, value, options)`: sets a `Set-Cookie` header.
  - `maxAge`: max age in milliseconds.
  - `expires`: explicit `Date` object.
  - `httpOnly`: if `true`, inaccessible to JavaScript (XSS protection).
  - `secure`: if `true`, sent only over HTTPS.
  - `sameSite`: `'Strict'`, `'Lax'`, or `'None'` (CSRF protection).
  - `signed`: if `true`, signs the cookie with the parser secret.
  - `domain`, `path`: scope the cookie.

- `res.clearCookie(name, options)`: expires the cookie.

```js
import express from "express";
import cookieParser from "cookie-parser";

const app = express();
app.use(cookieParser("mySigningSecret"));

// Set cookies
app.get("/set", (req, res) => {
  res.cookie("username", "alice", {
    maxAge:   7 * 24 * 60 * 60 * 1000,  // 7 days in ms
    httpOnly: true,                       // not readable by JS — XSS protection
    secure:   true,                       // HTTPS only
    sameSite: "Lax",                      // CSRF protection
  });

  res.cookie("token", "abc123", { signed: true });  // tamper-proof

  res.json({ message: "Cookies set" });
});

// Read cookies
app.get("/read", (req, res) => {
  console.log(req.cookies);              // unsigned cookies
  console.log(req.signedCookies);       // signed cookies (verified)
  res.json({ user: req.cookies.username });
});

// Clear a cookie
app.post("/logout", (req, res) => {
  res.clearCookie("username");
  res.clearCookie("token");
  res.json({ message: "Logged out" });
});
```

**Cookie attribute quick reference:**

| Attribute | Purpose |
|-----------|---------|
| `httpOnly` | Prevents JS access — mitigates XSS |
| `secure` | HTTPS only |
| `sameSite: 'Strict'` | Cookie never sent cross-site |
| `sameSite: 'Lax'` | Sent on top-level navigation (default in modern browsers) |
| `sameSite: 'None'` | Always sent — requires `secure: true` |
| `maxAge` | Seconds until expiry (relative) |
| `expires` | Absolute expiry `Date` |

---

### Sessions (`express-session`)

- `session(options)`: session middleware. Stores session data server-side; sends only a session ID cookie to the client.
  - `secret`: string or array — signs the session ID cookie. **Required**. Use a strong random value from env.
  - `resave`: if `false`, only saves the session if it was modified (recommended: `false`).
  - `saveUninitialized`: if `false`, does not store empty sessions (recommended: `false`).
  - `cookie`: options for the session ID cookie (`maxAge`, `secure`, `httpOnly`, `sameSite`).
  - `store`: session store — defaults to in-memory (not suitable for production). Use `connect-pg-simple`, `connect-redis`, etc.

```bash
npm install express-session connect-pg-simple
```

```js
import session from "express-session";
import pgSession from "connect-pg-simple";

const PgStore = pgSession(session);

app.use(session({
  secret:            process.env.SESSION_SECRET,
  resave:            false,
  saveUninitialized: false,
  cookie: {
    maxAge:   24 * 60 * 60 * 1000,  // 1 day
    httpOnly: true,
    secure:   process.env.NODE_ENV === "production",
    sameSite: "Lax",
  },
  store: new PgStore({
    conString: process.env.DATABASE_URL,  // PostgreSQL store
    tableName: "sessions",
  }),
}));

// Set session data
app.post("/login", async (req, res) => {
  const user = await authenticateUser(req.body.email, req.body.password);
  if (!user) return res.status(401).json({ error: "Invalid credentials" });

  req.session.userId = user.id;          // store arbitrary data in session
  req.session.role   = user.role;
  req.session.save((err) => {            // explicitly save before redirecting
    if (err) return next(err);
    res.json({ message: "Logged in" });
  });
});

// Read session data
app.get("/profile", (req, res) => {
  if (!req.session.userId) return res.status(401).json({ error: "Not authenticated" });
  res.json({ userId: req.session.userId, role: req.session.role });
});

// Destroy session on logout
app.post("/logout", (req, res) => {
  req.session.destroy((err) => {
    if (err) return res.status(500).json({ error: "Logout failed" });
    res.clearCookie("connect.sid");      // clear the session ID cookie
    res.json({ message: "Logged out" });
  });
});
```

---

## Environment Variables (dotenv)

**dotenv** loads variables from a `.env` file into `process.env`. Never commit `.env` to version control — commit `.env.example` instead.

```bash
npm install dotenv
```

```
# .env
PORT=3000
NODE_ENV=development
DATABASE_URL=postgres://user:pass@localhost:5432/mydb
JWT_SECRET=supersecretkey32chars
JWT_EXPIRES_IN=7d
BCRYPT_ROUNDS=12
```

```js
// Load at the very top of the entry file — before any other imports
import "dotenv/config";          // ES6 (Node 18+)
// or
require("dotenv").config();      // CommonJS

const port   = parseInt(process.env.PORT)   || 3000;
const dbUrl  = process.env.DATABASE_URL;

// Validate required variables at startup — fail fast rather than crash later
const required = ["DATABASE_URL", "JWT_SECRET"];
for (const key of required) {
  if (!process.env[key]) {
    console.error(`Missing required env var: ${key}`);
    process.exit(1);
  }
}
```

> Use `dotenv-expand` to allow variable interpolation (`API_URL=http://localhost:${PORT}/api`).

---

## JWT Authentication

JSON Web Tokens are the standard for stateless API authentication. The server signs a token containing the user's claims; the client sends it on every subsequent request.

```bash
npm install jsonwebtoken bcrypt
```

- `jwt.sign(payload, secret, options)`: creates a signed token.
  - `payload`: data to encode — keep it small (it is base64-encoded, not encrypted).
  - `secret`: secret key (HS256) or RSA private key (RS256).
  - `options.expiresIn`: duration string — `'15m'`, `'1h'`, `'7d'`.
  - `options.algorithm`: default `'HS256'`.

- `jwt.verify(token, secret, options)`: verifies signature and expiry. Throws `JsonWebTokenError` or `TokenExpiredError` on failure.

- `jwt.decode(token)`: decodes without verification — **never trust the result for auth decisions**.

```js
import jwt from "jsonwebtoken";
import bcrypt from "bcrypt";

const JWT_SECRET = process.env.JWT_SECRET;

// --- Helpers ---
function generateAccessToken(userId, role) {
  return jwt.sign({ userId, role }, JWT_SECRET, { expiresIn: "15m" });
}

function generateRefreshToken(userId) {
  return jwt.sign({ userId }, process.env.JWT_REFRESH_SECRET, { expiresIn: "7d" });
}

// --- Login route ---
app.post("/api/auth/login", async (req, res, next) => {
  try {
    const { email, password } = req.body;
    const user = await User.findOne({ where: { email } });
    if (!user) return res.status(401).json({ error: "Invalid credentials" });

    const match = await bcrypt.compare(password, user.password);
    if (!match)  return res.status(401).json({ error: "Invalid credentials" });

    const accessToken  = generateAccessToken(user.id, user.role);
    const refreshToken = generateRefreshToken(user.id);

    // Store refresh token in an httpOnly cookie — not in localStorage
    res.cookie("refreshToken", refreshToken, { httpOnly: true, secure: true, sameSite: "Strict" });
    res.json({ accessToken, user: { id: user.id, email: user.email, role: user.role } });
  } catch (err) { next(err); }
});

// --- Auth middleware ---
export function authenticate(req, res, next) {
  const authHeader = req.headers.authorization;
  if (!authHeader?.startsWith("Bearer ")) {
    return res.status(401).json({ error: "No token provided" });
  }
  try {
    req.user = jwt.verify(authHeader.slice(7), JWT_SECRET); // attaches { userId, role, iat, exp }
    next();
  } catch (err) {
    const msg = err.name === "TokenExpiredError" ? "Token expired" : "Invalid token";
    res.status(401).json({ error: msg });
  }
}

// --- Role-based authorisation middleware ---
export function authorize(...roles) {
  return (req, res, next) => {
    if (!roles.includes(req.user.role)) {
      return res.status(403).json({ error: "Insufficient permissions" });
    }
    next();
  };
}

// --- Refresh token route ---
app.post("/api/auth/refresh", (req, res) => {
  const token = req.cookies.refreshToken;
  if (!token) return res.status(401).json({ error: "No refresh token" });
  try {
    const { userId } = jwt.verify(token, process.env.JWT_REFRESH_SECRET);
    const accessToken = generateAccessToken(userId, "user");  // re-fetch role from DB in production
    res.json({ accessToken });
  } catch {
    res.status(401).json({ error: "Invalid refresh token" });
  }
});

// --- Protected routes ---
app.get("/api/profile",             authenticate, getProfile);
app.delete("/api/users/:id",        authenticate, authorize("admin"), deleteUser);
app.get("/api/admin/dashboard",     authenticate, authorize("admin", "moderator"), getDashboard);
```

---

## CORS

Cross-Origin Resource Sharing — required when your frontend (e.g. React on port 5173) calls your API (port 3000).

```bash
npm install cors
```

- `cors(options)`: returns middleware that sets CORS headers on responses.
  - `origin`: allowed origins — string, array, regex, or a `(origin, callback)` function.
  - `methods`: allowed HTTP verbs (default: `'GET,HEAD,PUT,PATCH,POST,DELETE'`).
  - `credentials`: if `true`, allows cookies and `Authorization` headers cross-origin.
  - `allowedHeaders`: headers the client may send.
  - `exposedHeaders`: headers the browser is allowed to read from the response.
  - `maxAge`: seconds to cache the preflight response.

```js
import cors from "cors";

// Allow all origins — development only
app.use(cors());

// Single origin
app.use(cors({
  origin:         "https://myfrontend.com",
  methods:        ["GET", "POST", "PUT", "DELETE", "PATCH"],
  credentials:    true,                        // allow cookies + auth headers
  allowedHeaders: ["Content-Type", "Authorization"],
}));

// Multiple allowed origins — dynamic check
const allowedOrigins = ["https://myfrontend.com", "https://admin.myfrontend.com"];

app.use(cors({
  origin: (origin, callback) => {
    // allow server-to-server (no origin) or whitelisted origins
    if (!origin || allowedOrigins.includes(origin)) return callback(null, true);
    callback(new Error("Not allowed by CORS"));
  },
  credentials: true,
}));
```

---

## Express Error Handling

Express error-handling middleware takes **four parameters** `(err, req, res, next)` and must be registered **after** all routes.

```js
// Custom operational error class
class AppError extends Error {
  constructor(message, statusCode) {
    super(message);
    this.statusCode  = statusCode;
    this.isOperational = true;   // distinguishes expected errors from bugs
  }
}

// 404 handler — catches all unmatched routes
app.use((req, res, next) => {
  next(new AppError(`Route ${req.originalUrl} not found`, 404));
});

// Global error handler — must have exactly 4 params
app.use((err, req, res, next) => {
  const status  = err.statusCode || 500;
  const message = err.message    || "Internal Server Error";

  if (status >= 500) console.error(err.stack);  // log unexpected errors

  // Sequelize validation errors
  if (err.name === "SequelizeValidationError") {
    const details = err.errors.map(e => ({ field: e.path, message: e.message }));
    return res.status(422).json({ error: "Validation failed", details });
  }

  // Sequelize unique constraint
  if (err.name === "SequelizeUniqueConstraintError") {
    return res.status(409).json({ error: "Resource already exists" });
  }

  // JWT errors
  if (err.name === "JsonWebTokenError") return res.status(401).json({ error: "Invalid token" });
  if (err.name === "TokenExpiredError") return res.status(401).json({ error: "Token expired" });

  res.status(status).json({
    error: message,
    ...(process.env.NODE_ENV === "development" && { stack: err.stack }),
  });
});

// In async route handlers — pass errors to next()
app.get("/api/users/:id", async (req, res, next) => {
  try {
    const user = await User.findByPk(req.params.id);
    if (!user) return next(new AppError("User not found", 404));
    res.json(user);
  } catch (err) {
    next(err);
  }
});

// Async wrapper — eliminates try/catch boilerplate in every handler
const asyncHandler = (fn) => (req, res, next) =>
  Promise.resolve(fn(req, res, next)).catch(next);

app.get("/api/posts", asyncHandler(async (req, res) => {
  const posts = await Post.findAll();
  res.json(posts);
}));
```

---

## Security & Rate Limiting

### Helmet — Security Headers

```bash
npm install helmet
```

`helmet()` sets security-related HTTP headers (Content-Security-Policy, X-Frame-Options, etc.).

```js
import helmet from "helmet";
app.use(helmet());   // apply all default headers

// Custom CSP
app.use(helmet({
  contentSecurityPolicy: {
    directives: {
      defaultSrc: ["'self'"],
      scriptSrc:  ["'self'", "https://cdn.example.com"],
      imgSrc:     ["'self'", "data:", "https:"],
    },
  },
  crossOriginEmbedderPolicy: false,
}));
```

### express-rate-limit

```bash
npm install express-rate-limit
```

- `rateLimit(options)`: creates a rate-limiting middleware.
  - `windowMs`: time window in milliseconds.
  - `max`: max requests per window per IP.
  - `message`: response sent when the limit is exceeded.
  - `standardHeaders`: sends `RateLimit-*` headers (recommended: `true`).
  - `legacyHeaders`: disables old `X-RateLimit-*` headers (recommended: `false`).

```js
import rateLimit from "express-rate-limit";

// Global limiter — all routes
const limiter = rateLimit({
  windowMs:        15 * 60 * 1000,   // 15 minutes
  max:             100,               // 100 requests per window
  standardHeaders: true,
  legacyHeaders:   false,
  message:         { error: "Too many requests, please try again later." },
});
app.use(limiter);

// Stricter limiter for auth routes
const authLimiter = rateLimit({
  windowMs: 15 * 60 * 1000,
  max:      10,                       // 10 login attempts per 15 minutes
  message:  { error: "Too many login attempts." },
});
app.post("/api/auth/login",    authLimiter, loginHandler);
app.post("/api/auth/register", authLimiter, registerHandler);
```

---

## WebSockets

WebSockets provide full-duplex communication over a single persistent TCP connection. Unlike HTTP, both sides can push messages at any time without a request-response cycle.

### `ws` — Bare WebSocket Server

```bash
npm install ws
```

- `new WebSocketServer({ port, server })`: creates a WebSocket server.
  - `port`: listen on a dedicated port.
  - `server`: attach to an existing HTTP server (same port as Express).

- `wss.on('connection', (ws, req) => {})`: fires when a client connects.
  - `ws`: the socket for this specific client.
  - `req`: the underlying HTTP upgrade request (useful for auth headers / cookies).

- `ws.on('message', (data, isBinary) => {})`: incoming message from this client.

- `ws.send(data, callback)`: sends data to this client.

- `ws.close(code, reason)`: closes the connection.

- `ws.readyState`: `ws.OPEN`, `ws.CLOSING`, `ws.CLOSED`.

- `wss.clients`: `Set` of all active `WebSocket` connections.

```js
import { WebSocketServer } from "ws";
import http from "http";
import express from "express";

const app        = express();
const httpServer = http.createServer(app);
const wss        = new WebSocketServer({ server: httpServer });  // share port with Express

// Client metadata map
const clients = new Map();   // ws → { id, joinedAt }

wss.on("connection", (ws, req) => {
  const clientId = req.headers["sec-websocket-key"];
  clients.set(ws, { id: clientId, joinedAt: Date.now() });
  console.log(`Client connected: ${clientId}`);

  ws.send(JSON.stringify({ type: "welcome", id: clientId }));

  ws.on("message", (data) => {
    const msg = JSON.parse(data.toString());

    // Echo back to sender
    ws.send(JSON.stringify({ type: "echo", payload: msg }));

    // Broadcast to all other clients
    for (const [client] of clients) {
      if (client !== ws && client.readyState === ws.OPEN) {
        client.send(JSON.stringify({ type: "broadcast", payload: msg }));
      }
    }
  });

  ws.on("close", (code, reason) => {
    clients.delete(ws);
    console.log(`Disconnected: ${code}`);
  });

  ws.on("error", (err) => console.error("WS error:", err));
});

// Keepalive — detect dead connections
wss.on("connection", (ws) => { ws.isAlive = true; });
ws.on("pong", () => { ws.isAlive = true; });

const heartbeat = setInterval(() => {
  wss.clients.forEach((ws) => {
    if (!ws.isAlive) return ws.terminate();
    ws.isAlive = false;
    ws.ping();
  });
}, 30_000);

wss.on("close", () => clearInterval(heartbeat));

httpServer.listen(3000);
```

**Browser client:**

```js
const ws = new WebSocket("ws://localhost:3000");
ws.onopen    = () => ws.send(JSON.stringify({ type: "hello" }));
ws.onmessage = (e) => console.log(JSON.parse(e.data));
ws.onerror   = (e) => console.error(e);
ws.onclose   = ()  => console.log("Disconnected");
```

---

### Socket.IO — Rooms, Namespaces, Events

Socket.IO adds auto-reconnection, rooms, namespaces, event acknowledgements, and a long-polling fallback.

```bash
npm install socket.io          # server
npm install socket.io-client   # client (or use CDN)
```

- `new Server(httpServer, options)`: creates a Socket.IO server.
  - `cors`: CORS options.
  - `pingTimeout` / `pingInterval`: keepalive tuning.

- `io.on('connection', (socket) => {})`: new client connected.

- `socket.emit(event, ...args)`: send to this client only.

- `socket.broadcast.emit(event, ...args)`: send to all clients **except** sender.

- `io.emit(event, ...args)`: send to **all** clients.

- `socket.join(room)`: add socket to a named room.

- `io.to(room).emit(event, ...args)`: broadcast to all sockets in a room.

- `socket.to(room).emit(event, ...args)`: broadcast to room **except** sender.

- `socket.leave(room)`: leave a room.

- `socket.id`: unique identifier for this connection.

```js
// server.js
import { Server } from "socket.io";
import { createServer } from "http";
import express from "express";

const app  = express();
const http = createServer(app);
const io   = new Server(http, {
  cors: { origin: "http://localhost:5173", credentials: true }
});

io.on("connection", (socket) => {
  console.log("Connected:", socket.id);

  // Join a chat room
  socket.on("join_room", (room) => {
    socket.join(room);
    io.to(room).emit("user_joined", { userId: socket.id, room });
  });

  // Relay a message within a room
  socket.on("send_message", ({ room, message }) => {
    io.to(room).emit("receive_message", {
      from:      socket.id,
      message,
      timestamp: new Date().toISOString(),
    });
  });

  // Private message to a specific socket ID
  socket.on("private_message", ({ to, message }) => {
    socket.to(to).emit("receive_private", { from: socket.id, message });
  });

  // Acknowledgement — client receives a server confirmation
  socket.on("save_data", (data, ack) => {
    // process data...
    ack({ status: "ok", id: data.id });
  });

  socket.on("disconnect", (reason) => {
    console.log(`Disconnected ${socket.id}: ${reason}`);
  });
});

http.listen(3000);
```

**React / browser client:**

```js
import { io } from "socket.io-client";

const socket = io("http://localhost:3000", { withCredentials: true });

socket.on("connect", () => {
  socket.emit("join_room", "general");
});

socket.emit("send_message", { room: "general", message: "Hello!" });

socket.on("receive_message", ({ from, message, timestamp }) => {
  console.log(`[${timestamp}] ${from}: ${message}`);
});

// Acknowledgement
socket.emit("save_data", { id: 42 }, (res) => {
  console.log("Ack:", res.status);
});
```

**Namespaces** — logical separation within one server (separate CORS / middleware per namespace):

```js
const chatNs  = io.of("/chat");
const adminNs = io.of("/admin");

adminNs.use((socket, next) => {  // middleware only on /admin
  if (!isAdmin(socket.handshake.auth.token)) return next(new Error("Forbidden"));
  next();
});

chatNs.on("connection",  (socket) => { /* chat logic */ });
adminNs.on("connection", (socket) => { /* admin logic */ });
```

---

## Sequelize.js

**Sequelize** is a promise-based ORM for Node.js supporting PostgreSQL, MySQL, MariaDB, SQLite, and MSSQL.
It maps ES6 classes to database tables and provides a full query API without writing raw SQL.

```bash
npm install sequelize
npm install pg pg-hstore   # PostgreSQL
npm install mysql2         # MySQL / MariaDB
npm install sqlite3        # SQLite
```

---

### Connection & Setup

- `new Sequelize(database, username, password, options)`: creates a Sequelize instance.
  - `dialect`: `'postgres'`, `'mysql'`, `'mariadb'`, `'sqlite'`, `'mssql'`.
  - `host`, `port`: database server address.
  - `logging`: `console.log` to print SQL, or `false` to silence.
  - `pool`: `{ max, min, acquire, idle }` — connection pool settings.
  - `storage`: path to the SQLite file (SQLite only).

- `sequelize.authenticate()`: tests the connection. Returns a promise.

- `sequelize.sync(options)`: creates/updates tables to match models.
  - `force: true`: drops and re-creates all tables — **dev only**.
  - `alter: true`: alters tables non-destructively — use with caution.

- `sequelize.close()`: closes the connection pool.

```js
// db.js
import { Sequelize } from "sequelize";

const sequelize = new Sequelize("mydb", "postgres", "password", {
  dialect: "postgres",
  host:    "localhost",
  port:    5432,
  logging: false,
  pool: { max: 10, min: 0, acquire: 30_000, idle: 10_000 },
});

// From DATABASE_URL (12-factor / Heroku / Railway)
const sequelize = new Sequelize(process.env.DATABASE_URL, {
  dialect: "postgres",
  dialectOptions: { ssl: { require: true, rejectUnauthorized: false } },
  logging: false,
});

try {
  await sequelize.authenticate();
  console.log("Database connected.");
} catch (err) {
  console.error("Connection failed:", err);
  process.exit(1);
}

export default sequelize;
```

---

### Defining Models

- `Model.init(attributes, options)`: registers the model with the Sequelize instance.
  - `attributes`: column definitions — each key maps to a `DataTypes` config.
  - `options.sequelize`: the Sequelize instance (required).
  - `options.modelName`: class name used as the model name.
  - `options.tableName`: explicit DB table name (defaults to pluralised class name).
  - `options.timestamps`: adds `createdAt` / `updatedAt` columns (default `true`).
  - `options.paranoid`: adds `deletedAt` and soft-deletes instead of hard-deletes.
  - `options.underscored`: uses `snake_case` column names in the DB.
  - `options.indexes`: array of index definitions.

**DataTypes quick reference:**

| DataType | SQL equivalent |
|----------|---------------|
| `DataTypes.INTEGER` | INT |
| `DataTypes.BIGINT` | BIGINT |
| `DataTypes.FLOAT` | FLOAT |
| `DataTypes.DECIMAL(p, s)` | DECIMAL(p, s) |
| `DataTypes.STRING` | VARCHAR(255) |
| `DataTypes.STRING(n)` | VARCHAR(n) |
| `DataTypes.TEXT` | TEXT |
| `DataTypes.BOOLEAN` | BOOLEAN |
| `DataTypes.DATE` | DATETIME / TIMESTAMP |
| `DataTypes.DATEONLY` | DATE |
| `DataTypes.UUID` | UUID / CHAR(36) |
| `DataTypes.UUIDV4` | default value generator |
| `DataTypes.JSON` | JSON |
| `DataTypes.JSONB` | JSONB (PostgreSQL) |
| `DataTypes.ENUM('a','b')` | ENUM |
| `DataTypes.ARRAY(DataTypes.STRING)` | ARRAY (PostgreSQL only) |
| `DataTypes.VIRTUAL` | not stored in DB — computed getter |

```js
// models/User.js
import { Model, DataTypes } from "sequelize";
import sequelize from "../db.js";

class User extends Model {}

User.init(
  {
    id: {
      type:          DataTypes.INTEGER,
      autoIncrement: true,
      primaryKey:    true,
    },
    uuid: {
      type:         DataTypes.UUID,
      defaultValue: DataTypes.UUIDV4,
      unique:       true,
    },
    email: {
      type:      DataTypes.STRING,
      allowNull: false,
      unique:    true,
      validate: {
        isEmail:  true,
        notEmpty: true,
      },
    },
    password: {
      type:      DataTypes.STRING,
      allowNull: false,
      validate: { len: [8, 128] },
    },
    role: {
      type:         DataTypes.ENUM("user", "admin", "moderator"),
      defaultValue: "user",
    },
    age: {
      type:     DataTypes.INTEGER,
      validate: { min: 0, max: 120 },
    },
    isActive: {
      type:         DataTypes.BOOLEAN,
      defaultValue: true,
    },
    fullName: {
      type: DataTypes.VIRTUAL,     // computed — not stored
      get() { return `${this.firstName} ${this.lastName}`; },
    },
  },
  {
    sequelize,
    modelName: "User",
    tableName: "users",
    timestamps:  true,             // createdAt, updatedAt
    paranoid:    true,             // soft delete — sets deletedAt instead of removing
    underscored: true,             // camelCase JS → snake_case DB column
    indexes: [
      { fields: ["email"] },
      { unique: true, fields: ["uuid"] },
    ],
  }
);

export default User;
```

---

### Hooks (Lifecycle Callbacks)

Hooks execute at specific points in the record's lifecycle — useful for hashing passwords, normalising data, and audit logging.

| Hook | When |
|------|------|
| `beforeValidate` / `afterValidate` | Around validation |
| `beforeCreate` / `afterCreate` | Around INSERT |
| `beforeUpdate` / `afterUpdate` | Around UPDATE |
| `beforeSave` / `afterSave` | Before/after INSERT or UPDATE |
| `beforeDestroy` / `afterDestroy` | Around DELETE |
| `beforeBulkCreate` / `afterBulkCreate` | Around bulk inserts |

```js
import bcrypt from "bcrypt";

// Hash password before every create
User.addHook("beforeCreate", async (user) => {
  user.password = await bcrypt.hash(user.password, parseInt(process.env.BCRYPT_ROUNDS) || 12);
});

// Hash only if password was changed on update
User.addHook("beforeUpdate", async (user) => {
  if (user.changed("password")) {
    user.password = await bcrypt.hash(user.password, 12);
  }
});

// Normalise email
User.addHook("beforeValidate", (user) => {
  if (user.email) user.email = user.email.toLowerCase().trim();
});
```

---

### CRUD Operations

#### Create

- `Model.create(values, options)`: inserts a new record. Runs validations and hooks.
  - `fields`: whitelist of allowed columns — prevents mass-assignment vulnerabilities.

- `Model.bulkCreate(records, options)`: inserts multiple records in one statement.
  - `validate: true`: runs validations on each record.
  - `ignoreDuplicates: true`: silently skips rows that would violate a unique constraint.
  - `updateOnDuplicate: [cols]`: upsert — update these columns on conflict (PostgreSQL / MySQL).

- `Model.findOrCreate({ where, defaults })`: finds a matching record or creates one.
  - Returns `[instance, created]` — `created` is `true` if it was inserted.

```js
// Single insert
const user = await User.create({
  email: "alice@example.com",
  password: "secret123",
});
console.log(user.id, user.createdAt);

// Safe create from user input — only allow these fields
const user2 = await User.create(req.body, { fields: ["email", "password"] });

// Bulk insert
await User.bulkCreate(
  [
    { email: "bob@example.com",   password: "pass1" },
    { email: "carol@example.com", password: "pass2" },
  ],
  { validate: true }
);

// Find or create
const [user3, created] = await User.findOrCreate({
  where:    { email: "dave@example.com" },
  defaults: { password: "pass3", role: "user" },
});
console.log(created);   // true = inserted, false = already existed
```

#### Read

- `Model.findAll(options)`: returns all matching records as model instances.
  - `where`: filter conditions.
  - `attributes`: columns to SELECT — array or `{ exclude: ['password'] }`.
  - `order`: `[['createdAt', 'DESC']]`.
  - `limit` / `offset`: pagination.
  - `include`: eager-load associated models (JOIN).
  - `raw: true`: returns plain JS objects (faster for read-only operations).
  - `group`: GROUP BY columns.

- `Model.findOne(options)`: first matching record or `null`.

- `Model.findByPk(id, options)`: find by primary key.

- `Model.findAndCountAll(options)`: returns `{ count, rows }` — ideal for paginated endpoints.

- `Model.count(options)`: count of matching records.

```js
// All records
const users = await User.findAll();

// Filtered, ordered, paginated
const page  = parseInt(req.query.page) || 1;
const limit = 10;

const { count, rows } = await User.findAndCountAll({
  where:      { isActive: true, role: "user" },
  attributes: { exclude: ["password"] },
  order:      [["createdAt", "DESC"]],
  limit,
  offset:     (page - 1) * limit,
});
res.json({ total: count, page, pages: Math.ceil(count / limit), data: rows });

// Find one
const user = await User.findOne({ where: { email: "alice@example.com" } });

// Find by PK
const user2 = await User.findByPk(req.params.id);
if (!user2) return res.status(404).json({ error: "Not found" });

// Count
const adminCount = await User.count({ where: { role: "admin" } });

// Raw — plain objects, no Sequelize overhead
const rows2 = await User.findAll({ raw: true });
```

#### Update

- `Model.update(values, options)`: updates all matching rows. Returns `[affectedCount]`.
  - `where`: required — omitting it updates every row.
  - `returning: true`: returns updated instances (PostgreSQL only).

- `instance.update(values)`: updates a specific instance. Runs hooks and validations. Preferred over the static form.

- `instance.increment(field, { by })` / `instance.decrement(field, { by })`: atomic increment/decrement.

```js
// Bulk update
const [count] = await User.update(
  { isActive: false },
  { where: { role: "banned" } }
);

// Instance update — runs beforeUpdate hook
const user = await User.findByPk(42);
await user.update({ role: "admin" });

// Set then save
user.set("bio", "Updated bio");
await user.save();

// Atomic increment
await user.increment("loginCount");
await user.decrement("credits", { by: 10 });
```

#### Delete

- `Model.destroy(options)`: deletes matching records. Returns count.
  - `where`: required — omitting it deletes all rows.

- `instance.destroy()`: deletes a specific record.

- `Model.restore(options)` / `instance.restore()`: restores soft-deleted records (only when `paranoid: true`).

> If the model has `paranoid: true`, `.destroy()` sets `deletedAt` instead of removing the row. Pass `{ force: true }` for a hard delete.

```js
// Bulk delete
const n = await User.destroy({ where: { isActive: false } });

// Instance delete
const user = await User.findByPk(42);
await user.destroy();          // soft-delete if paranoid is true

// Hard delete on a paranoid model
await user.destroy({ force: true });

// Restore a soft-deleted record
await User.restore({ where: { id: 42 } });
```

---

### Querying — Operators

```js
import { Op } from "sequelize";

// Comparison
User.findAll({ where: { age: { [Op.gt]: 18 } } });             // age > 18
User.findAll({ where: { age: { [Op.gte]: 18 } } });            // age >= 18
User.findAll({ where: { age: { [Op.between]: [18, 65] } } });  // BETWEEN
User.findAll({ where: { id: { [Op.in]: [1, 2, 3] } } });       // IN (1,2,3)
User.findAll({ where: { id: { [Op.notIn]: [4, 5] } } });       // NOT IN

// String matching
User.findAll({ where: { email: { [Op.like]:  "%@gmail.com" } } });  // LIKE
User.findAll({ where: { email: { [Op.iLike]: "%@gmail.com" } } });  // ILIKE (case-insensitive, PG)
User.findAll({ where: { name: { [Op.startsWith]: "Al" } } });
User.findAll({ where: { name: { [Op.endsWith]:   "son" } } });

// Null checks
User.findAll({ where: { deletedAt: null } });
User.findAll({ where: { deletedAt: { [Op.not]: null } } });

// Logical operators
User.findAll({
  where: {
    isActive: true,
    [Op.or]: [
      { role: "admin" },
      { age:  { [Op.lt]: 25 } },
    ],
  },
});
```

**Op reference:**

| Operator | SQL |
|----------|-----|
| `Op.eq` | `=` |
| `Op.ne` | `!=` |
| `Op.gt` | `>` |
| `Op.gte` | `>=` |
| `Op.lt` | `<` |
| `Op.lte` | `<=` |
| `Op.between` | `BETWEEN` |
| `Op.in` | `IN` |
| `Op.notIn` | `NOT IN` |
| `Op.like` | `LIKE` |
| `Op.iLike` | `ILIKE` |
| `Op.and` | `AND` |
| `Op.or` | `OR` |
| `Op.not` | `NOT` |
| `Op.is` | `IS` (NULL checks) |

---

### Associations

Associations define relationships between models. Always define them **after** all models are initialised.

- `Model.hasOne(Target, options)`: one-to-one — FK lives on `Target`.
- `Model.belongsTo(Target, options)`: one-to-one or many-to-one — FK lives on **this** model.
- `Model.hasMany(Target, options)`: one-to-many — FK lives on `Target`.
- `Model.belongsToMany(Target, options)`: many-to-many via a junction table.
  - `through`: junction model or table name string.
  - `foreignKey` / `otherKey`: FK names on the junction table.

```js
// models/associations.js — define all relationships in one place
import User    from "./User.js";
import Post    from "./Post.js";
import Tag     from "./Tag.js";
import Profile from "./Profile.js";

// One-to-One
User.hasOne(Profile, { foreignKey: "userId", as: "profile" });
Profile.belongsTo(User, { foreignKey: "userId", as: "user" });

// One-to-Many
User.hasMany(Post, { foreignKey: "authorId", as: "posts", onDelete: "CASCADE" });
Post.belongsTo(User, { foreignKey: "authorId", as: "author" });

// Many-to-Many
Post.belongsToMany(Tag, { through: "PostTags", foreignKey: "postId", as: "tags" });
Tag.belongsToMany(Post, { through: "PostTags", foreignKey: "tagId",  as: "posts" });
```

**Auto-generated instance methods:**

```js
const user = await User.findByPk(1);

// hasOne
const profile = await user.getProfile();
await user.setProfile(profile);
await user.createProfile({ bio: "Hello!" });

// hasMany
const posts = await user.getPosts({ where: { published: true } });
await user.createPost({ title: "New Post", content: "..." });

// belongsToMany
const post = await Post.findByPk(1);
await post.addTag(tag);
await post.addTags([tag1, tag2]);
await post.setTags([tag1, tag2]);   // replace all
await post.removeTag(tag);
const hasThem = await post.hasTags([tag1, tag2]);
```

**Eager loading (JOINs)** with `include`:

```js
// Include one association
const users = await User.findAll({
  include: { model: Profile, as: "profile" },
  attributes: { exclude: ["password"] },
});

// Nested eager loading
const posts = await Post.findAll({
  include: [
    { model: User, as: "author",  attributes: ["id", "email"] },
    { model: Tag,  as: "tags",    through: { attributes: [] } },  // hide junction columns
  ],
});

// Filter on associated model (INNER JOIN)
const activeAuthors = await User.findAll({
  include: {
    model:    Post,
    as:       "posts",
    where:    { published: true },
    required: true,              // INNER JOIN — only users with published posts
  },
});
```

---

### Transactions

Transactions group queries into an atomic unit — all succeed or all roll back.

- `sequelize.transaction(callback)`: **managed** — auto-commits on success, auto-rolls back on thrown error.
- `sequelize.transaction()`: **unmanaged** — you call `t.commit()` / `t.rollback()` manually.

Pass `{ transaction: t }` to **every** query that should participate.

```js
// Managed (preferred)
await sequelize.transaction(async (t) => {
  const user = await User.create(
    { email: "new@example.com", password: "pass" },
    { transaction: t }
  );
  await Profile.create({ userId: user.id, bio: "Hi" }, { transaction: t });
  // auto-commits; auto-rolls back on any thrown error
});

// Unmanaged (more control)
const t = await sequelize.transaction();
try {
  await User.update({ credits: 0 }, { where: { id: 1 }, transaction: t });
  await AuditLog.create({ action: "reset", userId: 1 }, { transaction: t });
  await t.commit();
} catch (err) {
  await t.rollback();
  throw err;
}
```

---

### Raw Queries

Use `sequelize.query()` for SQL that the ORM cannot express, or when performance is critical.

- `sequelize.query(sql, options)`: executes raw SQL.
  - `type: QueryTypes.SELECT`: returns plain objects.
  - `replacements`: named (`:key`) or positional (`?`) safe parameter substitution — **always use this instead of string interpolation**.
  - `model`: maps results to a model class.

```js
import { QueryTypes } from "sequelize";

const users = await sequelize.query(
  "SELECT id, email FROM users WHERE role = :role AND age > :age",
  {
    replacements: { role: "admin", age: 18 },
    type: QueryTypes.SELECT,
  }
);

// Positional replacements
const posts = await sequelize.query(
  "SELECT * FROM posts WHERE author_id = ?",
  { replacements: [userId], type: QueryTypes.SELECT }
);

// UPDATE / DELETE
await sequelize.query(
  "UPDATE users SET is_active = false WHERE last_login < :cutoff",
  { replacements: { cutoff: new Date(Date.now() - 90 * 86400_000) } }
);
```

---

### Migrations (Sequelize CLI)

Migrations track schema changes in version control. Use them instead of `sync({ force: true })` in production.

```bash
npm install --save-dev sequelize-cli

npx sequelize-cli init   # creates config/, models/, migrations/, seeders/
```

**`.sequelizerc`:**

```js
const path = require("path");
module.exports = {
  "config":          path.resolve("src/config/database.json"),
  "models-path":     path.resolve("src/models"),
  "migrations-path": path.resolve("src/migrations"),
  "seeders-path":    path.resolve("src/seeders"),
};
```

```bash
npx sequelize-cli migration:generate --name create-users-table
npx sequelize-cli db:migrate                # run pending migrations
npx sequelize-cli db:migrate:undo           # revert last migration
npx sequelize-cli db:migrate:undo:all       # revert all

npx sequelize-cli seed:generate --name demo-users
npx sequelize-cli db:seed:all
npx sequelize-cli db:seed:undo:all
```

**Migration file:**

```js
// migrations/20240101000000-create-users.js
"use strict";
module.exports = {
  async up(queryInterface, Sequelize) {
    await queryInterface.createTable("users", {
      id:         { type: Sequelize.INTEGER, autoIncrement: true, primaryKey: true },
      email:      { type: Sequelize.STRING,  allowNull: false, unique: true },
      password:   { type: Sequelize.STRING,  allowNull: false },
      role:       { type: Sequelize.ENUM("user", "admin"), defaultValue: "user" },
      is_active:  { type: Sequelize.BOOLEAN, defaultValue: true },
      created_at: { type: Sequelize.DATE,    allowNull: false },
      updated_at: { type: Sequelize.DATE,    allowNull: false },
      deleted_at: { type: Sequelize.DATE,    allowNull: true },
    });
    await queryInterface.addIndex("users", ["email"]);
  },

  async down(queryInterface) {
    await queryInterface.dropTable("users");
  },
};
```

**Add column migration:**

```js
module.exports = {
  async up(queryInterface, Sequelize) {
    await queryInterface.addColumn("users", "phone", { type: Sequelize.STRING, allowNull: true });
  },
  async down(queryInterface) {
    await queryInterface.removeColumn("users", "phone");
  },
};
```

**Seeder file:**

```js
// seeders/20240101000001-demo-users.js
"use strict";
const bcrypt = require("bcrypt");

module.exports = {
  async up(queryInterface) {
    await queryInterface.bulkInsert("users", [{
      email:      "admin@example.com",
      password:   await bcrypt.hash("admin123", 12),
      role:       "admin",
      is_active:  true,
      created_at: new Date(),
      updated_at: new Date(),
    }]);
  },
  async down(queryInterface) {
    await queryInterface.bulkDelete("users", { email: "admin@example.com" });
  },
};
```

---

### Integrating with Express

```js
// models/index.js — central export point
import sequelize from "../db.js";
import User      from "./User.js";
import Post      from "./Post.js";
import Profile   from "./Profile.js";
import "./associations.js";   // registers all associations

export { sequelize, User, Post, Profile };

// app.js — connect before starting the server
import { sequelize } from "./models/index.js";

sequelize.authenticate()
  .then(() => app.listen(3000, () => console.log("Server running")))
  .catch((err) => { console.error(err); process.exit(1); });

// controllers/userController.js
import { User, Post } from "../models/index.js";

export const getUser = async (req, res, next) => {
  try {
    const user = await User.findByPk(req.params.id, {
      attributes: { exclude: ["password"] },
      include:    [{ model: Post, as: "posts", limit: 5 }],
    });
    if (!user) return res.status(404).json({ error: "User not found" });
    res.json(user);
  } catch (err) {
    next(err);   // delegate to Express error handler
  }
};
```

---

## EventEmitter

Node.js's built-in event system — the foundation of streams, HTTP, and most core modules.

- `emitter.on(event, listener)`: adds a persistent listener. Alias: `addListener`.
- `emitter.once(event, listener)`: fires only on the first occurrence, then auto-removes.
- `emitter.emit(event, ...args)`: synchronously invokes all listeners for the event.
- `emitter.off(event, listener)`: removes a specific listener. Alias: `removeListener`.
- `emitter.removeAllListeners(event)`: removes all listeners for an event.
- `emitter.listenerCount(event)`: number of attached listeners.
- `emitter.setMaxListeners(n)`: raise the listener cap to avoid memory-leak warnings (default 15).

```js
import { EventEmitter } from "events";

// Custom event-driven service
class OrderService extends EventEmitter {
  async placeOrder(order) {
    // business logic...
    this.emit("order:placed", order);
  }

  async cancelOrder(orderId) {
    // business logic...
    this.emit("order:cancelled", { orderId });
  }
}

const orderService = new OrderService();

// Separate concerns by reacting to events
orderService.on("order:placed", async (order) => {
  await sendConfirmationEmail(order.userId);
});

orderService.on("order:placed", async (order) => {
  await updateInventory(order.items);
});

orderService.once("order:placed", (order) => {
  console.log("First ever order:", order.id);  // fires only once
});

// Always handle the error event — unhandled emitter errors crash the process
orderService.on("error", (err) => console.error("OrderService error:", err));

await orderService.placeOrder({ id: 1, userId: 42, items: [] });
```

---

## Streams

Streams process data in **chunks** — essential for large files, HTTP I/O, and data pipelines without loading everything into memory.

| Type | Class | Description | Example |
|------|-------|-------------|---------|
| Readable | `Readable` | Source | `fs.createReadStream` |
| Writable | `Writable` | Sink | `fs.createWriteStream` |
| Duplex | `Duplex` | Read + Write | TCP socket |
| Transform | `Transform` | Read, transform, write | `zlib.createGzip` |

- `readable.pipe(writable)`: connects streams and handles backpressure automatically.
- `stream.pipeline(...streams, callback)`: like `pipe` but cleans up correctly on error — **prefer this**.
- `pipeline` from `stream/promises`: promise-based version (Node 15+).

```js
import { createReadStream, createWriteStream } from "fs";
import { createGzip }                          from "zlib";
import { pipeline }                            from "stream/promises";

// Compress a large file without loading it into memory
await pipeline(
  createReadStream("large.csv"),
  createGzip(),
  createWriteStream("large.csv.gz")
);

// Stream a file download via Express
app.get("/download/:filename", (req, res) => {
  const filePath = `./uploads/${path.basename(req.params.filename)}`;
  res.setHeader("Content-Disposition", `attachment; filename="${req.params.filename}"`);
  createReadStream(filePath).pipe(res);
});

// Process a large CSV line-by-line without loading it into memory
import { createInterface } from "readline";

const rl = createInterface({ input: createReadStream("data.csv") });
rl.on("line", (line) => {
  const [name, age] = line.split(",");
  // process each row
});
await new Promise((resolve, reject) => {
  rl.on("close", resolve);
  rl.on("error", reject);
});
```

---

## Async Patterns

```js
// Promise.all — parallel execution, fails fast on first rejection
const [users, posts, stats] = await Promise.all([
  User.findAll(),
  Post.findAll(),
  getStats(),
]);

// Promise.allSettled — collect every result regardless of failure
const results = await Promise.allSettled([
  fetch("https://api1.com"),
  fetch("https://api2.com"),
]);
for (const r of results) {
  if (r.status === "fulfilled") process(r.value);
  else console.error("Failed:", r.reason);
}

// Promise.race — first to resolve or reject wins
const fastest = await Promise.race([fetchPrimary(), fetchFallback()]);

// Promise.any — first to resolve wins (ignores rejections)
const result = await Promise.any([mirror1(), mirror2(), mirror3()]);

// Async route wrapper — eliminates try/catch in every Express handler
const asyncHandler = (fn) => (req, res, next) =>
  Promise.resolve(fn(req, res, next)).catch(next);

app.get("/api/users", asyncHandler(async (req, res) => {
  const users = await User.findAll({ attributes: { exclude: ["password"] } });
  res.json(users);
}));

// Sequential async with a for-of loop (use when order matters)
for (const user of users) {
  await sendWelcomeEmail(user.email);   // one at a time
}

// Parallel with concurrency limit (p-limit)
import pLimit from "p-limit";
const limit = pLimit(5);               // max 5 concurrent tasks
await Promise.all(
  users.map((user) => limit(() => processUser(user)))
);
```

---

## Project Structure (Convention)

A recommended layout for a full Express + Sequelize backend:

```
src/
├── app.js                  ← Express app setup (middleware, routes, error handlers)
├── server.js               ← Entry point — DB connect, server.listen
├── config/
│   └── database.json       ← Sequelize CLI config
├── db.js                   ← Sequelize instance
├── models/
│   ├── index.js            ← Central model export + associations
│   ├── User.js
│   └── Post.js
├── migrations/             ← Sequelize migration files
├── seeders/                ← Sequelize seeder files
├── routes/
│   ├── index.js            ← Mount all routers
│   ├── auth.js
│   └── users.js
├── controllers/
│   ├── authController.js
│   └── userController.js
├── middleware/
│   ├── authenticate.js     ← JWT auth middleware
│   ├── authorize.js        ← Role-based access
│   └── asyncHandler.js     ← try/catch wrapper
├── services/               ← Business logic (optional layer between controller and model)
│   └── emailService.js
└── utils/
    └── AppError.js         ← Custom error class
```

**`server.js` bootstrap pattern:**

```js
import "dotenv/config";
import app                from "./app.js";
import { sequelize }      from "./models/index.js";

const PORT = parseInt(process.env.PORT) || 3000;

async function start() {
  try {
    await sequelize.authenticate();
    console.log("Database connected.");
    app.listen(PORT, () => console.log(`Server running on port ${PORT}`));
  } catch (err) {
    console.error("Startup failed:", err);
    process.exit(1);
  }
}

start();
```




