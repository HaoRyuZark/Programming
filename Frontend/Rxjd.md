# RxJS

**RxJS** is a reactive library for JavaScript used by a lot of projects and frameworks like **Angular**.

--- 

## Async Model 

--- 

## Streams 


--- 

## Bindin RxJS 

```html 

```

--- 

## Data Sources

--- 


## Observables

An **observable** is informally: something like an array which gets build over time. This library provides a large numbers
of operator which makes using observables easier than vanilla JavaScript.

Basic example:

```js 
let button = document.querySelector('button');

Rx.Observable.fromEvent(button, 'click')
    .throttleTime(1000)                     // every 1000 mls
    .map((data) => return data.clientY;)    // get the clientY-coord
    .subscribe(
        (coordinate) => console.log(coordinate) // log it to the console
    )
```

### Observers

- `next()`:

- `error()`:

- `complete()`:


```js 

```

### Creation 

All of the next are methods of `Rx.Observable`

- `.create()`:

- `.fromPromise()`: 

- `.interval()`:

- ``

--- 

## Operators

### .filter

### .map 

### .do / .tap

### .first & .last

### .throttleTime 

### .debounce 

### .scan

### .switch / .switchAll 

### .switchMap 

### .takeUntil 

### .takeWhile

### .zip

### .forkJoin

- `forkJoin()`: It waits for obsevables to complete and then it combines the values together.
    - ``

```js 

```


### .catch / .catchError


### .retry

### .finally() / .finalize()

### .throw() / .throwError()

### .pluck()

### .mergeMap()


---

## Pipes

--- 


## .multicast


--- 

## Subject

--- 

## BehaviorSubject



