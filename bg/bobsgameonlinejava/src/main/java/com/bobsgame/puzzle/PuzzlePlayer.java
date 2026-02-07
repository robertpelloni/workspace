package com.bobsgame.puzzle;

import com.bobsgame.shared.BobColor;

public class PuzzlePlayer {
    public GameLogic gameLogic;

    // Input state
    public boolean ROTATECW_HELD = false;
    public boolean HOLDRAISE_HELD = false;
    public boolean ROTATECCW_HELD = false;
    public boolean UP_HELD = false;
    public boolean LEFT_HELD = false;
    public boolean DOWN_HELD = false;
    public boolean RIGHT_HELD = false;
    public boolean SLAM_HELD = false;

    public boolean slamLock = true;
    public boolean singleDownLock = false;
    public boolean doubleDownLock = true;

    // Config
    public boolean gridRule_showWarningForFieldThreeQuartersFilled = true;
    public BobColor gridCheckeredBackgroundColor1 = BobColor.gray;
    public BobColor gridCheckeredBackgroundColor2 = BobColor.darkGray;

    // Caption placeholders
    // public Caption nameCaption;
    // public Caption gameCaption;
    // public Caption difficultyCaption;

    public PuzzlePlayer(GameLogic logic) {
        this.gameLogic = logic;
    }

    public boolean pausePressed() {
        return false; // TODO
    }
}
