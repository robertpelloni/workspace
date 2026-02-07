package com.bobsgame.editor.MultipleTileEditor;

import java.awt.*;
import java.awt.event.*;

import javax.swing.*;

import com.bobsgame.EditorMain;
import com.bobsgame.editor.InfoLabelPanel;
import com.bobsgame.editor.MapCanvas.MapCanvas;

//===============================================================================================
public class MultipleTileEditor extends JFrame implements WindowListener, KeyListener
{//===============================================================================================

	/**
	 *
	 */
	private static final long serialVersionUID = 1L;
	public EditorMain E;

	public MTECanvas editCanvas;
	public MTEControlPanel controlPanel;


	public JScrollPane editCanvasScrollPane;
	public int tiles[][];
	public int widthTiles, heightTiles;

	public InfoLabelPanel infoLabel;


	//===============================================================================================
	public MultipleTileEditor(EditorMain e)
	{//===============================================================================================
		super("Multiple Tile Editor");
		setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);

		E = e;
		addWindowListener(this);
		setSize(1600, 1200);

		editCanvas = new MTECanvas(this);

		controlPanel = new MTEControlPanel(this);

		infoLabel = new InfoLabelPanel("Multiple Tile Editor", E);
		infoLabel.setBackground(Color.BLACK);
		infoLabel.setForeground(Color.WHITE);
		infoLabel.text.setFont(new Font("Tahoma", Font.BOLD, 16));

		editCanvasScrollPane = new JScrollPane(editCanvas);
		editCanvasScrollPane.getViewport().setBackground(Color.DARK_GRAY);





		add(controlPanel, BorderLayout.WEST);
		add(editCanvasScrollPane, BorderLayout.CENTER);
		add(infoLabel, BorderLayout.SOUTH);

		setFocusable(true);
		addKeyListener(this);
		recursivelyAddKeyListener(this);



	}
	//===============================================================================================
	public void recursivelyAddKeyListener(Container container)
	{//===============================================================================================
		Component[] c = container.getComponents();
		for(int i=0;i<c.length;i++)
		{

			c[i].removeKeyListener(this);

			if(
					c[i].getClass()!=TextArea.class&&
					c[i].getClass()!=TextField.class
			)
			{
				c[i].setFocusable(true);
				c[i].addKeyListener(this);

			}

			if(c[i].getClass().equals(JPanel.class))
			{
				recursivelyAddKeyListener((Container) c[i]);
			}

		}

	}

	//===============================================================================================
	public void show(int tls[][], int width, int height)
	{//===============================================================================================
		editCanvas.editBufferImage = null;

		this.widthTiles = width;
		this.heightTiles = height;
		tiles = tls;
		editCanvas.repaintBufferImage();
		//editCanvas.initUndo();
		setVisible(true);
		editCanvas.repaint();
	}

	//===============================================================================================
	public void windowOpened(WindowEvent we)
	{//===============================================================================================
		editCanvas.repaintBufferImage();
		editCanvas.repaint();
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
	public void windowOpening(WindowEvent we)
	{//===============================================================================================
	}
	//===============================================================================================
	public void windowClosing(WindowEvent we)
	{//===============================================================================================
		setVisible(false);


		EditorMain.tileCanvas.updateAllTiles();
		EditorMain.tileCanvas.paint();



		if(MapCanvas.selectedAllLayers == true)
		{
			MapCanvas.selectedAllLayers = false;
			EditorMain.controlPanel.allLayersLabel.setForeground(Color.GRAY);
		}


		//tiles have changed, so we should update the whole map.
		//in theory, we could find every changed tile and just draw them into mapcanvasimage or each layer image


		//if buffered, we need to update all the layers and then draw them into mapcanvasimage.
		//if not buffered, we need to update a lot of stuff.
		//so we should do this every time.
		EditorMain.mapCanvas.updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();

	}

	//===============================================================================================
	@Override
	public void keyTyped(KeyEvent e)
	{//===============================================================================================
		// TODO Auto-generated method stub

	}
	//===============================================================================================
	@Override
	public void keyPressed(KeyEvent e)
	{//===============================================================================================
		editCanvas.keyPressed(e);

	}
	//===============================================================================================
	@Override
	public void keyReleased(KeyEvent e)
	{//===============================================================================================
		// TODO Auto-generated method stub

	}

}
