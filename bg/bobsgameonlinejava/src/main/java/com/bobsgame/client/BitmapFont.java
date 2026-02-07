package com.bobsgame.client;

import org.lwjgl.BufferUtils;
import org.lwjgl.stb.STBTTAlignedQuad;
import org.lwjgl.stb.STBTTBakedChar;
import org.lwjgl.stb.STBTruetype;
import org.lwjgl.system.MemoryStack;

import java.nio.ByteBuffer;
import java.nio.FloatBuffer;
import java.nio.IntBuffer;
import java.io.IOException;

import static org.lwjgl.opengl.GL11.*;

import com.bobsgame.shared.BobColor;
import com.bobsgame.shared.Utils;

public class BitmapFont {
    private final int textureID;
    private final STBTTBakedChar.Buffer cdata;
    private final int BITMAP_W = 512;
    private final int BITMAP_H = 512;

    public BitmapFont(String fontPath, float size) throws IOException {
        cdata = STBTTBakedChar.malloc(96);

        textureID = glGenTextures();
        byte[] ttfData = Utils.getResourceAsBytes(fontPath);
        if (ttfData == null) throw new IOException("Font not found: " + fontPath);

        ByteBuffer bitmap = BufferUtils.createByteBuffer(BITMAP_W * BITMAP_H);
        ByteBuffer ttfBuffer = BufferUtils.createByteBuffer(ttfData.length);
        ttfBuffer.put(ttfData);
        ttfBuffer.flip();

        STBTruetype.stbtt_BakeFontBitmap(ttfBuffer, size, bitmap, BITMAP_W, BITMAP_H, 32, cdata);

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, BITMAP_W, BITMAP_H, 0, GL_ALPHA, GL_UNSIGNED_BYTE, bitmap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }

    public void drawString(float x, float y, String text, BobColor color) {
        if (text == null) return;

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);

        if (color != null) {
            glColor4f(color.r(), color.g(), color.b(), color.a());
        } else {
            glColor4f(1f, 1f, 1f, 1f);
        }

        glBegin(GL_QUADS);
        try (MemoryStack stack = MemoryStack.stackPush()) {
            FloatBuffer xpos = stack.floats(x);
            FloatBuffer ypos = stack.floats(y);
            STBTTAlignedQuad q = STBTTAlignedQuad.malloc(stack);

            for (int i = 0; i < text.length(); i++) {
                char c = text.charAt(i);
                if (c < 32 || c >= 128) continue;

                STBTruetype.stbtt_GetBakedQuad(cdata, BITMAP_W, BITMAP_H, c - 32, xpos, ypos, q, true);

                glTexCoord2f(q.s0(), q.t0());
                glVertex2f(q.x0(), q.y0());

                glTexCoord2f(q.s1(), q.t0());
                glVertex2f(q.x1(), q.y0());

                glTexCoord2f(q.s1(), q.t1());
                glVertex2f(q.x1(), q.y1());

                glTexCoord2f(q.s0(), q.t1());
                glVertex2f(q.x0(), q.y1());
            }
        }
        glEnd();
    }

    public int getWidth(String text) {
        if (text == null) return 0;
        float width = 0;
        try (MemoryStack stack = MemoryStack.stackPush()) {
            FloatBuffer xpos = stack.floats(0);
            FloatBuffer ypos = stack.floats(0);
            STBTTAlignedQuad q = STBTTAlignedQuad.malloc(stack);

            for (int i = 0; i < text.length(); i++) {
                char c = text.charAt(i);
                if (c < 32 || c >= 128) continue;

                STBTruetype.stbtt_GetBakedQuad(cdata, BITMAP_W, BITMAP_H, c - 32, xpos, ypos, q, true);
            }
            width = xpos.get(0);
        }
        return (int)width;
    }

    public void destroy() {
        glDeleteTextures(textureID);
        cdata.free();
    }
}
