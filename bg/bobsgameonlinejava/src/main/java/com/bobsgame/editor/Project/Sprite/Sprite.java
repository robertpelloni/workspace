package com.bobsgame.editor.Project.Sprite;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

import java.awt.*;

import java.awt.image.*;

import com.bobsgame.EditorMain;


import com.bobsgame.editor.HQ2X;
import com.bobsgame.editor.Project.GameObject;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.Event.Event;
import com.bobsgame.editor.TileCanvas.TileCanvas;
import com.bobsgame.shared.EventData;
import com.bobsgame.shared.SpriteAnimationSequence;
import com.bobsgame.shared.SpriteData;
import com.bobsgame.shared.Utils;

//===============================================================================================
public class Sprite implements GameObject
{//===============================================================================================

	public class Layer implements Serializable {
		private static final long serialVersionUID = 1L;
		public String name;
		public boolean visible = true;
		public boolean isReference = false;
		public float opacity = 1.0f;
		public int pixels[][][]; //[frame][width][height]

		public Layer(String name, int frames, int width, int height) {
			this.name = name;
			this.pixels = new int[frames][width][height];
		}

		public Layer duplicate() {
			Layer l = new Layer(name + " Copy", pixels.length, pixels[0].length, pixels[0][0].length);
			l.visible = this.visible;
			l.isReference = this.isReference;
			l.opacity = this.opacity;
			for(int f=0; f<pixels.length; f++) {
				for(int x=0; x<pixels[0].length; x++) {
					for(int y=0; y<pixels[0][0].length; y++) {
						l.pixels[f][x][y] = this.pixels[f][x][y];
					}
				}
			}
			return l;
		}
	}

	private List<Layer> layers = new ArrayList<>();
	public int activeLayerIndex = 0;

	public int selectedFrameIndex = 0;
	private SpriteData data;


	//===============================================================================================
	public Sprite(String name, int frames, int width, int height)
	{//===============================================================================================
		int id = getBiggestID();
		this.data = new SpriteData(id,name,width,height,frames);

		// Initialize default layer
		layers.add(new Layer("Layer 1", frames, width, height));

		data.addAnimation("Frame0",0,0,0,0,0);

		Project.spriteList.add(this);
		Project.spriteHashtable.put(getTYPEIDString(),this);
	}

	//===============================================================================================
	public Sprite(SpriteData s)
	{//===============================================================================================

		this.data = s;

		// Initialize default layer
		layers.add(new Layer("Layer 1", data.frames(), data.widthPixels1X(), data.heightPixels1X()));

		if(data.displayName().equals("No Name"))data.setDisplayName("");

		if(Project.spriteHashtable.get(getTYPEIDString())!=null)
		{
			System.err.println("Sprite ID for Sprite: "+name()+" already exists. Creating new ID.");
			int id = getBiggestID();
			setID(id);
		}

		Project.spriteList.add(this);
		Project.spriteHashtable.put(getTYPEIDString(),this);


		if(eventData()!=null)new Event(eventData());
	}

	//===============================================================================================
	public List<Layer> getLayers() {
		return layers;
	}

	public Layer getActiveLayer() {
		if(activeLayerIndex < 0 || activeLayerIndex >= layers.size()) activeLayerIndex = 0;
		return layers.get(activeLayerIndex);
	}

	public void addLayer() {
		layers.add(new Layer("Layer " + (layers.size() + 1), frames(), wP(), hP()));
		activeLayerIndex = layers.size() - 1;
	}

	public void removeLayer(int index) {
		if(layers.size() > 1) {
			layers.remove(index);
			if(activeLayerIndex >= layers.size()) activeLayerIndex = layers.size() - 1;
		}
	}

	//===============================================================================================
	public int getBiggestID()
	{//===============================================================================================
		int id = -1;

		int size=Project.spriteList.size();
		if(size==0)id=0;
		else
		{
			int biggest=0;
			for(int i=0;i<size;i++)
			{
				int testid = Project.spriteList.get(i).id();
				if(testid>biggest)biggest=testid;
			}
			id=biggest+1;
		}
		return id;

	}




	//===============================================================================================
	public String toString()
	{//===============================================================================================
		return getTYPEIDString();
	}
	//===============================================================================================
	@Override
	public String getShortTypeName()
	{//===============================================================================================
		return "SPRITE."+name();
	}
	//===============================================================================================
	@Override
	public String getLongTypeName()
	{//===============================================================================================
		return "SPRITE."+name();
	}


	//===============================================================================================
	public int[] getAsIntArray()
	{//===============================================================================================
		// Flatten layers for export/legacy support
		// For int array export, we assume index 0 (transparent) allows lower layers to show through.

		int[] intArray = new int[frames()*wP()*hP()];

		for(int f = 0; f < frames(); f++)
		{
			for(int y = 0; y < hP(); y++)
			{
				for(int x = 0; x < wP(); x++)
				{
					// Composite layers
					int compositePixel = 0;
					for(Layer layer : layers) {
						if(!layer.visible || layer.isReference) continue;
						int p = layer.pixels[f][x][y];
						if(p != 0) {
							compositePixel = p; // Simple overwrite blending for now
						}
					}

					int index = (f*hP()*wP())+(y*wP())+(x);
					intArray[index]=compositePixel;
				}
			}
		}

		return intArray;
	}

	//===============================================================================================
	public byte[] getAsByteArray()
	{//===============================================================================================
		return Utils.getByteArrayFromIntArray(getAsIntArray());
	}

	//===============================================================================================
	public void initializeFromIntArray(int[] intArray)
	{//===============================================================================================
		// When initializing from flat array, we clear layers and put everything on default layer
		layers.clear();
		layers.add(new Layer("Layer 1", frames(), wP(), hP()));
		activeLayerIndex = 0;

		for(int f = 0; f < frames(); f++)
		{
			for(int y = 0; y < hP(); y++)
			{
				for(int x = 0; x < wP(); x++)
				{
					int index = (f*hP()*wP())+(y*wP())+(x);
					int i = intArray[index];
					setPixel(f, x, y, i);
				}
			}
		}

	}

	//===============================================================================================
	public class SpriteBinWithUniquePalette
	{//===============================================================================================
		public int[] dataIntArray;
		public byte[] paletteRGBByteArray;


		public String getDataIntArrayAsGZippedBase64String()
		{
			return Utils.encodeStringToBase64(Utils.zipByteArrayToString(Utils.getByteArrayFromIntArray(dataIntArray)));
		}
		public String getPaletteRGBByteArrayAsGZippedBase64String()
		{
			return Utils.encodeStringToBase64(Utils.zipByteArrayToString(paletteRGBByteArray));
		}
	}

	//===============================================================================================
	public SpriteBinWithUniquePalette makeSpriteBinWithUniquePalette()
	{//===============================================================================================
		SpriteBinWithUniquePalette s = new SpriteBinWithUniquePalette();

		int[] newData = new int[frames()*wP()*hP()];
		ArrayList<Color> newPal = new ArrayList<Color>();

		newPal.add(Project.getSelectedSpritePalette().getColor(0));
		newPal.add(Project.getSelectedSpritePalette().getColor(1));
		newPal.add(Project.getSelectedSpritePalette().getColor(2));

		for(int f = 0; f < frames(); f++)
		{
			for(int y = 0; y < hP(); y++)
			{
				for(int x = 0; x < wP(); x++)
				{
					// Composite layers for export
					int compositePixel = 0;
					for(Layer layer : layers) {
						if(!layer.visible || layer.isReference) continue;
						int p = layer.pixels[f][x][y];
						if(p != 0) {
							compositePixel = p;
						}
					}

					int oldPalIndex = compositePixel;
					Color c = Project.getSelectedSpritePalette().getColor(oldPalIndex);

					//run through palette and see if color exists
					//if it doesn't, add it.
					int newPalIndex=-1;
					for(int i=0;i<newPal.size();i++)
					{
						if(newPal.get(i)==c){newPalIndex=i;break;}
					}
					if(newPalIndex==-1)//we didn't find the color
					{
						newPal.add(c);//add the new color to newpal
						newPalIndex = newPal.size()-1;
					}
					newData[(f*wP()*hP())+(y*wP())+x] = newPalIndex;
				}
			}
		}

		s.dataIntArray = newData;
		s.paletteRGBByteArray = new byte[newPal.size()*3];

		for(int i=0;i<newPal.size();i++)
		{
			s.paletteRGBByteArray[i*3+0] = (byte)newPal.get(i).getRed();
			s.paletteRGBByteArray[i*3+1] = (byte)newPal.get(i).getGreen();
			s.paletteRGBByteArray[i*3+2] = (byte)newPal.get(i).getBlue();
		}

		return s;
	}


	//===============================================================================================
	public void outputBINWithCustomPalette()
	{//===============================================================================================

		String dirpath = EditorMain.getDesktopTempDirPath() + "htdocs\\bin\\sprite\\";

		Utils.makeDir(dirpath);
		//Utils.makeDir(dirpath + name() + "\\");

		//if(dirpath==null)dirpath = EditorMain.getDesktopTempDirPath();
		//Utils.makeDir(dirpath + "bin\\sprite\\");


		SpriteBinWithUniquePalette s = makeSpriteBinWithUniquePalette();

		try
		{
			File file = new File(dirpath + name() + "_SpriteDataUnique.bin");
			FileOutputStream fileOutputStream = new FileOutputStream(file);
			fileOutputStream.write(Utils.getByteArrayFromIntArray(s.dataIntArray));
			fileOutputStream.close();
		}
		catch(FileNotFoundException fnfe){System.out.println("Could not create file.");return;}
		catch(IOException e){}


		try
		{
			File file = new File(dirpath + name() + "_SpritePaletteUnique.bin");
			FileOutputStream fileOutputStream = new FileOutputStream(file);
			fileOutputStream.write(s.paletteRGBByteArray);
			fileOutputStream.close();
		}
		catch(FileNotFoundException fnfe){System.out.println("Could not create file.");return;}
		catch(IOException e){}


		String filename = dirpath + name() + "_SpriteDataUnique" + ".bin";
		String filenamePalette = dirpath + name() + "_SpritePaletteUnique" + ".bin";

		String md5FileName = Utils.getFileMD5Checksum(filename);
		String md5FileNamePalette = Utils.getFileMD5Checksum(filenamePalette);

		setDataMD5(md5FileName);
		setPaletteMD5(md5FileNamePalette);

	}


	//===============================================================================================
	public Sprite duplicate()
	{//===============================================================================================
		Sprite spriteCopy = new Sprite(""+name()+"Copy"+Project.getNumSprites(), frames(), wP(), hP());

		spriteCopy.setIsNPC(isNPC());
		spriteCopy.setIsKid(isKid());
		spriteCopy.setIsAdult(isAdult());
		spriteCopy.setIsMale(isMale());
		spriteCopy.setIsFemale(isFemale());
		spriteCopy.setIsCar(isCar());
		spriteCopy.setIsAnimal(isAnimal());
		spriteCopy.setHasShadow(hasShadow());
		spriteCopy.setUtilityOffsetXPixels1X(utilityOffsetXPixels1X());
		spriteCopy.setUtilityOffsetYPixels1X(utilityOffsetYPixels1X());
		spriteCopy.setDisplayName(""+displayName());
		spriteCopy.setIsRandom(isRandom());

		spriteCopy.setIsItem(isItem());
		spriteCopy.setIsGame(isGame());
		spriteCopy.setForceMD5Export(forceMD5Export());
		spriteCopy.setForceHQ2X(forceHQ2X());
		if(eventData()!=null)spriteCopy.setEventData(Project.getEventByID(eventData().id()).duplicate().getData());
		spriteCopy.setGamePrice(gamePrice());
		spriteCopy.setItemGameDescription(""+itemGameDescription());


		// Deep copy layers
		spriteCopy.layers.clear();
		for(Layer l : layers) {
			spriteCopy.layers.add(l.duplicate());
		}
		spriteCopy.activeLayerIndex = this.activeLayerIndex;

		spriteCopy.animationList().clear();
		for(int i=0;i<animationList().size();i++)
		{
			SpriteAnimationSequence a = animationList().get(i);
			spriteCopy.data.addAnimation(a.frameSequenceName,a.frameStart,a.hitBoxFromLeftPixels1X,a.hitBoxFromRightPixels1X,a.hitBoxFromTopPixels1X,a.hitBoxFromBottomPixels1X);
		}

		return spriteCopy;
	}

	//===============================================================================================
	public SpriteAnimationSequence getClosestAnimationForCurrentFrame()
	{//===============================================================================================
		return getAnimationStartFrameForFrame(selectedFrameIndex);
	}


	//===============================================================================================
	public SpriteAnimationSequence getAnimationStartFrameForFrame(int currentFrame)
	{//===============================================================================================

		//check current frame to 0, looking for frameSequenceName
		//if found, return

		for(int n = currentFrame;n>=0;n--)
		{

			for(int i=0;i<animationList().size();i++)
			{
				SpriteAnimationSequence a = animationList().get(i);
				if(a.frameStart==n)return a;

			}
		}
		return null;
	}
	//===============================================================================================
	public SpriteAnimationSequence getAnimationForExactCurrentFrameOrNull()
	{//===============================================================================================
		return getAnimationForExactFrameOrNull(selectedFrameIndex);
	}

	//===============================================================================================
	public SpriteAnimationSequence getAnimationForExactFrameOrNull(int frame)
	{//===============================================================================================
		for(int i=0;i<animationList().size();i++)
		{
			SpriteAnimationSequence a = animationList().get(i);
			if(a.frameStart==frame)return a;
		}
		return null;
	}


	//===============================================================================================
	public void swapSpriteColors(int origCol, int newCol)
	{//===============================================================================================
		for(Layer layer : layers) {
			for(int f = 0; f < frames(); f++)
			{
				for(int y = 0; y < hP(); y++)
				{
					for(int x = 0; x < wP(); x++)
					{
						if(layer.pixels[f][x][y] == origCol)
						{
							layer.pixels[f][x][y] = newCol;
						}
						else if(layer.pixels[f][x][y] == newCol)
						{
							layer.pixels[f][x][y] = origCol;
						}
					}
				}
			}
		}
	}


	//===============================================================================================
	public void setSize(int w, int h)
	{//===============================================================================================

		while(w%8!=0)w++;
		while(h%8!=0)h++;

		for(Layer layer : layers) {
			int d[][][] = new int[frames()][w][h];

			for(int f = 0; f < frames() && f < frames(); f++)
			{
				for(int y = 0; y < h && y < hP(); y++)
				{
					for(int x = 0; x < w && x < wP(); x++)
					{
						d[f][x][y] = layer.pixels[f][x][y];
					}
				}
			}
			layer.pixels = d;
		}

		setWidthPixels(w);
		setHeightPixels(h);

	}


	//===============================================================================================
	public void setNumFrames(int newFrames)
	{//===============================================================================================

		for(Layer layer : layers) {
			int d[][][] = new int[newFrames][wP()][hP()];

			for(int f = 0; f < newFrames && f < frames(); f++)
			{
				for(int y = 0; y < hP(); y++)
				{
					for(int x = 0; x < wP(); x++)
					{
						d[f][x][y] = layer.pixels[f][x][y];
					}
				}
			}
			layer.pixels = d;
		}

		setFrames(newFrames);

		//remove any animations that start on frames past the new frame limit
		for(int i=0;i<animationList().size();i++)
		{
			SpriteAnimationSequence a = animationList().get(i);
			if(a.frameStart>=newFrames){animationList().remove(i);i=-1;continue;}
		}
	}


	//===============================================================================================
	public void deleteFrame(int deleteFrame)
	{//===============================================================================================
		for(Layer layer : layers) {
			for(int f = deleteFrame; f < frames() - 1; f++)
			{

				for(int y = 0; y < hP(); y++)
				{
					for(int x = 0; x < wP(); x++)
					{
						layer.pixels[f][x][y] = layer.pixels[f + 1][x][y];
					}
				}

			}
		}

		//move any animations past this frame down 1, delete any animation on the deleted frame
		for(int i=0;i<animationList().size();i++)
		{
			SpriteAnimationSequence a = animationList().get(i);
			if(a.frameStart==deleteFrame){animationList().remove(i);i=-1;continue;}
			if(a.frameStart>deleteFrame){a.frameStart--;}
		}

		setNumFrames(frames() - 1);
		if(deleteFrame>0)setFrame(deleteFrame - 1);
	}


	//===============================================================================================
	public void insertFrame(int insertFrame)
	{//===============================================================================================

		setNumFrames(frames() + 1);

		for(Layer layer : layers) {
			for(int f = frames() - 2; f >= insertFrame; f--)
			{
				for(int y = 0; y < hP(); y++)
				{
					for(int x = 0; x < wP(); x++)
					{
						layer.pixels[f + 1][x][y] = layer.pixels[f][x][y];
					}
				}
			}
			for(int y = 0; y < hP(); y++)
			{
				for(int x = 0; x < wP(); x++)
				{
					layer.pixels[insertFrame][x][y] = 0;
				}
			}
		}

		//move any animations on current frame and everything past it up one
		for(int i=0;i<animationList().size();i++)
		{
			SpriteAnimationSequence a = animationList().get(i);
			if(a.frameStart>=insertFrame){a.frameStart++;}
		}

	}
	//===============================================================================================
	public void insertFrameAfter(int insertFrame)
	{//===============================================================================================

		//we want to insert a frame after the one we are on and select it.
		setNumFrames(frames() + 1);

		for(Layer layer : layers) {
			for(int f = frames() - 2; f > insertFrame; f--)
			{
				for(int y = 0; y < hP(); y++)
				{
					for(int x = 0; x < wP(); x++)
					{
						layer.pixels[f + 1][x][y] = layer.pixels[f][x][y];
					}
				}
			}

			for(int y = 0; y < hP(); y++)
			{
				for(int x = 0; x < wP(); x++)
				{
					layer.pixels[insertFrame+1][x][y] = 0;
				}
			}
		}

		//move any animations past it up one
		for(int i=0;i<animationList().size();i++)
		{
			SpriteAnimationSequence a = animationList().get(i);
			if(a.frameStart>insertFrame){a.frameStart++;}
		}

		//switch to new frame
		setFrame(insertFrame + 1);
	}

	//===============================================================================================
	public void duplicateFrame(int frame)
	{//===============================================================================================

		insertFrameAfter(frame);

		for(Layer layer : layers) {
			for(int y = 0; y < hP(); y++)
			{
				for(int x = 0; x < wP(); x++)
				{
					layer.pixels[frame+1][x][y] = layer.pixels[frame][x][y];
				}
			}
		}

	}

	//===============================================================================================
	public void moveFrameLeft(int frame)
	{//===============================================================================================
		if(frame > 0 && frames() > 1)
		{
			insertFrame(frame - 1);
			for(Layer layer : layers) {
				for(int y = 0; y < hP(); y++)
				{
					for(int x = 0; x < wP(); x++)
					{
						layer.pixels[frame - 1][x][y] = layer.pixels[frame + 1][x][y];
					}
				}
			}

			//move any animation on this frame left, any animation to the left frame right
			for(int i=0;i<animationList().size();i++)
			{
				SpriteAnimationSequence a = animationList().get(i);
				if(a.frameStart==frame-1){a.frameStart++;}
				else if(a.frameStart==frame){a.frameStart--;}
			}



			deleteFrame(frame + 1);
			setFrame(frame - 1);
		}
	}


	//===============================================================================================
	public void moveFrameRight(int frame)
	{//===============================================================================================
		if(frame < frames() - 1 && frames() > 1)
		{
			insertFrame(frame + 2);

			for(Layer layer : layers) {
				for(int y = 0; y < hP(); y++)
				{
					for(int x = 0; x < wP(); x++)
					{
						layer.pixels[frame + 2][x][y] = layer.pixels[frame][x][y];
					}
				}
			}

			//move any animation on this frame right, any animation to the right frame left
			for(int i=0;i<animationList().size();i++)
			{
				SpriteAnimationSequence a = animationList().get(i);
				if(a.frameStart==frame+1){a.frameStart--;}
				else if(a.frameStart==frame){a.frameStart++;}
			}

			deleteFrame(frame);
			setFrame(frame + 1);
		}
	}


	//===============================================================================================
	public void moveFrameLeft()
	{//===============================================================================================
		moveFrameLeft(selectedFrameIndex);
	}


	//===============================================================================================
	public void moveFrameRight()
	{//===============================================================================================
		moveFrameRight(selectedFrameIndex);
	}


	//===============================================================================================
	public void deleteFrame()
	{//===============================================================================================
		deleteFrame(selectedFrameIndex);
	}


	//===============================================================================================
	public void duplicateFrame()
	{//===============================================================================================
		duplicateFrame(selectedFrameIndex);
	}


	//===============================================================================================
	public void insertFrame()
	{//===============================================================================================
		insertFrame(selectedFrameIndex);
	}

	//===============================================================================================
	public void insertFrameAfter()
	{//===============================================================================================
		insertFrameAfter(selectedFrameIndex);
	}




	//===============================================================================================
	public int getSelectedFrameIndex()
	{//===============================================================================================
		return selectedFrameIndex;
	}


	//===============================================================================================
	public void previousFrame()
	{//===============================================================================================
		if(selectedFrameIndex > 0)
		{
			selectedFrameIndex--;
		}
	}


	//===============================================================================================
	public void nextFrame()
	{//===============================================================================================
		if(selectedFrameIndex < frames() - 1)
		{
			selectedFrameIndex++;
		}
	}


	//===============================================================================================
	public void setFrame(int frm)
	{//===============================================================================================
		if(frm <= frames() - 1)
		{
			selectedFrameIndex = frm;
		}
	}





	//===============================================================================================
	public int getPixel(int x, int y)
	{//===============================================================================================
		return getActiveLayer().pixels[selectedFrameIndex][x][y];
	}


	//===============================================================================================
	public void setPixel(int x, int y, int color)
	{//===============================================================================================
		getActiveLayer().pixels[selectedFrameIndex][x][y] = color;
	}


	//===============================================================================================
	public int getPixel(int frame, int x, int y)
	{//===============================================================================================
		// NOTE: This legacy accessor is ambiguous with layers.
		// We will default to active layer to allow tools to work on current layer.
		return getActiveLayer().pixels[frame][x][y];
	}


	//===============================================================================================
	public void setPixel(int frame, int x, int y, int color)
	{//===============================================================================================
		getActiveLayer().pixels[frame][x][y] = color;
	}


	//===============================================================================================
	public void sendToTiles(EditorMain E)
	{//===============================================================================================
		//for each sprite pixel, get rgb value and look at the tileset palette for an exact or fuzzy value
		//then set that tile pixel

		//YesNoWindow ynw = new YesNoWindow(new Frame(),"Will overwrite selected tile+xy on tileset, you sure?");
		//ynw.show();
		//if(ynw.result==true)

		EditorMain.tileCanvas.tileSelected = Project.tileset.num_Tiles;
		Project.tileset.setNumTiles(Project.tileset.num_Tiles + 1 + ((hP() / 8) * TileCanvas.WIDTH_TILES));


		EditorMain.tileCanvas.scrollToSelectedTile();



		{

			for(int y = 0; y < hP(); y += 8)
			{
				for(int x = 0; x < wP(); x += 8)
				{
					for(int yy = 0; yy < 8; yy++)
					{
						for(int xx = 0; xx < 8; xx++)
						{
							// Composite layers
							int compositePixel = 0;
							for(Layer layer : layers) {
								if(!layer.visible) continue;
								int p = layer.pixels[selectedFrameIndex][x + xx][y + yy];
								if(p != 0) {
									compositePixel = p;
								}
							}

							int r = Project.getSelectedSpritePalette().data[compositePixel][0];
							int g = Project.getSelectedSpritePalette().data[compositePixel][1];
							int b = Project.getSelectedSpritePalette().data[compositePixel][2];

							int palcol = Project.getSelectedPalette().getColorIfExistsOrAddColor(r, g, b, 4);

							Project.tileset.setPixel(EditorMain.tileCanvas.tileSelected + ((y / 8) * TileCanvas.WIDTH_TILES) + (x / 8), xx, yy, palcol);

						}
					}
					EditorMain.tileCanvas.paint(EditorMain.tileCanvas.tileSelected + ((y / 8) * TileCanvas.WIDTH_TILES) + (x / 8));
					EditorMain.tileCanvas.tileSelectionArea.repaint();

				}
			}
			EditorMain.tileCanvas.repaint();

		}
		EditorMain.spriteEditor.infoLabel.setTextSuccess("Sprite Editor: Sent Sprite To Tiles.");
		EditorMain.infoLabel.setTextSuccess("Sprite Editor: Sent Sprite To Tiles.");

		EditorMain.tileCanvas.setSizedoLayout();
		EditorMain.tileCanvas.updateAllTiles();
		EditorMain.tileCanvas.paintBuffer();
		EditorMain.tileCanvas.repaint();
	}

	//===============================================================================================
	public BufferedImage getFrameImage(int frame)
	{//===============================================================================================

		BufferedImage bufferedImage = (new Frame()).getGraphicsConfiguration().createCompatibleImage(wP(), hP(), Transparency.TRANSLUCENT);

			for(int y = 0; y < hP(); y++)
			{
				for(int x = 0; x < wP(); x++)
				{
					// Composite layers
					int compositePixel = 0;
					for(Layer layer : layers) {
						if(!layer.visible) continue;
						int p = layer.pixels[frame][x][y];
						if(p != 0) {
							compositePixel = p;
						}
					}

					if(compositePixel!=0)
					bufferedImage.setRGB(x, y, (Project.getSelectedSpritePalette().getColor(compositePixel)).getRGB());
				}
			}

		return bufferedImage;
	}

	//===============================================================================================
	public BufferedImage getFrameImageTransparent(int frame)
	{//===============================================================================================

		BufferedImage bufferedImage = (new Frame()).getGraphicsConfiguration().createCompatibleImage(wP(), hP(), Transparency.TRANSLUCENT);

			for(int y = 0; y < hP(); y++)
			{
				for(int x = 0; x < wP(); x++)
				{
					// Composite layers
					int compositePixel = 0;
					for(Layer layer : layers) {
						if(!layer.visible) continue;
						int p = layer.pixels[frame][x][y];
						if(p != 0) {
							compositePixel = p;
						}
					}

					if(compositePixel!=0)
					{
						Color c = Project.getSelectedSpritePalette().getColor(compositePixel);
						Color ct = new Color(c.getRed(),c.getGreen(),c.getBlue(),127);
						bufferedImage.setRGB(x, y, ct.getRGB());
					}
				}
			}

		return bufferedImage;
	}


	//===============================================================================================
	public void outputPNG(String dirpath)
	{//===============================================================================================

		//---------------------------
		//create directory if doesn't exist
		//---------------------------
			if(dirpath==null)dirpath = EditorMain.exportDirectory;
			Utils.makeDir(dirpath + "png\\sprite\\");


		//---------------------------
		//make bufferedimage the size of all sprite frames and fill it
		//---------------------------
			BufferedImage bufferedImage = (new Frame()).getGraphicsConfiguration().createCompatibleImage(wP(), hP() * frames(), Transparency.TRANSLUCENT);
			for(int f = 0; f < frames(); f++)
			{
				for(int y = 0; y < hP(); y++)
				{
					for(int x = 0; x < wP(); x++)
					{
						// Composite layers
						int compositePixel = 0;
						for(Layer layer : layers) {
							if(!layer.visible) continue;
							int p = layer.pixels[f][x][y];
							if(p != 0) {
								compositePixel = p;
							}
						}

						if(compositePixel!=0)
						bufferedImage.setRGB(x, y + (hP() * f), (Project.getSelectedSpritePalette().getColor(compositePixel)).getRGB());
					}
				}
			}

		//---------------------------
		//save to png
		//---------------------------


			Utils.saveImage(dirpath + "png\\sprite\\" + name() + "_Sprite_" + wP() + "x" + hP() + "x" + frames() + ".png",bufferedImage);


		//---------------------------
		//write shadow frames
		//---------------------------
			bufferedImage = (new Frame()).getGraphicsConfiguration().createCompatibleImage(wP(), hP() * frames(), Transparency.TRANSLUCENT);
			for(int f = 0; f < frames(); f++)
			{
				for(int y = 0; y < hP(); y++)
				{
					for(int x = 0; x < wP(); x++)
					{
						// Composite layers for shadow calculation
						int compositePixel = 0;
						for(Layer layer : layers) {
							if(!layer.visible) continue;
							int p = layer.pixels[f][x][y];
							if(p != 0) {
								compositePixel = p;
							}
						}

						if(compositePixel!=0)
						{

							int bottom_pixel_y=hP()-1;

							//find bottom pixel to start copying shadow from so feet are exactly at the top of the frame
							for(int yy=hP()-1;yy>=0;yy--)
								for(int xx=0;xx<wP();xx++)
								{
									// Composite layers for shadow check
									int compositePixelCheck = 0;
									for(Layer layer : layers) {
										if(!layer.visible) continue;
										int p = layer.pixels[f][xx][yy];
										if(p != 0) {
											compositePixelCheck = p;
										}
									}

									if(compositePixelCheck!=0)
									{
										bottom_pixel_y = yy;
										yy=-1;
										break;
									}
								}

							//since we're not copying from the bottom, we need to stop when we reach the top, not copy the full height()
							if(bottom_pixel_y-y<0)
							{
								y=hP();
								break;
							}

							int nx = x;
							int ny = (hP() * f) + ((bottom_pixel_y)-y);
							int col = Color.black.getRGB();

							bufferedImage.setRGB(nx, ny, col);
						}
					}
				}
			}

		//---------------------------
		//save to png
		//---------------------------


			Utils.saveImage(dirpath + "png\\sprite\\" + name() + "_SpriteShadow_" + wP() + "x" + hP() + "x" + frames() + ".png",bufferedImage);



	}


	//===============================================================================================
	public void outputSpriteSheetPNG(EditorMain E)
	{//===============================================================================================

		//---------------------------
		//create directory if doesn't exist
		//---------------------------
			//if(dirpath==null)
			String dirpath = EditorMain.exportDirectory;
			Utils.makeDir(dirpath + "png\\sprite\\");


		//we want a one pixel border, 00ff00
		//background color should be actual color


			BufferedImage bufferedImage = new BufferedImage((wP() * (frames() / 8)) + ((frames() / 8) - 1), hP() * 8 + 7, Transparency.TRANSLUCENT);

		//---------------------------
		//make bufferedimage the size of all sprite frames and fill it
		//---------------------------

			for(int x=0;x<bufferedImage.getWidth();x++)
			for(int y=0;y<bufferedImage.getHeight();y++)
			bufferedImage.setRGB(x, y, new Color(255,255,255).getRGB());


			for(int f = 0; f < frames(); f++)
			{
				for(int y = 0; y < hP(); y++)
				{
					for(int x = 0; x < wP(); x++)
					{
						// Composite layers
						int compositePixel = 0;
						for(Layer layer : layers) {
							if(!layer.visible) continue;
							int p = layer.pixels[f][x][y];
							if(p != 0) {
								compositePixel = p;
							}
						}

						int offsetX = (f/8)*(wP()+1);
						int offsetY = (f%8)*(hP()+1);


						bufferedImage.setRGB(offsetX+x, offsetY+y, (Project.getSelectedSpritePalette().getColor(compositePixel)).getRGB());
					}

				}
			}

		//---------------------------
		//save to png
		//---------------------------


			Utils.saveImage(dirpath + "png\\sprite\\" + name() + ".png",bufferedImage);

	}

	//===============================================================================================
	public void outputHorizontalVerticalSpriteSheetPNGAndDescriptorTextFile(String dirpath, EditorMain E, int textureSizePowerOfTwo)
	{//===============================================================================================


		//background color should be transparent


			BufferedImage bufferedImage = new BufferedImage(textureSizePowerOfTwo,textureSizePowerOfTwo, Transparency.TRANSLUCENT);

		//---------------------------
		//make bufferedimage the size of all sprite frames and fill it
		//---------------------------

			int column = 0;
			int row = 0;

			int framesPerRow = textureSizePowerOfTwo / wP();

			for(int f = 0; f < frames(); f++)
			{
				if((column+1)*wP()>=textureSizePowerOfTwo)
				{
					row++;
					column=0;

					if((row+1)*hP()>=textureSizePowerOfTwo)
					{

						// ERROR
						System.err.println("Sprite "+name()+" cannot fit in texture size "+textureSizePowerOfTwo);
						return;
					}
				}

				for(int y = 0; y < hP(); y++)
				{
					for(int x = 0; x < wP(); x++)
					{
						// Composite layers
						int compositePixel = 0;
						for(Layer layer : layers) {
							if(!layer.visible) continue;
							int p = layer.pixels[f][x][y];
							if(p != 0) {
								compositePixel = p;
							}
						}

						int offsetX = column*wP();
						int offsetY = row*hP();

						if(compositePixel>0)//no clear
						bufferedImage.setRGB(offsetX+x, offsetY+y, (Project.getSelectedSpritePalette().getColor(compositePixel)).getRGB());
					}

				}

				column++;


			}

		//---------------------------
		//save to png
		//---------------------------


			Utils.saveImage(dirpath + name() + ".png",bufferedImage);

		//---------------------------
		//save text file
		//---------------------------

			//id,name,w,h,frames

			File sessionFile = new File(dirpath + name() + ".txt");

			if(sessionFile.exists()==false)
			{
				try
				{
					sessionFile.createNewFile();
				}
				catch (IOException e1)
				{
					e1.printStackTrace();
				}
			}

			PrintWriter output;
			try
			{
				output = new PrintWriter(new BufferedWriter(new FileWriter(sessionFile)));
				output.println("id:"+id());
				output.println("name:"+name());
				output.println("width:"+wP());
				output.println("height:"+hP());
				output.println("frames:"+frames());

				for(int i=0;i<animationList().size();i++)
				{
					SpriteAnimationSequence a = animationList().get(i);

					output.println("animation:"+a.frameSequenceName+":"+a.frameStart);
				}

				output.close();
			}
			catch (IOException e)
			{
				e.printStackTrace();
			}


	}




	//===============================================================================================
	public void antialiasBufferedImage(BufferedImage bufferedImage)
	{//===============================================================================================

		//go through hq2x image
		//if pixel is transparent, and the pixel right and down, down and left, left and up, or up and right are black, this one is black

		//have to make a copy otherwise the algorithm becomes recursive
		BufferedImage copy = new BufferedImage(bufferedImage.getWidth(), bufferedImage.getHeight(), BufferedImage.TYPE_INT_ARGB);
		for(int y = 0; y < bufferedImage.getHeight(); y++)
		{
			for(int x = 0; x < bufferedImage.getWidth(); x++)
			{
				copy.setRGB(x, y, bufferedImage.getRGB(x,y));
			}
		}

		int clear = new Color(0,0,0,0).getRGB();

		for(int y = 0; y < bufferedImage.getHeight(); y++)
		{
			for(int x = 0; x < bufferedImage.getWidth(); x++)
			{
				if(copy.getRGB(x, y)==clear)
				{
					int black=0;

					//check right and down
					if(x+1<bufferedImage.getWidth()&&y+1<bufferedImage.getHeight())
					{
						if(
								copy.getRGB(x+1, y)!=clear&&
								copy.getRGB(x, y+1)!=clear
						)
						black=1;
					}

					//check right and up
					if(x+1<bufferedImage.getWidth()&&y-1>=0)
					{
						if(
								copy.getRGB(x+1, y)!=clear&&
								copy.getRGB(x, y-1)!=clear
						)
						black=1;
					}


					//check left and down
					if(x-1>=0&&y+1<bufferedImage.getHeight())
					{
						if(
								copy.getRGB(x-1, y)!=clear&&
								copy.getRGB(x, y+1)!=clear
						)
						black=1;
					}

					//check left and up
					if(x-1>=0&&y-1>=0)
					{
						if(
								copy.getRGB(x-1, y)!=clear&&
								copy.getRGB(x, y-1)!=clear
						)
						black=1;
					}

					if(black==1)bufferedImage.setRGB(x, y, new Color(0,0,0,127).getRGB());
				}

			}
		}
	}

	//===============================================================================================
	public void setHQ2XAlphaFromOriginal(BufferedImage hq2xBufferedImage, BufferedImage bufferedImage)
	{//===============================================================================================
		//now go through original image again. take each transparent pixel and set the hq2x one with it at 2x
		for(int y = 0; y < bufferedImage.getHeight(); y++)
		{
			for(int x = 0; x < bufferedImage.getWidth(); x++)
			{
				if(bufferedImage.getRGB(x, y)==0)
				{
					for(int xx=0;xx<2;xx++)
					for(int yy=0;yy<2;yy++)
						hq2xBufferedImage.setRGB((x*2)+xx, ((y*2)+yy), new Color(0,0,0,0).getRGB());
				}

			}
		}
	}

	//===============================================================================================
	public void outputHQ2XPNG(String dirpath, EditorMain E)
	{//===============================================================================================

		//---------------------------
		//create directory if doesn't exist
		//---------------------------
		if(dirpath==null)dirpath = EditorMain.exportDirectory;
		Utils.makeDir(dirpath + "png\\sprite\\");



		//---------------------------
		//make bufferedimage the size of all sprite frames and fill it
		//---------------------------


			//BufferedImage bufferedImage = (new Frame()).getGraphicsConfiguration().createCompatibleImage(width(), (height()) * frames(), Transparency.TRANSLUCENT);
			BufferedImage bufferedImage = new BufferedImage(wP(), hP()* frames(), BufferedImage.TYPE_INT_ARGB);
			for(int f = 0; f < frames(); f++)
			{
				for(int y = 0; y < hP(); y++)
				{
					for(int x = 0; x < wP(); x++)
					{
						// Composite layers
						int compositePixel = 0;
						for(Layer layer : layers) {
							if(!layer.visible) continue;
							int p = layer.pixels[f][x][y];
							if(p != 0) {
								compositePixel = p;
							}
						}

						if(compositePixel!=0)
						bufferedImage.setRGB(x, y + (hP() * f), (Project.getSelectedSpritePalette().getColor(compositePixel)).getRGB());
					}
				}
			}

			BufferedImage hq2xBufferedImage = new HQ2X().HQ2X(bufferedImage);

			setHQ2XAlphaFromOriginal(hq2xBufferedImage,bufferedImage);

			antialiasBufferedImage(hq2xBufferedImage);

			bufferedImage = hq2xBufferedImage;



		//---------------------------
		//save to png
		//---------------------------

			Utils.saveImage(dirpath + "png\\sprite\\" + name() + "_Sprite_HQ2X_" + wP()*2 + "x" + hP()*2 + "x" + frames() + ".png",bufferedImage);


		//---------------------------
		//write shadow frames
		//---------------------------


			//bufferedImage = (new Frame()).getGraphicsConfiguration().createCompatibleImage(width(), (height()) * frames(), Transparency.TRANSLUCENT);
			bufferedImage = new BufferedImage(wP(), hP()* frames(), BufferedImage.TYPE_INT_ARGB);
			for(int f = 0; f < frames(); f++)
			{
				for(int y = 0; y < hP(); y++)
				{
					for(int x = 0; x < wP(); x++)
					{
						// Composite layers for shadow
						int compositePixel = 0;
						for(Layer layer : layers) {
						if(!layer.visible || layer.isReference) continue;
							int p = layer.pixels[f][x][y];
							if(p != 0) {
								compositePixel = p;
							}
						}

						if(compositePixel!=0)
						{

							int bottom_pixel_y=hP()-1;

							//find bottom pixel to start copying shadow from so feet are exactly at the top of the frame
							for(int yy=hP()-1;yy>=0;yy--)
								for(int xx=0;xx<wP();xx++)
								{
									// Composite layers for shadow check
									int compositePixelCheck = 0;
									for(Layer layer : layers) {
										if(!layer.visible) continue;
										int p = layer.pixels[f][xx][yy];
										if(p != 0) {
											compositePixelCheck = p;
										}
									}

									if(compositePixelCheck!=0)
									{
										bottom_pixel_y = yy;
										yy=-1;
										break;
									}
								}

							//since we're not copying from the bottom, we need to stop when we reach the top, not copy the full height()
							if(bottom_pixel_y-y<0)
							{
								y=hP();
								break;
							}

							int nx = x;
							int ny = (hP() * f) + ((bottom_pixel_y)-y);
							int col = Color.black.getRGB();

							bufferedImage.setRGB(nx, ny, col);
						}
					}
				}
			}

			BufferedImage hq2xShadowBufferedImage = new HQ2X().HQ2X(bufferedImage);

			setHQ2XAlphaFromOriginal(hq2xShadowBufferedImage,bufferedImage);

			antialiasBufferedImage(hq2xShadowBufferedImage);

			bufferedImage = hq2xShadowBufferedImage;


		//---------------------------
		//save to png
		//---------------------------

			Utils.saveImage(dirpath + "png\\sprite\\" + name() + "_SpriteShadow_HQ2X_" + wP()*2 + "x" + hP()*2 + "x" + frames() + ".png",bufferedImage);


	}





	//===============================================================================================
	public void duplicateToHQ2XSprite()
	{//===============================================================================================



		//---------------------------
		//make bufferedimage the size of all sprite frames and fill it
		//---------------------------


			//BufferedImage bufferedImage = (new Frame()).getGraphicsConfiguration().createCompatibleImage(width(), (height()) * frames(), Transparency.TRANSLUCENT);
			BufferedImage bufferedImage = new BufferedImage(wP(), hP()* frames(), BufferedImage.TYPE_INT_ARGB);
			for(int f = 0; f < frames(); f++)
			{
				for(int y = 0; y < hP(); y++)
				{
					for(int x = 0; x < wP(); x++)
					{
						// Composite layers
						int compositePixel = 0;
						for(Layer layer : layers) {
							if(!layer.visible) continue;
							int p = layer.pixels[f][x][y];
							if(p != 0) {
								compositePixel = p;
							}
						}

						if(compositePixel!=0)
						bufferedImage.setRGB(x, y + (hP() * f), (Project.getSelectedSpritePalette().getColor(compositePixel)).getRGB());
					}
				}
			}

			BufferedImage hq2xBufferedImage = new HQ2X().HQ2X(bufferedImage);

			setHQ2XAlphaFromOriginal(hq2xBufferedImage,bufferedImage);

			//antialiasBufferedImage(hq2xBufferedImage);

			bufferedImage = hq2xBufferedImage;



			Sprite s = this.duplicate();

			s.setSize(wP()*2,hP()*2);


			for(int f = 0; f < s.frames(); f++)
			{
				for(int y = 0; y < s.hP(); y++)
				{
					for(int x = 0; x < s.wP(); x++)
					{

						Color c = new Color(bufferedImage.getRGB(x, y + (s.hP() * f)));

						int colorIndex = 0;
						if(c.getAlpha()==255)	colorIndex = Project.getSelectedSpritePalette().getColorIfExistsOrAddColor(c.getRed(),c.getGreen(),c.getBlue(),16);

						s.setPixel(f,x,y,colorIndex);

					}
				}
			}


	}






	public SpriteData getData(){return data;}

	public int id(){return data.id();}
	public String name(){return data.name();}
	public String getTYPEIDString(){return data.getTYPEIDString();}

	public String comment(){return data.comment();}

	public int wP(){return data.widthPixels1X();}
	public int hP(){return data.heightPixels1X();}
	public int frames(){return data.frames();}
	public String displayName(){return data.displayName();}
	public boolean isNPC(){return data.isNPC();}
	public boolean isKid(){return data.isKid();}
	public boolean isAdult(){return data.isAdult();}
	public boolean isMale(){return data.isMale();}
	public boolean isFemale(){return data.isFemale();}
	public boolean isCar(){return data.isCar();}
	public boolean isAnimal(){return data.isAnimal();}
	public boolean hasShadow(){return data.hasShadow();}
	public boolean isRandom(){return data.isRandom();}
	public boolean isDoor(){return data.isDoor();}
	public boolean isGame(){return data.isGame();}
	public boolean isItem(){return data.isItem();}
	public boolean forceHQ2X(){return data.forceHQ2X();}
	public boolean forceMD5Export(){return data.forceMD5Export();}
	public EventData eventData(){return data.eventData();}
	public String itemGameDescription(){return data.itemGameDescription();}

	public String dataMD5(){return data.dataMD5();}
	public String paletteMD5(){return data.paletteMD5();}

	public float gamePrice(){return data.gamePrice();}
	public int utilityOffsetXPixels1X(){return data.utilityOffsetXPixels1X();}
	public int utilityOffsetYPixels1X(){return data.utilityOffsetYPixels1X();}
	public ArrayList<SpriteAnimationSequence> animationList(){return data.animationList();}




	public void setName(String s){data.setName(s);}
	public void setComment(String s){data.setComment(s);}
	public void setID(int s){data.setID(s);}
	public void setWidthPixels(int s){data.setWidthPixels1X(s);}
	public void setHeightPixels(int s){data.setHeightPixels1X(s);}
	public void setFrames(int s){data.setFrames(s);}
	public void setDisplayName(String s){data.setDisplayName(s);}
	public void setIsNPC(boolean s){data.setIsNPC(s);}
	public void setIsKid(boolean s){data.setIsKid(s);}
	public void setIsAdult(boolean s){data.setIsAdult(s);}
	public void setIsMale(boolean s){data.setIsMale(s);}
	public void setIsFemale(boolean s){data.setIsFemale(s);}
	public void setIsCar(boolean s){data.setIsCar(s);}
	public void setIsAnimal(boolean s){data.setIsAnimal(s);}
	public void setHasShadow(boolean s){data.setHasShadow(s);}
	public void setIsRandom(boolean s){data.setIsRandom(s);}
	public void setIsDoor(boolean s){data.setIsDoor(s);}
	public void setIsGame(boolean s){data.setIsGame(s);}
	public void setIsItem(boolean s){data.setIsItem(s);}
	public void setForceHQ2X(boolean s){data.setForceHQ2X(s);}
	public void setForceMD5Export(boolean s){data.setForceMD5Export(s);}
	public void setEventData(EventData s){data.setEventData(s);}
	public void setItemGameDescription(String s){data.setItemGameDescription(s);}

	public void setDataMD5(String s){data.setDataMD5(s);}
	public void setPaletteMD5(String s){data.setPaletteMD5(s);}

	public void setGamePrice(float s){data.setGamePrice(s);}
	public void setUtilityOffsetXPixels1X(int s){data.setUtilityOffsetXPixels1X(s);}
	public void setUtilityOffsetYPixels1X(int s){data.setUtilityOffsetYPixels1X(s);}

}
