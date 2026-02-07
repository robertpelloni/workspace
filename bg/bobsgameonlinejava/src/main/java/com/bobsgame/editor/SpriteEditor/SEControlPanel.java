package com.bobsgame.editor.SpriteEditor;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Frame;
import java.awt.Graphics;
import java.awt.GridLayout;
import java.awt.Label;
import java.awt.Panel;
import java.awt.ScrollPane;
import java.awt.SystemColor;
import java.awt.TextField;
import java.awt.Transparency;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.InputEvent;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;
import java.awt.event.TextEvent;
import java.awt.event.TextListener;
import java.awt.image.BufferedImage;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.Timer;

import com.bobsgame.editor.ControlPanel.PaletteCanvas;


//===============================================================================================
public class SEControlPanel extends JPanel
{//===============================================================================================MouseListener, MouseMotionListener,

	/**
	 *
	 */
	private static final long serialVersionUID = 1L;
	protected SpriteEditor SE;

	public SEPaletteCanvas paletteCanvas;

	public JScrollPane paletteScrollPane;

	public JLabel colorNumLabel, rgbLabel, hsbLabel, bgrLabel;
	public JPanel colorInfoPanel, selectedColorPanel;


	//===============================================================================================
	public SEControlPanel(SpriteEditor se)
	{//===============================================================================================
		setLayout(new BorderLayout());
		SE = se;



		addKeyListener(SpriteEditor.editCanvas);

		setBackground(Color.BLACK);
		setForeground(Color.WHITE);

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

			Panel colorPanel = new Panel();
			colorPanel.setLayout(new GridLayout(0,2,1,1));
			colorPanel.setBackground(Color.BLACK);


			Panel spacerPanel = new Panel();
			spacerPanel.setLayout(new BoxLayout(spacerPanel,BoxLayout.PAGE_AXIS));
			//spacerPanel.add(new JLabel(""));
			spacerPanel.add(Box.createRigidArea(new Dimension(60,1)));

			colorPanel.add(Box.createRigidArea(new Dimension(90,1)));
			colorPanel.add(Box.createRigidArea(new Dimension(90,1)));

			colorPanel.add(colorInfoPanel);
			colorPanel.add(selectedColorPanel);


			Panel topPanel = new Panel();
			topPanel.setLayout(new BorderLayout());

			topPanel.add(colorPanel,BorderLayout.NORTH);



		//-----------------------------
		//palette panel
		//-----------------------------
			paletteCanvas = new SEPaletteCanvas(SE);

			Dimension palD = new Dimension(((PaletteCanvas.colorsPerRow*paletteCanvas.swathSize))+paletteCanvas.PaletteGrid_x+2, (paletteCanvas.colorsPerColumn*paletteCanvas.swathSize)+paletteCanvas.PaletteGrid_y+2);


			paletteCanvas.setSize(palD);
			paletteCanvas.setPreferredSize(palD);
			paletteCanvas.setMinimumSize(palD);
			paletteCanvas.setMaximumSize(palD);


			paletteScrollPane = new JScrollPane(paletteCanvas, JScrollPane.VERTICAL_SCROLLBAR_ALWAYS ,JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);//ScrollPane.SCROLLBARS_AS_NEEDED)
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


	}

	//===============================================================================================
	public void paint(Graphics G)
	{//===============================================================================================

		super.paint(G);
		paletteCanvas.paint();
	}
}
