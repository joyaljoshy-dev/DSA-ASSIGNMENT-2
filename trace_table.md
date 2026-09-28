# Trace Tables

## Trace Table 1 — Insertion (Part A)

Table size `m = 10`. Hash function: `h(k) = k mod 10`.

| Step | Key inserted | h(key) calculation | Index | Bucket before | Collision? | Bucket after |
|---|---|---|---|---|---|---|
| 1 | 105 | 105 mod 10 | 5 | `[]` | No  | `[105]` |
| 2 | 210 | 210 mod 10 | 0 | `[]` | No  | `[210]` |
| 3 | 315 | 315 mod 10 | 5 | `[105]` | **Yes** | `[105, 315]` |
| 4 | 420 | 420 mod 10 | 0 | `[210]` | **Yes** | `[210, 420]` |
| 5 | 525 | 525 mod 10 | 5 | `[105, 315]` | **Yes** | `[105, 315, 525]` |
| 6 | 630 | 630 mod 10 | 0 | `[210, 420]` | **Yes** | `[210, 420, 630]` |
| 7 | 735 | 735 mod 10 | 5 | `[105, 315, 525]` | **Yes** | `[105, 315, 525, 735]` |
| 8 | 840 | 840 mod 10 | 0 | `[210, 420, 630]` | **Yes** | `[210, 420, 630, 840]` |

**Final table state:**

| Index | Bucket contents |
|---|---|
| 0 | `[210, 420, 630, 840]` |
| 1 | `[]` |
| 2 | `[]` |
| 3 | `[]` |
| 4 | `[]` |
| 5 | `[105, 315, 525, 735]` |
| 6 | `[]` |
| 7 | `[]` |
| 8 | `[]` |
| 9 | `[]` |

Total collisions: **6** (out of 8 insertions). Only 2 of the 10 buckets
are ever used — see `complexity_analysis.md` for why.

---

## Trace Table 2 — Search using Hashing (Part B)

`comparisons` = 1 (computing the hash index) + 1 per key checked while
walking the bucket's chain.

| Key | h(key) | Bucket visited | Elements checked (in order) | Match found at | Comparisons |
|---|---|---|---|---|---|
| 420 | 0 | `[210, 420, 630, 840]` | 210 (no), 420 (yes) | 2nd in bucket | 1 + 2 = **3** |
| 735 | 5 | `[105, 315, 525, 735]` | 105 (no), 315 (no), 525 (no), 735 (yes) | 4th in bucket | 1 + 4 = **5** |
| 999 | 9 | `[]` | — (bucket empty) | not found | 1 + 0 = **1** |
| 105 | 5 | `[105, 315, 525, 735]` | 105 (yes) | 1st in bucket | 1 + 1 = **2** |

Total comparisons across 4 searches: 3 + 5 + 1 + 2 = 11
Average = 11 / 4 = **2.75**

---

## Trace Table 3 — Linear Search over the original array (Part B)

Array (index : value): `0:105, 1:210, 2:315, 3:420, 4:525, 5:630, 6:735, 7:840`

| Key | Elements checked in order (index:value) | Match found at index | Comparisons |
|---|---|---|---|
| 420 | 0:105(no), 1:210(no), 2:315(no), 3:420(yes) | 3 | **4** |
| 735 | 0:105 … 6:735(yes) (7 checks) | 6 | **7** |
| 999 | 0:105 … 7:840, no match (8 checks) | not found | **8** |
| 105 | 0:105(yes) | 0 | **1** |

Total comparisons across 4 searches: 4 + 7 + 8 + 1 = 20
Average = 20 / 4 = **5.00**
