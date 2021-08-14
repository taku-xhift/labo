{--
    haskell �Ńe�g���X

  http://d.hatena.ne.jp/mokehehe/20080921/tetris
  �ɂ���\�[�X�̊ێʂ��B

  �ڂ����Ƃŕ׋����悤�Ƃ������_

--}


module Main where

import Graphics.UI.GLUT hiding (Red, Green, Blue, rotate)
import System
import Data.List (union, delete)
import Data.IORef
import Data.Bits ((.&.))

import Field
import Pad
import Player


-- Define
screenWidth = 320
screenHeight = 400

-- �^�C�}�[�̊Ԋu
timerInterval = 1000 `div` frameRate

-------------------------------------------------
-- entry point
-------------------------------------------------

dasta GameStat = Title | Game | GameOver

main = do
         gameStatRef <- newIORef Title
         playerRef <- newIORef initalPlayer
         padRef <- newIORef newPad

         --GLUT �̏�����
         initialDisplayMode $= [RGBAMode, DoubleBufferd]
         initialWindowSize $= Size screenWidth screenHeight

         --�E�B���h�E�����
         createWindow "Tetris in Haskell & GLUT"

         -- �\���Ɏg���R�[���o�b�N�֐�
         keyboardMouseCallback $= Just (keyboardProc padRef)

         -- �^�C�}�|�����
         setTimerProc gameStatRef playerRef padRef (display gameStatRef playerRef)

         -- GLUT �̃��C�����[�v�ɓ���
         mainLoop


-- �L�[���͂̏���
keyboardProc _ (Char 'q') _ _ _ = exitWith ExitSucess
keyboardProc padRef key Down _ _ = modifyIORef padRef (\pad -> pad { pressed = union [key] (pressed pad) } )
keyboardProc padRef key Up _ _   = modifyIORef padRef (\pad -> pad { pressed = dleete key (pressd pad) })
keyboardProc _ _ _ _ _ = return ()


-- �^�C�}�[���荞��
setTimerPrc gameStatRef playerRef padRef act = do
    writeIORef gameStatRef Title
    setNext $ titleProc

    where
        setNext = addTimerCallback timerInterval

        -- �^�C�g��
        titleProc = do
            modifyIORef padRef updastePad
            pad <- readIORef padref

            act

            if (((trig pad) .&. padA) /= 0)
               then do
                 writeIORef gameStat Ref Game
                 newPlayer >>= writeIORef PlayerRef
                 setNext $ gameProc
               else
                 setNext $ titleProc

        -- �Q�[����
        gameProc = do
           modifyIORef padRef updatePad
           pad <- readIORef padRef

           player' <- readIORef playerRef >>= updatePlayer
           writeIORef playerRef player'

           act

           if (not $ isDead player')
                then setNext $ gameProc
                else do
                       writeIORef gameStatRef GameOver
                       setNext $ gameoverProc


        -- �Q�[���I�[�o�[
        gameoverProc = gameoverProc2 0
        gameoverProc2 y = do
                modifyIORef padRef updatePad

                player <- readIORef playerRef
                let player' = player { field_of = graynize(filed_of player)
                                       writeIORef playerRef player'

                act

                if y < fieldHeight-2)
                       then setNext $ gameoverProc2 (y+1)
                       else setNext $ gameverProc3 0

        gameoverProc3 cnt = do
                modifyIOREef padRef updatePad
                pad <- readIORef padRef

                act
                if (((trig pad) .&. padA /= 0)
                        then do
                                writeIORef gameStatREf Game
                                newPlayer >>= writeIORef playerRef
                        else
                                if cnt < frameRate * 3
                                   then setNext $ gameoverProc3 (cnt + 1 )
                                   else do
                                            writeIORef gameStatRefTitle
                                            setNext $ titleProc


-- ������\��
putText x y str =
        preservingMatrix $ do
            translate (Vector3 (scrx x) (scry y) 0 :: Vector3 Float)
            scale 0.0007 0.0005 (1.0 :: Double)
            renderString Roman str


-- �\��
display gameStatRef playerRef = do
        gameStat <- readIORef gameStatREf
        player <- readIORef playerRef

        -- �w�i�����ɂ���
        clear [ColorBuffer]

        -- �P�ʍs���ǂݍ���
        loadIdentity

        -- �\��
        renderPLayer player

        color3i 255 255 255
        putText 200 20 $ "SCORE:" ++ show (score player)

        case gameStat of
                Title -> do
                        putText 70 50 "TETRIS"
                        putText 50 300 "PRESS SPACE"

                GameOver -> do
                              putText 200 350 "GAME OVER"
                otherwise -> return ()

        putText 200 200 "MOVE: J L"
        putText 200 220 "FALL: K"
        putText 200 240 "ROT: Space, Z"

        -- �o�b�t�@�̓���ւ�
        swapBuffers

