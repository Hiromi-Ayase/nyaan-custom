## 永続キュー

`PersistentQueue<T>` は初期状態を版番号 0 の空キューとして保持する。

`push(value,id=-1)` は指定版の末尾へ追加した新しい版番号を返す。`pop(id=-1)` は先頭を削除した `(取り出した値, 新しい版番号)` を返す。`id=-1` は最後に作った版を意味する。古い版は変更されない。

空の版に `pop` しない。祖先ダブリングにより、各操作は履歴の深さ $D$ に対して $O(\log D)$。追加した要素は祖先表を保持し、履歴全体で $O(Q\log Q)$ の領域を使う。

#### 実装・検証

- [実装](../../data-structure/persistent-queue.hpp)
- [Verify: persistent.cpp](../../tests/unit/data-structure/persistent.cpp)
