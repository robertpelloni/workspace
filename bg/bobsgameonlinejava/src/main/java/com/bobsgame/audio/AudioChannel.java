package com.bobsgame.audio;

import org.lwjgl.openal.AL10;

public class AudioChannel {
	protected int openALBufferID;

	protected int channelIndex = -1;

	protected float length;

	/**
	 * Create a new sound
	 * @param openALBufferID The buffer containing the sound data
	 */
	AudioChannel(int openALBufferID) {
		this.openALBufferID = openALBufferID;

		int bytes = AL10.alGetBufferi(openALBufferID, AL10.AL_SIZE);
		int bits = AL10.alGetBufferi(openALBufferID, AL10.AL_BITS);
		int channels = AL10.alGetBufferi(openALBufferID, AL10.AL_CHANNELS);
		int freq = AL10.alGetBufferi(openALBufferID, AL10.AL_FREQUENCY);

		int samples = bytes / (bits / 8);
		length = (samples / (float) freq) / channels;
	}

	public void setVolume(float v) {
		if (channelIndex != -1) {
			AudioUtils.setChannelVolume(channelIndex, v);
		}
	}

	public void setPitch(float p) {
		if (channelIndex != -1) {
			AudioUtils.setChannelPitch(channelIndex, p);
		}
	}

	public void closeChannelAndFlushBuffers() {
		if (channelIndex != -1) {
			AudioUtils.closeChannelAndFlushBuffers(channelIndex);
		}
		channelIndex = -1;
	}

	public void play() {
		play(1.0f, 1.0f, true);
	}

	public void play(float pitch,float gain,boolean loop) {
		play(pitch, gain, loop, 0, 0, 0);
	}

	private void play(float pitch, float gain, boolean loop, float x, float y, float z) {
		if (channelIndex != -1 && isPaused() == true) {
			unPause();
		} else {
			closeChannelAndFlushBuffers();
			channelIndex = AudioUtils.playBufferInAnyOpenChannel(openALBufferID, pitch, gain, loop, x, y, z);
		}
	}

	public void setLoop(boolean loop) {
		if (channelIndex != -1) {
			AudioUtils.setLoop(channelIndex, loop);
		}
	}

	public void pause() {
		if (isPaused() == false) {
			if (channelIndex !=- 1) {
				AudioUtils.pauseChannel(channelIndex);
			}
		}
	}

	public void unPause() {
		if (isPaused() == true) {
			if (channelIndex != -1) {
				AudioUtils.unpauseChannel(channelIndex);
			}
		}
	}

	public boolean isPlaying() {
		if (channelIndex != -1) {
			return AudioUtils.isChannelPlaying(channelIndex);
		}
		return false;
	}

	public boolean isPaused() {
		if (channelIndex != -1) {
			return AudioUtils.isChannelPaused(channelIndex);
		}
		return false;
	}

	public boolean isDone() {
		if (channelIndex != -1) {
			return AudioUtils.isChannelStopped(channelIndex);
		}
		return true;
	}

	public boolean setPosition(float position) {
		position = position % length;
		return AudioUtils.setPosition(channelIndex, position);
	}

	public float getPosition() {
		return AudioUtils.getPosition(channelIndex);
	}

	public void updateBufferAndPlay()
	{
	}
}