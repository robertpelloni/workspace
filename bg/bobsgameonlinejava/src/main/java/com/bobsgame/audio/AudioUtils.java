package com.bobsgame.audio;

import ch.qos.logback.classic.Logger;
import com.bobsgame.shared.Utils;
import org.lwjgl.BufferUtils;
import org.lwjgl.openal.AL;
import org.lwjgl.openal.AL10;
import org.lwjgl.openal.AL11;
import org.lwjgl.openal.ALC;
import org.lwjgl.openal.ALC10;
import org.lwjgl.openal.ALCCapabilities;
import org.lwjgl.openal.ALCapabilities;
import org.slf4j.LoggerFactory;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.nio.ByteBuffer;
import java.nio.FloatBuffer;
import java.nio.IntBuffer;
import java.util.HashMap;

public class AudioUtils {
	public static Logger log = (Logger) LoggerFactory.getLogger(AudioUtils.class);

	private static int maximumChannels = 128;
	private static int channelsAvailable;
	private static IntBuffer channels;

	private static boolean[] channelInUse;

	private static HashMap<String, Integer> loadedSoundHashMap = new HashMap<>();

	// The buffer used to set the velocity of a source
	private static FloatBuffer sourceVel = BufferUtils.createFloatBuffer(3).put(new float[]{0, 0, 0});

	// The buffer used to set the position of a source
	private static FloatBuffer sourcePos = BufferUtils.createFloatBuffer(3);

    private static long device;
    private static long context;

	public AudioUtils() {
		log.info("Init AL...");

        String defaultDeviceName = ALC10.alcGetString(0, ALC10.ALC_DEFAULT_DEVICE_SPECIFIER);
        device = ALC10.alcOpenDevice(defaultDeviceName);

        int[] attributes = {0};
        context = ALC10.alcCreateContext(device, attributes);
        ALC10.alcMakeContextCurrent(context);

        ALCCapabilities alcCapabilities = ALC.createCapabilities(device);
        ALCapabilities alCapabilities = AL.createCapabilities(alcCapabilities);

		channelsAvailable = 0;
		channels = BufferUtils.createIntBuffer(maximumChannels);

		while (AL10.alGetError() == AL10.AL_NO_ERROR) {
			IntBuffer temp = BufferUtils.createIntBuffer(1);

			try {
				AL10.alGenSources(temp);

				if (AL10.alGetError() == AL10.AL_NO_ERROR) {
					channelsAvailable++;
					channels.put(temp.get(0));
					if (channelsAvailable > maximumChannels-  1) {
						break;
					}
				}
			} catch (Exception e) {
				// expected at the end
				break;
			}
		}

		log.debug(channelsAvailable + " OpenAL sound sources available.");
		channelInUse = new boolean[channelsAvailable];
		for (int i = 0; i < channelInUse.length; i++) {
			channelInUse[i] = false;
		}

		int error = AL10.alGetError();

		if (error != AL10.AL_NO_ERROR) {
			if (error == AL10.AL_INVALID_NAME) log.error("OpenAL Error: Invalid Name parameter.");
			if (error == AL10.AL_INVALID_ENUM) log.error("OpenAL Error: Invalid parameter.");
			if (error == AL10.AL_INVALID_VALUE) log.error("OpenAL Error: Invalid enum parameter value.");
			if (error == AL10.AL_INVALID_OPERATION) log.error("OpenAL Error: Illegal call.");
			if (error == AL10.AL_OUT_OF_MEMORY) log.error("OpenAL Error: Unable to allocate memory.");
		} else {
			FloatBuffer listenerOri = BufferUtils.createFloatBuffer(6).put(new float[]{0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f});
			FloatBuffer listenerVel = BufferUtils.createFloatBuffer(3).put(new float[]{0.0f, 0.0f, 0.0f});
			FloatBuffer listenerPos = BufferUtils.createFloatBuffer(3).put(new float[]{0.0f, 0.0f, 0.0f});
			listenerPos.flip();
			listenerVel.flip();
			listenerOri.flip();
			AL10.alListenerfv(AL10.AL_POSITION, listenerPos);
			AL10.alListenerfv(AL10.AL_VELOCITY, listenerVel);
			AL10.alListenerfv(AL10.AL_ORIENTATION, listenerOri);
		}

		log.info("AL Complete.");
	}


	public static int getChannelFromIndex(int channelIndex) {
		return channels.get(channelIndex);
	}

	public static void setMaxChannels(int max) {
		maximumChannels = max;
	}

	public static int getOpenChannelIndex() {
		for (int index = 0; index < channelsAvailable - 1; index++) {
			int state = AL10.alGetSourcei(getChannelFromIndex(index), AL10.AL_SOURCE_STATE);
			if ((state != AL10.AL_PLAYING) && (state != AL10.AL_PAUSED) && channelInUse[index] == false) {
				channelInUse[index] = true;
				return index;
			}
		}
		return -1;
	}

	public static int getChannelCount() {
		return channelsAvailable;
	}

	public static void setChannelVolume(int channelIndex, float volume) {
		if (channelIndex == -1) return;

		if (volume < 0) volume = 0;
		if (volume > 1) volume = 1;

		AL10.alSourcef(getChannelFromIndex(channelIndex), AL10.AL_GAIN, volume);
	}

	public static float getChannelVolume(int channelIndex) {
		if (channelIndex < 0) return 0;
		return AL10.alGetSourcef(getChannelFromIndex(channelIndex), AL10.AL_GAIN);
	}

	public static void pauseChannel(int channelIndex) {
		if (channelIndex == -1) return;
		AL10.alSourcePause(getChannelFromIndex(channelIndex));
	}

	public static void unpauseChannel(int channelIndex) {
		if (channelIndex == -1) return;
		AL10.alSourcePlay(getChannelFromIndex(channelIndex));
	}

	public static void playChannel(int channelIndex) {
		if (channelIndex == -1) return;
		AL10.alSourcePlay(getChannelFromIndex(channelIndex));
	}

	public static void setChannelPitch(int channelIndex,float pitch) {
		if (channelIndex == -1) return;
		AL10.alSourcef(getChannelFromIndex(channelIndex), AL10.AL_PITCH, pitch);
	}

	public static boolean isChannelPlaying(int channelIndex) {
		if (channelIndex == -1) return false;
		int state = AL10.alGetSourcei(getChannelFromIndex(channelIndex), AL10.AL_SOURCE_STATE);
		return(state == AL10.AL_PLAYING);
	}

	public static boolean isChannelStopped(int channelIndex) {
		if (channelIndex == -1) return false;
		int state = AL10.alGetSourcei(getChannelFromIndex(channelIndex), AL10.AL_SOURCE_STATE);
		return(state == AL10.AL_STOPPED);
	}

	public static boolean isChannelPaused(int channelIndex) {
		if (channelIndex == -1) return false;
		int state = AL10.alGetSourcei(getChannelFromIndex(channelIndex), AL10.AL_SOURCE_STATE);
		return(state == AL10.AL_PAUSED);
	}

	public static boolean setPosition(int channelIndex, float position) {
		if (channelIndex == -1) return false;
		AL10.alSourcef(AudioUtils.getChannelFromIndex(channelIndex), AL11.AL_SEC_OFFSET, position);
		if (AL10.alGetError() != 0) {
			return false;
		}
		return true;
	}

	public static float getPosition(int channelIndex) {
		if (channelIndex == -1) return 0;
		return AL10.alGetSourcef(AudioUtils.getChannelFromIndex(channelIndex), AL11.AL_SEC_OFFSET);
	}

	public static void closeChannelAndFlushBuffers(int channelIndex) {
		if (channelIndex == -1) return;

		AL10.alSourceStop(AudioUtils.getChannelFromIndex(channelIndex));
		IntBuffer buffer = BufferUtils.createIntBuffer(1);
		int queued = AL10.alGetSourcei(AudioUtils.getChannelFromIndex(channelIndex), AL10.AL_BUFFERS_QUEUED);

		while (queued > 0) {
			AL10.alSourceUnqueueBuffers(AudioUtils.getChannelFromIndex(channelIndex), buffer);
			queued--;
		}

		AL10.alSourcei(AudioUtils.getChannelFromIndex(channelIndex), AL10.AL_BUFFER,0);

		channelInUse[channelIndex] = false;
	}

	int playBufferInAnyOpenChannel(int openALBufferID, float pitch, float gain, boolean loop) {
		return playBufferInAnyOpenChannel(openALBufferID, pitch, gain, loop, 0, 0, 0);
	}

	static int playBufferInAnyOpenChannel(int openALBufferID, float pitch, float gain, boolean loop, float x, float y, float z) {
		if (gain == 0) gain = 0.001f;

		int openChannelIndex = getOpenChannelIndex();
		if (openChannelIndex == -1) return -1;

		AL10.alSourceStop(getChannelFromIndex(openChannelIndex));

		AL10.alSourcei(getChannelFromIndex(openChannelIndex), AL10.AL_BUFFER, openALBufferID);
		AL10.alSourcef(getChannelFromIndex(openChannelIndex), AL10.AL_PITCH, pitch);
		AL10.alSourcef(getChannelFromIndex(openChannelIndex), AL10.AL_GAIN, gain);
		AL10.alSourcei(getChannelFromIndex(openChannelIndex), AL10.AL_LOOPING, loop ? AL10.AL_TRUE : AL10.AL_FALSE);

		sourcePos.clear();
		sourceVel.clear();
		sourceVel.put(new float[]{0, 0, 0});
		sourcePos.put(new float[]{x, y, z});
		sourcePos.flip();
		sourceVel.flip();

		AL10.alSourcefv(getChannelFromIndex(openChannelIndex), AL10.AL_POSITION, sourcePos);
		AL10.alSourcefv(getChannelFromIndex(openChannelIndex), AL10.AL_VELOCITY, sourceVel);

		AL10.alSourcePlay(getChannelFromIndex(openChannelIndex));

		return openChannelIndex;
	}

	static void setLoop(int channelIndex, boolean loop) {
		AL10.alSourcei(getChannelFromIndex(channelIndex), AL10.AL_LOOPING, loop ? AL10.AL_TRUE : AL10.AL_FALSE);
	}

	public static AudioChannel open(String fileName, String md5Name) {
		AudioChannel audio = null;

		String extension = fileName;

		while (extension.contains(".")) {
			extension = extension.substring(extension.indexOf(".") + 1).toUpperCase();
		}

		try {
			InputStream is = Utils.getResourceAsStream(md5Name);
			if (extension.equals("WAV")) audio = getWAVAudioChannel(md5Name, is);
			if (extension.equals("OGG")) audio = getOggStreamAudioChannel(md5Name, is);
			if (extension.equals("MOD") || extension.equals("XM") || extension.equals("S3M")) audio = getMODFileAudioChannel(is);
		} catch (IOException e) {
			e.printStackTrace();
		}

		return audio;
	}

	public static AudioChannel open(String fileName, String md5Name, byte[] byteData) {
		AudioChannel audio = null;

		String extension = fileName;

		while (extension.contains(".")) {
			extension = extension.substring(extension.indexOf(".") + 1).toUpperCase();
		}

		try {
			ByteArrayInputStream is = new ByteArrayInputStream(byteData);
			if (extension.equals("WAV")) audio = getWAVAudioChannel(md5Name, is);
			if (extension.equals("OGG")) audio = getOggStreamAudioChannel(md5Name, is);
			if (extension.equals("MOD") || extension.equals("XM") || extension.equals("S3M")) audio = getMODFileAudioChannel(is);
		} catch (IOException e) {
			e.printStackTrace();
		}

		return audio;
	}

	public static AudioChannel getWAVAudioChannel(String nameForSoundCache, InputStream in) throws IOException {
		int openALBufferID;

		if (loadedSoundHashMap.get(nameForSoundCache) != null) {
			openALBufferID = loadedSoundHashMap.get(nameForSoundCache).intValue();
		} else {
			try {
				IntBuffer buf=BufferUtils.createIntBuffer(1);

				WaveData data = WaveData.create(in);
				AL10.alGenBuffers(buf);
				AL10.alBufferData(buf.get(0), data.format, data.data, data.samplerate);

				loadedSoundHashMap.put(nameForSoundCache, Integer.valueOf(buf.get(0)));
				openALBufferID = buf.get(0);
			} catch (Exception e) {
				log.error(e.getMessage());
				IOException x = new IOException("Failed to load: " + nameForSoundCache);
				x.initCause(e);
				throw x;
			}
		}

		if (openALBufferID == -1) {
			throw new IOException("Unable to load: " + nameForSoundCache);
		}

		return new AudioChannel(openALBufferID);
	}

	public static AudioChannel getOggStreamAudioChannel(URL fileURL) {
		return new OggStreamAudioChannel(fileURL);
	}

	public static AudioChannel getMODFileAudioChannel(InputStream in) throws IOException {
		return new MODFileAudioChannel(in);
	}

	public static AudioChannel getOggStreamAudioChannel(String nameForSoundCache, InputStream in) throws IOException {
		int buffer;

		if (loadedSoundHashMap.get(nameForSoundCache) != null) {
			buffer = loadedSoundHashMap.get(nameForSoundCache).intValue();
		} else {
			try {
				IntBuffer buf = BufferUtils.createIntBuffer(1);

				OggDecoder decoder = new OggDecoder();
				OggData ogg = decoder.getData(in);

				AL10.alGenBuffers(buf);
				AL10.alBufferData(buf.get(0), ogg.channels > 1 ? AL10.AL_FORMAT_STEREO16 : AL10.AL_FORMAT_MONO16, ogg.data, ogg.rate);

				loadedSoundHashMap.put(nameForSoundCache, Integer.valueOf(buf.get(0)));

				buffer = buf.get(0);
			} catch (Exception e) {
				log.error(e.getMessage());
				throw new IOException("Unable to load: " + nameForSoundCache);
			}
		}

		if (buffer == -1) {
			throw new IOException("Unable to load: " + nameForSoundCache);
		}

		return new AudioChannel(buffer);
	}

    public static void destroy() {
        ALC10.alcDestroyContext(context);
        ALC10.alcCloseDevice(device);
    }
}
