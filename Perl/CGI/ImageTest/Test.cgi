#!/usr/local/bin/perl

$view = 'embTest_4040_base_r.png';

print "Content-type: image/png\n\n"; #�R���e���c�^�C�v���w�肷��
open IMGG,"$view"; #�t�@�C���n���h�� IMGG�ɉ摜�t�@�C����ǂݍ���
binmode (IMGG); #�摜�Ȃ̂Ńo�C�i�����[�h�ɐݒ肷��
print <IMGG>; #�t�@�C���n���h������ʂɏ����o��
close (IMGG); #�t�@�C���n���h�������

exit;

