## 整数区間の黄金分割探索

`golden_section_search<T,get_min=true>(f,min,max)` は整数の**閉区間**で単峰な関数の最適点と値を `pair<long long,T>` として返す。`get_min=false` なら最大化。

最小化では値が減少してから増加する（同値を含む）こと、最大化ではその逆が必要。`min <= max` とし、境界を広げる内部の整数計算が `long long` に収まる範囲で使う。

関数評価は $O(\log(max-min+2))$ 回、追加領域は $O(1)$。

#### 実装・検証

- [実装](../../dp/golden-section-search.hpp)
- [Verify: monge.cpp](../../tests/unit/dp/monge.cpp)
