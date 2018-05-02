# word-count
Software Engineering, BUAA

---

## 指令格式

```
WordCount.exe [-r] [-m 词组长度] [-n 输出数量] 路径
```

 - -r参数递归地统计文件夹下所有文件的单词词频并累积成一个列表，最终输出；
 - -m参数设定统计的词组长度（要求词组长度>0，默认为1，表示统计单词）；
 - -n参数设定输出的单词数量（要求输出数量>0，默认为10）。

## 执行结果

执行后会在当前目录生成result.txt文件，输出的格式为：
```
characters: number  // 字符数
words: number       // 合法单词数
lines: number       // 非空行数
<word1>: number     // <word1>出现的次数
<word2>: number     // <word2>出现的次数
...
