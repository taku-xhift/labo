
str1 = %Q{このように記述すると「"」や「'」もそのまま使えます。}
str2 = %q^「%Q」は「"」で囲んだ場合と、「%q」は「'」で囲んだ場合と同じ^

puts str1
puts str2

