# Parallel Programming

## Architecture and Performance

### Speedup

It is the sequential execution time divided by the parallel execution time.

$$
  S(n) = \frac{T(s)}{T(n)}
$$

It depends on the number of cores $n$. For example: for 2 cores the speedup should be 
idealy 2.

### Efficiency

It is the **speedup** divided by the number of cores.

$$
  E(n) = \frac{S(n)}{n}
$$

The ideal case is an efficiency of 1. 

### Amdahl's Law

Each program has a part which cannot be performed in parallel.

Given:

- $p$ the part of the program which can run in parallel. In percentage.
- $s$ the non-parallel part $s + p = 1$
- $n$ cores
- $S(n)$ and $E(n)$ the speedup and efficiency

Then the following holds:

- If the program runs sequentially in time $x$, then the program runs in parallel in $sx + \left(\frac{p}{n}\right)x$.
Therefore, $S(n) = \frac{T_s}{T_p} = \frac{x}{sx + \left(\frac{p}{n}\right)x} = \frac{1}{s + (p/n)}$

$$
  S_{max}(n) = \frac{1}{s + (p/n))}.
$$

The ideal case is $s = 0$ and $p = 1$ then

$$
  S_{max}(n) = \frac{1}{(1/n)} = n,
$$

which means that the program can run completely in parallel.

The maximal **speedup** as $n \to \infty$ is $S_{max}(p) = \frac{1}{s}$.

In summary, the speed of each program with a non parallel portion will reach a limit 
even if we increase the number of cores.

### Reality

In the real world when a certain number of cores is reached we encounter **parallel overhead** due
to synchronization and communication problems. Also, not only we reach a speed limit, but 
after adding more cores we can hurt the performance.

### Scalability

A program is considered scalable if

- A large portion can run in parallel
- The processes or threads do not exchange too much data
- It has to make sense to run in parallel
- If there is data sharing, then the communication has to be efficient

Good Scalability means: 

- The speedup is near the optimum, even by multiple cores 
- The efficiency stays be multiple cores also near 1

### Superlinear Scalability

When the speed of execution is way faster than before we can encounter this case.
The reasons are mostly:

- Perfect division of work
- The amount of data is small
- The data is extremly cache-friendly

---

## Parallel Architecture

### Components

We have the following structure for hardware which allows parallel programs:

- **Cores**: the processing units. They can share the cache regions or have each dedicated ones.

- **On-chip cache**: small quick access memory region

- **Off-chip-cache**: bigger quick access memory region

- **RAM**: Big, but also slower memory region.


### One core Architecture

One core, one on/off-chip-cache and one memory.

We can not achive true parallelism, only concurrency which might be enought but it has its limits when 
we want to run multiple processes. Specially with **cache-misses** which cost a lot time.

We cannot just increase the clock-rate due to physical limitations. Hence,
we need the complexity of parallel hardware for efficient computing.

### Shared Memory Systems

Mutiple cores share the same RAM.

They can perform **symmetric multiprocessing** allowing them to use all shared resources. It is easy to do  
multiprocessing in such systems, most of the heavy-lifting is handled by the operating system.

The case of **asymmetric multiprocessing** is a little bit more complex, because we have specialized cores 
for certain task. Example: CPU + GPU.

### Distributed Memory Systems

Each of the cores has its own memory and they are connected via a fast network. This may be efficient for certain cases, but
at the same time it is harder to coordinate and program in such systems.

### Hybrid Systems 

This systems use a combination of the shared and distributed systems. For example: we can have 
different groups of cores which share a certain number of RAM-chips and other which have access to other RAM-chips. They 
are connected via a fast network. 

### NUMA

**Non Uniform Memory Access** each core or group of cores has its own memory region, but they can also access the regions
of other cores/groups. This leads to slower communication when this clusters need to exchange information; therefore it 
is importan where the data is located in memory. 

There is a variation with the prefix **cc-** which means cache coherent. This allows the synchronization of the cache of the
clusters.

### Clusters-System

A cluster is a group of interconnected nodes. Nodes are individual computing entities of one or more cores 
which are connected via a fast network. 

In clusters we often have shared memory on different nodes.

### Processes

A **process** is an instance of a program with its own memory region. Process can not directly access 
the memory of other processes but they can communicate via pipes or via specific memory regions provided by 
the operating system for message passing.

### Threads

Threads are inner entities in a process which can be executed concurrently inside a process. They have their own CPU state and are
handled via syscalls for creation, deletion and execution. When the OS changes from one process to another it will execute the
threads which are not sleeping.

From the OS perspective a thread is not very different from a process but for a developer it is a
way to inform the operating system that specific regions of a program can be executed concurrently.

---

## Parallel Patterns

### Master Worker

There is one **master thread** which can instantiate multiple **worker threads**
to do certain work. This is the case for the well known **thread pool**.

The synchronization points are

- The master gives a worker the data and task
- The worker gives the master the result

Java example:

```java

// Worker
public class Worker extends Thread {
 private int x;
 private int res;

    // In java the start() does not accept or return values; therefore, we use attributes of 
    // the worker for the arguments and return value of our routine
 public Worker(int x) {
  this.x = x;       // Parameter was given to the worker
  this.start();     // start() begins the execution of another thread and call the runs() method
 }
 
 public void run() {   // The actual routine for the thread
  this.res = this.x * this.x;      
 }
  
 public int get() {    // Getter for the master to get the data
  try {
   this.join();  // Waiting for the thread
  } catch (InterruptedException e) {
   return -1;
  }
  return this.res;
 }
}


// Master
public class Test { 
 public static void main(String[] args) {
 
        Worker w = new Worker(5); // the worker thread is instantiated and starts running
    
  int r = w.get();  // joining the thread and getting the result
  System.out.println(r);
 }
}
```

**Disadvantages**:

- Starting a thread takes time. It is better to already have them instantiated in a thread pool.
- We can use streams with `parallel()` instead of creating another class when the routine is not very complex.

#### Blocking Queue 

If a worker-thread wants to take an element/task from an empty queue it is blocked, means it has to wait until
a producer comes and fills up the queue with some task. Anagously, if the master/producer wants to 
enqueue more task on an already full queue it has to wait until the worker-threads have already make space for new 
tasks.


### Thread Pool in Java

Java already provides an abstraction for a thread pool

```java
ExecutorService executor = Executors.newFixedThreadPool(4);  // fixed-size number of threads
ExecutorService executor = Executors.newCachedThreadPool();  // variable number of threads
```

With `submit` we can pass a lambda or **closure** which is going to be our task. The return type is
`Future<T>`.

Example with lambda:

```java

// submitting a task to the thread pool
Future<Integer> fu = ForkJoinPool.commonPool().submit(() -> {
 calcLifeUniverseAndEverything();
 return 42;
});


int result = fu.get();
```

Example with closure as anonymous `Callable` class:

```java

// A limitation of java is that the parameter has to be final or it can not be modified
// in the body of the closure
public static Future<Integer> square(final int z) {
    // Using an anonymous class for the closure
    return ForkJoinPool.commonPool().submit(new Callable<Integer>() {
          public Integer call() {
              return z * z;
          }
    });
}

public static void main(String[] args) {
 
    Future<Integer> future = square(5);

 int res;
 try {

        res = future.get();
        System.out.println(res);
 
    } catch (InterruptedException | ExecutionException e) {
  e.printStackTrace();
 }
}
```

In addition to the pool we also have two blocking **queues** for the incoming
and outgoing tasks. They are used to keep track of the ins and outs and to whom the results
have to be delivered.

They are implemented in java under

```java
LinkedBlockingQueue<T>
```

#### Examples of master worker using multiple processes

Example on the same computer:

```java

public static void main(String[] args) throws IOException {

    // Creating a process
 ProcessBuilder pb = new ProcessBuilder("java", "-cp", "c:/PP26/bin", "Worker");
 Process process = pb.start();

 // Streams for communication

    // Using stdout as the input for the other process
 PrintWriter parameter = new PrintWriter(process.getOutputStream());
    
 Scanner result = new Scanner(process.getInputStream());

 // Parameter passing
 parameter.println(5);
 parameter.flush(); // necessary!!!!!

 // Getting the result
 System.out.println(result.nextLine());

}

```

Example over a network:

```java

public static void main(String[] args) {

 try (Socket socket = new Socket("tcpbin.com", 4242)) {   //Echo-Server
  
  // Blocking Queues  
  PrintWriter request = new PrintWriter(socket.getOutputStream(), true);
  Scanner response = new Scanner(socket.getInputStream());
  
  // Making the request  
  request.println("Hallo öffentlicher Server!");

  
  // Getting the response
  String res = response.nextLine();
  System.out.println("Antwort: " + res);

 } catch (IOException e) {
  e.printStackTrace();
 }
}

```

Example with Async

```java

public static void main(String[] args) throws Exception {

 HttpClient client = HttpClient.newHttpClient();

 HttpRequest request = HttpRequest.newBuilder().uri(URI.create("https://jsonplaceholder.typicode.com/posts/1"))
   .GET().build();
    
 // Sending the request
 Future<HttpResponse<String>> future = client.sendAsync(request, HttpResponse.BodyHandlers.ofString());
  
  
 // Getting the response
 HttpResponse<String> response = future.get();
 String s = response.body();
 System.out.println(s);
}
```

#### Recursive example

Parallelis is not only limnited to iterative approaches, but also for recursive ones.
```java

public static int fibonacci1Parallel(final int i) throws Exception {
 
 if (i <= 2) {
  return 1;
 }
 
 Future<Integer> f1 = ForkJoinPool.commonPool().submit(() -> {
  return fibonacci1Parallel(i - 1);
 });
 
 return fibonacci1Parallel(i - 2) + f1.get().intValue();
}
```

### Work-Stealing-Pool

This is a strategy used by thread pools for when there are a lot of work to do, but 
no workers threads available. In this case a worker-thread can push its state into a stack and 
continue working on the other available work. Then if its or a task from other thread was not finnished it enqueues 
the new resut into the return queue, and pops its stae from the start to continue working

This is specially well suited for recursive approaches.

### Parallel Loops

The go-to way of doing this is via streams. Note that not only foreach-like 
(concrete) loops are suited for this, also non-concrete loops can be parallelized but a 
little bit different and it is harder to predict its behaiviour.

**Concrete**:

```java

int[] arr = IntStream.rangeClosed(0, 100)
     .parallel()
     .map(i -> (int)Math.pow(i, 2))
     .toArray();

int[] arr2 = {1,6,2,67,23,4,2,7,2,4,2};
int sum = Arrays.stream(arr2).parallel().sum();
```

**Non-concrete**:

```java
IntStream.iterate(0, i->i<3200, i->i+1).parallel().forEach((int i) -> {
 id[i] = (int)Thread.currentThread().threadId();
});
```

Internally our domain of indeces is divided into blocks and each loop with the new domains
performs the operation in parallel.

---

## Atomic Operations

Atomic operations are operations that are completed in a single step relative to other threads.
They are indivisible and cannot be interrupted.

Java provides atomic data-types for this kind of operations

- `AtomicBoolean`
- `AtomicInteger`
- `AtomicLong`

Example:

```java

import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.IntStream;

public class AtomicDataTypes {
 public static void main(String[] args) {
  
  final AtomicInteger sum = new AtomicInteger(0);
  
  IntStream.range(0,1000000).parallel().forEach((int i)->{
   sum.addAndGet(1);
  });
  
  System.out.println(sum.get());
 }
}
```

In the case of `C` we use mutexes and other simpler abstractions.

---

## Mutexes and Condition Variables

Mutexes (mutual exclusions) and condition variables are synchronization primitives used to manage access to shared resources in concurrent programming.
Mutexes provide a way to lock a resource so that only one thread can access it at a time, preventing race conditions.

Condition variables allow threads to wait for certain conditions to be met before continuing execution, enabling more complex synchronization patterns.

Both approaches use **atomic operations** to ensure no race conditions occur.

---

## Reduction Operations

Some languages and libraries which offer so called **reduction operations** which for example
in the case of java-streams with `sum` or others the operation is reduced to its return value.
These operations are well suited for parallelization.

The general syntax has a form:

$$
 \mathrm{reduce(identity, operator)}
$$

the allowed functions have names like: allMatch, anyMatch, average, count, findAny, findFirst, max, min, noneMatch, sum

```java

int[] arr = {1,6,2,67,23,4,2,7,2,4,2};

int sum = Arrays.stream(arr).parallel().reduce(0, (x, y) -> x+y);

int max = Arrays.stream(arr).parallel().reduce(Integer.MIN_VALUE, (x, y) -> Math.max(x, y));

int maxIdx = IntStream.range(0, arr.length).reduce(0, (x, y) -> arr[x] > arr[y] ? x : y);
```

---

## Common Problems in Parallel Programming

### Race Conditions

Race conditions occur when multiple threads or processes access shared resources concurrently, and the
final outcome depends on the timing of their execution. The minimal requirement are two threads from which at
least one overwrites the variable.

The solution are mutexes and synchronization mechanism.

Example:

```java

public class RaceCondition {
 private void raceCond() {
  int[] res = {0}; 
  IntStream.range(0, 1000000).parallel().forEach(i -> res[0]++);
  System.out.println(res[0]); // there is not guarantee that the other thread terminates before this
 }

 private void solution() {
  int[] res = {0}; 
  IntStream.range(0, 1000000).parallel().forEach(i -> {
  synchronized (res) { res[0]++ } 
  });
  System.out.println(res[0]);  
 }
}

```

### Structures Suited and Unsuited for parallelization

**Suited**:

- Recursion
- Backtracking
- Nested Loops

**Unsuited**:

- Simple loops
- Intrinsic sequential problems like loops where the order matters

Example of an unsuited loop:

```java
public int indexOf(String s, char c) {
  for (int i=0; i<s.length(); i++) {
    if (s.charAt(i)==c) {
      return i;
    }
  }
  return -1;
}
```

### Serialization

This problem occurs when we try to run a portion of our program in parallel and we end up
with just sequential execution.

### Deadlocks

This happens when two or more threads or processes are waiting for a "signal" which
can only be sent if the other sends it but it is also waiting for the signal of the other. This
results in a lock.

### Work Imbalance

Some threads get too little work and the others too much. This leads to questionable
performance improvements or directly to a decrement.

---
