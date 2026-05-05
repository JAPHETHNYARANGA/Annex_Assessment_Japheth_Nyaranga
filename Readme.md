# Annex Assessment - Japheth Nyaranga

## Overview
This repository contains solutions to coding assessment problems implemented in C, C++, and SQL:

| File              | Language | Problem Description |
|-------------------|----------|---------------------|
| `pth_factor.c`    | C        | Find the p-th smallest factor of number n (1-indexed) |
| `top_articles.cpp`| C++      | Fetch and rank top articles from HackerRank JSON mock API by comments (DESC), then title (DESC) |
| `top_students.sql`| SQL      | Query top 3 students by score (DESC), then ID (ASC) |

## Prerequisites
- macOS/Linux/Unix-like system with:
  - `gcc` (for C)
  - `g++` (for C++)
  - `curl` (required for `top_articles.cpp` API fetches)
- SQL client (e.g., sqlite3, psql) for SQL query

No additional installations or dependencies required.

## How to Run

### 1. pth_factor.c (Pth Factor)
```bash
gcc -o pth_factor pth_factor.c
./pth_factor
```
**Expected Output:**
```
5
8
100
```

### 2. top_articles.cpp (Top Articles)
```bash
g++ -o top_articles top_articles.cpp
./top_articles
```
**Expected Output:** (Top 2 article titles, varies by API data)
```
[First top article title]
[Second top article title]
```
*Note: Fetches live data from `https://jsonmock.hackerrank.com/api/articles`; requires internet.*

### 3. top_students.sql (Top Students)
Assuming a `STUDENT` table with columns `ID`, `NAME`, `SCORE`:
```bash
# Example with sqlite3 (create DB and run query as needed)
sqlite3 test.db
```
Then paste/run the query:
```sql
SELECT ID, NAME
FROM STUDENT
ORDER BY SCORE DESC, ID ASC
LIMIT 3;
```
**Expected Output:** (Depends on data)
```
1|Student1
2|Student2
3|Student3
```



## Author
Japheth Nyaranga  
[nyaranga4@gmail.com](nyaranga4@gmail.com) 



