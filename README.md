# cp_template

Competitive programming templates and solved problems, organized by topic.

```
templates/     reusable code: paste into templates/base/cp_template.cpp
problems/      full solutions to specific problems, grouped by topic
assignments/   university online/offline assignment solutions
```

Most snippets assume the macros from `templates/base/cp_template.cpp` (`int` = `long long`, `vi`, `rep`, `pb`, `nl`, `MOD`, ...).

## templates/

| Folder | Contents |
|---|---|
| `base/` | `cp_template.cpp`, the main starter file (debug, binExp, factorials/nCr, Mint, sieve, anti-hack hash) |
| `number_theory/` | Euler totient, Mobius (standalone full templates) |
| `math/` | 2x2 linear equation solver, NTT (polynomial multiply), exact convolution (two primes + CRT), FWHT (xor convolution) |
| `combinatorics/` | full combinatorics template, Catalan numbers, de Bruijn sequence |
| `data_structures/` | DSU, DSU with parity, offline DSU (reverse edge deletion), sparse table, trie, xor minimum spanning tree |
| `data_structures/segment_tree/` | generic lazy segment tree, max segment tree, point update, lazy range-add sum, range-add max |
| `data_structures/sqrt_decomposition/` | range min query, sqrt decomposition with lazy min update |
| `graph/` | bridges, articulation points, biconnected components, SCC (Tarjan), Euler path (Hierholzer), bipartite coloring, Dijkstra, Floyd-Warshall, Dinic max flow, Kuhn bipartite matching, Hungarian assignment, dominator tree |
| `trees/` | binary lifting / LCA, tree diameter, sum of all pair distances |
| `strings/` | generalized suffix automaton |
| `strings/hashing/` | polynomial rolling hash, substring hash, double hash, double hash with lcp |
| `geometry/` | integer convex hull + point in convex polygon, Minkowski sum, 3d point / segment / triangle distances |

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

## assignments/

Online/offline assignment solutions for `hashing/`, `flow/`, and `shortest_path/`.
