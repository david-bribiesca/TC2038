# Problem C — 0/1 Knapsack

## Compile

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main
```

## Run

```bash
./main < input.txt
```

## Test cases

**Input**
```
3 10
3 4
4 5
7 10
```
**Output**
```
14
```
(Take modules 1 and 3: time 3+7=10, value 4+10=14.)

**Input**
```
3 5
6 10
7 20
8 30
```
**Output**
```
0
```
(No module fits inside a budget of 5.)

**Input**
```
4 6
1 2
2 4
3 4
4 7
```
**Output**
```
11
```
(Take modules 2 and 4: time 2+4=6, value 4+7=11.)

**Input**
```
1 10
10 99
```
**Output**
```
99
```

**Input**
```
5 10
2 3
3 4
4 5
5 6
9 10
```
**Output**
```
13
```
