#!/usr/local/bin/perl

$view = 'embTest_4040_base_r.png';

print "Content-type: image/png\n\n"; #コンテンツタイプを指定する
open IMGG,"$view"; #ファイルハンドル IMGGに画像ファイルを読み込む
binmode (IMGG); #画像なのでバイナリモードに設定する
print <IMGG>; #ファイルハンドルを画面に書き出す
close (IMGG); #ファイルハンドルを閉じる

exit;

