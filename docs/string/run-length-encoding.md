## 連長圧縮

`RunLengthEncoding(s)` は連続する同値要素を `(値, 個数)` にまとめ、元の順に返す。文字列・配列など `value_type`, `size`, `operator[]` を持つコンテナを渡す。

空入力には空配列を返す。時間は $O(n)$、出力領域は連続区間数に比例する。

#### 実装・検証

- [実装](../../string/run-length-encoding.hpp)
- [Verify: run-length-encoding.cpp](../../tests/unit/string/run-length-encoding.cpp)
