package com.bobsgame.client;


import static org.lwjgl.opengl.ARBFramebufferObject.*;
import static org.lwjgl.opengl.EXTFramebufferObject.*;


import static org.lwjgl.opengl.ARBFragmentShader.*;
import static org.lwjgl.opengl.ARBVertexShader.*;
import static org.lwjgl.opengl.ARBShaderObjects.*;


import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.opengl.GL12.*;
import static org.lwjgl.opengl.GL20.*;


import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.IntBuffer;
import java.util.ArrayList;

import com.bobsgame.ClientMain;
import de.matthiasmann.twl.input.Input;
import de.matthiasmann.twl.input.lwjgl.LWJGLInput;
import org.lwjgl.PointerBuffer;
import org.lwjgl.glfw.GLFW;
import org.lwjgl.glfw.GLFWImage;
import org.lwjgl.glfw.GLFWVidMode;
import org.lwjgl.opengl.*;
import org.lwjgl.stb.STBImage;
import org.lwjgl.glfw.GLFWVidMode;
import org.lwjgl.opengl.*;
import org.lwjgl.system.MemoryStack;
import org.slf4j.LoggerFactory;

import ch.qos.logback.classic.Logger;

import com.bobsgame.client.engine.game.nd.ND;
import com.bobsgame.shared.BobColor;
import com.bobsgame.shared.Utils;

import de.matthiasmann.twl.renderer.lwjgl.LWJGLRenderer;
import de.matthiasmann.twl.theme.ThemeManager;


//=========================================================================================================================
public class LWJGLUtils
{//=========================================================================================================================


	public static Logger log = (Logger) LoggerFactory.getLogger(LWJGLUtils.class);
    public static long window;
    public static LWJGLInput twlInput;


	//=========================================================================================================================
	public LWJGLUtils()
	{//=========================================================================================================================



	}

	/**
	 * Set the display mode to be used
	 * @param width The width of the display required
	 * @param height The height of the display required
	 * @param fullscreen True if we want fullscreen mode
	 */
	public static void setFullscreenCompatibleDisplayMode(int width, int height, boolean fullscreen) {
        // TODO: Implement GLFW window resize/fullscreen toggle if needed
	}

	public static int SCREEN_SIZE_X = 1280;
	public static int SCREEN_SIZE_Y = 720;

	public static boolean vsync = true;

	public static boolean useShader = true;
	public static int lightShader = 0;
	public static int colorShader = 0;

	public static ArrayList<Integer> bgShaders = new ArrayList<>();

	public static int bgShaderCount = 61;

	public static int gaussianShader = 0;
	public static int maskShader = 0;
	public static int bloomShader = 0;

	public static boolean useFBO = true;

	public static int mainFBO_lightTexture;
	public static int mainFBO_Texture;

	public static int nDFBO_Texture;
	public static int nDFBO_MaskTexture;

	public static int nDBloomFBO_Texture_0;
	public static int nDBloomFBO_Texture_1;

	public static int nDBGFBO_Texture_0;
	public static int nDBGFBO_Texture_1;
	//static public int miniMapFBOTextureID;

	public static int mainFBO;
	public static int nDFBO;
	public static int nDBloomFBO;
	public static int nDBGFBO;
	//static public int miniMapFBOID;

	public static int nDBGFBOWidth = 640;
	public static int nDBGFBOHeight = 480;


	//public int lightFBOID;
	//public int depthRenderBufferID;


	//private AWTGLCanvas canvas;

	public static int desktopDisplayWidth = 0;
	public static int desktopDisplayHeight = 0;
	public static int desktopDisplayBPP = 0;
	public static int desktopDisplayFreq = 0;

	public static void setDisplayMode() {
        if (!GLFW.glfwInit()) {
            throw new IllegalStateException("Unable to initialize GLFW");
        }

        GLFWVidMode vidMode = GLFW.glfwGetVideoMode(GLFW.glfwGetPrimaryMonitor());
        if (vidMode != null) {
            desktopDisplayWidth = vidMode.width();
            desktopDisplayHeight = vidMode.height();
            desktopDisplayBPP = vidMode.redBits() + vidMode.greenBits() + vidMode.blueBits();
            desktopDisplayFreq = vidMode.refreshRate();
        }
	}

	public static void setViewport() {
		glViewport(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y);
		glLoadIdentity();
		glOrtho(0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0, -1, 1);
	}

	public static void initGL(String windowName) {

        GLFW.glfwDefaultWindowHints();
        GLFW.glfwWindowHint(GLFW.GLFW_VISIBLE, GLFW.GLFW_FALSE);
        GLFW.glfwWindowHint(GLFW.GLFW_RESIZABLE, GLFW.GLFW_TRUE);

        window = GLFW.glfwCreateWindow(SCREEN_SIZE_X, SCREEN_SIZE_Y, windowName, 0, 0);
        if (window == 0) {
            throw new RuntimeException("Failed to create the GLFW window");
        }

        try (MemoryStack stack = MemoryStack.stackPush()) {
            IntBuffer pWidth = stack.mallocInt(1);
            IntBuffer pHeight = stack.mallocInt(1);

            GLFW.glfwGetWindowSize(window, pWidth, pHeight);

            GLFWVidMode vidmode = GLFW.glfwGetVideoMode(GLFW.glfwGetPrimaryMonitor());

            GLFW.glfwSetWindowPos(
                    window,
                    (vidmode.width() - pWidth.get(0)) / 2,
                    (vidmode.height() - pHeight.get(0)) / 2
            );
        }

        GLFW.glfwMakeContextCurrent(window);
        if (vsync) {
            GLFW.glfwSwapInterval(1);
        } else {
            GLFW.glfwSwapInterval(0);
        }

        GLFW.glfwSetWindowSizeCallback(window, (window, width, height) -> {
            doResize();
        });

        // Set window icon
        try (MemoryStack stack = MemoryStack.stackPush()) {
            IntBuffer w = stack.mallocInt(1);
            IntBuffer h = stack.mallocInt(1);
            IntBuffer comp = stack.mallocInt(1);

            // Use the icon from the resources
            java.nio.ByteBuffer iconBuf = Utils.ioResourceToByteBuffer("res/nD/nDicon.png", 1024);
            if (iconBuf != null) {
                java.nio.ByteBuffer pixels = STBImage.stbi_load_from_memory(iconBuf, w, h, comp, 4);
                if (pixels != null) {
                    GLFWImage.Buffer icons = GLFWImage.malloc(1, stack);
                    icons.position(0).width(w.get(0)).height(h.get(0)).pixels(pixels);
                    GLFW.glfwSetWindowIcon(window, icons);
                    STBImage.stbi_image_free(pixels);
                } else {
                    log.warn("Could not load icon: res/nD/nDicon.png");
                }
            } else {
                log.warn("Could not find icon: res/nD/nDicon.png");
            }
        } catch (Exception e) {
            log.error("Error setting window icon: " + e.getMessage());
        }

        GLFW.glfwShowWindow(window);

        GL.createCapabilities();

			log.info("Setting up GL...");

			log.info("GL vendor: " + glGetString(GL_VENDOR));
			log.info("GL version: " + glGetString(GL_VERSION));
			log.info("Renderer: " + glGetString(GL_RENDERER));
			log.info("Shader version: " + glGetString(GL_SHADING_LANGUAGE_VERSION));
			log.info("Extensions: " + glGetString(GL_EXTENSIONS));


			glEnable(GL_BLEND);


			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);


			glDisable(GL_SCISSOR_TEST);
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_LIGHTING);


			setViewport();


			log.info("Setting up FBO...");

			// check if GL_ARB_framebuffer_object can be use on this system

			if (GL.getCapabilities().GL_EXT_framebuffer_object) {
				useFBO = true;
				ARBFBO = false;
				log.info("EXT FBO supported.");
			} else if (GL.getCapabilities().GL_ARB_framebuffer_object) {
				useFBO = true;
				ARBFBO = true;
				log.info("EXT FBO not supported. Using ARB FBO.");
			} else {
				log.error("FBO not supported.");
				useFBO = false;

				new GLUtils();

				GLUtils.drawFilledRect(0, 0, 0, 0, 1280, 0, 720, 0.5f);
				GLUtils.drawOutlinedString("Your graphics card is not supported yet. (Needs FBO support.)", 1280 / 2 - 100, 720 / 2 - 12, BobColor.white);

				//Display.update();
                updateDisplay();

				try {
					Thread.sleep(5000);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}

				ClientMain.exit();
			}

			{
				// generate FBOs
				mainFBO = LWJGLUtils.genFBO();
				LWJGLUtils.bindFBO(mainFBO);

				mainFBO_Texture = LWJGLUtils.setupFBOTexture(glGenTextures(), SCREEN_SIZE_X, SCREEN_SIZE_Y);
				LWJGLUtils.attachTextureToFBO(0,mainFBO_Texture);

				mainFBO_lightTexture = LWJGLUtils.setupFBOTexture(glGenTextures(), SCREEN_SIZE_X, SCREEN_SIZE_Y);
				LWJGLUtils.attachTextureToFBO(1, mainFBO_lightTexture);

				//=================================

				nDFBO = LWJGLUtils.genFBO();
				LWJGLUtils.bindFBO(nDFBO);

				nDFBO_Texture = LWJGLUtils.setupFBOTexture(glGenTextures(), ND.SCREEN_SIZE_X * ND.FBO_SCALE_MULTIPLIER, ND.SCREEN_SIZE_Y * ND.FBO_SCALE_MULTIPLIER);
				LWJGLUtils.attachTextureToFBO(0, nDFBO_Texture);

				nDFBO_MaskTexture = LWJGLUtils.setupFBOTexture(glGenTextures(), ND.SCREEN_SIZE_X * ND.FBO_SCALE_MULTIPLIER, ND.SCREEN_SIZE_Y * ND.FBO_SCALE_MULTIPLIER);
				LWJGLUtils.attachTextureToFBO(1, nDFBO_MaskTexture);

				//=================================

				nDBloomFBO = LWJGLUtils.genFBO();
				LWJGLUtils.bindFBO(nDBloomFBO);

				nDBloomFBO_Texture_0 = LWJGLUtils.setupFBOTexture(glGenTextures(), (int) (ND.SCREEN_SIZE_X * ND.FBO_SCALE_MULTIPLIER * ND.BLOOM_FBO_SCALE), (int) (ND.SCREEN_SIZE_Y * ND.FBO_SCALE_MULTIPLIER * ND.BLOOM_FBO_SCALE));
				LWJGLUtils.attachTextureToFBO(0, nDBloomFBO_Texture_0);

				nDBloomFBO_Texture_1 = LWJGLUtils.setupFBOTexture(glGenTextures(), (int) (ND.SCREEN_SIZE_X * ND.FBO_SCALE_MULTIPLIER * ND.BLOOM_FBO_SCALE), (int) (ND.SCREEN_SIZE_Y * ND.FBO_SCALE_MULTIPLIER * ND.BLOOM_FBO_SCALE));
				LWJGLUtils.attachTextureToFBO(1, nDBloomFBO_Texture_1);

				//=================================

				nDBGFBO = LWJGLUtils.genFBO();
				LWJGLUtils.bindFBO(nDBGFBO);

				nDBGFBO_Texture_0 = LWJGLUtils.setupFBOTexture(glGenTextures(), nDBGFBOWidth, nDBGFBOHeight);
				LWJGLUtils.attachTextureToFBO(0, nDBGFBO_Texture_0);

				nDBGFBO_Texture_1 = LWJGLUtils.setupFBOTexture(glGenTextures(), nDBGFBOWidth, nDBGFBOHeight);
				LWJGLUtils.attachTextureToFBO(1, nDBGFBO_Texture_1);

				//bind the depth renderbuffer
				//glBindRenderbuffer(GL_RENDERBUFFER, depthRenderBufferID);
				//get the data space for it
				//glRenderbufferStorage(GL_RENDERBUFFER, GL14.GL_DEPTH_COMPONENT24, 512, 512);
				//bind it to the renderbuffer
				//glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER, depthRenderBufferID);

				//switch back to normal framebuffer
				LWJGLUtils.bindFBO(0);
			}

			checkForGLError();

			log.info("Setting up shaders...");

			String glVersion = glGetString(GL_VERSION);
			//String shaderVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
			//String glExtensions = glGetString(GL_EXTENSIONS);

			boolean hasARBShadingLanguage100 = GL.getCapabilities().GL_ARB_shading_language_100;
			boolean hasARBFragmentShader = GL.getCapabilities().GL_ARB_fragment_shader;
			boolean hasARBVertexShader = GL.getCapabilities().GL_ARB_vertex_shader;
			boolean hasARBShaderObjects = GL.getCapabilities().GL_ARB_shader_objects;
			boolean hasARBFragmentProgram = GL.getCapabilities().GL_ARB_fragment_program;
			//boolean hasNVVertexProgram3 = GL.getCapabilities().GL_NV_vertex_program3;
			//boolean hasNVGPUProgram4 = GL.getCapabilities().GL_NV_gpu_program4;

//			boolean extensionsStringHasARBShadingLanguage = glExtensions.contains("GL_ARB_shading_language_100");
//			boolean extensionsStringHasARBFragmentShader = glExtensions.contains("GL_ARB_fragment_shader");
//			boolean extensionsStringHasARBVertexShader = glExtensions.contains("GL_ARB_vertex_shader");
//			boolean extensionsStringHasARBShaderObjects = glExtensions.contains("GL_ARB_shader_objects");
//			boolean extensionsStringHasARBFragmentProgram = glExtensions.contains("GL_ARB_fragment_program");
//			boolean extensionsStringHasNVVertexProgram3 = glExtensions.contains("GL_NV_vertex_program3");
//			boolean extensionsStringHasNVGPUProgram4 = glExtensions.contains("GL_NV_gpu_program4");

			int glVersionMajor = 0;
			glVersionMajor = Integer.parseInt(glVersion.substring(0, glVersion.indexOf(".")));

//			log.info("glVersion:"+glVersion);
//			log.info("shaderVersion:"+shaderVersion);
//			log.info("glExtensions:"+glExtensions);
			log.info("glVersionMajor:" + glVersionMajor);
			log.info("Shader version: " + glGetString(GL_SHADING_LANGUAGE_VERSION));

			log.info("hasARBShadingLanguage100 (GLSL 1.00):" + hasARBShadingLanguage100);
			log.info("hasARBFragmentShader (GLSL 1.00):" + hasARBFragmentShader);
			log.info("hasARBVertexShader (GLSL 1.00):" + hasARBVertexShader);
			log.info("hasARBShaderObjects (GLSL 1.00):" + hasARBShaderObjects);
			log.info("shadingVersionExists (GLSL 1.051):" + (glGetString(GL_SHADING_LANGUAGE_VERSION).equals("0") == false));

			log.info("hasARBFragmentProgram (SM 2):" + hasARBFragmentProgram);
			//log.info("hasNVVertexProgram3 (SM 3):" + hasNVVertexProgram3);
			//log.info("hasNVGPUProgram4 (SM 4):" + hasNVGPUProgram4);
//			log.info("extensionsStringHasARBShadingLanguage:"+extensionsStringHasARBShadingLanguage);
//			log.info("extensionsStringHasARBFragmentShader:"+extensionsStringHasARBFragmentShader);
//			log.info("extensionsStringHasARBVertexShader:"+extensionsStringHasARBVertexShader);
//			log.info("extensionsStringHasARBShaderObjects:"+extensionsStringHasARBShaderObjects);
//			log.info("extensionsStringHasARBFragmentProgram:"+extensionsStringHasARBFragmentProgram);
//			log.info("extensionsStringHasNVVertexProgram3:"+extensionsStringHasNVVertexProgram3);
//			log.info("extensionsStringHasNVGPUProgram4:"+extensionsStringHasNVGPUProgram4);

			if (glVersionMajor < 2) useShader = false;

			if (useShader) {
				lightShader = LWJGLUtils.createProgramObject();
				colorShader = LWJGLUtils.createProgramObject();
				gaussianShader = LWJGLUtils.createProgramObject();
				maskShader = LWJGLUtils.createProgramObject();
				bloomShader = LWJGLUtils.createProgramObject();

				if (LWJGLUtils.makeShader("lightShader", lightShader, "res/shaders/texCoord.vert", "res/shaders/lightBlend.frag") == false) useShader = false;
				if (LWJGLUtils.makeShader("colorShader", colorShader, "res/shaders/texCoord.vert", "res/shaders/colorAdjust.frag") == false) useShader = false;
				if (LWJGLUtils.makeShader("gaussianShader", gaussianShader, "res/shaders/bloom_blurspace.vert", "res/shaders/bloom_alpha_gaussian.frag") == false) useShader = false;
				if (LWJGLUtils.makeShader("maskShader", maskShader, "res/shaders/bloom_screenspace.vert", "res/shaders/bloom_alpha_threshold.frag") == false) useShader = false;
				if (LWJGLUtils.makeShader("bloomShader", bloomShader, "res/shaders/bloom_screenspace.vert", "res/shaders/bloom_alpha_bloom.frag") == false) useShader = false;

				if (useShader) {
					for (int i = 0; i < bgShaderCount; i++) {
						int p = LWJGLUtils.createProgramObject();
						bgShaders.add(Integer.valueOf(p));
					}

					int count = 0;

					for (int i = 0; i < bgShaderCount; i++) {
						String name = count + ".frag";
						if (count < 10) name = "0" + name;

						if (LWJGLUtils.makeShader(name, bgShaders.get(i).intValue(), "res/shaders/texCoord.vert", "res/shaders/bg/" + name) == false) {
							bgShaderCount--;
							bgShaders.remove(i);
							i--;
						}

						count++;
					}
				}
			} else {
				useShader = false;
			}

			if (useShader == false) {
				log.warn("Shaders not supported.");
			}


		log.info("GL Complete.");
	}

	private static void attachTextureToFBO(int attachment, int textureID) {
		if (ARBFBO) {
			if (attachment == 0) {
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
			} else {
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, textureID, 0);
			}
		} else {
			if (attachment == 0) {
				glFramebufferTexture2DEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, textureID, 0);
			}
			glFramebufferTexture2DEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1_EXT, GL_TEXTURE_2D, textureID, 0);
		}
	}

	public static boolean ARBFBO = false;

	public static void bindFBO(int fboID) {
		if (ARBFBO) {
			glBindFramebuffer(GL_FRAMEBUFFER, fboID);
		} else {
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboID);
		}
	}

	public static void drawIntoFBOAttachment(int i) {
		if (ARBFBO) {
			if (i == 0) {
				glDrawBuffer(GL_COLOR_ATTACHMENT0);
			} else {
				glDrawBuffer(GL_COLOR_ATTACHMENT1);
			}
		} else {
			if (i == 0) {
				glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
			} else {
				glDrawBuffer(GL_COLOR_ATTACHMENT1_EXT);
			}
		}
	}

	public static int genFBO() {
		if (ARBFBO) {
			return glGenFramebuffers();
		} else {
			return glGenFramebuffersEXT();
		}
	}

	public static int setupFBOTexture(int tex, int width, int height) {
		// init FBO texture
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (java.nio.ByteBuffer) null);
		return tex;
	}

	public static boolean ARBShader = false;

	public static int createProgramObject() {
		int i = 0;
		if (useShader == true) {
			if (ARBShader == false) {
				i = glCreateProgram();
				checkForGLError();
				if (i == 0) {
					ARBShader = true;
					log.error("Core shaders failed. Trying ARB shaders.");
				}
			}
			if (ARBShader == true) {
				i = glCreateProgramObjectARB();
				checkForGLError();
				if (i == 0) {
					useShader = false;
					log.error("ARB shaders failed. Using no shaders.");
				}
			}
		}
		return i;
	}

	public static final int FRAG = 0;
	public static final int VERT = 1;

	private static int compileShaderObject(String filename, int type) {
		// will be non zero if successfully created
		int shader = 0;

		if (type == FRAG) {
			if (ARBShader) {
				shader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
			} else {
				shader = glCreateShader(GL_FRAGMENT_SHADER);
			}
		} else {
			if (ARBShader) {
				shader = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
			} else {
				shader = glCreateShader(GL_VERTEX_SHADER);
			}
		}

		checkForGLError();

		// if created, convert the shader code to a String
		if (shader == 0) return 0;

		String code = "";
		String line;

		try {
			BufferedInputStream inputStream = new BufferedInputStream(Utils.getResourceAsStream(filename));
			//InputStream inputStream = Utils.getResourceAsStream(filename);
			BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream, "UTF-8"));

			//BufferedReader reader=new BufferedReader(new FileReader(filename));
			while ((line=reader.readLine()) != null) {
				code += line + "\n";
			}
			reader.close();
		} catch (Exception e) {
			log.error("Could not read code: " + filename);
			return 0;
		}

		if (ARBShader) {
			glShaderSourceARB(shader, code);
			checkForGLError();
			glCompileShaderARB(shader);
			checkForGLError();

			//if there was a problem compiling, reset to zero
			if (glGetObjectParameteriARB(shader, GL_OBJECT_COMPILE_STATUS_ARB) == GL_FALSE) {
				checkForGLError();
				int logLength = glGetObjectParameteriARB(shader,GL_OBJECT_INFO_LOG_LENGTH_ARB);
				checkForGLError();
				if (logLength > 0) {
					String out = glGetInfoLogARB(shader, 1024);
					checkForGLError();
					if (out.length() > 0) {
						out = out.substring(0, out.length() - 1); // remove extra newline
					}
					log.error("ShaderInfoLogARB: "+out);
				}
				shader = 0;
			}
		} else {
			glShaderSource(shader, code);
			checkForGLError();
			glCompileShader(shader);
			checkForGLError();

			//if there was a problem compiling, reset to zero
			if (glGetShaderi(shader, GL_COMPILE_STATUS) == GL_FALSE) {
				checkForGLError();

				int logLength = glGetShaderi(shader, GL_INFO_LOG_LENGTH);
				checkForGLError();
				if (logLength > 0) {
					String out = glGetShaderInfoLog(shader, 1024);
					checkForGLError();
					if (out.length() > 0) out = out.substring(0, out.length() - 1); // remove extra newline
					log.error("ShaderInfoLog: " + out);
				}
				shader = 0;
			}
		}

		// if zero we won't be using the shader
		return shader;
	}

	public static boolean makeShader(String name, int shaderProgram, String vertPath, String fragPath) {
		int vertShader = 0;
		int fragShader = 0;

		vertShader = LWJGLUtils.compileShaderObject(vertPath, VERT);
		fragShader = LWJGLUtils.compileShaderObject(fragPath, FRAG);

		if (vertShader != 0 && fragShader != 0) {
			if (ARBShader) {
				glAttachObjectARB(shaderProgram, vertShader);
				checkForGLError();
				glAttachObjectARB(shaderProgram, fragShader);
				checkForGLError();
				glLinkProgramARB(shaderProgram);
				checkForGLError();
				glValidateProgramARB(shaderProgram);
				checkForGLError();
			} else {
				glAttachShader(shaderProgram, vertShader);
				checkForGLError();
				glAttachShader(shaderProgram, fragShader);
				checkForGLError();
				glLinkProgram(shaderProgram);
				checkForGLError();
				glValidateProgram(shaderProgram);
				checkForGLError();
			}

			String out = "";

			if (ARBShader) {
				int logLength = glGetObjectParameteriARB(shaderProgram, GL_OBJECT_INFO_LOG_LENGTH_ARB);
				checkForGLError();
				if (logLength > 0) {
					out = glGetInfoLogARB(shaderProgram, 1024);
					checkForGLError();
					if (out.length() > 0) out = out.substring(0, out.length() - 1);//remove extra newline
					out = ("ProgramInfoLog: " + out);
				}
			} else {
				int logLength = glGetProgrami(shaderProgram, GL_INFO_LOG_LENGTH);
				checkForGLError();
				if (logLength > 0) {
					out = glGetProgramInfoLog(shaderProgram, 1024);
					checkForGLError();
					if (out.length() > 0) out = out.substring(0, out.length() - 1);//remove extra newline
					out = ("ProgramInfoLog: "+out);
				}
			}

			if (out.toLowerCase().contains("error")) {
				log.warn(name + " status: " + out);
				return false;
			} else {
				return true;
			}
		} else {
			log.error(name + " did not compile!");
			return false;
		}
	}

	public static void checkForGLError() {
        int err = glGetError();
        if (err != GL_NO_ERROR) {
            log.error("GL Error: " + err);
        }
	}

	public static void useShader(int shader) {
		//if(useShader==false)return;
		if (ARBShader) {
			glUseProgramObjectARB(shader);
		} else {
			glUseProgram(shader);
		}
	}

	public static LWJGLRenderer TWLrenderer = null;
	public static ThemeManager TWLthemeManager = null;

	public static void initTWL() {
		log.info("Init TWL...");
		try {
			TWLrenderer = new LWJGLRenderer();
            twlInput = (LWJGLInput)TWLrenderer.getInput();
		} catch (Exception e) {
			e.printStackTrace();
		}

		log.info("Load Theme...");
		try {
			TWLthemeManager = ThemeManager.createThemeManager(Utils.getResource("res/theme/themetest.xml"), TWLrenderer);
		} catch (IOException e) {
			e.printStackTrace();
		}
		log.info("Theme Loaded.");
	}

	public static int numControllers = 0;
	public static String controllerNames = "";

	public static void initControllers() {
        // Joystick support in GLFW is handled differently.
        // We can check present joysticks.
		log.info("Init Controllers...");

		numControllers = 0;
		controllerNames = "";

        for (int i = GLFW.GLFW_JOYSTICK_1; i <= GLFW.GLFW_JOYSTICK_LAST; i++) {
            if (GLFW.glfwJoystickPresent(i)) {
                numControllers++;
                String name = GLFW.glfwGetJoystickName(i);
                log.info("Joystick " + i + ": " + name);
                if (controllerNames.length() > 0) controllerNames += "," + name;
                else controllerNames += name;
            }
        }

		log.info(numControllers+" Controllers Found");
		log.info("Controllers Loaded.");
	}

	public static void doResize() {
        try (MemoryStack stack = MemoryStack.stackPush()) {
            IntBuffer width = stack.mallocInt(1);
            IntBuffer height = stack.mallocInt(1);
            GLFW.glfwGetWindowSize(window, width, height);
            SCREEN_SIZE_X = width.get(0);
            SCREEN_SIZE_Y = height.get(0);
        }

		//order does matter
		glLoadIdentity();//reset selected transform matrix
		glOrtho(0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0, -1, 1);

		glViewport(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y);//order doesn't matter

		//fix FBO sizes

		//switch to the new framebuffer
		LWJGLUtils.bindFBO(mainFBO);

		mainFBO_Texture = LWJGLUtils.setupFBOTexture(mainFBO_Texture,(int)(SCREEN_SIZE_X), (int)(SCREEN_SIZE_Y));
		LWJGLUtils.attachTextureToFBO(0, mainFBO_Texture);


		mainFBO_lightTexture = LWJGLUtils.setupFBOTexture(mainFBO_lightTexture,(int)(SCREEN_SIZE_X), (int)(SCREEN_SIZE_Y));
		LWJGLUtils.attachTextureToFBO(1,mainFBO_lightTexture);

		//switch back to normal framebuffer
		LWJGLUtils.bindFBO(0);

		TWLrenderer.syncViewportSize();
	}

    public static void updateDisplay() {
        GLFW.glfwSwapBuffers(window);
        GLFW.glfwPollEvents();
    }

    public static void destroy() {
        GLFW.glfwDestroyWindow(window);
        GLFW.glfwTerminate();
    }

	public static void setBlendMode(int src,int dst) {
		//if(Keyboard.isKeyDown(Keyboard.KEY_COMMA))glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//else
		//if(Keyboard.isKeyDown(Keyboard.KEY_PERIOD))glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		//else
		glBlendFunc(src,dst);
	}

	public static void setShaderVar1i(int shader,String string,int i) {
		if(ARBShader)glUniform1iARB(glGetUniformLocationARB(shader, new StringBuffer(string)), i);
		else glUniform1i(glGetUniformLocation(shader, new StringBuffer(string)), i);
	}

	public static void setShaderVar1f(int shader,String string,float f) {
		if(ARBShader)glUniform1fARB(glGetUniformLocationARB(shader, new StringBuffer(string)), f);
		else glUniform1f(glGetUniformLocation(shader, new StringBuffer(string)), f);

	}

	public static void setShaderVar2f(int shader,String string,float f1,float f2) {
		if(ARBShader)glUniform2fARB(glGetUniformLocationARB(shader, new StringBuffer(string)), f1,f2);
		else glUniform2f(glGetUniformLocation(shader, new StringBuffer(string)), f1,f2);

	}
}
