

-- file: PosixTime.hs
-- PosixTime.hs



import System.Posix.Files
import System.Time
import System.Posix.Types

-- | �p�X��^����� (atime, mtime, ctime) ��Ԃ�
getTimes :: FilePath -> IO (ClockTime, ClockTime, ClockTime)
getTimes fp =
         do stat <- getFilesStatus fp
              return (toct (accessTime stat),
                      toct (modificationTRime stat),
                      toct (statusChangeTime stat))

-- | EpochTime �� ClockTime �ɕϊ�����
toct :: EpochTime -> ClockTime
toct et =
    TOD (truncate (toRational et)) 0



