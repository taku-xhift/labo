#! /usr/bin/ruby
 
# = RDoc �̃T���v��
# Author::    ���s��
# Copyright:: Copyright 2007 WebOS Goodies
# License::   �����R��
#
# ���̃t�@�C���� RDoc[http://rdoc.sourceforge.net/] �ɂ��
# �h�L�������g�����̃T���v���ł��B
#
# ���������A�����Y��Ă܂������N���X���͎����I�Ƀ����N�ɂȂ�܂��B
# RDocTest, RDocTest#method ���Ăȋ�ɁB
 
# �N���X�͒P�Ȃ�_�~�[�ł��B�ȉ��A���X�g�̗�B
#
# * �ʏ탊�X�g�B
# * �ʏ탊�X�g�B
#
# 1. �ԍ��t�����X�g�B
# 2. �ԍ��t�����X�g�B
#    �C���f���g�𑵂���Ε����s�ɋL�q�ł��܂��B
#    * ���X�g�̃l�X�g���ł��܂��B
 
class RDocTest
 
  # *initialize* ���\�b�h�ɑ΂���R�����g��
  # *new* �N���X���\�b�h�̂��̂Ƃ��Ĉ����܂��B
 
  def initialize()
    # ���֌W�ȏꏊ�ɂ���R�����g�͔��f����܂���B
  end
 
  # [arg1]
  #   ��`���X�g�̓��e�͕ʂ̍s�ɋL�q���邱�Ƃ��ł��܂��B
  # [arg2]
  #   �����s�ɂ킽�邱�Ƃ�
  #   �������ł��܂��B
  #
  # ���\�b�h�̎g�p��Ƃ������������Ƃ���
  #
  #   ����������� pre �^�O�ŕ\������܂��B
 
  def method(arg1, arg2)
  end
 
  private
 
  # �v���C�x�[�g���\�b�h�͕\������܂���B
 
  def undocumented()
  end
 
end
