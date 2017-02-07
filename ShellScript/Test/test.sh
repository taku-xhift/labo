#! /bin/sh
arg_chk()
{
# 引数の数が 2 の場合
if test $# -eq 2
then
    return 0
# 引数の数が 2 以外の場合
else
    return 1
fi
}


arg_chk $@
ret=$?
echo "引数チェック結果=${ret}"
