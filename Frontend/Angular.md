# Angular 

**Angular** is an opinionated, component-based TypeScript framework for building single-page applications (SPAs) and
large-scale GUIs. It ships with a full toolchain: a CLI, a router, a dependency-injection system, an HTTP client,
forms, and a reactive state model built on **signals** and **RxJS**.

**Opinions** (things Angular decides for you):

- **TypeScript-first**: components, services, and templates are strongly typed; JavaScript is not the primary path.

- **Component + template + style triad**: every UI unit is a class decorated with `@Component`, paired with an HTML
  template and scoped styles.

- **Dependency injection everywhere**: shared logic lives in `@Injectable` services provided through a hierarchical
  DI container rather than imported directly.

- **Convention over configuration**: the CLI scaffolds a fixed folder layout, naming scheme, and build pipeline.

- **Standalone by default** (v17+): components declare their own `imports`; `NgModule` is now optional/legacy.

- **Reactivity via signals** (v16+): and RxJS observables for async streams.

--- 

## Installation & Set-Up

Install the **CLI** globally, which provides different functionalities for generating code and other features.

```bash 
npm install -g @angular/cli

ng version          # verify installation and list versions
```

### Set-Up Project

```bash 
ng new my-app                 # interactive wizard (routing? CSS/SCSS?)
ng new my-app --routing --style=scss --ssr=false
ng new my-app --dry-run       # simulate creation without writing files
```

The wizard asks for preferences (routing, stylesheet format, SSR). `--dry-run` previews the generated files without
touching the disk.

```bash
cd my-app
ng serve            # start dev server at http://localhost:4200
```

--- 

## CLI Tool Commands 

- `ng serve`: builds and runs the app in development mode with live reload.
  - `--open` / `-o`: open the browser automatically.
  - `--port <n>`: use a custom port.
  - `--configuration production`: serve a production build.

- `ng generate <schematic> <name>` (alias `ng g`): scaffolds code from a blueprint.
  - `ng g component header` (`c`): a component.
  - `ng g service data` (`s`): a service.
  - `ng g directive highlight` (`d`): a directive.
  - `ng g pipe currency` (`p`): a pipe.
  - `ng g guard auth` (`g`): a route guard.
  - `ng g interface user` / `ng g class models/user`.

- `ng build`: compiles the app into `dist/` for deployment.
  - `--configuration production` (default in modern CLI): enables AOT, minification, and tree-shaking.

- `ng test`: runs unit tests with Karma/Jasmine (or Vitest/Jest in newer setups).

- `ng e2e`: runs end-to-end tests.

- `ng lint`: runs the linter.

- `ng add <package>`: installs and configures a library (e.g. `ng add @angular/material`).

- `ng update`: upgrades Angular and dependencies across major versions.

```bash
ng serve -o --port 4300
ng g component components/user-card --inline-style --skip-tests
ng build --configuration production
```

--- 

## Project Structure

A typical standalone Angular project scaffolded by the CLI:

```txt 
my-app/
├── src/
│   ├── main.ts                 ← bootstraps the root component
│   ├── index.html              ← the single HTML page shell (<app-root>)
│   ├── styles.scss             ← global styles
│   └── app/
│       ├── app.component.ts    ← root component (logic)
│       ├── app.component.html  ← root component (template)
│       ├── app.component.scss  ← root component (styles)
│       ├── app.config.ts       ← application-level providers (router, http…)
│       ├── app.routes.ts       ← route definitions
│       ├── components/         ← reusable UI components
│       ├── services/           ← injectable business logic
│       ├── models/             ← interfaces / types
│       └── guards/             ← route guards
├── public/                     ← static assets served as-is
├── angular.json                ← workspace & build configuration
├── tsconfig.json               ← TypeScript config
└── package.json
```

> The `.component.x` is not necessary anymore and also, the core structure has changed a little, but the most of if is still the same.

**`main.ts` bootstrap (standalone):**

```ts
import { bootstrapApplication } from "@angular/platform-browser";
import { AppComponent } from "./app/app.component";
import { appConfig } from "./app/app.config";

bootstrapApplication(AppComponent, appConfig)
  .catch((err) => console.error(err));
```

**`app.config.ts` — application-wide providers:**

```ts
import { ApplicationConfig } from "@angular/core";
import { provideRouter } from "@angular/router";
import { provideHttpClient } from "@angular/common/http";
import { routes } from "./app.routes";

export const appConfig: ApplicationConfig = {
  providers: [
    provideRouter(routes),
    provideHttpClient(),
  ],
};
```

--- 

## Angular Components

**Angular components** are UI elements consisting of **logic** in a `.ts` file, **styles** in a `.css`/`.scss` file,
and a **template** in an `.html` file. You can also use **inline** `template` and `styles` to keep everything in one
file.

Declare a component with the `@Component` decorator, whose main fields are:

- `selector`: the custom element name used to place the component in another template, e.g. `<app-header />`, `'app-header'`.

- `standalone`: when `true`, the component manages its own `imports` (no `NgModule`). Default `true` in v19+.

- `imports`: other standalone components, directives, and pipes this template uses (e.g. `RouterOutlet`, `NgIf`).

- `template`: inline HTML markup.

- `templateUrl`: path to an external HTML file (use instead of `template`).

- `styles`: inline styles (array of strings).

- `styleUrl` / `styleUrls`: path(s) to external stylesheet(s).

- `changeDetection`: strategy — `ChangeDetectionStrategy.OnPush` for performance.

- `providers`: services scoped to this component and its children.

```ts 
import { Component } from "@angular/core";
import { RouterOutlet } from "@angular/router";

@Component({
  selector:    "app-root",
  standalone:  true,
  imports:     [RouterOutlet],
  templateUrl: "./app.component.html",
  styleUrl:    "./app.component.scss",
})
export class AppComponent {
  title = "my-app";   // fields and methods define the component's logic
  description = signal("Goofy AHH");
}
```

The class underneath the decorator holds the component's state (fields) and behavior (methods), which the template
binds to.

### Generating Components

```bash 
ng generate component header        # creates a folder with 4 files
ng g c header                       # shorthand
```

#### Flags 

- `--inline-template` / `-t`: put the HTML inside the `.ts` file.
- `--inline-style` / `-s`: put the CSS inside the `.ts` file.
- `--skip-tests`: do not generate the `.spec.ts` test file.
- `--standalone`: generate a standalone component (default in modern CLI).
- `--change-detection OnPush`: set the change-detection strategy.
- `--prefix <p>`: override the selector prefix (default `app`).

```bash
ng g c components/user-card -t -s --skip-tests --change-detection OnPush
```

### Life-cycle Hooks

Angular calls **lifecycle hooks** at key moments. Implement the matching interface and method:

| Hook | Interface | When it runs |
|------|-----------|-------------|
| `ngOnChanges` | `OnChanges` | On any `@Input`/input signal change (before `ngOnInit`) |
| `ngOnInit` | `OnInit` | Once, after the first `ngOnChanges`; do initialization here |
| `ngDoCheck` | `DoCheck` | On every change-detection run |
| `ngAfterViewInit` | `AfterViewInit` | Once, after the component's view initializes |
| `ngAfterContentInit` | `AfterContentInit` | Once, after projected content initializes |
| `ngOnDestroy` | `OnDestroy` | Just before the component is destroyed |

```ts
import { Component, OnInit, OnDestroy } from "@angular/core";

@Component({ selector: "app-timer", standalone: true, template: `{{ seconds }}s` })
export class TimerComponent implements OnInit, OnDestroy {
  seconds = 0;
  private id?: ReturnType<typeof setInterval>;

  ngOnInit(): void {
    this.id = setInterval(() => this.seconds++, 1000);
  }

  ngOnDestroy(): void {
    clearInterval(this.id);   // always clean up to avoid leaks
  }
}
```

--- 

## Data-Binding

Data binding connects component logic to the template. Angular has four kinds:

```html
<h1>{{ title }}</h1>                          <!-- interpolation -->
<img [src]="imageUrl" [alt]="description" />  <!-- property binding -->
<button (click)="save()">Save</button>        <!-- event binding -->
<input [(ngModel)]="name" />                  <!-- two-way (needs FormsModule) -->
```

### Interpolation 

**Interpolation** uses the `{{}}` syntax to pass variables directly as html-text or attribute-value. (Component to view).

### Property Binding 

**Property binding** is used by writing our attributes like `[attribute] = "JS-Expression"`. The attribute inside the `[]` 
is an attribute of our html-element and the right side is an expression, which can be a method call, etc. (Component to view).

### Event Binding 

**Event binding** allows us to bind a method, expression, etc. when an specific event takes place after an **event**. We use `(event)=function()`.
(Component to view).

### ngModel

The **ngModel** is used for two-way communication which means that the changes made in the view are reflected inside our variables in the component class.
`<input [(ngModel)="name] />`.


### Signals 

**Signals** (v16+) are reactive wrappers around a value. When a signal changes, Angular updates only the parts of the
view that read it. 

For example a side-bar-item which displays text of the last user reviews. 

- `signal(initialValue)`: creates a writable signal. Read it by **calling** it: `count()`.

- `signal.set(value)`: replaces the value.

- `signal.update(fn)`: derives the new value from the old one — `count.update(c => c + 1)`.

- `computed(fn)`: creates a **read-only** derived signal that recomputes when its dependencies change.

- `effect(fn)`: runs a side effect whenever any signal it reads changes (logging, syncing to storage).

```ts
import { Component, signal, computed, effect } from "@angular/core";

@Component({
  selector: "app-counter",
  standalone: true,
  template: `
    <p>Count: {{ count() }}</p>
    <p>Doubled: {{ doubled() }}</p>
    <button (click)="increment()">+</button>
  `,
})
export class CounterComponent {
  count   = signal(0);                       // writable signal
  doubled = computed(() => this.count() * 2); // derived, auto-updates

  constructor() {
    effect(() => console.log("count is", this.count())); // runs on every change
  }

  increment() {
    this.count.update((c) => c + 1);
  }
}
```

### Variables

Plain class fields are also usable in templates, but they rely on Angular's default (zone-based) change detection
rather than signal-based reactivity.

```ts
@Component({ /* ... */ })
export class ProfileComponent {
  name = "Alice";                 // plain property
  readonly createdAt = new Date();
  items: string[] = ["a", "b"];
}
```

**Template reference variables** (`#var`) capture a DOM element or component instance within the template:

```html
<input #searchBox (keyup)="onKey(searchBox.value)" />
<button (click)="searchBox.focus()">Focus</button>
```

--- 

## Passing Data

### Inputs (Parent -> Child)

**Signal inputs** (v17.1+) are the modern way to receive data from a parent.

- `input(default?)`: declares an optional input signal, read by calling it.
- `input.required<T>()`: declares a required input — Angular errors if the parent omits it.
- `input(default, { alias, transform })`: options for aliasing and value transformation.

```ts
import { Component, input } from "@angular/core";

@Component({
  selector: "app-user-card",
  standalone: true,
  template: `<h3>{{ name() }}</h3><p>Age: {{ age() }}</p>`,
})
export class UserCardComponent {
  name = input.required<string>();   // <app-user-card [name]="..."> required
  age  = input(0);                   // optional, default 0
}
```

The legacy decorator form still works:

```ts
import { Input } from "@angular/core";
@Input() name = "";
@Input({ required: true }) id!: number;
```

Usage from the parent template:

```html
<app-user-card [name]="user.name" [age]="user.age" />
```

### Outputs (Child -> Parent)

- `output()`: creates an event emitter the child calls with `.emit(value)`.
- The parent listens with event binding `(eventName)="handler($event)"`.

```ts
import { Component, output } from "@angular/core";

@Component({
  selector: "app-search",
  standalone: true,
  template: `<input (input)="onInput($event)" />`,
})
export class SearchComponent {
  search = output<string>();

  onInput(e: Event) {
    this.search.emit((e.target as HTMLInputElement).value);
  }
}
```

```html
<app-search (search)="handleSearch($event)" />
```

The legacy form uses `@Output()` with an `EventEmitter`:

```ts
import { Output, EventEmitter } from "@angular/core";
@Output() search = new EventEmitter<string>();
```

### Two-way Binding with `model()`

- `model(default?)`: creates a **two-way bindable** signal, enabling custom `[(value)]` syntax on components.

```ts
import { Component, model } from "@angular/core";

@Component({ selector: "app-toggle", standalone: true, template: `...` })
export class ToggleComponent {
  checked = model(false);   // parent: <app-toggle [(checked)]="isOn" />
}
```

--- 

## Event Listeners

Bind DOM events with `(event)="handler($event)"`. The `$event` object is the native DOM event.

```html
<button (click)="onClick()">Click</button>
<input (input)="onInput($event)" (blur)="onBlur()" />
<div (mouseenter)="hover = true" (mouseleave)="hover = false"></div>

<!-- Key event with a filter modifier -->
<input (keyup.enter)="submit()" (keyup.escape)="cancel()" />
```

```ts
export class FormComponent {
  onClick()            { console.log("clicked"); }
  onInput(e: Event)    { console.log((e.target as HTMLInputElement).value); }
  submit()             { /* ... */ }
}
```

**`HostListener`** binds events at the host-element level, useful in directives:

```ts
import { Directive, HostListener } from "@angular/core";

@Directive({ selector: "[appClickLog]", standalone: true })
export class ClickLogDirective {
  @HostListener("click", ["$event"])
  onClick(event: MouseEvent) {
    console.log("host clicked", event);
  }
}
```

--- 

## Control Flow & Directives 

**Directives** add behavior to elements. Angular v17 introduced **built-in control flow** blocks (`@if`, `@for`,
`@switch`) that replace the older structural directives (`*ngIf`, `*ngFor`, `*ngSwitch`).

### @if (formerly *ngIf)

Conditionally renders a block. Supports `@else if` and `@else`.

```html
@if (user()) {
  <p>Welcome, {{ user().name }}</p>
} @else if (loading()) {
  <p>Loading…</p>
} @else {
  <p>Please log in.</p>
}
```

Legacy structural directive:

```html
<p *ngIf="user; else login">Welcome</p>
<ng-template #login><p>Please log in.</p></ng-template>
```

### @for (formerly *ngFor)

Iterates over a collection. The `track` expression is **required** — it identifies items for efficient DOM updates.

```html
@for (item of items(); track item.id) {
  <li>{{ item.name }}</li>
} @empty {
  <li>No items found.</li>
}
```

Available contextual variables: `$index`, `$first`, `$last`, `$even`, `$odd`, `$count`.

Legacy form:

```html
<li *ngFor="let item of items; let i = index; trackBy: trackById">{{ item.name }}</li>
```

### @switch (formerly *ngSwitch)

```html
@switch (status()) {
  @case ("active")   { <span class="green">Active</span> }
  @case ("pending")  { <span class="amber">Pending</span> }
  @default           { <span class="grey">Unknown</span> }
}
```

### Attribute Directives

- `[ngClass]`: adds/removes CSS classes conditionally.
- `[ngStyle]`: sets inline styles dynamically.

```html
<div [ngClass]="{ active: isActive, disabled: !isActive }">…</div>
<div [ngStyle]="{ color: textColor, 'font-size.px': size }">…</div>

<!-- Simple single-class / single-style bindings (no directive needed) -->
<div [class.active]="isActive" [style.color]="textColor">…</div>
```

### Custom Directive

```ts
import { Directive, ElementRef, HostListener, inject } from "@angular/core";

@Directive({ selector: "[appHighlight]", standalone: true })
export class HighlightDirective {
  private el = inject(ElementRef);

  @HostListener("mouseenter") onEnter() { this.setColor("yellow"); }
  @HostListener("mouseleave") onLeave() { this.setColor(""); }

  private setColor(color: string) {
    this.el.nativeElement.style.backgroundColor = color;
  }
}
```

--- 

## Services & Dependency Injection

**Services** are reusable, injectable pieces of logic (data access, business rules, shared state). Mark a class with
`@Injectable` and inject it where needed.

- `@Injectable({ providedIn: "root" })`: registers the service as an app-wide singleton (tree-shakable).

- `inject(Token)`: the modern function-based way to obtain a dependency (works in constructors, field initializers,
  and factory functions).

- Constructor injection: the classic form — list dependencies as constructor parameters.

```ts
import { Injectable } from "@angular/core";

@Injectable({ providedIn: "root" })   // singleton for the whole app
export class CounterService {
  private count = signal(0);
  readonly value = this.count.asReadonly();

  increment() { this.count.update((c) => c + 1); }
  reset()     { this.count.set(0); }
}
```

Injecting the service into a component:

```ts
import { Component, inject } from "@angular/core";
import { CounterService } from "./counter.service";

@Component({ /* ... */ })
export class WidgetComponent {
  // Modern: inject() function
  private counter = inject(CounterService);

  // Classic: constructor injection (equivalent)
  // constructor(private counter: CounterService) {}

  add() { this.counter.increment(); }
}
```

**Provider scopes:**

| `providedIn` / provider location | Scope |
|----------------------------------|-------|
| `providedIn: "root"` | One singleton for the whole app |
| `providers` in `app.config.ts` | App-wide (explicit) |
| `providers` in a `@Component` | New instance per component subtree |

--- 

## HTTP Requests 

Angular's `HttpClient` performs HTTP calls and returns **observables**. Enable it once with `provideHttpClient()` in
`app.config.ts`.

- `http.get<T>(url, options?)`: GET request typed as `T`.
- `http.post<T>(url, body, options?)`: POST with a request body.
- `http.put<T>(url, body)` / `http.patch<T>(url, body)`: full / partial update.
- `http.delete<T>(url)`: DELETE request.
- `options`: `{ params, headers, responseType, observe }`.

```ts
import { Injectable, inject } from "@angular/core";
import { HttpClient, HttpParams } from "@angular/common/http";
import { Observable } from "rxjs";

interface User { id: number; name: string; }

@Injectable({ providedIn: "root" })
export class UserService {
  private http = inject(HttpClient);
  private base = "/api/users";

  getUsers(page = 1): Observable<User[]> {
    const params = new HttpParams().set("page", page);
    return this.http.get<User[]>(this.base, { params });
  }

  getUser(id: number): Observable<User> {
    return this.http.get<User>(`${this.base}/${id}`);
  }

  createUser(data: Partial<User>): Observable<User> {
    return this.http.post<User>(this.base, data);
  }

  deleteUser(id: number): Observable<void> {
    return this.http.delete<void>(`${this.base}/${id}`);
  }
}
```

Consuming it in a component — subscribe manually, or convert to a signal:

```ts
import { Component, inject, signal } from "@angular/core";
import { toSignal } from "@angular/core/rxjs-interop";

@Component({ /* ... */ })
export class UserListComponent {
  private service = inject(UserService);

  // Option A — signal from an observable (auto-unsubscribes)
  users = toSignal(this.service.getUsers(), { initialValue: [] });

  // Option B — manual subscription
  loadOne(id: number) {
    this.service.getUser(id).subscribe({
      next:  (user) => console.log(user),
      error: (err)  => console.error(err),
    });
  }
}
```

### Interceptors

Interceptors sit in the request/response pipeline; ideal for attaching auth tokens or global error handling.

```ts
import { HttpInterceptorFn } from "@angular/common/http";

export const authInterceptor: HttpInterceptorFn = (req, next) => {
  const token = localStorage.getItem("token");
  const authReq = token
    ? req.clone({ setHeaders: { Authorization: `Bearer ${token}` } })
    : req;
  return next(authReq);
};

// register in app.config.ts
// provideHttpClient(withInterceptors([authInterceptor]))
```

--- 

## Routers 

The **Router** maps URL paths to components, enabling client-side navigation without full page reloads.

- `provideRouter(routes)`: registers the route configuration (in `app.config.ts`).

- `<router-outlet />`: placeholder where the matched component renders.

- `routerLink`: directive for declarative navigation links.

- `Router.navigate(commands)`: programmatic navigation.

- `ActivatedRoute`: access to route params, query params, and data.

```ts
// app.routes.ts
import { Routes } from "@angular/router";

export const routes: Routes = [
  { path: "",            component: HomeComponent },
  { path: "users",       component: UserListComponent },
  { path: "users/:id",   component: UserDetailComponent },      // route parameter
  {
    path: "admin",
    loadComponent: () => import("./admin/admin.component")       // lazy loading
      .then((m) => m.AdminComponent),
    canActivate: [authGuard],                                    // route guard
  },
  { path: "**", component: NotFoundComponent },                  // wildcard (404)
];
```

```html
<!-- Navigation links -->
<nav>
  <a routerLink="/">Home</a>
  <a routerLink="/users" routerLinkActive="active">Users</a>
  <a [routerLink]="['/users', user.id]">Details</a>
</nav>

<router-outlet />   <!-- matched component renders here -->
```

Reading parameters and navigating in code:

```ts
import { Component, inject, input } from "@angular/core";
import { ActivatedRoute, Router } from "@angular/router";

@Component({ /* ... */ })
export class UserDetailComponent {
  private route  = inject(ActivatedRoute);
  private router = inject(Router);

  // With withComponentInputBinding(), route params bind directly to inputs:
  id = input.required<string>();

  // Or read them manually:
  ngOnInit() {
    const id = this.route.snapshot.paramMap.get("id");
    this.route.queryParamMap.subscribe((q) => console.log(q.get("tab")));
  }

  goBack() {
    this.router.navigate(["/users"]);
  }
}
```

### Route Guards

Guards control whether navigation to a route is allowed. Modern guards are plain functions.

```ts
import { CanActivateFn, Router } from "@angular/router";
import { inject } from "@angular/core";

export const authGuard: CanActivateFn = (route, state) => {
  const router = inject(Router);
  const loggedIn = !!localStorage.getItem("token");
  return loggedIn ? true : router.createUrlTree(["/login"]);
};
```

--- 

## Pipes 

**Pipes** transform a displayed value directly in the template with the `|` syntax. Angular ships several built-in
pipes, and you can create your own.

**Built-in pipes:**

```html
{{ name | uppercase }}                         <!-- ALICE -->
{{ name | lowercase }}                          <!-- alice -->
{{ price | currency:'EUR' }}                     <!-- €42.00 -->
{{ today | date:'dd/MM/yyyy' }}                  <!-- 07/09/2026 -->
{{ ratio | percent:'1.0-2' }}                    <!-- 25% -->
{{ value | number:'1.2-2' }}                     <!-- 3.14 -->
{{ obj | json }}                                 <!-- debug output -->
{{ text | slice:0:20 }}                          <!-- first 20 chars -->
{{ data$ | async }}                              <!-- unwraps an Observable/Promise -->
```

`async` is especially important: it **subscribes** to an observable and **auto-unsubscribes** when the component is
destroyed, avoiding manual subscription management.

### Custom Pipe

- `@Pipe({ name, standalone })`: registers the pipe; use its `name` in templates.
- Implement `PipeTransform` with a `transform(value, ...args)` method.

```ts
import { Pipe, PipeTransform } from "@angular/core";

@Pipe({ name: "truncate", standalone: true })
export class TruncatePipe implements PipeTransform {
  transform(value: string, limit = 20, trail = "…"): string {
    return value.length > limit ? value.slice(0, limit) + trail : value;
  }
}
```

```html
<p>{{ description | truncate:50 }}</p>
```

--- 

## Forms

Angular provides two form strategies:

- **Template-driven forms**: simple, driven by directives in the template (`ngModel`). Good for small forms.

- **Reactive forms**: explicit, type-safe form models defined in the component. Preferred for complex validation.

### Template-driven Forms

Requires importing `FormsModule`.

```ts
import { FormsModule } from "@angular/forms";

@Component({
  selector: "app-login",
  standalone: true,
  imports: [FormsModule],
  template: `
    <form #f="ngForm" (ngSubmit)="submit(f)">
      <input name="email" [(ngModel)]="email" required email />
      <input name="pass"  [(ngModel)]="password" required minlength="8" />
      <button [disabled]="f.invalid">Log in</button>
    </form>
  `,
})
export class LoginComponent {
  email = "";
  password = "";
  submit(form: any) { console.log(form.value); }
}
```

### Reactive Forms

Requires importing `ReactiveFormsModule`.

- `FormControl`: a single field with a value and validators.

- `FormGroup`: a collection of controls forming an object.

- `FormArray`: a dynamic list of controls.

- `FormBuilder` (`fb`): a shorthand factory for building the above.

- `Validators`: built-in validators (`required`, `email`, `minLength`, `pattern`, …).

```ts
import { Component, inject } from "@angular/core";
import { FormBuilder, ReactiveFormsModule, Validators } from "@angular/forms";

@Component({
  selector: "app-signup",
  standalone: true,
  imports: [ReactiveFormsModule],
  template: `
    <form [formGroup]="form" (ngSubmit)="submit()">
      <input formControlName="name" placeholder="Name" />
      @if (form.controls.name.invalid && form.controls.name.touched) {
        <small>Name is required</small>
      }

      <input formControlName="email" placeholder="Email" />
      <input formControlName="password" type="password" />

      <button [disabled]="form.invalid">Sign up</button>
    </form>
  `,
})
export class SignupComponent {
  private fb = inject(FormBuilder);

  form = this.fb.group({
    name:     ["", Validators.required],
    email:    ["", [Validators.required, Validators.email]],
    password: ["", [Validators.required, Validators.minLength(8)]],
  });

  submit() {
    if (this.form.valid) {
      console.log(this.form.value);   // { name, email, password }
    }
  }
}
```

**Useful form control state flags:** `valid` / `invalid`, `touched` / `untouched`, `dirty` / `pristine`, `pending`,
`errors`.

--- 

## Content Projection

`<ng-content />` lets a component render markup passed in by its parent.

```ts
@Component({
  selector: "app-card",
  standalone: true,
  template: `
    <div class="card">
      <header><ng-content select="[card-title]" /></header>
      <div class="body"><ng-content /></div>   <!-- default slot -->
    </div>
  `,
})
export class CardComponent {}
```

```html
<app-card>
  <h2 card-title>Title</h2>
  <p>Body content projected into the default slot.</p>
</app-card>
```

--- 

## RxJS Interop

Bridge between Angular signals and RxJS observables (from `@angular/core/rxjs-interop`).

- `toSignal(observable$, { initialValue })`: converts an observable into a read-only signal; auto-unsubscribes.

- `toObservable(signal)`: converts a signal into an observable that emits on every change.

```ts
import { toSignal, toObservable } from "@angular/core/rxjs-interop";
import { switchMap } from "rxjs";

@Component({ /* ... */ })
export class SearchComponent {
  query   = signal("");
  results = toSignal(
    toObservable(this.query).pipe(
      switchMap((q) => this.api.search(q))   // reactive search stream
    ),
    { initialValue: [] }
  );
}
```

--- 


