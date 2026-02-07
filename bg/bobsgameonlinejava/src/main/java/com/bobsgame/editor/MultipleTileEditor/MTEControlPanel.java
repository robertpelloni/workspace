package com.bobsgame.editor.MultipleTileEditor;

import java.awt.BorderLayout;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Frame;
import java.awt.Graphics;
import java.awt.GridLayout;

import java.awt.SystemColor;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import com.bobsgame.EditorMain;
import com.bobsgame.editor.ControlPanel.PaletteCanvas;
import com.bobsgame.editor.Dialogs.StringDialog;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.Sprite.Sprite;


//===============================================================================================
public class MTEControlPanel extends JPanel implements ActionListener
{//===============================================================================================

	/**
	 *
	 */
	private static final long serialVersionUID = 1L;

	public EditorMain E;
	protected MultipleTileEditor MTE;


	public MTEPaletteCanvas paletteCanvas;


	public JLabel colorNumLabel, rgbLabel, hsbLabel, bgrLabel;
	public JPanel colorInfoPanel, selectedColorPanel;
	private JPanel refreshMapButtonPanel;
	private JPanel sendToSpriteEditorButtonPanel;

	private JButton sendToSpriteEditorButton;
	private JButton refreshMapButton;

	public JScrollPane paletteScrollPane;

	//===============================================================================================
	public MTEControlPanel(MultipleTileEditor mte)
	{//===============================================================================================

		super(new BorderLayout());
		MTE = mte;
		E=MTE.E;


		setBackground(Color.BLACK);
		setForeground(Color.WHITE);

		addKeyListener(MTE.editCanvas);




		refreshMapButton = new JButton("Refresh Map");
		refreshMapButton.addActionListener(this);

		refreshMapButtonPanel = new JPanel();
		refreshMapButtonPanel.setBackground(SystemColor.menu);
		refreshMapButtonPanel.setForeground(Color.BLACK);
		refreshMapButtonPanel.add(refreshMapButton);


		sendToSpriteEditorButton = new JButton("Send To Sprite Editor");
		sendToSpriteEditorButton.addActionListener(this);

		sendToSpriteEditorButtonPanel = new JPanel();
		sendToSpriteEditorButtonPanel.setBackground(SystemColor.menu);
		sendToSpriteEditorButtonPanel.setForeground(Color.BLACK);
		sendToSpriteEditorButtonPanel.add(sendToSpriteEditorButton);


		JPanel buttonPanel = new JPanel(new GridLayout(0,1,0,0));

		buttonPanel.add(sendToSpriteEditorButtonPanel);
		buttonPanel.add(refreshMapButtonPanel);



		//-----------------------------
		//labels
		//-----------------------------


			colorNumLabel = new JLabel(" Color 0", JLabel.LEFT);
			colorNumLabel.setForeground(Color.WHITE);
			colorNumLabel.setFont(new Font("Tahoma", Font.BOLD, 10));
			//colorNumLabel.setMaximumSize(new Dimension(130, 20));

			rgbLabel = new JLabel(" RGB:0,0,0", JLabel.LEFT);
			rgbLabel.setForeground(Color.WHITE);
			rgbLabel.setFont(new Font("Tahoma", Font.PLAIN, 10));
			//rgbLabel.setMaximumSize(new Dimension(130, 20));

			hsbLabel = new JLabel(" HSB:0,0,0", JLabel.LEFT);
			hsbLabel.setForeground(Color.WHITE);
			hsbLabel.setFont(new Font("Tahoma", Font.PLAIN, 10));
			//hsbLabel.setMaximumSize(new Dimension(130, 20));

			bgrLabel = new JLabel(" BGR:0", JLabel.LEFT);
			bgrLabel.setForeground(Color.WHITE);
			bgrLabel.setFont(new Font("Tahoma", Font.PLAIN, 10));
			//bgrLabel.setMaximumSize(new Dimension(130, 20));



			colorInfoPanel = new JPanel();
			colorInfoPanel.setLayout(new GridLayout(0,1,0,0));
			colorInfoPanel.setBackground(Color.BLACK);

			colorInfoPanel.add(colorNumLabel);
			colorInfoPanel.add(rgbLabel);
			colorInfoPanel.add(hsbLabel);
			colorInfoPanel.add(bgrLabel);


			selectedColorPanel = new JPanel();
			selectedColorPanel.setBackground(Color.BLACK);

			JPanel colorPanel = new JPanel();
			colorPanel.setLayout(new GridLayout(0,2,1,1));
			colorPanel.setBackground(Color.BLACK);

			JPanel spacerPanel = new JPanel();
			spacerPanel.setLayout(new BoxLayout(spacerPanel,BoxLayout.PAGE_AXIS));
			spacerPanel.add(Box.createRigidArea(new Dimension(60,1)));

			colorPanel.add(Box.createRigidArea(new Dimension(90,1)));
			colorPanel.add(Box.createRigidArea(new Dimension(90,1)));

			colorPanel.add(colorInfoPanel);
			colorPanel.add(selectedColorPanel);


			JPanel topPanel = new JPanel();
			topPanel.setLayout(new BorderLayout());

			topPanel.add(colorPanel,BorderLayout.NORTH);

		//-----------------------------
		//palette panel
		//-----------------------------

			paletteCanvas = new MTEPaletteCanvas(MTE);

			Dimension palD = new Dimension(((PaletteCanvas.colorsPerRow*paletteCanvas.swathSize))+paletteCanvas.PaletteGrid_x+2, (paletteCanvas.colorsPerColumn*paletteCanvas.swathSize)+paletteCanvas.PaletteGrid_y+2);


			paletteCanvas.setSize(palD);
			paletteCanvas.setPreferredSize(palD);
			paletteCanvas.setMinimumSize(palD);
			paletteCanvas.setMaximumSize(palD);


			paletteScrollPane = new JScrollPane(paletteCanvas, JScrollPane.VERTICAL_SCROLLBAR_ALWAYS ,JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
//			{
//				@Override
//				public void doLayout()
//				{
//					super.doLayout();
//
//					/*int height = (E.controlPanel.getHeight()-buttonPanel.getHeight())-tileEditCanvas.getHeight()-colorInfoPanel.getHeight();
//					int maxheight = ((paletteCanvas.colorsPerColumn*paletteCanvas.swathSize)+paletteCanvas.PaletteGrid_y+2)+4;
//					if(height>maxheight)height=maxheight;
//					setSize(new Dimension(((paletteCanvas.colorsPerRow*paletteCanvas.swathSize))+paletteCanvas.PaletteGrid_x+2+24,height));*/
//
//					//mteTileEditCanvas.setSize(new Dimension((tileEditCanvas.EditZoom*8)+(tileEditCanvas.EditGrid_x*2)+1,(tileEditCanvas.EditZoom*8)+(tileEditCanvas.EditGrid_x*2)+1));
//					paletteCanvas.setSize(new Dimension(((PaletteCanvas.colorsPerRow*paletteCanvas.swathSize))+paletteCanvas.PaletteGrid_x+2, (paletteCanvas.colorsPerColumn*paletteCanvas.swathSize)+paletteCanvas.PaletteGrid_y+2));
//				}
//			};


			paletteScrollPane.setFocusable(false);
			paletteScrollPane.setWheelScrollingEnabled(false);
			paletteScrollPane.setForeground(Color.BLACK);
			paletteScrollPane.setBackground(Color.BLACK);

			paletteScrollPane.setPreferredSize(new Dimension((PaletteCanvas.colorsPerRow*16)+25, 32*16));


			paletteScrollPane.doLayout();


			topPanel.add(paletteScrollPane,BorderLayout.CENTER);


		add(topPanel,BorderLayout.CENTER);
		add(buttonPanel, BorderLayout.SOUTH);


	}
	//===============================================================================================
	public void paint(Graphics G)
	{//===============================================================================================

		super.paint(G);
		//mteTileEditCanvas.paint();
		paletteCanvas.paint();

	}

	//===============================================================================================
	public void actionPerformed(ActionEvent ae)
	{//===============================================================================================
		if(ae.getSource() == refreshMapButton)
		{

			EditorMain.tileCanvas.updateAllTiles();
			EditorMain.tileCanvas.paint();

			//tiles have changed, so we should update the whole map.
			//in theory, we could find every changed tile and just draw them into mapcanvasimage or each layer image


			//if buffered, we need to update all the layers and then draw them into mapcanvasimage.
			//if not buffered, we need to update a lot of stuff.
			//so we should do this every time.
			EditorMain.mapCanvas.updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();

		}
		else
		if(ae.getSource()==sendToSpriteEditorButton)
		{

			//ask for name?
			StringDialog sw = new StringDialog(new Frame(), "Sprite Name?");
			sw.show("Sprite" + Project.getNumSprites());

			String name = sw.newName.getText();

			//make new sprite with these dimensions

			//Sprite sprite =
			new Sprite(name, 1, MTE.widthTiles*8, MTE.heightTiles*8);

			Project.setSelectedSpriteIndex(Project.getNumSprites()-1);

			//for each pixel, try to find color in sprite palette. if not exist, add it.
			//set the sprite data to the sprite palette color
			for(int x=0;x<MTE.widthTiles*8;x++)
			for(int y=0;y<MTE.heightTiles*8;y++)
			{

				Color pixelColor = Project.getSelectedPalette().getColor(MTE.editCanvas.getPixel(x,y));

				int r = pixelColor.getRed();
				int g = pixelColor.getGreen();
				int b = pixelColor.getBlue();

				int newColorIndex = Project.getSelectedSpritePalette().getColorIfExistsOrAddColor(r, g, b, 0);
				Project.getSelectedSprite().setPixel(0, x, y, newColorIndex);

			}

			MTE.infoLabel.setTextSuccess("MTE: Sent Tiles to Sprite Editor.");
			EditorMain.infoLabel.setTextSuccess("MTE: Sent Tiles To Sprite Editor.");


		}
	}



}
