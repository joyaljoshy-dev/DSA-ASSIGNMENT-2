# Comparison Table — Hashing vs Linear Search

## A. Per-key comparison count (from actual program run)

| Key | Hashing: Found | Hashing: Comparisons | Linear Search: Found | Linear Search: Comparisons | Faster method |
|---|---|---|---|---|---|
| 420 | True  | 3 | True  | 4 | Hashing |
| 735 | True  | 5 | True  | 7 | Hashing |
| 999 | False | 1 | False | 8 | Hashing |
| 105 | True  | 2 | True  | 1 | **Linear search** (105 is first in the array) |
| **Average** | — | **2.75** | — | **5.00** | Hashing (overall) |

## B. Structural comparison

| Aspect | Hashing (Division Method + Chaining) | Linear Search |
|---|---|---|
| Time complexity (average) | O(1 + alpha) | O(n) |
| Time complexity (worst case) | O(n) (all keys in one chain) | O(n) |
| Space complexity | O(n + m) | O(n) |
| Depends on data distribution? | Yes — a poor hash/table-size choice (as seen here) degrades performance sharply | No — always scans in the same way regardless of data pattern |
| Performance as n grows | Roughly constant, if table is resized / rehashed to keep alpha low | Grows linearly, always |
| Implementation complexity | Higher (hash function, collision handling, possible resizing) | Very low |
| Best for | Frequent lookups, large or growing datasets | Small datasets, or one-off scans where simplicity matters more than speed |

## C. Result of this specific run

Even with heavy collisions (load factor 0.8, 6 collisions out of 8
inserts), hashing still averaged fewer comparisons (2.75) than linear
search (5.00) across the 4 test keys. The one exception (`105`) is
expected: linear search is unbeatable when the target happens to be the
very first element checked, but that advantage disappears as soon as
the dataset grows or the target is anywhere else — which is the normal
case in a real music app.
