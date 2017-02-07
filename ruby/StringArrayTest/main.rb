

def printer(*array)
  p array[0].capitalize
end

stringArray = ["apple", "tea", "is", "so", "hot", "!"]


#p stringArray[0].capitalize
printer(*stringArray)

