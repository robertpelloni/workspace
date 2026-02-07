package com.bobsgame.client;

import java.awt.Font;
import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.nio.FloatBuffer;
import java.nio.IntBuffer;
import org.lwjgl.BufferUtils;
import org.lwjgl.stb.STBImage;
import org.lwjgl.system.MemoryStack;
import org.slf4j.LoggerFactory;
import com.bobsgame.shared.BobColor;
import com.bobsgame.shared.Utils;

import ch.qos.logback.classic.Logger;
import org.lwjgl.opengl.GL11;
import org.lwjgl.opengl.GL12;
import org.lwjgl.opengl.GL14;

import static org.lwjgl.opengl.GL11.*;
import com.bobsgame.client.BitmapFont;

public class GLUtils {
	public static Logger log = (Logger) LoggerFactory.getLogger(GLUtils.class);

	public static BitmapFont font;

	static private boolean antiAlias = true;

	public static int texturesLoaded = 0;
	public static long textureBytesLoaded = 0;

	public static Texture blankTexture = null;
	public static Texture boxTexture = null;

	public final static int FILTER_FBO_LINEAR_NO_MIPMAPPING = -2;
	public final static int FILTER_FBO_NEAREST_NO_MIPMAPPING = -1;
	public final static int FILTER_NEAREST = 0;
	public final static int FILTER_LINEAR = 1;

	public static float globalDrawScale = 1.0f;

    public static class DummyFont {
        public int getWidth(String text) {
            if (text == null) return 0;
            return text.length() * 10;
        }

        public void drawString(float x, float y, String text, BobColor color) {
            // TODO
        }
    }

	public GLUtils() {
		blankTexture = GLUtils.loadTexture("res/misc/blank.png");
		boxTexture = GLUtils.loadTexture("res/misc/box.png");

		// load font from file
		try {
            // Initialize BitmapFont with a size (e.g., 8.0f or 16.0f depending on original scale)
            // Original code had: awtFont.deriveFont(8f);
            font = new BitmapFont("res/fonts/bobsgame.ttf", 16.0f);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static Texture loadTexture(String name, int imageWidth, int imageHeight, ByteBuffer textureByteBuffer) {
		// This method seems to be used when we already have the byte buffer, e.g. from network or generated?
        // For now, let's assume it's standard RGBA8

		int texWidth = Utils.getClosestPowerOfTwo(imageWidth);
		int texHeight = Utils.getClosestPowerOfTwo(imageHeight);

		int textureID = glGenTextures();
		Texture textureImpl = new Texture(textureID, texWidth, texHeight);
        textureImpl.setWidth(imageWidth);
        textureImpl.setHeight(imageHeight);

		glBindTexture(GL_TEXTURE_2D, textureID);

		//IntBuffer temp = BufferUtils.createIntBuffer(16);
		//glGetInteger(GL_MAX_TEXTURE_SIZE, temp);
		//int max = temp.get(0);
        int max = glGetInteger(GL_MAX_TEXTURE_SIZE);

		if ((texWidth > max) || (texHeight > max)) {
			try {
				throw new IOException("Attempt to allocate a texture too big for the current hardware");
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

		setDefaultTextureParams();

		glTexImage2D(
			GL_TEXTURE_2D, // type of texture we're creating
			0, // level-of-detail: use 0
			GL_RGBA8, // texture pixel format
			texWidth, texHeight, // width and height of texture image (powers of 2)
			0, // width of the border (either 0 or 1, use 0)
			GL_RGBA, // image pixel format
			GL_UNSIGNED_BYTE, // image pixel data type
			textureByteBuffer // image pixel data
		);

		texturesLoaded++;
		textureBytesLoaded += (texWidth * texHeight * 4);

		return textureImpl;
	}

	public static void setDefaultTextureParams() {
		glTexParameteri(GL_TEXTURE_2D, GL12.GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_2D, GL12.GL_TEXTURE_MAX_LEVEL, 2);//0=100% 1=50% 2=25%
		glTexParameteri(GL_TEXTURE_2D, GL14.GL_GENERATE_MIPMAP, GL_TRUE);
	}

	public static Texture loadTexture(String s) {
        // STB Image loading
        ByteBuffer imageBuffer;
        int width, height;

        try (MemoryStack stack = MemoryStack.stackPush()) {
            IntBuffer w = stack.mallocInt(1);
            IntBuffer h = stack.mallocInt(1);
            IntBuffer comp = stack.mallocInt(1);

            // Read file to ByteBuffer
            try {
                byte[] data = Utils.getResourceAsBytes(s);
                if (data == null) {
                    log.error("Could not load texture (not found): " + s);
                    return null;
                }
                ByteBuffer resourceBuffer = BufferUtils.createByteBuffer(data.length);
                resourceBuffer.put(data);
                resourceBuffer.flip();

                // Load image
                imageBuffer = STBImage.stbi_load_from_memory(resourceBuffer, w, h, comp, 4);
                if (imageBuffer == null) {
                    log.error("Could not decode texture: " + s + " Reason: " + STBImage.stbi_failure_reason());
                    return null;
                }

                width = w.get(0);
                height = h.get(0);
            } catch (Exception e) {
                e.printStackTrace();
                return null;
            }
        }

        // We need power of two textures for mipmaps if we want to stick to old GL logic,
        // but modern GL supports NPOT. However, let's stick to what the code expects if possible,
        // or just upload as is. The original code resized to POT.
        // STB loads the image as is. To resize to POT we would need to create a new buffer.
        // For simplicity let's try uploading as POT if we want to match old behavior,
        // OR rely on driver support for NPOT if we don't use strict mipmap generation that requires POT.
        // The old code used Utils.getClosestPowerOfTwo.

        int texWidth = Utils.getClosestPowerOfTwo(width);
        int texHeight = Utils.getClosestPowerOfTwo(height);

        // If we want to support POT, we need to pad.
        // Actually, let's just try using what we have. If it crashes we fix it.
        // Wait, `glTexImage2D` expects the buffer to match the dimensions provided.
        // If we say texWidth/texHeight but provide buffer of width/height, it will read garbage or crash if buffer is smaller.

        // Let's implement proper padding if needed, but for now let's see if we can just use the image dimensions directly
        // if we are willing to give up on POT requirements (which might break old shaders or wrap modes on old hardware, but this is 2024).
        // However, the drawing code `drawTexture` calculates ratios based on `getImageWidth` / `getTextureWidth`.
        // So we should probably maintain that distinction.

        // Simplest way: Use the image buffer as is, set texture width/height to image width/height.
        // But if the code relies on POT for tiling...

        // Let's assume modern hardware and use image dimensions as texture dimensions for now.
        // But wait, `GLUtils.drawTexture` uses:
		// float tXRatio = (float) texture.getImageWidth() / (float) texture.getTextureWidth();
        // If they are equal, ratio is 1.0.

        int textureID = glGenTextures();
        glBindTexture(GL_TEXTURE_2D, textureID);

        setDefaultTextureParams();

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageBuffer);

        STBImage.stbi_image_free(imageBuffer);

        Texture t = new Texture(textureID, width, height);
        t.setWidth(width);
        t.setHeight(height);

        texturesLoaded++;
        textureBytesLoaded += (width * height * 4);

        return t;
	}

	public static Texture releaseTexture(Texture t) {
        if (t == null) return null;
		texturesLoaded--;
		textureBytesLoaded -= (t.getTextureWidth() * t.getTextureHeight() * 4);
		t.release();
		return null;
	}

	public static FloatBuffer boxBuffer = BufferUtils.createFloatBuffer(12);
	public static FloatBuffer colBuffer = BufferUtils.createFloatBuffer(16);
	public static FloatBuffer texBuffer = BufferUtils.createFloatBuffer(8);

	static float box[] = new float[12];
	static float col[] = new float[16];
	static float tex[] = new float[8];

	public static void drawTexture(Texture texture, float sx0, float sy0, int filter) {
		drawTexture(texture,sx0,sy0,1.0f,filter);
	}

	public static void drawTexture(Texture texture, float sx0, float sy0, float alpha, int filter) {
        if (texture == null) return;
		float sx1 = sx0 + texture.getImageWidth();
		float sy1 = sy0 + texture.getImageHeight();
		drawTexture(texture, sx0, sx1, sy0, sy1, alpha, filter);
	}

	public static void drawTexture(Texture texture, float sx0, float sx1, float sy0, float sy1, float alpha, int filter) {
        if (texture == null) return;
		float tXRatio = (float) texture.getImageWidth() / (float) texture.getTextureWidth();
		float tYRatio = (float) texture.getImageHeight() / (float) texture.getTextureHeight();

		float ix0 = 0.0f;
		float ix1 = 1.0f;

		float iy0 = 0.0f;
		float iy1 = 1.0f;

		float tx0 = ix0 * tXRatio;
		float tx1 = ix1 * tXRatio;

		float ty0 = iy0 * tYRatio;
		float ty1 = iy1 * tYRatio;

		drawTexture(texture,tx0,tx1,ty0,ty1,sx0,sx1,sy0,sy1,alpha,filter);
	}

	public static void drawTexture(Texture texture, float tx0, float tx1, float ty0, float ty1, float sx0, float sx1, float sy0, float sy1, float alpha, int filter) {
		if (texture == null) {
			return;
		}
		drawTexture(texture.getTextureID(), tx0, tx1, ty0, ty1, sx0, sx1, sy0, sy1, alpha, filter);
	}

	public static void drawTexture(int textureID, float tx0, float tx1, float ty0, float ty1, float sx0, float sx1, float sy0, float sy1, float alpha, int filter) {
		glBindTexture(GL_TEXTURE_2D, textureID);
		drawTexture(tx0, tx1, ty0, ty1, sx0, sx1, sy0, sy1, 1.0f, 1.0f, 1.0f, alpha, filter);
	}

	public static void drawTexture(float tx0, float tx1, float ty0, float ty1, float sx0, float sx1, float sy0, float sy1, float alpha, int filter) {
		drawTexture(tx0, tx1, ty0, ty1, sx0, sx1, sy0, sy1, 1.0f, 1.0f, 1.0f, alpha, filter);
	}

	public static void drawTexture(Texture texture, float tx0, float tx1, float ty0, float ty1, float sx0, float sx1, float sy0, float sy1, float r, float g, float b, float a, int filter) {
        if (texture == null) return;
		glBindTexture(GL_TEXTURE_2D, texture.getTextureID());
		drawTexture(tx0, tx1, ty0, ty1, sx0, sx1, sy0, sy1, r, g, b, a, filter);
	}

	public static void drawTexture(float textureX0, float textureX1, float textureY0, float textureY1, float screenX0, float screenX1, float screenY0, float screenY1, float r, float g, float b, float a, int filter) {
		screenX0 *= globalDrawScale;
		screenX1 *= globalDrawScale;
		screenY0 *= globalDrawScale;
		screenY1 *= globalDrawScale;

		glEnable(GL_TEXTURE_2D);

		if (filter == FILTER_FBO_LINEAR_NO_MIPMAPPING) { // for FBO rendering only
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		} else if (filter == FILTER_FBO_NEAREST_NO_MIPMAPPING) { //for FBO rendering only
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		} else if (filter == FILTER_NEAREST) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			//if(Keyboard.isKeyDown(Keyboard.KEY_1))glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		} else if (filter == FILTER_LINEAR) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL12.GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL12.GL_CLAMP_TO_EDGE);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL12.GL_CLAMP_TO_EDGE); // TODO: what does this do and why did i comment it out? i forget.

		box[0] = screenX0;
		box[1] = screenY0;
		box[2] = 0.0f;
		box[3] = screenX0;
		box[4] = screenY1;
		box[5] = 0.0f;
		box[6] = screenX1;
		box[7] = screenY1;
		box[8] = 0.0f;
		box[9] = screenX1;
		box[10] = screenY0;
		box[11] = 0.0f;

		boxBuffer.put(box);
		boxBuffer.position(0);

		col[0] = r;
		col[1] = g;
		col[2] = b;
		col[3] = a;

		col[4] = r;
		col[5] = g;
		col[6] = b;
		col[7] = a;

		col[8] = r;
		col[9] = g;
		col[10] = b;
		col[11] = a;

		col[12] = r;
		col[13] = g;
		col[14] = b;
		col[15] = a;

		colBuffer.put(col);
		colBuffer.position(0);

		tex[0] = textureX0;
		tex[1] = textureY0;
		tex[2] = textureX0;
		tex[3] = textureY1;
		tex[4] = textureX1;
		tex[5] = textureY1;
		tex[6] = textureX1;
		tex[7] = textureY0;

		texBuffer.put(tex);
		texBuffer.position(0);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, boxBuffer);
		glColorPointer(4, GL_FLOAT, 0, colBuffer);
		glTexCoordPointer(2, GL_FLOAT, 0, texBuffer);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	public static void drawOutlinedString(String text, int screenX, int screenY, BobColor color) {
		drawOutlinedString(screenX, screenY, text, color);
	}

	public static void drawOutlinedString(int screenX0, int screenY0, String text, BobColor color) {
        // TODO: Reimplement Font rendering using STB Truetype or similar
		if (font == null) {
			log.error("Font is null");
			return;
		}

		if (text == null) {
			log.error("Text is null");
			return;
		}

        float sx = screenX0 * globalDrawScale;
        float sy = screenY0 * globalDrawScale;

        // Save GL state
        glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_TEXTURE_BIT | GL_TRANSFORM_BIT);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();

		{
            // Simple outline by drawing black offsets
			font.drawString(sx-1, sy-1, text, BobColor.black);
			font.drawString(sx+1, sy-1, text, BobColor.black);
			font.drawString(sx-1, sy+1, text, BobColor.black);
			font.drawString(sx+1, sy+1, text, BobColor.black);
			font.drawString(sx+1, sy, text, BobColor.black);
			font.drawString(sx-1, sy, text, BobColor.black);
			font.drawString(sx, sy+1, text, BobColor.black);
			font.drawString(sx, sy-1, text, BobColor.black);

			font.drawString(sx, sy, text, color);
		}

        // Restore GL state
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glPopAttrib();
	}

	public static void drawLine(float screenX0, float screenY0, float screenX1, float screenY1, int r, int g, int b) {
		drawLine(screenX0, screenY0, screenX1, screenY1, r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
	}

	public static void drawLine(float screenX0, float screenY0, float screenX1, float screenY1, float r, float g, float b) {
		drawLine(screenX0, screenY0, screenX1, screenY1, r, g, b, 1.0f);
	}

	public static void drawLine(float screenX0, float screenY0, float screenX1, float screenY1, float r, float g, float b, float a) {
		screenX0 *= globalDrawScale;
		screenX1 *= globalDrawScale;
		screenY0 *= globalDrawScale;
		screenY1 *= globalDrawScale;

		glDisable(GL_TEXTURE_2D);

		glColor4f(r, g, b, a);

		glBegin(GL_LINES);
		glVertex2f(screenX0, screenY0);
		glVertex2f(screenX1, screenY1);
		glEnd();
	}

	public static void drawArrowLine(float screenX0, float screenY0, float screenX1, float screenY1, int r, int g, int b) {
		drawLine(screenX0, screenY0, screenX1, screenY1, r, g, b);

		screenX0 *= globalDrawScale;
		screenX1 *= globalDrawScale;
		screenY0 *= globalDrawScale;
		screenY1 *= globalDrawScale;

		float dx = (screenX1 - screenX0);
		float dy = (screenY1 - screenY0);

		float midX = (screenX0 + dx / 2);
		float midY = (screenY0 + dy / 2);

		dx /= 2;
		dy /= 2;

		float dist = (float) Math.sqrt(dx * dx + dy * dy);

		float distXRatio = dx / dist;
		float distYRatio = dy / dist;

		int arrowWidth = 12;

		float midXPerpX1 = (midX + (arrowWidth / 2) * distYRatio);
		float midYPerpY1 = (midY - (arrowWidth / 2) * distXRatio);
		float midXPerpX2 = (midX - (arrowWidth / 2) * distYRatio);
		float midYPerpY2 = (midY + (arrowWidth / 2) * distXRatio);

		float pastMidX = (screenX0 + (dist + 16) * distXRatio);
		float pastMidY = (screenY0 + (dist + 16) * distYRatio);

		drawLine(midXPerpX1, midYPerpY1, midXPerpX2, midYPerpY2, r, g, b);
		drawLine(midXPerpX1, midYPerpY1, pastMidX, pastMidY, r, g, b);
		drawLine(midXPerpX2, midYPerpY2, pastMidX, pastMidY, r, g, b);
	}

	public static void drawBox(float screenX0, float screenX1, float screenY0, float screenY1, int r, int g, int b) {
		screenX0 *= globalDrawScale;
		screenX1 *= globalDrawScale;
		screenY0 *= globalDrawScale;
		screenY1 *= globalDrawScale;


		glColor3f(r / 255.0f,g / 255.0f,b / 255.0f);

		glBegin(GL_LINES);

		glVertex2f(screenX0, screenY0);
		glVertex2f(screenX1, screenY0);

		glVertex2f(screenX0, screenY1);
		glVertex2f(screenX1, screenY1);

		glVertex2f(screenX0, screenY0);
		glVertex2f(screenX0, screenY1);

		glVertex2f(screenX1, screenY0);
		glVertex2f(screenX1, screenY1);

		glEnd();
	}

	public static void drawFilledRect(int ri, int gi, int bi, float screenX0, float screenX1, float screenY0, float screenY1, float alpha) {
		screenX0 *= globalDrawScale;
		screenX1 *= globalDrawScale;
		screenY0 *= globalDrawScale;
		screenY1 *= globalDrawScale;

		glDisable(GL_TEXTURE_2D);

		glColor4f(ri / 255.0f,gi / 255.0f,bi / 255.0f, alpha);

		box[0] = screenX0;
		box[1] = screenY0;
		box[2] = 0.0f;
		box[3] = screenX0;
		box[4] = screenY1;
		box[5] = 0.0f;
		box[6] = screenX1;
		box[7] = screenY1;
		box[8] = 0.0f;
		box[9] = screenX1;
		box[10] = screenY0;
		box[11] = 0.0f;

		boxBuffer.put(box);
		boxBuffer.position(0);

		glEnableClientState(GL_VERTEX_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0,  boxBuffer);
		glDrawArrays(GL_TRIANGLE_FAN,0,4);

		glDisableClientState(GL_VERTEX_ARRAY);
	}

	public static void drawFilledRectXYWH(float x, float y, float w, float h, float r, float g, float b, float a) {
		drawFilledRect((int) (r * 255.0f), (int) (g * 255.0f), (int) (b * 255.0f), x, x + w, y, y + h, a);
	}
}
