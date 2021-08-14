module Adder where

adder :: Int -> Int -> IO Int  -- —]Œv‚ÈIO
adder x y = return (x+y)

foreign export stdcall adder :: Int -> Int -> IO Int
