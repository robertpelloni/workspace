package com.bobsgame.editor.SpriteEditor;

import java.io.*;

import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;

import javax.swing.JFrame;

import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.Sprite.Sprite;
//===============================================================================================
public class SEBitmapSpriteLoader extends JFrame implements WindowListener, ActionListener, TextListener, ImageObserver, ItemListener
{//===============================================================================================

	/**
	 *
	 */
	private static final long serialVersionUID = 1L;

	private FileDialog filedialog;
	private Button loadBitmapButton, createSpriteButton, createDitheredSpriteButton;
	private TextField spriteSizeX;
	private TextField spriteSizeY;
	private TextField borderSize;
	private TextField frames;
	private TextField directions;
	private SEBitmapSplicer splicer;
	private ScrollPane scroll;
	public BufferedImage image;
	public Sprite newSprite;
	public SpriteEditor SE;

	public Checkbox isRandomCheckbox = null;

	//===============================================================================================
	SEBitmapSpriteLoader(SpriteEditor se)
	{//===============================================================================================
		super("Bitmap Sprite Loader");
		setSize(350, 700);

		SE = se;

		filedialog = new FileDialog(this, "Select File", FileDialog.LOAD);
		splicer = new SEBitmapSplicer();
		scroll = new ScrollPane();
		scroll.setBackground(Color.DARK_GRAY);
		scroll.add(splicer);
		splicer.addPane(scroll);
		add(scroll, BorderLayout.CENTER);
		Panel top = new Panel();
		top.setBackground(SystemColor.menu);
		add(top, BorderLayout.NORTH);
		loadBitmapButton = new Button("Load Bitmap");
		loadBitmapButton.addActionListener(this);
		top.add(loadBitmapButton);


		//horizontalDivisions = new TextField(2);
		//horizontalDivisions.addTextListener(this);
		//verticalDivisions = new TextField(2);
		//verticalDivisions.addTextListener(this);

		spriteSizeX = new TextField(2);
		spriteSizeX.addTextListener(this);
		spriteSizeY = new TextField(2);
		spriteSizeY.addTextListener(this);

		frames = new TextField(2);
		frames.addTextListener(this);
		directions = new TextField(2);
		directions.addTextListener(this);

		borderSize = new TextField(2);
		borderSize.addTextListener(this);

		top.add(new Label("Sprite Size X"));
		top.add(spriteSizeX);

		top.add(new Label("Sprite Size Y"));
		top.add(spriteSizeY);

		top.add(new Label("Frames"));
		top.add(frames);

		top.add(new Label("Directions"));
		top.add(directions);

		top.add(new Label("Border px"));
		top.add(borderSize);

		isRandomCheckbox = new Checkbox("Use Random Colors?");
		isRandomCheckbox.addItemListener(this);

		top.add(isRandomCheckbox);


		createSpriteButton = new Button("Create Sprite");
		createSpriteButton.addActionListener(this);
		top.add(createSpriteButton);

		createDitheredSpriteButton = new Button("Dither Sprite");
		createDitheredSpriteButton.addActionListener(this);
		top.add(createDitheredSpriteButton);

		addWindowListener(this);
		setVisible(true);
	}
	//===============================================================================================
	public void windowClosing(WindowEvent we)
	{//===============================================================================================
		setVisible(false);
	}
	//===============================================================================================
	public void windowOpened(WindowEvent we)
	{//===============================================================================================
	}
	//===============================================================================================
	public void windowClosed(WindowEvent we)
	{//===============================================================================================
	}
	//===============================================================================================
	public void windowIconified(WindowEvent we)
	{//===============================================================================================
	}
	//===============================================================================================
	public void windowDeiconified(WindowEvent we)
	{//===============================================================================================
	}
	//===============================================================================================
	public void windowActivated(WindowEvent we)
	{//===============================================================================================
	}
	//===============================================================================================
	public void windowDeactivated(WindowEvent we)
	{//===============================================================================================
	}
	//===============================================================================================
	public void actionPerformed(ActionEvent ae)
	{//===============================================================================================
		if(ae.getSource() == loadBitmapButton)
		{
			filedialog.setTitle("Load Bitmap File");
			filedialog.setVisible(true);
			Image tempimage = loadBitmap(filedialog.getDirectory(), filedialog.getFile());
			image = getGraphicsConfiguration().createCompatibleImage(tempimage.getWidth(this), tempimage.getHeight(this), Transparency.OPAQUE);
			image.getGraphics().drawImage(tempimage, 0, 0, this);
			if(image != null)
			{
				splicer.setImage(image);
			}
		}
		else if(ae.getSource() == createSpriteButton)
		{
			newSprite = splicer.generateSprite(Project.getSelectedSpritePalette(), SE);
			// Add sprite to the tileset
			// Update Sprite editor
			SE.updateInfo();
			SpriteEditor.controlPanel.repaint();
			SpriteEditor.editCanvas.repaintBufferImage();
			SpriteEditor.editCanvas.setSizeDoLayout();
			SpriteEditor.editCanvas.repaint();
			// Close Window
			setVisible(false);
		}
		else if(ae.getSource() == createDitheredSpriteButton)
		{
			newSprite = splicer.generateDitheredSprite(Project.getSelectedSpritePalette(), SE);
			// Add sprite to the tileset
			// Update Sprite editor
			SE.updateInfo();
			SpriteEditor.controlPanel.repaint();
			SpriteEditor.editCanvas.repaintBufferImage();
			SpriteEditor.editCanvas.setSizeDoLayout();
			SpriteEditor.editCanvas.repaint();
			// Close Window
			setVisible(false);
		}

	}
	//===============================================================================================
	public void textValueChanged(TextEvent te)
	{//===============================================================================================
		if(te.getSource() == spriteSizeX)
		{
			splicer.spriteSizeX = (Integer.parseInt(spriteSizeX.getText()));
		}
		else if(te.getSource() == spriteSizeY)
		{
			splicer.spriteSizeY = (Integer.parseInt(spriteSizeY.getText()));
		}
		else if(te.getSource() == frames)
		{
			splicer.frames = (Integer.parseInt(frames.getText()));
		}
		else if(te.getSource() == directions)
		{
			splicer.directions = (Integer.parseInt(directions.getText()));
		}
		else if(te.getSource() == borderSize)
		{
			splicer.borderSize = (Integer.parseInt(borderSize.getText()));
		}
	}
	//===============================================================================================
	public Image loadBitmap(String sdir, String sfile)
	{//===============================================================================================
		Image image;
		System.out.println("loading: " + sdir + sfile);
		try
		{
			FileInputStream fs = new FileInputStream(sdir + sfile);
			int bflen = 14;  // 14 byte BITMAPFILEHEADER
			byte bf[] = new byte[bflen];
			fs.read(bf, 0, bflen);
			int bilen = 40; // 40-byte BITMAPINFOHEADER
			byte bi[] = new byte[bilen];
			fs.read(bi, 0, bilen);

// Interperet data.
			int nsize = (((int) bf[5] & 0xff) << 24) | (((int) bf[4] & 0xff) << 16) | (((int) bf[3] & 0xff) << 8) | (int) bf[2] & 0xff;
			System.out.println("File type is :" + (char) bf[0] + (char) bf[1]);
			System.out.println("Size of bmp is :" + nsize);

			int nbisize = (((int) bi[3] & 0xff) << 24) | (((int) bi[2] & 0xff) << 16) | (((int) bi[1] & 0xff) << 8) | (int) bi[0] & 0xff;
			System.out.println("Size of bitmapinfoheader is :" + nbisize);

			int nwidth = (((int) bi[7] & 0xff) << 24) | (((int) bi[6] & 0xff) << 16) | (((int) bi[5] & 0xff) << 8) | (int) bi[4] & 0xff;
			System.out.println("Width is :" + nwidth);

			int nheight = (((int) bi[11] & 0xff) << 24) | (((int) bi[10] & 0xff) << 16) | (((int) bi[9] & 0xff) << 8) | (int) bi[8] & 0xff;
			System.out.println("Height is :" + nheight);

			int nplanes = (((int) bi[13] & 0xff) << 8) | (int) bi[12] & 0xff;
			System.out.println("Planes is :" + nplanes);

			int nbitcount = (((int) bi[15] & 0xff) << 8) | (int) bi[14] & 0xff;
			System.out.println("BitCount is :" + nbitcount);

// Look for non-zero values to indicate compression
			int ncompression = (((int) bi[19]) << 24) | (((int) bi[18]) << 16) | (((int) bi[17]) << 8) | (int) bi[16];
			System.out.println("Compression is :" + ncompression);

			int nsizeimage = (((int) bi[23] & 0xff) << 24) | (((int) bi[22] & 0xff) << 16) | (((int) bi[21] & 0xff) << 8) | (int) bi[20] & 0xff;
			System.out.println("SizeImage is :" + nsizeimage);

			int nxpm = (((int) bi[27] & 0xff) << 24) | (((int) bi[26] & 0xff) << 16) | (((int) bi[25] & 0xff) << 8) | (int) bi[24] & 0xff;
			System.out.println("X-Pixels per meter is :" + nxpm);

			int nypm = (((int) bi[31] & 0xff) << 24) | (((int) bi[30] & 0xff) << 16) | (((int) bi[29] & 0xff) << 8) | (int) bi[28] & 0xff;
			System.out.println("Y-Pixels per meter is :" + nypm);

			int nclrused = (((int) bi[35] & 0xff) << 24) | (((int) bi[34] & 0xff) << 16) | (((int) bi[33] & 0xff) << 8) | (int) bi[32] & 0xff;
			System.out.println("Colors used are :" + nclrused);

			int nclrimp = (((int) bi[39] & 0xff) << 24) | (((int) bi[38] & 0xff) << 16) | (((int) bi[37] & 0xff) << 8) | (int) bi[36] & 0xff;
			System.out.println("Colors important are :" + nclrimp);

			if(nbitcount == 24)
			{
// No Palatte data for 24-bit format but scan lines are
// padded out to even 4-byte boundaries.
				int npad = (nsizeimage / nheight) - nwidth * 3;
				int ndata[] = new int[nheight * nwidth];
				byte brgb[] = new byte[(nwidth + npad) * 3 * nheight];
				fs.read(brgb, 0, (nwidth + npad) * 3 * nheight);
				int nindex = 0;
				for(int j = 0; j < nheight; j++)
				{
					for(int i = 0; i < nwidth; i++)
					{
						ndata[nwidth * (nheight - j - 1) + i] = (255 & 0xff) << 24 | (((int) brgb[nindex + 2] & 0xff) << 16) | (((int) brgb[nindex + 1] & 0xff) << 8) | (int) brgb[nindex] & 0xff;
// System.out.println("Encoded Color at ("+i+","+j+")is:"+nrgb+" (R,G,B)= ("+((int)(brgb[2]) & 0xff)+","+((int)brgb[1]&0xff)+","+((int)brgb[0]&0xff)+")");
						nindex += 3;
					}
					nindex += npad;
				}

				image = createImage(new MemoryImageSource(nwidth, nheight, ndata, 0, nwidth));
			}
			else if(nbitcount == 8)
			{
// Have to determine the number of colors, the clrsused
// parameter is dominant if it is greater than zero.  If
// zero, calculate colors based on bitsperpixel.
				int nNumColors = 0;
				if(nclrused > 0)
				{
					nNumColors = nclrused;
				}
				else
				{
					nNumColors = (1 & 0xff) << nbitcount;
				}
				System.out.println("The number of Colors is" + nNumColors);

// Some bitmaps do not have the sizeimage field calculated
// Ferret out these cases and fix 'em.
				if(nsizeimage == 0)
				{
					nsizeimage = ((((nwidth * nbitcount) + 31) & ~31) >> 3);
					nsizeimage *= nheight;
					System.out.println("nsizeimage (backup) is" + nsizeimage);
				}

// Read the palatte colors.
				int npalette[] = new int[nNumColors];
				byte bpalette[] = new byte[nNumColors * 4];
				fs.read(bpalette, 0, nNumColors * 4);
				int nindex8 = 0;
				for(int n = 0; n < nNumColors; n++)
				{
					npalette[n] = (255 & 0xff) << 24 | (((int) bpalette[nindex8 + 2] & 0xff) << 16) | (((int) bpalette[nindex8 + 1] & 0xff) << 8) | (int) bpalette[nindex8] & 0xff;
// System.out.println ("Palette Color "+n+" is:"+ngetPalette(n)+" (res,R,G,B)= ("+((int)(bgetPalette(nindex8+3)) & 0xff)+","+((int)(bgetPalette(nindex8+2)) & 0xff)+","+((int)bgetPalette(nindex8+1)&0xff)+","+((int)bgetPalette(nindex8)&0xff)+")");
					nindex8 += 4;
				}

// Read the image data (actually indices into the palette)
// Scan lines are still padded out to even 4-byte
// boundaries.
				int npad8 = (nsizeimage / nheight) - nwidth;
				System.out.println("nPad is:" + npad8);

				int ndata8[] = new int[nwidth * nheight];
				byte bdata[] = new byte[(nwidth + npad8) * nheight];
				fs.read(bdata, 0, (nwidth + npad8) * nheight);
				nindex8 = 0;
				for(int j8 = 0; j8 < nheight; j8++)
				{
					for(int i8 = 0; i8 < nwidth; i8++)
					{
						ndata8[nwidth * (nheight - j8 - 1) + i8] = npalette[((int) bdata[nindex8] & 0xff)];
						nindex8++;
					}
					nindex8 += npad8;
				}
				image = createImage(new MemoryImageSource(nwidth, nheight, ndata8, 0, nwidth));
			}
			else
			{
				System.out.println("Not a 24-bit or 8-bit Windows Bitmap, aborting...");
				image = (Image) null;
			}

			fs.close();
			return image;
		}
		catch(IOException e)
		{
			System.out.println("Caught exception in loadbitmap!");
		}
		return (Image) null;
	}




	//===============================================================================================
	@Override
	public void itemStateChanged(ItemEvent e)
	{//===============================================================================================
		if(e.getSource()==isRandomCheckbox)splicer.isRandom=isRandomCheckbox.getState();

	}
}
