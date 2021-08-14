

-- file: PosixTime.hs
-- PosixTime.hs



import System.Posix.Files
import System.Time
import System.Posix.Types

-- | ƒpƒX‚ð—^‚¦‚é‚Æ (atime, mtime, ctime) ‚ð•Ô‚·
getTimes :: FilePath -> IO (ClockTime, ClockTime, ClockTime)
getTimes fp =
         do stat <- getFilesStatus fp
              return (toct (accessTime stat),
                      toct (modificationTRime stat),
                      toct (statusChangeTime stat))

-- | EpochTime ‚ð ClockTime ‚É•ÏŠ·‚·‚é
toct :: EpochTime -> ClockTime
toct et =
    TOD (truncate (toRational et)) 0



