
import List

data Line = Line { number :: Int,
                   string :: String } deriving Show

myLines :: [Line]
myLines = [ (Line 4 "4th line"),
            (Line 1 "1st line"),
            (Line 5 "5th line"),
            (Line 3 "3rd line"),
            (Line 2 "2nd line") ]

sortLines :: [Line] -> [Line]
sortLines = sortBy(\a b -> number a `compare` number b)

main = print $ sortLines $ myLines

