# cp_template

Competitive programming templates and solved problems, organized by topic.

```
templates/     reusable code: paste into templates/base/cp_template.cpp
problems/      full solutions to specific problems, grouped by topic
```

Most snippets assume the macros from `templates/base/cp_template.cpp` (`int` = `long long`, `vi`, `rep`, `pb`, `nl`, `MOD`, ...).

## templates/

| Folder | Contents |
|---|---|
| `base/` | `cp_template.cpp`, the main starter file (debug, binExp/binMul safe up to 1e18, factorials/nCr, Mint, linear sieve + factorize, anti-hack hash) |
| `misc/` | coordinate compression, LIS, binary / ternary search, submask + SOS dp, __int128 io, digit dp skeleton, stress test script + generator |
| `number_theory/` | Miller-Rabin + Pollard rho, CRT (any moduli) + general inverse, linear sieve (mu, phi) + segmented sieve, discrete log, Euler totient, Mobius (full templates) |
| `math/` | matrix power, Gaussian elimination mod p + xor basis, Lagrange interpolation, FFT, NTT, exact convolution (two primes + CRT), FWHT, 2x2 linear equations |
| `combinatorics/` | full combinatorics template, Catalan numbers, de Bruijn sequence |
| `data_structures/` | DSU, DSU with parity, rollback DSU, offline edge deletion, Fenwick (point, range, 2d, lower bound), sparse table, ordered set (pb_ds), Li Chao tree, Mo's algorithm, persistent segment tree (k-th smallest), implicit treap, trie, binary trie (max/min xor), xor MST |
| `data_structures/segment_tree/` | generic lazy segment tree, iterative point-update tree, lazy range-add sum, max segment tree, range-add max |
| `data_structures/sqrt_decomposition/` | point update range min, range chmin + range sum |
| `graph/` | Dijkstra + 0-1 BFS, Bellman-Ford (negative cycles), Floyd-Warshall, Kruskal, bridges + articulation points + 2-edge components (multi-edge safe), biconnected components, SCC (Tarjan), 2-SAT, topological sort, bipartite coloring, Euler path (directed / undirected), one simple cycle, Kuhn, Hopcroft-Karp, Hungarian, Dinic, min cost max flow, dominator tree |
| `trees/` | binary lifting LCA, HLD, centroid decomposition, tree diameter, sum of all pair distances |
| `strings/` | KMP (+ automaton), Z function, Manacher, suffix array + LCP, Aho-Corasick, suffix automaton (+ generalized), palindromic tree, minimal rotation, Lyndon (Duval), wildcard matching (FFT), string DP (edit distance, LCS, distinct subsequences), bracket sequences, expression parser, big integers (decimal strings), subsequence automaton, Burrows-Wheeler transform |
| `strings/hashing/` | double hash (Hash struct, preCompute), hashing with point updates (DynHash, DynPal), forward + backward hash with O(1) palindrome check (PalHash), single substring hash, whole-string hash, lcp of suffixes of one or two different strings (needs double_hash), palindrome tracker (push_back / pop_back), set / multiset hashing with random values (xor_hash), 2D hashing |
| `geometry/` | 2d kit (exact segment intersection, point in polygon, area, Pick, closest pair, rotating calipers, angle sort, line / circle intersections), integer convex hull + point in convex polygon, Minkowski sum, 3d distances |

## problems/

| Folder | Problems |
|---|---|
| `dp/` | dice rolls, distance in tree, the queue, just another robbery, subgrid count 1 & 2, appleman and tree, Caesar's legions, Ada and subsequence, remove k subtrees, maximum product, coins exhibition, Berland federalization, compatible numbers (SOS dp) |
| `graph/` | cutting figure, CSES mail delivery, CSES level games, Bertown roads, cactus, fairy, min edges to make graph safe, word chain (Euler path), delete edges for degree constraint, UVa tourist guide, UVa network |
| `shortest_path/` | Jzzhu and cities, CF Dijkstra, Floyd with restricted intermediates, arbitrage with at most k trades |
| `trees/` | remove k edges to minimize max component |
| `flow/` | CSES download speed (Edmonds-Karp), police chase (min cut), school dance, distinct routes |
| `segment_tree/` | Sereja and brackets, save the trees, cakes (dp + segment tree) |
| `sqrt_decomposition/` | SPOJ DQUERY (Mo's), powerful array, cut and stick, holes, small-to-large value merge |
| `strings/` | good substrings, palindrome check, longest common substring, least period, tree isomorphism, longest palindromic substring, restore a+b=c expression (all hashing) |
| `game_theory/` | nim, misere nim, nimble nim, staircase nim (move the coins), Grundy problems, power beaker, knight game, stoned game |
| `number_theory/` | LCM sum (phi), count GCD, GCD extreme |
| `combinatorics/` | two arrays, trees counted by height, pankac |
| `data_structures/` | Shichikuji and power grid (DSU/MST), Vasiliy's multiset (xor trie) |
| `bit_manipulation/` | xor of a range (CF 2036F) |
