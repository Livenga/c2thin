# c2thin
入力画像に対して, 細線化処理を行い出力をする.  

## 要約
パターン認識に用いる画像の前処理として, 細線化処理を行う.  
そのために, 細線化処理のみを行うプログラム.

## 使用方法
オプション等は現在(2015/11/10)ついていないため, ソース内の画像ファイル名を変更する.  
`$ ./c2thin`

### 入出力画像
![input][input_img]
![output][output_img]  

### 参考文献
1. technotype [technotype][reference_thin]

[input_img]: imgs/a.png
[output_img]: imgs/a_thin.png

[reference_thin]: http://www.technotype.net/tutorial/tutorial.php?fileId={Image%20processing}&sectionId={thinning-filter} "technotype"
