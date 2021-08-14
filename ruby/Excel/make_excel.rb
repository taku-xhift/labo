#!/usr/bin/ruby
 
require 'excel_base'
include ExcelBase
 
book = Spreadsheet::Workbook.new
sheet1 = book.create_worksheet_with_name 'fruit' # �^�u���쐬
 
sheet1.row(0).make_title %w(name num price)
 
fruits = [
  ['apple', 5, 100],
  ['banana', 10, 200],
  ['orange', 10, 150],
]
fruits.each_with_index do |fruit, i|
  sheet1.row(i+1).add_data fruit # �z���n��
end
 
sheet2 = book.create_worksheet_with_name 'another' # �^�u���쐬
sheet2.row(0).add_data %W(http://sasata299.com/ http://www.zozom.net/)
sheet2.row(1).add_data %w(hoge huga)
 
sheet2.row(0).set_format(1, ColorFormat.new(:red))
sheet2.rows.each_with_index do |row, i|
  sheet2.column(i).width = 30 # �J��������ς�����Ƃ�
end
 
book.write 'hoge.xls' # �ۑ�����t�@�C����