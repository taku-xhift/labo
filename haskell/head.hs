
main :: IO ()
main = getContents >>= putStr . firstNLines 10

firstNLines n = unlines . take  n . lines
