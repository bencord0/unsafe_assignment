module UnsafeAssignment
    ( run
    ) where

import qualified Data.IORef as IR
import qualified System.Random as R
import qualified Control.Concurrent as C
import qualified Control.Concurrent.MVar as MV

maybeSlowAssignment :: IR.IORef Int -> Int -> IO ()
maybeSlowAssignment ref i = do
    b <- R.randomIO
    case b of
        True -> C.threadDelay 1000
        False -> return ()
    IR.writeIORef ref i 

run :: IO ()
run = do 
    a <- IR.newIORef 0
    atEnd1 <- MV.newEmptyMVar
    atEnd2 <- MV.newEmptyMVar
    _ <- C.forkIO $ do
      (maybeSlowAssignment a 1)
      MV.putMVar atEnd1 ()
    _ <- C.forkIO $ do
      (maybeSlowAssignment a 2)
      MV.putMVar atEnd2 ()
    MV.takeMVar atEnd1
    MV.takeMVar atEnd2
    print =<< IR.readIORef a
    return ()

