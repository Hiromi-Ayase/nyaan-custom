## 多倍長整数

`bigint`（`MultiPrecisionInteger`）は符号と 10^9 進の桁配列で整数を保持する。整数型または十進文字列から構築し、加減乗除・剰余・比較・入出力を提供する。

`divmod(a,b)` は商と余り。商は 0 方向への丸め、余りの符号は被除数と同じ。零除算は禁止。`to_string`, `to_ll`, `to_i128`, `to_ld`, `dfp()`（仮数・十進指数）で変換できる。固定幅への変換には範囲検査がない。

零は `neg=false,dat={}` が正規形。`-0` の入力や内部配列の直接変更を避ける。加減算は桁数に比例、乗算は小規模で素朴法、大規模で畳み込み、除算は Newton 法へ切り替える。

#### 実装・検証

- [実装](../../math/bigint.hpp)
- [Verify: bigint.cpp](../../tests/unit/math/bigint.cpp)
