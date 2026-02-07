package com.bobsgame.client.engine.game.nd.bobsgame.game;

import java.util.ArrayList;
import java.util.UUID;
import com.bobsgame.shared.BobColor;

public class PieceType {

    public String uuid = "";
    public String name = "New Piece Type";
    @Override public String toString() { return name; }

    // Classification Flags
    public boolean useAsNormalPiece = false;
    public boolean useAsGarbagePiece = false;
    public boolean useAsPlayingFieldFillerPiece = false;
    public boolean disallowAsFirstPiece = false;

	public String spriteName = "";
	public BobColor color = null;
	public int numBlocks = 1;
	public ArrayList<Piece.Rotation> rotationSet = null;
	public int randomSpecialPieceChanceOneOutOf = 0;
	public int frequencySpecialPieceTypeOnceEveryNPieces = 0;

	public boolean flashingSpecialType = false;
	public boolean clearEveryRowPieceIsOnIfAnySingleRowCleared = false;
	public int turnBackToNormalPieceAfterNPiecesLock = -1;

	public boolean bombPiece = false;
	public boolean weightPiece = false;
	public boolean pieceRemovalShooterPiece = false;
	public boolean pieceShooterPiece = false;

	public boolean disappearOnceSetInGrid = false;

	public BlockType overrideBlockType = null;
    //public ArrayList<BlockType> overrideBlockTypes = new ArrayList<BlockType>();

	public PieceType() {
        this.uuid = UUID.randomUUID().toString();
	}

	public PieceType(int numBlocks, ArrayList<Piece.Rotation> rotationSet) {
		this();
		this.numBlocks = numBlocks;
		this.rotationSet = rotationSet;
	}

	public PieceType(BobColor color, int numBlocks, ArrayList<Piece.Rotation> rotationSet) {
		this();
		this.color = color;
		this.numBlocks = numBlocks;
		this.rotationSet = rotationSet;
	}

	public PieceType(BobColor color, int numBlocks, ArrayList<Piece.Rotation> rotationSet, int randomSpecialPieceChanceOneOutOf, int frequencySpecialPieceTypeOnceEveryNPieces) {
		this();
		this.color = color;
		this.numBlocks = numBlocks;
		this.rotationSet = rotationSet;
		this.randomSpecialPieceChanceOneOutOf = randomSpecialPieceChanceOneOutOf;
		this.frequencySpecialPieceTypeOnceEveryNPieces = frequencySpecialPieceTypeOnceEveryNPieces;
	}

	public PieceType(String spriteName, BobColor color, int numBlocks, ArrayList<Piece.Rotation> rotationSet, int randomSpecialPieceChanceOneOutOf, int frequencySpecialPieceTypeOnceEveryNPieces) {
		this();
		this.spriteName = spriteName;
		this.color = color;
		this.numBlocks = numBlocks;
		this.rotationSet = rotationSet;
		this.randomSpecialPieceChanceOneOutOf = randomSpecialPieceChanceOneOutOf;
		this.frequencySpecialPieceTypeOnceEveryNPieces = frequencySpecialPieceTypeOnceEveryNPieces;
	}

	public boolean isSpecialType() {
		if(randomSpecialPieceChanceOneOutOf!=0)return true;
		if(frequencySpecialPieceTypeOnceEveryNPieces!=0)return true;
		if(flashingSpecialType!=false)return true;
		if(bombPiece)return true;
		if(weightPiece)return true;
		if(pieceRemovalShooterPiece)return true;
		if(pieceShooterPiece)return true;

		return false;
	}
}
