# Chrome DevTools

**Chrome DevTools** is a set of web developer tools built directly into the Google Chrome browser.
It gives you live access to the DOM, styles, JavaScript runtime, network traffic, storage, security certificates,
and much more — without ever leaving the browser.

Open DevTools with any of the following:

| Method | Shortcut |
|--------|----------|
| Open with focus on Elements | `Ctrl+Shift+C` / `Cmd+Opt+C` |
| Open with focus on Console | `Ctrl+Shift+J` / `Cmd+Opt+J` |
| Open / Close toggle | `F12` / `Ctrl+Shift+I` / `Cmd+Opt+I` |
| Inspect element (right-click) | Right-click → **Inspect** |
| Command Menu (like VS Code) | `Ctrl+Shift+P` / `Cmd+Shift+P` |

DevTools can be docked to the bottom, left, right, or popped out as a separate window via the three-dot menu in the top-right corner of the panel.

---

## Elements

**Elements** is the live DOM inspector. Every change made here is immediately reflected in the page, but
changes are not persisted — a refresh resets everything to the original source.

### DOM Tree

Click any element in the viewport with **Inspect** (`Ctrl+Shift+C`) to jump directly to its node in the tree.
The selected node is highlighted in blue and its CSS rules appear in the **Styles** sub-panel on the right.

```
▼ <html lang="en">
  ▼ <body>
    ▼ <main>
        <h1 id="title">Hello World</h1>   ← selected node
      ▼ <section class="card">
          <p>Some text</p>
```

Key actions on the DOM tree:

| Action | How |
|--------|-----|
| Edit HTML inline | Double-click the element tag or text |
| Add / edit attribute | Double-click the attribute name or value |
| Delete node | Select node → `Delete` key |
| Hide / show node | Select node → `H` key (toggles `visibility: hidden`) |
| Duplicate node | Right-click → **Duplicate element** |
| Move node | Drag-and-drop in the tree |
| Scroll into view | Right-click → **Scroll into view** |
| Copy XPath / CSS selector | Right-click → **Copy** → Copy XPath / Copy selector |
| Force element state | Right-click → **Force state** → `:hover`, `:focus`, `:active`, `:visited` |
| Break on DOM mutations | Right-click → **Break on** → subtree modifications / attribute modifications / node removal |

### Styles Sub-panel

Shows all CSS rules applying to the selected element, sorted by specificity (most specific on top).

- **Crossed-out rules** are overridden by a higher-specificity rule.
- **Greyed rules** are invalid or not applicable.
- Click a property value to edit it live.
- Click the `+` button to add a new rule scoped to the current element.
- The `element.style` section at the top represents inline styles.
- Hold `Shift` and click a color swatch to cycle through color formats (`hex → rgb → hsl`).
- Click the colored square next to a color value to open the color picker, which also supports contrast ratio checking for accessibility.

```css
/* Styles panel shows computed cascade — example output */
element.style {
  color: red;               /* inline — highest specificity */
}
.card h1 {                  /* class + type */
  font-size: 2rem;
  color: blue;              /* overridden — struck through */
}
h1 {                        /* type only */
  font-size: 1.5rem;
}
```

### Computed Sub-panel

Shows the **final resolved value** of every CSS property after the cascade has been applied. Useful for
debugging why a property is not what you expect.

- Click the arrow next to a property to jump to the rule that set it in the **Styles** panel.
- Check **Show all** to see inherited and user-agent default properties.
- The **Box Model** diagram at the top visualises content / padding / border / margin dimensions.
  Click any region of the diagram to edit it live.

### Layout Sub-panel

Provides an overlay for **Flexbox** and **Grid** containers. Click the grid/flex icon badge that appears
next to containers in the Elements tree, or enable overlays from the **Layout** sub-panel.

Grid overlays show line numbers, track sizes, named areas, and gaps. Flex overlays show the main axis,
cross axis, and item alignment lines.

### Event Listeners Sub-panel

Lists all JavaScript event listeners attached to the selected node and its ancestors.

- Shows the source file and line number for each listener.
- **Passive** checkbox indicates listeners that cannot call `preventDefault()`.
- Click the file link to jump to the handler in the **Sources** panel.
- Uncheck **Ancestors** to see only listeners on the node itself.

### Accessibility Sub-panel

Shows the ARIA role, accessible name, accessible description, and the full accessibility tree rooted at the selected element.

---

## Console

The **Console** is a full JavaScript REPL with access to the page's `window` object. It serves two purposes:
viewing logged messages from the application code and running JavaScript interactively.

### Opening Context

By default the Console runs in the **top** frame. Use the JavaScript context selector (the dropdown showing
`top`) to switch into an `<iframe>`, a web worker, or a service worker context.

### Logging API

```javascript
// Basic levels — each has its own icon and color
console.log("General info");
console.info("ℹ️  Info");
console.warn("⚠️  Warning");          // yellow — treated as warning
console.error("❌ Error");            // red — includes stack trace

// Assertion — only logs if the condition is false
console.assert(1 === 2, "Math is broken");

// Formatted output — supports %s, %d, %i, %f, %o, %O, %c
console.log("User: %s, Age: %d", "Alice", 30);

// CSS styling in the console
console.log("%cStyled text", "color: hotpink; font-size: 20px; font-weight: bold");

// Objects — %o = interactive, %O = expanded
console.log("%o", document.body);

// Table — renders an array of objects as a table
console.table([
    { name: "Alice", age: 30 },
    { name: "Bob",   age: 25 }
]);

// Group — collapsible nested sections
console.group("Fetch results");
console.log("Status: 200");
console.log("Body: {...}");
console.groupEnd();

// Collapsed by default
console.groupCollapsed("Verbose data");
console.log("...");
console.groupEnd();

// Timer
console.time("loop");
for (let i = 0; i < 1e6; i++) {}
console.timeEnd("loop");           // "loop: 4.321ms"
console.timeLog("loop");          // logs intermediate time without stopping

// Count how many times a label has been called
console.count("login");
console.countReset("login");

// Stack trace from the current call site
console.trace("Where was I called?");

// Clear the console
console.clear();
```

### Console Utilities API

These functions are only available in the DevTools console — they are **not** part of the standard `console` API.

```javascript
// Shortcut for document.querySelector / querySelectorAll
$("h1")                         // returns first match
$$("a[href]")                   // returns NodeList of all matches

// Last expression value
$_                              // returns the result of the last evaluated expression

// Selected element in the Elements panel
$0                              // currently selected node
$1                              // previously selected node (up to $4)

// Inspect a node — jumps to it in Elements panel
inspect($0)
inspect(document.getElementById("app"))

// jQuery-like event listener shortcut
monitorEvents(window, "resize")     // logs all resize events
unmonitorEvents(window)

// Monitor all calls to a function
monitor(fetch)
unmonitor(fetch)

// Pause execution when the function is called (adds a breakpoint)
debug(myFunction)
undebug(myFunction)

// Copy a value as a string to the clipboard
copy(location.href)
copy(document.cookie)

// Get event listeners on an element
getEventListeners(document.querySelector("button"))

// XHR and Fetch logging in the console
// Enable via: Console settings → Log XMLHttpRequests

// Query objects by constructor — useful for finding all instances
queryObjects(Promise)
queryObjects(HTMLElement)

// Profile CPU usage
profile("myProfile")
profileEnd("myProfile")
```

### Live Expressions

Click the **eye icon** (Create live expression) to pin an expression that re-evaluates continuously in
real time — useful for watching `document.activeElement`, a scroll position, or a global variable
without typing it repeatedly.

```javascript
// Examples of useful live expressions
window.scrollY
document.activeElement
performance.memory.usedJSHeapSize
document.querySelectorAll(".active").length
```

### Console Filters

Use the filter bar to show only relevant messages:

| Filter | Meaning |
|--------|---------|
| `url:app.js` | Messages from a specific source file |
| `-url:extension` | Exclude messages from extensions |
| `/regex/` | Messages matching a regular expression |
| Text string | Plain substring search |
| Level buttons | Verbose / Info / Warnings / Errors |

Sidebar (click the funnel icon) groups messages by source URL for easier triage.

### Security Recon via Console

```javascript
// Check CSP headers reflected in blocked violations
// Listen for CSP violations
document.addEventListener("securitypolicyviolation", (e) => {
    console.warn("CSP violation:", e.blockedURI, "directive:", e.violatedDirective);
});

// Inspect all cookies accessible to JS (HttpOnly ones are hidden)
document.cookie

// Check for HTTPS-only context
window.isSecureContext    // true if served over HTTPS or localhost

// Check the origin
location.origin
location.protocol

// Enumerate localStorage and sessionStorage keys
Object.keys(localStorage)
Object.entries(localStorage)

// Find all forms and their action targets
$$("form").map(f => ({ action: f.action, method: f.method }))

// Find all external scripts loaded on the page
$$("script[src]").map(s => s.src)

// Check if a Service Worker is active
navigator.serviceWorker.controller

// Inspect all iframes and their origins
$$("iframe").map(f => ({ src: f.src, origin: new URL(f.src).origin }))

// Test for open redirects — check where redirect parameters point
new URLSearchParams(location.search).get("redirect")
```

---

## Sources

The **Sources** panel is the JavaScript debugger and file browser. It shows all resources loaded by the
page, lets you set breakpoints, and allows you to edit and persist files.

### Panel Layout

- **Navigator** (left pane): file tree of all loaded resources, grouped by origin. Tabs: Page, Overrides, Content scripts, Snippets.
- **Editor** (centre pane): source viewer / editor with syntax highlighting and breakpoint gutters.
- **Debugger** (right pane): breakpoint list, call stack, scope variables, and watch expressions.

### Breakpoints

Breakpoints pause JavaScript execution at a specific point, allowing you to inspect state.

| Breakpoint Type | How to Set |
|-----------------|-----------|
| **Line-of-code** | Click the line number gutter in the editor |
| **Conditional** | Right-click line number → **Add conditional breakpoint** → enter JS expression |
| **Logpoint** | Right-click line number → **Add logpoint** → acts like `console.log`, no pause |
| **DOM mutation** | Elements panel → right-click node → **Break on** |
| **XHR / Fetch** | Debugger pane → **XHR/Fetch Breakpoints** → `+` → URL substring |
| **Event listener** | Debugger pane → **Event Listener Breakpoints** → expand category |
| **Exception** | Click **Pause on exceptions** button (||) → optionally pause only on uncaught |
| **Function** | Console: `debug(myFn)` — pauses when `myFn` is called |

When paused:

```
▶ Resume                  F8
▶ Step over               F10  (executes current line, moves to next)
▶ Step into               F11  (enters function call)
▶ Step out                Shift+F11 (exits current function)
▶ Step (one instruction)  F9
```

The **Call Stack** in the right pane shows the chain of function calls that led to the pause. Click any
frame to jump to that context and inspect its local variables in **Scope**.

### Watch Expressions

Add JavaScript expressions to the **Watch** pane to see their value at every pause:

```javascript
user.id
JSON.stringify(state)
Array.from(document.querySelectorAll(".item")).length
performance.now()
```

### Scope Variables

Shows **Local**, **Closure**, **Script**, and **Global** scope. Variables can be edited in place by
double-clicking their value.

### Call Stack

Right-click any frame in the call stack to:
- **Restart frame** — re-run from the beginning of that function without a full page reload.
- **Black-box script** — hide third-party library frames (e.g., React, lodash) from the stack so you only see your own code.

### Source Maps

When code is compiled, transpiled, or minified, DevTools uses source maps (`.map` files) to map the
deployed code back to the original TypeScript, SCSS, or unminified JavaScript.

```json
// app.js.map — generated automatically by webpack/esbuild/Vite
{
  "version": 3,
  "sources": ["src/app.ts"],
  "mappings": "AAAA...",
  "sourcesContent": ["...original TypeScript..."]
}
```

If source maps are not loading:
- DevTools → Settings → **Enable JavaScript source maps** / **Enable CSS source maps**
- Check that the server serves `.map` files and that the `//# sourceMappingURL=` comment is present at the bottom of the minified file.

For security reasons, you may want to serve source maps only to authenticated users or internal networks, or
use the `x_google_ignoreList` extension in the source map to exclude vendor code.

### Overrides

**Overrides** let you replace a live server resource with a local file that persists across reloads — no
deploy needed.

1. Sources → **Overrides** tab → **Select folder for overrides** → choose a local directory.
2. In the Network panel, right-click any request → **Override content**.
3. Edit the file in the Sources editor and save (`Ctrl+S`).

Overrides can replace:
- JavaScript and CSS files
- HTTP response headers (via `.headers` files in the overrides folder)
- HTML pages

This is extremely useful for testing patches on production sites without a local dev server, or for
bypassing CSP headers temporarily while investigating security issues.

### Snippets

**Snippets** are small JS scripts stored in DevTools and runnable on any page.

1. Sources → **Snippets** tab → **New snippet**.
2. Write any JavaScript.
3. Run with `Ctrl+Enter` or right-click → **Run**.

```javascript
// Snippet: Dump all cookies as a table
const cookies = document.cookie.split("; ").map(c => {
    const [name, ...rest] = c.split("=");
    return { name, value: rest.join("=") };
});
console.table(cookies);

// Snippet: Find all inputs without labels (accessibility audit)
const inputs = $$("input, textarea, select");
const unlabelled = inputs.filter(i =>
    !i.id ||
    !document.querySelector(`label[for="${i.id}"]`)
);
console.table(unlabelled.map(i => ({ tag: i.tagName, type: i.type, name: i.name })));

// Snippet: Extract all links from the current page
const links = $$("a[href]").map(a => ({
    text: a.textContent.trim(),
    href: a.href,
    external: a.hostname !== location.hostname
}));
console.table(links.filter(l => l.external));
```

---

## Network

The **Network** panel records every HTTP request made by the page. It is the primary tool for performance
profiling, API debugging, and inspecting the security posture of web traffic.

### Toolbar Controls

| Control | Purpose |
|---------|---------|
| Record (red dot) | Start / stop capturing requests |
| Clear (⊘) | Clear the request log |
| Preserve log | Keep requests across navigations |
| Disable cache | Forces requests to bypass the browser cache (simulates first-time visitor) |
| Throttling | Simulate slow networks (Slow 3G, Fast 4G, custom profiles) |
| Offline | Simulate no network connection |

### Request Table Columns

Right-click the column header to add / remove columns. Key columns:

| Column | Meaning |
|--------|---------|
| **Name** | Filename or endpoint path |
| **Status** | HTTP status code (`200`, `304`, `404`, `500`, etc.) |
| **Type** | MIME type (`document`, `script`, `fetch`, `xhr`, `websocket`, etc.) |
| **Initiator** | What caused the request (parser, script, redirect) |
| **Size** | Transfer size / actual size (gzip vs uncompressed) |
| **Time** | Total request duration |
| **Waterfall** | Visual timeline bar |
| **Protocol** | `http/1.1`, `h2`, `h3` |
| **Priority** | Browser fetch priority (`Highest` for main document, `Low` for images below fold) |

### Filters

The filter bar supports text search, type buttons, and special property syntax:

```
domain:api.example.com          show only requests to this domain
status-code:401                 show only 401 responses
method:POST                     show only POST requests
larger-than:100k                show only responses > 100 KB
mime-type:application/json      show only JSON responses
scheme:http                     show only non-HTTPS requests (mixed content)
-url:analytics                  exclude analytics requests
is:running                      show active WebSocket connections
has-response-header:set-cookie  show responses that set cookies
mixed-content:all               show all mixed content
```

### Request Detail Tabs

Click any request to open the detail pane:

#### Headers

Shows the full **Request Headers** and **Response Headers**.

```
General
  Request URL: https://api.example.com/users
  Request Method: POST
  Status Code: 201 Created
  Remote Address: 93.184.216.34:443

Response Headers
  content-type: application/json; charset=utf-8
  strict-transport-security: max-age=31536000; includeSubDomains
  x-content-type-options: nosniff
  x-frame-options: DENY
  content-security-policy: default-src 'self'
  set-cookie: session=abc123; HttpOnly; Secure; SameSite=Strict

Request Headers
  authorization: Bearer eyJhbGci...
  content-type: application/json
  origin: https://example.com
```

> Click **view source** next to any header section to see the raw, unformatted headers.

#### Payload

Shows the request body — query string parameters (GET) or POST body. Toggle **view source** to see the
raw bytes, or **view decoded** to URL-decode the values.

#### Preview / Response

**Preview** renders HTML and images. **Response** shows the raw response body as text. JSON responses are
rendered as an interactive collapsible tree.

#### Cookies

Lists every cookie sent with the request and every `Set-Cookie` header in the response, along with all
cookie attributes: `Domain`, `Path`, `Expires`, `HttpOnly`, `Secure`, `SameSite`.

> A `⚠` icon next to a cookie indicates it is **blocked** — hover for the reason (e.g., SameSite mismatch, missing Secure attribute on HTTPS).

#### Timing

Breaks the full request lifecycle into its phases:

| Phase | What It Measures |
|-------|-----------------|
| **Queueing** | Time waiting for a free TCP slot or high-priority resource to finish |
| **Stalled** | Time waiting after being dequeued |
| **DNS Lookup** | Hostname resolution |
| **Initial Connection** | TCP handshake + retries |
| **SSL** | TLS negotiation |
| **Request Sent** | Time to transmit the request bytes |
| **Waiting (TTFB)** | Time to first byte — server processing time + one RTT |
| **Content Download** | Time to download the full response body |

High TTFB → slow server / database. High Content Download → large response or slow link.

### Copy as cURL

Right-click any request → **Copy** → **Copy as cURL** to get a fully reproducible command:

```bash
curl 'https://api.example.com/login' \
  -H 'Content-Type: application/json' \
  -H 'Authorization: Bearer eyJhbGci...' \
  --data-raw '{"username":"alice","password":"s3cr3t"}' \
  --compressed
```

This is invaluable for replaying requests outside the browser — in a terminal, Postman, or scripts.

### HAR Export

**HAR (HTTP Archive)** is a JSON format capturing the full session log.

- Right-click in the request table → **Save all as HAR (sanitized)** — excludes sensitive headers like `Cookie`, `Authorization`.
- **Save all as HAR (with sensitive data)** — includes all headers. Handle with care.
- Drag a `.har` file onto the request table to import and replay a session.

HAR files can be analysed at [toolbox.googleapps.com/apps/har_analyzer](https://toolbox.googleapps.com/apps/har_analyzer/).

### WebSockets

Filter by `WS` type to see WebSocket connections. Click a connection to see the **Messages** tab:

- **Green** = outgoing (client → server)
- **White** = incoming (server → client)
- **Yellow** = protocol frames (ping, pong, close)

### Blocking Requests

In the **Network request blocking** drawer (three-dot menu → More tools → Network request blocking):

- Add URL patterns (`*.tracking.com`, `ads.js`) to block them.
- Blocked requests appear in red in the log.
- Useful for testing graceful degradation when third-party scripts fail, or for simulating WAF blocking.

### Throttling Custom Profiles

Create a precise profile under Settings → **Throttling** → Add profile:

```
Name:       Flaky 4G
Download:   3000 kb/s
Upload:     750 kb/s
Latency:    100 ms
```

### Security-Focused Network Analysis

```
# Look for these security issues in the Network panel:

1. scheme:http — any resource loaded over plain HTTP (mixed content)
2. Requests to unexpected third-party domains (data exfiltration or supply-chain attacks)
3. Cookies without HttpOnly, Secure, or SameSite=Strict/Lax
4. Missing security headers in responses:
     strict-transport-security (HSTS)
     content-security-policy (CSP)
     x-frame-options or CSP frame-ancestors
     x-content-type-options: nosniff
     referrer-policy
     permissions-policy
5. Authorization tokens in query strings (visible in URLs, cached in logs)
6. Verbose error responses exposing stack traces or internal paths
7. Overly broad CORS headers: Access-Control-Allow-Origin: *
8. Long max-age on sensitive cookies
9. Large JWT payloads that may contain sensitive claims
10. HTTP/1.1 connections instead of HTTP/2 or HTTP/3 (performance + security downgrade risk)
```

---

## Security

The **Security** panel gives a high-level overview of the TLS/HTTPS security of the current page.

### Security Overview

The panel header shows one of three states:

- **Secure** (green lock) — the main origin is served over valid HTTPS with no issues.
- **Not secure** (red warning) — the page is HTTP, has an invalid certificate, or has mixed content.
- **Info** — HTTPS but with minor warnings (e.g., some resources loaded over HTTP).

### Certificate Inspection

Click **View certificate** to see the full TLS certificate chain:

```
Subject:       CN=*.example.com, O=Example Inc., C=US
Issuer:        CN=DigiCert TLS RSA SHA256 2020 CA1, O=DigiCert Inc, C=US
Valid from:    Jan  1 00:00:00 2024 GMT
Valid to:      Jan  1 00:00:00 2025 GMT
Serial Number: 0f:a4:77:...
Public Key:    RSA 2048-bit
SANs:          *.example.com, example.com
Signature Alg: SHA256WithRSAEncryption
```

Key things to check:

| Field | What to Look For |
|-------|----------------|
| Valid to | Is the cert expired? |
| Issuer | Is it a trusted CA or a self-signed / unexpected CA? (Man-in-the-middle) |
| SANs | Does the domain match exactly — no wildcard mismatches? |
| Key length | RSA ≥ 2048-bit or ECC P-256/P-384 |
| HSTS preloaded | Is the domain in the HSTS preload list? |

### Connection Details

Below the certificate, the panel shows:

```
Protocol:       TLS 1.3
Key exchange:   X25519
Cipher:         AES_128_GCM
```

Flags to investigate:
- **TLS 1.0 / 1.1** — deprecated, vulnerable to POODLE, BEAST. Should be TLS 1.2 minimum, 1.3 preferred.
- **RC4, 3DES, CBC ciphers** — weak, deprecated.
- **Non-forward-secret key exchange** — RSA key exchange (without ECDHE/DHE) means past traffic can be decrypted if the private key is later compromised.

### Origins List

The left sidebar shows every origin from which resources were loaded. Click an origin to see its
certificate and connection details. Origins marked with a warning icon have issues (expired cert,
mixed content, weak cipher).

### Mixed Content

Mixed content occurs when an HTTPS page loads HTTP sub-resources:

- **Active mixed content** (scripts, iframes, XHR) — blocked by browsers. Shown as errors in the Security panel and Console.
- **Passive mixed content** (images, audio, video) — still loaded but flagged. Allows SSL-stripping attacks where the image can be swapped.

Find mixed content quickly:

```
# In the Network filter bar:
scheme:http

# In the Console filter:
Mixed Content
```

### HSTS (HTTP Strict Transport Security)

If the server sends `Strict-Transport-Security: max-age=31536000; includeSubDomains; preload`, the browser
will refuse all HTTP connections to that host for the duration, even if the user types `http://`.

Check if a domain is in the preload list: [hstspreload.org](https://hstspreload.org)

To clear HSTS state for a domain (for local testing):
- Navigate to `chrome://net-internals/#hsts`
- Enter the domain under **Delete domain security policies**

---

## Application

The **Application** panel manages all client-side storage and service workers. Critical for both debugging
persistent state and for security reconnaissance of what a site stores on the user's machine.

### Storage

#### Local Storage & Session Storage

Key-value stores accessible via JavaScript.

```javascript
// Console: inspect / manipulate storage
localStorage.getItem("token")
localStorage.setItem("debug", "true")
localStorage.removeItem("token")
localStorage.clear()

// Session storage (cleared when tab closes)
sessionStorage.getItem("csrf_token")
```

In the Application panel, click an origin under **Local storage** or **Session storage** to see all keys and values.
Double-click a value to edit it. Right-click to delete.

**Security issues to look for:**
- Sensitive tokens (JWTs, API keys, session IDs) stored in `localStorage` — accessible to any JavaScript on the page, making them vulnerable to XSS.
- `sessionStorage` is slightly safer but still accessible to XSS.
- Prefer `HttpOnly` cookies for session tokens.

#### Cookies

The **Cookies** section shows every cookie for the current origin with full attribute details:

| Column | Meaning |
|--------|---------|
| Name | Cookie name |
| Value | Cookie value |
| Domain | Which hosts receive the cookie |
| Path | Which URL paths receive the cookie |
| Expires / Max-Age | Expiry timestamp. "Session" = deleted on close |
| Size | Size in bytes |
| HttpOnly | ✓ = JS cannot read this cookie (`document.cookie` hides it) |
| Secure | ✓ = only sent over HTTPS |
| SameSite | `Strict` / `Lax` / `None` — CSRF protection level |
| Priority | `Low` / `Medium` / `High` — Chrome's cookie eviction priority |
| Partition key | Indicates partitioned (CHIPS) cookies |

**Security audit checklist for cookies:**
- Session tokens must be `HttpOnly` + `Secure` + `SameSite=Strict` or `Lax`.
- `SameSite=None` cookies require `Secure` and are sent cross-site — verify they are intentional.
- Long-lived authentication cookies (`Expires` years in the future) are a risk if stolen.
- Cookies with `Domain=.example.com` (leading dot) are sent to all subdomains — subdomain takeover risk.

#### IndexedDB & Web SQL

Full databases in the browser. The Application panel lets you browse tables and run queries.
Check for sensitive data (tokens, PII) stored unencrypted in IndexedDB.

#### Cache Storage

Shows the caches populated by service workers (`caches.put()`). Lists every URL cached and the full
response. Check that sensitive API responses with user data are not cached here.

#### Trust Tokens & Interest Groups

Privacy-focused APIs (formerly FLoC). Visible in Application for debugging/auditing.

### Service Workers

A service worker is a JavaScript file that runs in a background thread, intercepts network requests, and
can serve responses from the cache. It is the backbone of Progressive Web Apps (PWAs).

```
Status:  activated and is running
Source:  /sw.js
Clients: https://example.com/
```

Controls in the panel:

| Control | Purpose |
|---------|---------|
| **Update** | Force an update check for the SW script |
| **Unregister** | Remove the service worker |
| **Offline** | Toggle offline mode for this origin |
| **Bypass for network** | Skip the SW and go directly to the network |
| **Update on reload** | Force SW to update on every page reload (for development) |

Click the SW source file to inspect it in Sources.

**Security note:** A compromised or maliciously injected service worker can intercept all requests for
the origin indefinitely. After a penetration test, verify no unauthorised SWs are registered at
`chrome://serviceworker-internals/`.

### Frames

Lists every frame context on the page (main frame, iframes, popups) with their origins and CSP policies.
Useful for understanding the security context of embedded third-party content and verifying that iframes
are sandboxed correctly.

---

## Sources — Advanced Features

### Workspaces

Map a DevTools editing session to a local folder so that edits in the Sources panel write directly to
disk.

1. Sources → **Filesystem** tab → **Add folder to workspace** → select your project `src/`.
2. Chrome asks for permission. Grant it.
3. A green dot appears next to files that are mapped. `Ctrl+S` in the editor now saves to the file.

Changes made via the **Styles** panel to mapped CSS files also persist to disk.

### Local Overrides for Security Testing

Overrides (covered above) are the most powerful DevTools feature for security testing:

```
# Use-cases:
1. Remove or modify CSP headers to test what a page would do without them.
2. Modify CORS response headers to test cross-origin scenarios.
3. Replace a CDN-hosted library with a patched local version to test a prototype fix.
4. Add console.log() to minified production code without a local build.
5. Replace a script with an XSS payload to verify CSP effectiveness.
```

Override HTTP headers by creating a `.headers` file in the overrides folder:

```json
[
  {
    "applyTo": "api/user",
    "headers": [
      { "name": "Content-Security-Policy", "value": "default-src *" },
      { "name": "Access-Control-Allow-Origin", "value": "*" }
    ]
  }
]
```

---

## Performance

The **Performance** panel records a CPU / rendering / memory trace for profiling page load and runtime
performance.

### Recording

- Click **Record** (⏺) then interact with the page, then **Stop**.
- Or click **Reload** (⟳) to record from the very beginning of the page load.

### Flame Chart

The main view is a **flame chart** — a top-down stack visualization where the x-axis is time and the
y-axis is the call stack depth.

```
Main Thread
│
├─ Parse HTML ──────────────────────────────
│   └─ Parse Stylesheet
├─ Evaluate Script ─────────────────────────
│   └─ (anonymous) → fetchData → processJSON
│       └─ Recalculate Style
│           └─ Layout ────────────────────
│               └─ Paint
│                   └─ Composite Layers
└─ ───────────────────────────────────────
     0 ms           100 ms          200 ms
```

Click any bar to see its duration and source location in the Summary tab at the bottom.

### Core Web Vitals

DevTools marks Core Web Vitals on the timeline:

| Metric | What It Measures | Good |
|--------|-----------------|------|
| **LCP** (Largest Contentful Paint) | When the main content is visible | ≤ 2.5 s |
| **CLS** (Cumulative Layout Shift) | Visual stability — unexpected layout shifts | ≤ 0.1 |
| **INP** (Interaction to Next Paint) | Responsiveness to user input | ≤ 200 ms |
| **FID** (First Input Delay) | Legacy input responsiveness | ≤ 100 ms |
| **TTFB** (Time to First Byte) | Server response speed | ≤ 800 ms |

### Long Tasks

Long tasks (> 50 ms on the main thread) are highlighted in red. They block user interaction.
Look for JavaScript that runs synchronously for long periods.

### Rendering Panel (in drawer)

Open from the three-dot menu → **Rendering**:

| Option | Use |
|--------|-----|
| Paint flashing | Highlights areas being repainted in green |
| Layer borders | Shows composited layer boundaries |
| FPS meter | Real-time frame rate overlay |
| Scrolling performance issues | Highlights non-passive event listeners |
| Core Web Vitals | Overlay of LCP element and CLS regions |
| Emulate CSS media: prefers-color-scheme | Test dark/light mode |
| Emulate CSS media: prefers-reduced-motion | Test reduced motion |

---

## Lighthouse

**Lighthouse** is an automated auditing tool built into DevTools. Run it from the **Lighthouse** tab.

Select categories (Performance, Accessibility, Best Practices, SEO, PWA) and device (Mobile / Desktop),
then click **Analyze page load**.

### Score Categories

- **Performance**: LCP, CLS, INP, FCP, Speed Index, TTFB.
- **Accessibility**: ARIA labels, color contrast, keyboard navigation, form labels.
- **Best Practices**: HTTPS, no deprecated APIs, correct image aspect ratios, CSP policy, no mixed content.
- **SEO**: meta description, crawlable links, robots.txt, structured data.

### Security-Related Lighthouse Checks

Lighthouse flags several security issues in the **Best Practices** category:

```
✗ Does not use HTTPS
✗ Uses vulnerable JavaScript libraries (compared against Snyk database)
✗ Issues logged to the console
✗ Missing Content Security Policy
✗ Allows users to paste into password fields (false positive — do not fix this)
✗ Page has mixed content
```

---

## Device Mode

Accessed via the **Toggle Device Toolbar** button (`Ctrl+Shift+M` / `Cmd+Shift+M`) or the phone icon in
the top-left of DevTools.

### Responsive Mode

Drag the viewport handles to test arbitrary widths. The toolbar shows the current dimensions and
device pixel ratio (DPR).

### Device Emulation

Select a device from the dropdown (iPhone 14, Pixel 7, iPad Air, etc.) to emulate:
- Viewport size and DPR
- Touch events instead of mouse events
- User-Agent string
- Screen orientation (portrait / landscape toggle)

### Throttling in Device Mode

Independently set CPU throttling (4x slowdown, 6x slowdown) and network throttling to simulate
mobile performance.

### Custom Devices

Add custom device profiles under Settings → **Devices** for internal test devices or unusual screen sizes.

---

## Keyboard Shortcuts Reference

### Global

| Shortcut | Action |
|----------|--------|
| `F12` / `Ctrl+Shift+I` | Open / close DevTools |
| `Ctrl+Shift+P` | Command Menu |
| `Ctrl+[` / `Ctrl+]` | Switch to previous / next panel |
| `Ctrl+Shift+M` | Toggle Device Mode |
| `Ctrl+Shift+C` | Inspect element mode |
| `Esc` | Toggle Console drawer |
| `?` | Open DevTools settings |

### Elements Panel

| Shortcut | Action |
|----------|--------|
| `H` | Hide / show selected element |
| `Delete` | Delete selected node |
| `Ctrl+Z` | Undo DOM change |
| `Arrow keys` | Navigate the DOM tree |
| `Enter` | Edit selected node |

### Sources / Debugger

| Shortcut | Action |
|----------|--------|
| `F8` | Resume execution |
| `F10` | Step over |
| `F11` | Step into |
| `Shift+F11` | Step out |
| `Ctrl+B` | Toggle breakpoint on current line |
| `Ctrl+G` | Go to line number |
| `Ctrl+P` | Go to file |
| `Ctrl+Shift+O` | Go to function / symbol in current file |

### Network Panel

| Shortcut | Action |
|----------|--------|
| `Ctrl+E` | Toggle recording |
| `Ctrl+R` | Clear and reload |
| `R` (on selected request) | Replay XHR request |
| `Shift+hover` | Show initiators (green) and dependencies (red) |

---

## Tips & Tricks

```javascript
// Quick DOM queries in the Console
document.querySelector("#app")    // standard
$("#app")                          // DevTools shorthand

// Inspect the properties of an object cleanly
console.dir(document.body)

// Capture a full-page screenshot
// Command Menu → Capture full size screenshot

// Find which CSS rule is responsible for a computed value
// Elements → Computed → click the arrow next to any property

// Debug a function you cannot find in source
debug(someGlobalFunction)         // next call will pause

// Replay any request with modified headers / body
// Network → right-click request → Override content

// Check if a JWT is expired in the console
const [, payload] = document.cookie.match(/token=([^;]+)/)[1].split(".");
JSON.parse(atob(payload))         // decode without verification — development only!

// Emulate prefers-color-scheme for dark mode testing
// Rendering panel → Emulate CSS media feature prefers-color-scheme → dark

// See all requests that set cookies
// Network filter: has-response-header:set-cookie

// Profile a specific function
console.profile("myFn");
myExpensiveFunction();
console.profileEnd("myFn");
// → opens in Performance panel
```

---

## Common Security Checks Workflow

A repeatable checklist using DevTools for a black-box web security assessment:

```
1. HTTPS & TLS
   Security panel → check TLS version (≥ 1.2), cipher suite, cert validity, HSTS

2. Security Headers
   Network → click main document request → Response Headers
   Look for: CSP, HSTS, X-Frame-Options, X-Content-Type-Options, Referrer-Policy

3. Cookies
   Application → Cookies → audit all cookies for HttpOnly, Secure, SameSite

4. Mixed Content
   Security panel + Network filter (scheme:http)

5. Client-Side Storage
   Application → localStorage / sessionStorage / IndexedDB → look for tokens, PII

6. Third-Party Scripts
   Network → examine external JS domains, check for SRI (integrity attribute)
   Elements → $$("script[src]").map(s => s.src)

7. CORS
   Network → filter Fetch/XHR → check Access-Control-Allow-Origin response headers

8. Information Disclosure
   Console → watch for verbose errors, internal paths, stack traces

9. Service Workers
   Application → Service Workers → check for unexpected registrations

10. JWT Inspection
    Console: copy token from localStorage or cookie, split and base64-decode the payload

11. Overrides for Header Manipulation
    Sources → Overrides → create .headers file to test removal of security headers

12. Request Replay
    Network → Copy as cURL → modify parameters → replay in terminal
```
