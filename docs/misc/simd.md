## SIMD 演算マクロ

256 bit 整数ベクトル型 `m256` と `SET`, `SET64`, `LOAD`, `STORE`, `AND`, `OR`, `XOR`, `ADD`, `SUB`, `CMP` などのマクロを提供する。通常の ADD/SUB は 32 bit レーン、ADD64 は 64 bit レーン。

`GETMOD`, `MADD`, `MSUB` は値域を限定した剰余計算用で、任意整数を正規化する関数ではない。`ALIGN` は 64 byte アラインメント指定。

GCC のターゲットを `avx2,avx512f,avx512vl` に設定するため、対応する x86 CPU とコンパイラが必要。マクロ名とコンパイル設定への影響は include 後にも及ぶ。

#### 実装・検証

- [実装](../../misc/simd.hpp)
- [Verify: simd.cpp](../../tests/unit/misc/simd.cpp)
