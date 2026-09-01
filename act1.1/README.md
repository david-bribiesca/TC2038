# Act 1.1 — Algorithm Design Mini Lab

Analysis and Design of Advanced Algorithms (TC2038)

This activity contains three independent problems, each solved with a
different algorithm design technique:

| Problem | Folder | Technique | Description |
|---|---|---|---|
| A | [`problemA/`](problemA) | Divide and Conquer (Merge Sort) | Count inversions in an array |
| B | [`problemB/`](problemB) | Greedy | Minimum number of meeting rooms |
| C | [`problemC/`](problemC) | Dynamic Programming | 0/1 Knapsack (budgeted study plan) |

See [`report.md`](report.md) for pseudocode, correctness arguments, and
complexity analysis of all three problems.

## General requirements

- Language: C++17.
- Input: read from **stdin**.
- Output: written to **stdout**.
- 64-bit integers (`long long`) are used wherever a count or sum could
  exceed the 32-bit range (e.g., inversion counts, knapsack values).

## How to compile

Each problem folder contains its own `main.cpp`. Compile from inside the
corresponding folder:

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main
```

Run this once per problem, e.g.:

```bash
cd problemA && g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main && cd ..
cd problemB && g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main && cd ..
cd problemC && g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main && cd ..
```

## How to run

Each folder includes an `input.txt` with a sample test case.

**Linux / macOS:**
```bash
./problemA/main < problemA/input.txt
./problemB/main < problemB/input.txt
./problemC/main < problemC/input.txt
```

## Assumptions

- **Problem A:** array values fit in a 32-bit signed range on input, but
  the inversion count is accumulated as `long long` since it can exceed
  32 bits for large `n` (up to `n(n-1)/2` inversions).
- **Problem B:** if one meeting ends exactly when another starts
  (`e_i = s_j`), they are **not** considered overlapping and may share a
  room (half-open interval semantics), per the assignment's clarification.
- **Problem C:** each module/item can be selected **at most once** (0/1
  knapsack, not the unbounded/fractional variant). Values are stored as
  `long long` because the total value can approach `n * max(value) =
  2000 * 10^6 = 2*10^9`, close to the 32-bit signed limit.
- No interactive prompts are printed; programs read all input from stdin
  in the format documented in each problem's `README.md` and write only
  the final answer to stdout.