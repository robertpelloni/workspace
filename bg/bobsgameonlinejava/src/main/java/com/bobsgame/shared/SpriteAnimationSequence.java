package com.bobsgame.shared;

public class SpriteAnimationSequence {
	public String frameSequenceName;
	public int frameStart;
	public int hitBoxFromLeftPixels1X;
	public int hitBoxFromRightPixels1X;
	public int hitBoxFromTopPixels1X;
	public int hitBoxFromBottomPixels1X;

	public SpriteAnimationSequence(String frameSequenceName, int frameStart, int hitBoxFromLeft1X, int hitBoxFromRight1X, int hitBoxFromTop1X, int hitBoxFromBottom1X) {
		this.frameSequenceName = frameSequenceName;
		this.frameStart = frameStart;
		this.hitBoxFromLeftPixels1X = hitBoxFromLeft1X;
		this.hitBoxFromRightPixels1X = hitBoxFromRight1X;
		this.hitBoxFromTopPixels1X = hitBoxFromTop1X;
		this.hitBoxFromBottomPixels1X = hitBoxFromBottom1X;
	}
}

