
main = do cs <- getContents
          putStr $ count cs

count :: String -> String
count cs = countString . readLine

countString :: String -> Int
countString num = num.length

readLine :: String -> String
readLine cs = 
