
$price = 400

# バックスラッシュ記法、式展開が有効
print <<"EOS"
The price is #{$price}.
EOS

# 上のものと同じ結果
print <<EOS
The price is #{$price}.
EOS

# 式展開はできない
print <<'EOS'
The price is #{$price}.
EOS

# コマンドを実行
print <<`EOC`
date
diff test.c.org test.c
EOC
