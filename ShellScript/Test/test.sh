#! /bin/sh
arg_chk()
{
# �����̐��� 2 �̏ꍇ
if test $# -eq 2
then
    return 0
# �����̐��� 2 �ȊO�̏ꍇ
else
    return 1
fi
}


arg_chk $@
ret=$?
echo "�����`�F�b�N����=${ret}"
