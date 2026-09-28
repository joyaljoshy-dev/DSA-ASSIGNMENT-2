# Final Conclusion

## Is hashing suitable for this music application?

**Yes — hashing (Division Method) is the right choice, provided the
table size is chosen carefully.**

**Why:**
1. A music app performs lookups constantly (playback, search-as-you-type,
   playlist building), and its song library can realistically grow into
   the thousands or millions of tracks. Linear search's O(n) cost scales
   badly at that size, while hashing stays close to O(1) on average.
2. Even in this project's worst-case setup (`m = 10`, load factor 0.8,
   6 collisions out of 8 inserts), hashing still needed fewer average
   comparisons than linear search (2.75 vs 5.00). The advantage only
   grows as the dataset gets larger.

**Why the caveat matters:**
This project's own results show that the Division Method is only as
good as the table size chosen relative to the data. Because every song
ID here was a multiple of 105, table sizes that share factors with 105
(`m = 7`, `m = 10`) caused heavy clustering into 1–2 buckets, while
prime sizes unrelated to that pattern (`m = 11`, `m = 13`) gave a
perfect, collision-free spread of the same 8 IDs.

## Recommendation

- Use the Division Method with a **prime table size**, sized comfortably
  above the expected number of songs (e.g., choose a prime `m` such that
  `n / m` stays around 0.6–0.7) so chains stay short as the library grows.
- If song IDs are ever generated in a predictable pattern (sequential,
  multiples of some base number, etc.), explicitly check the resulting
  distribution for a few candidate table sizes before committing to one
  — as demonstrated in `complexity_analysis.md`.
- Combine this with a resizing/rehashing strategy so the load factor
  doesn't creep upward indefinitely as more songs are added.

With those precautions, hashing comfortably outperforms linear search
for this application, both in theory and in the numbers this project
measured directly.
