package com.bobsgame.editor.SpriteEditor;

import java.awt.Canvas;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.image.ImageObserver;

import javax.swing.JComponent;
import javax.swing.JViewport;
import javax.swing.Scrollable;

import com.bobsgame.editor.Project.Sprite.Sprite;
import com.bobsgame.shared.SpriteAnimationSequence;


//===============================================================================================
public class SEFrameCanvas extends JComponent implements MouseListener, ImageObserver, Scrollable
{//===============================================================================================


	protected SpriteEditor SE;



	//===============================================================================================
	public SEFrameCanvas(SpriteEditor se)
	{//===============================================================================================
		SE = se;

		addMouseListener(this);



	}

	//===============================================================================================
	public Sprite getSprite()
	{//===============================================================================================
		return SpriteEditor.getSprite();
	}

	@Override
	public Dimension getPreferredScrollableViewportSize() {
		return getPreferredSize();
	}

	@Override
	public int getScrollableUnitIncrement(Rectangle visibleRect, int orientation, int direction) {
		return 10;
	}

	@Override
	public int getScrollableBlockIncrement(Rectangle visibleRect, int orientation, int direction) {
		return 100;
	}

	@Override
	public boolean getScrollableTracksViewportWidth() {
		return true;
	}

	@Override
	public boolean getScrollableTracksViewportHeight() {
		return false;
	}

	@Override
	public Dimension getPreferredSize() {
		if(getSprite() == null) return new Dimension(100, 100);
		
		int zoom = 4;
		int w = getSprite().wP()*zoom;
		int h = getSprite().hP()*zoom;
		int f = getSprite().frames();
		
		int viewportWidth = 100;
		if(getParent() instanceof JViewport) {
			viewportWidth = ((JViewport)getParent()).getWidth();
		} else if (SpriteEditor.frameScrollPane != null) {
			 viewportWidth = SpriteEditor.frameScrollPane.getViewport().getWidth();
		}
		
		if(viewportWidth <= 0) viewportWidth = 100;

		int frameTotalWidth = w + 1;
		int columns = viewportWidth / frameTotalWidth;
		if (columns < 1) columns = 1;
		
		int rows = (f + columns - 1) / columns;
		
		return new Dimension(viewportWidth, rows * (h + 40));
	}

	//===============================================================================================
	public void paint(Graphics G)
	{//===============================================================================================

		super.paint(G);

		if(G!=null && getSprite() != null)
		{
			int zoom = 4;

			int w = getSprite().wP()*zoom;
			int h = getSprite().hP()*zoom;
			int f = getSprite().frames();

			//setSize((w*f)+(f*1),h+40);
			
			int viewportWidth = getWidth();
			int frameTotalWidth = w + 1;
			int columns = viewportWidth / frameTotalWidth;
			if (columns < 1) columns = 1;

			G.setColor(SE.getSpritePal().getColor(0));
			G.fillRect(0,0,getWidth(),getHeight());
			//G.setColor(Color.BLACK);
			//G.fillRect(0,getHeight()-40,getWidth(),getHeight());
			G.setFont(new Font("Tahoma",Font.PLAIN,9));

			for(int n=0;n<f;n++)
			{
				int col = n % columns;
				int row = n / columns;
				
				int x = col * frameTotalWidth;
				int y = row * (h + 40);

				//draw sprite frame
				G.drawImage(getSprite().getFrameImage(n),x+1,y,w,h,this);

				//draw sprite frame hitbox
				SpriteAnimationSequence a = getSprite().getAnimationStartFrameForFrame(n);
				if(a!=null)
				{

					G.setColor(Color.RED);
					//int x = ((n*w)+(n*1))+1;
					//int y = 0;

					int hL = a.hitBoxFromLeftPixels1X*zoom;
					int hR = a.hitBoxFromRightPixels1X*zoom;
					int hT = a.hitBoxFromTopPixels1X*zoom;
					int hB = a.hitBoxFromBottomPixels1X*zoom;

					G.drawRect(x+1+hL, y+hT, ((w-hL)-hR)-1, ((h-hT)-hB)-1);
				}

				//draw divider line
				G.setColor(Color.BLACK);
				G.drawLine(x, y, x, y+h);

				//draw frame #
				G.setColor(Color.WHITE);
				G.drawString(""+n, x+1, y+h+10);


				SpriteAnimationSequence currentFrameAnimation = getSprite().getAnimationForExactFrameOrNull(n);
				if(currentFrameAnimation!=null)
				{
					//draw frame Name
					G.setColor(Color.RED);
					G.drawString(currentFrameAnimation.frameSequenceName, x+1, y+h+20);
				}
				
				int currentFrame = getSprite().getSelectedFrameIndex();
				if(n == currentFrame) {
					G.setColor(Color.GREEN);
					G.drawRect(x, y, w+1, h+40);
					G.drawString(""+currentFrame, x+1, y+h+10);
				}
			}

			//int currentFrame = getSprite().getSelectedFrameIndex();

			//G.setColor(Color.GREEN);
			//G.drawRect((currentFrame*w)+(currentFrame*1), 0, w, h);
			//G.drawString(""+currentFrame, ((currentFrame*w)+(currentFrame*1))+1, h+10);
		}

	}
	//===============================================================================================
	public void scrollToFrame(int frame)
	{//===============================================================================================
		if(getSprite() == null) return;
		int w = getSprite().wP()*4;
		int h = getSprite().hP()*4;
		//int f = getSprite().frames();

		int viewportWidth = getWidth();
		int frameTotalWidth = w + 1;
		int columns = viewportWidth / frameTotalWidth;
		if (columns < 1) columns = 1;
		
		int col = frame % columns;
		int row = frame / columns;

		Point p = new Point();

		p.x = col * frameTotalWidth;
		p.y = row * (h + 40);
		//p.x = SE.frameScrollPane.getViewportSize().width;
		//p.y = SE.frameScrollPane.getViewportSize().height;

		SpriteEditor.frameScrollPane.getHorizontalScrollBar().setValue(p.x);
		SpriteEditor.frameScrollPane.getVerticalScrollBar().setValue(p.y);
	}

	//===============================================================================================
	@Override
	public void mouseClicked(MouseEvent me)
	{//===============================================================================================




	}


	//===============================================================================================
	@Override
	public void mousePressed(MouseEvent me)
	{//===============================================================================================
		if(getSprite() == null) return;

		int w = getSprite().wP()*4;
		int h = getSprite().hP()*4;
		int f = getSprite().frames();

		int x = me.getX();
		int y = me.getY();

		int viewportWidth = getWidth();
		int frameTotalWidth = w + 1;
		int columns = viewportWidth / frameTotalWidth;
		if (columns < 1) columns = 1;
		
		int col = x / frameTotalWidth;
		int row = y / (h + 40);
		
		int frame = row * columns + col;

		if(frame >= 0 && frame < f) {
			getSprite().setFrame(frame);
	
			SpriteEditor.frameControlPanel.updateSpriteInfo();
			SpriteEditor.frameControlPanel.updateFrames();
	
			SpriteEditor.editCanvas.repaintBufferImage();
			SpriteEditor.editCanvas.repaint();
		}


	}


	//===============================================================================================
	@Override
	public void mouseReleased(MouseEvent e)
	{//===============================================================================================


	}


	//===============================================================================================
	@Override
	public void mouseEntered(MouseEvent e)
	{//===============================================================================================


	}


	//===============================================================================================
	@Override
	public void mouseExited(MouseEvent e)
	{//===============================================================================================


	}


}
