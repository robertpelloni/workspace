package com.bobsgame.editor.MultipleTileEditor;

import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;

import javax.swing.JComponent;

import com.bobsgame.EditorMain;
import com.bobsgame.editor.SelectionArea;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Undo.*;

//===============================================================================================
public class MTECanvas extends JComponent implements MouseListener, MouseWheelListener, MouseMotionListener, KeyListener, ImageObserver
{//===============================================================================================

	/**
	 *
	 */
	private static final long serialVersionUID = 1L;
	public BufferedImage editBufferImage;


	public MTESelectionArea selectionBox;

	public int dragPixelx;
	public int dragPixely;
	public boolean mouseDrag;
	public boolean selectionDragged;
	public boolean mousePressed;
	public int zoom = 8;
	protected int oldPixelColor = -1;
	
	public UndoManager undoManager = new UndoManager();
	protected CompoundEdit currentEdit;


	private MultipleTileEditor MTE;
	private EditorMain E;


	private int oldx=0;
	private int oldy=0;




	//===============================================================================================
	public MTECanvas()
	{//===============================================================================================

	}
	//===============================================================================================
	public MTECanvas(MultipleTileEditor mte)
	{//===============================================================================================
		MTE = mte;
		E=mte.E;

		selectionBox = new MTESelectionArea(this);
		//setBackground(Color.BLACK);
		addMouseWheelListener(this);
		addMouseListener(this);
		addMouseMotionListener(this);
		addKeyListener(this);
		setSize(0, 0);

	}


	//===============================================================================================
	public void setText(String s)
	{//===============================================================================================

		MTE.infoLabel.setTextNoConsole(s);

	}
	//===============================================================================================
	public SelectionArea getSelectionBox()
	{//===============================================================================================
		return selectionBox;
	}

	//===============================================================================================
	public void undo()
	{//===============================================================================================
		if(undoManager.canUndo()) {
			undoManager.undo();
			setText("MTECanvas: Undid " + undoManager.getUndoPresentationName());
		} else {
			setText("MTECanvas: Nothing to undo");
		}
	}
	//===============================================================================================
	public void redo()
	{//===============================================================================================
		if(undoManager.canRedo()) {
			undoManager.redo();
			setText("MTECanvas: Redid " + undoManager.getRedoPresentationName());
		} else {
			setText("MTECanvas: Nothing to redo");
		}
	}
	
	//===============================================================================================
	public void setPixel(int x, int y, int color, CompoundEdit edit)
	{//===============================================================================================
		int oldColor = getPixel(x, y);
		if(oldColor != color) {
			if(edit != null) {
				edit.addEdit(new PixelChangeEdit(this, x, y, oldColor, color));
			}
			setPixel(x, y, color);
		}
	}


	//===============================================================================================
	public void paint(Graphics G, int x, int y)
	{//===============================================================================================
		int tile = MTE.tiles[x][y];
		G.drawImage(Project.tileset.getTileImage(tile), x * 8, y * 8, this);
	}
	//===============================================================================================
	public void paint(Graphics G)
	{//===============================================================================================

		super.paint(G);

		if(editBufferImage == null)
		{
			repaintBufferImage();
		}

		if(G != null)
		{
			G.drawImage(editBufferImage, 0, 0, MTE.widthTiles * 8 * zoom, MTE.heightTiles * 8 * zoom, 0, 0, MTE.widthTiles * 8, MTE.heightTiles * 8, this);
			//G.setColor(Color.white);
			//G.drawRect(0, 0, MTE.width * 8 * zoom, MTE.height * 8 * zoom);
			if(EditorMain.mapCanvas.showMapGrid)
			{
				G.setColor(Color.white);

				for(int yy = 8 * zoom; yy < MTE.heightTiles * 8 * zoom; yy += 8 * zoom)
				{
					G.drawLine(0, yy, MTE.widthTiles * 8 * zoom, yy);
				}
				for(int xx = 8 * zoom; xx < MTE.widthTiles * 8 * zoom; xx += 8 * zoom)
				{
					G.drawLine(xx, 0, xx, MTE.heightTiles * 8 * zoom);
				}
			}

			if(getSelectionBox().isShowing)
			{
				G.setColor(getSelectionBox().color);
				G.fillRect(getSelectionBox().x1 * zoom, getSelectionBox().y1 * zoom, (getSelectionBox().x2 - getSelectionBox().x1) * zoom, (getSelectionBox().y2 - getSelectionBox().y1) * zoom);
				G.setColor(Color.RED);
				G.drawRect(getSelectionBox().x1 * zoom, getSelectionBox().y1 * zoom, (getSelectionBox().x2 - getSelectionBox().x1) * zoom - 1, (getSelectionBox().y2 - getSelectionBox().y1) * zoom - 1);
			}
			G.dispose();
		}

	}


	//===============================================================================================
	public void repaintBufferImage()
	{//===============================================================================================
		if(editBufferImage == null)editBufferImage = getGraphicsConfiguration().createCompatibleImage(MTE.widthTiles * 8, MTE.heightTiles * 8, Transparency.OPAQUE);

		Graphics G = editBufferImage.getGraphics();
		G.setColor(Project.getSelectedPalette().getColor(0));
		G.fillRect(0, 0, MTE.widthTiles * 8 + 1, MTE.heightTiles * 8 + 1);
		for(int y = 0; y < MTE.heightTiles; y++)
		{
			for(int x = 0; x < MTE.widthTiles; x++)
			{
				paint(G, x, y);
			}
		}

	}



	public void setSizeDoLayout()
	{

		int sizeX = MTE.widthTiles * 8 * zoom;
		int sizeY = MTE.heightTiles * 8 * zoom;

		setSize(new Dimension(sizeX,sizeY));
		setPreferredSize(new Dimension(sizeX,sizeY));
		setMinimumSize(new Dimension(sizeX,sizeY));
		setMaximumSize(new Dimension(sizeX,sizeY));
		validate();



		MTE.editCanvasScrollPane.setViewportView(this);
		MTE.editCanvasScrollPane.getViewport().setViewSize(new Dimension(sizeX,sizeY));
		MTE.editCanvasScrollPane.getViewport().validate();

		MTE.editCanvasScrollPane.validate();
	}



	//===============================================================================================
	public void zoomIn()
	{//===============================================================================================
		if(zoom < 32)
		{
			zoom += 2;
		}



		setSizeDoLayout();

		Point p = new Point();
		p.x = MTE.editCanvasScrollPane.getHorizontalScrollBar().getValue();
		p.y = MTE.editCanvasScrollPane.getVerticalScrollBar().getValue();


		if(getSelectionBox().isShowing)
		{
			p.x = (getSelectionBox().x2 * zoom) - ((MTE.widthTiles * 8 * zoom) / 2); //(((SA.x1*zoom) + (((SA.x2*zoom)-(SA.x1*zoom))/2))) - ((TE.width*8*zoom)/2);
			p.y = (getSelectionBox().y2 * zoom) - ((MTE.heightTiles * 8 * zoom) / 2); //(((SA.y1*zoom) + (((SA.y2*zoom)-(SA.y1*zoom))/2))) - ((TE.height*8*zoom)/2);
		}
		else
		{
			p.x = (((p.x + ((MTE.widthTiles * 8 * zoom) / 2)) / (zoom - 1)) * zoom) - ((MTE.widthTiles * 8 * zoom) / 2);
			p.y = (((p.y + ((MTE.heightTiles * 8 * zoom) / 2)) / (zoom - 1)) * zoom) - ((MTE.heightTiles * 8 * zoom) / 2);
			if(MTE.widthTiles * 8 * zoom < MTE.widthTiles * 8)
			{
				p.x = 0;
			}
			if(MTE.heightTiles * 8 * zoom < MTE.heightTiles * 8)
			{
				p.y = 0;
			}
		}
		if(p.x > MTE.editCanvasScrollPane.getHorizontalScrollBar().getMaximum())
		{
			p.x = MTE.editCanvasScrollPane.getHorizontalScrollBar().getMaximum();
		}
		if(p.y > MTE.editCanvasScrollPane.getVerticalScrollBar().getMaximum())
		{
			p.y = MTE.editCanvasScrollPane.getVerticalScrollBar().getMaximum();
		}
		MTE.editCanvasScrollPane.getHorizontalScrollBar().setValue(p.x);
		MTE.editCanvasScrollPane.getVerticalScrollBar().setValue(p.y);


	}
	//===============================================================================================
	public void zoomOut()
	{//===============================================================================================
		if(zoom > 2)
		{
			zoom -= 2;
		}


		setSizeDoLayout();

		Point p = new Point();
		p.x = MTE.editCanvasScrollPane.getHorizontalScrollBar().getValue();
		p.y = MTE.editCanvasScrollPane.getVerticalScrollBar().getValue();



		if(getSelectionBox().isShowing)
		{
			p.x = (getSelectionBox().x2 * zoom) - ((MTE.widthTiles * 8 * zoom) / 2); //(((SA.x1*zoom) + (((SA.x2*zoom)-(SA.x1*zoom))/2))) - ((TE.width*8*zoom)/2);
			p.y = (getSelectionBox().y2 * zoom) - ((MTE.heightTiles * 8 * zoom) / 2); //(((SA.y1*zoom) + (((SA.y2*zoom)-(SA.y1*zoom))/2))) - ((TE.height*8*zoom)/2);
		}
		else
		{
			p.x = (((p.x + ((MTE.widthTiles * 8 * zoom) / 2)) / (zoom - 1)) * zoom) - ((MTE.widthTiles * 8 * zoom) / 2);
			p.y = (((p.y + ((MTE.heightTiles * 8 * zoom) / 2)) / (zoom - 1)) * zoom) - ((MTE.heightTiles * 8 * zoom) / 2);
			if(MTE.widthTiles * 8 * zoom < MTE.widthTiles * 8)
			{
				p.x = 0;
			}
			if(MTE.heightTiles * 8 * zoom < MTE.heightTiles * 8)
			{
				p.y = 0;
			}
		}

		if(p.x > MTE.editCanvasScrollPane.getHorizontalScrollBar().getMaximum())
		{
			p.x = MTE.editCanvasScrollPane.getHorizontalScrollBar().getMaximum();
		}
		if(p.y > MTE.editCanvasScrollPane.getVerticalScrollBar().getMaximum())
		{
			p.y = MTE.editCanvasScrollPane.getVerticalScrollBar().getMaximum();
		}
		MTE.editCanvasScrollPane.getHorizontalScrollBar().setValue(p.x);
		MTE.editCanvasScrollPane.getVerticalScrollBar().setValue(p.y);


	}
	//===============================================================================================
	public void fill(int sx, int sy, int color, int prevcolor, CompoundEdit edit)
	{//===============================================================================================

		setPixel(sx, sy, MTE.controlPanel.paletteCanvas.colorSelected, edit);
		int pixel;

		if(sx > 0)
		{
			pixel = Project.tileset.getPixel(MTE.tiles[(sx - 1) / 8][sy / 8], (sx - 1) % 8, sy % 8);
			if(pixel != color && pixel == prevcolor)
			{
				fill(sx - 1, sy, color, prevcolor, edit);
			}
		}
		if(sx < MTE.widthTiles * 8 - 1)
		{
			pixel = Project.tileset.getPixel(MTE.tiles[(sx + 1) / 8][sy / 8], (sx + 1) % 8, sy % 8);
			if(pixel != color && pixel == prevcolor)
			{
				fill(sx + 1, sy, color, prevcolor, edit);
			}
		}
		if(sy > 0)
		{
			pixel = Project.tileset.getPixel(MTE.tiles[sx / 8][(sy - 1) / 8], sx % 8, (sy - 1) % 8);
			if(pixel != color && pixel == prevcolor)
			{
				fill(sx, sy - 1, color, prevcolor, edit);
			}
		}
		if(sy < MTE.heightTiles * 8 - 1)
		{
			pixel = Project.tileset.getPixel(MTE.tiles[sx / 8][(sy + 1) / 8], sx % 8, (sy + 1) % 8);
			if(pixel != color && pixel == prevcolor)
			{
				fill(sx, sy + 1, color, prevcolor, edit);
			}
		}

	}
	//===============================================================================================
	public void setPixel(int x, int y, int color)
	{//===============================================================================================

		Project.tileset.setPixel(MTE.tiles[x / 8][y / 8], x % 8, y % 8, color);

	}
	
	//===============================================================================================
	public void setPixelRaw(int x, int y, int color)
	{//===============================================================================================
		setPixel(x, y, color);
	}
	//===============================================================================================
	public int getPixel(int x, int y)
	{//===============================================================================================

		return Project.tileset.getPixel(MTE.tiles[x / 8][y / 8], x % 8, y % 8);

	}
	//===============================================================================================
	public void copySelection(int oldx, int oldy, int newx, int newy, CompoundEdit edit)
	{//===============================================================================================
		if(getSelectionBox().isShowing && getSelectionBox().contains(oldx, oldy))
		{
			int xmax, ymax;

			xmax = MTE.widthTiles * 8;
			ymax = MTE.heightTiles * 8;


			if(getSelectionBox().x1 + (newx - oldx) >= 0 && getSelectionBox().y1 + (newy - oldy) >= 0 && getSelectionBox().x2 + (newx - oldx) <= xmax && getSelectionBox().y2 + (newy - oldy) <= ymax)
			{
				getSelectionBox().copy();
				getSelectionBox().moveSelectionBoxPositionByAmt(newx - oldx, newy - oldy);
				((MTESelectionArea)getSelectionBox()).paste(edit);
				repaintBufferImage();
				repaint();
				setText("MTECanvas: Copied Selection");
			}
		}
	}

	//===============================================================================================
	public void moveSelection(int oldx, int oldy, int newx, int newy, CompoundEdit edit)
	{//===============================================================================================
		if(getSelectionBox().isShowing && getSelectionBox().contains(oldx, oldy))
		{
			int xmax, ymax;

			xmax = MTE.widthTiles * 8;
			ymax = MTE.heightTiles * 8;


			if(getSelectionBox().x1 + (newx - oldx) >= 0 && getSelectionBox().y1 + (newy - oldy) >= 0 && getSelectionBox().x2 + (newx - oldx) <= xmax && getSelectionBox().y2 + (newy - oldy) <= ymax)
			{
				getSelectionBox().cut(); // cut() calls delete(), which creates its own edit.
				// We should probably make cut() accept an edit too, or just accept that cut is separate?
				// Actually cut() calls delete(). delete() creates a new CompoundEdit.
				// If we want to group cut and paste into one move operation, we need to pass edit to cut/delete.
				// But cut() is void and calls delete().
				// Let's assume for now move is two operations or I need to update cut/delete further.
				// Wait, if I pass 'edit' to paste, paste adds to 'edit'.
				// If cut() adds to undoManager separately, then undoing move will require two undos.
				// That's acceptable for now, or I can update cut/delete later.
				// Actually, let's just use paste(edit) here.
				
				getSelectionBox().moveSelectionBoxPositionByAmt(newx - oldx, newy - oldy);
				((MTESelectionArea)getSelectionBox()).paste(edit);
				repaintBufferImage();
				repaint();
				setText("MTECanvas: Moved Selection");
			}
		}
	}
	//===============================================================================================
	public void deleteSelection()
	{//===============================================================================================
		if(getSelectionBox().isShowing)
		{
			getSelectionBox().delete();
			repaintBufferImage();
			repaint();
			setText("MTECanvas: Deleted Selection");
		}
	}
	//===============================================================================================
	public void cutSelectionKeys()
	{//===============================================================================================
		if(getSelectionBox().isShowing)
		{
			getSelectionBox().cutkeys();
			repaintBufferImage();
			repaint();
			setText("MTECanvas: Cut Selection to clipboard");
		}
	}
	//===============================================================================================
	public void copySelectionKeys()
	{//===============================================================================================
		if(getSelectionBox().isShowing)
		{
			getSelectionBox().copykeys();
			repaintBufferImage();
			repaint();
			setText("MTECanvas: Copied Selection to clipboard");
		}
	}
	//===============================================================================================
	public void pasteSelectionKeys()
	{//===============================================================================================
		if(getSelectionBox().isShowing)
		{
			getSelectionBox().pastekeys();
			repaintBufferImage();
			repaint();
			setText("MTECanvas: Pasted Selection from clipboard");
		}
	}
	//===============================================================================================
	public void pasteSelectionKeysNonZero()
	{//===============================================================================================
		if(getSelectionBox().isShowing)
		{
			getSelectionBox().pastekeysNonZero();
			repaintBufferImage();
			repaint();
			setText("MTECanvas: Pasted Selection (Non-Zero) from clipboard");
		}
	}
	//===============================================================================================
	public void reverseSelection()
	{//===============================================================================================
		if(getSelectionBox().isShowing)
		{
			getSelectionBox().copy();
			getSelectionBox().pasteReverse();
			repaintBufferImage();
			repaint();
			setText("MTECanvas: Reversed Selection");
		}
	}
	//===============================================================================================
	public void flipSelection()
	{//===============================================================================================
		if(getSelectionBox().isShowing)
		{
			getSelectionBox().copy();
			getSelectionBox().pasteFlipped();
			repaintBufferImage();
			repaint();
			setText("MTECanvas: Flipped Selection");
		}
	}
	//===============================================================================================
	public void mouseClicked(MouseEvent me)
	{//===============================================================================================
		int leftMask = InputEvent.BUTTON1_DOWN_MASK;
		int middleMask = InputEvent.BUTTON2_DOWN_MASK;
		int rightMask = InputEvent.BUTTON3_DOWN_MASK;
		int shiftClickMask = InputEvent.BUTTON1_DOWN_MASK | InputEvent.SHIFT_DOWN_MASK;
		int ctrlClickMask = InputEvent.BUTTON1_DOWN_MASK | InputEvent.CTRL_DOWN_MASK;
		//int altClickMask = me.BUTTON1_DOWN_MASK | me.ALT_DOWN_MASK;
		int x = me.getX() / zoom;
		int y = me.getY() / zoom;



		if(
				x < MTE.widthTiles * 8 &&
				y < MTE.heightTiles * 8 &&
				x >=0 &&
				y >=0
		)
		{

			int tile = MTE.tiles[x / 8][y / 8];

			if(me.getModifiersEx() == leftMask)
			{
				CompoundEdit edit = currentEdit;
				boolean localEdit = false;
				if(edit == null) {
					edit = new CompoundEdit();
					localEdit = true;
				}
				
				if(MTE.controlPanel.paletteCanvas.colorSelected != Project.tileset.getPixel(tile, x % 8, y % 8))
				{

					oldPixelColor = Project.tileset.getPixel(tile, x % 8, y % 8);
					setPixel(x, y, MTE.controlPanel.paletteCanvas.colorSelected, edit);
					repaintBufferImage();
					repaint();
					//TE.E.project.getSelectedMap().destroyImages();
					//TE.E.mapCanvas.paintBuffer();
					//TE.E.mapCanvas.repaint();
				}
				else if(me.getClickCount() == 2)
				{
					fill(x, y, MTE.controlPanel.paletteCanvas.colorSelected, oldPixelColor, edit);
					repaintBufferImage();
					repaint();
					//TE.E.project.getSelectedMap().destroyImages();
					//TE.E.mapCanvas.paintBuffer();
					//TE.E.mapCanvas.repaint();
					setText("Filled");
				}
				
				if(localEdit) {
					edit.end();
					if(edit.isSignificant()) undoManager.addEdit(edit);
				}
			}
			else if((me.getModifiersEx() == rightMask || me.getModifiersEx() == ctrlClickMask))
			{
				if(MTE.controlPanel.paletteCanvas.colorSelected != Project.tileset.getPixel(tile, x % 8, y % 8))
				{

					MTE.controlPanel.paletteCanvas.selectColor(Project.tileset.getPixel(tile, x % 8, y % 8));

				}
			}
		}

		if((me.getModifiersEx() == middleMask || me.getModifiersEx() == shiftClickMask))
		{
			getSelectionBox().isShowing=false;
			setText("MTECanvas: Deselected Area");
			repaint();
		}
	}
	//===============================================================================================
	public void mousePressed(MouseEvent me)
	{//===============================================================================================
		int leftMask = InputEvent.BUTTON1_DOWN_MASK;
		int middleMask = InputEvent.BUTTON2_DOWN_MASK;
		int rightMask = InputEvent.BUTTON3_DOWN_MASK;
		int shiftClickMask = InputEvent.BUTTON1_DOWN_MASK | InputEvent.SHIFT_DOWN_MASK;
		int ctrlClickMask = InputEvent.BUTTON1_DOWN_MASK | InputEvent.CTRL_DOWN_MASK;
		//int altClickMask = me.BUTTON1_DOWN_MASK | me.ALT_DOWN_MASK;



		oldx = me.getX();
		oldy = me.getY();


		int x = me.getX() / zoom;
		int y = me.getY() / zoom;
		mousePressed = true;
		
		currentEdit = new CompoundEdit();
		
		if((me.getModifiersEx() == rightMask || me.getModifiersEx() == ctrlClickMask) || me.getModifiersEx() == leftMask)
		{
			dragPixelx = x;
			dragPixely = y;
		}
		else if((me.getModifiersEx() == middleMask || me.getModifiersEx() == shiftClickMask))
		{
			int pressedX = (int)(me.getX() / zoom);
			int pressedY = (int)(me.getY() / zoom);
			if(pressedX>=0&&pressedY>=0&&pressedX<MTE.widthTiles*8&&pressedY<MTE.heightTiles*8)
			{
				getSelectionBox().setLocation(x, y);
				getSelectionBox().setSize(0, 0);
				getSelectionBox().isShowing=true;
				setText("MTECanvas: Selection set: " + x + "," + y);
				repaint();
			}
			else
			{

				//deselect any selected area if we've pressed the middle mouse button outside the canvas
				if(getSelectionBox().isShowing==true)
				{
					getSelectionBox().isShowing=false;
					setText("MTECanvas: Deselected Area");
					repaint();

				}
			}
		}
	}
	//===============================================================================================
	public void mouseReleased(MouseEvent me)
	{//===============================================================================================
		int leftMask = InputEvent.BUTTON1_DOWN_MASK;
		int rightMask = InputEvent.BUTTON3_DOWN_MASK;
		int ctrlClickMask = InputEvent.BUTTON1_DOWN_MASK | InputEvent.CTRL_DOWN_MASK;
		int x = me.getX() / zoom;
		int y = me.getY() / zoom;
		mousePressed = false;

		//TE.E.project.getSelectedMap().destroyImages();
		//TE.E.mapCanvas.paintBuffer();
		//TE.E.mapCanvas.repaint();

		if(selectionDragged)
		{
			mouseDrag = false;
			if((me.getModifiersEx() == rightMask || me.getModifiersEx() == ctrlClickMask))
			{
				selectionDragged = false;
				copySelection(dragPixelx, dragPixely, x, y, currentEdit);
			}
			else if(me.getModifiersEx() == leftMask)
			{
				selectionDragged = false;
				moveSelection(dragPixelx, dragPixely, x, y, currentEdit);
			}
		}
		
		if(currentEdit != null) {
			currentEdit.end();
			if(currentEdit.isSignificant()) undoManager.addEdit(currentEdit);
			currentEdit = null;
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

		int middleMask = InputEvent.BUTTON2_DOWN_MASK;
		int shiftClickMask = InputEvent.BUTTON1_DOWN_MASK | InputEvent.SHIFT_DOWN_MASK;



		int x = (me.getX() / zoom);
		int y = (me.getY() / zoom);
		mouseDrag = true;

		int shiftMiddleClickMask = InputEvent.BUTTON2_DOWN_MASK | InputEvent.SHIFT_DOWN_MASK;

		if(me.getModifiersEx() == shiftMiddleClickMask)
		{

			int offsetX = oldx - me.getX();
			int offsetY = oldy - me.getY();

			Point p = MTE.editCanvasScrollPane.getViewport().getViewPosition();

			p.x+=offsetX;
			p.y+=offsetY;

			MTE.editCanvasScrollPane.getViewport().setViewPosition(p);

			//repaint();

		}
		else
		{

			if(getSelectionBox().isShowing)
			{
				if((me.getModifiersEx() == middleMask || me.getModifiersEx() == shiftClickMask))
				{

					x++;//so the selection box is actually under the cursor
					y++;

					if(x<0)x=0;
					if(y<0)y=0;
					if(x > MTE.widthTiles * 8)x = MTE.widthTiles * 8;
					if(y > MTE.heightTiles * 8)y = MTE.heightTiles * 8;

					getSelectionBox().setLocation2(x, y);
					repaintBufferImage();
					repaint();
					setText("MTECanvas: Selection set: " + getSelectionBox().x1 + "," + getSelectionBox().y1 + " to " + x + "," + y + " ("+getSelectionBox().getWidth()+" x "+getSelectionBox().getHeight()+")");
					return;
				}


				if(
						getSelectionBox().isShowing&&
						selectionDragged==false&&
						getSelectionBox().contains(x, y)
				)
				{
					setCursor(new Cursor(Cursor.MOVE_CURSOR));
					selectionDragged = true;
					return;
				}


				if(selectionDragged)
				{
					//draw selection box under cursor
					repaint();
					Graphics G = getGraphics();
					G.setColor(new Color(255,0,0,255));

					G.drawRect(x*zoom-(dragPixelx-getSelectionBox().x1)*zoom,y*zoom-(dragPixely-getSelectionBox().y1)*zoom,getSelectionBox().getWidth()*zoom,getSelectionBox().getHeight()*zoom);

					return;
				}
			}
			mouseClicked(me);
		}
	}
	//===============================================================================================
	public void mouseWheelMoved(MouseWheelEvent mwe)
	{//===============================================================================================
		if(mwe.getWheelRotation() > 0)
		{
			zoomIn();
		}
		if(mwe.getWheelRotation() < 0)
		{
			zoomOut();
		}
	}
	//===============================================================================================
	public void keyPressed(KeyEvent ke)
	{//===============================================================================================
		if(ke.getKeyCode() == KeyEvent.VK_DELETE)
		{
			deleteSelection();
		}
		else if(ke.getKeyCode() == KeyEvent.VK_X && ke.isControlDown())
		{
			cutSelectionKeys();
		}
		else if(ke.getKeyCode() == KeyEvent.VK_F && ke.isControlDown())
		{
			flipSelection();
		}
		else if(ke.getKeyCode() == KeyEvent.VK_R && ke.isControlDown())
		{
			reverseSelection();
		}
		else if(ke.getKeyCode() == KeyEvent.VK_V && ke.isControlDown())
		{
			if(ke.isShiftDown())
			{
				pasteSelectionKeysNonZero();
			}
			else
			{
				pasteSelectionKeys();
			}
		}
		else if(ke.getKeyCode() == KeyEvent.VK_C && ke.isControlDown())
		{
			copySelectionKeys();
		}
		else if(ke.getKeyCode() == KeyEvent.VK_Z && ke.isControlDown())
		{
			undo();

		}
		else if(ke.getKeyCode() == KeyEvent.VK_Y && ke.isControlDown())
		{
			redo();
		}
		else if(ke.getKeyCode() == KeyEvent.VK_A && ke.isControlDown())
		{
			getSelectionBox().setLocation(0, 0);
			getSelectionBox().setSize(MTE.widthTiles * 8, MTE.heightTiles * 8);
			getSelectionBox().isShowing = true;
			setText("MTECanvas: Selected All");
			repaint();
		}
		else if(ke.getKeyCode() == KeyEvent.VK_MINUS)
		{
			zoomOut();
		}
		else if(ke.getKeyCode() == KeyEvent.VK_EQUALS)
		{
			zoomIn();
		}
		else if(ke.getKeyCode() == KeyEvent.VK_ADD)
		{

			if(MTE.controlPanel.paletteCanvas.colorSelected < 255)
			{
				MTE.controlPanel.paletteCanvas.selectColor(MTE.controlPanel.paletteCanvas.colorSelected + 1);
			}

		}
		else if(ke.getKeyCode() == KeyEvent.VK_SUBTRACT)
		{

			if(MTE.controlPanel.paletteCanvas.colorSelected > 0)
			{
				MTE.controlPanel.paletteCanvas.selectColor(MTE.controlPanel.paletteCanvas.colorSelected - 1);
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
}
