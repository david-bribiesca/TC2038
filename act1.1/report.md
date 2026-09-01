# Act 1.1 — Technical Report

This report covers the three problems solved in Act 1.1:

- **Problem A** — Counting Inversions (Divide and Conquer / Merge Sort)
- **Problem B** — Minimum Number of Meeting Rooms (Greedy)
- **Problem C** — 0/1 Knapsack (Dynamic Programming)

For each problem: language-agnostic pseudocode, a correctness argument,
a complexity analysis, and a verified example execution are given below.

---

## Problem A — Counting Inversions

### Pseudocode

```
function MERGE-COUNT(A, l, mid, r):
    Left  <- A[l .. mid]          // copy of left half
    Right <- A[mid+1 .. r]        // copy of right half
    i <- 0, j <- 0, k <- l
    inversions <- 0

    while i < length(Left) and j < length(Right):
        if Left[i] <= Right[j]:
            A[k] <- Left[i]; i <- i + 1
        else:
            A[k] <- Right[j]; j <- j + 1
            inversions <- inversions + (length(Left) - i)   // Left[i..] all > Right[j]
        k <- k + 1

    copy any remaining elements of Left into A
    copy any remaining elements of Right into A
    return inversions


function COUNT-INVERSIONS(A, l, r):
    if l >= r:
        return 0
    mid <- floor((l + r) / 2)
    inversions <- COUNT-INVERSIONS(A, l, mid)
                + COUNT-INVERSIONS(A, mid + 1, r)
                + MERGE-COUNT(A, l, mid, r)
    return inversions

// Driver
read n, A[1..n]
print COUNT-INVERSIONS(A, 1, n)
```

### Correctness argument

**Loop invariant (merge step).** At the start of each iteration of the
merge `while` loop, `A[l .. k-1]` contains the `k - l` smallest elements of
`Left[i..] ∪ Right[j..]` in sorted order, and every inversion between an
already-placed element and a not-yet-placed element has been accounted for.

**Inductive argument (divide and conquer).**
- *Base case:* a subarray of size ≤ 1 (`l >= r`) has zero inversions and is
  trivially sorted.
- *Inductive step:* assume `COUNT-INVERSIONS` correctly sorts and counts
  inversions for any subarray of length `< r - l + 1`. By the induction
  hypothesis the two recursive calls correctly sort `A[l..mid]` and
  `A[mid+1..r]` and correctly count all inversions *within* each half.
  What remains are **split inversions**: pairs `(x, y)` with `x` in the
  left half, `y` in the right half, and `x > y`. Because both halves are
  now individually sorted, whenever `MERGE-COUNT` takes an element
  `Right[j]` instead of `Left[i]`, it must be that `Right[j] < Left[i]`,
  and since `Left` is sorted ascending, `Right[j]` is also smaller than
  every remaining element `Left[i], Left[i+1], ..., Left[n-1]`. Hence all
  `length(Left) - i` remaining left elements form a split inversion with
  `Right[j]`, which is exactly what is added to `inversions`. No split
  inversion is double-counted (each `Right[j]` is processed once) and none
  is missed (every time a left element "loses" to a not-yet-placed right
  element, it is counted when that right element is placed).
- Total inversions returned = (left-half inversions) + (right-half
  inversions) + (split inversions) = all inversions in `A[l..r]`. ∎

### Complexity analysis

- **Time:** `T(n) = 2T(n/2) + O(n)` (two recursive calls of half size plus
  a linear-time merge/count step) which by the Master Theorem solves to
  **O(n log n)**.
- **Space:** `O(n)` auxiliary space for the temporary `Left`/`Right`
  buffers used during merging (reused level by level), plus **O(log n)**
  additional space for the recursion stack (recursion depth is
  `log2(n)`). Total auxiliary space: **O(n)**.

### Example execution

Input:
```
5
2 4 1 3 5
```
Trace (sketch): the array splits into `[2,4]` and `[1,3,5]`; each half is
sorted recursively (0 inversions inside `[2,4]`, 0 inside `[1,3,5]`); the
merge of `[2,4]` and `[1,3,5]` places `1` before `2,4` (2 split
inversions: `(2,1)`,`(4,1)`) and `3` before `4` (1 split inversion:
`(4,3)`), for a total of `3`.

Output:
```
3
```

---

## Problem B — Minimum Number of Meeting Rooms

### Pseudocode

```
function MIN-MEETING-ROOMS(meetings[1..m]):
    starts <- sort( [meetings[i].start for i in 1..m] )
    ends   <- sort( [meetings[i].end   for i in 1..m] )

    rooms <- 0
    maxRooms <- 0
    si <- 1, ei <- 1

    while si <= m:
        if starts[si] < ends[ei]:
            rooms <- rooms + 1              // a new meeting starts before the earliest one ends
            maxRooms <- max(maxRooms, rooms)
            si <- si + 1
        else:
            rooms <- rooms - 1              // the earliest running meeting has ended, free its room
            ei <- ei + 1

    return maxRooms
```

### Correctness argument

**Greedy-choice property.** Sorting start times and end times separately
and sweeping them in increasing order simulates, at any instant, the
number of meetings that are simultaneously in progress: `rooms` after
processing a prefix of `starts`/`ends` equals `(number of meetings started
so far) - (number of meetings ended so far)`, which is exactly the number
of meetings currently active, regardless of *which* specific meeting
occupies which room (any free room can host any newly starting meeting —
this is the greedy/exchange-argument insight: room *identity* never
matters, only room *count*).

**Invariant.** At every iteration, `rooms` equals the number of meetings
whose start time (among the first `si` sorted starts) is less than the
current smallest unprocessed end time boundary being compared — i.e., the
number of meetings active at the time of the most recently processed
start. Because `starts` and `ends` are both processed in non-decreasing
order, comparing `starts[si]` to `ends[ei]` always compares the next
chronological event, so `rooms` is updated in true time order and never
undercounts or overcounts concurrent meetings.

**Optimality.** `maxRooms` is the maximum, over all instants in time, of
the number of concurrently active meetings. This quantity is a **lower
bound** on any valid room assignment (you cannot host `k` simultaneous
meetings in fewer than `k` rooms), and it is also **achievable** (assign
meetings to rooms greedily as they start, reusing any room freed by an
earlier meeting — since at most `maxRooms` meetings are ever
simultaneously active, `maxRooms` rooms always suffice). Hence `maxRooms`
is exactly the minimum number of rooms required. ∎

### Complexity analysis

- **Time:** sorting `starts` and `ends` costs `O(m log m)` each; the
  sweep is a single pass over `2m` events, `O(m)`. Total: **O(m log m)**.
- **Space:** `O(m)` for the `starts` and `ends` arrays (auxiliary copies
  of the input). No recursion is used. Total auxiliary space: **O(m)**.

### Example execution

Input:
```
3
1 4
2 5
7 9
```
Trace: `starts = [1,2,7]`, `ends = [4,5,9]`.
- `1 < 4` → rooms=1 (max=1)
- `2 < 4` → rooms=2 (max=2)
- `4 !< 4`... `4 < 5`? Compare `starts[2]=7` vs `ends[0]=4`: `7 < 4` false → rooms=1, advance ends
- `7 < 5`? false → rooms=0, advance ends
- `7 < 9`? true → rooms=1 (max stays 2)

Output:
```
2
```

---

## Problem C — 0/1 Knapsack

### Pseudocode

```
function KNAPSACK(n, T, time[1..n], value[1..n]):
    dp <- array[0..n][0..T] initialized to 0

    for i <- 1 to n:
        for j <- 1 to T:
            if time[i] > j:
                dp[i][j] <- dp[i-1][j]                       // item i cannot fit
            else:
                dp[i][j] <- max( dp[i-1][j],                 // skip item i
                                  dp[i-1][j - time[i]] + value[i] )  // take item i

    return dp[n][T]
```

### Correctness argument

**Recurrence / optimal substructure.** Define `dp[i][j]` as the maximum
value obtainable by choosing a subset of the first `i` items with total
time at most `j`. Every optimal solution to the subproblem `(i, j)` either
excludes item `i` — in which case its value is exactly the optimum for
`(i-1, j)` — or includes item `i` (only possible when `time[i] <= j`) — in
which case the remaining items must form an optimal solution to
`(i-1, j - time[i])`, since if a better selection existed for that
reduced subproblem, substituting it would strictly improve the solution
for `(i, j)`, contradicting optimality. Hence:

```
dp[i][j] = dp[i-1][j]                                    if time[i] > j
dp[i][j] = max(dp[i-1][j], dp[i-1][j-time[i]] + value[i]) otherwise
```

which is precisely the recurrence implemented.

**Base case.** `dp[0][j] = 0` for all `j` (no items available, no value
attainable), and `dp[i][0] = 0` for all `i` (no time budget available),
both correctly initialized by the all-zero table.

**Inductive argument.** By induction on `i`: assume `dp[i-1][*]` holds the
correct optimum for every budget using the first `i-1` items. The
recurrence above computes `dp[i][j]` as the better of the two only
possible cases (exclude/include item `i`), so `dp[i][j]` is correct for
every `j`. By induction, `dp[n][T]` — the value returned — is the true
optimum over all `n` items with budget `T`. Since each item is only ever
referenced once per `(i, j)` transition (via `dp[i-1][...]`, never
`dp[i][...]`), no item can be counted twice, correctly enforcing the 0/1
(take-at-most-once) constraint. ∎

### Complexity analysis

- **Time:** the table has `(n+1) * (T+1)` cells, each computed in `O(1)`
  time. Total: **O(nT)** (pseudo-polynomial, since `T` is a numeric value,
  not the size of the input in bits).
- **Space:** the full 2D DP table uses `O(nT)` cells. No recursion is
  used. (This could be optimized to `O(T)` with a rolling 1D array, but
  the implementation as written uses the full 2D table.) Total auxiliary
  space: **O(nT)**.
- **Overflow note:** `dp` and `value` are stored as `long long`, since the
  total value can reach `n * max(value) = 2000 * 10^6 = 2 * 10^9`, which
  is close to the 32-bit signed limit (`INT_MAX ≈ 2.147 * 10^9`).

### Example execution

Input format (official — `t_i v_i` paired per line):
```
3 10
3 4
4 5
7 10
```
Items: `(time=3,val=4)`, `(time=4,val=5)`, `(time=7,val=10)`; budget
`T=10`. Optimal choice: items 1 and 3 (total time `3 + 7 = 10`, total
value `4 + 10 = 14`) — no other combination within budget `10` beats this.

Output:
```
14
```