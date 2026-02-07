package com.bobsgame.puzzle;

import java.io.Serializable;

public class FrameState implements Serializable {
    public long ticksPassed = 0;
    public int receivedGarbageAmount = 0;
    public boolean ROTATECW_HELD = false;
    public boolean HOLDRAISE_HELD = false;
    public boolean ROTATECCW_HELD = false;
    public boolean UP_HELD = false;
    public boolean LEFT_HELD = false;
    public boolean DOWN_HELD = false;
    public boolean RIGHT_HELD = false;
    public boolean SLAM_HELD = false;
    public String gridString = "";
    public int randomInt = 0;

    public boolean slamLock = true;
    public boolean singleDownLock = false;
    public boolean doubleDownLock = true;
}
