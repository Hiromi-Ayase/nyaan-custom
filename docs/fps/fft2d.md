## 2 次元 NTT と畳み込み

`vector<FormalPowerSeries<mint>>` を行列状の係数列として扱う。行添字と列添字がそれぞれ変数の次数に対応する。

- `fft2d(a)` / `ifft2d(a)` は行・列方向の変換と正規化済みの逆変換。非空の長方形配列で、行数・列数をともに正の 2 冪にする。
- `multiply2d(a,b)` は通常の 2 変数多項式積。出力の形は `(Ha+Hb-1) × (Wa+Wb-1)`。入力は変更せず、空入力の積は空。
- `multiply2d_naive` は直接計算、`multiply2d_partially_naive` は片方向の変換を中心に使う版。
- `transpose(a)` は非空の長方形配列の転置。

NTT 向け FPS バックエンドを使い、両軸の変換長が法の上限内に収まるようにする。主な変換経路は、ゼロ埋め後の形を $H\times W$ として時間 $O(HW(\log H+\log W))$、領域 $O(HW)$。小さい形では直接計算へ切り替える。

#### 実装・検証

- [実装](../../fps/fft2d.hpp)
- [検証: fft2d.test.cpp](../../verify/verify-unit-test/fft2d.test.cpp)
