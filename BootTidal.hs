:set -package hosc
:set -XOverloadedStrings
:set prompt ""

import Sound.Tidal.Context

import System.IO (hSetEncoding, stdout, utf8)

import qualified Control.Concurrent.MVar as MV
import qualified Sound.Tidal.Tempo as Tempo
import qualified Sound.OSC.FD as O

hSetEncoding stdout utf8

-- total latency = oLatency + cFrameTimespan

:{
let target = Target {oName = "visualiser",   -- A friendly name for the target (only used in error messages)
                     oAddress = "127.0.0.1", -- The target's network address, normally "localhost"
                     oPort = 50500,           -- The network port the target is listening on
                     oLatency = 0.2,         -- Additional delay, to smooth out network jitter/get things in sync
                     oSchedule = Live,       -- The scheduling method - see below
                     oWindow = Nothing,       -- Not yet used
                     oHandshake = False,
                     oBusPort = Just 1
                    }
    oscmap = [(target, [superdirtShape]),
              (superdirtTarget, [superdirtShape])
             ]        
:}

tidal <- startStream defaultConfig oscmap

--stream <- startStream defaultConfig oscmap
--d = streamReplace stream




--tidal <- startTidal (superdirtTarget {oLatency = 0.1, oAddress = "127.0.0.1", oPort = 57120}) (defaultConfig {cFrameTimespan = 1/20})

:{
let only = (hush >>)
    p = streamReplace tidal
    hush = streamHush tidal
    panic = do hush
               once $ sound "superpanic"
    list = streamList tidal
    mute = streamMute tidal
    unmute = streamUnmute tidal
    unmuteAll = streamUnmuteAll tidal
    solo = streamSolo tidal
    unsolo = streamUnsolo tidal
    once = streamOnce tidal
    first = streamFirst tidal
    asap = once
    nudgeAll = streamNudgeAll tidal
    all = streamAll tidal
    resetCycles = streamResetCycles tidal
    setcps = asap . cps
    getcps = do tempo <- MV.readMVar $ sTempoMV tidal
                return $ Tempo.cps tempo
    getnow = do tempo <- MV.readMVar $ sTempoMV tidal
                now <- O.time
                return $ fromRational $ Tempo.timeToCycles tempo now
    xfade i = transition tidal True (Sound.Tidal.Transition.xfadeIn 4) i
    xfadeIn i t = transition tidal True (Sound.Tidal.Transition.xfadeIn t) i
    histpan i t = transition tidal True (Sound.Tidal.Transition.histpan t) i
    wait i t = transition tidal True (Sound.Tidal.Transition.wait t) i
    waitT i f t = transition tidal True (Sound.Tidal.Transition.waitT f t) i
    jump i = transition tidal True (Sound.Tidal.Transition.jump) i
    jumpIn i t = transition tidal True (Sound.Tidal.Transition.jumpIn t) i
    jumpIn' i t = transition tidal True (Sound.Tidal.Transition.jumpIn' t) i
    jumpMod i t = transition tidal True (Sound.Tidal.Transition.jumpMod t) i
    mortal i lifespan release = transition tidal True (Sound.Tidal.Transition.mortal lifespan release) i
    interpolate i = transition tidal True (Sound.Tidal.Transition.interpolate) i
    interpolateIn i t = transition tidal True (Sound.Tidal.Transition.interpolateIn t) i
    clutch i = transition tidal True (Sound.Tidal.Transition.clutch) i
    clutchIn i t = transition tidal True (Sound.Tidal.Transition.clutchIn t) i
    anticipate i = transition tidal True (Sound.Tidal.Transition.anticipate) i
    anticipateIn i t = transition tidal True (Sound.Tidal.Transition.anticipateIn t) i
    forId i t = transition tidal False (Sound.Tidal.Transition.mortalOverlay t) i
    d1 = p 1 . (|< orbit 0)
    d2 = p 2 . (|< orbit 1)
    d3 = p 3 . (|< orbit 2)
    d4 = p 4 . (|< orbit 3)
    d5 = p 5 . (|< orbit 4)
    d6 = p 6 . (|< orbit 5)
    d7 = p 7 . (|< orbit 6)
    d8 = p 8 . (|< orbit 7)
    d9 = p 9 . (|< orbit 8)
    d10 = p 10 . (|< orbit 9)
    d11 = p 11 . (|< orbit 10)
    d12 = p 12 . (|< orbit 11)
    d13 = p 13
    d14 = p 14
    d15 = p 15
    d16 = p 16
:}

:{
let setI = streamSetI tidal
    setF = streamSetF tidal
    setS = streamSetS tidal
    setR = streamSetR tidal
    setB = streamSetB tidal
:}

-- these are the low level parameters that define the coordinates, the target grid, the shape radius, color etc.
:{
let x = pI "x"
    y = pI "y"
    x2 = pI "x2"
    y2 = pI "y2"
    rad = pI "rad"
    rad2 = pI "rad2"
    target = pI "target"
    t = pS "type"
    mode = pI "mode"
    color = pS "color"
    red = pI "red"
    green = pI "green"
    blue = pI "blue"
    updating = pS "updating"
    fill = pS "fill"
    primitive = pS "primitive"
    primres = pI "primres"
    boundMin = pI "boundMin"
    boundMax = pI "boundMax"
    rotateX = pI "rotateX"
    rotateY = pI "rotateY"
    rotateZ = pI "rotateZ"
    length = pF "length"
    z = pI "z"
    sys = pS "sys"
    m = degradeBy 1
    shiftBy n = (n <~)
    shrand n = shiftBy n $ rand
:}

-- these are the more complex functions that make coding much more simple
:{
let circle xpos ypos radius p = ((# x xpos) . (# y ypos) . (# rad radius) . (# t "circle")) $ p
    ellipse xpos ypos xradius yradius p = ((# x xpos) . (# y ypos) . (# rad xradius) . (# rad2 yradius) . (# t "ellipse")) $ p
    sqr xpos ypos radius p = ((# x xpos) . (# y ypos) . (# rad radius) . (# t "square")) $ p
    line xpos ypos xpos2 ypos2 p = ((# x xpos) . (# y ypos) . (# x2 xpos2) . (# y2 ypos2) . (# t "line")) $ p
    rgb r g b p = ((# red r) . (# green g) . (# blue b)) $ p 
    diag xpos ypos radius p = ((# x xpos) . (# y ypos) . (# rad radius) . (# t "diagonal")) $ p
    rotate x y z p = ((# rotateX x) . (# rotateY y) . (# rotateZ z)) $ p
:}

:set prompt "tidal> "
:set prompt-cont ""
