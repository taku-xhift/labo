require 'spreadsheet'

xls = Spreadsheet.open('test.xls', 'rb') #Excelファイルの読み込み
sheet = xls.worksheet(0) #0番目つまり1番始めのsheetを読み込む

#読み込みの開始が'０'から始まる。
puts sheet[0,0] #実際のExcelでは、1行目の2列目の値を読み込み
#sheet[4,6] #実際のExcelでは、5行目の6列目の値を読み込み
