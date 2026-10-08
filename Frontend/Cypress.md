# Cypress

**Cypress** is a JavaScript-based end-to-end (E2E) testing framework that runs **inside the browser**, alongside the
application under test. Unlike Selenium-style tools that drive the browser from the outside over the network, Cypress
executes in the same run-loop as your app, giving it native access to the DOM, network layer, and JavaScript runtime.
It bundles a test runner, assertion library, mocking tools, and a time-travel debugger into a single package.

**Opinions** (things Cypress decides for you):

- **All-in-one**: the runner, assertion library (Chai), mocking/stubbing (Sinon), and retry logic ship together — no
  separate wiring of Mocha + Chai + WebDriver.

- **In-browser execution**: tests run in the same context as the app, so there is no network lag between commands and
  the page.

- **Automatic waiting**: commands **retry** until the element exists / the assertion passes, eliminating most manual
  `sleep`/`wait` calls.

- **Command chaining**: tests read as fluent chains (`cy.get(...).click()`), each command yielding a subject to the
  next.

- **Time-travel debugging**: the UI captures a DOM snapshot at every step so you can hover back through the test.

- **Deterministic control of the network**: requests can be stubbed, spied on, and waited for declaratively.

---

## Test Types

Cypress supports two testing modes from the same project:

- **End-to-End (E2E)**: drives the fully running application in a real browser as a user would — visiting URLs,
  clicking, typing, and asserting. Specs live in `cypress/e2e/`.

- **Component testing**: mounts a single component (Angular, React, Vue, Svelte) in isolation and tests it directly,
  without booting the whole app. Specs live beside the component or in `cypress/component/`.

---

## Installation & Set-Up

Install Cypress as a dev dependency in an existing project.

```bash
npm install -D cypress

npx cypress --version          # verify installation
```

### Opening Cypress

```bash
npx cypress open               # launch the interactive Test Runner (GUI)
npx cypress run                # run all tests headlessly (CI mode)
```

The first `cypress open` scaffolds the folder structure and a `cypress.config.ts`, and walks you through choosing E2E
or component testing and a browser.

### Angular Integration (via schematic)

For an Angular workspace, the official schematic wires everything up and adds an `ng e2e` target:

```bash
ng add @cypress/schematic      # installs Cypress + configures angular.json
ng e2e                         # run E2E tests through the Angular CLI
```

---

## CLI Commands

- `cypress open`: opens the interactive Test Runner GUI with time-travel debugging.
  - `--e2e` / `--component`: open directly in a given testing mode.
  - `--browser chrome`: pick the browser.

- `cypress run`: runs tests headlessly (default for CI).
  - `--spec <glob>`: run only matching spec files.
  - `--browser <name>`: `chrome`, `firefox`, `edge`, `electron`.
  - `--headed`: show the browser while running.
  - `--record --key <key>`: record results to Cypress Cloud (Dashboard).
  - `--config <k=v>`: override config values inline.
  - `--env <k=v>`: pass environment variables.

- `cypress info`: prints detected browsers and system info.
- `cypress verify`: verifies the installed binary is runnable.

```bash
npx cypress run --spec "cypress/e2e/auth/**" --browser chrome --headed
npx cypress run --env apiUrl=http://localhost:3000 --config video=false
```

---

## Project Structure

A typical Cypress layout scaffolded by the runner:

```txt
my-app/
├── cypress/
│   ├── e2e/                      ← end-to-end spec files (*.cy.ts)
│   │   ├── login.cy.ts
│   │   └── users.cy.ts
│   ├── component/                ← component test specs
│   ├── fixtures/                 ← static test data (JSON, images)
│   │   └── users.json
│   ├── support/
│   │   ├── commands.ts           ← custom commands (cy.login(), etc.)
│   │   ├── e2e.ts                ← runs before every E2E spec (global hooks)
│   │   └── component.ts          ← runs before every component spec
│   └── downloads/                ← files downloaded during tests
├── cypress.config.ts             ← main configuration
├── tsconfig.json
└── package.json
```

### `cypress.config.ts`

The central configuration file defines per-mode settings and plugins.

```ts
import { defineConfig } from "cypress";

export default defineConfig({
  e2e: {
    baseUrl: "http://localhost:4200",   // prefix for cy.visit("/")
    specPattern: "cypress/e2e/**/*.cy.{ts,js}",
    supportFile: "cypress/support/e2e.ts",
    viewportWidth: 1280,
    viewportHeight: 720,
    defaultCommandTimeout: 4000,        // retry window per command (ms)
    video: false,
    setupNodeEvents(on, config) {
      // register plugins / node-side event listeners here
      return config;
    },
  },

  component: {
    devServer: {
      framework: "angular",
      bundler: "webpack",
    },
    specPattern: "**/*.cy.ts",
  },

  env: {
    apiUrl: "http://localhost:3000",    // read via Cypress.env("apiUrl")
  },
});
```

---

## Test Structure

Cypress uses **Mocha's** BDD syntax for structuring tests and **Chai** for assertions.

- `describe(label, fn)`: groups related tests into a suite.
- `context(label, fn)`: an alias for `describe`, used for readability.
- `it(label, fn)`: a single test case (alias `specify`).
- `before` / `after`: run once before/after all tests in the block.
- `beforeEach` / `afterEach`: run before/after **each** test.
- `.only` / `.skip`: focus on or skip a suite/test (`it.only`, `describe.skip`).

```ts
describe("Login page", () => {
  beforeEach(() => {
    cy.visit("/login");          // runs before every test
  });

  it("shows an error on bad credentials", () => {
    cy.get("[data-cy=email]").type("wrong@example.com");
    cy.get("[data-cy=password]").type("badpass");
    cy.get("[data-cy=submit]").click();
    cy.contains("Invalid credentials").should("be.visible");
  });

  it.skip("remembers the user (not implemented yet)", () => {
    // skipped
  });
});
```

---

## Commands & Chaining

**Cypress commands** are chained and **asynchronous** — they don't execute immediately but are enqueued and run in
order. Each command yields a **subject** to the next. You never use `await`; Cypress manages the queue.

- `cy.visit(url)`: navigates to a page (relative to `baseUrl`).
- `cy.get(selector)`: queries the DOM, retrying until the element appears.
- `cy.contains(text)`: finds an element containing the given text.
- `cy.find(selector)`: searches **within** the previous subject.
- `cy.first()` / `cy.last()` / `cy.eq(index)`: narrow a set of matched elements.
- `cy.children()` / `cy.parent()` / `cy.siblings()`: traverse the DOM tree.
- `cy.wrap(value)`: wraps any value so it can be chained/asserted on.

```ts
cy.visit("/users");
cy.get("table tbody tr")      // all rows
  .first()                    // first row
  .find("td.name")            // its name cell
  .should("have.text", "Alice");
```

> **Commands are not promises.** You cannot `return` or `await` them. To act on a yielded value, use `.then()`.

### `.then()` — Working with Yielded Subjects

```ts
cy.get("[data-cy=counter]").then(($el) => {
  const count = parseInt($el.text(), 10);   // jQuery element → value
  expect(count).to.be.greaterThan(0);
});
```

---

## Selecting Elements

Cypress recommends **dedicated test attributes** (`data-cy`, `data-test`) over CSS classes or IDs, which change for
styling reasons and make tests brittle.

```html
<button data-cy="submit">Save</button>
```

```ts
cy.get("[data-cy=submit]");          // preferred: resilient to style changes
cy.get("#submit");                   // by id
cy.get(".btn-primary");              // by class (fragile)
cy.contains("button", "Save");       // by tag + text
cy.get("input[name=email]");         // by attribute
```

**Selector priority (most → least recommended):** `data-cy` / `data-test` → `data-*` semantic attrs → ARIA roles /
text → IDs → CSS classes → tag/attribute chains.

---

## Interacting with Elements

Commands that act on the yielded element. They auto-wait for the element to be **actionable** (visible, not disabled,
not covered).

- `.click(options?)`: clicks an element. `{ force: true }` bypasses actionability checks; `{ multiple: true }` clicks all.
- `.dblclick()` / `.rightclick()`: double / right click.
- `.type(text, options?)`: types into an input. Supports special sequences like `{enter}`, `{backspace}`, `{selectall}`.
- `.clear()`: clears an input or textarea.
- `.check()` / `.uncheck()`: toggle checkboxes/radios.
- `.select(value)`: choose an option from a `<select>`.
- `.focus()` / `.blur()`: focus management.
- `.scrollIntoView()` / `.scrollTo(position)`: scroll handling.
- `.trigger(event)`: dispatch a raw DOM event (e.g. `mouseover`).

```ts
cy.get("[data-cy=email]").type("alice@example.com");
cy.get("[data-cy=password]").type("secret{enter}");   // submit via Enter
cy.get("[data-cy=terms]").check();
cy.get("[data-cy=country]").select("Germany");
cy.get("[data-cy=modal-close]").click({ force: true });
```

### Keyboard & Special Characters

```ts
cy.get("input").type("{selectall}{backspace}");   // clear via keystrokes
cy.get("input").type("Hello{leftarrow}{leftarrow}X");
cy.get("body").type("{esc}");                     // press Escape globally
```

---

## Assertions

Cypress bundles **Chai** (with `chai-jquery` and `sinon-chai`). Assertions **retry** until they pass or time out.
There are two styles:

### Implicit Assertions — `.should()` / `.and()`

Chained directly onto a subject; the most idiomatic form.

```ts
cy.get("[data-cy=title]")
  .should("be.visible")
  .and("have.text", "Dashboard")
  .and("have.class", "active");

cy.get("input").should("have.value", "alice");
cy.get("li").should("have.length", 3);
cy.get("[data-cy=btn]").should("be.disabled");
cy.url().should("include", "/users");
cy.get(".alert").should("contain.text", "Saved");
```

**Common assertion chains:**

| Assertion | Checks |
|-----------|--------|
| `be.visible` / `not.be.visible` | Element visibility |
| `exist` / `not.exist` | Presence in the DOM |
| `have.text` / `contain.text` | Exact / partial text |
| `have.value` | Input value |
| `have.class` / `have.attr` | Class / attribute |
| `have.length` | Number of matched elements |
| `be.checked` / `be.disabled` | Form control state |
| `include` / `match` | String containment / regex |

### Explicit Assertions — `expect` / `assert`

Used inside `.then()` for custom logic.

```ts
cy.get("[data-cy=count]").then(($el) => {
  expect($el.text()).to.match(/^\d+$/);
  expect($el).to.have.length(1);
});
```

---

## Network Requests

Cypress intercepts and controls the network with `cy.intercept()`, enabling **spying**, **stubbing**, and **waiting**
on requests — essential for deterministic tests.

- `cy.intercept(method, url, response?)`: intercepts matching requests.
  - As a **spy**: omit the response to simply observe/wait on real requests.
  - As a **stub**: provide a response object/fixture to fake the backend.
- `cy.request(options)`: makes a **real** HTTP request outside the app (e.g. seeding data), bypassing the browser.
- Aliasing with `.as(name)` lets you `cy.wait("@name")` for a request to complete.

### Spying & Waiting

```ts
cy.intercept("GET", "/api/users").as("getUsers");   // spy, no stub
cy.visit("/users");
cy.wait("@getUsers").its("response.statusCode").should("eq", 200);
```

### Stubbing a Response

```ts
cy.intercept("GET", "/api/users", {
  statusCode: 200,
  body: [{ id: 1, name: "Alice" }],
}).as("getUsers");

cy.visit("/users");
cy.wait("@getUsers");
cy.get("table tbody tr").should("have.length", 1);
```

### Stubbing with a Fixture

```ts
cy.intercept("GET", "/api/users", { fixture: "users.json" }).as("getUsers");
```

### Asserting on Request Payloads

```ts
cy.intercept("POST", "/api/users").as("createUser");
cy.get("[data-cy=submit]").click();
cy.wait("@createUser").then((interception) => {
  expect(interception.request.body).to.deep.equal({
    name: "Bob",
    email: "bob@example.com",
  });
  expect(interception.response?.statusCode).to.eq(201);
});
```

### Direct Requests (seeding / teardown)

```ts
cy.request("POST", "/api/test/reset");                 // reset DB before a test
cy.request({
  method: "POST",
  url: "/api/login",
  body: { email: "a@b.c", password: "secret" },
}).then((res) => {
  window.localStorage.setItem("token", res.body.access_token);
});
```

---

## Fixtures

**Fixtures** are static files (usually JSON) in `cypress/fixtures/` holding reusable mock data. Load them with
`cy.fixture()` or reference them directly in `cy.intercept()`.

```json
// cypress/fixtures/users.json
[
  { "id": 1, "name": "Alice", "email": "alice@example.com" },
  { "id": 2, "name": "Bob",   "email": "bob@example.com" }
]
```

```ts
cy.fixture("users.json").then((users) => {
  expect(users).to.have.length(2);
});

// or pass straight into an intercept:
cy.intercept("GET", "/api/users", { fixture: "users.json" });
```

---

## Aliases

**Aliases** (`.as(name)`) store a reference to a subject, intercept, or request so it can be reused later with the
`@name` syntax. This avoids re-querying and makes waits explicit.

```ts
cy.get("[data-cy=submit]").as("submitBtn");
cy.get("@submitBtn").click();           // reuse the element

cy.intercept("GET", "/api/data").as("loadData");
cy.wait("@loadData");                   // wait for the request

cy.wrap({ id: 1 }).as("user");
cy.get("@user").should("have.property", "id", 1);
```

---

## Hooks & Setup

Lifecycle hooks share setup/teardown across tests. A common pattern is to seed state and set up intercepts in
`beforeEach`.

```ts
describe("Users dashboard", () => {
  before(() => {
    cy.request("POST", "/api/test/seed");   // once, before all tests
  });

  beforeEach(() => {
    cy.intercept("GET", "/api/users", { fixture: "users.json" }).as("getUsers");
    cy.visit("/users");
    cy.wait("@getUsers");
  });

  afterEach(() => {
    cy.screenshot();            // capture state after each test
  });

  it("lists users", () => {
    cy.get("table tbody tr").should("have.length", 2);
  });
});
```

---

## Custom Commands

Define reusable commands in `cypress/support/commands.ts` to encapsulate repeated flows (login, navigation, etc.).

- `Cypress.Commands.add(name, fn)`: registers a new `cy.name()` command.
- `Cypress.Commands.overwrite(name, fn)`: overrides a built-in command.

```ts
// cypress/support/commands.ts
Cypress.Commands.add("login", (email: string, password: string) => {
  cy.session([email, password], () => {        // cache the session
    cy.request("POST", "/api/login", { email, password }).then((res) => {
      window.localStorage.setItem("token", res.body.access_token);
    });
  });
});

// TypeScript typing for the custom command
declare global {
  namespace Cypress {
    interface Chainable {
      login(email: string, password: string): Chainable<void>;
    }
  }
}
export {};
```

```ts
// usage in any spec
beforeEach(() => {
  cy.login("alice@example.com", "secret");
  cy.visit("/dashboard");
});
```

### `cy.session()` — Caching Login State

`cy.session(id, setup)` caches cookies, `localStorage`, and `sessionStorage` across tests, so you log in once instead
of per test, drastically speeding up suites.

---

## Working with the DOM & App State

- `cy.url()`: yields the current URL. `cy.location(part)`: yields a location part (`pathname`, `search`, `hash`).
- `cy.title()`: the document title.
- `cy.window()`: the app's `window` object. `cy.document()`: the `document`.
- `cy.go("back" | "forward")`: browser history navigation.
- `cy.reload()`: reloads the page.
- `cy.viewport(width, height)`: resize the viewport (responsive testing).

```ts
cy.url().should("include", "/dashboard");
cy.location("pathname").should("eq", "/users/1");
cy.title().should("eq", "My App");

cy.window().its("localStorage.token").should("exist");
cy.window().then((win) => win.scrollTo(0, 500));

cy.viewport("iphone-x");             // preset device
cy.viewport(1920, 1080);             // custom size
```

### Cookies & Storage

```ts
cy.setCookie("session", "abc123");
cy.getCookie("session").should("have.property", "value", "abc123");
cy.clearCookies();
cy.clearLocalStorage();
```

---

## Stubbing, Spies & Clock

Cypress bundles **Sinon** for stubbing functions and controlling time.

- `cy.stub()`: creates a stub function whose behavior you control and whose calls you assert.
- `cy.spy()`: wraps a real function to record calls without changing behavior.
- `cy.clock()`: freezes/controls `Date`, `setTimeout`, `setInterval` in the app.
- `cy.tick(ms)`: advances the frozen clock, flushing timers.

```ts
it("calls the callback on click", () => {
  const onClick = cy.stub().as("handler");
  cy.mount(MyButton, { props: { onClick } });   // component test
  cy.get("button").click();
  cy.get("@handler").should("have.been.calledOnce");
});

it("controls time", () => {
  cy.clock();
  cy.visit("/");
  cy.tick(5000);                   // fast-forward 5s (e.g. a toast auto-dismiss)
  cy.get(".toast").should("not.exist");
});
```

---

## Component Testing (Angular)

Component tests mount a single Angular component in isolation using `cy.mount()`.

- `cy.mount(Component, config)`: mounts the component with inputs, providers, and imports.
- Interact and assert with the same `cy.*` commands as E2E.

```ts
// button.component.cy.ts
import { ButtonComponent } from "./button.component";

describe("ButtonComponent", () => {
  it("renders the label and emits on click", () => {
    const onClick = cy.stub().as("clicked");

    cy.mount(ButtonComponent, {
      componentProperties: {
        label: "Save",
        clicked: { emit: onClick } as any,   // stub the @Output
      },
    });

    cy.get("button").should("have.text", "Save").click();
    cy.get("@clicked").should("have.been.calledOnce");
  });
});
```

Mounting with providers and imports:

```ts
cy.mount(UserCardComponent, {
  componentProperties: { user: { id: 1, name: "Alice" } },
  imports: [HttpClientTestingModule],
  providers: [{ provide: UserService, useValue: mockService }],
});
```

---

## Debugging

Cypress offers several tools to inspect failing tests.

- **Time-travel**: hover over commands in the Runner to see DOM snapshots at each step.
- `cy.pause()`: pauses the test, letting you step through commands manually.
- `cy.debug()`: logs the current subject and triggers a `debugger` breakpoint.
- `.then(($el) => { debugger; })`: drop into DevTools with the subject in scope.
- `cy.log(message)`: prints a custom message to the command log.
- `cy.screenshot()`: captures a screenshot (auto-taken on failure in `run` mode).

```ts
cy.get("[data-cy=list]")
  .debug()                        // inspect the subject in DevTools
  .find("li")
  .should("have.length", 3);

cy.log("About to submit the form");
cy.pause();                       // halt here to inspect manually
```

> In headless `cypress run`, Cypress automatically records **videos** and captures **screenshots on failure**,
> stored under `cypress/videos/` and `cypress/screenshots/`.

---

## Retry-ability & Timeouts

Cypress **retries queries and assertions** automatically until they pass or the timeout elapses — this is why explicit
waits are rarely needed.

- `defaultCommandTimeout` (default 4000ms): how long a command retries to find an element / satisfy an assertion.
- `cy.get(selector, { timeout: 10000 })`: override the timeout per command.
- `cy.wait(ms)`: a **fixed** pause (discouraged — prefer waiting on an aliased request instead).
- `cy.wait("@alias")`: wait for a specific network request (deterministic, preferred).

```ts
cy.get("[data-cy=spinner]", { timeout: 10000 }).should("not.exist");

cy.intercept("GET", "/api/slow").as("slow");
cy.visit("/report");
cy.wait("@slow");                 // ✅ deterministic
// cy.wait(3000);                 // ❌ arbitrary, flaky
```

> **Only queries retry.** Commands with side effects (`.click()`, `.type()`) run once. If you chain an assertion after
> a query, the whole chain re-runs until the assertion passes.

---

## Environment & Configuration

- `Cypress.env(key)`: reads an environment variable (from config `env`, `cypress.env.json`, CLI `--env`, or `CYPRESS_*`).
- `Cypress.config(key)`: reads a configuration value at runtime.
- `cypress.env.json`: a git-ignored file for local/secret env values.

```ts
const apiUrl = Cypress.env("apiUrl");
cy.request(`${apiUrl}/health`).its("status").should("eq", 200);

const timeout = Cypress.config("defaultCommandTimeout");
```

```jsonc
// cypress.env.json (git-ignored)
{
  "apiUrl": "http://localhost:3000",
  "adminToken": "secret-token"
}
```

---

## Best Practices

- **Use `data-cy` attributes** for selectors — decouple tests from styling and content changes.
- **Don't use arbitrary `cy.wait(ms)`** — wait on aliased requests (`cy.wait("@alias")`) or let assertions retry.
- **Keep tests independent** — each `it` should set up its own state; don't rely on execution order.
- **Seed state via `cy.request()`**, not the UI — log in and create data through the API for speed and reliability.
- **Cache login with `cy.session()`** instead of logging in through the UI every test.
- **Assert on visible outcomes**, not implementation details.
- **One logical flow per test**, but don't over-split — Cypress tests are heavier than unit tests.
- **Avoid chaining off non-query commands** — `.click()` doesn't yield a useful subject.

```ts
// ❌ brittle, slow, order-dependent
cy.get(".btn.primary").click();
cy.wait(2000);

// ✅ resilient, deterministic
cy.intercept("POST", "/api/users").as("create");
cy.get("[data-cy=submit]").click();
cy.wait("@create").its("response.statusCode").should("eq", 201);
```

---

## Command Reference Summary

| Command | Purpose |
|---------|---------|
| `cy.visit(url)` | Navigate to a page |
| `cy.get(selector)` | Query the DOM (retries) |
| `cy.contains(text)` | Find element by text |
| `cy.find(selector)` | Search within a subject |
| `.click()` / `.type()` / `.clear()` | Interact with elements |
| `.check()` / `.select()` | Form controls |
| `.should()` / `.and()` | Implicit (retrying) assertions |
| `.then(fn)` | Act on the yielded subject |
| `cy.intercept()` | Spy on / stub network requests |
| `cy.request()` | Make a real HTTP request |
| `cy.wait("@alias")` | Wait for a request to finish |
| `cy.fixture()` | Load static test data |
| `.as(name)` | Create an alias |
| `cy.session()` | Cache login state |
| `Cypress.Commands.add()` | Define a custom command |
| `cy.mount()` | Mount a component (component testing) |
| `cy.stub()` / `cy.spy()` | Stub / spy on functions |
| `cy.clock()` / `cy.tick()` | Control time |
| `cy.wrap()` | Wrap a value for chaining |
| `cy.pause()` / `cy.debug()` | Debugging helpers |
| `Cypress.env()` / `Cypress.config()` | Read env / config |

---
