
$price = 400

# �o�b�N�X���b�V���L�@�A���W�J���L��
print <<"EOS"
The price is #{$price}.
EOS

# ��̂��̂Ɠ�������
print <<EOS
The price is #{$price}.
EOS

# ���W�J�͂ł��Ȃ�
print <<'EOS'
The price is #{$price}.
EOS

# �R�}���h�����s
print <<`EOC`
date
diff test.c.org test.c
EOC
