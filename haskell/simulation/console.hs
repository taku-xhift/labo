


-- エントリポイント
main = gameRoop



data UserData = UserData {
     money :: Int,
     playerID :: Int,
     input :: String
}

getMoney :: UserData -> Int
getMoney = money

setInput :: UserData -> String
setInput = input

userData = UserData 400 2 "input"



gameRoop :: IO ()
--gameRoop = getContents >>= inputTest
gameRoop = getLine >>= inputTest




inputTest :: String -> IO()
inputTest cs = if cs == "get"
                  then putStrLn $ show $ getMoney userData
                  else putStrLn cs



