package com.bobsgame.editor.SpriteEditor;


import java.awt.Color;
import java.awt.Cursor;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.Transparency;
import java.awt.event.InputEvent;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;

import javax.swing.event.ListSelectionEvent;


import com.bobsgame.editor.SelectionArea;
import com.bobsgame.editor.MultipleTileEditor.MTECanvas;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.Sprite.Sprite;
import com.bobsgame.shared.SpriteAnimationSequence;
import com.bobsgame.editor.Undo.*;
import com.bobsgame.editor.SpriteEditor.Tools.Brush;
import com.bobsgame.editor.SpriteEditor.Tools.PixelBrush;

//===============================================================================================
public class SECanvas extends MTECanvas
{//===============================================================================================


	protected SpriteEditor SE;

	public Brush currentBrush = new PixelBrush();

	public SESelectionArea selectionBox;

	public CompoundEdit getCurrentEdit() {
		return currentEdit;
	}


	private int oldx=0;
	private int oldy=0;



	//===============================================================================================
	public SECanvas(SpriteEditor se)
	{//===============================================================================================
		SE = se;

		selectionBox = new SESelectionArea(this);
		//setBackground(Color.BLACK);


		setFocusable(true);
		addMouseWheelListener(this);
		addMouseListener(this);
		addMouseMotionListener(this);
		addKeyListener(this);

	}

	//===============================================================================================
	public void setText(String s)
	{//===============================================================================================
		SE.infoLabel.setTextNoConsole(s);
	}
	//===============================================================================================
	public SelectionArea getSelectionBox()
	{//===============================================================================================
		return selectionBox;
	}

	//===============================================================================================
	public Sprite getSprite()
	{//===============================================================================================
		return SpriteEditor.getSprite();
	}

	//===============================================================================================
	public void undo()
	{//===============================================================================================
		super.undo();
		setText("Sprite Editor: Undid " + undoManager.getUndoPresentationName());
	}
	//===============================================================================================
	public void redo()
	{//===============================================================================================
		super.redo();
		setText("Sprite Editor: Redid " + undoManager.getRedoPresentationName());
	}





	//===============================================================================================
	public void paint(Graphics G)
	{//===============================================================================================

		if(editBufferImage == null)
		{
			repaintBufferImage();
		}

		if(G!=null)
		{

			//G.setColor(Color.DARK_GRAY.darker());
			//G.fillRect(0, 0, this.getWidth(), this.getHeight());
			G.drawImage(editBufferImage, 0, 0, getSprite().wP() * zoom, getSprite().hP() * zoom, 0, 0, getSprite().wP(), getSprite().hP(), this);
			//G.setColor(Color.WHITE);
			//G.drawRect(0, 0, SE.getSprite().getWidth() * zoom, (SE.getSprite().getHeight() * zoom));


			if(SpriteEditor.showGrid.isSelected()==true)
			{
				G.setColor(Color.white);

				for(int yy = 8 * zoom; yy < getSprite().hP() * zoom; yy += 8 * zoom)
				{
					G.drawLine(0, yy, getSprite().wP() * zoom, yy);
				}
				for(int xx = 8 * zoom; xx < getSprite().wP() * zoom; xx += 8 * zoom)
				{
					G.drawLine(xx, 0, xx, getSprite().hP() * zoom);
				}
			}

			if(SpriteEditor.mirrorMode.isSelected())
			{
				//draw hit bounds on sprite
				G.setColor(Color.MAGENTA);

				int w = getSprite().wP();
				int h = getSprite().hP();

				G.drawLine(w*zoom/2,0,w*zoom/2,h*zoom);
			}

			if(SpriteEditor.mirrorYMode.isSelected())
			{
				G.setColor(Color.MAGENTA);
				int w = getSprite().wP();
				int h = getSprite().hP();
				G.drawLine(0, h*zoom/2, w*zoom, h*zoom/2);
			}

			if(SpriteEditor.showHitBox.isSelected())
			{

				SpriteAnimationSequence a = getSprite().getClosestAnimationForCurrentFrame();
				if(a!=null)
				{

					//draw hit bounds on sprite
					G.setColor(Color.RED);


					int hL = a.hitBoxFromLeftPixels1X;
					int hR = a.hitBoxFromRightPixels1X;
					int hT = a.hitBoxFromTopPixels1X;
					int hB = a.hitBoxFromBottomPixels1X;

					int w = getSprite().wP();
					int h = getSprite().hP();

					G.drawRect(hL * zoom, hT * zoom, ((((w-(hL))-hR)) * zoom)-1, ((h-hT)-hB)*zoom-1);
				}
			}

			if(SpriteEditor.showUtilityPoint.isSelected())
			{
				//draw utility point on sprite
				G.setColor(Color.GREEN);
				G.fillRect(getSprite().utilityOffsetXPixels1X() * zoom, getSprite().utilityOffsetYPixels1X() * zoom, 2, 2);
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

		Graphics BG = getGraphics();
		if(BG!=null)
		{
			BG.setColor(Color.DARK_GRAY);
			BG.fillRect(0, 0, this.getWidth(), this.getHeight());
		}

		if(editBufferImage == null)editBufferImage = getGraphicsConfiguration().createCompatibleImage(getSprite().wP(), getSprite().hP(), Transparency.OPAQUE);

		Graphics G = editBufferImage.getGraphics();

		if(Project.getNumSprites() > 0 && Project.getNumSpritePalettes() > 0)
		{
			G.setColor(Project.getSelectedSpritePalette().getColor(0));
			G.fillRect(0, 0, getSprite().wP(), getSprite().hP());

			int f = getSprite().selectedFrameIndex;

			if (SpriteEditor.onionSkinMode.isSelected()) {
				if (f > 0) drawFrame(G, f - 1, 0.3f);
				if (f < getSprite().frames() - 1) drawFrame(G, f + 1, 0.3f);
			}

			drawFrame(G, f, 1.0f);
		}

		SpriteEditor.setFrameCanvasHeight();

	}

	private void drawFrame(Graphics G, int frameIndex, float alphaMult) {
		for(Sprite.Layer layer : getSprite().getLayers()) {
			if(!layer.visible) continue;

			for(int y = 0; y < getSprite().hP(); y++)
			{
				for(int x = 0; x < getSprite().wP(); x++)
				{
					int p = layer.pixels[frameIndex][x][y];
					if(p == 0) continue;

					Color c = Project.getSelectedSpritePalette().getColor(p);
					float finalAlpha = layer.opacity * alphaMult;

					if(finalAlpha < 1.0f) {
						c = new Color(c.getRed(), c.getGreen(), c.getBlue(), (int)(255 * finalAlpha));
					}

					G.setColor(c);
					G.fillRect(x, y, 1, 1);
				}
			}
		}
	}

	//===============================================================================================
	public void setSizeDoLayout()
	{//===============================================================================================

		int sizeX = getSprite().wP() * zoom;
		int sizeY = getSprite().hP() * zoom;

		setSize(new Dimension(sizeX,sizeY));
		setPreferredSize(new Dimension(sizeX,sizeY));
		setMinimumSize(new Dimension(sizeX,sizeY));
		setMaximumSize(new Dimension(sizeX,sizeY));
		validate();



		SE.editCanvasScrollPane.setViewportView(this);
		SE.editCanvasScrollPane.getViewport().setViewSize(new Dimension(sizeX,sizeY));
		SE.editCanvasScrollPane.getViewport().validate();

		SE.editCanvasScrollPane.validate();
	}


	//===============================================================================================
	public void zoomIn()
	{//===============================================================================================
		if(zoom < 32)
		{
			zoom += 2;
		}


		{

			setSizeDoLayout();


			Point p = new Point();
			p.x = SE.editCanvasScrollPane.getHorizontalScrollBar().getValue();
			p.y = SE.editCanvasScrollPane.getVerticalScrollBar().getValue();
			if(getSelectionBox().isShowing)
			{
				p.x = (getSelectionBox().x2 * zoom) - ((getSprite().wP() * zoom) / 2);  //(((SA.x1*zoom) + (((SA.x2*zoom)-(SA.x1*zoom))/2))) - ((SE.getSprite().getWidth()*zoom)/2);
				p.y = (getSelectionBox().y2 * zoom) - ((getSprite().hP() * zoom) / 2);  //(((SA.y1*zoom) + (((SA.y2*zoom)-(SA.y1*zoom))/2))) - ((SE.getSprite().getHeight()*zoom)/2);
			}
			else
			{
				p.x = (((p.x + ((getSprite().wP() * zoom) / 2)) / (zoom - 1)) * zoom) - ((getSprite().wP() * zoom) / 2);
				p.y = (((p.y + ((getSprite().hP() * zoom) / 2)) / (zoom - 1)) * zoom) - ((getSprite().hP() * zoom) / 2);
				if(getSprite().wP() * zoom < getSprite().wP())
				{
					p.x = 0;
				}
				if(getSprite().hP() * zoom < getSprite().hP())
				{
					p.y = 0;
				}
			}
			if(p.x > SE.editCanvasScrollPane.getHorizontalScrollBar().getMaximum())
			{
				p.x = SE.editCanvasScrollPane.getHorizontalScrollBar().getMaximum();
			}
			if(p.y > SE.editCanvasScrollPane.getVerticalScrollBar().getMaximum())
			{
				p.y = SE.editCanvasScrollPane.getVerticalScrollBar().getMaximum();
			}
			SE.editCanvasScrollPane.getHorizontalScrollBar().setValue(p.x);
			SE.editCanvasScrollPane.getVerticalScrollBar().setValue(p.y);
		}
	}
	//===============================================================================================
	public void zoomOut()
	{//===============================================================================================
		if(zoom > 2)
		{
			zoom -= 2;
		}


		{
			setSizeDoLayout();

			Point p = new Point();
			p.x = SE.editCanvasScrollPane.getHorizontalScrollBar().getValue();
			p.y = SE.editCanvasScrollPane.getVerticalScrollBar().getValue();
			if(getSelectionBox().isShowing)
			{
				p.x = (getSelectionBox().x2 * zoom) - ((getSprite().wP() * zoom) / 2);  //(((SA.x1*zoom) + (((SA.x2*zoom)-(SA.x1*zoom))/2))) - ((SE.getSprite().getWidth()*zoom)/2);
				p.y = (getSelectionBox().y2 * zoom) - ((getSprite().hP() * zoom) / 2);  //(((SA.y1*zoom) + (((SA.y2*zoom)-(SA.y1*zoom))/2))) - ((SE.getSprite().getHeight()*zoom)/2);
			}
			else
			{
				p.x = (((p.x + ((getSprite().wP() * zoom) / 2)) / (zoom - 1)) * zoom) - ((getSprite().wP() * zoom) / 2);
				p.y = (((p.y + ((getSprite().hP() * zoom) / 2)) / (zoom - 1)) * zoom) - ((getSprite().hP() * zoom) / 2);
				if(getSprite().wP() * zoom < getSprite().wP())
				{
					p.x = 0;
				}
				if(getSprite().hP() * zoom < getSprite().hP())
				{
					p.y = 0;
				}
			}
			if(p.x > SE.editCanvasScrollPane.getHorizontalScrollBar().getMaximum())
			{
				p.x = SE.editCanvasScrollPane.getHorizontalScrollBar().getMaximum();
			}
			if(p.y > SE.editCanvasScrollPane.getVerticalScrollBar().getMaximum())
			{
				p.y = SE.editCanvasScrollPane.getVerticalScrollBar().getMaximum();
			}
			SE.editCanvasScrollPane.getHorizontalScrollBar().setValue(p.x);
			SE.editCanvasScrollPane.getVerticalScrollBar().setValue(p.y);

		}
	}
	//===============================================================================================
	public void fill(int sx, int sy, int color, int prevcolor, CompoundEdit edit)
	{//===============================================================================================

		{
			setPixel(sx, sy, color, edit);


			int pixel;
			if(sx > 0)
			{
				pixel = getPixel(sx - 1, sy);
				if(pixel != color && pixel == prevcolor)
				{
					fill(sx - 1, sy, color, prevcolor, edit);
				}
			}
			if(sx < getSprite().wP() - 1)
			{
				pixel = getPixel(sx + 1, sy);
				if(pixel != color && pixel == prevcolor)
				{
					fill(sx + 1, sy, color, prevcolor, edit);
				}
			}
			if(sy > 0)
			{
				pixel = getPixel(sx, sy - 1);
				if(pixel != color && pixel == prevcolor)
				{
					fill(sx, sy - 1, color, prevcolor, edit);
				}
			}
			if(sy < getSprite().hP() - 1)
			{
				pixel = getPixel(sx, sy + 1);
				if(pixel != color && pixel == prevcolor)
				{
					fill(sx, sy + 1, color, prevcolor, edit);
				}
			}
		}
	}
	//===============================================================================================
	public void setPixelRaw(int x, int y, int color)
	{//===============================================================================================
		getSprite().setPixel(x, y, color);
	}

	//===============================================================================================
	private void applyPixel(int x, int y, int color, CompoundEdit edit) {
		int oldColor = getPixel(x, y);
		if(oldColor != color) {
			if(edit != null) {
				edit.addEdit(new PixelChangeEdit(this, x, y, oldColor, color));
			}
			setPixelRaw(x, y, color);
		}
	}

	public void setPixel(int x, int y, int color, CompoundEdit edit)
	{//===============================================================================================
		applyPixel(x, y, color, edit);

		boolean mx = SpriteEditor.mirrorMode.isSelected();
		boolean my = SpriteEditor.mirrorYMode.isSelected();

		int w = getSprite().wP()-1;
		int h = getSprite().hP()-1;

		if(mx)
		{
			int newX = (w-x);
			applyPixel(newX, y, color, edit);
		}

		if(my)
		{
			int newY = (h-y);
			applyPixel(x, newY, color, edit);
		}

		if(mx && my)
		{
			int newX = (w-x);
			int newY = (h-y);
			applyPixel(newX, newY, color, edit);
		}
	}

	//===============================================================================================
	public void setPixel(int x, int y, int color)
	{//===============================================================================================

		getSprite().setPixel(x, y, color);

		boolean mx = SpriteEditor.mirrorMode.isSelected();
		boolean my = SpriteEditor.mirrorYMode.isSelected();

		int w = getSprite().wP()-1;
		int h = getSprite().hP()-1;

		if(mx)
		{
			int newX = (w-x);
			getSprite().setPixel(newX, y, color);
		}

		if(my)
		{
			int newY = (h-y);
			getSprite().setPixel(x, newY, color);
		}

		if(mx && my)
		{
			int newX = (w-x);
			int newY = (h-y);
			getSprite().setPixel(newX, newY, color);
		}

	}
	//===============================================================================================
	public int getPixel(int x, int y)
	{//===============================================================================================


			return getSprite().getPixel(x, y);

	}
	//===============================================================================================
	public void copySelection(int oldx, int oldy, int newx, int newy, CompoundEdit edit)
	{//===============================================================================================
		if(getSelectionBox().isShowing && getSelectionBox().contains(oldx, oldy))
		{
			int xmax, ymax;

			{
				xmax = getSprite().wP();
				ymax = getSprite().hP();
			}

			if(getSelectionBox().x1 + (newx - oldx) >= 0 && getSelectionBox().y1 + (newy - oldy) >= 0 && getSelectionBox().x2 + (newx - oldx) <= xmax && getSelectionBox().y2 + (newy - oldy) <= ymax)
			{
				getSelectionBox().copy();
				getSelectionBox().moveSelectionBoxPositionByAmt(newx - oldx, newy - oldy);
				((SESelectionArea)getSelectionBox()).paste(edit);
				repaintBufferImage();
				repaint();
				setText("Sprite Editor: Copied Selection");
			}
		}
	}
	//===============================================================================================
	public void moveSelection(int oldx, int oldy, int newx, int newy, CompoundEdit edit)
	{//===============================================================================================
		if(getSelectionBox().isShowing && getSelectionBox().contains(oldx, oldy))
		{
			int xmax, ymax;

			{
				xmax = getSprite().wP();
				ymax = getSprite().hP();
			}

			if(getSelectionBox().x1 + (newx - oldx) >= 0 && getSelectionBox().y1 + (newy - oldy) >= 0 && getSelectionBox().x2 + (newx - oldx) <= xmax && getSelectionBox().y2 + (newy - oldy) <= ymax)
			{
				getSelectionBox().cut();
				getSelectionBox().moveSelectionBoxPositionByAmt(newx - oldx, newy - oldy);
				((SESelectionArea)getSelectionBox()).paste(edit);
				repaintBufferImage();
				repaint();
				setText("Sprite Editor: Moved Selection");
			}
		}
	}



	//===============================================================================================
	public void mouseClicked(MouseEvent me)
	{//===============================================================================================
		// Logic moved to mousePressed/Released to support Drag
	}
	//===============================================================================================
	public void mousePressed(MouseEvent me)
	{//===============================================================================================


		requestFocus();
		requestFocusInWindow();

		int leftMask = InputEvent.BUTTON1_DOWN_MASK;
		int middleMask = InputEvent.BUTTON2_DOWN_MASK;
		int rightMask = InputEvent.BUTTON3_DOWN_MASK;
		int shiftClickMask = InputEvent.BUTTON1_DOWN_MASK | InputEvent.SHIFT_DOWN_MASK;
		int ctrlClickMask = InputEvent.BUTTON1_DOWN_MASK | InputEvent.CTRL_DOWN_MASK;



		oldx = me.getX();
		oldy = me.getY();


		int x = me.getX() / zoom;
		int y = me.getY() / zoom;
		mousePressed = true;
		
		currentEdit = new CompoundEdit();

		if((me.getModifiersEx() == rightMask || me.getModifiersEx() == ctrlClickMask))
		{
			dragPixelx = x;
			dragPixely = y;

			// Right click color pick
			if(x>=0 && y>=0 && x < getSprite().wP() && y < getSprite().hP()) {
				if(SpriteEditor.controlPanel.paletteCanvas.colorSelected != getSprite().getPixel(x, y))
				{
					SpriteEditor.controlPanel.paletteCanvas.selectColor(getSprite().getPixel(x, y));
				}
			}
		}
		else if (me.getModifiersEx() == leftMask)
		{
			dragPixelx = x;
			dragPixely = y;

			if(x>=0 && y>=0 && x < getSprite().wP() && y < getSprite().hP()) {
				// Use Brush
				currentBrush.onMousePress(this, x, y, SpriteEditor.controlPanel.paletteCanvas.colorSelected, me.getModifiersEx());
				repaintBufferImage();
				repaint();
			}
		}
		else if((me.getModifiersEx() == middleMask || me.getModifiersEx() == shiftClickMask))
		{
			int pressedX = (int)(me.getX() / zoom);
			int pressedY = (int)(me.getY() / zoom);
			if(pressedX>=0&&pressedY>=0&&pressedX<getSprite().wP()&&pressedY<getSprite().hP())
			{

				getSelectionBox().setLocation(x, y);
				getSelectionBox().setSize(0, 0);
				getSelectionBox().isShowing=true;
				setText("Sprite Editor: Selection set: " + x + "," + y);
				repaint();
			}
			else
			{

				//deselect any selected area if we've pressed the middle mouse button outside the canvas
				if(getSelectionBox().isShowing==true)
				{
					getSelectionBox().isShowing=false;
					setText("Sprite Editor: Deselected Area");
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

		int x = (me.getX() / zoom);
		int y = (me.getY() / zoom);
		mousePressed = false;

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
		else
		{
			// Brush Release
			currentBrush.onMouseRelease(this, x, y, SpriteEditor.controlPanel.paletteCanvas.colorSelected, me.getModifiersEx());
		}
		
		if(currentEdit != null) {
			currentEdit.end();
			if(currentEdit.isSignificant()) undoManager.addEdit(currentEdit);
			currentEdit = null;
		}
		
		setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
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

			Point p = SE.editCanvasScrollPane.getViewport().getViewPosition();

			p.x+=offsetX;
			p.y+=offsetY;

			SE.editCanvasScrollPane.getViewport().setViewPosition(p);

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
					if(x > getSprite().wP())x = getSprite().wP();
					if(y > getSprite().hP())y = getSprite().hP();

					getSelectionBox().setLocation2(x, y);
					repaintBufferImage();
					repaint();
					setText("Sprite Editor: Selection set: " + getSelectionBox().x1 + "," + getSelectionBox().y1 + " to " + x + "," + y+ " ("+getSelectionBox().getWidth()+" x "+getSelectionBox().getHeight()+")");
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

			// Brush Drag
			int leftMask = InputEvent.BUTTON1_DOWN_MASK;
			if ((me.getModifiersEx() & leftMask) == leftMask) {
				if(x>=0 && y>=0 && x < getSprite().wP() && y < getSprite().hP()) {
					currentBrush.onMouseDrag(this, x, y, SpriteEditor.controlPanel.paletteCanvas.colorSelected, me.getModifiersEx());
					repaintBufferImage();
					repaint();
				}
			}
		}
	}

	//===============================================================================================
	public void keyPressed(KeyEvent ke)
	{//===============================================================================================



		if(ke.getKeyCode() == KeyEvent.VK_U)
		{
			//set utility point offset from SelectionBox
			getSprite().setUtilityOffsetXPixels1X(getSelectionBox().getX());
			getSprite().setUtilityOffsetYPixels1X(getSelectionBox().getY());

			SpriteEditor.frameControlPanel.updateSpriteInfo();

		}
		else
		if(ke.getKeyCode() == KeyEvent.VK_H)
		{
			SpriteAnimationSequence a = getSprite().getClosestAnimationForCurrentFrame();

			if(a==null)
			{
				a = new SpriteAnimationSequence("Frame0",0,0,0,0,0);
				getSprite().animationList().add(a);
			}

			//set hitBox left, right, top, bottom from SelectionBox
			a.hitBoxFromLeftPixels1X = getSelectionBox().getX();
			a.hitBoxFromRightPixels1X = (getSprite().wP()-getSelectionBox().getX())-getSelectionBox().getWidth();
			a.hitBoxFromTopPixels1X = getSelectionBox().getY();
			a.hitBoxFromBottomPixels1X = (getSprite().hP()-getSelectionBox().getY())-getSelectionBox().getHeight();

			SpriteEditor.frameControlPanel.updateSpriteInfo();

		}
		else
		if(ke.getKeyCode() == KeyEvent.VK_A && (ke.getModifiersEx() & InputEvent.CTRL_DOWN_MASK) != 0)
		{
			getSelectionBox().setLocation(0, 0);
			getSelectionBox().setSize(getSprite().wP(), getSprite().hP());
			getSelectionBox().isShowing = true;
			setText("Sprite Editor: Selected All");
			repaint();
		}
		else
		if(ke.getKeyCode() == KeyEvent.VK_A)
		{
			if(getSprite().selectedFrameIndex>0)
			{
				getSprite().previousFrame();
				SpriteEditor.frameControlPanel.updateSpriteInfo();
				SpriteEditor.frameControlPanel.updateFrames();
				repaintBufferImage();
				repaint();
			}
		}
		else
		if(ke.getKeyCode() == KeyEvent.VK_S)
		{
			if(getSprite().selectedFrameIndex<getSprite().frames()-1)
			{
				getSprite().nextFrame();
				SpriteEditor.frameControlPanel.updateSpriteInfo();
				SpriteEditor.frameControlPanel.updateFrames();
				repaintBufferImage();
				repaint();
			}
		}
		else
		if(ke.getKeyCode() == KeyEvent.VK_PAGE_UP)
		{


			if(SE.spriteList.getSelectedIndex()>0)SE.spriteList.setSelectedIndex(SE.spriteList.getSelectedIndex()-1);
			SE.valueChanged(new ListSelectionEvent(SE.spriteList,0,SE.spriteListModel.size()-1, false));




//			if(SE.spriteChoice.getSelectedIndex() - 1 >= 0)
//			{
//				SE.spriteChoice.setSelectedIndex(SE.spriteChoice.getSelectedIndex() - 1);
//			}
//			SE.spriteChoice.paintImmediately(0, 0, SE.spriteChoice.getWidth(), SE.spriteChoice.getHeight());


			//SE.spriteChoice.repaint();
			//SE.itemStateChanged(new ItemEvent(SE.spriteChoice, 701, "", 1));
			//SE.itemStateChanged(new ItemEvent(SE.spriteChoice, 1, "", 1));
		}
		else
		if(ke.getKeyCode() == KeyEvent.VK_PAGE_DOWN)
		{

			if(SE.spriteList.getSelectedIndex()>=0&&SE.spriteList.getSelectedIndex()<SE.spriteListModel.size()-1)SE.spriteList.setSelectedIndex(SE.spriteList.getSelectedIndex()+1);
			SE.valueChanged(new ListSelectionEvent(SE.spriteList,0,SE.spriteListModel.size()-1, false));


//			if(SE.spriteChoice.getSelectedIndex() + 1 < SE.spriteChoice.getItemCount())
//			{
//				SE.spriteChoice.setSelectedIndex(SE.spriteChoice.getSelectedIndex() + 1);
//			}
//			SE.spriteChoice.paintImmediately(0, 0, SE.spriteChoice.getWidth(), SE.spriteChoice.getHeight());



			//SE.spriteChoice.repaint();
			//SE.itemStateChanged(new ItemEvent(SE.spriteChoice, 701, "", 1));
			//SE.itemStateChanged(new ItemEvent(SE.spriteChoice, 1, "", 1));
		}
		else
		if(ke.getKeyCode() == KeyEvent.VK_ADD)
		{
			if(SpriteEditor.controlPanel.paletteCanvas.colorSelected < SE.getSpritePal().numColors)
			{
				SpriteEditor.controlPanel.paletteCanvas.selectColor(SpriteEditor.controlPanel.paletteCanvas.colorSelected + 1);
			}

		}
		else
		if(ke.getKeyCode() == KeyEvent.VK_SUBTRACT)
		{
			if(SpriteEditor.controlPanel.paletteCanvas.colorSelected > 0)
			{
				SpriteEditor.controlPanel.paletteCanvas.selectColor(SpriteEditor.controlPanel.paletteCanvas.colorSelected - 1);
			}
		}
		else
		super.keyPressed(ke);
	}



}
