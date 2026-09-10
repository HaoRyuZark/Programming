# RxJS

**RxJS** is a reactive library for JavaScript used by a lot of projects and frameworks like **Angular**.
It implements the **Observer** and **Iterator** patterns together with functional programming to let you treat
asynchronous events (clicks, HTTP responses, timers, WebSocket messages) as **streams** of values you can compose,
transform, and combine with a large collection of operators.

```bash
npm install rxjs
```

Modern RxJS (v6+) imports **creation functions** and **types** from `rxjs` and **pipeable operators** from
`rxjs/operators` (merged into `rxjs` in v7.2+). The old `Rx.Observable.prototype` chaining syntax is deprecated.

```js
import { Observable, of, from, interval, fromEvent } from "rxjs";
import { map, filter, take, mergeMap } from "rxjs/operators";
```

--- 

## Async Model 

Vanilla JavaScript handles asynchrony with several distinct tools, each with its own API:

| Type | Single value | Multiple values |
|------|-------------|-----------------|
| **Pull** (consumer decides) | Function (`return`) | Iterator / Generator |
| **Push** (producer decides) | Promise | **Observable** |

- A **Promise** pushes a *single* value (or error) and is **eager** — it starts running the moment it is created.

- An **Observable** pushes *zero, one, or many* values over time and is **lazy** — nothing happens until you
  `subscribe()`. It can also be **cancelled** (via unsubscribe) and **retried**, which promises cannot.

```js
// Promise — eager, single value, not cancellable
const p = new Promise((resolve) => resolve(42));

// Observable — lazy, multi-value, cancellable
import { Observable } from "rxjs";

const obs = new Observable((subscriber) => {
  subscriber.next(1);
  subscriber.next(2);
  subscriber.next(3);
  subscriber.complete();
});

obs.subscribe((x) => console.log(x)); // 1  2  3 — runs only now
```

--- 

## Streams 

A **stream** is a sequence of values made available over time. In RxJS the stream is modeled by an **Observable**,
which emits three kinds of notifications through its lifecycle:

- **`next`**: emits the next value in the stream (can happen 0..∞ times).
- **`error`**: emits an error and **terminates** the stream (no further emissions).
- **`complete`**: signals the stream finished successfully and **terminates** it (no value).

A stream is guaranteed to send **zero or more `next`** notifications followed by **at most one** `error` **or**
`complete` — never both, and nothing after a terminating notification. This is the **Observable contract**.

```txt
--1--2--3--4--|->      complete
--1--2--X            error
--1--2--3-->          never completes (infinite)
```

--- 

## Marble Diagrams 

**Marble diagrams** are the standard visual notation for streams, used across the RxJS docs and tests.

- `-` : a frame of passing time.
- `1`, `a` : an emitted value (`next`).
- `|` : `complete`.
- `X` : `error`.
- `()` : values emitted synchronously in the same frame, e.g. `(12|)`.
- `^` : the point of subscription (in hot-observable diagrams).

```txt
input:  --1--2--3--|
map(x => x * 10):
output: --10-20-30-|
```

--- 

## Observables

An **observable** is informally: something like an array which gets built over time. This library provides a large
number of operators which makes working with observables easier than with vanilla JavaScript.

- `new Observable(subscribe)`: creates an observable from a subscribe function.
  - `subscribe`: a function receiving a `subscriber` (observer). Call `subscriber.next(value)`, `subscriber.error(err)`,
    and `subscriber.complete()` to push notifications. It may **return** a teardown function that runs on unsubscribe.

- `observable.subscribe(observer)`: starts execution of the observable and returns a `Subscription`.
  - `observer`: either a callback `(value) => {}` for `next`, or an object `{ next, error, complete }`.
  - Returns a **`Subscription`** used to cancel the stream with `.unsubscribe()`.

- `observable.pipe(...operators)`: composes pipeable operators left-to-right and returns a **new** observable.

```js
import { Observable } from "rxjs";

// Custom observable that emits 3 values then completes
const numbers$ = new Observable((subscriber) => {
  subscriber.next(1);
  subscriber.next(2);

  const id = setTimeout(() => {
    subscriber.next(3);
    subscriber.complete();
  }, 1000);

  return () => clearInterval(id); // teardown — runs on unsubscribe / complete
});

const subscription = numbers$.subscribe({
  next:     (x)   => console.log("value:", x),
  error:    (err) => console.error("error:", err),
  complete: ()    => console.log("done"),
});

// Cancel the stream early if needed
subscription.unsubscribe();
```

> **Convention:** variables holding an observable are suffixed with `$` (e.g. `clicks$`, `user$`).

### Observers

An **observer** is a consumer of values delivered by an observable. It is just an object with up to three callbacks:

- `next(value)`: called for each emitted value. May be called many times.

- `error(err)`: called once if the stream fails. Terminates the subscription.

- `complete()`: called once when the stream finishes. Terminates the subscription. Receives no value.

```js
const observer = {
  next:     (value) => console.log("Next:", value),
  error:    (err)   => console.error("Error:", err),
  complete: ()      => console.log("Completed"),
};

source$.subscribe(observer);

// Shorthand — a single function is treated as the `next` callback
source$.subscribe((value) => console.log(value));
```

### Subscriptions

A **`Subscription`** represents the execution of an observable and is primarily used to **cancel** it.

- `subscription.unsubscribe()`: disposes the resource held by the subscription and runs the teardown logic.

- `subscription.add(otherSubscription)`: groups child subscriptions so a single `unsubscribe()` tears down all of them.

- `subscription.remove(otherSubscription)`: removes a previously added child subscription.

```js
import { interval } from "rxjs";

const sub1 = interval(1000).subscribe((x) => console.log("A", x));
const sub2 = interval(500).subscribe((x)  => console.log("B", x));

sub1.add(sub2);   // group them

setTimeout(() => sub1.unsubscribe(), 3000); // tears down BOTH A and B
```

### Creation Functions

Creation functions build observables from existing sources. Import them from `rxjs`.

- `of(...values)`: emits each argument synchronously, then completes.

- `from(input)`: converts an array, iterable, promise, or observable-like into an observable.

- `fromEvent(target, eventName)`: creates an observable from DOM/EventEmitter events.
  - `target`: the event source (e.g. a DOM element).
  - `eventName`: the event to listen for (e.g. `"click"`).

- `interval(period)`: emits incrementing integers (0, 1, 2, …) every `period` milliseconds. Never completes.

- `timer(due, period?)`: emits `0` after `due` ms; if `period` is given, keeps emitting every `period` ms afterwards.

- `range(start, count)`: emits `count` sequential integers starting at `start`, then completes.

- `EMPTY`: emits no value and completes immediately.

- `NEVER`: never emits and never completes.

- `throwError(() => err)`: creates an observable that errors immediately.

- `defer(factory)`: creates the observable lazily, per subscriber, by calling `factory` at subscription time.

- `ajax(urlOrConfig)` (from `rxjs/ajax`): performs an HTTP request and emits the response.

```js
import { of, from, fromEvent, interval, timer, range, EMPTY, throwError, defer } from "rxjs";

of(1, 2, 3).subscribe(console.log);                    // 1 2 3 |

from([10, 20, 30]).subscribe(console.log);             // 10 20 30 |
from(fetch("/api/users")).subscribe(console.log);      // resolves the promise

fromEvent(document, "click").subscribe((e) => console.log(e.clientX, e.clientY));

interval(1000).subscribe(console.log);                 // 0 1 2 3 ... every second
timer(2000, 1000).subscribe(console.log);              // waits 2s, then 0 1 2 ... every 1s

range(1, 5).subscribe(console.log);                    // 1 2 3 4 5 |

// Lazy creation — a fresh random value per subscriber
const random$ = defer(() => of(Math.random()));
```

### Cold vs Hot Observables

- **Cold**: the producer is created **inside** the observable — each subscriber gets its own independent execution
  (e.g. `of`, `from`, `interval`, HTTP requests). Subscribing twice runs the work twice.

- **Hot**: the producer lives **outside** and is **shared** — subscribers share a single execution and only receive
  values emitted *after* they subscribe (e.g. `fromEvent`, `Subject`). Late subscribers miss earlier values.

```js
// Cold — two independent timers, values not shared
const cold$ = interval(1000);
cold$.subscribe((x) => console.log("A", x));
cold$.subscribe((x) => console.log("B", x)); // independent sequence

// Hot — shared execution via a Subject (see below)
```

--- 

## Operators

**Operators** are pure functions that take an observable as input and return a new observable, without modifying the
original. They are used inside `.pipe()` and split into two groups:

- **Pipeable operators**: `source$.pipe(op1(), op2())` — transform an existing stream (`map`, `filter`, `take`…).
- **Creation operators**: standalone functions that create streams (`of`, `interval`, `merge`…).

### Transformation

#### .map

- `map(project)`: applies `project` to each emitted value and emits the result.

```js
import { of } from "rxjs";
import { map } from "rxjs/operators";

of(1, 2, 3).pipe(
  map((x) => x * 10)
).subscribe(console.log);   // 10 20 30
```

#### .pluck

- `pluck(...keys)`: maps each value to the nested property named by `keys`. (Deprecated in v7 — prefer `map`.)

```js
import { pluck, map } from "rxjs/operators";

// pluck (legacy)
source$.pipe(pluck("target", "value"));

// preferred equivalent
source$.pipe(map((e) => e.target.value));
```

#### .scan

- `scan(accumulator, seed?)`: like `Array.reduce` but emits the **running** accumulated value on **each** emission.
  - `accumulator`: `(acc, value, index) => newAcc`.
  - `seed`: optional initial accumulator value.

```js
import { of } from "rxjs";
import { scan } from "rxjs/operators";

of(1, 2, 3, 4).pipe(
  scan((acc, x) => acc + x, 0)
).subscribe(console.log);   // 1 3 6 10  (running total)
```

#### .reduce

- `reduce(accumulator, seed?)`: like `scan`, but emits **only the final** accumulated value on `complete`.

```js
import { reduce } from "rxjs/operators";

of(1, 2, 3, 4).pipe(
  reduce((acc, x) => acc + x, 0)
).subscribe(console.log);   // 10  (only once, on complete)
```

#### .mergeMap

- `mergeMap(project, concurrent?)`: maps each value to an **inner observable** and merges their outputs, running them
  **concurrently** (no ordering guarantee). Alias: `flatMap`.
  - `project`: `(value, index) => Observable`.
  - `concurrent`: max number of inner subscriptions active at once.

Use it for parallel work where order does not matter (e.g. independent HTTP requests).

```js
import { of } from "rxjs";
import { mergeMap } from "rxjs/operators";
import { ajax } from "rxjs/ajax";

of(1, 2, 3).pipe(
  mergeMap((id) => ajax.getJSON(`/api/users/${id}`))
).subscribe(console.log);   // responses arrive in any order
```

#### .switchMap

- `switchMap(project)`: maps to an inner observable, but **cancels** the previous inner subscription whenever the
  source emits again. Only the **latest** inner stream stays active.

Ideal for type-ahead search and route changes — stale requests are discarded.

```js
import { fromEvent } from "rxjs";
import { debounceTime, map, switchMap } from "rxjs/operators";
import { ajax } from "rxjs/ajax";

fromEvent(input, "input").pipe(
  debounceTime(300),
  map((e) => e.target.value),
  switchMap((term) => ajax.getJSON(`/search?q=${term}`)) // cancels prior request
).subscribe(renderResults);
```

#### .concatMap

- `concatMap(project)`: maps to an inner observable and runs them **one after another**, preserving order — waits for
  each inner stream to complete before subscribing to the next.

Use when order matters and operations must not overlap (e.g. sequential writes).

```js
import { concatMap } from "rxjs/operators";

of(1, 2, 3).pipe(
  concatMap((id) => saveToServer(id))   // strictly sequential
).subscribe(console.log);
```

#### .exhaustMap

- `exhaustMap(project)`: maps to an inner observable but **ignores** new source values while the current inner stream
  is still active. Good for preventing double-submits (e.g. login button spam).

```js
import { exhaustMap } from "rxjs/operators";

fromEvent(loginBtn, "click").pipe(
  exhaustMap(() => login(credentials))  // ignores clicks until login finishes
).subscribe();
```

**Higher-order mapping — quick comparison:**

| Operator | Concurrency | On new source value | Typical use |
|----------|-------------|---------------------|-------------|
| `mergeMap` | Parallel | Keep all inner streams | Independent parallel requests |
| `switchMap` | One at a time | Cancel previous inner | Type-ahead search, latest-only |
| `concatMap` | Sequential | Queue after current | Ordered, non-overlapping work |
| `exhaustMap` | One at a time | Ignore until current done | Prevent duplicate submits |

### Filtering

#### .filter

- `filter(predicate)`: emits only values for which `predicate` returns truthy.

```js
import { filter } from "rxjs/operators";

of(1, 2, 3, 4, 5).pipe(
  filter((x) => x % 2 === 0)
).subscribe(console.log);   // 2 4
```

#### .first & .last

- `first(predicate?, default?)`: emits the first value (optionally matching `predicate`), then completes.
  Errors with `EmptyError` if the source completes with no match and no default is given.

- `last(predicate?, default?)`: emits the last value (optionally matching `predicate`) on completion, then completes.

```js
import { first, last } from "rxjs/operators";

of(1, 2, 3).pipe(first()).subscribe(console.log);            // 1
of(1, 2, 3).pipe(first((x) => x > 1)).subscribe(console.log); // 2
of(1, 2, 3).pipe(last()).subscribe(console.log);             // 3
```

#### .take & .takeLast

- `take(count)`: emits the first `count` values, then completes.

- `takeLast(count)`: emits the last `count` values once the source completes.

```js
import { take } from "rxjs/operators";

interval(1000).pipe(take(3)).subscribe(console.log); // 0 1 2 | (then stops)
```

#### .takeUntil

- `takeUntil(notifier$)`: emits values until `notifier$` emits its first value, then completes. The canonical way to
  **auto-unsubscribe** (e.g. tearing down streams on component destroy).

```js
import { interval, Subject } from "rxjs";
import { takeUntil } from "rxjs/operators";

const destroy$ = new Subject();

interval(1000).pipe(
  takeUntil(destroy$)
).subscribe(console.log);

// later — completes the stream above
destroy$.next();
destroy$.complete();
```

#### .takeWhile

- `takeWhile(predicate, inclusive?)`: emits values while `predicate` is truthy, then completes. If `inclusive` is
  `true`, also emits the value that failed the predicate.

```js
import { takeWhile } from "rxjs/operators";

of(1, 2, 3, 4, 1).pipe(
  takeWhile((x) => x < 3)
).subscribe(console.log);   // 1 2 | (completes at 3)
```

#### .skip & .skipUntil

- `skip(count)`: ignores the first `count` values, then emits the rest.

- `skipUntil(notifier$)`: ignores values until `notifier$` emits, then mirrors the source.

```js
import { skip } from "rxjs/operators";

of(1, 2, 3, 4).pipe(skip(2)).subscribe(console.log); // 3 4
```

#### .distinctUntilChanged

- `distinctUntilChanged(comparator?)`: emits a value only if it is different from the **previous** one.
  - `comparator`: optional `(prev, curr) => boolean` equality function.

```js
import { distinctUntilChanged } from "rxjs/operators";

of(1, 1, 2, 2, 3, 1).pipe(
  distinctUntilChanged()
).subscribe(console.log);   // 1 2 3 1
```

### Rate Limiting

#### .throttleTime

- `throttleTime(duration)`: emits the first value, then **ignores** subsequent values for `duration` ms. Good for
  rate-limiting high-frequency events like scroll or mousemove.

```js
import { fromEvent } from "rxjs";
import { throttleTime } from "rxjs/operators";

fromEvent(document, "scroll").pipe(
  throttleTime(1000)   // at most one event per second
).subscribe(() => console.log("scrolled"));
```

#### .debounceTime

- `debounceTime(duration)`: emits a value only after `duration` ms have passed **without** another emission. Ideal
  for waiting until the user stops typing.

```js
import { debounceTime, map } from "rxjs/operators";

fromEvent(input, "input").pipe(
  debounceTime(300),
  map((e) => e.target.value)
).subscribe(console.log);   // fires 300ms after typing stops
```

> **Throttle vs debounce:** throttle emits at the *start* of a burst and caps the rate; debounce waits for a *quiet
> period* and emits at the end.

#### .auditTime & .sampleTime

- `auditTime(duration)`: emits the **most recent** value after `duration` ms following an emission.

- `sampleTime(period)`: emits the most recent value on a fixed `period` interval.

### Utility

#### .tap (do)

- `tap(observerOrNext)`: performs a **side effect** for each notification (logging, debugging, cache writes) without
  altering the stream. Formerly named `do`.

```js
import { tap } from "rxjs/operators";

of(1, 2, 3).pipe(
  tap((x) => console.log("before map:", x)),
  map((x) => x * 2),
  tap({ complete: () => console.log("done") })
).subscribe(console.log);
```

#### .delay

- `delay(dueTime)`: time-shifts each emission by `dueTime` milliseconds (or until an absolute `Date`).

#### .startWith

- `startWith(...values)`: emits the given values **before** the source begins. Useful for seeding an initial UI state.

```js
import { startWith } from "rxjs/operators";

source$.pipe(startWith("loading...")).subscribe(console.log);
```

#### .toArray

- `toArray()`: collects all emissions into a single array, emitted on `complete`.

#### .finalize (finally)

- `finalize(callback)`: runs `callback` when the observable **completes, errors, or is unsubscribed**. Ideal for
  cleanup like hiding a spinner. Formerly named `finally`.

```js
import { finalize } from "rxjs/operators";

showSpinner();
data$.pipe(
  finalize(() => hideSpinner())   // runs on success, error, OR unsubscribe
).subscribe(render);
```

### Combination

#### .zip

- `zip(...observables)`: combines emissions by **index** — emits an array once **every** source has emitted a value
  at that position. Waits for the slowest.

```js
import { zip, of } from "rxjs";

zip(
  of("a", "b", "c"),
  of(1, 2, 3)
).subscribe(console.log);   // ['a',1]  ['b',2]  ['c',3]
```

#### .combineLatest

- `combineLatest([...observables])`: emits an array of the **latest** value from each source whenever **any** of them
  emits (after all have emitted at least once).

```js
import { combineLatest } from "rxjs";

combineLatest([width$, height$]).subscribe(
  ([w, h]) => console.log("area:", w * h)
);
```

#### .forkJoin

- `forkJoin(sources)`: waits for **every** source observable to **complete**, then emits a single array/object of
  their **last** values. The RxJS equivalent of `Promise.all` — great for firing parallel requests once.
  - `sources`: an array or dictionary of observables.

```js
import { forkJoin } from "rxjs";
import { ajax } from "rxjs/ajax";

forkJoin({
  user:  ajax.getJSON("/api/user/1"),
  posts: ajax.getJSON("/api/user/1/posts"),
}).subscribe(({ user, posts }) => {
  console.log(user, posts);   // fires once, when both complete
});
```

#### .merge

- `merge(...observables)`: subscribes to all sources at once and emits their values as they arrive, interleaved.

```js
import { merge, interval } from "rxjs";
import { map } from "rxjs/operators";

merge(
  interval(1000).pipe(map((x) => `A${x}`)),
  interval(1500).pipe(map((x) => `B${x}`))
).subscribe(console.log);   // A0 B0 A1 A2 B1 ...
```

#### .concat

- `concat(...observables)`: subscribes to each source **in order**, moving to the next only after the current one
  completes. Preserves ordering.

#### .withLatestFrom

- `withLatestFrom(...others)`: for each source emission, combines it with the **latest** value from the `others`.
  Unlike `combineLatest`, only the **source** triggers an emission.

```js
import { withLatestFrom, map } from "rxjs/operators";

clicks$.pipe(
  withLatestFrom(currentUser$),
  map(([click, user]) => `${user.name} clicked`)
).subscribe(console.log);
```

### Error Handling

#### .catchError (catch)

- `catchError(selector)`: catches an error on the source and switches to a **new** observable returned by `selector`.
  - `selector`: `(error, caught$) => Observable`. Return a fallback stream, or re-throw with `throwError`.

```js
import { of, throwError } from "rxjs";
import { catchError } from "rxjs/operators";

data$.pipe(
  catchError((err) => {
    console.error(err);
    return of([]);            // graceful fallback value
  })
).subscribe(render);

// Re-throw / transform the error instead
data$.pipe(
  catchError((err) => throwError(() => new Error("Request failed")))
);
```

#### .retry

- `retry(count)`: re-subscribes to the source up to `count` times if it errors. Useful for transient network failures.

```js
import { retry } from "rxjs/operators";

ajax.getJSON("/api/data").pipe(
  retry(3)   // try up to 3 more times before giving up
).subscribe(render);
```

#### .retryWhen

- `retryWhen(notifier)`: re-subscribes when the `notifier` observable (built from the stream of errors) emits.
  Enables custom strategies like exponential backoff. (Deprecated in v7.8 in favour of `retry({ delay })`.)

```js
import { retry, timer } from "rxjs";

source$.pipe(
  retry({
    count: 3,
    delay: (err, retryCount) => timer(retryCount * 1000), // backoff: 1s, 2s, 3s
  })
);
```

#### .throwError

- `throwError(errorFactory)`: creation function that emits **no** value and immediately errors with the produced error.

```js
import { throwError } from "rxjs";

throwError(() => new Error("boom")).subscribe({
  error: (err) => console.error(err.message),
});
```

--- 

## Pipes

The **`.pipe()`** method chains pipeable operators, passing each operator's output observable as the input to the
next — the reactive equivalent of function composition. It reads top-to-bottom and keeps the original observable
unchanged.

- `observable.pipe(op1, op2, ..., opN)`: returns a new observable with all operators applied in order.

```js
import { fromEvent } from "rxjs";
import { map, filter, debounceTime, distinctUntilChanged, switchMap } from "rxjs/operators";

const results$ = fromEvent(searchInput, "input").pipe(
  map((e) => e.target.value),        // extract the text
  filter((text) => text.length > 2), // ignore short queries
  debounceTime(300),                 // wait for typing to pause
  distinctUntilChanged(),            // skip repeats
  switchMap((term) => search(term))  // cancel stale requests
);

results$.subscribe(render);
```

> In **Angular**, the `async` pipe (`{{ data$ | async }}`) is a template feature that subscribes to an observable
> and auto-unsubscribes — distinct from RxJS's `.pipe()` operator composition method.

--- 

## Subject

A **`Subject`** is both an **Observable** and an **Observer**: you can `subscribe` to it *and* push values into it
with `next()`. It **multicasts** — a single execution is shared among all subscribers, making it the primary tool for
turning cold observables hot and for cross-component event buses.

- `new Subject()`: creates a multicasting subject.

- `subject.next(value)`: pushes a value to **all** current subscribers.

- `subject.error(err)`: sends an error to all subscribers and terminates.

- `subject.complete()`: completes the subject for all subscribers.

- `subject.subscribe(observer)`: registers an observer. Only receives values emitted **after** subscribing.

- `subject.asObservable()`: returns an observable view that **hides** the `next`/`error`/`complete` methods —
  exposes read-only access so external code cannot push values.

```js
import { Subject } from "rxjs";

const subject = new Subject();

subject.subscribe((x) => console.log("Observer A:", x));
subject.next(1);   // A: 1

subject.subscribe((x) => console.log("Observer B:", x));
subject.next(2);   // A: 2   B: 2   (B missed the first value)

// Expose a read-only stream
const events$ = subject.asObservable();
```

--- 

## BehaviorSubject

A **`BehaviorSubject`** is a `Subject` that remembers the **current (latest) value** and immediately emits it to every
new subscriber. It requires an **initial value** and is the standard building block for reactive state stores.

- `new BehaviorSubject(initialValue)`: creates the subject seeded with `initialValue`.

- `subject.getValue()` / `subject.value`: synchronously returns the current value without subscribing.

- Inherits `next`, `error`, `complete`, `subscribe`, and `asObservable` from `Subject`.

```js
import { BehaviorSubject } from "rxjs";

const count$ = new BehaviorSubject(0);   // seeded with 0

count$.subscribe((x) => console.log("A:", x)); // A: 0  (gets current value at once)

count$.next(1);   // A: 1
count$.next(2);   // A: 2

count$.subscribe((x) => console.log("B:", x)); // B: 2  (latest value on subscribe)

console.log(count$.getValue()); // 2  (synchronous read)
```

### Simple State Store Pattern

```js
import { BehaviorSubject } from "rxjs";

class Store {
  #state$ = new BehaviorSubject({ user: null, cart: [] });

  state$ = this.#state$.asObservable();       // read-only stream

  get snapshot() { return this.#state$.getValue(); }

  update(partial) {
    this.#state$.next({ ...this.#state$.getValue(), ...partial });
  }
}

const store = new Store();
store.state$.subscribe((s) => render(s));
store.update({ user: { name: "Alice" } });    // notifies all subscribers
```

--- 

## ReplaySubject & AsyncSubject

- `new ReplaySubject(bufferSize?, windowTime?)`: replays the last `bufferSize` values (optionally only those within
  `windowTime` ms) to **every** new subscriber — even those emitted before they subscribed.

- `new AsyncSubject()`: emits **only the last** value, and **only when** the subject completes.

```js
import { ReplaySubject, AsyncSubject } from "rxjs";

// ReplaySubject — new subscribers receive the buffered history
const replay$ = new ReplaySubject(2);   // remember last 2 values
replay$.next(1);
replay$.next(2);
replay$.next(3);
replay$.subscribe(console.log);         // 2 3  (last two replayed)

// AsyncSubject — only the final value, on complete
const async$ = new AsyncSubject();
async$.subscribe(console.log);
async$.next(1);
async$.next(2);
async$.complete();                      // 2  (emits only now)
```

**Subject variants — quick comparison:**

| Type | Initial value | New subscriber receives | Emits on |
|------|--------------|-------------------------|----------|
| `Subject` | none | future values only | each `next` |
| `BehaviorSubject` | **required** | current value + future | each `next` |
| `ReplaySubject` | none | buffered history + future | each `next` |
| `AsyncSubject` | none | last value only | `complete` |

--- 

## Multicasting

By default observables are **unicast** — each subscription triggers a separate execution. **Multicasting** shares one
execution among many subscribers, typically backed by a `Subject`.

- `share(config?)`: multicasts the source and keeps it alive while there is at least one subscriber; re-subscribing
  after all leave can restart it. The modern, recommended operator.

- `shareReplay(bufferSize | config)`: multicasts **and** replays the last `bufferSize` values to late subscribers.
  Commonly used to cache an HTTP response so multiple consumers share one request.

- `connectable(source)` / `connect()`: lower-level manual control over when the shared execution begins.
  (Replaces the deprecated `multicast`, `publish`, and `refCount` operators.)

```js
import { interval } from "rxjs";
import { share, shareReplay, take } from "rxjs/operators";

// share — one interval execution shared by both subscribers
const shared$ = interval(1000).pipe(take(3), share());
shared$.subscribe((x) => console.log("A", x));
shared$.subscribe((x) => console.log("B", x)); // same values, one execution

// shareReplay — cache an HTTP result for all subscribers
const config$ = ajax.getJSON("/api/config").pipe(
  shareReplay(1)   // request runs once; every subscriber gets the cached response
);
config$.subscribe(useConfig);
config$.subscribe(useConfigElsewhere); // no second HTTP request
```

--- 

## Schedulers

A **scheduler** controls **when** a subscription starts and **when** notifications are delivered — effectively the
concurrency model of a stream. Pass one to operators like `observeOn` / `subscribeOn`, or to creation functions.

- `asyncScheduler`: schedules work on the macrotask queue (like `setTimeout`). Default for time-based operators.

- `asapScheduler`: schedules on the microtask queue (like `Promise.then`) — runs before the next timer.

- `queueScheduler`: schedules synchronously in a queue — useful for recursion without stack overflow.

- `animationFrameScheduler`: schedules work with `requestAnimationFrame` — ideal for smooth animations.

- `observeOn(scheduler)`: re-emits notifications **using** the given scheduler.

- `subscribeOn(scheduler)`: schedules the **subscription** itself with the given scheduler.

```js
import { of, asyncScheduler } from "rxjs";
import { observeOn } from "rxjs/operators";

console.log("start");
of(1, 2, 3).pipe(
  observeOn(asyncScheduler)   // deliver values asynchronously
).subscribe(console.log);
console.log("end");
// Output: start  end  1  2  3
```

--- 

## Common Patterns

### Auto-unsubscribe (component teardown)

```js
import { Subject } from "rxjs";
import { takeUntil } from "rxjs/operators";

const destroy$ = new Subject();

source$.pipe(takeUntil(destroy$)).subscribe(handle);

// on destroy:
destroy$.next();
destroy$.complete();
```

### Type-ahead search

```js
fromEvent(input, "input").pipe(
  map((e) => e.target.value),
  debounceTime(300),
  distinctUntilChanged(),
  filter((term) => term.length > 1),
  switchMap((term) => ajax.getJSON(`/search?q=${term}`).pipe(
    catchError(() => of([]))   // keep the outer stream alive on error
  ))
).subscribe(render);
```

### Polling with cancellation

```js
import { timer } from "rxjs";
import { switchMap, takeUntil } from "rxjs/operators";

timer(0, 5000).pipe(               // immediately, then every 5s
  switchMap(() => ajax.getJSON("/api/status")),
  takeUntil(stop$)
).subscribe(updateStatus);
```

### Retry with exponential backoff

```js
import { timer } from "rxjs";
import { retry } from "rxjs/operators";

request$.pipe(
  retry({
    count: 5,
    delay: (_err, n) => timer(Math.min(1000 * 2 ** n, 30_000)),
  })
).subscribe(render);
```

