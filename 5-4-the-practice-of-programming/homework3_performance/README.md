# 性能作业

## 测试用例

测试文件《资本论》第一卷`Capital-Volume-I.txt`。

- 总单词数量：256241

- 文本中所含不同单词的数量：11747

- 排名前三的单词及其数量

    - the，24250次
    - of，17206次
    - in，6789次

- 采用`-std=c++11`编译选项，不开启优化，执行所用时间（测试十次取平均值）：

    ```
    real    0m0.365s
    user    0m0.356s
    sys     0m0.004s
    ```

> 注：在`printStatis`函数中添加`total`变量，统计所有单词的总数。

## 性能优化

1. 由于单词对出现行数的`map`映射中，单词的顺序并不重要，因此将`WordsStatis`变量改用`unordered_map`。
2. `statisWord`函数中，采用`find`找到单词对应的迭代器后，在`else`中就不需要再进行一次索引，可以用一个迭代器变量`wordStatis`记录`find`的结果，在`else`中直接采用`wordStatis`的值更新行号。
3. 27行，`unordered_map`的索引字符串只需要使用这一次，因此改为`std::move`移动，避免字符串的复制，在主程序中将`word.clear()`改为`word = {}`，新申请一个字符串对象。
4. 37行，`cmp`函数的两个参数都改为`const`引用，避免字符串复制。
5. 可选：开启优化选项，例如`-O3`。

进行前四项性能优化后，不开启优化选项，运行十次的平均执行时间为：

```
real    0m0.128s
user    0m0.118s
sys     0m0.008s
```

性能提高的比例约为(0.365-0.128)/0.365=65%。