


data UserData = UserData {
     money :: Int,
     playerID :: Int,
     input :: String
}


userData = UserData 400 2 "input"


getMoney :: UserData -> Int
getMoney = money




inputTest :: String -> IO()
inputTest cs = if cs == "get\n"
                  then putStrLn $ show $ getMoney userData
                  else putStrLn cs


sample :: Bool
sample = if "get" == "get"
            then True
            else False
