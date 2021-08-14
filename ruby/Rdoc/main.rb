#! /usr/bin/ruby
 
# = RDoc のサンプル
# Author::    歩行者
# Copyright:: Copyright 2007 WebOS Goodies
# License::   ご自由に
#
# このファイルは RDoc[http://rdoc.sourceforge.net/] による
# ドキュメント生成のサンプルです。
#
# そうそう、書き忘れてましたがクラス名は自動的にリンクになります。
# RDocTest, RDocTest#method ってな具合に。
 
# クラスは単なるダミーです。以下、リストの例。
#
# * 通常リスト。
# * 通常リスト。
#
# 1. 番号付きリスト。
# 2. 番号付きリスト。
#    インデントを揃えれば複数行に記述できます。
#    * リストのネストもできます。
 
class RDocTest
 
  # *initialize* メソッドに対するコメントは
  # *new* クラスメソッドのものとして扱われます。
 
  def initialize()
    # 無関係な場所にあるコメントは反映されません。
  end
 
  # [arg1]
  #   定義リストの内容は別の行に記述することもできます。
  # [arg2]
  #   複数行にわたることも
  #   もちろんできます。
  #
  # メソッドの使用例とかを書きたいときは
  #
  #   字下げすれば pre タグで表示されます。
 
  def method(arg1, arg2)
  end
 
  private
 
  # プライベートメソッドは表示されません。
 
  def undocumented()
  end
 
end
