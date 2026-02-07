package com.bobsgame.audio;

import ibxm.IBXM;
import ibxm.Module;
import org.apache.commons.io.IOUtils;
import org.lwjgl.BufferUtils;
import org.lwjgl.openal.AL10;

import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.IntBuffer;

public class MODFileAudioChannel extends AudioChannel {
	/** The size of the sections to stream from the mod file */
	//private static final int sectionSize=4096*10;

	/** Holds the OpenAL buffer names */
	private IntBuffer bufferNames;
	/** The IBXM reference */
	public IBXM ibxm;
	/** The length of the track in frames */
	private int songDuration;
	/** The data read for this section */
	//private byte[] data=new byte[sectionSize*4];


	/** The byte buffer passed to OpenAL containing the section */
	private ByteBuffer bufferData;//=BufferUtils.createByteBuffer(44100*32);


	/** The buffer holding the names of the OpenAL buffer thats been fully played back */
	private IntBuffer unqueued=BufferUtils.createIntBuffer(1);


	/** The source we're playing back on */
	private int channel;
	/** True if sound works */
	//private boolean soundWorks=true;
	/** The module being played */
	private Module module;
	/** True if we should loop the track */
	private boolean loop;
	/** True if we've completed play back */
	public boolean done=true;
	/** The number of buffers remaining to be played back */
	private int remainingBufferCount;



	//private OpenALMODPlayer player = new OpenALMODPlayer();

	//private Module module;

	private static final int SAMPLE_RATE = 48000;


	//=========================================================================================================================
	public MODFileAudioChannel(InputStream in)
	{//=========================================================================================================================
        super(-1);
		module = loadModule(in);
	}



	//=========================================================================================================================
	public void updateBufferAndPlay()
	{//=========================================================================================================================
		if(channelIndex!=-1)
		{


			if(isPaused())
			{

			}
			else
			{
				//updatePlayer();
				/**
				 * Poll the bufferNames - check if we need to fill the bufferNames with another
				 * section.
				 * Most of the time this should be reasonably quick
				 */
				//=========================================================================================================================
				//public void updatePlayer()
				{//=========================================================================================================================
					if(done)
					{
						return;
					}

					int processed=AL10.alGetSourcei(channel,AL10.AL_BUFFERS_PROCESSED);

					while(processed>0)
					{
						unqueued.clear();

						AL10.alSourceUnqueueBuffers(channel,unqueued);

						if(stream(unqueued.get(0)))
						{
							AL10.alSourceQueueBuffers(channel,unqueued);
						}
						else
						{
							remainingBufferCount--;
							if(remainingBufferCount==0)
							{
								done=true;
							}
						}
						processed--;
					}

					int state=AL10.alGetSourcei(channel,AL10.AL_SOURCE_STATE);

					if(state!=AL10.AL_PLAYING)
					{
						AL10.alSourcePlay(channel);
					}
				}
			}

		}
	}




	//=========================================================================================================================
	public void play(float pitch,float gain,boolean loop)
	{//=========================================================================================================================


		if(channelIndex!=-1 && isPaused()==true)
		{
			unPause();
		}
		else
		{
			closeChannelAndFlushBuffers();

			channelIndex = AudioUtils.getOpenChannelIndex();


			this.channel=AudioUtils.getChannelFromIndex(channelIndex);

			this.loop=loop;

			done=false;

			ibxm=new IBXM(module,SAMPLE_RATE);

			bufferData=BufferUtils.createByteBuffer(ibxm.getMixBufferLength()*2);

			songDuration=ibxm.calculateSongDuration();

//			System.out.println("duration:"+songDuration/SAMPLE_RATE);
//			System.out.println("mixBufferLength:"+ibxm.getMixBufferLength());
//			System.out.println("samplerate:"+ibxm.getSampleRate());


			if(bufferNames!=null)
			{
				AL10.alSourceStop(channel);
				bufferNames.flip();
				AL10.alDeleteBuffers(bufferNames);
			}

			bufferNames=BufferUtils.createIntBuffer(2);
			AL10.alGenBuffers(bufferNames);
			remainingBufferCount=2;

			for(int i=0;i<2;i++)
			{
				stream(bufferNames.get(i));
			}
			AL10.alSourceQueueBuffers(channel,bufferNames);
			AL10.alSourcef(channel,AL10.AL_PITCH,(float)pitch);
			AL10.alSourcef(channel,AL10.AL_GAIN,(float)gain);


			AL10.alSourcePlay(channel);

		}
	}


	//=========================================================================================================================
	public boolean isDone()
	{//=========================================================================================================================
		return done;
	}


	//=========================================================================================================================
	public static Module loadModule(InputStream in)
	{//=========================================================================================================================

		// DataInputStream din;
		// byte[] xm_header, s3m_header, mod_header, output_buffer;
		// int frames;


		byte[] moduleData=null;

		try
		{
			moduleData=IOUtils.toByteArray(in);
		}
		catch(IOException e1)
		{
			e1.printStackTrace();
		}


		Module module=new Module(moduleData);

		// din = new DataInputStream(in);
		// module = null;
		// //xm_header = new byte[ 60 ];
		// din.readFully( xm_header );
		//
		// if( FastTracker2.is_xm( xm_header ) ) {
		// module = FastTracker2.load_xm( xm_header, din );
		// } else {
		// s3m_header = new byte[ 96 ];
		// System.arraycopy( xm_header, 0, s3m_header, 0, 60 );
		// din.readFully( s3m_header, 60, 36 );
		//
		// if( ScreamTracker3.is_s3m( s3m_header ) ) {
		// module = ScreamTracker3.load_s3m( s3m_header, din );
		// } else {
		// mod_header = new byte[ 1084 ];
		// System.arraycopy( s3m_header, 0, mod_header, 0, 96 );
		// din.readFully( mod_header, 96, 988 );
		// module = ProTracker.load_mod( mod_header, din );
		// }
		// }
		// din.close();

		return module;
	}





	/**
	 * Stream one section from the mod/xm into an OpenAL buffer
	 *
	 * @param bufferId
	 *            The ID of the buffer to fill
	 * @return True if another section was available
	 */
	//=========================================================================================================================
	public boolean stream(int bufferId)
	{//=========================================================================================================================

		int frames=1;
		boolean reset=false;
		boolean more=true;

		if(frames>songDuration)
		{
			frames=songDuration;
			reset=true;
		}

/*
	int[] mixBuf = new int[ ibxm.getMixBufferLength() ];
	byte[] outBuf = new byte[ mixBuf.length * 2 ];
	AudioFormat audioFormat = null;
	SourceDataLine audioLine = null;
	try
	{
		audioFormat = new AudioFormat( SAMPLE_RATE, 16, 2, true, true );
		audioLine = AudioSystem.getSourceDataLine( audioFormat );
		audioLine.open();
		audioLine.start();
		while( playing )
		{
			int count = getAudio( mixBuf );
			int outIdx = 0;
			for( int mixIdx = 0, mixEnd = count * 2; mixIdx < mixEnd; mixIdx++ ) {
				int ampl = mixBuf[ mixIdx ];
				if( ampl > 32767 ) ampl = 32767;
				if( ampl < -32768 ) ampl = -32768;
				outBuf[ outIdx++ ] = ( byte ) ( ampl >> 8 );
				outBuf[ outIdx++ ] = ( byte ) ampl;
			}
			audioLine.write( outBuf, 0, outIdx );
		}
		audioLine.drain();
	}
*/

		int[] mixBuf=new int[ibxm.getMixBufferLength()];
		byte[] outBuf=new byte[mixBuf.length*2];

		int count=ibxm.getAudio(mixBuf);

		boolean bigEndian = ByteOrder.nativeOrder().equals(ByteOrder.BIG_ENDIAN);

		int outIdx=0;
		for(int mixIdx=0,mixEnd=count*2;mixIdx<mixEnd;mixIdx++)
		{
			int ampl=mixBuf[mixIdx];
			if(ampl>32767) ampl=32767;
			if(ampl<-32768) ampl=-32768;

			if (bigEndian)
			{
				outBuf[outIdx++] = ( byte ) ( ampl >> 8 );
				outBuf[outIdx++] = ( byte ) ( ampl & 0xFF );
			}
			else
			{
				outBuf[outIdx++] = ( byte ) ( ampl & 0xFF );
				outBuf[outIdx++] = ( byte ) ( ampl >> 8 );
			}

//			outBuf[outIdx++]=(byte)(ampl>>8);
//			outBuf[outIdx++]=(byte)ampl;
		}

		bufferData.clear();
		bufferData.put(outBuf);
		bufferData.limit(outIdx);

		if(reset)
		{
			if(loop)
			{
				ibxm.seek(0);

				songDuration=ibxm.calculateSongDuration();
			}
			else
			{
				more=false;
				songDuration-=frames;
			}
		}
		else
		{
			songDuration-=frames;
		}

		bufferData.flip();
		AL10.alBufferData(bufferId,AL10.AL_FORMAT_STEREO16,bufferData,SAMPLE_RATE);

		return more;














//
//
//
//		int frames = sectionSize;
//		boolean reset = false;
//		boolean more = true;
//
//		if (frames > songDuration) {
//			frames = songDuration;
//			reset = true;
//		}
//
//		ibxm.get_audio(data, frames);
//		bufferData.clear();
//		bufferData.put(data);
//		bufferData.limit(frames * 4);
//
//		if (reset) {
//			if (loop) {
//				ibxm.seek(0);
//				ibxm.set_module(module);
//				songDuration = ibxm.calculate_song_duration();
//			} else {
//				more = false;
//				songDuration -= frames;
//			}
//		} else {
//			songDuration -= frames;
//		}
//
//		bufferData.flip();
//		AL10.alBufferData(bufferId, AL10.AL_FORMAT_STEREO16, bufferData, 48000);
//
//		return more;
//
//




//
//		int output_idx, mix_idx, mix_end, count, amplitude;
//		output_idx = 0;
//
//		while( frames > 0 )
//		{
//
//			count = tick_length_samples - current_tick_samples;
//
//			if( count > frames )
//			{
//				count = frames;
//			}
//
//			mix_idx = current_tick_samples << 1;
//			mix_end = mix_idx + ( count << 1 ) - 1;
//
//			while( mix_idx <= mix_end )
//			{
//				amplitude = mixing_buffer[ mix_idx ];
//
//				if( amplitude > 32767 )
//				{
//					amplitude = 32767;
//				}
//
//				if( amplitude < -32768 )
//				{
//					amplitude = -32768;
//				}
//
//				if (bigEndian)
//				{
//					output_buffer[ output_idx     ] = ( byte ) ( amplitude >> 8 );
//					output_buffer[ output_idx + 1 ] = ( byte ) ( amplitude & 0xFF );
//				} else {
//					output_buffer[ output_idx     ] = ( byte ) ( amplitude & 0xFF );
//					output_buffer[ output_idx + 1 ] = ( byte ) ( amplitude >> 8 );
//				}
//				output_idx += 2;
//				mix_idx += 1;
//			}
//		}
//








	}
}
