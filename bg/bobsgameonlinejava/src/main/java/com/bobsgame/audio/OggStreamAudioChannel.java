package com.bobsgame.audio;

import java.io.IOException;
import java.net.URL;
import java.nio.ByteBuffer;
import java.nio.IntBuffer;

import org.lwjgl.BufferUtils;
import org.lwjgl.openal.AL10;
import org.lwjgl.openal.AL11;
//import org.lwjgl.openal.OpenALException;

import com.bobsgame.shared.Utils;

public class OggStreamAudioChannel extends AudioChannel {
	URL fileURL;
	String fileName;

	public OggStreamAudioChannel(URL fileURL) {
        super(-1);
		this.fileURL = fileURL;
	}

	public OggStreamAudioChannel(String fileName) {
        super(-1);
		this.fileName = fileName;
	}


	public void init() {
		if (audio != null) {
			try {
				audio.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

		if (fileName != null) {
			try {
				audio = new OggInputStream(Utils.getResourceAsStream(fileName));
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

		if (fileURL != null) {
			try {
				audio = new OggInputStream(fileURL.openStream());
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

		positionOffset = 0;
	}

	public void play(float pitch, float gain, boolean loop) {
		if(channelIndex!=-1 && isPaused()==true) {
			unPause();
		} else {
			closeChannelAndFlushBuffers();

			channelIndex = AudioUtils.getOpenChannelIndex();

			channel=AudioUtils.getChannelFromIndex(channelIndex);

			bufferNames=BufferUtils.createIntBuffer(BUFFER_COUNT);
			AL10.alGenBuffers(bufferNames);

			try {
				this.loop=loop;
				this.pitch=pitch;
				this.gain=gain;

				init();

				done=false;

				//AL10.alSourceStop(channel);
				//removeBuffers();

				startPlayback();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}

	public static final int BUFFER_COUNT=3;

	private static final int sectionSize=4096*20;// The size of the sections to stream from the stream

	private byte[] buffer=new byte[sectionSize];// The buffer read from the data stream

	private IntBuffer bufferNames;// OpenAL buffer names


	private ByteBuffer bufferData=BufferUtils.createByteBuffer(sectionSize);// byte buffer passed to OpenAL containing the section


	private IntBuffer unqueued=BufferUtils.createIntBuffer(1);// buffer holding the names of the OpenAL buffer thats been fully played back


	private int channel;


	private int remainingBufferCount;


	private boolean loop;


	private boolean done=true;

	/** The stream we're currently reading from */
	private OggInputStream audio;
	private float pitch;
	private float positionOffset;// Position in seconds of the previously played buffers
	float gain;

//
//	//=========================================================================================================================
//	private void removeBuffers()
//	{//=========================================================================================================================
//		IntBuffer buffer=BufferUtils.createIntBuffer(1);
//		int queued=AL10.alGetSourcei(channel,AL10.AL_BUFFERS_QUEUED);
//
//		while(queued>0)
//		{
//			AL10.alSourceUnqueueBuffers(channel,buffer);
//			queued--;
//		}
//	}


	public boolean isDone() {
		return done;
	}

	public void updateBufferAndPlay() {
		if(channelIndex!=-1) {
			if(isPaused()) {
			} else {
				if(done) {
					return;
				}

				float sampleRate=audio.getRate();
				float sampleSize;
				if(audio.getChannels()>1) {
					sampleSize=4; // AL10.AL_FORMAT_STEREO16
				} else {
					sampleSize=2; // AL10.AL_FORMAT_MONO16
				}

				int processed=AL10.alGetSourcei(channel,AL10.AL_BUFFERS_PROCESSED);
				while(processed>0) {
					unqueued.clear();
					AL10.alSourceUnqueueBuffers(channel,unqueued);

					int bufferIndex=unqueued.get(0);

					float bufferLength=(AL10.alGetBufferi(bufferIndex,AL10.AL_SIZE)/sampleSize)/sampleRate;
					positionOffset+=bufferLength;

					if(stream(bufferIndex)) {
						AL10.alSourceQueueBuffers(channel,unqueued);
					} else {
						remainingBufferCount--;
						if(remainingBufferCount==0)
						{
							done=true;
						}
					}
					processed--;
				}

				int state=AL10.alGetSourcei(channel,AL10.AL_SOURCE_STATE);

				if(state!=AL10.AL_PLAYING) {
					AL10.alSourcePlay(channel);
				}
			}
		}
	}

	public boolean stream(int bufferId) {
		try {
			int count = audio.read(buffer);

			if (count != -1) {
				bufferData.clear();
				bufferData.put(buffer, 0, count);
				bufferData.flip();

				int format = audio.getChannels() > 1 ? AL10.AL_FORMAT_STEREO16 : AL10.AL_FORMAT_MONO16;
				try {
					AL10.alBufferData(bufferId, format, bufferData, audio.getRate());
				} catch (Exception e) {
					System.err.println("Failed to loop buffer: " + bufferId + " " + format + " " + count + " " + audio.getRate() + " " + e);
					return false;
				}
			} else {
				if (loop) {
					init();
					stream(bufferId);
				} else {
					done = true;
					return false;
				}
			}

			return true;
		} catch (IOException e) {
			System.err.println(e);
			return false;
		}
	}

	public boolean setPosition(float position) {
		try {
			if (getPosition() > position) {
				init();
			}

			float sampleRate = audio.getRate();
			float sampleSize;
			if (audio.getChannels() > 1) {
				sampleSize=4; // AL10.AL_FORMAT_STEREO16
			} else {
				sampleSize = 2; // AL10.AL_FORMAT_MONO16
			}

			while(positionOffset<position)
			{
				int count = audio.read(buffer);
				if (count != -1) {
					float bufferLength = (count / sampleSize) / sampleRate;
					positionOffset += bufferLength;
				} else {
					if (loop) {
						init();
					} else {
						done = true;
					}
					return false;
				}
			}

			startPlayback();

			return true;
		} catch (IOException e) {
			System.err.println(e);
			return false;
		}
	}

	private void startPlayback() {
		AL10.alSourcei(channel, AL10.AL_LOOPING, AL10.AL_FALSE);
		AL10.alSourcef(channel, AL10.AL_PITCH, pitch);
		AL10.alSourcef(channel, AL10.AL_GAIN, gain);

		remainingBufferCount = BUFFER_COUNT;

		for (int i = 0; i < BUFFER_COUNT; i++) {
			stream(bufferNames.get(i));
		}

		AL10.alSourceQueueBuffers(channel,bufferNames);
		AL10.alSourcePlay(channel);
	}

	public float getPosition() {
		return positionOffset + AL10.alGetSourcef(channel, AL11.AL_SEC_OFFSET);
	}
}
