package com.bobsgame.client;

import static org.lwjgl.opengl.GL11.*;
import java.nio.ByteBuffer;
import org.lwjgl.BufferUtils;

public class Texture {
    private int textureID;
    private int width;
    private int height;
    private int imageWidth;
    private int imageHeight;

    public Texture(int textureID, int width, int height) {
        this.textureID = textureID;
        this.width = width;
        this.height = height;
        this.imageWidth = width;
        this.imageHeight = height;
    }

    public int getTextureID() {
        return textureID;
    }

    public int getTextureWidth() {
        return width;
    }

    public int getTextureHeight() {
        return height;
    }

    public int getImageWidth() {
        return imageWidth;
    }

    public int getImageHeight() {
        return imageHeight;
    }

    public void setTextureWidth(int width) {
        this.width = width;
    }

    public void setTextureHeight(int height) {
        this.height = height;
    }

    public void setWidth(int width) {
        this.imageWidth = width;
    }

    public void setHeight(int height) {
        this.imageHeight = height;
    }

    public void setAlpha(boolean b) {
        // No-op for now
    }

    public void release() {
        glDeleteTextures(textureID);
    }

    public byte[] getTextureData() {
        ByteBuffer buffer = BufferUtils.createByteBuffer(width * height * 4);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
        byte[] data = new byte[width * height * 4];
        buffer.get(data);
        return data;
    }
}
