package com.bobsgame.puzzle;

import com.bobsgame.shared.BobColor;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.UUID;

public class BlockType implements Serializable {
    public String name = "";
    public String uuid = "";

    public String spriteName = "";
    public String specialSpriteName = "";

    public boolean useInNormalPieces = false;
    public boolean useAsGarbage = false;
    public boolean useAsPlayingFieldFiller = false;
    public boolean ignoreWhenMovingDownBlocks = false;
    public boolean chainConnectionsMustContainAtLeastOneBlockWithThisTrue = false;
    public boolean ignoreWhenCheckingChainConnections = false;

    public ArrayList<BobColor> colors = new ArrayList<>();
    public BobColor specialColor = null;

    public int randomSpecialBlockChanceOneOutOf = 0;
    public int frequencySpecialBlockTypeOnceEveryNPieces = 0;

    public boolean flashingSpecialType = false;
    public int turnBackToNormalBlockAfterNPiecesLock = -1;

    public ArrayList<String> makePieceTypeWhenCleared_UUID = new ArrayList<>();

    public boolean clearEveryOtherLineOnGridWhenCleared = false;

    public boolean counterType = false;
    public boolean pacmanType = false;
    public boolean pacJarType = false;
    public int ticksToChangeDirection = 1000;

    public ArrayList<String> ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType_UUID = new ArrayList<>();
    public boolean addToChainIfConnectedUpDownLeftRightToExplodingChainBlocks = false;

    public ArrayList<TurnFromBlockTypeToType> whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut = new ArrayList<>();

    public boolean removeAllBlocksOfColorOnFieldBlockIsSetOn = false;
    public boolean changeAllBlocksOfColorOnFieldBlockIsSetOnToDiamondColor = false;
    public boolean matchAnyColor = false;

    public static BlockType emptyBlockType;
    public static BlockType squareBlockType;
    public static BlockType shotPieceBlockType;

    // TODO: Sprite integration
    // Sprite* sprite = nullptr;
    // Sprite* specialSprite = nullptr;

    public BlockType() {
        this.name = "empty";
        this.uuid = UUID.randomUUID().toString();
    }

    public BlockType(String name, String spriteName, String specialSpriteName, ArrayList<BobColor> colorsArray, BobColor specialColor, int randomSpecialBlockChanceOneOutOf, int frequencySpecialBlockTypeOnceEveryNBlocks) {
        this.name = name;
        this.spriteName = spriteName;
        this.specialSpriteName = specialSpriteName;
        if (colorsArray != null) {
            this.colors.addAll(colorsArray);
        }
        this.specialColor = specialColor;
        this.randomSpecialBlockChanceOneOutOf = randomSpecialBlockChanceOneOutOf;
        this.frequencySpecialBlockTypeOnceEveryNPieces = frequencySpecialBlockTypeOnceEveryNBlocks;
        this.uuid = UUID.randomUUID().toString();
    }

    public boolean isNormalType() {
        return useInNormalPieces;
    }

    public boolean isSpecialType() {
        if (randomSpecialBlockChanceOneOutOf != 0) return true;
        if (frequencySpecialBlockTypeOnceEveryNPieces != 0) return true;
        if (flashingSpecialType) return true;
        if (!makePieceTypeWhenCleared_UUID.isEmpty()) return true;
        if (clearEveryOtherLineOnGridWhenCleared) return true;
        return false;
    }
}
