
# Common Programming Patterns in LeetCode and How to Approach Them

This guide covers major programming patterns frequently used in solving LeetCode problems, including their use cases, examples, and approaches.

---

## 1. Backtracking

**Use Cases:**

* Permutations
* Combinations
* Sudoku Solver
* N-Queens Problem

**Example Problems:**

* [Permutations](https://leetcode.com/problems/permutations/) (LC 46)
* [Combination Sum](https://leetcode.com/problems/combination-sum/) (LC 39)
* [Sudoku Solver](https://leetcode.com/problems/sudoku-solver/) (LC 37)

**Approach:**

1. Use recursion to explore all potential options.
2. Add a base case for stopping the recursion.
3. Use backtracking to undo previous choices.
4. Prune invalid paths early for efficiency.

---

## 2. Two Pointers

**Use Cases:**

* Sorted array problems
* Linked list manipulation
* Opposite-direction searching

**Example Problems:**

* [Two Sum II - Input array is sorted](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/) (LC 167)
* [Remove Duplicates from Sorted Array](https://leetcode.com/problems/remove-duplicates-from-sorted-array/) (LC 26)

**Approach:**

1. Initialize two pointers at start and end.
2. Move pointers based on the condition.
3. Commonly used for sorted arrays.

---

## 3. Sliding Window

**Use Cases:**

* Subarray problems
* Maximum/minimum in a window
* Longest substring problems

**Example Problems:**

* [Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/) (LC 3)
* [Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/) (LC 209)

**Approach:**

1. Maintain a window using two pointers.
2. Expand/shrink the window based on constraints.
3. Track max/min/required values within the window.

---

## 4. Dynamic Programming (DP)

**Use Cases:**

* Optimization problems
* Overlapping subproblems
* Optimal substructure

**Example Problems:**

* [Climbing Stairs](https://leetcode.com/problems/climbing-stairs/) (LC 70)
* [Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/) (LC 5)
* [Coin Change](https://leetcode.com/problems/coin-change/) (LC 322)

**Approach:**

1. Identify subproblems.
2. Define state variables.
3. Create recurrence relations.
4. Optimize using memoization or tabulation.

---

## 5. BFS & DFS

**Use Cases:**

* Tree and graph traversal
* Path finding
* Connected components

**Example Problems:**

* [Number of Islands](https://leetcode.com/problems/number-of-islands/) (LC 200)
* [Clone Graph](https://leetcode.com/problems/clone-graph/) (LC 133)

**Approach:**

* **DFS:** Recursively or using stack; explore as deep as possible.
* **BFS:** Use queue; explore level by level.

---

## 6. Binary Search

**Use Cases:**

* Searching in sorted arrays
* Monotonic functions
* Finding bounds (first/last occurrence)

**Example Problems:**

* [Binary Search](https://leetcode.com/problems/binary-search/) (LC 704)
* [Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/) (LC 153)

**Approach:**

1. Define low and high bounds.
2. Use mid = low + (high - low) / 2.
3. Adjust bounds based on condition.

---

## 7. Priority Queues

**Use Cases:**

* Task scheduling
* Finding k-largest/smallest elements
* Dijkstra's algorithm

**Example Problems:**

* [Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/) (LC 23)
* [Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/) (LC 347)

**Approach:**

1. Use `heapq` in Python or `PriorityQueue` in Java.
2. Define custom comparator if needed.

---

## 8. Trie

**Use Cases:**

* Prefix search
* Autocomplete
* Dictionary storage

**Example Problems:**

* [Implement Trie (Prefix Tree)](https://leetcode.com/problems/implement-trie-prefix-tree/) (LC 208)
* [Word Search II](https://leetcode.com/problems/word-search-ii/) (LC 212)

**Approach:**

1. Implement a TrieNode with children and word-end marker.
2. Build Trie for dictionary.
3. Use it for efficient prefix queries.

---

## 9. Greedy

**Use Cases:**

* Interval scheduling
* Resource allocation
* Path optimization

**Example Problems:**

* [Jump Game](https://leetcode.com/problems/jump-game/) (LC 55)
* [Greedy Jump Game II](https://leetcode.com/problems/jump-game-ii/) (LC 45)
* [Activity Selection](https://www.geeksforgeeks.org/greedy-algorithms-set-1-activity-selection-problem/)

**Approach:**

1. Make the locally optimal choice.
2. Prove or validate it leads to a global optimum.
3. Sort if necessary to prioritize selection.

---

## 10. Sorting

**Use Cases:**

* Array transformation
* Counting problems
* Prioritization

**Example Problems:**

* [Merge Intervals](https://leetcode.com/problems/merge-intervals/) (LC 56)
* [Meeting Rooms II](https://leetcode.com/problems/meeting-rooms-ii/) (LC 253)

**Approach:**

1. Choose correct comparator logic.
2. Sort data upfront.
3. Combine sorted results as needed.

---

## 11. Pattern Matching

**Use Cases:**

* String comparison
* Regex-like problems
* Word patterns

**Example Problems:**

* [Word Pattern](https://leetcode.com/problems/word-pattern/) (LC 290)
* [Regular Expression Matching](https://leetcode.com/problems/regular-expression-matching/) (LC 10)

**Approach:**

1. Map between characters and words (for bijection).
2. Use backtracking or DP for regex patterns.

---

## Notes

* These patterns often overlap.
* Combine multiple patterns to solve complex problems.
* Practice recognizing which pattern applies based on constraints and input size.

---

*End of File*

