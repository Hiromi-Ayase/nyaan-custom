## CNF SAT solver

`SatSolver(n)` に `add_clause({{v,bool},...})` でリテラルの OR 節を登録する。`(v,true)` は変数 v、false はその否定。

`if_then(v1,a1,v2,a2)` は `v1==a1` なら `v2==a2`、`set_val(v,a)` は固定値制約。`solve()` が真なら `assigns` に充足割当が入る。

一般の CNF を探索するため最悪指数時間。空節はこの実装では検出されず、事前に充足不能として扱う。節の重複リテラル等は呼び出し側で整理し、解いた後に追加入力して再利用する用途は想定しない。

#### 実装・検証

- [実装](../../math/sat-solver.hpp)
- [Verify: sat.cpp](../../tests/unit/math/sat.cpp)
