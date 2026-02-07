package com.bobsgame.editor.TileCanvas;

import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import com.bobsgame.editor.Undo.*;

import javax.swing.JComponent;

import com.bobsgame.EditorMain;
import com.bobsgame.editor.Dialogs.NumberDialog;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.Tileset;


//===============================================================================================
public class TileCanvas extends JComponent implements MouseMotionListener, MouseListener, ActionListener, ImageObserver, KeyListener
{//===============================================================================================

	/**
	 *
	 */
	private static final long serialVersionUID = 1L;

	//public int tile[][][];
	public boolean showTileGrid = true;
	public Graphics G;
	public int tileSelected = 0;
	public int actionSelected = 0;
	public int dragTile;
	public boolean mouseDrag;
	public boolean mousePressed;
	public TileCanvasSelectionArea tileSelectionArea;
	private Image tileBufferImage = null;
	public NumberDialog SW;

	public UndoManager undoManager = new UndoManager();
	public CompoundEdit currentCompoundEdit = null;

	public void undo() {
		if (undoManager.canUndo()) {
			undoManager.undo();
			EditorMain.infoLabel.setTextNoConsole("TileCanvas: Undid " + undoManager.getUndoPresentationName());
		}
	}

	public void redo() {
		if (undoManager.canRedo()) {
			undoManager.redo();
			EditorMain.infoLabel.setTextNoConsole("TileCanvas: Redid " + undoManager.getRedoPresentationName());
		}
	}

	public static int WIDTH_TILES = 16;
	public static int TILE_SIZE = 16;
	//public PopupMenu menu;
	//public MenuItem menuCopy,menuEdit,menuCut,menuPaste,menuDelete;

	public static int sizeX = 0;
	public static int sizeY = 0;


	//===============================================================================================
	public TileCanvas()
	{//===============================================================================================





		setBackground(SystemColor.menu);

		addMouseListener(this);
		addMouseMotionListener(this);

		//addMouseWheelListener(E);

		setFocusable(true);
		addKeyListener(this);


		//tile = new int[1024][8][8];
		tileSelectionArea = new TileCanvasSelectionArea(this);

		setSizedoLayout();

		SW = new NumberDialog("Tileset Size");

		/*menu = new PopupMenu();
		menuEdit = new MenuItem();
		menuCopy = new MenuItem();
		menuCut = new MenuItem();
		menuPaste = new MenuItem();
		menuDelete = new MenuItem();
		menu.add(menuEdit);
		menu.add(menuCopy);
		menu.add(menuCut);
		menu.add(menuPaste);
		menu.add(menuDelete);

		menuCut.addActionListener(this);
		menuPaste.addActionListener(this);
		menuCopy.addActionListener(this);
		menuEdit.addActionListener(this);
		menuDelete.addActionListener(this);*/
	}


	//===============================================================================================
	public void setSizedoLayout()
	{//===============================================================================================
		int tilesetSize = 5000;

		if(Project.tileset != null)
		{
			if(Tileset.num_Tiles > tilesetSize)
			{
				tilesetSize = Tileset.num_Tiles;
			}
		}



		if(tilesetSize % WIDTH_TILES == 0)
		{
			sizeX = (WIDTH_TILES * TILE_SIZE)+1;
			sizeY = (((tilesetSize / WIDTH_TILES)) * TILE_SIZE)+1;

		}
		else
		{

			sizeX = (WIDTH_TILES * TILE_SIZE)+1;
			sizeY = (((tilesetSize / WIDTH_TILES) + 1) * TILE_SIZE)+1;

		}

		tileBufferImage = new BufferedImage(sizeX, sizeY, BufferedImage.TYPE_INT_ARGB);



		setSize(sizeX, sizeY);
		setPreferredSize(new Dimension(sizeX, sizeY));
		setMaximumSize(new Dimension(sizeX, sizeY));
		setMinimumSize(new Dimension(sizeX, sizeY));





		validate();
		//E.tileScrollPane.validate();
	}



	//===============================================================================================
	public void scrollToSelectedTile()
	{//===============================================================================================
		EditorMain.tileScrollPane.getHorizontalScrollBar().setValue(EditorMain.tileCanvas.getTileX(EditorMain.tileCanvas.tileSelected));
		EditorMain.tileScrollPane.getVerticalScrollBar().setValue(EditorMain.tileCanvas.getTileY(EditorMain.tileCanvas.tileSelected));

		//E.tileScrollPane.setScrollPosition(EditorMain.tileCanvas.getTileX(EditorMain.tileCanvas.tileSelected), EditorMain.tileCanvas.getTileY(EditorMain.tileCanvas.tileSelected));


	}


	//===============================================================================================
	public void paint(int t)
	{//===============================================================================================

		if(tileBufferImage==null)
		{
			tileBufferImage = new BufferedImage(sizeX, sizeY, BufferedImage.TYPE_INT_ARGB);
		}

		validate();

		G = tileBufferImage.getGraphics();



		if(Project.tileset != null)
		{
			int xx = t % WIDTH_TILES * TILE_SIZE;
			int yy = t / WIDTH_TILES * TILE_SIZE;
			G.setColor(Project.getSelectedPalette().getColor(0));
			G.fillRect(xx, yy, TILE_SIZE, TILE_SIZE);
			G.drawImage((Image) Project.tileset.getTileImage(t), xx, yy, xx + TILE_SIZE, yy + TILE_SIZE, 0, 0, 8, 8, this);

		}
		if(showTileGrid == true)
		{
			G.setColor(new Color(0, 0, 170));
			G.drawRect(t % WIDTH_TILES * TILE_SIZE, t / WIDTH_TILES * TILE_SIZE, TILE_SIZE, TILE_SIZE);
		}


	}


	//===============================================================================================
	public void paint(Graphics g)
	{//===============================================================================================

		//super.paint(g);
		G = g;


		G.drawImage(tileBufferImage, 0, 0, this);

		G.setColor(Color.RED);
		G.drawRect(tileSelected % WIDTH_TILES * TILE_SIZE, tileSelected / WIDTH_TILES * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	}


	//===============================================================================================
	public void updateAllTiles()
	{//===============================================================================================
		Project.tileset.buildTileImages();
		for(int t = 0; t < Tileset.num_Tiles; t++)
		{
			paint(t);
		}
	}


	//===============================================================================================
	public void paint()
	{//===============================================================================================
		if(tileSelectionArea.isShowing)
		{
			tileSelectionArea.repaint();
		}
		else
		{
			paint(getGraphics());
		}
	}


	//===============================================================================================
	public void paintBuffer()
	{//===============================================================================================

		paint(getGraphics());

	}


	//===============================================================================================
	public void copyTile(int tile, int oldtile)
	{//===============================================================================================
		copyTile(tile, oldtile, true);
	}

	public void copyTile(int tile, int oldtile, boolean recordUndo)
	{//===============================================================================================
		int[][] oldPixels = null;
		if (recordUndo) {
			oldPixels = new int[8][8];
			for(int y=0; y<8; y++) for(int x=0; x<8; x++) oldPixels[x][y] = Project.tileset.getPixel(tile, x, y);
		}

		for(int y = 0; y < 8; y++)
		{
			for(int x = 0; x < 8; x++)
			{
				Project.tileset.setPixel(tile, x, y, Project.tileset.getPixel(oldtile, x, y));
			}
		}

		if (recordUndo) {
			int[][] newPixels = new int[8][8];
			for(int y=0; y<8; y++) for(int x=0; x<8; x++) newPixels[x][y] = Project.tileset.getPixel(tile, x, y);
			
			TilePixelChangeEdit edit = new TilePixelChangeEdit(this, tile, oldPixels, newPixels);
			if (currentCompoundEdit != null) {
				currentCompoundEdit.addEdit(edit);
			} else {
				undoManager.addEdit(edit);
			}
		}

		paint(tile);
		paint(oldtile);
		EditorMain.mapCanvas.repaint();
		EditorMain.infoLabel.setTextNoConsole("TileCanvas: Copied Tile");
	}


	//===============================================================================================
	public int getTileIndexAt(int x, int y)
	{//===============================================================================================
		return y / TILE_SIZE * WIDTH_TILES + x / TILE_SIZE;
	}


	//===============================================================================================
	public int getTileX(int tile)
	{//===============================================================================================
		return tile % WIDTH_TILES * TILE_SIZE;
	}


	//===============================================================================================
	public int getTileY(int tile)
	{//===============================================================================================
		return tile / WIDTH_TILES * TILE_SIZE;
	}


	//===============================================================================================
	public void moveTile(int tile, int oldtile)
	{//===============================================================================================
		moveTile(tile, oldtile, true);
	}

	public void moveTile(int tile, int oldtile, boolean recordUndo)
	{//===============================================================================================
		if (recordUndo) {
			TileMoveEdit edit = new TileMoveEdit(this, tile, oldtile);
			if (currentCompoundEdit != null) {
				currentCompoundEdit.addEdit(edit);
			} else {
				undoManager.addEdit(edit);
			}
		}

		int oldtiledata[][] = new int[8][8];
		for(int y = 0; y < 8; y++)
		{
			for(int x = 0; x < 8; x++)
			{
				oldtiledata[x][y] = Project.tileset.getPixel(tile, x, y);
			}
		}
		for(int y = 0; y < 8; y++)
		{
			for(int x = 0; x < 8; x++)
			{
				Project.tileset.setPixel(tile, x, y, Project.tileset.getPixel(oldtile, x, y));
			}
		}
		for(int y = 0; y < 8; y++)
		{
			for(int x = 0; x < 8; x++)
			{
				Project.tileset.setPixel(oldtile, x, y, oldtiledata[x][y]);
			}
		}
		paint(tile);
		paint(oldtile);
		Project.swapTilesEveryMap(oldtile, tile);
		paint();
	}

	//===============================================================================================
	public void moveTileCursor(int lastTile)
	{//===============================================================================================
		if(!tileSelectionArea.contains(getTileX(lastTile), getTileY(lastTile)))
		{
			paint(lastTile);
		}
		tileSelectionArea.repaint();
		EditorMain.infoLabel.setTextNoConsole("TileCanvas: Tile Selected: " + tileSelected);
		if(!tileSelectionArea.contains(getTileX(tileSelected), getTileY(tileSelected)))
		{
			paint(tileSelected);
		}
		tileSelectionArea.repaint();
		EditorMain.controlPanel.tileEditCanvas.paint();
	}

	//===============================================================================================
	public void moveTileCursorUp()
	{//===============================================================================================

		int t = tileSelected;

		if(t-WIDTH_TILES>=0)
		tileSelected -= WIDTH_TILES;

		moveTileCursor(t);

	}

	//===============================================================================================
	public void moveTileCursorDown()
	{//===============================================================================================

		int t = tileSelected;

		if(t+WIDTH_TILES<Tileset.num_Tiles)
		tileSelected += WIDTH_TILES;

		moveTileCursor(t);

	}
	//===============================================================================================
	public void moveTileCursorRight()
	{//===============================================================================================

		int t = tileSelected;

		if(t+1 < Tileset.num_Tiles)
		tileSelected += 1;

		moveTileCursor(t);

	}
	//===============================================================================================
	public void moveTileCursorLeft()
	{//===============================================================================================

		int t = tileSelected;

		if(t-1>=0)
		tileSelected -= 1;


		moveTileCursor(t);

	}


	//===============================================================================================
	public void copySelection(int tile, int oldtile)
	{//===============================================================================================
		currentCompoundEdit = new CompoundEdit();
		if(tileSelectionArea.isShowing
			&& getTileX(oldtile) >= tileSelectionArea.x1
			&& getTileY(oldtile) >= tileSelectionArea.y1
			&& getTileX(oldtile) < tileSelectionArea.x2
			&& getTileY(oldtile) < tileSelectionArea.y2)
		{
			int offsetx = getTileX(tile) - getTileX(oldtile);
			int offsety = getTileY(tile) - getTileY(oldtile);
			for(int y = tileSelectionArea.y1; y < tileSelectionArea.y2; y += TILE_SIZE)
			{
				for(int x = tileSelectionArea.x1; x < tileSelectionArea.x2; x += TILE_SIZE)
				{
					if(!tileSelectionArea.contains(x + offsetx, y + offsety))
					{
						copyTile(getTileIndexAt(x + offsetx, y + offsety), getTileIndexAt(x, y));
					}
				}
			}
			tileSelectionArea.moveSelectionBoxPositionByAmt(offsetx, offsety);
			EditorMain.infoLabel.setTextNoConsole("TileCanvas: Copied Selected Tile(s)");
		}
		else
		{
			copyTile(tile, oldtile);
			EditorMain.infoLabel.setTextNoConsole("TileCanvas: Copied Tile");
		}
		currentCompoundEdit.end();
		undoManager.addEdit(currentCompoundEdit);
		currentCompoundEdit = null;
	}


	//===============================================================================================
	public void moveSelection(int tile, int oldtile)
	{//===============================================================================================
		currentCompoundEdit = new CompoundEdit();
		if(tileSelectionArea.isShowing
			&& getTileX(oldtile) >= tileSelectionArea.x1
			&& getTileY(oldtile) >= tileSelectionArea.y1
			&& getTileX(oldtile) < tileSelectionArea.x2
			&& getTileY(oldtile) < tileSelectionArea.y2)
		{
			int offsetx = getTileX(tile) - getTileX(oldtile);
			int offsety = getTileY(tile) - getTileY(oldtile);
			if(offsety < 0)
			{
				for(int y = tileSelectionArea.y1; y < tileSelectionArea.y2; y += TILE_SIZE)
				{
					if(offsetx < 0)
					{
						for(int x = tileSelectionArea.x1; x < tileSelectionArea.x2; x += TILE_SIZE)
						{
							moveTile(getTileIndexAt(x + offsetx, y + offsety), getTileIndexAt(x, y));
						}
					}
					else
					{
						for(int x = tileSelectionArea.x2 - TILE_SIZE; x >= tileSelectionArea.x1; x -= TILE_SIZE)
						{
							moveTile(getTileIndexAt(x + offsetx, y + offsety), getTileIndexAt(x, y));
						}
					}
				}
			}
			else
			{
				for(int y = tileSelectionArea.y2 - TILE_SIZE; y >= tileSelectionArea.y1; y -= TILE_SIZE)
				{
					if(offsetx < 0)
					{
						for(int x = tileSelectionArea.x1; x < tileSelectionArea.x2; x += TILE_SIZE)
						{
							moveTile(getTileIndexAt(x + offsetx, y + offsety), getTileIndexAt(x, y));
						}
					}
					else
					{
						for(int x = tileSelectionArea.x2 - TILE_SIZE; x >= tileSelectionArea.x1; x -= TILE_SIZE)
						{
							moveTile(getTileIndexAt(x + offsetx, y + offsety), getTileIndexAt(x, y));
						}
					}
				}
			}
			tileSelectionArea.moveSelectionBoxPositionByAmt(offsetx, offsety);
			EditorMain.infoLabel.setTextNoConsole("TileCanvas: Swapped Selected Tile(s)");
		}
		else
		{
			moveTile(tile, oldtile);
			EditorMain.infoLabel.setTextNoConsole("TileCanvas: Swapped Tile");
		}
		currentCompoundEdit.end();
		undoManager.addEdit(currentCompoundEdit);
		currentCompoundEdit = null;
	}


	//===============================================================================================
	public void copySelectionKeys(int tile, int oldtile)
	{//===============================================================================================
		currentCompoundEdit = new CompoundEdit();
		if(getTileX(oldtile) >= tileSelectionArea.x1Copy && getTileY(oldtile) >= tileSelectionArea.y1Copy && getTileX(oldtile) < tileSelectionArea.x2Copy && getTileY(oldtile) < tileSelectionArea.y2Copy)
		{
			int offsetx = getTileX(tile) - getTileX(oldtile);
			int offsety = getTileY(tile) - getTileY(oldtile);
			for(int y = tileSelectionArea.y1Copy; y < tileSelectionArea.y2Copy; y += TILE_SIZE)
			{
				for(int x = tileSelectionArea.x1Copy; x < tileSelectionArea.x2Copy; x += TILE_SIZE)
				{
					if(!tileSelectionArea.contains(x + offsetx, y + offsety))
					{
						copyTile(getTileIndexAt(x + offsetx, y + offsety), getTileIndexAt(x, y));
					}
				}
			}
			tileSelectionArea.moveSelectionBoxPositionByAmt(offsetx, offsety);
			EditorMain.infoLabel.setTextSuccess("TileCanvas: Pasted Copied Tiles From Clipboard");
		}
		currentCompoundEdit.end();
		undoManager.addEdit(currentCompoundEdit);
		currentCompoundEdit = null;
	}


	//===============================================================================================
	public void moveSelectionKeys(int tile, int oldtile)
	{//===============================================================================================
		currentCompoundEdit = new CompoundEdit();
		if(getTileX(oldtile) >= tileSelectionArea.x1Cut && getTileY(oldtile) >= tileSelectionArea.y1Cut && getTileX(oldtile) < tileSelectionArea.x2Cut && getTileY(oldtile) < tileSelectionArea.y2Cut)
		{
			int offsetx = getTileX(tile) - getTileX(oldtile);
			int offsety = getTileY(tile) - getTileY(oldtile);
			if(offsety < 0)
			{
				for(int y = tileSelectionArea.y1Cut; y < tileSelectionArea.y2Cut; y += TILE_SIZE)
				{
					if(offsetx < 0)
					{
						for(int x = tileSelectionArea.x1Cut; x < tileSelectionArea.x2Cut; x += TILE_SIZE)
						{
							moveTile(getTileIndexAt(x + offsetx, y + offsety), getTileIndexAt(x, y));
						}
					}
					else
					{
						for(int x = tileSelectionArea.x2Cut - TILE_SIZE; x >= tileSelectionArea.x1Cut; x -= TILE_SIZE)
						{
							moveTile(getTileIndexAt(x + offsetx, y + offsety), getTileIndexAt(x, y));
						}
					}
				}
			}
			else
			{
				for(int y = tileSelectionArea.y2Cut - TILE_SIZE; y >= tileSelectionArea.y1Cut; y -= TILE_SIZE)
				{
					if(offsetx < 0)
					{
						for(int x = tileSelectionArea.x1Cut; x < tileSelectionArea.x2Cut; x += TILE_SIZE)
						{
							moveTile(getTileIndexAt(x + offsetx, y + offsety), getTileIndexAt(x, y));
						}
					}
					else
					{
						for(int x = tileSelectionArea.x2Cut - TILE_SIZE; x >= tileSelectionArea.x1Cut; x -= TILE_SIZE)
						{
							moveTile(getTileIndexAt(x + offsetx, y + offsety), getTileIndexAt(x, y));
						}
					}
				}
			}
			tileSelectionArea.moveSelectionBoxPositionByAmt(offsetx, offsety);
			EditorMain.infoLabel.setTextSuccess("TileCanvas: Swapped Cut Tiles From Clipboard");
		}
		currentCompoundEdit.end();
		undoManager.addEdit(currentCompoundEdit);
		currentCompoundEdit = null;
	}


	//===============================================================================================
	public void setCut()
	{//===============================================================================================
		tileSelectionArea.x1Cut = tileSelectionArea.x1;
		tileSelectionArea.x2Cut = tileSelectionArea.x2;
		tileSelectionArea.y1Cut = tileSelectionArea.y1;
		tileSelectionArea.y2Cut = tileSelectionArea.y2;
		tileSelectionArea.isSelectedCut = true;
		tileSelectionArea.isSelectedCopy = false;
		tileSelectionArea.isShowing = false;
		tileSelectionArea.repaint();
		EditorMain.infoLabel.setTextNoConsole("TileCanvas: Cut Selected Tile Area (Swap on Paste)");

	}


	//===============================================================================================
	public void paste()
	{//===============================================================================================


		if(tileSelectionArea.isSelectedCopy)
		{
			copySelectionKeys(tileSelected, (tileSelectionArea.y1Copy / TILE_SIZE) * WIDTH_TILES + (tileSelectionArea.x1Copy / TILE_SIZE));
		}
		if(tileSelectionArea.isSelectedCut)
		{
			moveSelectionKeys(tileSelected, (tileSelectionArea.y1Cut / TILE_SIZE) * WIDTH_TILES +( tileSelectionArea.x1Cut / TILE_SIZE));
		}

		tileSelectionArea.isShowing=true;
		tileSelectionArea.isSelectedCopy = false;
		tileSelectionArea.isSelectedCut = false;
		tileSelectionArea.repaint();
	}


	//===============================================================================================
	public void setCopy()
	{//===============================================================================================

		tileSelectionArea.x1Copy = tileSelectionArea.x1;
		tileSelectionArea.x2Copy = tileSelectionArea.x2;
		tileSelectionArea.y1Copy = tileSelectionArea.y1;
		tileSelectionArea.y2Copy = tileSelectionArea.y2;
		tileSelectionArea.isSelectedCopy = true;
		tileSelectionArea.isSelectedCut = false;
		tileSelectionArea.isShowing = false;
		tileSelectionArea.repaint();
		EditorMain.infoLabel.setTextNoConsole("TileCanvas: Copied Selected Tile Area (Overwrite on Paste)");
	}


	//===============================================================================================
	public void mouseClicked(MouseEvent me)
	{//===============================================================================================
		//int leftMask = InputEvent.BUTTON1_DOWN_MASK;
		int middleMask = InputEvent.BUTTON2_DOWN_MASK;
		int rightMask = InputEvent.BUTTON3_DOWN_MASK;
		int shiftClickMask = InputEvent.BUTTON1_DOWN_MASK | InputEvent.SHIFT_DOWN_MASK;
		int ctrlClickMask = InputEvent.BUTTON1_DOWN_MASK | InputEvent.CTRL_DOWN_MASK;



		if(tileSelectionArea.contains(me.getX(), me.getY()) && tileSelectionArea.isShowing)
		{
			if((me.getModifiersEx() == rightMask || me.getModifiersEx() == ctrlClickMask))
			{
				if(me.getClickCount() == 2)
				{
					EditorMain.infoLabel.setTextSuccess("TileCanvas: Opening Multiple Tile Editor");
					int tls[][] = new int[tileSelectionArea.getWidth() / TILE_SIZE][tileSelectionArea.getHeight() / TILE_SIZE];
					for(int ty = 0; ty < tileSelectionArea.getHeight() / TILE_SIZE; ty++)
					{
						for(int tx = 0; tx < tileSelectionArea.getWidth() / TILE_SIZE; tx++)
						{
							tls[tx][ty] = getTileIndexAt(tileSelectionArea.getX() + tx * TILE_SIZE, tileSelectionArea.getY() + ty * TILE_SIZE);
						}
					}
					EditorMain.multipleTileEditor.show(tls, tileSelectionArea.getWidth() / TILE_SIZE, tileSelectionArea.getHeight() / TILE_SIZE);
					if(EditorMain.multipleTileEditor.getExtendedState() == Frame.ICONIFIED)
					{
						EditorMain.multipleTileEditor.setExtendedState(Frame.NORMAL);
					}
				}
				//else menu.show(E.tileCanvas,me.getX(),me.getY());
			}

		}
		if((me.getModifiersEx() == middleMask || me.getModifiersEx() == shiftClickMask))
		{
			tileSelectionArea.isShowing=false;
			EditorMain.infoLabel.setTextNoConsole("TileCanvas: Deselected Area");
		}

	}


	//===============================================================================================
	public void mousePressed(MouseEvent me)
	{//===============================================================================================
		EditorMain.lastActiveCanvas = this;
		int leftMask = InputEvent.BUTTON1_DOWN_MASK;
		int middleMask = InputEvent.BUTTON2_DOWN_MASK;
		int rightMask = InputEvent.BUTTON3_DOWN_MASK;
		int shiftClickMask = InputEvent.BUTTON1_DOWN_MASK | InputEvent.SHIFT_DOWN_MASK;
		int ctrlClickMask = InputEvent.BUTTON1_DOWN_MASK | InputEvent.CTRL_DOWN_MASK;


		int clickedTile = me.getY() / TILE_SIZE * WIDTH_TILES + me.getX() / TILE_SIZE;
		if(clickedTile < 0 ||clickedTile >= Tileset.num_Tiles)return;

		mousePressed = true;

		if((me.getModifiersEx() == rightMask || me.getModifiersEx() == ctrlClickMask) || me.getModifiersEx() == leftMask)
		{

			int t = tileSelected;
			tileSelected = clickedTile;

			if(!tileSelectionArea.contains(getTileX(t), getTileY(t)))
			{
				//repaint the previous tile so the tile selection rectangle isn't shown over it
				paint(t);
			}

			tileSelectionArea.repaint();

			EditorMain.infoLabel.setTextNoConsole("TileCanvas: Tile Selected: " + tileSelected);
			dragTile = tileSelected;

		}
		else
		if((me.getModifiersEx() == middleMask || me.getModifiersEx() == shiftClickMask) && tileSelectionArea.isSelectedCopy == false && tileSelectionArea.isSelectedCut == false)
		{
			tileSelectionArea.setLocation(me.getX()/TILE_SIZE*TILE_SIZE, me.getY()/TILE_SIZE*TILE_SIZE);
			tileSelectionArea.setSize(0, 0);
			tileSelectionArea.isShowing=true;
			tileSelectionArea.repaint();

		}
		EditorMain.controlPanel.tileEditCanvas.paint();
	}


	//===============================================================================================
	public void mouseReleased(MouseEvent me)
	{//===============================================================================================
		int leftMask = InputEvent.BUTTON1_DOWN_MASK;
		int middleMask = InputEvent.BUTTON2_DOWN_MASK;
		int rightMask = InputEvent.BUTTON3_DOWN_MASK;
		int shiftClickMask = InputEvent.BUTTON1_DOWN_MASK | InputEvent.SHIFT_DOWN_MASK;
		int ctrlClickMask = InputEvent.BUTTON1_DOWN_MASK | InputEvent.CTRL_DOWN_MASK;


		int clickedTile = me.getY() / TILE_SIZE * WIDTH_TILES + me.getX() / TILE_SIZE;
		if(clickedTile < 0 ||clickedTile >= Tileset.num_Tiles)return;

		mousePressed = false;

		if(mouseDrag)
		{
			mouseDrag = false;
			if((me.getModifiersEx() == rightMask || me.getModifiersEx() == ctrlClickMask))
			{
				tileSelected = clickedTile;
				copySelection(tileSelected, dragTile);
				paint();
			}
			else if(me.getModifiersEx() == leftMask)
			{
				tileSelected = clickedTile;
				moveSelection(tileSelected, dragTile);
				paint();
			}
			else if((me.getModifiersEx() == middleMask || me.getModifiersEx() == shiftClickMask) && tileSelectionArea.isShowing)
			{
				EditorMain.infoLabel.setTextNoConsole("TileCanvas: Selected Area");
			}
		}
		else
		{
			if(!tileSelectionArea.contains(getTileX(tileSelected), getTileY(tileSelected)))
			{
				paint(tileSelected);
			}
			tileSelectionArea.repaint();
		}
		setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
	}


	//===============================================================================================
	public void mouseEntered(MouseEvent me)
	{//===============================================================================================
	}


	//===============================================================================================
	public void mouseExited(MouseEvent me)
	{//===============================================================================================
	}


	//===============================================================================================
	public void mouseMoved(MouseEvent me)
	{//===============================================================================================
	}


	//===============================================================================================
	public void mouseDragged(MouseEvent me)
	{//===============================================================================================
		int leftMask = InputEvent.BUTTON1_DOWN_MASK;
		int middleMask = InputEvent.BUTTON2_DOWN_MASK;
		int rightMask = InputEvent.BUTTON3_DOWN_MASK;
		int shiftClickMask = InputEvent.BUTTON1_DOWN_MASK | InputEvent.SHIFT_DOWN_MASK;
		int ctrlClickMask = InputEvent.BUTTON1_DOWN_MASK | InputEvent.CTRL_DOWN_MASK;


		mouseDrag = true;
		if(
				tileSelectionArea.isShowing &&
				(me.getModifiersEx() == middleMask || me.getModifiersEx() == shiftClickMask)

		)
		{
			int x = (me.getX() + TILE_SIZE) / TILE_SIZE * TILE_SIZE;
			int y = (me.getY() + TILE_SIZE) / TILE_SIZE * TILE_SIZE;

			if(x != tileSelectionArea.x2 || y != tileSelectionArea.y2)
			{
				tileSelectionArea.setLocation2(x, y);
				tileSelectionArea.repaint();
			}
		}
		else if((me.getModifiersEx() == rightMask || me.getModifiersEx() == ctrlClickMask) || me.getModifiersEx() == leftMask && tileSelectionArea.contains(me.getX(), me.getY()))
		{
			setCursor(new Cursor(Cursor.MOVE_CURSOR));
		}
	}


	//===============================================================================================
	public void actionPerformed(ActionEvent ae)
	{//===============================================================================================

		/*if(ae.getSource()==menuCut) {
		setCut();
		} else
		if(ae.getSource()==menuCopy) {
		setCopy();
		} else
		if(ae.getSource()==menuPaste) {
		paste();
		} */
	}


	//===============================================================================================
	public void keyPressed(KeyEvent ke)
	{//===============================================================================================


		//TILECANVAS SPECIFIC KEYS
		if(ke.getKeyCode() == KeyEvent.VK_X && ke.isControlDown())
		{
			if(tileSelectionArea.isShowing)
			{
				setCut();
			}
		}
		else if(ke.getKeyCode() == KeyEvent.VK_V && ke.isControlDown())
		{
			paste();
		}
		else if(ke.getKeyCode() == KeyEvent.VK_C && ke.isControlDown())
		{
			if(tileSelectionArea.isShowing)
			{
				setCopy();
			}
		}



	}

	//===============================================================================================
	public void keyReleased(KeyEvent ke)
	{//===============================================================================================

	}

	//===============================================================================================
	public void keyTyped(KeyEvent ke)
	{//===============================================================================================
	}

	//===============================================================================================
	public void toggleTileGrid(EditorMain e)
	{//===============================================================================================
		showTileGrid = !showTileGrid;
		updateAllTiles();
		repaint();
	}


}
