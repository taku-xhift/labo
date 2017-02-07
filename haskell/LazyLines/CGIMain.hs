
-- This program is rewrite by Shishido.
-- The original program is write by Minero Aoki

module Main (main) where

import CGI
import LazyLines

main = do ctx <- loadContext "./config"
          runCGI (appMain ctx)

