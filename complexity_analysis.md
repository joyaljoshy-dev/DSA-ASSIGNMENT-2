# Complexity Analysis

## 1. Load Factor

```
alpha = n / m = 8 / 10 = 0.8
```

Where `n` = number of keys inserted (8), `m` = table size (10).

A load factor of 0.8 is high for separate chaining (0.7–1.0 is generally
where average chain length starts hurting performance noticeably), which
matches what the trace tables show: chains of length 4 in only 2 of the
10 buckets, instead of ~1 key spread evenly across 8 buckets.

## 2. Why the collisions happen (root cause)

Every song ID is a multiple of 105 (105 × 1, 2, 3, … 8), and
`gcd(105, 10) = 5`. Because the table size 10 shares the factor 5 with
105, `key mod 10` can only ever produce `0` or `5` for these particular
inputs — regardless of how "large" the table is. This is not a bug in
the hash function itself; it is a mismatch between the Division Method
and this specific, patterned dataset.

Testing other table sizes against the same 8 IDs confirms this:

| Table size m | `key mod m` for all 8 IDs | Collisions |
|---|---|---|
| 7  | `0,0,0,0,0,0,0,0` | 7 (single bucket — 105 is a multiple of 7) |
| 10 | `5,0,5,0,5,0,5,0` | 6 (two buckets — shares factor 5 with 105) |
| 11 | `6,1,7,2,8,3,9,4` | **0** |
| 13 | `1,2,3,4,5,6,7,8` | **0** |

**Conclusion of this sub-analysis:** the Division Method works best with
a prime table size that shares no factors with patterns in the key set.
`m = 11` or `m = 13` would have given a perfect, collision-free spread
of these 8 IDs; `m = 10` and `m = 7` are poor choices specifically
because every ID is a multiple of `3 × 5 × 7 = 105`.

## 3. Theoretical Time Complexity

| Operation | Best case | Average case | Worst case |
|---|---|---|---|
| Hashing — insert | O(1) | O(1) | O(n) (all keys hash to one bucket) |
| Hashing — search (chaining) | O(1) | O(1 + alpha) | O(n) (all keys in one chain) |
| Linear search | O(1) (key is first) | O(n) | O(n) |

**Space complexity:**
- Hash table (chaining): O(n + m) — `m` slots for the table itself, plus
  `n` nodes for the keys actually stored.
- Linear search over an array: O(n) — just the array; no auxiliary
  structure.

## 4. Observed vs Theoretical (this run)

| Metric | Theoretical expectation | Observed (this program) |
|---|---|---|
| Hashing average comparisons | Close to O(1) when alpha is low and distribution is uniform | **2.75** — noticeably above ideal O(1), because 6 of 8 keys are in 4-long chains |
| Linear search average comparisons | (n+1)/2 = 4.5 for n = 8 | **5.00** — close match to theory (small difference due to the specific mix of keys searched, e.g. one is a guaranteed miss) |

**Interpretation:** hashing still beats linear search here (2.75 vs
5.00 average comparisons), but it is far from its theoretical best.
With only 2 of 10 buckets used, each successful hash search essentially
degrades into a short linear scan (through a 4-element chain) instead
of a true O(1) lookup. This is a direct, measurable consequence of the
collisions caused by the table size / key pattern mismatch described
above — not a flaw in hashing as a technique.
