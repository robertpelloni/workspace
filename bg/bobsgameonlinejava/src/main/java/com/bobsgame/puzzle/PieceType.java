package com.bobsgame.puzzle;

import com.bobsgame.shared.BobColor;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.UUID;

public class PieceType implements Serializable {
    public String name = "";
    public String uuid = "";

    public BobColor color = null;
    public RotationSet rotationSet;

    public int frequencySpecialPieceTypeOnceEveryNPieces = 0;
    public int randomSpecialPieceChanceOneOutOf = 0;
    public boolean flashingSpecialType = false;
    public boolean clearEveryRowPieceIsOnIfAnySingleRowCleared = false;
    public int turnBackToNormalPieceAfterNPiecesLock = -1;
    public boolean fadeOutOnceSetInsteadOfAddedToGrid = false;

    public boolean useAsNormalPiece = false;
    public boolean useAsGarbagePiece = false;
    public boolean useAsPlayingFieldFillerPiece = false;
    public boolean disallowAsFirstPiece = false;

    public String spriteName = "";

    public boolean bombPiece = false;
    public boolean weightPiece = false;
    public boolean pieceRemovalShooterPiece = false;
    public boolean pieceShooterPiece = false;

    public ArrayList<String> overrideBlockTypes_UUID = new ArrayList<>();

    public static PieceType emptyPieceType;
    public static PieceType oneBlockCursorPieceType;
    public static PieceType twoBlockHorizontalCursorPieceType;
    public static PieceType twoBlockVerticalCursorPieceType;
    public static PieceType threeBlockHorizontalCursorPieceType;
    public static PieceType threeBlockVerticalCursorPieceType;
    public static PieceType fourBlockCursorPieceType;

    public PieceType() {
        this.name = "empty";
        this.uuid = UUID.randomUUID().toString();

        BlockOffset b = new BlockOffset(0, 0);
        Rotation r = new Rotation();
        r.add(b);
        rotationSet = new RotationSet("");
        rotationSet.add(r);
    }

    public PieceType(String name, String spriteName, BobColor color, int numBlocks, RotationSet rotationSet, int randomSpecialPieceChanceOneOutOf, int frequencySpecialPieceTypeOnceEveryNPieces) {
        this.name = name;
        this.uuid = UUID.randomUUID().toString();
        this.spriteName = spriteName;
        this.color = color;
        this.rotationSet = rotationSet;
        this.randomSpecialPieceChanceOneOutOf = randomSpecialPieceChanceOneOutOf;
        this.frequencySpecialPieceTypeOnceEveryNPieces = frequencySpecialPieceTypeOnceEveryNPieces;
    }
}
