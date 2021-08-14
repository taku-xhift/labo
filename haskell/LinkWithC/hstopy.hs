module Htop where
import CString

fact :: Int -> Int
fact n = if n == 1 then 1 else (n * fact (n - 1))

factorial :: Int -> IO Int
factorial n = return (fact n)

mystring :: IO CString
mystring = newCString "hello haskell world!"

foreign export ccall factorial :: Int -> IO Int
foreign export ccall mystring :: IO CString
