# Hash Table for a Music Application — Division Method (C)

DSA assignment: hash table implementation in C, using the Division
Method with separate chaining, plus a comparison against linear search.

**Song IDs:** `105, 210, 315, 420, 525, 630, 735, 840` | **Table size:** `m = 10`

## Repository structure

```
song-hash-c/
├── src/
│   └── hash_table.c          # source code (Parts A & B, in C)
├── input/
│   └── input_data.txt        # exact input data used
├── output/
│   └── output.txt            # captured program output (Parts A & B)
├── docs/
│   ├── trace_table.md        # step-by-step trace tables (insert + search)
│   ├── complexity_analysis.md# load factor, theoretical vs observed complexity
│   ├── comparison_table.md   # hashing vs linear search, side by side
│   └── conclusion.md         # final justification / recommendation
└── README.md                 # this file
```

## How to compile and run

```bash
gcc -Wall -o hash_table src/hash_table.c
./hash_table
```

To regenerate `output/output.txt` yourself:

```bash
./hash_table > output/output.txt
```

## Summary of results

- **Collisions during insertion:** 6 out of 8 (only 2 of 10 buckets used —
  every ID is a multiple of 105, which shares a factor with the table
  size 10; see `docs/complexity_analysis.md`)
- **Load factor:** alpha = 8 / 10 = **0.8**
- **Average comparisons — hashing:** 2.75
- **Average comparisons — linear search:** 5.00
- **Conclusion:** hashing is faster on average even under heavy
  collisions, and is the right structure for this application **provided
  a well-chosen (prime) table size** is used — full reasoning in
  `docs/conclusion.md`.

See `docs/trace_table.md`, `docs/complexity_analysis.md`,
`docs/comparison_table.md`, and `docs/conclusion.md` for the full
write-up required by the assignment.

## Submitting this as a GitHub repository

1. **Create the repo**
   - GitHub → **New repository** → name it (e.g. `song-hash-table-dsa-c`)
     → leave it empty (no README/gitignore, you already have one) →
     **Create repository**.

2. **Push the project** (run inside the `song-hash-c` folder):

   ```bash
   git init
   git add .
   git commit -m "Hash table (Division Method) in C: source, input, output, trace tables, analysis"
   git branch -M main
   git remote add origin https://github.com/<your-username>/<repo-name>.git
   git push -u origin main
   ```

3. **Verify on GitHub** that all four folders (`src/`, `input/`,
   `output/`, `docs/`) and this README show up correctly, and that the
   markdown tables in `docs/` render properly.

4. **Submit the link**, e.g.
   `https://github.com/<your-username>/<repo-name>`

If `git` isn't configured yet:
```bash
git config --global user.name "Your Name"
git config --global user.email "you@example.com"
```
