# ドキュメント索引

`library/nyaan` の各カテゴリにあるヘッダと、その `@docs` が参照する説明の一覧です。対象は 364 ヘッダです。同梱の AtCoder Library (`atcoder/`)、未使用コード (`unused/`)、ユニットテスト (`tests/`) は一覧の対象外です。

各機能の API や利用条件は以下のリンクから参照できます。「実装・検証」欄の **Verify** は、対象を直接呼び出し、素朴な計算・全探索・境界ケースと照合する独立したユニットテストへのリンクです。[CTestでの実行方法](../tests/README.md)も参照してください。

## 利用時の共通事項

- 基本の想定環境は GCC / C++17 です。AVX2 や GCC 拡張を使う実装は各ページの条件も確認してください。
- ヘッダによっては標準ヘッダや共通テンプレートの事前読み込みが必要です。Verifyリンク先のユニットテストの include 順が参考になります。
- FPS の係数は通常、定数項から低次順です。演算には NTT 向けまたは任意法向けのバックエンドを選び、同名の実装を同時に読み込まないでください。
- 区間の端点、添字の基準、失敗時の値は API ごとに異なります。各ページはこのチェックアウトの実装に合わせています。

## カテゴリ

| カテゴリ | ヘッダ数 |
| --- | ---: |
| [data-structure-2d](#data-structure-2d) | 12 |
| [data-structure](#data-structure) | 32 |
| [dp](#dp) | 11 |
| [flow](#flow) | 1 |
| [fps](#fps) | 42 |
| [game](#game) | 3 |
| [geometry](#geometry) | 6 |
| [graph](#graph) | 17 |
| [hashmap](#hashmap) | 4 |
| [internal](#internal) | 5 |
| [lct](#lct) | 10 |
| [marathon](#marathon) | 5 |
| [math-fast](#math-fast) | 8 |
| [math](#math) | 37 |
| [matrix](#matrix) | 14 |
| [misc](#misc) | 14 |
| [modint](#modint) | 10 |
| [modulo](#modulo) | 14 |
| [multiplicative-function](#multiplicative-function) | 11 |
| [ntt](#ntt) | 19 |
| [orderedmap](#orderedmap) | 2 |
| [prime](#prime) | 6 |
| [random_graph](#random_graph) | 3 |
| [rbst](#rbst) | 3 |
| [segment-tree](#segment-tree) | 13 |
| [set-function](#set-function) | 9 |
| [shortest-path](#shortest-path) | 12 |
| [string](#string) | 14 |
| [template](#template) | 6 |
| [tree](#tree) | 21 |

## data-structure-2d

| ヘッダ | ドキュメント |
| --- | --- |
| [2d-binary-indexed-tree.hpp](../data-structure-2d/2d-binary-indexed-tree.hpp) | [二次元 Binary Indexed Tree](data-structure-2d/2d-binary-indexed-tree.md) |
| [2d-cumulative-sum.hpp](../data-structure-2d/2d-cumulative-sum.hpp) | [二次元累積和](data-structure-2d/2d-cumulative-sum.md) |
| [2d-segment-tree.hpp](../data-structure-2d/2d-segment-tree.hpp) | [二次元セグメント木](data-structure-2d/2d-segment-tree.md) |
| [abstract-range-tree.hpp](../data-structure-2d/abstract-range-tree.hpp) | [抽象化した領域木](data-structure-2d/abstract-range-tree.md) |
| [dynamic-binary-indexed-tree-2d.hpp](../data-structure-2d/dynamic-binary-indexed-tree-2d.hpp) | [動的二次元 Fenwick Tree](data-structure-2d/dynamic-binary-indexed-tree-2d.md) |
| [fenwick-tree-on-range-tree.hpp](../data-structure-2d/fenwick-tree-on-range-tree.hpp) | [Fenwick Tree を用いた領域木](data-structure-2d/fenwick-tree-on-range-tree.md) |
| [fenwick-tree-on-wavelet-matrix.hpp](../data-structure-2d/fenwick-tree-on-wavelet-matrix.hpp) | [Wavelet Matrix 上のFenwick Tree](data-structure-2d/fenwick-tree-on-wavelet-matrix.md) |
| [rectangle-add-rectangle-sum.hpp](../data-structure-2d/rectangle-add-rectangle-sum.hpp) | [矩形加算・矩形和（オフライン）](data-structure-2d/rectangle-add-rectangle-sum.md) |
| [rectangle-sum.hpp](../data-structure-2d/rectangle-sum.hpp) | [静的な点集合の矩形和](data-structure-2d/rectangle-sum.md) |
| [segment-tree-on-range-tree.hpp](../data-structure-2d/segment-tree-on-range-tree.hpp) | [Segment Tree を用いた領域木](data-structure-2d/segment-tree-on-range-tree.md) |
| [segment-tree-on-wavelet-matrix.hpp](../data-structure-2d/segment-tree-on-wavelet-matrix.hpp) | [Wavelet Matrix 上のSegment Tree](data-structure-2d/segment-tree-on-wavelet-matrix.md) |
| [wavelet-matrix.hpp](../data-structure-2d/wavelet-matrix.hpp) | [Wavelet Matrix](data-structure-2d/wavelet-matrix.md) |

## data-structure

| ヘッダ | ドキュメント |
| --- | --- |
| [binary-indexed-tree.hpp](../data-structure/binary-indexed-tree.hpp) | [Binary Indexed Tree](data-structure/binary-indexed-tree.md) |
| [binary-trie.hpp](../data-structure/binary-trie.hpp) | [Binary Trie](data-structure/binary-trie.md) |
| [divide-interval.hpp](../data-structure/divide-interval.hpp) | [セグメント木状の区間分割](data-structure/divide-interval.md) |
| [dynamic-binary-indexed-tree.hpp](../data-structure/dynamic-binary-indexed-tree.hpp) | [動的Binary Indexed Tree](data-structure/dynamic-binary-indexed-tree.md) |
| [dynamic-bitset.hpp](../data-structure/dynamic-bitset.hpp) | [動的サイズの BitSet](data-structure/dynamic-bitset.md) |
| [dynamic-union-find.hpp](../data-structure/dynamic-union-find.hpp) | [動的Union Find](data-structure/dynamic-union-find.md) |
| [erasable-priority-queue.hpp](../data-structure/erasable-priority-queue.hpp) | [削除可能な優先度付きキュー](data-structure/erasable-priority-queue.md) |
| [hash-map-variable-length.hpp](../data-structure/hash-map-variable-length.hpp) | [Hash Map](data-structure/hash-map.md) |
| [line-container-2d.hpp](../data-structure/line-container-2d.hpp) | [二次元点集合の線形目的関数](data-structure/line-container-2d.md) |
| [line-container.hpp](../data-structure/line-container.hpp) | [直線の追加と最小値・最大値](data-structure/line-container.md) |
| [parallel-union-find.hpp](../data-structure/parallel-union-find.hpp) | [二つの区間を対応させる Union Find](data-structure/parallel-union-find.md) |
| [persistent-array.hpp](../data-structure/persistent-array.hpp) | [永続配列](data-structure/persistent-array.md) |
| [persistent-queue.hpp](../data-structure/persistent-queue.hpp) | [永続キュー](data-structure/persistent-queue.md) |
| [persistent-union-find.hpp](../data-structure/persistent-union-find.hpp) | [完全永続 Union Find](data-structure/persistent-union-find.md) |
| [radix-heap.hpp](../data-structure/radix-heap.hpp) | [Radix Heap](data-structure/radix-heap.md) |
| [range-sum-range-add-bit.hpp](../data-structure/range-sum-range-add-bit.hpp) | [区間加算・区間和 BIT](data-structure/range-sum-range-add-bit.md) |
| [range-union-find.hpp](../data-structure/range-union-find.hpp) | [連続区間を併合する Union Find](data-structure/range-union-find.md) |
| [rollback-union-find.hpp](../data-structure/rollback-union-find.hpp) | [rollbackつきUnion-Find](data-structure/rollback-union-find.md) |
| [segment-set.hpp](../data-structure/segment-set.hpp) | [互いに重ならない区間の集合](data-structure/segment-set.md) |
| [skew-heap.hpp](../data-structure/skew-heap.hpp) | [Skew Heap](data-structure/skew-heap.md) |
| [slide-window-aggregation-deque.hpp](../data-structure/slide-window-aggregation-deque.hpp) | [両端操作できる Sliding Window Aggregation](data-structure/slide-window-aggregation-deque.md) |
| [slide-window-aggregation.hpp](../data-structure/slide-window-aggregation.hpp) | [Slide Window Aggrigation](data-structure/slide-window-aggregation.md) |
| [sliding-window-minimum.hpp](../data-structure/sliding-window-minimum.hpp) | [スライド窓の最小値・最大値](data-structure/sliding-window-minimum.md) |
| [slope-trick-weighted.hpp](../data-structure/slope-trick-weighted.hpp) | [重み付き Slope Trick（RBST）](data-structure/slope-trick-weighted.md) |
| [slope-trick.hpp](../data-structure/slope-trick.hpp) | [Slope Trick（ヒープ）](data-structure/slope-trick.md) |
| [sparse-table.hpp](../data-structure/sparse-table.hpp) | [静的区間最小値](data-structure/sparse-table.md) |
| [square-root-decomposition.hpp](../data-structure/square-root-decomposition.hpp) | [平方分割](data-structure/sqrt-dec.md) |
| [union-find-enumerate.hpp](../data-structure/union-find-enumerate.hpp) | [要素列挙付き Union Find](data-structure/union-find-enumerate.md) |
| [union-find-with-potential.hpp](../data-structure/union-find-with-potential.hpp) | [ポテンシャル付き Union Find](data-structure/union-find-with-potential.md) |
| [union-find.hpp](../data-structure/union-find.hpp) | [Union-Find Tree(Disjoint Set Union)](data-structure/union-find.md) |
| [van-emde-boas-tree.hpp](../data-structure/van-emde-boas-tree.hpp) | [van Emde Boas 型の整数集合](data-structure/van-emde-boas-tree.md) |
| [w-ary-tree.hpp](../data-structure/w-ary-tree.hpp) | [64 分木による整数集合](data-structure/w-ary-tree.md) |

## dp

| ヘッダ | ドキュメント |
| --- | --- |
| [branch-and-bound.hpp](../dp/branch-and-bound.hpp) | [0-1ナップサック問題の、分枝限定法による解法](dp/branch-and-bound.md) |
| [concave-min-plus-convolution.hpp](../dp/concave-min-plus-convolution.hpp) | [凸性を利用する min-plus / max-plus 畳み込み](dp/concave-min-plus-convolution.md) |
| [golden-section-search.hpp](../dp/golden-section-search.hpp) | [整数区間の黄金分割探索](dp/golden-section-search.md) |
| [inversion-counting.hpp](../dp/inversion-counting.hpp) | [転倒数と隣接交換距離](dp/inversion-counting.md) |
| [knapsack01.hpp](../dp/knapsack01.hpp) | [0-1ナップサック問題](dp/knapsack01.md) |
| [longest-increasing-sequence.hpp](../dp/longest-increasing-sequence.hpp) | [最長増加部分列の復元](dp/longest-increasing-sequence.md) |
| [maximal-rectangle.hpp](../dp/maximal-rectangle.hpp) | [最大長方形](dp/maximal-rectangle.md) |
| [monge-d-edge-shortest-path-enumerate.hpp](../dp/monge-d-edge-shortest-path-enumerate.hpp) | [各辺数に対する Monge 最短路の列挙](dp/monge-d-edge-shortest-path-enumerate.md) |
| [monge-d-edge-shortest-path.hpp](../dp/monge-d-edge-shortest-path.hpp) | [辺数を指定した Monge 最短路](dp/monge-d-edge-shortest-path.md) |
| [monge-shortest-path.hpp](../dp/monge-shortest-path.hpp) | [Monge な DAG の最短路](dp/monge-shortest-path.md) |
| [monotone-minima.hpp](../dp/monotone-minima.hpp) | [Monotone Minima](dp/monotone-minima.md) |

## flow

| ヘッダ | ドキュメント |
| --- | --- |
| [flow-on-bipartite-graph.hpp](../flow/flow-on-bipartite-graph.hpp) | [二部グラフのフロー](flow/flow-on-bipartite-graph.md) |

## fps

| ヘッダ | ドキュメント |
| --- | --- |
| [arbitrary-fps.hpp](../fps/arbitrary-fps.hpp) | [任意の法向け FPS バックエンド](fps/arbitrary-fps.md) |
| [berlekamp-massey.hpp](../fps/berlekamp-massey.hpp) | [線形漸化式の推定](fps/berlekamp-massey.md) |
| [composite-exp.hpp](../fps/composite-exp.hpp) | [指数関数への代入と逆変換](fps/composite-exp.md) |
| [differential-equation.hpp](../fps/differential-equation.hpp) | [常微分方程式](fps/differential-equation.md) |
| [dual-fps.hpp](../fps/dual-fps.hpp) | [周波数領域に保持する多項式](fps/dual-fps.md) |
| [fast-interpolate.hpp](../fps/fast-interpolate.hpp) | [積の木による高速補間・多点評価](fps/fast-interpolate.md) |
| [fast-multieval.hpp](../fps/fast-multieval.hpp) | [NTT を利用した高速多点評価](fps/fast-multieval.md) |
| [fft2d.hpp](../fps/fft2d.hpp) | [2 次元 NTT と畳み込み](fps/fft2d.md) |
| [find-p-recursive.hpp](../fps/find-p-recursive.hpp) | [P-recursiveの高速計算](fps/find-p-recursive.md) |
| [formal-power-series.hpp](../fps/formal-power-series.hpp) | [形式的冪級数](fps/formal-power-series.md) |
| [fps-circular.hpp](../fps/fps-circular.hpp) | [fps-三角関数](fps/fps-circular.md) |
| [fps-composition-fast-old.hpp](../fps/fps-composition-fast-old.hpp) | [行列積を用いた FPS 合成](fps/fps-composition-fast-old.md) |
| [fps-composition-old.hpp](../fps/fps-composition-old.hpp) | [関数の合成](fps/fps-composition-old.md) |
| [fps-composition.hpp](../fps/fps-composition.hpp) | [形式的冪級数の合成](fps/fps-composition.md) |
| [fps-compositional-inverse.hpp](../fps/fps-compositional-inverse.hpp) | [形式的冪級数の逆関数](fps/fps-compositional-inverse.md) |
| [fps-famous-series.hpp](../fps/fps-famous-series.hpp) | [代表的な数列の母関数](fps/fps-famous-series.md) |
| [fps-fraction.hpp](../fps/fps-fraction.hpp) | [多項式の分数](fps/fps-fraction.md) |
| [fps-sqrt.hpp](../fps/fps-sqrt.hpp) | [fps-平方根](fps/fps-sqrt.md) |
| [fps-utility.hpp](../fps/fps-utility.hpp) | [複数の多項式の積](fps/fps-utility.md) |
| [fualhuber.hpp](../fps/fualhuber.hpp) | [多項式で表される数列の累積和](fps/fualhuber.md) |
| [inversion-formula.hpp](../fps/inversion-formula.hpp) | [係数の漸化式による FPS 演算](fps/inversion-formula.md) |
| [kitamasa.hpp](../fps/kitamasa.hpp) | [線形漸化式の高速計算](fps/kitamasa.md) |
| [lagrange-interpolation-point.hpp](../fps/lagrange-interpolation-point.hpp) | [連続する点からの 1 点補間](fps/lagrange-interpolation-point.md) |
| [middle-product.hpp](../fps/middle-product.hpp) | [Middle product](fps/middle-product.md) |
| [mod-pow.hpp](../fps/mod-pow.hpp) | [多項式を法とする累乗](fps/mod-pow.md) |
| [multipoint-evaluation.hpp](../fps/multipoint-evaluation.hpp) | [多項式の多点評価](fps/multipoint-evaluation.md) |
| [multivariate-fps.hpp](../fps/multivariate-fps.hpp) | [打ち切った多変数形式的冪級数](fps/multivariate-fps.md) |
| [newton-method.hpp](../fps/newton-method.hpp) | [形式的冪級数の Newton 法](fps/newton-method.md) |
| [nth-term.hpp](../fps/nth-term.hpp) | [線形回帰数列の高速計算(Berlekamp-Massey/Bostan-Mori)](fps/nth-term.md) |
| [ntt-friendly-fps.hpp](../fps/ntt-friendly-fps.hpp) | [NTT mod専用の形式的冪級数ライブラリ](fps/ntt-friendly-fps.md) |
| [online-fps.hpp](../fps/online-fps.hpp) | [遅延評価する形式的冪級数](fps/online-fps.md) |
| [partial-fraction-decomposition.hpp](../fps/partial-fraction-decomposition.hpp) | [一次式の積を分母とする部分分数分解](fps/partial-fraction-decomposition.md) |
| [pascal-matrix.hpp](../fps/pascal-matrix.hpp) | [Pascal 行列の作用](fps/pascal-matrix.md) |
| [polynomial-gcd.hpp](../fps/polynomial-gcd.hpp) | [多項式GCD](fps/polynomial-gcd.md) |
| [polynomial-interpolation.hpp](../fps/polynomial-interpolation.hpp) | [多項式補間](fps/polynomial-interpolation.md) |
| [pow-enumerate.hpp](../fps/pow-enumerate.hpp) | [多項式の冪から同じ次数の係数を列挙](fps/pow-enumerate.md) |
| [root-finding.hpp](../fps/root-finding.hpp) | [有限体上の多項式の根の列挙](fps/root-finding.md) |
| [sample-point-shift.hpp](../fps/sample-point-shift.hpp) | [連続する評価点のシフト](fps/sample-point-shift.md) |
| [sparse-fps.hpp](../fps/sparse-fps.hpp) | [疎な多項式の FPS 演算](fps/sparse-fps.md) |
| [stirling-matrix.hpp](../fps/stirling-matrix.hpp) | [Stirling 行列の作用](fps/stirling-matrix.md) |
| [sum-of-exponential-times-poly.hpp](../fps/sum-of-exponential-times-poly.hpp) | [$\sum_{i}a^i f(i)$](fps/sum-of-exponential-times-poly.md) |
| [taylor-shift.hpp](../fps/taylor-shift.hpp) | [fps-平行移動](fps/fps-taylor-shift.md) |

## game

| ヘッダ | ドキュメント |
| --- | --- |
| [impartial-game.hpp](../game/impartial-game.hpp) | [不偏ゲームの Grundy 数](game/impartial-game.md) |
| [partisan-game.hpp](../game/partisan-game.hpp) | [数として評価できる非不偏ゲーム](game/partisan-game.md) |
| [surreal-number.hpp](../game/surreal-number.hpp) | [二進有理数による超現実数の表現](game/surreal-number.md) |

## geometry

| ヘッダ | ドキュメント |
| --- | --- |
| [circle.hpp](../geometry/circle.hpp) | [円の位置関係と交点](geometry/circle.md) |
| [geometry-base.hpp](../geometry/geometry-base.hpp) | [平面幾何の基本型](geometry/geometry-base.md) |
| [integer-geometry.hpp](../geometry/integer-geometry.hpp) | [整数平面幾何](geometry/integer-geometry.md) |
| [line.hpp](../geometry/line.hpp) | [直線・射影・凸多角形の切断](geometry/line.md) |
| [polygon.hpp](../geometry/polygon.hpp) | [多角形・凸包](geometry/polygon.md) |
| [segment.hpp](../geometry/segment.hpp) | [線分の交差・距離](geometry/segment.md) |

## graph

| ヘッダ | ドキュメント |
| --- | --- |
| [biconnected-components.hpp](../graph/biconnected-components.hpp) | [二重頂点連結成分分解](graph/biconnected-components.md) |
| [chromatic-number.hpp](../graph/chromatic-number.hpp) | [彩色数](graph/chromatic-number.md) |
| [cycle-detection.hpp](../graph/cycle-detection.hpp) | [閉路の検出](graph/cycle-detection.md) |
| [dimension-expanded-graph.hpp](../graph/dimension-expanded-graph.hpp) | [次元拡張グラフ](graph/dimension-expanded-graph.md) |
| [functional-graph.hpp](../graph/functional-graph.hpp) | [Functional Graph の木への分解](graph/functional-graph-decomposition.md) |
| [graph-template.hpp](../graph/graph-template.hpp) | [グラフテンプレート](graph/graph-template.md) |
| [graph-utility.hpp](../graph/graph-utility.hpp) | [グラフユーティリティ](graph/graph-utility.md) |
| [kruskal.hpp](../graph/kruskal.hpp) | [Kruskal 法](graph/kruskal.md) |
| [lowlink.hpp](../graph/lowlink.hpp) | [Low Link（関節点・橋）](graph/lowlink.md) |
| [max-independent-set.hpp](../graph/max-independent-set.hpp) | [最大独立集合](graph/max-independent-set.md) |
| [minimum-cost-arborescence.hpp](../graph/minimum-cost-arborescence.hpp) | [最小全域有向木](graph/minimum-cost-arborescence.md) |
| [namori.hpp](../graph/namori.hpp) | [Functional Graph(なもりグラフ)](graph/functional-graph.md) |
| [offline-dynamic-connectivity.hpp](../graph/offline-dynamic-connectivity.hpp) | [オフライン動的連結性](graph/offline-dynamic-connectivity.md) |
| [static-graph.hpp](../graph/static-graph.hpp) | [Static Graph](graph/static-graph.md) |
| [strongly-connected-components.hpp](../graph/strongly-connected-components.hpp) | [強連結成分分解](graph/strongly-connected-components.md) |
| [topological-sort.hpp](../graph/topological-sort.hpp) | [トポロジカルソート](graph/topological-sort.md) |
| [two-edge-connected-components.hpp](../graph/two-edge-connected-components.hpp) | [二重辺連結成分分解](graph/two-edge-connected-components.md) |

## hashmap

| ヘッダ | ドキュメント |
| --- | --- |
| [hashmap-base.hpp](../hashmap/hashmap-base.hpp) | [HashMap / HashSet の基底実装](hashmap/hashmap-base.md) |
| [hashmap-unerasable.hpp](../hashmap/hashmap-unerasable.hpp) | [削除なしのハッシュマップ](hashmap/hashmap-unerasable.md) |
| [hashmap.hpp](../hashmap/hashmap.hpp) | [HashMap(連想配列)](hashmap/hashmap.md) |
| [hashset.hpp](../hashmap/hashset.hpp) | [HashSet(集合)](hashmap/hashset.md) |

## internal

| ヘッダ | ドキュメント |
| --- | --- |
| [internal-hash-function.hpp](../internal/internal-hash-function.hpp) | [整数・pair・列のハッシュ関数](internal/internal-hash-function.md) |
| [internal-hash.hpp](../internal/internal-hash.hpp) | [ハッシュ構造体](internal/internal-hash.md) |
| [internal-math.hpp](../internal/internal-math.hpp) | [内部用の整数剰余演算](internal/internal-math.md) |
| [internal-seed.hpp](../internal/internal-seed.hpp) | [内部用の乱数シード](internal/internal-seed.md) |
| [internal-type-traits.hpp](../internal/internal-type-traits.hpp) | [内部用の型判定](internal/internal-type-traits.md) |

## lct

| ヘッダ | ドキュメント |
| --- | --- |
| [lazy-reversible-bbst-base.hpp](../lct/lazy-reversible-bbst-base.hpp) | [遅延・反転対応平衡木の基底](lct/lazy-reversible-bbst-base.md) |
| [link-cut-base.hpp](../lct/link-cut-base.hpp) | [Link/Cut Tree](lct/link-cut-tree.md) |
| [link-cut-tree-lazy.hpp](../lct/link-cut-tree-lazy.hpp) | [パス作用付き Link/Cut Tree](lct/link-cut-tree-lazy.md) |
| [link-cut-tree-subtree-add.hpp](../lct/link-cut-tree-subtree-add.hpp) | [部分木加算・部分木和 Link/Cut Tree](lct/link-cut-tree-subtree-add.md) |
| [link-cut-tree-subtree.hpp](../lct/link-cut-tree-subtree.hpp) | [部分木集約付き Link/Cut Tree](lct/link-cut-tree-subtree.md) |
| [link-cut-tree.hpp](../lct/link-cut-tree.hpp) | [Link/Cut Tree](lct/link-cut-tree.md) |
| [reversible-bbst-base.hpp](../lct/reversible-bbst-base.hpp) | [反転可能な平衡二分木の基底](lct/reversible-bbst-base.md) |
| [splay-base.hpp](../lct/splay-base.hpp) | [Splay Tree の基底](lct/splay-base.md) |
| [splay-lazy-reversible.hpp](../lct/splay-lazy-reversible.hpp) | [遅延・反転対応 Splay Tree](lct/splay-lazy-reversible.md) |
| [splay-reversible.hpp](../lct/splay-reversible.hpp) | [反転可能 Splay Tree](lct/splay-reversible.md) |

## marathon

| ヘッダ | ドキュメント |
| --- | --- |
| [log_table.hpp](../marathon/log_table.hpp) | [対数乱数の事前計算](marathon/log_table.md) |
| [multi-armed-bandit.hpp](../marathon/multi-armed-bandit.hpp) | [多腕バンディットによる選択](marathon/multi-armed-bandit.md) |
| [sa-manager.hpp](../marathon/sa-manager.hpp) | [焼きなまし法](marathon/sa-manager.md) |
| [simulated-annealing.hpp](../marathon/simulated-annealing.hpp) | [テンプレート](marathon/simulated-annealing.md) |
| [top-k.hpp](../marathon/top-k.hpp) | [ハッシュ重複を除いた上位 K 件](marathon/top-k.md) |

## math-fast

| ヘッダ | ドキュメント |
| --- | --- |
| [binary-search.hpp](../math-fast/binary-search.hpp) | [配列上の二分探索](math-fast/binary-search.md) |
| [gcd.hpp](../math-fast/gcd.hpp) | [二進 GCD](math-fast/gcd.md) |
| [inv-o1.hpp](../math-fast/inv-o1.hpp) | [前計算による定数時間の逆元](math-fast/inv-o1.md) |
| [inv.hpp](../math-fast/inv.hpp) | [固定法での逆元の高速計算](math-fast/inv.md) |
| [mat-prod-strassen.hpp](../math-fast/mat-prod-strassen.hpp) | [AVX2 を用いた固定サイズ行列積](math-fast/mat-prod-strassen.md) |
| [radix-sort.hpp](../math-fast/radix-sort.hpp) | [整数の基数ソート](math-fast/radix-sort.md) |
| [subset-convolution.hpp](../math-fast/subset-convolution.hpp) | [SIMD による部分集合畳み込み](math-fast/subset-convolution.md) |
| [vectorize-modint.hpp](../math-fast/vectorize-modint.hpp) | [8 要素をまとめた Montgomery 演算](math-fast/vectorize-modint.md) |

## math

| ヘッダ | ドキュメント |
| --- | --- |
| [affine-transformation.hpp](../math/affine-transformation.hpp) | [一次関数の合成](math/affine-transformation.md) |
| [bigint-all.hpp](../math/bigint-all.hpp) | [多倍長整数・有理数の一括 include](math/bigint-all.md) |
| [bigint-binary.hpp](../math/bigint-binary.hpp) | [二進表現の多倍長整数](math/bigint-binary.md) |
| [bigint-garner.hpp](../math/bigint-garner.hpp) | [多倍長整数での中国剰余定理](math/bigint-garner.md) |
| [bigint-gcd.hpp](../math/bigint-gcd.hpp) | [多倍長整数の GCD・LCM](math/bigint-gcd.md) |
| [bigint-rational.hpp](../math/bigint-rational.hpp) | [多倍長有理数](math/bigint-rational.md) |
| [bigint-to-hex.hpp](../math/bigint-to-hex.hpp) | [多倍長整数の十六進変換](math/bigint-to-hex.md) |
| [bigint.hpp](../math/bigint.hpp) | [多倍長整数](math/bigint.md) |
| [constexpr-primitive-root.hpp](../math/constexpr-primitive-root.hpp) | [constexpr 原始根探索](math/constexpr-primitive-root.md) |
| [elementary-function.hpp](../math/elementary-function.hpp) | [基本整数関数](math/elementary-function.md) |
| [enumerate-convex.hpp](../math/enumerate-convex.hpp) | [判定関数から下側凸包を列挙](math/enumerate-convex.md) |
| [enumerate-quotient.hpp](../math/enumerate-quotient.hpp) | [整数除算の商をまとめて列挙](math/enumerate-quotient.md) |
| [f2.hpp](../math/f2.hpp) | [二元体の多項式 GCD・行列消去](math/f2.md) |
| [float-binomial.hpp](../math/float-binomial.hpp) | [階乗・二項係数の対数](math/float-binomial.md) |
| [floor-sum.hpp](../math/floor-sum.hpp) | [床関数の総和](math/floor-sum.md) |
| [garner.hpp](../math/garner.hpp) | [整数型の中国剰余定理](math/garner.md) |
| [gaussian-integer.hpp](../math/gaussian-integer.hpp) | [Gauss 整数](math/gaussian-integer.md) |
| [gray-code.hpp](../math/gray-code.hpp) | [Gray code の列挙](math/gray-code.md) |
| [grundy-number.hpp](../math/grundy-number.hpp) | [DAG 上の Grundy 数](math/grundy-number.md) |
| [inv-mod.hpp](../math/inv-mod.hpp) | [整数の逆元](math/inv-mod.md) |
| [isqrt.hpp](../math/isqrt.hpp) | [整数平方根](math/isqrt.md) |
| [kth-root-integral.hpp](../math/kth-root-integral.hpp) | [$\mathrm{floor}(a^{\frac{1}{k}})$](math/kth-root-integral.md) |
| [nimber-to-field.hpp](../math/nimber-to-field.hpp) | [Nimber と多項式基底の変換](math/nimber-to-field.md) |
| [nimber.hpp](../math/nimber.hpp) | [Nim Product](math/nimber.md) |
| [primitive-root-ll.hpp](../math/primitive-root-ll.hpp) | [64 bit 素数の原始根](math/primitive-root-ll.md) |
| [rational-binomial.hpp](../math/rational-binomial.hpp) | [有理数による組合せ計算](math/rational-binomial.md) |
| [rational-fps.hpp](../math/rational-fps.hpp) | [有理数係数の形式的冪級数](math/rational-fps.md) |
| [rational.hpp](../math/rational.hpp) | [有理数](math/rational.md) |
| [sat-solver.hpp](../math/sat-solver.hpp) | [CNF SAT solver](math/sat-solver.md) |
| [semiring-linear-recursive.hpp](../math/semiring-linear-recursive.hpp) | [半環上の線形漸化式](math/semiring-linear-recursive.md) |
| [semiring.hpp](../math/semiring.hpp) | [半環ライブラリ](math/semiring.md) |
| [stern-brocot-tree-binary-search.hpp](../math/stern-brocot-tree-binary-search.hpp) | [有理数上の二分探索](math/stern-brocot-tree-binary-search.md) |
| [stern-brocot-tree.hpp](../math/stern-brocot-tree.hpp) | [Stern–Brocot 木](math/stern-brocot-tree.md) |
| [sweep-restore.hpp](../math/sweep-restore.hpp) | [復元付き XOR 線形基底](math/sweep-restore.md) |
| [sweep.hpp](../math/sweep.hpp) | [XOR 線形基底](math/sweep.md) |
| [two-sat.hpp](../math/two-sat.hpp) | [2-SAT](math/two-sat.md) |
| [two-square.hpp](../math/two-square.hpp) | [二平方和の整数解](math/two-square.md) |

## matrix

| ヘッダ | ドキュメント |
| --- | --- |
| [black-box-linear-algebra.hpp](../matrix/black-box-linear-algebra.hpp) | [行列ベクトル積を用いる線形代数](matrix/black-box-linear-algebra.md) |
| [characteristric-polynomial.hpp](../matrix/characteristric-polynomial.hpp) | [行列の特性多項式](matrix/characteristric-polynomial.md) |
| [determinant-arbitrary-mod.hpp](../matrix/determinant-arbitrary-mod.hpp) | [任意の法での行列式](matrix/determinant-arbitrary-mod.md) |
| [f2-matrix.hpp](../matrix/f2-matrix.hpp) | [GF(2) と Boolean 行列](matrix/f2-matrix.md) |
| [gauss-elimination.hpp](../matrix/gauss-elimination.hpp) | [Gauss の消去法](matrix/gauss-elimination.md) |
| [hafnian.hpp](../matrix/hafnian.hpp) | [Hafnian](matrix/hafnian.md) |
| [inverse-matrix.hpp](../matrix/inverse-matrix.hpp) | [逆行列](matrix/inverse-matrix.md) |
| [linear-equation-hashmap.hpp](../matrix/linear-equation-hashmap.hpp) | [疎な連立一次方程式](matrix/linear-equation-hashmap.md) |
| [linear-equation.hpp](../matrix/linear-equation.hpp) | [連立一次方程式の解空間](matrix/linear-equation.md) |
| [matrix-fast.hpp](../matrix/matrix-fast.hpp) | [固定サイズの行列](matrix/matrix-fast.md) |
| [matrix-tree.hpp](../matrix/matrix-tree.hpp) | [行列木定理](matrix/matrix-tree.md) |
| [matrix.hpp](../matrix/matrix.hpp) | [動的サイズの行列](matrix/matrix.md) |
| [polynomial-matrix-determinant.hpp](../matrix/polynomial-matrix-determinant.hpp) | [多項式行列の行列式](matrix/polynomial-matrix-determinant.md) |
| [polynomial-matrix-prefix-prod.hpp](../matrix/polynomial-matrix-prefix-prod.hpp) | [多項式行列の連続積](matrix/polynomial-matrix-prefix-prod.md) |

## misc

| ヘッダ | ドキュメント |
| --- | --- |
| [all.hpp](../misc/all.hpp) | [入出力・乱数・タイマーの一括 include](misc/all.md) |
| [base64.hpp](../misc/base64.hpp) | [ソース埋め込み用の整数列符号化](misc/base64.md) |
| [bitset-find-prev.hpp](../misc/bitset-find-prev.hpp) | [bitset の後方ビット探索](misc/bitset-find-prev.md) |
| [compress.hpp](../misc/compress.hpp) | [座標圧縮](misc/compress.md) |
| [doubling.hpp](../misc/doubling.hpp) | [Binary Lifting(ダブリング)](misc/doubling.md) |
| [fastio.hpp](../misc/fastio.hpp) | [バッファ付き高速入出力](misc/fastio.md) |
| [int_div.hpp](../misc/int_div.hpp) | [符号付き整数の除算と丸め](misc/int_div.md) |
| [interval-union.hpp](../misc/interval-union.hpp) | [半開区間の和集合](misc/interval-union.md) |
| [mo-fast.hpp](../misc/mo-fast.hpp) | [処理順を調整した Mo 法](misc/mo-fast.md) |
| [mo.hpp](../misc/mo.hpp) | [Mo's algorithm](misc/mo.md) |
| [rng.hpp](../misc/rng.hpp) | [乱数生成補助](misc/rng.md) |
| [simd.hpp](../misc/simd.hpp) | [SIMD 演算マクロ](misc/simd.md) |
| [timer.hpp](../misc/timer.hpp) | [経過時間の計測](misc/timer.md) |
| [vector-pool.hpp](../misc/vector-pool.hpp) | [添字によるオブジェクトプール](misc/vector-pool.md) |

## modint

| ヘッダ | ドキュメント |
| --- | --- |
| [adjunction-modint.hpp](../modint/adjunction-modint.hpp) | [平方根を添加した係数型](modint/adjunction-modint.md) |
| [arbitrary-modint.hpp](../modint/arbitrary-modint.hpp) | [実行時に法を指定する modint](modint/arbitrary-modint.md) |
| [arbitrary-montgomery-modint.hpp](../modint/arbitrary-montgomery-modint.hpp) | [実行時法の Montgomery modint](modint/arbitrary-montgomery-modint.md) |
| [barrett-reduction.hpp](../modint/barrett-reduction.hpp) | [Barrett reduction](modint/barrett-reduction.md) |
| [modint-2-61m1.hpp](../modint/modint-2-61m1.hpp) | [法 2^61−1 の modint](modint/modint-2-61m1.md) |
| [modint-cpp11.hpp](../modint/modint-cpp11.hpp) | [998244353 の C++11 用 modint](modint/modint-cpp11.md) |
| [modint.hpp](../modint/modint.hpp) | [固定法の modint](modint/modint.md) |
| [montgomery-modint.hpp](../modint/montgomery-modint.hpp) | [Montgomery modint（固定法）](modint/montgomery-modint.md) |
| [simd-montgomery.hpp](../modint/simd-montgomery.hpp) | [SIMD Montgomery 演算](modint/simd-montgomery.md) |
| [vectorize-modint.hpp](../modint/vectorize-modint.hpp) | [八要素並列の modint](modint/vectorize-modint.md) |

## modulo

| ヘッダ | ドキュメント |
| --- | --- |
| [arbitrary-mod-binomial-large.hpp](../modulo/arbitrary-mod-binomial-large.hpp) | [大きい法に対応した二項係数](modulo/arbitrary-mod-binomial-large.md) |
| [arbitrary-mod-binomial.hpp](../modulo/arbitrary-mod-binomial.hpp) | [任意mod二項係数](modulo/arbitrary-mod-binomial.md) |
| [binomial-table.hpp](../modulo/binomial-table.hpp) | [Pascal の三角形](modulo/binomial-table.md) |
| [binomial.hpp](../modulo/binomial.hpp) | [階乗表による二項係数](modulo/binomial.md) |
| [factorial.hpp](../modulo/factorial.hpp) | [階乗 $\mod p$](modulo/factorial.md) |
| [fastpow.hpp](../modulo/fastpow.hpp) | [固定底の累乗表](modulo/fastpow.md) |
| [gauss-elimination-fast.hpp](../modulo/gauss-elimination-fast.hpp) | [AVX2 による Gauss 消去法](modulo/gauss-elimination-fast.md) |
| [mod-kth-root.hpp](../modulo/mod-kth-root.hpp) | [kth root](modulo/mod-kth-root.md) |
| [mod-log.hpp](../modulo/mod-log.hpp) | [離散対数](modulo/mod-log.md) |
| [mod-sqrt.hpp](../modulo/mod-sqrt.hpp) | [mod sqrt(Tonelli-Shanks algorithm)](modulo/mod-sqrt.md) |
| [multipoint-binomial-sum.hpp](../modulo/multipoint-binomial-sum.hpp) | [二項係数の部分和の多点評価](modulo/multipoint-binomial-sum.md) |
| [quadratic-equation.hpp](../modulo/quadratic-equation.hpp) | [有限体上の二次方程式](modulo/quadratic-equation.md) |
| [strassen.hpp](../modulo/strassen.hpp) | [Montgomery modint の高速行列積](modulo/strassen.md) |
| [tetration.hpp](../modulo/tetration.hpp) | [Tetration](modulo/tetration.md) |

## multiplicative-function

| ヘッダ | ドキュメント |
| --- | --- |
| [count-square-free.hpp](../multiplicative-function/count-square-free.hpp) | [平方因子を持たない整数の個数](multiplicative-function/count-square-free.md) |
| [divisor-multiple-transform.hpp](../multiplicative-function/divisor-multiple-transform.hpp) | [倍数変換/約数変換](multiplicative-function/divisor-multiple-transform.md) |
| [enamurate-multiplicative-function.hpp](../multiplicative-function/enamurate-multiplicative-function.hpp) | [乗法的関数の値の列挙](multiplicative-function/enamurate-multiplicative-function.md) |
| [enumerate-sum-of-multiplicative-function.hpp](../multiplicative-function/enumerate-sum-of-multiplicative-function.hpp) | [Dirichlet 畳み込みからの累積和列挙](multiplicative-function/enumerate-sum-of-multiplicative-function.md) |
| [gcd-convolution.hpp](../multiplicative-function/gcd-convolution.hpp) | [GCD 畳み込み](multiplicative-function/gcd-convolution.md) |
| [mf-famous-series.hpp](../multiplicative-function/mf-famous-series.hpp) | [有名な乗法的関数](multiplicative-function/mf-famous-series.md) |
| [prime-counting-faster.hpp](../multiplicative-function/prime-counting-faster.hpp) | [素数の個数$\pi(N)$の高速計算](multiplicative-function/prime-counting.md) |
| [prime-counting-o2d3.hpp](../multiplicative-function/prime-counting-o2d3.hpp) | [prime-counting-o2d3](multiplicative-function/prime-counting-o2d3.md) |
| [prime-counting.hpp](../multiplicative-function/prime-counting.hpp) | [素数の個数$\pi(N)$の高速計算](multiplicative-function/prime-counting.md) |
| [sum-of-multiplicative-function.hpp](../multiplicative-function/sum-of-multiplicative-function.hpp) | [乗法的関数の和](multiplicative-function/sum-of-multiplicative-function.md) |
| [sum-of-totient.hpp](../multiplicative-function/sum-of-totient.hpp) | [Euler の φ 関数の累積和](multiplicative-function/sum-of-totient.md) |

## ntt

| ヘッダ | ドキュメント |
| --- | --- |
| [arbitrary-ntt-mod18446744069414584321.hpp](../ntt/arbitrary-ntt-mod18446744069414584321.hpp) | [法 2^64 − 2^32 + 1 の NTT](ntt/arbitrary-ntt-mod18446744069414584321.md) |
| [arbitrary-ntt.hpp](../ntt/arbitrary-ntt.hpp) | [3 つの NTT による任意法の畳み込み](ntt/arbitrary-ntt.md) |
| [chirp-z.hpp](../ntt/chirp-z.hpp) | [等比数列上の多項式評価](ntt/chirp-z.md) |
| [complex-fft.hpp](../ntt/complex-fft.hpp) | [複素数 FFT による畳み込み](ntt/complex-fft.md) |
| [convolution-large.hpp](../ntt/convolution-large.hpp) | [NTT の最大長を超える畳み込み](ntt/convolution-large.md) |
| [cooley-tukey-ntt.hpp](../ntt/cooley-tukey-ntt.hpp) | [任意長の数論変換](ntt/cooley-tukey-ntt.md) |
| [karatsuba.hpp](../ntt/karatsuba.hpp) | [Karatsuba 法の多項式積](ntt/karatsuba.md) |
| [multidimensional-ntt.hpp](../ntt/multidimensional-ntt.hpp) | [多次元 Fourier 変換](ntt/multidimensional-ntt.md) |
| [multiplicative-convolution-mod-p.hpp](../ntt/multiplicative-convolution-mod-p.hpp) | [添字の積に関する畳み込み](ntt/multiplicative-convolution-mod-p.md) |
| [multivariate-circular-convolution.hpp](../ntt/multivariate-circular-convolution.hpp) | [多変数の巡回畳み込み](ntt/multivariate-circular-convolution.md) |
| [multivariate-multiplication.hpp](../ntt/multivariate-multiplication.hpp) | [Multivariate Multiplication](ntt/multivariate-multiplication.md) |
| [ntt-64bit.hpp](../ntt/ntt-64bit.hpp) | [64 bit の法での数論変換](ntt/ntt-64bit.md) |
| [ntt-avx2.hpp](../ntt/ntt-avx2.hpp) | [AVX2 による数論変換](ntt/ntt-avx2.md) |
| [ntt-cpp11.hpp](../ntt/ntt-cpp11.hpp) | [C++11 向けの数論変換](ntt/ntt-cpp11.md) |
| [ntt-sse42.hpp](../ntt/ntt-sse42.hpp) | [SSE による数論変換](ntt/ntt-sse42.md) |
| [ntt.hpp](../ntt/ntt.hpp) | [2 冪長の数論変換](ntt/ntt.md) |
| [rader-ntt.hpp](../ntt/rader-ntt.hpp) | [素数長の Rader 変換](ntt/rader-ntt.md) |
| [relaxed-convolution.hpp](../ntt/relaxed-convolution.hpp) | [オンライン畳み込み](ntt/relaxed-convolution.md) |
| [schoenhage-strassen-radix2.hpp](../ntt/schoenhage-strassen-radix2.hpp) | [Schönhage–Strassen 型の多項式積](ntt/schoenhage-strassen-radix2.md) |

## orderedmap

| ヘッダ | ドキュメント |
| --- | --- |
| [orderedmap-base.hpp](../orderedmap/orderedmap-base.hpp) | [順序付き map の RBST 基底](orderedmap/orderedmap-base.md) |
| [orderedmap.hpp](../orderedmap/orderedmap.hpp) | [順序統計付き連想配列](orderedmap/orderedmap.md) |

## prime

| ヘッダ | ドキュメント |
| --- | --- |
| [factor-enumerate.hpp](../prime/factor-enumerate.hpp) | [最小素因数の列挙](prime/factor-enumerate.md) |
| [fast-factorize.hpp](../prime/fast-factorize.hpp) | [高速な素因数分解](prime/fast-factorize.md) |
| [miller-rabin.hpp](../prime/miller-rabin.hpp) | [64 bit 整数の素数判定](prime/miller-rabin.md) |
| [osak.hpp](../prime/osak.hpp) | [最小素因数表による素因数分解・約数列挙](prime/osak.md) |
| [prime-enumerate.hpp](../prime/prime-enumerate.hpp) | [素数の列挙](prime/prime-enumerate.md) |
| [prime-sieve.hpp](../prime/prime-sieve.hpp) | [素数判定表](prime/prime-sieve.md) |

## random_graph

| ヘッダ | ドキュメント |
| --- | --- |
| [gen.hpp](../random_graph/gen.hpp) | [無向グラフのテスト生成](random_graph/gen.md) |
| [graph.hpp](../random_graph/graph.hpp) | [生成用グラフの保存・出力](random_graph/graph.md) |
| [random.hpp](../random_graph/random.hpp) | [テスト生成用の乱数生成器](random_graph/random.md) |

## rbst

| ヘッダ | ドキュメント |
| --- | --- |
| [lazy-reversible-rbst.hpp](../rbst/lazy-reversible-rbst.hpp) | [遅延伝搬反転可能乱択平衡二分木](rbst/lazy-reversible-rbst.md) |
| [rbst-base.hpp](../rbst/rbst-base.hpp) | [乱択平衡二分木の基底](rbst/rbst-base.md) |
| [treap.hpp](../rbst/treap.hpp) | [遅延・反転対応 Treap](rbst/treap.md) |

## segment-tree

| ヘッダ | ドキュメント |
| --- | --- |
| [dynamic-li-chao-tree.hpp](../segment-tree/dynamic-li-chao-tree.hpp) | [動的 Li Chao Tree](segment-tree/dynamic-li-chao-tree.md) |
| [dynamic-segment-tree.hpp](../segment-tree/dynamic-segment-tree.hpp) | [動的 Segment Tree](segment-tree/dynamic-segment-tree.md) |
| [lazy-segment-tree-utility.hpp](../segment-tree/lazy-segment-tree-utility.hpp) | [使用頻度の高い遅延セグメント木](segment-tree/lazy-segment-tree-utility.md) |
| [li-chao-tree-abstruct.hpp](../segment-tree/li-chao-tree-abstruct.hpp) | [Li Chao Tree（関数型・区間取得対応）](segment-tree/li-chao-tree-abstruct.md) |
| [li-chao-tree.hpp](../segment-tree/li-chao-tree.hpp) | [Li Chao Tree（座標圧縮）](segment-tree/li-chao-tree.md) |
| [persistent-segment-tree.hpp](../segment-tree/persistent-segment-tree.hpp) | [永続セグメント木(Persistent Segment Tree)](segment-tree/persistent-segtree.md) |
| [range-weighted-add-range-sum-lazyseg.hpp](../segment-tree/range-weighted-add-range-sum-lazyseg.hpp) | [重み付き区間加算・区間和](segment-tree/range-weighted-add-range-sum-lazyseg.md) |
| [rbst-segment-tree.hpp](../segment-tree/rbst-segment-tree.hpp) | [RBST による動的 Segment Tree](segment-tree/rbst-segment-tree.md) |
| [rbst-sequence.hpp](../segment-tree/rbst-sequence.hpp) | [RBST による可変長列](segment-tree/rbst-sequence.md) |
| [segment-tree-beats-abstract.hpp](../segment-tree/segment-tree-beats-abstract.hpp) | [抽象化Segment Tree Beats](segment-tree/segment-tree-beats-abstract.md) |
| [segment-tree-beats.hpp](../segment-tree/segment-tree-beats.hpp) | [Range Chmin Chmax Add Update Range Min Max Sum Segment Tree Beats](segment-tree/segment-tree-beats.md) |
| [segment-tree-max-of-interval.hpp](../segment-tree/segment-tree-max-of-interval.hpp) | [最大・最小連続部分列和のモノイド](segment-tree/segment-tree-max-of-interval.md) |
| [segment-tree-utility.hpp](../segment-tree/segment-tree-utility.hpp) | [使用頻度の高いセグメント木](segment-tree/segment-tree-utility.md) |

## set-function

| ヘッダ | ドキュメント |
| --- | --- |
| [and-convolution.hpp](../set-function/and-convolution.hpp) | [AND 畳み込み](set-function/and-convolution.md) |
| [enumerate-set.hpp](../set-function/enumerate-set.hpp) | [下位集合・上位集合の列挙](set-function/enumerate-set.md) |
| [exp-of-set-power-series.hpp](../set-function/exp-of-set-power-series.hpp) | [集合冪級数の指数関数](set-function/exp-of-set-power-series.md) |
| [or-convolution.hpp](../set-function/or-convolution.hpp) | [OR 畳み込み](set-function/or-convolution.md) |
| [polynomial-composite-set-power-series.hpp](../set-function/polynomial-composite-set-power-series.hpp) | [多項式と集合冪級数の合成](set-function/polynomial-composite-set-power-series.md) |
| [subset-convolution.hpp](../set-function/subset-convolution.hpp) | [Subset Convolution](set-function/subset-convolution.md) |
| [walsh-hadamard-transform.hpp](../set-function/walsh-hadamard-transform.hpp) | [Walsh–Hadamard 変換](set-function/walsh-hadamard-transform.md) |
| [xor-convolution.hpp](../set-function/xor-convolution.hpp) | [XOR 畳み込み](set-function/xor-convolution.md) |
| [zeta-mobius-transform.hpp](../set-function/zeta-mobius-transform.hpp) | [部分集合・上位集合のゼータ／Möbius 変換](set-function/zeta-mobius-transform.md) |

## shortest-path

| ヘッダ | ドキュメント |
| --- | --- |
| [bellman-ford.hpp](../shortest-path/bellman-ford.hpp) | [Bellman–Ford 法](shortest-path/bellman-ford.md) |
| [bfs-restore.hpp](../shortest-path/bfs-restore.hpp) | [幅優先探索（経路復元用の親付き）](shortest-path/bfs-restore.md) |
| [bfs01.hpp](../shortest-path/bfs01.hpp) | [0-1 BFS](shortest-path/bfs01.md) |
| [dijkstra-abstruct.hpp](../shortest-path/dijkstra-abstruct.hpp) | [状態遷移を関数で与える Dijkstra 法](shortest-path/dijkstra-abstruct.md) |
| [dijkstra-fast.hpp](../shortest-path/dijkstra-fast.hpp) | [定数倍高速化ダイクストラ法](shortest-path/dijkstra-fast.md) |
| [dijkstra-radix-heap.hpp](../shortest-path/dijkstra-radix-heap.hpp) | [ダイクストラ法(Radix Heap)](shortest-path/dijkstra-radix-heap.md) |
| [dijkstra-skew-heap.hpp](../shortest-path/dijkstra-skew-heap.hpp) | [ダイクストラ法(Skew Heap)](shortest-path/dijkstra-skew-heap.md) |
| [dijkstra-with-restore.hpp](../shortest-path/dijkstra-with-restore.hpp) | [Dijkstra 法（経路復元用の親付き）](shortest-path/dijkstra-with-restore.md) |
| [dijkstra.hpp](../shortest-path/dijkstra.hpp) | [ダイクストラ法](shortest-path/dijkstra.md) |
| [dual-of-shortest-path.hpp](../shortest-path/dual-of-shortest-path.hpp) | [差分制約（最短路問題の双対）](shortest-path/dual-of-shortest-path.md) |
| [restore-shortest-path.hpp](../shortest-path/restore-shortest-path.hpp) | [距離配列からの最短路復元](shortest-path/restore-shortest-path.md) |
| [warshall-floyd.hpp](../shortest-path/warshall-floyd.hpp) | [Warshall–Floyd 法](shortest-path/warshall-floyd.md) |

## string

| ヘッダ | ドキュメント |
| --- | --- |
| [aho-corasick.hpp](../string/aho-corasick.hpp) | [Aho–Corasick 法](string/aho-corasick.md) |
| [manacher.hpp](../string/manacher.hpp) | [Manacher 法と回文列挙](string/manacher.md) |
| [number-of-subsequences.hpp](../string/number-of-subsequences.hpp) | [異なる非空部分列の個数](string/number-of-subsequences.md) |
| [rolling-hash-2d.hpp](../string/rolling-hash-2d.hpp) | [二次元Rolling Hash](string/rolling-hash-2d.md) |
| [rolling-hash-on-segment-tree.hpp](../string/rolling-hash-on-segment-tree.hpp) | [一点更新できる Rolling Hash](string/rolling-hash-on-segment-tree.md) |
| [rolling-hash.hpp](../string/rolling-hash.hpp) | [Rolling Hash](string/rolling-hash.md) |
| [run-enumerate.hpp](../string/run-enumerate.hpp) | [Run（極大周期区間）の列挙](string/run-enumerate.md) |
| [run-length-encoding.hpp](../string/run-length-encoding.hpp) | [連長圧縮](string/run-length-encoding.md) |
| [string-search.hpp](../string/string-search.hpp) | [接尾辞・部分列の LCP と辞書順比較](string/string-search.md) |
| [suffix-array.hpp](../string/suffix-array.hpp) | [Suffix Array と LCP（旧実装）](string/suffix-array.md) |
| [suffix-automaton.hpp](../string/suffix-automaton.hpp) | [Suffix Automaton](string/suffix-automaton.md) |
| [trie.hpp](../string/trie.hpp) | [Trie](string/trie.md) |
| [wildcard-pattern-matching.hpp](../string/wildcard-pattern-matching.hpp) | [ワイルドカード付きパターン照合](string/wildcard-pattern-matching.md) |
| [z-algorithm.hpp](../string/z-algorithm.hpp) | [Z algorithm](string/z-algorithm.md) |

## template

| ヘッダ | ドキュメント |
| --- | --- |
| [bitop.hpp](../template/bitop.hpp) | [ビット演算補助](template/bitop.md) |
| [debug.hpp](../template/debug.hpp) | [デバッグ表示](template/debug.md) |
| [inout.hpp](../template/inout.hpp) | [iostream 入出力補助](template/inout.md) |
| [macro.hpp](../template/macro.hpp) | [ループ・入力マクロ](template/macro.md) |
| [template.hpp](../template/template.hpp) | [競技プログラミング用テンプレート](template/template.md) |
| [util.hpp](../template/util.hpp) | [型・配列・累乗の補助関数](template/util.md) |

## tree

| ヘッダ | ドキュメント |
| --- | --- |
| [auxiliary-tree.hpp](../tree/auxiliary-tree.hpp) | [Auxiliary Tree（Virtual Tree）](tree/auxiliary-tree.md) |
| [block-cut-tree.hpp](../tree/block-cut-tree.hpp) | [Block-Cut Tree](tree/block-cut-tree.md) |
| [cartesian-tree.hpp](../tree/cartesian-tree.hpp) | [Cartesian Tree](tree/cartesian-tree.md) |
| [centroid-decomposition.hpp](../tree/centroid-decomposition.hpp) | [重心分解](tree/centroid-decomposition.md) |
| [centroid.hpp](../tree/centroid.hpp) | [木の重心](tree/centroid.md) |
| [convert-tree.hpp](../tree/convert-tree.hpp) | [根付き木・逆辺への変換](tree/convert-tree.md) |
| [dsu-on-tree.hpp](../tree/dsu-on-tree.hpp) | [DSU on Tree](tree/dsu-on-tree.md) |
| [dynamic-diameter.hpp](../tree/dynamic-diameter.hpp) | [辺重み更新付きの木の直径](tree/dynamic-diameter.md) |
| [dynamic-rerooting.hpp](../tree/dynamic-rerooting.hpp) | [動的な木の全方位 DP](tree/dynamic-rerooting.md) |
| [euler-tour.hpp](../tree/euler-tour.hpp) | [Euler Tour](tree/euler-tour.md) |
| [frequency-table-of-tree-distance.hpp](../tree/frequency-table-of-tree-distance.hpp) | [頂点間の距離の度数分布](tree/frequency-table-of-tree-distance.md) |
| [heavy-light-decomposition.hpp](../tree/heavy-light-decomposition.hpp) | [Heavy Light Decomposition(重軽分解)](tree/heavy-light-decomposition.md) |
| [inclusion-tree.hpp](../tree/inclusion-tree.hpp) | [区間の包含関係の木](tree/inclusion-tree.md) |
| [process-of-merging-tree.hpp](../tree/process-of-merging-tree.hpp) | [併合過程を表す木](tree/process-of-merging-tree.md) |
| [pruefer-code.hpp](../tree/pruefer-code.hpp) | [Prüfer 列からの木の復元](tree/pruefer-code.md) |
| [rerooting.hpp](../tree/rerooting.hpp) | [全方位木DP](tree/rerooting.md) |
| [rooted-tree-hash.hpp](../tree/rooted-tree-hash.hpp) | [根付き木のハッシュ](tree/rooted-tree-hash.md) |
| [static-top-tree-edge-based.hpp](../tree/static-top-tree-edge-based.hpp) | [辺を基礎とする Static Top Tree](tree/static-top-tree-edge-based.md) |
| [static-top-tree-vertex-based.hpp](../tree/static-top-tree-vertex-based.hpp) | [頂点を基礎とする Static Top Tree](tree/static-top-tree-vertex-based.md) |
| [tree-hash.hpp](../tree/tree-hash.hpp) | [根のない木のハッシュ](tree/tree-hash.md) |
| [tree-query.hpp](../tree/tree-query.hpp) | [木に対する一般的なクエリ](tree/tree-query.md) |
