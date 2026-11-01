## 削除可能な優先度付きキュー

`ErasablePriorityQueue<T,Minimize=true>` は二つのヒープで遅延削除する。`false` なら最大値を優先する。

`push(x)` で追加、`erase(x)` で一個の削除を予約し、`top()` / `pop()` で最良要素を参照・削除する。`erase` には実際に残っている値だけを渡し、空のキューで `top` / `pop` しない。重複値は個数で管理される。

各挿入・削除は償却 $O(\log Q)$。削除待ちの要素も保持するため、領域は現在の要素数ではなく操作数 $Q$ に対して $O(Q)$。

#### 実装・検証

- [実装](../../data-structure/erasable-priority-queue.hpp)
- [Verify: heaps.cpp](../../tests/unit/data-structure/heaps.cpp)
