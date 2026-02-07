package com.bobsgame.editor.MapCanvas;



import java.io.*;
import java.util.Iterator;


import javax.imageio.*;
import javax.imageio.stream.*;
import javax.swing.JComponent;
import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;

import com.bobsgame.EditorMain;
import com.bobsgame.editor.Dialogs.StringDialog;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.Map.Area;
import com.bobsgame.editor.Project.Map.Door;
import com.bobsgame.editor.Project.Map.Entity;
import com.bobsgame.editor.Project.Map.Light;
import com.bobsgame.editor.Project.Map.Map;
import com.bobsgame.editor.Project.Map.MapState;
import com.bobsgame.editor.TileCanvas.TileCanvas;
import com.bobsgame.shared.MapData;
import com.bobsgame.shared.Utils;

import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import com.bobsgame.editor.Undo.*;
//===============================================================================================
public class MapCanvas extends JComponent implements MouseMotionListener, MouseListener, ActionListener, ImageObserver
{//===============================================================================================
	//, KeyListener{//bob9-23-05 //mousewheellistener

	/**
	 *
	 */
	private static final long serialVersionUID = 1L;
	public EditorMain E;

	private int clickedTileX=0;
	private int clickedTileY=0;
	private int clickedMapX=0;
	private int clickedMapY=0;


	private int prevtile=0;
	private int mousePressedX=0;
	private int mousePressedY=0;



	public static int zoom = 16;
	public boolean showMapGrid = false;
	//public Graphics g;
	public MapSizeWindow mapSizeWindow;

	public LightEditWindow lightWindow;
	public AreaEditWindow areaWindow;

	public EntityEditWindow entityWindow;
	public DoorEditWindow doorWindow;

	static public boolean selectedAllLayers = false;//bob 20060523
	static public boolean lockPressed = false;
	static public int selectedLayer = 0;


	public int maxRGBValue=255;

	public boolean
	mouseDragged,
	selectionDragged,
	entityDragged,
	lightDragged,
	lightToggleDragged,
	areaDragged,
	areaArrivalDragged,
	doorDragged,
	doorArrivalDragged,
	doorConnectionDragged,
	entityConnectionDragged,
	areaConnectionDragged
	;

	public MapCanvasSelectionArea mapSelectionArea;



	public boolean zoomOutLock = false;
	public boolean zoomInLock = false;


	public boolean useLayerImageBuffer = false;

	public static int MAXZOOM = 32;
	public BufferedImage mapCanvasImage = null;;
	public int previewMode = 0;
	public int previewX = 0;
	public int previewY = 0;
	
	public UndoManager undoManager = new UndoManager();
	public CompoundEdit currentCompoundEdit = null;


	public boolean lightBlackMasking=false;
	public boolean lightScreenBlending=true;
	public boolean moveEntityByPixel=false;

	public boolean lightBlendWithShadow = false;


	public JPopupMenu entityPopup;
	public JMenuItem spritePopupItem[];

	SpriteSelectionDialog spriteSelectionDialog;
	SpriteSelectionDialog doorSelectionDialog;

	static public boolean nightTimePreview = false;


	public static boolean alwaysShowAreaAndSpriteInfo = true;
	public static boolean alwaysShowAreaOutlines = true;
	public static boolean drawRandomPointOfInterestLines = false;

	public static boolean tileEditMode = false;
	public static boolean autoTileMode = false;



	//===============================================================================================
	public MapCanvas(EditorMain e)
	{//===============================================================================================
		E = e;
		mapSizeWindow = new MapSizeWindow(this);
		lightWindow = new LightEditWindow(E);
		areaWindow = new AreaEditWindow(E);
		entityWindow = new EntityEditWindow(E);
		doorWindow = new DoorEditWindow(E);
		spriteSelectionDialog = new SpriteSelectionDialog(E,"Select Sprite", E, false);
		doorSelectionDialog = new SpriteSelectionDialog(E,"Select Sprite", E, true);

		addMouseListener(this);
		addMouseMotionListener(this);
		//addMouseWheelListener(this);

		setFocusable(true);
		addKeyListener(E);

		mapSelectionArea = new MapCanvasSelectionArea(this);
		//nopaint = false;

		//if(getPeer()==null)System.out.println("nopeer");else System.out.println("peer");
		//E.mapCanvas = this;
		//MapCanvas nmp= new MapCanvas(E);
		//nmp = this;
		//E.mapCanvas = nmp;


		entityPopup = new JPopupMenu();
		entityPopup.setLightWeightPopupEnabled(false);
		entityPopup.setAutoscrolls(true);

		//entityPopup.setMaximumSize(new Dimension(600, 1200));



		spritePopupItem = new JMenuItem[1024];

		entityPopup.setForeground(Color.WHITE);
		entityPopup.setBackground(Color.BLACK);
		//entityPopup.setBorderPainted(false);
		entityPopup.setFont(new Font("Tahoma", Font.PLAIN, 8));



	}

	//===============================================================================================
	public Map getMap()
	{//===============================================================================================
		return Project.getSelectedMap();
	}

	//===============================================================================================
	public MapState getState()
	{//===============================================================================================
		return getMap().getSelectedState();
	}




	/*//===============================================================================================
	public boolean isShadowLayer(int l)
	{//===============================================================================================

		if(l==MapData.SPRITE_SHADOW_LAYER)return true;
		if(l==MapData.GROUND_SHADOW_LAYER)return true;
		if(l==MapData.OBJECT_SHADOW_LAYER)return true;
		return false;
	}*/



	//===============================================================================================
	public void undo()
	{//===============================================================================================

		EditorMain.infoLabel.setTextNoConsole("MapCanvas: Undoing...");

		if(undoManager.canUndo()) {
			undoManager.undo();
			EditorMain.infoLabel.setTextSuccess("MapCanvas: Undid " + undoManager.getUndoPresentationName());
		} else {
			EditorMain.infoLabel.setTextError("MapCanvas: Nothing to undo");
		}
	}

	//===============================================================================================
	public void redo()
	{//===============================================================================================

		EditorMain.infoLabel.setTextNoConsole("MapCanvas: Redoing...");

		if(undoManager.canRedo()) {
			undoManager.redo();
			EditorMain.infoLabel.setTextSuccess("MapCanvas: Redid " + undoManager.getRedoPresentationName());
		} else {
			EditorMain.infoLabel.setTextError("MapCanvas: Nothing to redo");
		}

	}

	//===============================================================================================
	public void setSizedoLayout()
	{//===============================================================================================

		int viewportSizeX = EditorMain.mapScrollPane.getViewport().getWidth();//E.mapScrollPane.getViewportSize().width
		int viewportSizeY = EditorMain.mapScrollPane.getViewport().getHeight();//E.mapScrollPane.getViewportSize().height

		int sizeX = getMap().wT() * MAXZOOM + viewportSizeX*2;
		int sizeY = getMap().hT() * MAXZOOM + viewportSizeY*2;

		if(getMap() != null)
		{
			setSize(new Dimension(sizeX,sizeY));
			setPreferredSize(new Dimension(sizeX,sizeY));
			setMinimumSize(new Dimension(sizeX,sizeY));
			setMaximumSize(new Dimension(sizeX,sizeY));
			validate();
		}


		EditorMain.mapScrollPane.setViewportView(this);
		EditorMain.mapScrollPane.getViewport().setViewSize(new Dimension(sizeX,sizeY));
		EditorMain.mapScrollPane.getViewport().validate();

		EditorMain.mapScrollPane.validate();


		//undoinit = 0;
	}

	//===============================================================================================
	public void scrollToPixelXY(int pX, int pY)
	{//===============================================================================================

		setSizedoLayout();

		int viewportSizeX = EditorMain.mapScrollPane.getViewport().getWidth();//E.mapScrollPane.getViewportSize().width
		int viewportSizeY = EditorMain.mapScrollPane.getViewport().getHeight();//E.mapScrollPane.getViewportSize().height

		Point p = new Point();
		p.x = viewportSizeX + (pX/8*zoom) - (viewportSizeX / 2);
		p.y = viewportSizeY + (pY/8*zoom) - (viewportSizeY / 2);

		EditorMain.mapScrollPane.getViewport().setViewPosition(p);

		repaint();

	}

	//===============================================================================================
	public void scrollToPixelXYTop(int pX, int pY)
	{//===============================================================================================

		setSizedoLayout();

		int viewportSizeX = EditorMain.mapScrollPane.getViewport().getWidth();//E.mapScrollPane.getViewportSize().width
		int viewportSizeY = EditorMain.mapScrollPane.getViewport().getHeight();//E.mapScrollPane.getViewportSize().height

		Point p = new Point();
		p.x = viewportSizeX + (pX/8*zoom) - (viewportSizeX / 2);
		p.y = viewportSizeY + (pY/8*zoom) - (viewportSizeY / 4);

		EditorMain.mapScrollPane.getViewport().setViewPosition(p);

		repaint();

	}

	//===============================================================================================
	public static int drawOffsetX()
	{//===============================================================================================
		int viewportSizeX = EditorMain.mapScrollPane.getViewport().getWidth();//E.mapScrollPane.getViewportSize().width
		int viewportSizeY = EditorMain.mapScrollPane.getViewport().getHeight();//E.mapScrollPane.getViewportSize().height

		return viewportSizeX;

	}
	//===============================================================================================
	public static int drawOffsetY()
	{//===============================================================================================
		int viewportSizeX = EditorMain.mapScrollPane.getViewport().getWidth();//E.mapScrollPane.getViewportSize().width
		int viewportSizeY = EditorMain.mapScrollPane.getViewport().getHeight();//E.mapScrollPane.getViewportSize().height

		return viewportSizeY;

	}
	//===============================================================================================
	public int getTileXFromCanvasX(int tx)
	{//===============================================================================================
		return 0;

	}
	//===============================================================================================
	public int getTileYFromCanvasY(int ty)
	{//===============================================================================================
		return 0;
	}
	//===============================================================================================
	public int getMapXFromCanvasX(int px)
	{//===============================================================================================
		return 0;
	}
	//===============================================================================================
	public int getMapYFromCanvasY(int py)
	{//===============================================================================================
		return 0;

	}


	//===============================================================================================
	public void zoomIn()
	{//===============================================================================================



		if(zoom < MAXZOOM)
		{

			//if(zoomInLock==false)
			//{
			//zoomInLock=true;

			zoom++;

			//setSizedoLayout();

			if(getMap() != null)
			{
				//reshape(0,0,getMap().getWidth()*zoom,getMap().getHeight()*zoom);

				//Graphics G = getGraphics();
				//G.translate(drawOffsetX(),drawOffsetY());
				//g.setClip(null);
				//g.setColor(Color.DARK_GRAY);
				//g.fillRect(0, 0, getMap().getWidth() * MAXZOOM, getMap().getHeight() * MAXZOOM);
				//g.dispose();

				//Point p = new Point();
				//Point p = E.mapScrollPane.getScrollPosition();


				if(mapSelectionArea.isShowing)
				{

					if(selectedLayer==MapData.MAP_LIGHT_LAYER)
					{
						//p.x = ((((mapSelectionArea.x1/8) * zoom) + ((((mapSelectionArea.x2/8) * zoom) - ((mapSelectionArea.x1/8) * zoom)) / 2))) - (viewportSizeX / 2);
						//p.y = ((((mapSelectionArea.y1/8) * zoom) + ((((mapSelectionArea.y2/8) * zoom) - ((mapSelectionArea.y1/8) * zoom)) / 2))) - (viewportSizeY / 2);
						//p = E.mapScrollPane.getViewport().toViewCoordinates(p);

						int pX = ((mapSelectionArea.x1) + (((mapSelectionArea.x2) - (mapSelectionArea.x1)) / 2));
						int pY = ((mapSelectionArea.y1) + (((mapSelectionArea.y2) - (mapSelectionArea.y1)) / 2));

						scrollToPixelXY(pX, pY);
					}
					else
					{
						//p.x = (((mapSelectionArea.x1 * zoom) + (((mapSelectionArea.x2 * zoom) - (mapSelectionArea.x1 * zoom)) / 2))) - (viewportSizeX / 2);
						//p.y = (((mapSelectionArea.y1 * zoom) + (((mapSelectionArea.y2 * zoom) - (mapSelectionArea.y1 * zoom)) / 2))) - (viewportSizeY / 2);
						//p = E.mapScrollPane.getViewport().toViewCoordinates(p);

						int pX = ((mapSelectionArea.x1) + (((mapSelectionArea.x2) - (mapSelectionArea.x1)) / 2));
						int pY = ((mapSelectionArea.y1) + (((mapSelectionArea.y2) - (mapSelectionArea.y1)) / 2));

						scrollToTileXY(pX, pY);
					}
				}
				else if(mapSelectionArea.isShowingLock())
				{
					//p.x = (((mapSelectionArea.x1Lock * zoom) + (((mapSelectionArea.x2Lock * zoom) - (mapSelectionArea.x1Lock * zoom)) / 2))) - (viewportSizeX / 2);
					//p.y = (((mapSelectionArea.y1Lock * zoom) + (((mapSelectionArea.y2Lock * zoom) - (mapSelectionArea.y1Lock * zoom)) / 2))) - (viewportSizeY / 2);
					//p = E.mapScrollPane.getViewport().toViewCoordinates(p);

					int pX = ((mapSelectionArea.x1Lock) + (((mapSelectionArea.x2Lock) - (mapSelectionArea.x1Lock)) / 2));
					int pY = ((mapSelectionArea.y1Lock) + (((mapSelectionArea.y2Lock) - (mapSelectionArea.y1Lock)) / 2));

					scrollToTileXY(pX, pY);
				}
				else
				if(selectedLayer==MapData.MAP_LIGHT_LAYER&& getMap().getSelectedLightIndex()!=-1)
				{
					scrollTo(getMap().getSelectedLight());
				}
				else
				if(selectedLayer==MapData.MAP_DOOR_LAYER&& getMap().getSelectedDoorIndex()!=-1)
				{
					scrollTo(getMap().getSelectedDoor());
				}
				else
				if(selectedLayer==MapData.MAP_AREA_LAYER&& getMap().getSelectedAreaIndex()!=-1)
				{
					scrollTo(getMap().getSelectedArea());
				}
				else
				if(selectedLayer==MapData.MAP_ENTITY_LAYER&& getMap().getSelectedEntityIndex()!=-1)
				{
					scrollTo(getMap().getSelectedEntity());
				}
				else
				{

					//p.x = ((getMap().getWidth()*zoom)/2) - (E.mapScrollPane.getViewportSize().width/2);
					//p.y = ((getMap().getHeight()*zoom)/2) - (E.mapScrollPane.getViewportSize().height/2);

					//p.x = (p.x/(zoom-1))*zoom;
					//p.y = (p.y/(zoom-1))*zoom;


					setSizedoLayout();



					//if the map will fit in the viewport, center it.
					int viewportSizeX = EditorMain.mapScrollPane.getViewport().getWidth();//E.mapScrollPane.getViewportSize().width
					int viewportSizeY = EditorMain.mapScrollPane.getViewport().getHeight();//E.mapScrollPane.getViewportSize().height

					Point p = EditorMain.mapScrollPane.getViewport().getViewPosition();

					//if the map will fit in the viewport, center it.
					if(getMap().wT()*zoom<viewportSizeX)
					{
						p.x = viewportSizeX - (viewportSizeX-getMap().wT()*zoom)/2;
					}
					else
					{
						//zoom into point on map in the center of viewport

						int oldMapX = ((p.x + viewportSizeX / 2)-drawOffsetX())/(zoom-1);
						int newMapX = (oldMapX * zoom)+drawOffsetX();
						p.x = newMapX - viewportSizeX/2;
					}

					//if the map will fit in the viewport, center it.
					if(getMap().hT()*zoom<viewportSizeY)
					{
						p.y = viewportSizeY - (viewportSizeY-getMap().hT()*zoom)/2;
					}
					else
					{
						//zoom into point on map in the center of viewport

						int oldMapY = ((p.y + viewportSizeY / 2)-drawOffsetY())/(zoom-1);
						int newMapY = (oldMapY * zoom)+drawOffsetY();
						p.y = newMapY - viewportSizeY/2;
					}



					//if it's scrolled past the map left
					if(p.x<viewportSizeX/2)p.x = viewportSizeX/2;

					//if it's scrolled past the map right
					if(p.x>viewportSizeX/2+getMap().wT()*zoom)p.x = viewportSizeX/2+getMap().wT()*zoom;

					//if it's scrolled past the map top
					if(p.y<viewportSizeY/2)p.y = viewportSizeY/2;

					//if it's scrolled past the map bottom
					if(p.y>viewportSizeY/2+getMap().hT()*zoom)p.y = viewportSizeY/2+getMap().hT()*zoom;




					EditorMain.mapScrollPane.getViewport().setViewPosition(p);
					repaint();

				}

				//E.mapScrollPane.setScrollPosition(p);
				//EditorMain.mapScrollPane.getViewport().setViewPosition(p);
				//E.mapScrollPane.getHorizontalScrollBar().setValue(p.x);
				//E.mapScrollPane.getVerticalScrollBar().setValue(p.y);

				//repaint();

				EditorMain.infoLabel.updateStats();

				//E.mapScrollPane.doLayout();

				//Dimension d=E.mapScrollPane.getViewportSize();
				//d.setSize(getMap().getWidth()*zoom+8,getMap().getHeight()*zoom+8);
				//setPreferredSize(d);

				//ScrollPaneAdjustable v=(ScrollPaneAdjustable)E.mapScrollPane.getVAdjustable();
				//v.setSpan(0,getMap().getHeight()*zoom+8,E.mapScrollPane.getViewportSize().width);
					/*E.mapScrollPane.getVAdjustable().setMinimum(0);
				E.mapScrollPane.getVAdjustable().setMaximum(getMap().getHeight()*zoom);
				E.mapScrollPane.getVAdjustable().setVisibleAmount(E.mapScrollPane.getViewportSize().width);

				E.mapScrollPane.getHAdjustable().setMinimum(0);
				E.mapScrollPane.getHAdjustable().setMaximum(getMap().getWidth()*zoom);
				E.mapScrollPane.getHAdjustable().setVisibleAmount(E.mapScrollPane.getViewportSize().height);*/
				//zoomInLock=false;
			}
		}


	}

	//===============================================================================================
	public void zoomOut()
	{//===============================================================================================

		if(zoom > 1)
		{
			//if(zoomOutLock==false)
			//{
			//zoomOutLock=true;

			zoom--;

			//setSizedoLayout();

			if(getMap() != null)
			{
				//reshape(0,0,getMap().getWidth()*zoom,getMap().getHeight()*zoom);
				Graphics G = getGraphics();
				G.translate(drawOffsetX(),drawOffsetY());
				//g.setClip(null);
				G.setColor(Color.DARK_GRAY);
				G.fillRect(0, 0, getMap().wT() * MAXZOOM, getMap().hT() * MAXZOOM);
				G.dispose();


				if(mapSelectionArea.isShowing)
				{
					if(selectedLayer==MapData.MAP_LIGHT_LAYER)
					{
						//p.x = ((((mapSelectionArea.x1/8) * zoom) + ((((mapSelectionArea.x2/8) * zoom) - ((mapSelectionArea.x1/8) * zoom)) / 2))) - (viewportSizeX / 2);
						//p.y = ((((mapSelectionArea.y1/8) * zoom) + ((((mapSelectionArea.y2/8) * zoom) - ((mapSelectionArea.y1/8) * zoom)) / 2))) - (viewportSizeY / 2);

						int pX = ((mapSelectionArea.x1) + (((mapSelectionArea.x2) - (mapSelectionArea.x1)) / 2));
						int pY = ((mapSelectionArea.y1) + (((mapSelectionArea.y2) - (mapSelectionArea.y1)) / 2));

						scrollToPixelXY(pX, pY);
					}
					else
					{
						//p.x = (((mapSelectionArea.x1 * zoom) + (((mapSelectionArea.x2 * zoom) - (mapSelectionArea.x1 * zoom)) / 2))) - (viewportSizeX / 2);
						//p.y = (((mapSelectionArea.y1 * zoom) + (((mapSelectionArea.y2 * zoom) - (mapSelectionArea.y1 * zoom)) / 2))) - (viewportSizeY / 2);

						int pX = ((mapSelectionArea.x1) + (((mapSelectionArea.x2) - (mapSelectionArea.x1)) / 2));
						int pY = ((mapSelectionArea.y1) + (((mapSelectionArea.y2) - (mapSelectionArea.y1)) / 2));

						scrollToTileXY(pX, pY);
					}
				}
				else if(mapSelectionArea.isShowingLock())
				{
					//p.x = (((mapSelectionArea.x1Lock * zoom) + (((mapSelectionArea.x2Lock * zoom) - (mapSelectionArea.x1Lock * zoom)) / 2))) - (viewportSizeX / 2);
					//p.y = (((mapSelectionArea.y1Lock * zoom) + (((mapSelectionArea.y2Lock * zoom) - (mapSelectionArea.y1Lock * zoom)) / 2))) - (viewportSizeY / 2);

					int pX = ((mapSelectionArea.x1Lock) + (((mapSelectionArea.x2Lock) - (mapSelectionArea.x1Lock)) / 2));
					int pY = ((mapSelectionArea.y1Lock) + (((mapSelectionArea.y2Lock) - (mapSelectionArea.y1Lock)) / 2));

					scrollToTileXY(pX, pY);
				}

				else
				if(selectedLayer==MapData.MAP_LIGHT_LAYER&& getMap().getSelectedLightIndex()!=-1)
				{
					scrollTo(getMap().getSelectedLight());
				}
				else
				if(selectedLayer==MapData.MAP_DOOR_LAYER&& getMap().getSelectedDoorIndex()!=-1)
				{
					scrollTo(getMap().getSelectedDoor());
				}
				else
				if(selectedLayer==MapData.MAP_AREA_LAYER&& getMap().getSelectedAreaIndex()!=-1)
				{
					scrollTo(getMap().getSelectedArea());
				}
				else
				if(selectedLayer==MapData.MAP_ENTITY_LAYER&& getMap().getSelectedEntityIndex()!=-1)
				{
					scrollTo(getMap().getSelectedEntity());
				}
				else
				{


					//p.x = ((getMap().getWidth()*zoom)/2) - (viewportSizeX/2);
					//p.y = ((getMap().getHeight()*zoom)/2) - (viewportSizeY/2);

					//p.x = (p.x/(zoom+1))*zoom;
					//p.y = (p.y/(zoom+1))*zoom;


					setSizedoLayout();



					//if the map will fit in the viewport, center it.
					int viewportSizeX = EditorMain.mapScrollPane.getViewport().getWidth();//E.mapScrollPane.getViewportSize().width
					int viewportSizeY = EditorMain.mapScrollPane.getViewport().getHeight();//E.mapScrollPane.getViewportSize().height

					Point p = EditorMain.mapScrollPane.getViewport().getViewPosition();

					//if the map will fit in the viewport, center it.
					if(getMap().wT()*zoom<viewportSizeX)
					{
						p.x = viewportSizeX - (viewportSizeX-getMap().wT()*zoom)/2;
					}
					else
					{
						//zoom into point on map in the center of viewport


						int oldMapX = ((p.x + viewportSizeX / 2)-drawOffsetX())/(zoom+1);
						int newMapX = (oldMapX * zoom)+drawOffsetX();
						p.x = newMapX - viewportSizeX/2;
					}

					//if the map will fit in the viewport, center it.
					if(getMap().hT()*zoom<viewportSizeY)
					{
						p.y = viewportSizeY - (viewportSizeY-getMap().hT()*zoom)/2;
					}
					else
					{
						//zoom into point on map in the center of viewport

						int oldMapY = ((p.y + viewportSizeY / 2)-drawOffsetY())/(zoom+1);
						int newMapY = (oldMapY * zoom)+drawOffsetY();
						p.y = newMapY - viewportSizeY/2;
					}



					//if it's scrolled past the map left
					if(p.x<viewportSizeX/2)p.x = viewportSizeX/2;

					//if it's scrolled past the map right
					if(p.x>viewportSizeX/2+getMap().wT()*zoom)p.x = viewportSizeX/2+getMap().wT()*zoom;

					//if it's scrolled past the map top
					if(p.y<viewportSizeY/2)p.y = viewportSizeY/2;

					//if it's scrolled past the map bottom
					if(p.y>viewportSizeY/2+getMap().hT()*zoom)p.y = viewportSizeY/2+getMap().hT()*zoom;





					EditorMain.mapScrollPane.getViewport().setViewPosition(p);
					repaint();

				}


				//E.mapScrollPane.getHorizontalScrollBar().setValue(p.x);
				//E.mapScrollPane.getVerticalScrollBar().setValue(p.y);

				EditorMain.infoLabel.updateStats();

				//E.mapScrollPane.doLayout();

				//Dimension d=E.mapScrollPane.getViewportSize();
				//d.setSize(getMap().getWidth()*zoom+8,getMap().getHeight()*zoom+8);
				//setPreferredSize(d);

				/*E.mapScrollPane.getVAdjustable().setMinimum(0);
				E.mapScrollPane.getVAdjustable().setMaximum(getMap().getHeight()*zoom);
				E.mapScrollPane.getVAdjustable().setVisibleAmount(E.mapScrollPane.getViewportSize().width);

				E.mapScrollPane.getHAdjustable().setMinimum(0);
				E.mapScrollPane.getHAdjustable().setMaximum(getMap().getWidth()*zoom);
				E.mapScrollPane.getHAdjustable().setVisibleAmount(E.mapScrollPane.getViewportSize().height);*/
				//zoomOutLock=false;

			}
		}



	}





	//===============================================================================================
	public void paint(Graphics g)
	{//===============================================================================================

		//super.paint(g);


		g.translate(drawOffsetX(),drawOffsetY());

		Point p = EditorMain.mapScrollPane.getViewport().getViewPosition();



		int viewportSizeX = EditorMain.mapScrollPane.getViewport().getWidth();//E.mapScrollPane.getViewportSize().width
		int viewportSizeY = EditorMain.mapScrollPane.getViewport().getHeight();//E.mapScrollPane.getViewportSize().height

/*
		if(previewMode == 1)
		{

			//g.setClip((E.mapScrollPane.getViewportSize().width-32*MAXZOOM)/2,(E.mapScrollPane.getViewportSize().height-24*MAXZOOM)/2,(E.mapScrollPane.getViewportSize().width-32*MAXZOOM)/2+32*MAXZOOM,(E.mapScrollPane.getViewportSize().height-24*MAXZOOM)/2+24*MAXZOOM);
			g.setClip(0, 0, viewportSizeX, viewportSizeY);

			g.drawImage(mapCanvasImage, (viewportSizeX - (32 * (MAXZOOM / 2))) / 2, 0 + 8, (viewportSizeX - (32 * (MAXZOOM / 2))) / 2 + (32 * (MAXZOOM / 2)), 0 + 8 + (24 * (MAXZOOM / 2)), previewX, previewY, previewX + 32 * 8, previewY + 24 * 8, this);
			g.drawImage(mapCanvasImage, (viewportSizeX - (32 * (MAXZOOM / 2))) / 2, (24 * (MAXZOOM / 2)) + 8 + 8, (viewportSizeX - (32 * (MAXZOOM / 2))) / 2 + (32 * (MAXZOOM / 2)), (24 * (MAXZOOM / 2)) + 8 + 8 + (24 * (MAXZOOM / 2)), previewX - (16 * 8), previewY - (12 * 8), previewX + (32 * 8) + (16 * 8), previewY + (24 * 8) + (12 * 8), this);

			//g.drawImage(mapBufferImage,(E.mapScrollPane.getViewportSize().width-32*MAXZOOM)/2,(E.mapScrollPane.getViewportSize().height-24*MAXZOOM)/2,(E.mapScrollPane.getViewportSize().width-32*MAXZOOM)/2+32*MAXZOOM,(E.mapScrollPane.getViewportSize().height-24*MAXZOOM)/2+24*MAXZOOM,previewX,previewY,previewX+32*8,previewY+24*8,this);

		}
		else
		*/
		{


			//draw map canvas buffer
			if(mapCanvasImage != null)
			{
				//g.setClip(p.x, p.y, viewportSizeX, viewportSizeY);
				g.drawImage(mapCanvasImage, 0, 0, getMap().wT() * zoom, getMap().hT() * zoom, 0, 0, getMap().wT() * 8, getMap().hT() * 8, this);
			}
			else
			{
				g.setColor(Color.WHITE);
				g.drawString("No Map Loaded", 50, 50);
			}

			if(mapCanvasImage==null)return;

			if(showMapGrid)
			{
				g.setColor(Color.GRAY);
				for(int y = 0; y < (getMap().hT() * zoom); y += zoom)
				{
					g.drawLine(0, y, (getMap().wT() * zoom)-1, y);
				}
				for(int x = 0; x < (getMap().wT() * zoom); x += zoom)
				{
					g.drawLine(x, 0, x, (getMap().hT() * zoom)-1);
				}
			}

			if(selectedAllLayers || (EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_DOOR_LAYER].isSelected()&&selectedLayer==MapData.MAP_DOOR_LAYER))
			getMap().drawDoorLayerSelection(g);


			//draw selected mapsprite box here
			if(selectedAllLayers || (EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_ENTITY_LAYER].isSelected()&&selectedLayer==MapData.MAP_ENTITY_LAYER))
			getMap().drawSpriteLayerSelection(g);



			//draw maplight selection box here
			if((EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_LIGHT_LAYER].isSelected()&&selectedLayer==MapData.MAP_LIGHT_LAYER))
			getMap().drawLightsLayerSelection(g);

			//draw radius boxes around all lights if on lights mask layer
			if((EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_LIGHT_LAYER].isSelected()&&selectedLayer==MapData.MAP_LIGHT_MASK_LAYER))
			getMap().drawAllLightRadiusBoxes(g);

			//could draw lights layer here instead of drawing it as a layer,
			//there isn't much reason it has its own buffer layer and all that
			//except for screenshots maybe, could save memory

			//TODO: dont really need to allocate lights and action layer buffers, save memory


			//draw actions here and selected action
			if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_AREA_LAYER].isSelected())
			{
				if(alwaysShowAreaOutlines)getMap().drawAllAreaOutlines(g);

				if(selectedAllLayers)getMap().drawAllAreaConnections(g);

				if(selectedAllLayers || (selectedLayer==MapData.MAP_AREA_LAYER))getMap().drawAreaLayerSelection(g);
			}



			//draw selection box
			if(mapSelectionArea.isShowing)
			{

				if(selectedLayer==MapData.MAP_LIGHT_LAYER)
				{

					g.setColor(new Color(200,0,255,91));
					g.fillRect((int)(mapSelectionArea.x1 * (zoom/8.0f)), (int)(mapSelectionArea.y1 * (zoom/8.0f)), (int)((mapSelectionArea.x2 - mapSelectionArea.x1) * (zoom/8.0f)), (int)((mapSelectionArea.y2 - mapSelectionArea.y1) * (zoom/8.0f)));
					g.setColor(new Color(200,0,255));
					g.drawRect((int)(mapSelectionArea.x1 * (zoom/8.0f)), (int)(mapSelectionArea.y1 * (zoom/8.0f)), (int)((mapSelectionArea.x2 - mapSelectionArea.x1) * (zoom/8.0f)) - 1, (int)((mapSelectionArea.y2 - mapSelectionArea.y1) * (zoom/8.0f)) - 1);

				}
				else
				{
					g.setColor(mapSelectionArea.color);
					g.fillRect(mapSelectionArea.x1 * zoom, mapSelectionArea.y1 * zoom, (mapSelectionArea.x2 - mapSelectionArea.x1) * zoom, (mapSelectionArea.y2 - mapSelectionArea.y1) * zoom);
					g.setColor(Color.RED);
					g.drawRect(mapSelectionArea.x1 * zoom, mapSelectionArea.y1 * zoom, (mapSelectionArea.x2 - mapSelectionArea.x1) * zoom - 1, (mapSelectionArea.y2 - mapSelectionArea.y1) * zoom - 1);
				}

			}
			if(mapSelectionArea.isShowingLock())
			{
				g.setColor(Color.GREEN);
				g.drawRect(mapSelectionArea.x1Lock * zoom, mapSelectionArea.y1Lock * zoom, (mapSelectionArea.x2Lock - mapSelectionArea.x1Lock) * zoom - 1, (mapSelectionArea.y2Lock - mapSelectionArea.y1Lock) * zoom - 1);
			}
		}
		//g.dispose();

	}


	//===============================================================================================
	public void repaint()
	{//===============================================================================================

		Graphics G = getGraphics();
		if(G!=null)
		{

			paint(G);
		}
	}


	//===============================================================================================
	public void paintTileXY(int l, int mx, int my)
	{//===============================================================================================
		if(E.project_loaded)
		{

			if(mx<0||mx>=getMap().wT()||my<0||my>=getMap().hT())return;


			if(useLayerImageBuffer)
			{
				getMap().repaintTileXYInLayerImage(l, mx, my);

				//here we can either redraw all the layers into mapcanvasimage to update it, or we can just draw tile straight to mapcanvas same as unbuffered

				//basically the benefit of having a buffer is mostly for turning layers on and off, or whenever i have to redraw the full stack and the layers havent changed
			}


			//need to draw the tile from the bottom layer to the top so transparencies and masks draw properly
			repaintTileXYAllLayersOnMapCanvasImage(mx, my);
		}

		//repaint();//this should be done externally after calling paintTileXY because we don't need to do it every time in some cases.

	}

	//===============================================================================================
	public void repaintTileXYAllLayersOnMapCanvasImage(int mx, int my)
	{//===============================================================================================
		if(getMap() != null)
		{

			//if(mapCanvasImage==null)mapCanvasImage = new BufferedImage(getMap().getWidth() * 8, getMap().getHeight() * 8, BufferedImage.TYPE_INT_ARGB);

			//could optimise this by starting from the top layer, and finding any tiles that are opaque and contain no clear color, then start drawing from there.
			//this isn't much of an optimisation though because it has to parse each tile anyway which isn't much faster than just drawing them.

			int xx = mx * 8;
			int yy = my * 8;
			Graphics g = mapCanvasImage.getGraphics();
			g.setColor(Project.getSelectedPalette().getColor(0));
			g.fillRect(xx, yy, 8, 8);


			if(EditorMain.controlPanel.showLayerCheckbox[0].isSelected())g.drawImage(Project.tileset.getTileImage(getMap().getTileIndex(0, mx, my)), xx, yy, this);
			if(EditorMain.controlPanel.showLayerCheckbox[1].isSelected())g.drawImage(Project.tileset.getTileImage(getMap().getTileIndex(1, mx, my)), xx, yy, this);
			if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_SHADER_LAYER].isSelected())g.drawImage((Image) Project.tileset.getTileImageTranslucent(getMap().getTileIndex(MapData.MAP_SHADER_LAYER, mx, my)), xx, yy, this);
			if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_GROUND_SHADOW_LAYER].isSelected())g.drawImage((Image) Project.tileset.getTileImageTranslucent(getMap().getTileIndex(MapData.MAP_GROUND_SHADOW_LAYER, mx, my)), xx, yy, this);
			if(EditorMain.controlPanel.showLayerCheckbox[4].isSelected())g.drawImage(Project.tileset.getTileImage(getMap().getTileIndex(4, mx, my)), xx, yy, this);
			if(EditorMain.controlPanel.showLayerCheckbox[5].isSelected())g.drawImage(Project.tileset.getTileImage(getMap().getTileIndex(5, mx, my)), xx, yy, this);
			if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_OBJECT_SHADOW_LAYER].isSelected())g.drawImage((Image) Project.tileset.getTileImageTranslucent(getMap().getTileIndex(MapData.MAP_OBJECT_SHADOW_LAYER, mx, my)), xx, yy, this);



			if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_DOOR_LAYER].isSelected())
			{
				getMap().drawDoorLayerAtTileXY(g, xx, yy);
			}


			//redraw sprite layer
			//get full sprite layer image, only draw 8x8 area from image
			if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_ENTITY_LAYER].isSelected())getMap().drawSpriteLayerAtTileXY(g, xx, yy, false);


			if(EditorMain.controlPanel.showLayerCheckbox[7].isSelected())g.drawImage(Project.tileset.getTileImage(getMap().getTileIndex(7, mx, my)), xx, yy, this);
			if(EditorMain.controlPanel.showLayerCheckbox[8].isSelected())g.drawImage(Project.tileset.getTileImage(getMap().getTileIndex(8, mx, my)), xx, yy, this);


			if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_ENTITY_LAYER].isSelected())getMap().drawSpriteLayerAtTileXY(g, xx, yy, true);



			if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_SPRITE_SHADOW_LAYER].isSelected())g.drawImage((Image) Project.tileset.getTileImageTranslucent(getMap().getTileIndex(MapData.MAP_SPRITE_SHADOW_LAYER, mx, my)), xx, yy, this);

			if(nightTimePreview==true)
			{
				for(int x=0;x<8;x++)
				for(int y=0;y<8;y++)
				{
					Color c = new Color(mapCanvasImage.getRGB(xx+x,yy+y));
					float hsb[] = new float[3];
					hsb = Color.RGBtoHSB(c.getRed(), c.getGreen(), c.getBlue(), hsb);
					Color newColor = new Color(Color.HSBtoRGB(hsb[0],hsb[1],hsb[2]*0.5f));
					mapCanvasImage.setRGB(xx+x,yy+y,newColor.getRGB());
				}
			}

			if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_LIGHT_MASK_LAYER].isSelected()  && getMap().getTileIndex(MapData.MAP_LIGHT_MASK_LAYER, mx, my) != 0)
			{
				g.drawImage((Image) Project.tileset.getTileImageLightMask(getMap().getTileIndex(MapData.MAP_LIGHT_MASK_LAYER, mx, my)), xx, yy, this);
			}

			//if light mask layer is enabled, only draw light layer over mask areas, otherwise draw full light layer
			//should probably keep a buffer of the light layer, and then subtract the mask from it.
			//redraw lights layer
			//get full light layer image, only draw 8x8 area from image
			if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_LIGHT_LAYER].isSelected())
			{
					getMap().drawLightsLayerAtTileXY(g, mx, my, null, null);
			}

			if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_CAMERA_BOUNDS_LAYER].isSelected())g.drawImage((Image) Project.tileset.getTileImageTranslucent(getMap().getTileIndex(MapData.MAP_CAMERA_BOUNDS_LAYER, mx, my)), xx, yy, this);

			if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_HIT_LAYER].isSelected() && getMap().getTileIndex(MapData.MAP_HIT_LAYER, mx, my) != 0)
			{
				g.drawImage((Image) Project.tileset.hitTile, xx, yy, this);
				//g.setColor(TRANSPARENT_RED);
				//g.drawLine(xx, yy, xx + 7, yy + 7);
				//g.drawLine(xx + 7, yy, xx, yy + 7);
			}

			//redraw action layer
			if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_AREA_LAYER].isSelected())
			{
				//action layer is drawn with mapcanvas repaint

			}


			g.dispose();
		}
	}

	//===============================================================================================
	public void drawBufferedLayerImagesIntoMapCanvasImage()
	{//===============================================================================================


		if(
				mapCanvasImage!=null&&
				(mapCanvasImage.getWidth()!=getMap().wT()*8||mapCanvasImage.getHeight()!=getMap().hT()*8)
		)
		{
			//EditorMain.infoLabel.setText("MapCanvas: Flushed mapCanvasImage");
			//mapCanvasImage.flush();
			mapCanvasImage=null;
			//System.runFinalization();
			//System.gc();
		}

		if(mapCanvasImage==null)mapCanvasImage = new BufferedImage(getMap().wT() * 8, getMap().hT() * 8, BufferedImage.TYPE_INT_ARGB);

		Graphics g = mapCanvasImage.getGraphics();
		g.setColor(Project.getSelectedPalette().getColor(0));
		g.fillRect(0, 0, getMap().wT() * 8, getMap().hT() * 8);

		//only redraw layer images if they aren't allocated
		if(getMap().layerImagesAllocated==false)getMap().updateAllLayerBufferImages();


		//make sure layer images get updated when they need to be.
		//don't want to refill them often.
		//should just update single layers as they change!!!

		if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_GROUND_LAYER].isSelected())g.drawImage(getMap().layerImage[MapData.MAP_GROUND_LAYER], 0, 0, this);
		if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_GROUND_DETAIL_LAYER].isSelected())g.drawImage(getMap().layerImage[MapData.MAP_GROUND_DETAIL_LAYER], 0, 0, this);
		if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_SHADER_LAYER].isSelected())g.drawImage(getMap().layerImage[MapData.MAP_SHADER_LAYER], 0, 0, this);
		if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_GROUND_SHADOW_LAYER].isSelected())g.drawImage(getMap().layerImage[MapData.MAP_GROUND_SHADOW_LAYER],0, 0, this);
		if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_OBJECT_LAYER].isSelected())g.drawImage(getMap().layerImage[MapData.MAP_OBJECT_LAYER], 0, 0, this);
		if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_OBJECT_DETAIL_LAYER].isSelected())g.drawImage(getMap().layerImage[MapData.MAP_OBJECT_DETAIL_LAYER], 0, 0, this);
		if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_OBJECT_SHADOW_LAYER].isSelected())g.drawImage(getMap().layerImage[MapData.MAP_OBJECT_SHADOW_LAYER], 0, 0, this);
		if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_DOOR_LAYER].isSelected())g.drawImage(getMap().layerImage[MapData.MAP_DOOR_LAYER], 0, 0, this);
		if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_ENTITY_LAYER].isSelected())g.drawImage(getMap().layerImage[MapData.MAP_ENTITY_LAYER], 0, 0, this);
		if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_ABOVE_LAYER].isSelected())g.drawImage(getMap().layerImage[MapData.MAP_ABOVE_LAYER], 0, 0, this);
		if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_ABOVE_DETAIL_LAYER].isSelected())g.drawImage(getMap().layerImage[MapData.MAP_ABOVE_DETAIL_LAYER], 0, 0, this);
		if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_SPRITE_SHADOW_LAYER].isSelected())g.drawImage(getMap().layerImage[MapData.MAP_SPRITE_SHADOW_LAYER], 0, 0, this);

		//TODO: mapsprites with aboveTopLayer won't be drawn here, since they would need their own layer

		if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_LIGHT_MASK_LAYER].isSelected())g.drawImage(getMap().layerImage[MapData.MAP_LIGHT_MASK_LAYER],0, 0, this);
		if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_LIGHT_LAYER].isSelected())g.drawImage(getMap().layerImage[MapData.MAP_LIGHT_LAYER], 0, 0, this);
		if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_CAMERA_BOUNDS_LAYER].isSelected())g.drawImage(getMap().layerImage[MapData.MAP_CAMERA_BOUNDS_LAYER], 0, 0, this);
		if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_HIT_LAYER].isSelected())g.drawImage(getMap().layerImage[MapData.MAP_HIT_LAYER], 0, 0, this);

		//if(E.controlPanel.showLayerCheckbox[MapData.ACTION_LAYER].isSelected())g.drawImage(getMap().createTempLayerImage(MapData.ACTION_LAYER), 0, 0, this);




		g.dispose();

	}

	//===============================================================================================
	public void updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas()
	{//===============================================================================================
		if(getMap() != null && E.project_loaded)
		{

			if(useLayerImageBuffer==false)
			{
				if(
						mapCanvasImage!=null&&
						(mapCanvasImage.getWidth()!=getMap().wT()*8||mapCanvasImage.getHeight()!=getMap().hT()*8)
				)
				{
					//EditorMain.infoLabel.setText("MapCanvas: Flushed mapCanvasImage");
					//mapCanvasImage.flush();
					mapCanvasImage=null;
					//System.runFinalization();
					//System.gc();
				}

				if(mapCanvasImage==null)mapCanvasImage = new BufferedImage(getMap().wT() * 8, getMap().hT() * 8, BufferedImage.TYPE_INT_ARGB);

				Graphics g = mapCanvasImage.getGraphics();
				g.setColor(Project.getSelectedPalette().getColor(0));
				g.fillRect(0, 0, getMap().wT() * 8, getMap().hT() * 8);


				if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_GROUND_LAYER].isSelected())g.drawImage(getMap().createTempLayerImage(MapData.MAP_GROUND_LAYER), 0, 0,this);
				if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_GROUND_DETAIL_LAYER].isSelected())g.drawImage(getMap().createTempLayerImage(MapData.MAP_GROUND_DETAIL_LAYER), 0, 0,this);
				if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_SHADER_LAYER].isSelected())g.drawImage(getMap().createTempLayerImage(MapData.MAP_SHADER_LAYER), 0, 0,this);
				if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_GROUND_SHADOW_LAYER].isSelected())g.drawImage(getMap().createTempLayerImage(MapData.MAP_GROUND_SHADOW_LAYER), 0, 0,this);
				if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_OBJECT_LAYER].isSelected())g.drawImage(getMap().createTempLayerImage(MapData.MAP_OBJECT_LAYER), 0, 0,this);
				if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_OBJECT_DETAIL_LAYER].isSelected())g.drawImage(getMap().createTempLayerImage(MapData.MAP_OBJECT_DETAIL_LAYER), 0, 0,this);
				if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_OBJECT_SHADOW_LAYER].isSelected())g.drawImage(getMap().createTempLayerImage(MapData.MAP_OBJECT_SHADOW_LAYER), 0, 0,this);
				if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_DOOR_LAYER].isSelected())g.drawImage(getMap().createTempLayerImage(MapData.MAP_DOOR_LAYER), 0, 0,this);
				if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_ENTITY_LAYER].isSelected())g.drawImage(getMap().createTempLayerImage(MapData.MAP_ENTITY_LAYER), 0, 0,this);
				if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_ABOVE_LAYER].isSelected())g.drawImage(getMap().createTempLayerImage(MapData.MAP_ABOVE_LAYER), 0, 0,this);
				if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_ABOVE_DETAIL_LAYER].isSelected())g.drawImage(getMap().createTempLayerImage(MapData.MAP_ABOVE_DETAIL_LAYER), 0, 0,this);
				if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_ENTITY_LAYER].isSelected())g.drawImage(getMap().createTempLayerImage(MapData.MAP_ENTITY_LAYER_ABOVE), 0, 0,this);
				if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_SPRITE_SHADOW_LAYER].isSelected())g.drawImage(getMap().createTempLayerImage(MapData.MAP_SPRITE_SHADOW_LAYER), 0, 0,this);

				if(nightTimePreview==true)
				{
					for(int x=0;x<mapCanvasImage.getWidth();x++)
					for(int y=0;y<mapCanvasImage.getHeight();y++)
					{
						Color c = new Color(mapCanvasImage.getRGB(x,y));
						float hsb[] = new float[3];
						hsb = Color.RGBtoHSB(c.getRed(), c.getGreen(), c.getBlue(), hsb);
						Color newColor = new Color(Color.HSBtoRGB(hsb[0],hsb[1],hsb[2]*0.5f));
						mapCanvasImage.setRGB(x,y,newColor.getRGB());
					}
				}

				if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_LIGHT_MASK_LAYER].isSelected())g.drawImage(getMap().createTempLayerImage(MapData.MAP_LIGHT_MASK_LAYER), 0, 0,this);
				if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_LIGHT_LAYER].isSelected())g.drawImage(getMap().createTempLayerImage(MapData.MAP_LIGHT_LAYER), 0, 0,this);
				if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_CAMERA_BOUNDS_LAYER].isSelected())g.drawImage(getMap().createTempLayerImage(MapData.MAP_CAMERA_BOUNDS_LAYER), 0, 0,this);
				if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_HIT_LAYER].isSelected())g.drawImage(getMap().createTempLayerImage(MapData.MAP_HIT_LAYER), 0, 0,this);



				g.dispose();
			}
			else
			if(useLayerImageBuffer==true)
			{
				//this is also VERY SLOW
				getMap().updateAllLayerBufferImages();
				drawBufferedLayerImagesIntoMapCanvasImage();
			}


			if(getMap().wT() > 500 || getMap().hT() > 500)EditorMain.infoLabel.setTextSuccess("MapCanvas: Finished Drawing Large Map");
			else EditorMain.infoLabel.setTextNoConsole("MapCanvas: Finished Drawing Map");

			repaint();
		}
	}



	//===============================================================================================
	public void repaintTileEverywhereOnMap(int tile)
	{//===============================================================================================
		for(int y = 0; y < getMap().hT(); y++)
		{
			for(int x = 0; x < getMap().wT(); x++)
			{

				if(useLayerImageBuffer)
				{
					//we have to update each layer separately
					for(int l=0;l<MapData.layers;l++)
					{
						if(
								l!=MapData.MAP_HIT_LAYER&&
								MapData.isTileLayer(l)
						)
						{
							if(getMap().getTileIndex(l, x, y) == tile)
							{

								paintTileXY(l, x, y);
							}
						}
					}
				}
				else
				{
					//if not using the buffer, we only need to do this once because it will update all layers anyway
					paintTileXY(0, x, y);
				}

			}
		}
		repaint();
	}

	public void applyAutoTile(int layer, int x, int y) {
		int baseIndex = EditorMain.tileCanvas.tileSelected;

		// 1. Set current tile to base (so it counts as "Same Set")
		getMap().setTileIndex(layer, x, y, baseIndex);

		// 2. Update current tile and neighbors
		updateAutoTileAt(layer, x, y, baseIndex);
		updateAutoTileAt(layer, x, y-1, baseIndex); // N
		updateAutoTileAt(layer, x+1, y, baseIndex); // E
		updateAutoTileAt(layer, x, y+1, baseIndex); // S
		updateAutoTileAt(layer, x-1, y, baseIndex); // W

		repaint();
	}

	private void updateAutoTileAt(int layer, int x, int y, int baseIndex) {
		if (x < 0 || x >= getMap().wT() || y < 0 || y >= getMap().hT()) return;

		// Only update if it's part of the set
		int current = getMap().getTileIndex(layer, x, y);
		if (current >= baseIndex && current <= baseIndex + 15) {
			int newIndex = com.bobsgame.editor.Project.AutoTiler.getAutoTileIndex(getMap(), layer, x, y, baseIndex);
			if (current != newIndex) {
				getMap().setTileIndex(layer, x, y, newIndex);
				paintTileXY(layer, x, y);
			}
		}
	}



	//===============================================================================================
	public void recursiveFill(int l, int sx, int sy, int tile, int prevtile)
	{
		CompoundEdit edit = new CompoundEdit();
		recursiveFill(l, sx, sy, tile, prevtile, edit);
		edit.end();
		undoManager.addEdit(edit);
	}

	public void recursiveFill(int l, int sx, int sy, int tile, int prevtile, CompoundEdit edit)
	{//===============================================================================================

		if(MapData.isTileLayer(l)==false)return;


		int oldTile = getMap().getTileIndex(l, sx, sy);
		if(oldTile != tile) {
			edit.addEdit(new TileChangeEdit(this, l, sx, sy, oldTile, tile));
			getMap().setTileIndex(l, sx, sy, tile);
		}

		//paintTileXY(l, sx, sy);//we don't need to do this because the whole map gets redrawn afterwards.

		if(sx > 0 && getMap().getTileIndex(l, sx - 1, sy) != tile && getMap().getTileIndex(l, sx - 1, sy) == prevtile)
		{
			recursiveFill(l, sx - 1, sy, tile, prevtile, edit);
		}

		if(sx < getMap().wT() - 1 && getMap().getTileIndex(l, sx + 1, sy) != tile && getMap().getTileIndex(l, sx + 1, sy) == prevtile)
		{
			recursiveFill(l, sx + 1, sy, tile, prevtile, edit);
		}

		if(sy > 0 && getMap().getTileIndex(l, sx, sy - 1) != tile && getMap().getTileIndex(l, sx, sy - 1) == prevtile)
		{
			recursiveFill(l, sx, sy - 1, tile, prevtile, edit);
		}

		if(sy < getMap().hT() - 1 && getMap().getTileIndex(l, sx, sy + 1) != tile && getMap().getTileIndex(l, sx, sy + 1) == prevtile)
		{
			recursiveFill(l, sx, sy + 1, tile, prevtile, edit);
		}

	}

	//===============================================================================================
	public void fillSelectionWithSelectedTile()
	{//===============================================================================================


		if(MapData.isTileLayer(selectedLayer)==false)return;

		CompoundEdit edit = new CompoundEdit();

		if(mapSelectionArea.isShowing)//this is mapcanvas mapSelectionArea
		{
			for(int yy = mapSelectionArea.y1; yy < mapSelectionArea.y2; yy++)
			{
				for(int xx = mapSelectionArea.x1; xx < mapSelectionArea.x2; xx++)
				{
					int oldTile = getMap().getTileIndex(selectedLayer, xx, yy);
					int newTile;

					//if there is a mapSelectionArea on the tile canvas, then fill with that
					if(EditorMain.tileCanvas.tileSelectionArea.isShowing)
					{
						int tilesetSelectionW = (EditorMain.tileCanvas.tileSelectionArea.x2 - EditorMain.tileCanvas.tileSelectionArea.x1) / TileCanvas.TILE_SIZE;
						int tilesetSelectionH = (EditorMain.tileCanvas.tileSelectionArea.y2 - EditorMain.tileCanvas.tileSelectionArea.y1) / TileCanvas.TILE_SIZE;
						
						// Avoid division by zero if selection is weird
						if(tilesetSelectionW < 1) tilesetSelectionW = 1;
						if(tilesetSelectionH < 1) tilesetSelectionH = 1;

						int offsetX = (xx - mapSelectionArea.x1) % tilesetSelectionW;
						int offsetY = (yy - mapSelectionArea.y1) % tilesetSelectionH;
						
						int tileX = (EditorMain.tileCanvas.tileSelectionArea.x1 / TileCanvas.TILE_SIZE) + offsetX;
						int tileY = (EditorMain.tileCanvas.tileSelectionArea.y1 / TileCanvas.TILE_SIZE) + offsetY;
						
						newTile = tileY * TileCanvas.WIDTH_TILES + tileX;
					}
					else
					{
					//otherwise just fill with the single tile
						newTile = EditorMain.tileCanvas.tileSelected;
					}

					if(oldTile != newTile) {
						edit.addEdit(new TileChangeEdit(this, selectedLayer, xx, yy, oldTile, newTile));
						getMap().setTileIndex(selectedLayer, xx, yy, newTile);
						paintTileXY(selectedLayer, xx, yy);
					}
				}
			}
		}

		edit.end();
		if(edit.isSignificant()) undoManager.addEdit(edit);

		repaint();
	}






	//===============================================================================================
	public void mouseClicked(MouseEvent me)
	{//===============================================================================================

		me = new MouseEvent((Component) me.getSource(), me.getID(), me.getWhen(), me.getModifiersEx(), me.getX()-drawOffsetX(), me.getY()-drawOffsetY(), me.getXOnScreen(), me.getYOnScreen(), me.getClickCount(), me.isPopupTrigger(), me.getButton());

		int leftMask = InputEvent.BUTTON1_DOWN_MASK;
		int middleMask = InputEvent.BUTTON2_DOWN_MASK;
		int rightMask = InputEvent.BUTTON3_DOWN_MASK;
		int shiftClickMask = InputEvent.BUTTON1_DOWN_MASK | InputEvent.SHIFT_DOWN_MASK;
		//int ctrlClickMask = InputEvent.BUTTON1_DOWN_MASK | InputEvent.CTRL_DOWN_MASK;
		int ctrlRightClickMask = InputEvent.BUTTON3_DOWN_MASK | InputEvent.CTRL_DOWN_MASK;


		if(
				me.getY() <  +getMap().hT() * zoom &&
				me.getX() <  +getMap().wT() * zoom &&
				me.getX() >= 0 &&
				me.getY() >= 0
		)
		{
			clickedTileX = me.getX() / zoom;
			clickedTileY = me.getY() / zoom;
			clickedMapX = (int)(me.getX() / (zoom/8.0f));
			clickedMapY = (int)(me.getY() / (zoom/8.0f));

			if(
				EditorMain.controlPanel.showLayerCheckbox[selectedLayer].isSelected()
			)
			{

				if(selectedLayer == MapData.MAP_HIT_LAYER)
				{
					int val=0;

					if(me.getModifiersEx() == leftMask || me.getModifiersEx() == rightMask)
					{
						if(me.getModifiersEx() == leftMask)val = 1;
						if(me.getModifiersEx() == rightMask)val = 0;


						if(getMap().getTileIndex(MapData.MAP_HIT_LAYER, clickedTileX, clickedTileY) != val)
						{

							//if(mouseDragged==false)fillUndoArray();
							
							int oldVal = getMap().getTileIndex(MapData.MAP_HIT_LAYER, clickedTileX, clickedTileY);
							if(oldVal != val) {
								UndoableEdit edit = new TileChangeEdit(this, MapData.MAP_HIT_LAYER, clickedTileX, clickedTileY, oldVal, val);
								undoManager.addEdit(edit);
							}

							getMap().setTileIndex(MapData.MAP_HIT_LAYER, clickedTileX, clickedTileY, val);
							paintTileXY(MapData.MAP_HIT_LAYER, clickedTileX, clickedTileY);
							repaint();
							EditorMain.infoLabel.setTextNoConsole("MapCanvas: Hit Detection Layer (" + clickedTileX + "," + clickedTileY + ") set to: " + val);

						}
					}

					if(me.getModifiersEx() == middleMask)
					{
						deselectMapSelectionArea();
					}


				}
				else
				if(MapData.isTileLayer(selectedLayer)==false)
				{
					//handle door layer, sprite layer, action layer, lights layer

					if(selectedAllLayers)
					{
						if(me.getModifiersEx() == leftMask || me.getModifiersEx() == middleMask)
						{
							//go through all doors, actions, sprites

								getMap().setSelectedDoorIndex(-1);
								getMap().setSelectedEntityIndex(-1);
								getMap().setSelectedAreaIndex(-1);

								for(int n=0;n<getMap().getNumDoors();n++)
								{
									Door d = getMap().getDoor(n);
									if(
											clickedMapX>=d.xP()&&
											clickedMapX<=d.xP()+d.wP()&&
											clickedMapY>=d.yP()&&
											clickedMapY<=d.yP()+d.hP()
									)
									{
										deselectMapSelectionArea();

										getMap().setSelectedDoorIndex(n);
										EditorMain.controlPanel.setSelectedLayerIfEnabled(MapData.MAP_DOOR_LAYER);
										EditorMain.infoLabel.setTextNoConsole("MapCanvas: Selected Door \""+d.name()+"\"");

										if(me.getModifiersEx() == middleMask)doorWindow.showDoorWindow();
									}
								}

								for(int n=0;n<getMap().getNumEntities();n++)
								{
									Entity m = getMap().getEntity(n);
									if(
											clickedMapX>=m.xP()&&
											clickedMapX<=m.xP()+m.wP()&&
											clickedMapY>=m.yP()&&
											clickedMapY<=m.yP()+m.hP()
									)
									{
										deselectMapSelectionArea();

										getMap().setSelectedEntityIndex(n);
										EditorMain.controlPanel.setSelectedLayerIfEnabled(MapData.MAP_ENTITY_LAYER);
										EditorMain.infoLabel.setTextNoConsole("MapCanvas: Selected Map Sprite \""+m.name()+"\"");

										if(me.getModifiersEx() == middleMask)entityWindow.showEntityWindow();
									}
								}

								for(int n=0;n<getMap().getNumAreas();n++)
								{
									Area a = getMap().getArea(n);
									if(
											clickedMapX>=a.xP()&&
											clickedMapX<=a.xP()+a.wP()&&
											clickedMapY>=a.yP()&&
											clickedMapY<=a.yP()+a.hP()
									)
									{
										deselectMapSelectionArea();

										getMap().setSelectedAreaIndex(n);
										EditorMain.controlPanel.setSelectedLayerIfEnabled(MapData.MAP_AREA_LAYER);
										EditorMain.infoLabel.setTextNoConsole("MapCanvas: Selected Map Action");

										if(me.getModifiersEx() == middleMask)areaWindow.showAreaWindow();
									}
								}

								if(getMap().getSelectedDoorIndex()==-1&&getMap().getSelectedEntityIndex()==-1&&getMap().getSelectedAreaIndex()==-1)
								{
									deselectMapSelectionArea();

									EditorMain.infoLabel.setTextNoConsole("MapCanvas: Nothing Selected");
									repaint();
								}
						}

					}
					else
					if(selectedLayer==MapData.MAP_DOOR_LAYER)
					{
						//if left click or right click and sprite is under mouse, draw bounds box over sprite, select map sprite
						if(me.getModifiersEx() == leftMask || me.getModifiersEx() == rightMask || me.getModifiersEx() == middleMask)
						{

								//if sprite is under mouse, draw bounds box over sprite
								boolean clickedOnDoor = false;

								for(int n=0;n<getMap().getNumDoors();n++)
								{
									Door d = getMap().getDoor(n);
									if(
											clickedMapX>=d.xP()&&
											clickedMapX<=d.xP()+d.wP()&&
											clickedMapY>=d.yP()&&
											clickedMapY<=d.yP()+d.hP()
									)
									{

										deselectMapSelectionArea();

										clickedOnDoor=true;
										getMap().setSelectedDoorIndex(n);
										EditorMain.infoLabel.setTextNoConsole("MapCanvas: Selected Door \""+d.name()+"\"");

										if(me.getModifiersEx() == middleMask)
										{
											doorWindow.showDoorWindow();
										}
									}
								}

								if(clickedOnDoor==false)
								{
									deselectMapSelectionArea();

									getMap().setSelectedDoorIndex(-1);
									EditorMain.infoLabel.setTextNoConsole("MapCanvas: No Door Selected");


									//if right click on nothing, pop up right click menu
									if(me.getModifiersEx() == rightMask)
									{
										/*
										if(entityPopup.isVisible())
										{
											entityPopup.setVisible(false);
										}
										else
										{
											entityPopup.removeAll();
											int numDoorSprites=0;
											for(int n=0;n<E.project.getNumSprites();n++)
											{
												if(E.project.getSprite(n).name.startsWith("Door"))
												{
													spritePopupItem[numDoorSprites] = new JMenuItem(E.project.getSprite(n).name);
													spritePopupItem[numDoorSprites].addActionListener(this);
													spritePopupItem[numDoorSprites].setBorderPainted(false);
													spritePopupItem[numDoorSprites].setFont(new Font("Tahoma", Font.PLAIN, 10));
													entityPopup.add(spritePopupItem[numDoorSprites]);
													numDoorSprites++;
												}
											}

											if(numDoorSprites==0)
											{
												spritePopupItem[0] = new JMenuItem("No Sprites start with \"Door\"!");
												//spritePopupItem[0].addActionListener(this);
												spritePopupItem[0].setEnabled(false);

												spritePopupItem[0].setBorderPainted(false);
												spritePopupItem[0].setFont(new Font("Tahoma", Font.PLAIN, 10));
												entityPopup.add(spritePopupItem[0]);
											}
											entityPopup.show(this,me.getX(),me.getY());

											//if(entityPopup.getHeight()>1200)entityPopup.setPopupSize(entityPopup.getWidth(), 1200);
										}*/

										EditorMain.infoLabel.setTextNoConsole("MapCanvas: Created New Door");

										doorSelectionDialog = new SpriteSelectionDialog(E,"Select A Door Type",E,true);

										doorSelectionDialog.show("");

										if(doorSelectionDialog.spriteList.getSelectedValue()!=null)
										if(doorSelectionDialog.spriteList.getSelectedValue().equals("No Sprites start with \"Door\"!")==false)
										{
											//add new door at xy
											getMap().createDoor(doorSelectionDialog.spriteList.getSelectedValue(),clickedTileX*8,clickedTileY*8);
											undoManager.addEdit(new MapObjectAddEdit(getMap(), getMap().getSelectedDoor()));
											//entityPopup.setVisible(false);
											//buffered:
											//here i only need to refresh the map sprite layer buffer
											//then i need to redraw all the layers
											if(useLayerImageBuffer)
											{
												getMap().updateLayerBufferImage(MapData.MAP_DOOR_LAYER);
												drawBufferedLayerImagesIntoMapCanvasImage();

												repaint();
											}

											//unbuffered:
											//i need to redraw the mapcanvas, but only where the sprites are, really.
											//might be fastest to actually repaint tile xy where the sprites are, especially for huge maps.
											if(!useLayerImageBuffer)
											{
												int sx = getMap().getSelectedDoor().xP()/8;
												int sy = getMap().getSelectedDoor().yP()/8;
												int sw = getMap().getSelectedDoor().wP()/8;
												int sh = getMap().getSelectedDoor().hP()/8;

												for(int x=sx;x<sx+sw;x++)
												for(int y=sy;y<sy+sh;y++)
													paintTileXY(MapData.MAP_DOOR_LAYER,x,y);

												repaint();
											}
										}
									}

								}

							//we need to draw the door selection box which is done in repaint()
							repaint();
						}

					}
					else
					if(selectedLayer==MapData.MAP_ENTITY_LAYER)
					{
						//if left click or right click and sprite is under mouse, draw bounds box over sprite, select map sprite
						if(me.getModifiersEx() == leftMask || me.getModifiersEx() == rightMask || me.getModifiersEx() == middleMask)
						{

							boolean clickedOnSprite = false;

							for(int n=0;n<getMap().getNumEntities();n++)
							{
								Entity m = getMap().getEntity(n);
								if(
										clickedMapX>=m.xP()&&
										clickedMapX<=m.xP()+m.wP()&&
										clickedMapY>=m.yP()&&
										clickedMapY<=m.yP()+m.hP()
								)
								{
									deselectMapSelectionArea();

									clickedOnSprite = true;

									if(getMap().getSelectedEntityIndex()!=n)
									{
										getMap().setSelectedEntityIndex(n);
										EditorMain.infoLabel.setTextNoConsole("MapCanvas: Selected Entity \""+m.name()+"\"");
										break;
									}

									if(me.getModifiersEx() == middleMask)
									{
										entityWindow.showEntityWindow();
									}
								}
							}

							if(clickedOnSprite==false)
							{
								deselectMapSelectionArea();

								getMap().setSelectedEntityIndex(-1);
								EditorMain.infoLabel.setTextNoConsole("MapCanvas: No Entity Selected");

								//if right click on nothing, pop up right click menu
								if(me.getModifiersEx() == rightMask)
								{
									EditorMain.infoLabel.setTextNoConsole("MapCanvas: Created New Entity");

									spriteSelectionDialog = new SpriteSelectionDialog(E,"Select A Sprite",E,false);
									spriteSelectionDialog.show("");

									//add new sprite at xy
									if(spriteSelectionDialog.spriteList.getSelectedValue() != null) {
										getMap().createEntity(spriteSelectionDialog.spriteList.getSelectedValue(),clickedTileX*8,clickedTileY*8);
										undoManager.addEdit(new MapObjectAddEdit(getMap(), getMap().getSelectedEntity()));
									}


									//buffered:
									//here i only need to refresh the map sprite layer buffer
									//then i need to redraw all the layers
									if(useLayerImageBuffer)
									{
										getMap().updateLayerBufferImage(MapData.MAP_ENTITY_LAYER);
										drawBufferedLayerImagesIntoMapCanvasImage();

										repaint();
									}

									//unbuffered:
									//i need to redraw the mapcanvas, but only where the sprites are, really.
									//might be fastest to actually repaint tile xy where the sprites are, especially for huge maps.
									if(!useLayerImageBuffer)
									{
										if(getMap().getSelectedEntityIndex()!=-1)
										{
											Entity m = getMap().getSelectedEntity();

											int sx = m.xP()/8;
											int sy = m.yP()/8;
											int sw = ((int)(m.wP())/8)+1;
											int sh = ((int)(m.hP())/8)+1;


											for(int x=sx;x<sx+sw;x++)
											for(int y=sy;y<sy+sh;y++)
												paintTileXY(MapData.MAP_ENTITY_LAYER,x,y);
										}

										repaint();
									}
								}
							}

							//we need to draw the sprite selection box which is done in repaint()
							repaint();

						}
					}
					else
					if(selectedLayer==MapData.MAP_LIGHT_LAYER)
					{
						//if light is under mouse, draw bounds box over light
						if(me.getModifiersEx() == leftMask || me.getModifiersEx() == middleMask)
						{


							boolean clickedOnLight = false;

							for(int n=0;n<getMap().getNumLights();n++)
							{
								Light l = getMap().getLight(n);
								if(
										clickedMapX>=l.xP()&&
										clickedMapX<=l.xP()+l.wP()&&
										clickedMapY>=l.yP()&&
										clickedMapY<=l.yP()+l.hP()

								)
								{
									deselectMapSelectionArea();

									clickedOnLight = true;

									getMap().setSelectedLightIndex(n);
									EditorMain.infoLabel.setTextNoConsole("MapCanvas: Selected Map Light "+l.name());

									if(me.getModifiersEx() == middleMask)
									{
										lightWindow.showLightWindow();
									}
								}
							}

							if(clickedOnLight==false)
							{


								getMap().setSelectedLightIndex(-1);


								if(
										mapSelectionArea.isShowing&&
										mapSelectionArea.contains(clickedMapX, clickedMapY)&&
										me.getModifiersEx() == middleMask
								)
								{

									deselectMapSelectionArea();

									//add new lights
									EditorMain.infoLabel.setTextNoConsole("MapCanvas: Created New Light");
									//******* NOTICE this is using pixel precision here for the mapselectionarea!
									lightWindow.showLightWindow(mapSelectionArea.x1, mapSelectionArea.y1, mapSelectionArea.getWidth(),mapSelectionArea.getHeight());
									
									// Check if a light was actually created (selected index changed)
									if(getMap().getSelectedLightIndex() != -1) {
										undoManager.addEdit(new MapObjectAddEdit(getMap(), getMap().getSelectedLight()));
									}
								}
								else
								{

									deselectMapSelectionArea();
									EditorMain.infoLabel.setTextNoConsole("MapCanvas: No Map Light Selected");
								}



							}


							//we need to draw the light selection box which is done in repaint()
							repaint();
						}
					}

					else
					if(selectedLayer==MapData.MAP_AREA_LAYER)
					{

						//if light is under mouse, draw bounds box over light
						if(me.getModifiersEx() == leftMask || me.getModifiersEx() == middleMask)
						{

							boolean clickedOnArea = false;



							for(int n=0;n<getMap().getNumAreas();n++)
							{
								Area a = getMap().getArea(n);
								int w=a.wP();
								int h=a.hP();

								if(
										clickedMapX>=a.xP()&&
										clickedMapX<=a.xP()+w&&
										clickedMapY>=a.yP()&&
										clickedMapY<=a.yP()+h

								)
								{
									deselectMapSelectionArea();

									clickedOnArea = true;

									getMap().setSelectedAreaIndex(n);
									EditorMain.infoLabel.setTextNoConsole("MapCanvas: Selected Map Action " + a.name());

									if(me.getModifiersEx() == middleMask)
									{
										areaWindow.showAreaWindow();
									}
								}
							}

							if(clickedOnArea==false)
							{



								getMap().setSelectedAreaIndex(-1);


								if(
										mapSelectionArea.isShowing&&
										mapSelectionArea.contains(clickedTileX, clickedTileY)&&
										me.getModifiersEx() == middleMask
								)
								{

									deselectMapSelectionArea();

									EditorMain.infoLabel.setTextNoConsole("MapCanvas: Created New Action");

									//add new action
									areaWindow.showAreaWindow(mapSelectionArea.x1*8, mapSelectionArea.y1*8, mapSelectionArea.getWidth()*8,mapSelectionArea.getHeight()*8);
									
									// Check if an area was actually created
									if(getMap().getSelectedAreaIndex() != -1) {
										undoManager.addEdit(new MapObjectAddEdit(getMap(), getMap().getSelectedArea()));
									}

								}
								else
								{

									deselectMapSelectionArea();
									EditorMain.infoLabel.setTextNoConsole("MapCanvas: No Map Action Selected");
								}

							}

							//we need to show the action selection box which is done in repaint()
							repaint();

						}



					}

				}
				else
				{
					//---------------------------------
					//we are on a tile layer
					//---------------------------------

					if(me.getModifiersEx() == leftMask)
					{
						if (tileEditMode) {
							int px = clickedMapX;
							int py = clickedMapY;
							int tileX = px / 8;
							int tileY = py / 8;
							int pixelX = px % 8;
							int pixelY = py % 8;

							int tileIndex = getMap().getTileIndex(selectedLayer, tileX, tileY);
							if (tileIndex != 0) {
								int color = EditorMain.controlPanel.paletteCanvas.colorSelected;
								Project.tileset.setPixel(tileIndex, pixelX, pixelY, color);
								repaintTileEverywhereOnMap(tileIndex);
								EditorMain.tileCanvas.repaint();
							}
						}
						else if (autoTileMode) {
							applyAutoTile(selectedLayer, clickedTileX, clickedTileY);
						}
						else if(getMap().getTileIndex(selectedLayer, clickedTileX, clickedTileY) != EditorMain.tileCanvas.tileSelected)
						{
							prevtile = getMap().getTileIndex(selectedLayer, clickedTileX, clickedTileY);

							//if(mouseDragged==false)fillUndoArray();
							
							if(prevtile != EditorMain.tileCanvas.tileSelected) {
								UndoableEdit edit = new TileChangeEdit(this, selectedLayer, clickedTileX, clickedTileY, prevtile, EditorMain.tileCanvas.tileSelected);
								undoManager.addEdit(edit);
							}


							getMap().setTileIndex(selectedLayer, clickedTileX, clickedTileY, EditorMain.tileCanvas.tileSelected);
							paintTileXY(selectedLayer, clickedTileX, clickedTileY);
							repaint();
							EditorMain.infoLabel.setTextNoConsole("MapCanvas: Layer " + selectedLayer + " ("+EditorMain.controlPanel.layerLabel[selectedLayer].getText()+") " + clickedTileX + "," + clickedTileY + " set to Tile: " + EditorMain.tileCanvas.tileSelected);

						}
						else if(me.getClickCount() == 2)
						{



								//Recursive Flood Fill

								//fillUndoArray();

								recursiveFill(selectedLayer, clickedTileX, clickedTileY, EditorMain.tileCanvas.tileSelected, prevtile);

								repaintTileEverywhereOnMap(EditorMain.tileCanvas.tileSelected);

						}
					}
					else if(me.getModifiersEx() == ctrlRightClickMask)
					{
						if(mapSelectionArea.isShowing && mapSelectionArea.contains(clickedTileX, clickedTileY))
						{
							sendSelectedLayerToMTEAsNewTilesAndReplaceExistingTiles();
						}

					}
					else if(me.getModifiersEx() == rightMask)
					{
						if(me.getClickCount() == 2 && mapSelectionArea.isShowing && mapSelectionArea.contains(clickedTileX, clickedTileY))
						{

							if(selectedAllLayers)
							{
								sendCombinedLayersToMTEAsNewTiles();

							}
							else
							{
								sendSelectionToMTE();

							}

						}
						else if(getMap().getTileIndex(selectedLayer, clickedTileX, clickedTileY) != EditorMain.tileCanvas.tileSelected)
						{
							EditorMain.tileCanvas.tileSelected = getMap().getTileIndex(selectedLayer, clickedTileX, clickedTileY);
							EditorMain.infoLabel.setTextNoConsole("MapCanvas: Selected Tile "+EditorMain.tileCanvas.tileSelected+" at " + clickedTileX + "," + clickedTileY);
							EditorMain.tileCanvas.paint();//GREEN EYEDROPPER
							EditorMain.controlPanel.repaint();

						}
					}
					else if(me.getModifiersEx() == middleMask)
					{
						deselectMapSelectionArea();
					}
				}
			}

		}
		else //clicked outside of the map.
		{

			if((me.getModifiersEx() == middleMask || me.getModifiersEx() == shiftClickMask) && mouseDragged==false)
			{
				if(selectedLayer==MapData.MAP_DOOR_LAYER)
				{
					if(getMap().getSelectedDoorIndex()!=-1)
					{
						getMap().setSelectedDoorIndex(-1);
						repaint();
						EditorMain.infoLabel.setTextNoConsole("MapCanvas: Deselected Door");
					}

				}
				else
				if(selectedLayer==MapData.MAP_ENTITY_LAYER)
				{
					if(getMap().getSelectedEntityIndex()!=-1)
					{
						getMap().setSelectedEntityIndex(-1);
						repaint();
						EditorMain.infoLabel.setTextNoConsole("MapCanvas: Deselected Map Sprite");
					}

				}
				else
				if(selectedLayer==MapData.MAP_LIGHT_LAYER)
				{
					if(getMap().getSelectedLightIndex()!=-1)
					{
						getMap().setSelectedLightIndex(-1);
						repaint();
						EditorMain.infoLabel.setTextNoConsole("MapCanvas: Deselected Map Light");
					}
				}
				else
				if(selectedLayer==MapData.MAP_AREA_LAYER)
				{
					if(getMap().getSelectedAreaIndex()!=-1)
					{
						getMap().setSelectedAreaIndex(-1);
						repaint();
						EditorMain.infoLabel.setTextNoConsole("MapCanvas: Deselected Map Action");
					}
				}

				deselectMapSelectionArea();


			}
		}

	}


	public void deselectMapSelectionArea()
	{
		if(mapSelectionArea.isShowing==true)
		{
			mapSelectionArea.isShowing=false;
			EditorMain.infoLabel.setTextNoConsole("MapCanvas: Deselected Area");
			repaint();

		}

		if(lockPressed)
		{
			mapSelectionArea.setVisibleLock(false);
			mapSelectionArea.isSelectedLock = false;
			EditorMain.infoLabel.setTextNoConsole("MapCanvas: Disabled Zoom Lock Area");
			repaint();
		}

	}


	//===============================================================================================
	public void mousePressed(MouseEvent me)
	{//===============================================================================================
		EditorMain.lastActiveCanvas = this;

		me = new MouseEvent((Component) me.getSource(), me.getID(), me.getWhen(), me.getModifiersEx(), me.getX()-drawOffsetX(), me.getY()-drawOffsetY(), me.getXOnScreen(), me.getYOnScreen(), me.getClickCount(), me.isPopupTrigger(), me.getButton());


		//int leftMask = InputEvent.BUTTON1_DOWN_MASK;
		int middleMask = InputEvent.BUTTON2_DOWN_MASK;
		//int rightMask = InputEvent.BUTTON3_DOWN_MASK;
		//int shiftClickMask = InputEvent.BUTTON1_DOWN_MASK | InputEvent.SHIFT_DOWN_MASK;

		currentCompoundEdit = new CompoundEdit();

		mousePressedX = me.getX();
		mousePressedY = me.getY();

		int pressedMapX = (int)(me.getX() / (zoom/8.0f));
		int pressedMapY = (int)(me.getY() / (zoom/8.0f));
		int pressedTileX = (int)(me.getX() / zoom);
		int pressedTileY = (int)(me.getY() / zoom);

		if(pressedMapX<0)pressedMapX=0;
		if(pressedMapY<0)pressedMapY=0;
		if(pressedTileX<0)pressedTileX=0;
		if(pressedTileY<0)pressedTileY=0;


		if(me.getModifiersEx() == middleMask)
		{

			if(pressedTileX<getMap().wT()&&pressedTileY<getMap().hT())
			{

				if(selectedLayer==MapData.MAP_LIGHT_LAYER)
				{



					if(mapSelectionArea.isShowing)
					if(pressedMapX>=mapSelectionArea.x1&&pressedMapY>=mapSelectionArea.y1&&pressedMapX<mapSelectionArea.x2&&pressedMapY<mapSelectionArea.y2)
					return;

					//***use pixel precision for lights layer

					//mapSelectionArea.isShowing=true;
					mapSelectionArea.setLocation(pressedMapX+1, pressedMapY+1);//+1 so it's actually under the mouse cursor
					mapSelectionArea.setSize(0, 0);

					repaint();
				}
				else
				{


					if(mapSelectionArea.isShowing)
					if(pressedTileX>=mapSelectionArea.x1&&pressedTileY>=mapSelectionArea.y1&&pressedTileX<mapSelectionArea.x2&&pressedTileY<mapSelectionArea.y2)
					return;

					//mapSelectionArea.isShowing=true;
					mapSelectionArea.setLocation(pressedTileX, pressedTileY);
					mapSelectionArea.setSize(0, 0);

					if(lockPressed)
					{
						mapSelectionArea.isSelectedLock = false;
						mapSelectionArea.setVisibleLock(true);
						mapSelectionArea.setLocationLock(pressedTileX, pressedTileY);
						mapSelectionArea.setSizeLock(0, 0);
					}

					repaint();
				}


			}
			else
			{
				//deselect any selected area if we've pressed the middle mouse button outside the canvas
				deselectMapSelectionArea();
			}
		}
	}


	//===============================================================================================
	public void mouseReleased(MouseEvent me)
	{//===============================================================================================

		me = new MouseEvent((Component) me.getSource(), me.getID(), me.getWhen(), me.getModifiersEx(), me.getX()-drawOffsetX(), me.getY()-drawOffsetY(), me.getXOnScreen(), me.getYOnScreen(), me.getClickCount(), me.isPopupTrigger(), me.getButton());



		int leftMask = InputEvent.BUTTON1_DOWN_MASK;
		int rightMask = InputEvent.BUTTON3_DOWN_MASK;
		int ctrlClickMask = InputEvent.BUTTON1_DOWN_MASK | InputEvent.CTRL_DOWN_MASK;
		int shiftClickMask = InputEvent.BUTTON1_DOWN_MASK | InputEvent.SHIFT_DOWN_MASK;
		int shiftCtrlClickMask = InputEvent.BUTTON1_DOWN_MASK | InputEvent.SHIFT_DOWN_MASK | InputEvent.CTRL_DOWN_MASK;

		if(currentCompoundEdit != null) {
			currentCompoundEdit.end();
			if(currentCompoundEdit.isSignificant()) {
				undoManager.addEdit(currentCompoundEdit);
			}
			currentCompoundEdit = null;
		}

		mouseDragged = false;


		int releasedMapX = (int)(me.getX() / (zoom/8.0f));
		int releasedMapY = (int)(me.getY() / (zoom/8.0f));

		int releasedTileX = (int)(me.getX() / zoom);
		int releasedTileY = (int)(me.getY() / zoom);




		int pressedTileX = (int)(mousePressedX / zoom);
		int pressedTileY = (int)(mousePressedY / zoom);

		mousePressedX = this.getWidth();
		mousePressedY = this.getHeight();


		if(selectionDragged)
		{
			if(pressedTileX==releasedTileX&&pressedTileY==releasedTileY){selectionDragged = false;setCursor(new Cursor(Cursor.DEFAULT_CURSOR));repaint();return;}

			if((me.getModifiersEx() == rightMask || me.getModifiersEx() == ctrlClickMask))
			{
				selectionDragged = false;
				//fillUndoArray();
				mapSelectionArea.copyFromTo(releasedTileX, releasedTileY, pressedTileX, pressedTileY);
			}
			else
			if(me.getModifiersEx() == leftMask)
			{
				selectionDragged = false;
				//fillUndoArray();
				mapSelectionArea.swapFromTo(releasedTileX, releasedTileY, pressedTileX, pressedTileY);
			}
		}







		if(doorDragged)
		{

			if(pressedTileX==releasedTileX&&pressedTileY==releasedTileY){doorDragged = false; setCursor(new Cursor(Cursor.DEFAULT_CURSOR));repaint();return;}

			doorDragged = false;

			if(me.getModifiersEx() == leftMask)
			{
				Door door = getMap().getSelectedDoor();
				int oldX = door.xP();
				int oldY = door.yP();
				int newX = releasedTileX*8;
				int newY = releasedTileY*8;
				
				undoManager.addEdit(new MapObjectMoveEdit(door, oldX, oldY, newX, newY));

				//tile precision (default)
				door.setXPixels(newX);
				door.setYPixels(newY);

				EditorMain.infoLabel.setText("MapCanvas: Door Moved");

				//if we're using the buffer, we just need to update the sprite layer
				if(useLayerImageBuffer==true)
				{
					getMap().updateLayerBufferImage(MapData.MAP_DOOR_LAYER);
					drawBufferedLayerImagesIntoMapCanvasImage();

					repaint();
				}

				if(useLayerImageBuffer==false)
				{
					//if we're not using the buffer, we can either update the previous tiles it was on and the new tiles it was on
					//or just be lazy and redraw everything
					updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();
				}
			}
		}

		if(doorArrivalDragged)
		{
			doorArrivalDragged = false;

			if(me.getModifiersEx() == leftMask)
			{
				//tile precision (default)
				getMap().getSelectedDoor().setArrivalXPixels(releasedTileX*8);
				getMap().getSelectedDoor().setArrivalYPixels(releasedTileY*8);

				EditorMain.infoLabel.setText("MapCanvas: Door Arrival Point Moved");

				//for door arrival point, just need to repaint
				repaint();

				//if we're using the buffer, we just need to update the sprite layer
				/*
				if(useLayerImageBuffer==true)
				{
					getMap().updateLayerBufferImage(MapData.DOORSPRITE_LAYER);
					drawBufferedLayerImagesIntoMapCanvasImage();

					repaint();
				}

				if(useLayerImageBuffer==false)
				{
					//if we're not using the buffer, we can either update the previous tiles it was on and the new tiles it was on
					//or just be lazy and redraw everything
					updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();
				}
				*/
			}

		}

		if(entityDragged)
		{

			if(pressedTileX==releasedTileX&&pressedTileY==releasedTileY){entityDragged = false; setCursor(new Cursor(Cursor.DEFAULT_CURSOR));repaint();return;}

			entityDragged=false;

			int oldMapX = getMap().getSelectedEntity().xP();
			int oldMapY = getMap().getSelectedEntity().yP();

			if(me.getModifiersEx() == ctrlClickMask || me.getModifiersEx() == rightMask)
			{
				//copy sprite

				Entity e = getMap().getSelectedEntity().duplicate(getMap(),getState());

				e.setNameNoRename(getMap().createUniqueEntityName(getMap().getSelectedEntity().name(), -1));

				if(moveEntityByPixel)
				{
					//pixel precision
					e.setXPixels(releasedMapX);
					e.setYPixels(releasedMapY);
				}
				else
				{
					//tile precision (default)
					e.setXPixels(releasedTileX*8);
					e.setYPixels(releasedTileY*8);
				}

				getMap().addEntity(e);
				undoManager.addEdit(new MapObjectAddEdit(getMap(), e));

				getMap().setSelectedEntityIndex(getMap().getNumEntities()-1);

				if(moveEntityByPixel)
				{
					//pixel precision
					getMap().getSelectedEntity().setXPixels(releasedMapX);
					getMap().getSelectedEntity().setYPixels(releasedMapY);
				}
				else
				{
					//tile precision (default)
					getMap().getSelectedEntity().setXPixels(releasedTileX*8);
					getMap().getSelectedEntity().setYPixels(releasedTileY*8);
				}


				//getMap().getNumEntities()++;

				EditorMain.infoLabel.setText("MapCanvas: Map Sprite Copied");
			}
			else
			if(me.getModifiersEx() == leftMask)
			{
				//move sprite
				Entity entity = getMap().getSelectedEntity();
				int newX, newY;

				if(moveEntityByPixel)
				{
					//pixel precision
					newX = releasedMapX;
					newY = releasedMapY;
				}
				else
				{
					//tile precision (default)
					newX = releasedTileX*8;
					newY = releasedTileY*8;
				}
				
				undoManager.addEdit(new MapObjectMoveEdit(entity, oldMapX, oldMapY, newX, newY));
				entity.setXPixels(newX);
				entity.setYPixels(newY);

				EditorMain.infoLabel.setText("MapCanvas: Map Sprite Moved");
			}

			//if we're using the buffer, we just need to update the sprite layer
			if(useLayerImageBuffer==true)
			{
				getMap().updateLayerBufferImage(MapData.MAP_ENTITY_LAYER);
				drawBufferedLayerImagesIntoMapCanvasImage();

				repaint();
			}

			if(useLayerImageBuffer==false)
			{
				//if we're not using the buffer, we can either update the previous tiles it was on and the new tiles it was on
				Entity m =  getMap().getSelectedEntity();
				int sx = m.xP();
				int sy = m.yP();
				int sw = (int) (m.wP());
				int sh = (int) (m.hP());

				for(int x=oldMapX/8;x<((oldMapX+sw)/8)+1;x++)//repaint where the sprite WAS
				for(int y=oldMapY/8;y<((oldMapY+sh)/8)+1;y++)
					paintTileXY(MapData.MAP_ENTITY_LAYER,x,y);

				for(int x=sx/8;x<((sx+sw)/8)+1;x++)//repaint where the sprite IS
				for(int y=sy/8;y<((sy+sh)/8)+1;y++)
					paintTileXY(MapData.MAP_ENTITY_LAYER,x,y);

				repaint();
			}
		}


		if(lightDragged)
		{

			if(pressedTileX==releasedTileX&&pressedTileY==releasedTileY){lightDragged = false; setCursor(new Cursor(Cursor.DEFAULT_CURSOR));repaint();return;}


			lightDragged=false;

			if(me.getModifiersEx() == ctrlClickMask || me.getModifiersEx() == rightMask)
			{

				//copy light


				Light l = getMap().getSelectedLight().duplicate(getMap(),getState());

				l.setNameNoRename(getMap().createUniqueLightName(getMap().getSelectedLight().name(), -1));

				l.setXPixels(releasedMapX);
				l.setYPixels(releasedMapY);

				getMap().addLight(l);
				undoManager.addEdit(new MapObjectAddEdit(getMap(), l));

				getMap().setSelectedLightIndex(getMap().getNumLights()-1);

				//getMap().getNumLights()++;

				EditorMain.infoLabel.setText("MapCanvas: Map Light Copied");
			}
			else
			if(me.getModifiersEx() == leftMask)
			{
				Light light = getMap().getSelectedLight();
				int oldX = light.xP();
				int oldY = light.yP();
				int newX = releasedMapX;
				int newY = releasedMapY;
				
				undoManager.addEdit(new MapObjectMoveEdit(light, oldX, oldY, newX, newY));

				//pixel precision
				light.setXPixels(newX);
				light.setYPixels(newY);

				EditorMain.infoLabel.setText("MapCanvas: Map Light Moved");
			}


			//if we're using the buffer, we just need to update the lights layer
			if(useLayerImageBuffer==true)
			{
				getMap().updateLayerBufferImage(MapData.MAP_LIGHT_LAYER);
				drawBufferedLayerImagesIntoMapCanvasImage();

				repaint();
			}

			if(useLayerImageBuffer==false)
			{
				Light l = getMap().getSelectedLight();
				//if we're not using the buffer, we can either update the previous tiles it was on and the new tiles it was on
				int sx = (l.xP()-l.radiusPixels1X());
				int sy = (l.yP()-l.radiusPixels1X());
				int sw = ((l.radiusPixels1X()*2)+l.wP());
				int sh = ((l.radiusPixels1X()*2)+l.hP());

				for(int x=sx/8;x<((sx+sw)/8)+1;x++)
				for(int y=sy/8;y<((sy+sh)/8)+1;y++)
					paintTileXY(MapData.MAP_LIGHT_LAYER,x,y);

				repaint();
			}




		}


		if(lightToggleDragged)
		{
			lightToggleDragged = false;

			if(me.getModifiersEx() == leftMask)
			{
				//tile precision (default)
				getMap().getSelectedLight().setToggleXPixels(releasedTileX*8);
				getMap().getSelectedLight().setToggleYPixels(releasedTileY*8);

				EditorMain.infoLabel.setText("MapCanvas: Light Toggle Point Moved");

				repaint();
			}

		}


		if(areaDragged)
		{
			if(pressedTileX==releasedTileX&&pressedTileY==releasedTileY){areaDragged = false; setCursor(new Cursor(Cursor.DEFAULT_CURSOR));repaint();return;}

			areaDragged=false;


			if(me.getModifiersEx() == ctrlClickMask || me.getModifiersEx() == rightMask)
			{

				//copy action

				Area a = getMap().getSelectedArea().duplicate(getMap(),getState());

				a.setNameNoRename(getMap().createUniqueAreaName(getMap().getSelectedArea().name(), -1));

				a.setXPixels(releasedTileX*8);
				a.setYPixels(releasedTileY*8);


				getMap().addArea(a);
				undoManager.addEdit(new MapObjectAddEdit(getMap(), a));

				getMap().setSelectedAreaIndex(getMap().getNumAreas()-1);

				//getMap().getNumAreas()++;

				EditorMain.infoLabel.setText("MapCanvas: Map Action Copied");
			}
			else
			if(me.getModifiersEx() == shiftClickMask)
			{
				Area area = getMap().getSelectedArea();
				int oldX = area.xP();
				int oldY = area.yP();
				int newX = releasedMapX;
				int newY = releasedMapY;
				
				undoManager.addEdit(new MapObjectMoveEdit(area, oldX, oldY, newX, newY));

				//pixel precision
				area.setXPixels(newX);
				area.setYPixels(newY);
			}
			else
			if(me.getModifiersEx() == leftMask)
			{
				Area area = getMap().getSelectedArea();
				int oldX = area.xP();
				int oldY = area.yP();
				int newX = releasedTileX*8;
				int newY = releasedTileY*8;
				
				undoManager.addEdit(new MapObjectMoveEdit(area, oldX, oldY, newX, newY));

				//tile precision (default)
				area.setXPixels(newX);
				area.setYPixels(newY);
			}


			//for actions, we just need to repaint, as they are all drawn in the mapCanvas repaint function
			repaint();


			EditorMain.infoLabel.setText("MapCanvas: Map Action Moved");

		}

		if(areaArrivalDragged && (me.getModifiersEx() == leftMask || me.getModifiersEx() == shiftClickMask ))
		{
			areaArrivalDragged=false;

			if(me.getModifiersEx() == shiftClickMask)
			{
				//pixel precision
				getMap().getSelectedArea().setArrivalXPixels(releasedMapX);
				getMap().getSelectedArea().setArrivalYPixels(releasedMapY);
			}
			else
			if(me.getModifiersEx() == leftMask)
			{
				//tile precision (default)
				getMap().getSelectedArea().setArrivalXPixels(releasedTileX*8);
				getMap().getSelectedArea().setArrivalYPixels(releasedTileY*8);
			}

			//for actions, we just need to repaint, as they are all drawn in the mapCanvas repaint function
			repaint();

			EditorMain.infoLabel.setText("MapCanvas: Map Action Arrival Point Moved");

		}



		if(selectedLayer==MapData.MAP_DOOR_LAYER|| selectedLayer==MapData.MAP_ENTITY_LAYER|| selectedLayer==MapData.MAP_AREA_LAYER)
		if(doorConnectionDragged || entityConnectionDragged || areaConnectionDragged)
		{

			//if we let the mouse off over an action or another door, add connection

			//go through all doors, areas, if mouse is over any of them, highlight that object.
			for(int n=0;n<getMap().getNumDoors();n++)
			{
				Door dropDoor = getMap().getDoor(n);
				if(
						releasedMapX>=dropDoor.xP()&&
						releasedMapX<=dropDoor.xP()+dropDoor.wP()&&
						releasedMapY>=dropDoor.yP()&&
						releasedMapY<=dropDoor.yP()+dropDoor.hP()
				)
				{

					//create a connection to that door.
					if(doorConnectionDragged==true)
					{
						doorConnectionDragged=false;
						Door d = getMap().getSelectedDoor();

						if(d!=dropDoor)
						if(d.connectionTYPEIDList().contains(dropDoor.getTYPEIDString())==false)
						d.connectionTYPEIDList().add(dropDoor.getTYPEIDString());
					}

					if(entityConnectionDragged==true)
					{
						entityConnectionDragged=false;
						Entity s = getMap().getSelectedEntity();

						if(s.connectionTYPEIDList().contains(dropDoor.getTYPEIDString())==false)
						s.connectionTYPEIDList().add(dropDoor.getTYPEIDString());
					}

					if(areaConnectionDragged==true)
					{
						areaConnectionDragged=false;
						Area a = getMap().getSelectedArea();

						if(a.connectionTYPEIDList().contains(dropDoor.getTYPEIDString())==false)
						a.connectionTYPEIDList().add(dropDoor.getTYPEIDString());
					}

					repaint();

					break;
				}
			}

			for(int n=0;n<getMap().getNumAreas();n++)
			{

				Area dropArea = getMap().getArea(n);
				if(
						releasedMapX>=dropArea.xP()&&
						releasedMapX<=dropArea.xP()+dropArea.wP()&&
						releasedMapY>=dropArea.yP()&&
						releasedMapY<=dropArea.yP()+dropArea.hP()
				)
				{

					//create a connection to that door.
					if(doorConnectionDragged==true)
					{
						doorConnectionDragged=false;
						Door d = getMap().getSelectedDoor();

						if(d.connectionTYPEIDList().contains(dropArea.getTYPEIDString())==false)
						d.connectionTYPEIDList().add(dropArea.getTYPEIDString());
					}

					if(entityConnectionDragged==true)
					{
						entityConnectionDragged=false;
						Entity s = getMap().getSelectedEntity();

						if(s.connectionTYPEIDList().contains(dropArea.getTYPEIDString())==false)
						s.connectionTYPEIDList().add(dropArea.getTYPEIDString());
					}

					if(areaConnectionDragged==true)
					{
						areaConnectionDragged=false;
						Area a = getMap().getSelectedArea();

						if(a!=dropArea)
						if(a.connectionTYPEIDList().contains(dropArea.getTYPEIDString())==false)
						a.connectionTYPEIDList().add(dropArea.getTYPEIDString());
					}

					repaint();

					break;
				}
			}


			if(doorConnectionDragged || entityConnectionDragged || areaConnectionDragged)
			{


				if(me.getModifiersEx() == shiftCtrlClickMask)
				{
					//if we dropped it on nothing, create a waypoint action there.
					//if pull a connection from an area and drop it, should be automatic 1x1 waypoint.
					//not of interest to random, waitHereTicks=0, randomTime=false, name= waypoint0, onlyOneAllowed=false

					int draggedTileX = (int)(me.getX() / (zoom));
					int draggedTileY = (int)(me.getY() / (zoom));

					Area a = new Area(getMap(),getMap().getSelectedState());

					a.setNameNoRename(getMap().createUniqueAreaName("waypoint", -1));
					a.setXPixels(draggedTileX*8);
					a.setYPixels(draggedTileY*8);
					a.setWidthPixels(4);
					a.setHeightPixels(4);
					a.setWaitHereTicks(0); //0 is waypoint



					getMap().addArea(a);
					undoManager.addEdit(new MapObjectAddEdit(getMap(), a));



					if(doorConnectionDragged)getMap().getSelectedDoor().connectionTYPEIDList().add(a.getTYPEIDString());
					if(entityConnectionDragged)getMap().getSelectedEntity().connectionTYPEIDList().add(a.getTYPEIDString());
					if(areaConnectionDragged)getMap().getSelectedArea().connectionTYPEIDList().add(a.getTYPEIDString());
				}


				doorConnectionDragged=false;
				entityConnectionDragged=false;
				areaConnectionDragged=false;

				repaint();

			}

		}

		setCursor(new Cursor(Cursor.DEFAULT_CURSOR));

	}


	//===============================================================================================
	public void mouseEntered(MouseEvent me)
	{//===============================================================================================
		setCursor(new Cursor(Cursor.DEFAULT_CURSOR));//bob9-23-05

	}


	//===============================================================================================
	public void mouseExited(MouseEvent me)
	{//===============================================================================================

	}


	//===============================================================================================
	public void mouseMoved(MouseEvent me)
	{//===============================================================================================

		me = new MouseEvent((Component) me.getSource(), me.getID(), me.getWhen(), me.getModifiersEx(), me.getX()-drawOffsetX(), me.getY()-drawOffsetY(), me.getXOnScreen(), me.getYOnScreen(), me.getClickCount(), me.isPopupTrigger(), me.getButton());


		int movedTileX = me.getX() / zoom;
		int movedTileY = me.getY() / zoom;
		int movedMapX = (int)(me.getX() / (zoom/8.0f));
		int movedMapY = (int)(me.getY() / (zoom/8.0f));

		if(MapData.isTileLayer(selectedLayer)==false)
		{

			//there are always drawn anyway

//			if(selectedAllLayers || selectedLayer==MapData.DOOR_LAYER)
//			for(int n=0;n<getMap().getNumDoors();n++)
//			{
//				Door d = getMap().getDoor(n);
//				if(
//						movedMapX>=d.mapX&&
//								movedMapX<=d.mapX+d.getWidth()&&
//										movedMapY>=d.mapY&&
//												movedMapY<=d.mapY+d.getHeight()
//				)
//				{
//
//					//getMap().drawDoorLayerSelection(G);
//
//				}
//			}

			if(selectedAllLayers || selectedLayer==MapData.MAP_ENTITY_LAYER)
			for(int n=0;n<getMap().getNumEntities();n++)
			{
				Entity e = getMap().getEntity(n);
				if(
						movedMapX>=e.xP()&&
								movedMapX<=e.xP()+e.wP()&&
										movedMapY>=e.yP()&&
												movedMapY<=e.yP()+e.hP()
				)
				{

					repaint();
					Graphics G = getGraphics();
					G.translate(drawOffsetX(),drawOffsetY());
					getMap().drawSpriteConnections(G, e);
					getMap().drawSpriteHitBox(G, e);
					getMap().drawSpriteInfo(G, e);
				}
			}

			if(selectedAllLayers || selectedLayer==MapData.MAP_AREA_LAYER)
			for(int n=0;n<getMap().getNumAreas();n++)
			{
				Area a = getMap().getArea(n);
				if(
						movedMapX>=a.xP()&&
								movedMapX<=a.xP()+a.wP()&&
										movedMapY>=a.yP()&&
												movedMapY<=a.yP()+a.hP()
				)
				{

					repaint();
					Graphics G = getGraphics();
					G.translate(drawOffsetX(),drawOffsetY());
					getMap().drawAreaConnections(G, a);
					getMap().drawAreaInfo(G, a);
				}
			}
		}



	}

	//===============================================================================================
	public void mouseDragged(MouseEvent me)
	{//===============================================================================================
		MouseEvent originalME = me;
		me = new MouseEvent((Component) me.getSource(), me.getID(), me.getWhen(), me.getModifiersEx(), me.getX()-drawOffsetX(), me.getY()-drawOffsetY(), me.getXOnScreen(), me.getYOnScreen(), me.getClickCount(), me.isPopupTrigger(), me.getButton());


		int leftMask = InputEvent.BUTTON1_DOWN_MASK;
		int middleMask = InputEvent.BUTTON2_DOWN_MASK;
		int rightMask = InputEvent.BUTTON3_DOWN_MASK;
		int shiftClickMask = InputEvent.BUTTON1_DOWN_MASK | InputEvent.SHIFT_DOWN_MASK;
		int shiftMiddleClickMask = InputEvent.BUTTON2_DOWN_MASK | InputEvent.SHIFT_DOWN_MASK;
		int shiftCtrlClickMask = InputEvent.BUTTON1_DOWN_MASK | InputEvent.SHIFT_DOWN_MASK | InputEvent.CTRL_DOWN_MASK;


		mouseDragged = true;

		int oldMapX = (int)(mousePressedX / (zoom/8.0f));
		int oldMapY = (int)(mousePressedY / (zoom/8.0f));

		int draggedMapX = (int)(me.getX() / (zoom/8.0f));
		int draggedMapY = (int)(me.getY() / (zoom/8.0f));



		if(me.getModifiersEx() == shiftMiddleClickMask)
		{

			int offsetX = mousePressedX - me.getX();
			int offsetY = mousePressedY - me.getY();

			Point p = EditorMain.mapScrollPane.getViewport().getViewPosition();

			p.x+=offsetX;
			p.y+=offsetY;

			EditorMain.mapScrollPane.getViewport().setViewPosition(p);

			//repaint();

		}




		if(

				me.getModifiersEx() == middleMask
				&& (mapSelectionArea.isShowing || (me.getX()>mousePressedX+8&&me.getY()>mousePressedY+8))
		)
		{

			if(selectedLayer==MapData.MAP_LIGHT_LAYER)
			{
				mapSelectionArea.isShowing=true;

				//notice it is using mapX and not tileX here, because it is using pixel precision.

				int x = draggedMapX+1;//+1 so it's actually under the mouse cursor
				int y = draggedMapY+1;

				if(x > getMap().wT()*8)
				{
					x = getMap().wT()*8;
				}

				if(y > getMap().hT()*8)
				{
					y = getMap().hT()*8;
				}

				mapSelectionArea.setLocation2(x, y);
				repaint();

				EditorMain.infoLabel.setTextNoConsole("MapCanvas: Selected Area: " + (mapSelectionArea.x2 - mapSelectionArea.x1) + "x" + (mapSelectionArea.y2 - mapSelectionArea.y1));

				return;
			}
			else
			{
				if(lockPressed)
				{
					mapSelectionArea.setVisibleLock(true);
					mapSelectionArea.setLocation2Lock((me.getX() + zoom) / zoom, (me.getY() + zoom) / zoom);
					repaint();
					EditorMain.infoLabel.setTextNoConsole("MapCanvas: Zoom locked: " + (mapSelectionArea.x2Lock - mapSelectionArea.x1Lock) + "x" + (mapSelectionArea.y2Lock - mapSelectionArea.y1Lock));
				}
				else
				{
					mapSelectionArea.isShowing=true;

					int draggedTileX = (me.getX() + zoom) / zoom; //notice this is + zoom, so it selects the tile under the cursor
					int draggedTileY = (me.getY() + zoom) / zoom;
					if(draggedTileX > getMap().wT())
					{
						draggedTileX = getMap().wT();
					}
					if(draggedTileY > getMap().hT())
					{
						draggedTileY = getMap().hT();
					}

					mapSelectionArea.setLocation2(draggedTileX, draggedTileY);
					repaint();

					EditorMain.infoLabel.setTextNoConsole("MapCanvas: Selected Area: " + (mapSelectionArea.x2 - mapSelectionArea.x1) + "x" + (mapSelectionArea.y2 - mapSelectionArea.y1));
				}
				return;
			}
		}



		if(me.getModifiersEx() == shiftClickMask || me.getModifiersEx() == shiftCtrlClickMask)
		{

			if(selectedLayer==MapData.MAP_DOOR_LAYER|| selectedLayer==MapData.MAP_ENTITY_LAYER|| selectedLayer==MapData.MAP_AREA_LAYER)
			{

				if(selectedLayer==MapData.MAP_DOOR_LAYER&& doorConnectionDragged==false && getMap().getSelectedDoorIndex()!=-1)
				{
					doorConnectionDragged=true;
					return;
				}

				if(selectedLayer==MapData.MAP_ENTITY_LAYER&& entityConnectionDragged==false && getMap().getSelectedEntityIndex()!=-1)
				{
					entityConnectionDragged=true;
					return;
				}

				if(selectedLayer==MapData.MAP_AREA_LAYER&& areaConnectionDragged==false && getMap().getSelectedAreaIndex()!=-1)
				{
					areaConnectionDragged=true;
					return;
				}


				if(doorConnectionDragged==true || entityConnectionDragged==true || areaConnectionDragged==true)
				{

					if(me.getModifiersEx() == shiftClickMask)setCursor(new Cursor(Cursor.HAND_CURSOR));
					else setCursor(new Cursor(Cursor.CROSSHAIR_CURSOR));

					//draw line from door to cursor

					repaint();

					Graphics G = getGraphics();
					G.translate(drawOffsetX(),drawOffsetY());

					G.setColor(Color.GREEN);

					int objX = 0;
					int objY = 0;



					if(selectedLayer==MapData.MAP_DOOR_LAYER)
					{
						Door d = getMap().getSelectedDoor();

						objX = d.xP()*zoom/8 + d.wP()/2*zoom/8;
						objY = d.yP()*zoom/8 + d.hP()*zoom/8;

						//show area info
						getMap().drawAreaLayerSelection(G);

					}

					if(selectedLayer==MapData.MAP_ENTITY_LAYER)
					{
						Entity s = getMap().getSelectedEntity();

						objX = s.xP()*zoom/8 + s.wP()/2*zoom/8;
						objY = s.yP()*zoom/8 + s.hP()*zoom/8;

						//outline doors, show area info (areas already outlined)
						getMap().drawDoorLayerSelection(G);
						getMap().drawAreaLayerSelection(G);
					}


					if(selectedLayer==MapData.MAP_AREA_LAYER)
					{
						Area a = getMap().getSelectedArea();

						objX = a.xP()*zoom/8 + a.wP()/2*zoom/8;
						objY = a.yP()*zoom/8 + a.hP()/2*zoom/8;

						//outline doors
						getMap().drawDoorLayerSelection(G);

					}

					int movedMapX = (int)(me.getX() / (zoom/8.0f));
					int movedMapY = (int)(me.getY() / (zoom/8.0f));

					G.drawLine(objX,objY,me.getX(),me.getY());


					//go through all doors, areas, if mouse is over any of them, highlight that object.
					for(int n=0;n<getMap().getNumDoors();n++)
					{
						Door hoverDoor = getMap().getDoor(n);
						if(
								movedMapX>=hoverDoor.xP()&&
								movedMapX<=hoverDoor.xP()+hoverDoor.wP()&&
								movedMapY>=hoverDoor.yP()&&
								movedMapY<=hoverDoor.yP()+hoverDoor.hP()
						)
						{
							//draw highlight over door.
							int x = (int)(((float)hoverDoor.xP())*zoom/8);
							int y = (int)(((float)hoverDoor.yP())*zoom/8);
							int w = (int)(((float)(hoverDoor.wP()))*zoom/8)-1;
							int h = (int)(((float)(hoverDoor.hP()))*zoom/8)-1;

							//draw purple rectangle with black outlines
							G.setColor(Color.BLACK);
							G.drawRect(x+1,y+1,w-2,h-2);
							G.drawRect(x-1,y-1,w+2,h+2);
							G.setColor(new Color(200,0,255,255));
							G.fillRect(x,y,w,h);
						}
					}

					for(int n=0;n<getMap().getNumAreas();n++)
					{
						Area hoverArea = getMap().getArea(n);
						if(
								movedMapX>=hoverArea.xP()&&
								movedMapX<=hoverArea.xP()+hoverArea.wP()&&
								movedMapY>=hoverArea.yP()&&
								movedMapY<=hoverArea.yP()+hoverArea.hP()
						)
						{
							//draw highlight over action
							int x = (int)(((float)hoverArea.xP())*zoom/8);
							int y = (int)(((float)hoverArea.yP())*zoom/8);
							int w = (int)(((float)(hoverArea.wP()))*zoom/8)-1;
							int h = (int)(((float)(hoverArea.hP()))*zoom/8)-1;

							//draw purple rectangle with black outlines
							G.setColor(Color.BLACK);
							G.drawRect(x+1,y+1,w-2,h-2);
							G.drawRect(x-1,y-1,w+2,h+2);
							G.setColor(new Color(200,0,255,255));
							G.fillRect(x,y,w,h);
						}
					}

					int draggedTileX = (int)(me.getX() / (zoom));
					int draggedTileY = (int)(me.getY() / (zoom));

					if(me.getModifiersEx() == shiftCtrlClickMask)G.drawRect(draggedTileX*zoom, draggedTileY*zoom, zoom, zoom);

					return;
				}
			}

		}

		if(me.getModifiersEx() == leftMask || me.getModifiersEx() == rightMask)
		{

			Door selectedDoor = getMap().getSelectedDoor();
			Area selectedArea = getMap().getSelectedArea();
			Light selectedLight = getMap().getSelectedLight();
			Entity selectedEntity = getMap().getSelectedEntity();

			//handle movement and copying of selection
			if(
					selectionDragged==false&&
					mapSelectionArea.isShowing&&
					mapSelectionArea.contains(me.getX() / zoom, me.getY() / zoom)
					&&(draggedMapX>oldMapX-8&&draggedMapX<oldMapX+8&&draggedMapY>oldMapY-8&&draggedMapY<oldMapY+8)//this is so we can't click outside the item, drag over it, and move it by "picking it up"

			)
			{
				if(me.getModifiersEx() == rightMask)setCursor(new Cursor(Cursor.CROSSHAIR_CURSOR));
				else setCursor(new Cursor(Cursor.MOVE_CURSOR));
				selectionDragged = true;
				return;
			}

			//handle movement of door arrival point
			if(
					me.getModifiersEx() == leftMask&&
					doorArrivalDragged==false&&
					doorDragged==false&&
					selectedLayer==MapData.MAP_DOOR_LAYER&&
					getMap().getSelectedDoorIndex()!=-1&&
					draggedMapX>=selectedDoor.arrivalXPixels()&&
					draggedMapX<=selectedDoor.arrivalXPixels()+8&&
					draggedMapY>=selectedDoor.arrivalYPixels()&&
					draggedMapY<=selectedDoor.arrivalYPixels()+8
					&&(draggedMapX>oldMapX-8&&draggedMapX<oldMapX+8&&draggedMapY>oldMapY-8&&draggedMapY<oldMapY+8)


			)
			{
				setCursor(new Cursor(Cursor.MOVE_CURSOR));
				doorArrivalDragged = true;
				return;
			}

			//handle movement of door
			if(
					me.getModifiersEx() == leftMask&&
					doorDragged==false&&
					doorArrivalDragged==false&&
					selectedLayer==MapData.MAP_DOOR_LAYER&&
					getMap().getSelectedDoorIndex()!=-1&&
					draggedMapX>=selectedDoor.xP()&&
					draggedMapX<=selectedDoor.xP()+selectedDoor.wP()&&
					draggedMapY>=selectedDoor.yP()&&
					draggedMapY<=selectedDoor.yP()+selectedDoor.hP()
					&&(draggedMapX>oldMapX-8&&draggedMapX<oldMapX+8&&draggedMapY>oldMapY-8&&draggedMapY<oldMapY+8)

			)
			{
				setCursor(new Cursor(Cursor.MOVE_CURSOR));
				doorDragged = true;
				return;
			}

			//handle movement and copying of sprite
			if(
					entityDragged==false&&
					selectedLayer==MapData.MAP_ENTITY_LAYER&&
					getMap().getSelectedEntityIndex()!=-1&&
					draggedMapX>=selectedEntity.xP()&&
					draggedMapX<=selectedEntity.xP()+(selectedEntity.wP())&&
					draggedMapY>=selectedEntity.yP()&&
					draggedMapY<=selectedEntity.yP()+selectedEntity.hP()
					&&(draggedMapX>oldMapX-8&&draggedMapX<oldMapX+8&&draggedMapY>oldMapY-8&&draggedMapY<oldMapY+8)

			)
			{
				if(me.getModifiersEx() == rightMask)setCursor(new Cursor(Cursor.CROSSHAIR_CURSOR));
				else setCursor(new Cursor(Cursor.MOVE_CURSOR));
				entityDragged = true;
				return;
			}


			//handle movement of light toggle
			if(
					me.getModifiersEx() == leftMask&&
					lightToggleDragged==false&&
					lightDragged==false&&
					selectedLayer==MapData.MAP_LIGHT_LAYER&&
					getMap().getSelectedLightIndex()!=-1&&
					draggedMapX>=selectedLight.toggleXPixels1X()&&
					draggedMapX<=selectedLight.toggleXPixels1X()+8&&
					draggedMapY>=selectedLight.toggleYPixels1X()&&
					draggedMapY<=selectedLight.toggleYPixels1X()+8
					&&(draggedMapX>oldMapX-8&&draggedMapX<oldMapX+8&&draggedMapY>oldMapY-8&&draggedMapY<oldMapY+8)


			)
			{
				setCursor(new Cursor(Cursor.MOVE_CURSOR));
				lightToggleDragged = true;
				return;
			}


			//handle movement and copying of light
			if(
					lightToggleDragged==false&&
					lightDragged==false&&
					selectedLayer==MapData.MAP_LIGHT_LAYER&&
					getMap().getSelectedLightIndex()!=-1&&
					draggedMapX>=selectedLight.xP()&&
					draggedMapX<=selectedLight.xP()+selectedLight.wP()&&
					draggedMapY>=selectedLight.yP()&&
					draggedMapY<=selectedLight.yP()+selectedLight.hP()
					&&(draggedMapX>oldMapX-8&&draggedMapX<oldMapX+8&&draggedMapY>oldMapY-8&&draggedMapY<oldMapY+8)

			)
			{
				if(me.getModifiersEx() == rightMask)setCursor(new Cursor(Cursor.CROSSHAIR_CURSOR));
				else setCursor(new Cursor(Cursor.MOVE_CURSOR));
				lightDragged = true;
				return;
			}


			//handle movement of action arrival
			if(
					me.getModifiersEx() == leftMask&&
					areaDragged==false&&
					areaArrivalDragged==false&&
					selectedLayer==MapData.MAP_AREA_LAYER&&
					getMap().getSelectedAreaIndex()!=-1&&
					draggedMapX>=selectedArea.arrivalXPixels()&&
					draggedMapX<=selectedArea.arrivalXPixels()+8&&
					draggedMapY>=selectedArea.arrivalYPixels()&&
					draggedMapY<=selectedArea.arrivalYPixels()+8
					&&(draggedMapX>oldMapX-8&&draggedMapX<oldMapX+8&&draggedMapY>oldMapY-8&&draggedMapY<oldMapY+8)

			)
			{
				setCursor(new Cursor(Cursor.MOVE_CURSOR));
				areaArrivalDragged = true;
				return;
			}


			//handle movement and copying of action
			if(
					areaDragged==false&&
					areaArrivalDragged==false&&
					selectedLayer==MapData.MAP_AREA_LAYER&&
					getMap().getSelectedAreaIndex()!=-1&&
					draggedMapX>=selectedArea.xP()&&
					draggedMapX<=selectedArea.xP()+selectedArea.wP()&&
					draggedMapY>=selectedArea.yP()&&
					draggedMapY<=selectedArea.yP()+selectedArea.hP()
					&&(draggedMapX>oldMapX-8&&draggedMapX<oldMapX+8&&draggedMapY>oldMapY-8&&draggedMapY<oldMapY+8)

			)
			{
				if(me.getModifiersEx() == rightMask)setCursor(new Cursor(Cursor.CROSSHAIR_CURSOR));
				else setCursor(new Cursor(Cursor.MOVE_CURSOR));
				areaDragged = true;
				return;
			}




			int movedMapX = (int)(me.getX() / (zoom/8.0f));
			int movedMapY = (int)(me.getY() / (zoom/8.0f));

			int movedTileX = (int)(me.getX() / zoom);
			int movedTileY = (int)(me.getY() / zoom);

			if(areaArrivalDragged)
			{
				repaint();
				Graphics G = getGraphics();
				G.translate(drawOffsetX(),drawOffsetY());
				G.setColor(new Color(200,0,255));
				int w = 8;
				int h = 8;
				G.drawRect((movedTileX)*zoom,(movedTileY)*zoom,w*zoom/8,h*zoom/8);
				return;
			}

			if(areaDragged)
			{
				repaint();
				Graphics G = getGraphics();
				G.translate(drawOffsetX(),drawOffsetY());
				G.setColor(Color.GREEN);
				int w = selectedArea.wP();
				int h = selectedArea.hP();
				G.drawRect((movedTileX)*zoom,(movedTileY)*zoom,w*zoom/8,h*zoom/8);
				return;
			}


			if(lightToggleDragged)
			{
				repaint();
				Graphics G = getGraphics();
				G.translate(drawOffsetX(),drawOffsetY());
				G.setColor(new Color(200,0,255));
				int w = 8;
				int h = 8;
				G.drawRect((movedTileX)*zoom,(movedTileY)*zoom,w*zoom/8,h*zoom/8);
				return;
			}

			if(lightDragged)
			{
				repaint();
				Graphics G = getGraphics();
				G.translate(drawOffsetX(),drawOffsetY());
				G.setColor(Color.GREEN);

				int w = getMap().getSelectedLight().bufferedImage.getWidth();
				int h = getMap().getSelectedLight().bufferedImage.getHeight();
				int r = getMap().getSelectedLight().radiusPixels1X();

				int boxwidth = selectedLight.wP();
				int boxheight = selectedLight.hP();

				G.drawImage(getMap().getSelectedLight().bufferedImage,(movedMapX-r)*zoom/8,(movedMapY-r)*zoom/8,w*zoom/8,h*zoom/8, this);
				G.drawRect((movedMapX)*zoom/8,(movedMapY)*zoom/8,boxwidth*zoom/8,boxheight*zoom/8);
				return;
			}

			if(doorDragged)
			{
				repaint();
				Graphics G = getGraphics();
				G.translate(drawOffsetX(),drawOffsetY());
				G.setColor(Color.GREEN);

				int w = selectedDoor.wP();
				int h = selectedDoor.hP();

				G.drawImage(selectedDoor.getImage(),movedTileX*zoom,movedTileY*zoom,w*zoom/8,h*zoom/8, this);
				G.drawRect(movedTileX*zoom,movedTileY*zoom,w*zoom/8,h*zoom/8);

				return;
			}

			if(doorArrivalDragged)
			{
				repaint();
				Graphics G = getGraphics();
				G.translate(drawOffsetX(),drawOffsetY());
				G.setColor(new Color(200,0,255));
				int w = 8;
				int h = 8;
				G.drawRect((movedTileX)*zoom,(movedTileY)*zoom,w*zoom/8,h*zoom/8);
				return;
			}

			if(entityDragged)
			{
				repaint();
				Graphics G = getGraphics();
				G.translate(drawOffsetX(),drawOffsetY());
				G.setColor(Color.GREEN);

				int w = (int)(selectedEntity.wP());
				int h = (int)(selectedEntity.hP());
				//draw selected sprite under cursor
				if(moveEntityByPixel)
				{
					G.drawImage(selectedEntity.getImage(),movedMapX*zoom/8,movedMapY*zoom/8,w*zoom/8,h*zoom/8, this);
					G.drawRect(movedMapX*zoom/8, movedMapY*zoom/8,w*zoom/8,h*zoom/8);
				}
				else
				{
					G.drawImage(selectedEntity.getImage(), movedTileX*zoom, movedTileY*zoom,w*zoom/8,h*zoom/8, this);
					G.drawRect(movedTileX*zoom, movedTileY*zoom,w*zoom/8,h*zoom/8);
				}

				return;
			}

			if(selectionDragged)
			{

				//draw selection box under cursor
				repaint();
				Graphics G = getGraphics();
				G.translate(drawOffsetX(),drawOffsetY());
				G.setColor(new Color(255,0,0,255));

				G.drawRect(movedTileX*zoom-(mousePressedX/zoom-mapSelectionArea.x1)*zoom,movedTileY*zoom-(mousePressedY/zoom-mapSelectionArea.y1)*zoom,mapSelectionArea.getWidth()*zoom,mapSelectionArea.getHeight()*zoom);

				return;
			}



			//repeat click to draw tiles as the mouse drags, but not if we're dragging a selection (returns above)
			mouseClicked(originalME);
		}




	}




	//===============================================================================================
	public void actionPerformed(ActionEvent ae)
	{//===============================================================================================

		//handle clicking on mapsprite right click menu

		/*if(selectedLayer==MapData.SPRITE_LAYER)
		{
			for(int n=0;n<E.project.getNumSprites();n++)
			{
				if(ae.getSource()==spritePopupItem[n])
				{
					//add new mapsprite at xy
					getMap().createEntity(n,clickedTileX*8,clickedTileY*8);

					entityPopup.setVisible(false);

					entityWindow.showEntityWindow();

					//buffered:
					//here i only need to refresh the map sprite layer buffer
					//then i need to redraw all the layers
					if(useLayerImageBuffer)
					{
						getMap().updateLayerBufferImage(MapData.SPRITE_LAYER);
						drawBufferedLayerImagesIntoMapCanvasImage();

						repaint();
					}

					//unbuffered:
					//i need to redraw the mapcanvas, but only where the sprites are, really.
					//might be fastest to actually repaint tile xy where the sprites are, especially for huge maps.
					if(!useLayerImageBuffer)
					{
						int sx = getMap().getSelectedEntity().mapX/8;
						int sy = getMap().getSelectedEntity().mapY/8;
						int sw = getMap().getSelectedEntity().sprite.getWidth()/8;
						int sh = getMap().getSelectedEntity().sprite.getHeight()/8;


						for(int x=sx;x<sx+sw;x++)
						for(int y=sy;y<sy+sh;y++)
							paintTileXY(MapData.SPRITE_LAYER,x,y);

						repaint();
					}
				}
			}
		}

		if(selectedLayer==MapData.DOORSPRITE_LAYER)
		{
			//handle doorsprite right click
			for(int n=0;n<E.project.getNumSprites();n++)
			{
				if(spritePopupItem[n]!=null&&ae.getSource()==spritePopupItem[n])
				{
					//add new door at xy
					getMap().createDoor(spritePopupItem[n].getText(),clickedTileX*8,clickedTileY*8);

					entityPopup.setVisible(false);

					doorWindow.showDoorWindow();

					//buffered:
					//here i only need to refresh the map sprite layer buffer
					//then i need to redraw all the layers
					if(useLayerImageBuffer)
					{
						getMap().updateLayerBufferImage(MapData.DOORSPRITE_LAYER);
						drawBufferedLayerImagesIntoMapCanvasImage();

						repaint();
					}

					//unbuffered:
					//i need to redraw the mapcanvas, but only where the sprites are, really.
					//might be fastest to actually repaint tile xy where the sprites are, especially for huge maps.
					if(!useLayerImageBuffer)
					{
						int sx = getMap().getSelectedDoor().mapX/8;
						int sy = getMap().getSelectedDoor().mapY/8;
						int sw = getMap().getSelectedDoor().sprite.getWidth()/8;
						int sh = getMap().getSelectedDoor().sprite.getHeight()/8;


						for(int x=sx;x<sx+sw;x++)
						for(int y=sy;y<sy+sh;y++)
							paintTileXY(MapData.DOORSPRITE_LAYER,x,y);

						repaint();
					}
				}
			}


		}*/

		if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_ENTITY_LAYER].isSelected()==true)
		{
			for(int n=0;n<getMap().getNumEntities();n++)
			{

				Entity m = getMap().getEntity(n);

				if(ae.getSource() == m.frameTimer)
				{
					//draw current frame into mapcanvas.
					Graphics G = getGraphics();
					G.translate(drawOffsetX(),drawOffsetY());
					G.drawImage(m.getSprite().getFrameImage(m.currentAnimationFrame),(int)(m.xP()*(zoom/8.0f)),(int)(m.yP()*(zoom/8.0f)),(int)(m.wP()*(zoom/8.0f)),(int)(m.hP()*(zoom/8.0f)),this);


					//increment current frame
					m.currentAnimationFrame++;

					//if we're the last frame, set frame to 0, stop frameTimer
					if(m.currentAnimationFrame>=m.getSprite().frames())
					{
						m.currentAnimationFrame=0;
						m.frameTimer.stop();
						if(m.randomUpToTicksBetweenAnimationLoop())m.startAnimationTimer.setInitialDelay((int)(Math.random()*(m.ticksBetweenAnimationLoop()+1)));
						m.startAnimationTimer.start();
					}
				}

				if(ae.getSource() == m.startAnimationTimer)
				{
					//start frameTimer
					m.frameTimer.start();
					m.startAnimationTimer.stop();
				}
			}
		}


		//****done in mapChoice();
		//when map loads, go through all mapsprites, set timers to this ActionEventListener
		//when map unloads, turn off all mapsprite timers


		//System.out.println(ae.toString());
	}


	//===============================================================================================
	public void sendSelectionToMTE()
	{//===============================================================================================

		if(MapData.isTileLayer(selectedLayer)==false)return;

		int tls[][] = new int[mapSelectionArea.getWidth()][mapSelectionArea.getHeight()];

		for(int ty = 0; ty < mapSelectionArea.getHeight(); ty++)
		{
			for(int tx = 0; tx < mapSelectionArea.getWidth(); tx++)
			{
				tls[tx][ty] = getMap().getTileIndex(selectedLayer, mapSelectionArea.getX() + tx, mapSelectionArea.getY() + ty);
			}
		}

		EditorMain.multipleTileEditor.show(tls, mapSelectionArea.getWidth(), mapSelectionArea.getHeight());

		EditorMain.infoLabel.setTextSuccess("MapCanvas: Sent selected tiles to MTE");

	}

	//===============================================================================================
	public void sendSelectedLayerToMTEAsNewTilesAndReplaceExistingTiles()
	{//===============================================================================================


		int w = mapSelectionArea.getWidth();
		int h = mapSelectionArea.getHeight();

		int l = selectedLayer;

		if(MapData.isTileLayer(l)==false)return;
		if(l==MapData.MAP_HIT_LAYER)return;
		//if(l==Map.LIGHTS_MASK_LAYER)return;
		if(l==MapData.MAP_CAMERA_BOUNDS_LAYER)return;
		if(l==MapData.MAP_SHADER_LAYER)return;

		//only copy layers that are turned on
		if(!EditorMain.controlPanel.showLayerCheckbox[l].isSelected())return;


		EditorMain.tileCanvas.tileSelected = Project.tileset.num_Tiles;

		Project.tileset.setNumTiles(Project.tileset.num_Tiles + 1 + ((w / TileCanvas.WIDTH_TILES) + 1) * h * TileCanvas.WIDTH_TILES);


		EditorMain.tileCanvas.scrollToSelectedTile();

		int tls[][] = new int[w][h];


			for(int ty = 0; ty < h; ty++)
				for(int tx = 0; tx < w; tx++)
					for(int x = 0; x < 8; x++)
						for(int y = 0; y < 8; y++)
						{

							int oldTileIndex = getMap().getTileIndex(l, mapSelectionArea.getX() + tx, mapSelectionArea.getY() + ty);
							int newTileIndex = EditorMain.tileCanvas.tileSelected + ((((tx / TileCanvas.WIDTH_TILES)) * h) * TileCanvas.WIDTH_TILES) + (ty * TileCanvas.WIDTH_TILES) + (tx % TileCanvas.WIDTH_TILES);

							//if the pixel isn't clear
							if(Project.tileset.tilePaletteIndex[oldTileIndex][x][y] != 0)
							{

								//if it's a shadow layer, have to blend
								if(l == MapData.MAP_GROUND_SHADOW_LAYER|| l == MapData.MAP_OBJECT_SHADOW_LAYER|| l == MapData.MAP_SPRITE_SHADOW_LAYER)
								{
									//get color from previous layer
									int p = Project.tileset.tilePaletteIndex[newTileIndex][x][y];


									//get hsb values for that color
									float hsbf[] = new float[3];
									hsbf[0] = (float) Project.getSelectedPalette().hsbi[p][0] / (float)maxRGBValue;
									hsbf[1] = (float) Project.getSelectedPalette().hsbi[p][1] / (float)maxRGBValue;
									hsbf[2] = (float) Project.getSelectedPalette().hsbi[p][2] / (float)maxRGBValue;

									//get new java color for those hsb values with half brightness so it's similar to shadow color
									Color col = Color.getHSBColor(hsbf[0], hsbf[1], hsbf[2] * 0.4f);

									//find color similar to the shadow color using those rgb values
									int shadowcolor = Project.getSelectedPalette().getColorIfExistsOrAddColor((int) col.getRed(), (int) col.getGreen(), (int) col.getBlue(), 30);

									//set the shadow pixel to that value whee
									Project.tileset.tilePaletteIndex[newTileIndex][x][y] = shadowcolor;

								}
								else
								{
									Project.tileset.tilePaletteIndex[newTileIndex][x][y] = Project.tileset.tilePaletteIndex[oldTileIndex][x][y];
								}
							}
						}


		for(int ty = 0; ty < h; ty++)
		{
			for(int tx = 0; tx < w; tx++)
			{
				int newTileIndex = EditorMain.tileCanvas.tileSelected + ((((tx / TileCanvas.WIDTH_TILES)) * h) * TileCanvas.WIDTH_TILES) + (ty * TileCanvas.WIDTH_TILES) + (tx % TileCanvas.WIDTH_TILES);
				tls[tx][ty] = newTileIndex;
			}
		}


		//now copy those new tiles into the selected layer
		for(int ty = 0; ty < mapSelectionArea.getHeight(); ty++)
		{
			for(int tx = 0; tx < mapSelectionArea.getWidth(); tx++)
			{

				int tileindex = EditorMain.tileCanvas.tileSelected + ((((tx / TileCanvas.WIDTH_TILES)) * mapSelectionArea.getHeight()) * TileCanvas.WIDTH_TILES) + (ty * TileCanvas.WIDTH_TILES) + (tx % TileCanvas.WIDTH_TILES);

				int maptilex = mapSelectionArea.getX() + tx;
				int maptiley = mapSelectionArea.getY() + ty;


				if(!Project.tileset.isTileBlank(tileindex))
				{
					//if the tile isn't blank, then use the newly made one
					getMap().setTileIndex(l,maptilex,maptiley,tileindex);
					paintTileXY(l, maptilex,maptiley);

				}
				else
				{
					//if it is blank, then use tile 0
					getMap().setTileIndex(l,maptilex,maptiley,0);
					paintTileXY(l, maptilex,maptiley);
				}

			}
		}

		EditorMain.infoLabel.setTextError("MapCanvas: Sent selected tiles to MTE as NEW TILES");

		EditorMain.tileCanvas.setSizedoLayout();
		EditorMain.tileCanvas.updateAllTiles();
		//E.tileCanvas.paintBuffer();
		EditorMain.tileCanvas.paint();

		EditorMain.multipleTileEditor.show(tls, w, h);
	}

	//===============================================================================================
	public void sendCombinedLayersToMTEAsNewTiles()
	{//===============================================================================================


		int w = mapSelectionArea.getWidth();
		int h = mapSelectionArea.getHeight();



		EditorMain.tileCanvas.tileSelected = Project.tileset.num_Tiles;

		Project.tileset.setNumTiles(Project.tileset.num_Tiles + 1 + ((w / TileCanvas.WIDTH_TILES) + 1) * h * TileCanvas.WIDTH_TILES);

		EditorMain.tileCanvas.scrollToSelectedTile();

		int tls[][] = new int[w][h];

		for(int l = 0; l < MapData.layers; l++)
		{
			//skip layers in loop
			if(MapData.isTileLayer(l)==false)continue;
			if(l==MapData.MAP_HIT_LAYER)continue;
			if(l==MapData.MAP_LIGHT_MASK_LAYER)continue;
			if(l==MapData.MAP_CAMERA_BOUNDS_LAYER)continue;
			if(l==MapData.MAP_SHADER_LAYER)continue;


			//only copy layers that are turned on
			if(!EditorMain.controlPanel.showLayerCheckbox[l].isSelected())continue;

			for(int ty = 0; ty < h; ty++)
				for(int tx = 0; tx < w; tx++)
					for(int x = 0; x < 8; x++)
						for(int y = 0; y < 8; y++)
						{

							int oldTileIndex = getMap().getTileIndex(l, mapSelectionArea.getX() + tx, mapSelectionArea.getY() + ty);
							int newTileIndex = EditorMain.tileCanvas.tileSelected + ((((tx / TileCanvas.WIDTH_TILES)) * h) * TileCanvas.WIDTH_TILES) + (ty * TileCanvas.WIDTH_TILES) + (tx % TileCanvas.WIDTH_TILES);

							//if the pixel isn't clear
							if(Project.tileset.tilePaletteIndex[oldTileIndex][x][y] != 0)
							{

								//if it's a shadow layer, have to blend
								if(l == MapData.MAP_GROUND_SHADOW_LAYER|| l == MapData.MAP_OBJECT_SHADOW_LAYER|| l == MapData.MAP_SPRITE_SHADOW_LAYER)
								{
									//get color from previous layer
									int p = Project.tileset.tilePaletteIndex[newTileIndex][x][y];


									//get hsb values for that color
									float hsbf[] = new float[3];
									hsbf[0] = (float) Project.getSelectedPalette().hsbi[p][0] / (float)maxRGBValue;
									hsbf[1] = (float) Project.getSelectedPalette().hsbi[p][1] / (float)maxRGBValue;
									hsbf[2] = (float) Project.getSelectedPalette().hsbi[p][2] / (float)maxRGBValue;

									//get new java color for those hsb values with half brightness so it's similar to shadow color
									Color col = Color.getHSBColor(hsbf[0], hsbf[1], hsbf[2] * 0.4f);

									//find color similar to the shadow color using those rgb values
									int shadowcolor = Project.getSelectedPalette().getColorIfExistsOrAddColor((int) col.getRed(), (int) col.getGreen(), (int) col.getBlue(), 30);

									//set the shadow pixel to that value whee
									Project.tileset.tilePaletteIndex[newTileIndex][x][y] = shadowcolor;

								}
								else
								{
									Project.tileset.tilePaletteIndex[newTileIndex][x][y] = Project.tileset.tilePaletteIndex[oldTileIndex][x][y];
								}
							}
						}




		}

		for(int ty = 0; ty < h; ty++)
		{
			for(int tx = 0; tx < w; tx++)
			{
				int newTileIndex = EditorMain.tileCanvas.tileSelected + ((((tx / TileCanvas.WIDTH_TILES)) * h) * TileCanvas.WIDTH_TILES) + (ty * TileCanvas.WIDTH_TILES) + (tx % TileCanvas.WIDTH_TILES);
				tls[tx][ty] = newTileIndex;
			}
		}

		EditorMain.infoLabel.setTextError("MapCanvas: Sent COMBINED LAYERS to MTE as NEW TILES");

		EditorMain.tileCanvas.setSizedoLayout();
		EditorMain.tileCanvas.updateAllTiles();
		//E.tileCanvas.paintBuffer();
		EditorMain.tileCanvas.paint();

		EditorMain.multipleTileEditor.show(tls, w, h);
	}


	//===============================================================================================
	public void combineSelectedTilesOnActiveLayersIntoNewTilesOnTheLowestLayer()
	{//===============================================================================================
			EditorMain.tileCanvas.tileSelected = Project.tileset.num_Tiles;

			Project.tileset.setNumTiles(Project.tileset.num_Tiles + 1 + ((mapSelectionArea.getWidth() / TileCanvas.WIDTH_TILES) + 1) * mapSelectionArea.getHeight() * TileCanvas.WIDTH_TILES);


			EditorMain.tileCanvas.scrollToSelectedTile();



			int bottommost_layer=MapData.layers;

			for(int l = 0; l < MapData.layers; l++)
			{
				//skip layers in loop
				if(MapData.isTileLayer(l)==false)continue;
				if(l==MapData.MAP_HIT_LAYER)continue;
				if(l==MapData.MAP_CAMERA_BOUNDS_LAYER)continue;
				if(l==MapData.MAP_SHADER_LAYER)continue;
				if(l==MapData.MAP_LIGHT_MASK_LAYER)continue;

				//skip shadow layers
				if(l==MapData.MAP_GROUND_SHADOW_LAYER)continue;
				if(l==MapData.MAP_OBJECT_SHADOW_LAYER)continue;
				if(l==MapData.MAP_SPRITE_SHADOW_LAYER)continue;


				//only copy layers that are turned on
				if(!EditorMain.controlPanel.showLayerCheckbox[l].isSelected())continue;


				if(l<bottommost_layer)bottommost_layer=l;

				//for each layer, copy the tile pixels into the new tiles, overwriting previous pixels
				for(int ty = 0; ty < mapSelectionArea.getHeight(); ty++)
					for(int tx = 0; tx < mapSelectionArea.getWidth(); tx++)
						for(int x = 0; x < 8; x++)
							for(int y = 0; y < 8; y++)
							{
								int oldTileIndex = getMap().getTileIndex(l, mapSelectionArea.getX() + tx, mapSelectionArea.getY() + ty);
								int newTileIndex = EditorMain.tileCanvas.tileSelected + ((((tx / TileCanvas.WIDTH_TILES)) * mapSelectionArea.getHeight()) * TileCanvas.WIDTH_TILES) + (ty * TileCanvas.WIDTH_TILES) + (tx % TileCanvas.WIDTH_TILES);

								if(Project.tileset.tilePaletteIndex[oldTileIndex][x][y] != 0)
								{
										Project.tileset.tilePaletteIndex[newTileIndex][x][y] = Project.tileset.tilePaletteIndex[oldTileIndex][x][y];
								}
							}



			}

			//now copy those new tiles into the bottom layer
			for(int ty = 0; ty < mapSelectionArea.getHeight(); ty++)
			{
				for(int tx = 0; tx < mapSelectionArea.getWidth(); tx++)
				{

					int tileindex = EditorMain.tileCanvas.tileSelected + ((((tx / TileCanvas.WIDTH_TILES)) * mapSelectionArea.getHeight()) * TileCanvas.WIDTH_TILES) + (ty * TileCanvas.WIDTH_TILES) + (tx % TileCanvas.WIDTH_TILES);

					int maptilex = mapSelectionArea.getX() + tx;
					int maptiley = mapSelectionArea.getY() + ty;


					if(!Project.tileset.isTileBlank(tileindex))
					{
						//if the tile isn't blank, then use the newly made one
						getMap().setTileIndex(bottommost_layer,maptilex,maptiley,tileindex);
						paintTileXY(bottommost_layer, maptilex,maptiley);

					}
					else
					{
						//if it is blank, then use tile 0
						getMap().setTileIndex(bottommost_layer,maptilex,maptiley,0);
						paintTileXY(bottommost_layer, maptilex,maptiley);
					}


					//now delete all the layers above bottommost layer
					for(int l=bottommost_layer+1;l<MapData.layers;l++)
					{

						if(MapData.isTileLayer(l)==false)continue;
						if(l==MapData.MAP_LIGHT_MASK_LAYER)continue;
						if(l==MapData.MAP_HIT_LAYER)continue;
						if(l==MapData.MAP_CAMERA_BOUNDS_LAYER)continue;
						if(l==MapData.MAP_SHADER_LAYER)continue;

						//skip shadow layers
						if(l==MapData.MAP_GROUND_SHADOW_LAYER)continue;
						if(l==MapData.MAP_OBJECT_SHADOW_LAYER)continue;
						if(l==MapData.MAP_SPRITE_SHADOW_LAYER)continue;

						//only visible layers
						if(!EditorMain.controlPanel.showLayerCheckbox[l].isSelected())continue;



						getMap().setTileIndex(l,maptilex,maptiley,0);
						paintTileXY(l, maptilex,maptiley);
					}

				}
			}


			EditorMain.tileCanvas.setSizedoLayout();
			EditorMain.tileCanvas.updateAllTiles();
			//E.tileCanvas.paintBuffer();
			EditorMain.tileCanvas.paint();

			updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();
			repaint();

			//need to set the status bar for this
			EditorMain.infoLabel.setTextSuccess("MapCanvas: Mashed all enabled layers down to new tiles on bottommost enabled layer.");
	}

	//===============================================================================================
	public void combineSelectedTilesOnActiveLayersIntoFlippedShadowTilesOnSelectedShadowLayer()
	{//===============================================================================================


		if(
				selectedLayer!=MapData.MAP_GROUND_SHADOW_LAYER&&
				selectedLayer!=MapData.MAP_OBJECT_SHADOW_LAYER&&
				selectedLayer!=MapData.MAP_SPRITE_SHADOW_LAYER
		)
		{
			EditorMain.infoLabel.setTextError("MapCanvas: Must select a SHADOW LAYER to draw on!!");
			return;
		}

		EditorMain.tileCanvas.tileSelected = Project.tileset.num_Tiles;

		Project.tileset.setNumTiles(Project.tileset.num_Tiles + 1 + ((mapSelectionArea.getWidth() / TileCanvas.WIDTH_TILES) + 1) * mapSelectionArea.getHeight() * TileCanvas.WIDTH_TILES);


		EditorMain.tileCanvas.scrollToSelectedTile();

		for(int l = 0; l < MapData.layers; l++)
		{
			//skip layers in loop
			if(MapData.isTileLayer(l)==false)continue;
			if(l==MapData.MAP_HIT_LAYER)continue;
			if(l==MapData.MAP_CAMERA_BOUNDS_LAYER)continue;
			if(l==MapData.MAP_SHADER_LAYER)continue;
			if(l==MapData.MAP_LIGHT_MASK_LAYER)continue;

			//skip shadow layers
			if(l==MapData.MAP_GROUND_SHADOW_LAYER)continue;
			if(l==MapData.MAP_OBJECT_SHADOW_LAYER)continue;
			if(l==MapData.MAP_SPRITE_SHADOW_LAYER)continue;


			//only copy layers that are turned on
			if(!EditorMain.controlPanel.showLayerCheckbox[l].isSelected())continue;




			//for each layer, copy the tile pixels into the new tiles, overwriting previous pixels
			for(int ty = 0; ty < mapSelectionArea.getHeight(); ty++)
				for(int tx = 0; tx < mapSelectionArea.getWidth(); tx++)
					for(int x = 0; x < 8; x++)
						for(int y = 0; y < 8; y++)
						{
							int oldTileIndex = getMap().getTileIndex(l, mapSelectionArea.getX() + tx, mapSelectionArea.getY() + ty);
							int newTileIndex = EditorMain.tileCanvas.tileSelected + ((((tx / TileCanvas.WIDTH_TILES)) * mapSelectionArea.getHeight()) * TileCanvas.WIDTH_TILES) + (ty * TileCanvas.WIDTH_TILES) + (tx % TileCanvas.WIDTH_TILES);

							if(Project.tileset.tilePaletteIndex[oldTileIndex][x][y] != 0)
							{
								//7-y for FLIPPED
								Project.tileset.tilePaletteIndex[newTileIndex][x][7-y] = 1;//E.project.tileset.tileData[oldTileIndex][x][y];
							}
						}



		}


		//now move the selection area to the bottom tile of the selected area
		mapSelectionArea.moveSelectionBoxPositionByAmt(0, mapSelectionArea.getHeight()-1);

		//now copy those new tiles into the bottom layer
		for(int ty = 0; ty < mapSelectionArea.getHeight(); ty++)
		{
			for(int tx = 0; tx < mapSelectionArea.getWidth(); tx++)
			{

				int tileindex = EditorMain.tileCanvas.tileSelected + ((((tx / TileCanvas.WIDTH_TILES)) * mapSelectionArea.getHeight()) * TileCanvas.WIDTH_TILES) + (ty * TileCanvas.WIDTH_TILES) + (tx % TileCanvas.WIDTH_TILES);

				int maptilex = mapSelectionArea.getX() + tx;
				int maptiley = mapSelectionArea.getY() + (mapSelectionArea.getHeight()-1)-ty;//mapselectionarea.getheight-1-ty = flipped upside down


				if(!Project.tileset.isTileBlank(tileindex))
				{
					//if the tile isn't blank, then use the newly made one
					getMap().setTileIndex(selectedLayer,maptilex,maptiley,tileindex);
					paintTileXY(selectedLayer, maptilex,maptiley);

				}
				else
				{
					//if it is blank, then use tile 0
					getMap().setTileIndex(selectedLayer,maptilex,maptiley,0);
					paintTileXY(selectedLayer, maptilex,maptiley);
				}


			}
		}


		EditorMain.tileCanvas.setSizedoLayout();
		EditorMain.tileCanvas.updateAllTiles();
		//E.tileCanvas.paintBuffer();
		EditorMain.tileCanvas.paint();

		updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();
		repaint();

		//need to set the status bar for this
		EditorMain.infoLabel.setTextSuccess("MapCanvas: Combined all enabled layers to new FLIPPED SHADOW tiles on SELECTED SHADOW layer.");

	}


	//===============================================================================================
	public void shiftSelectedTilesUpALayer()
	{//===============================================================================================

		//dont care if the next layer is enabled or not (so can shift tiles to a disabled layer)
		//but dont shift the tiles onto a layer that has tiles in it already


		int next_layer_not_empty=0;
		int target_layer=0;


		if(MapData.isTileLayer(selectedLayer)==false)return;
		if(selectedLayer==MapData.MAP_LIGHT_MASK_LAYER)return;
		if(selectedLayer==MapData.MAP_HIT_LAYER)return;
		if(selectedLayer==MapData.MAP_CAMERA_BOUNDS_LAYER)return;
		if(selectedLayer==MapData.MAP_SHADER_LAYER)return;

		//skip shadow layers
		if(selectedLayer==MapData.MAP_GROUND_SHADOW_LAYER)return;
		if(selectedLayer==MapData.MAP_OBJECT_SHADOW_LAYER)return;
		if(selectedLayer==MapData.MAP_SPRITE_SHADOW_LAYER)return;

		if(selectedLayer==MapData.MAP_GROUND_LAYER)target_layer=MapData.MAP_GROUND_DETAIL_LAYER;
		if(selectedLayer==MapData.MAP_GROUND_DETAIL_LAYER)target_layer=MapData.MAP_OBJECT_LAYER;
		if(selectedLayer==MapData.MAP_SHADER_LAYER)return;
		if(selectedLayer==MapData.MAP_GROUND_SHADOW_LAYER)return;
		if(selectedLayer==MapData.MAP_OBJECT_LAYER)target_layer=MapData.MAP_OBJECT_DETAIL_LAYER;
		if(selectedLayer==MapData.MAP_OBJECT_DETAIL_LAYER)target_layer=MapData.MAP_ABOVE_LAYER;
		if(selectedLayer==MapData.MAP_OBJECT_SHADOW_LAYER)return;
		if(selectedLayer==MapData.MAP_ABOVE_LAYER)target_layer=MapData.MAP_ABOVE_DETAIL_LAYER;
		if(selectedLayer==MapData.MAP_ABOVE_DETAIL_LAYER)return;

		if(mapSelectionArea.isShowing)
		{

			//check the selected tiles on the next layer
			for(int ty = 0; ty < mapSelectionArea.getHeight(); ty++)
			{
				for(int tx = 0; tx < mapSelectionArea.getWidth(); tx++)
				{

					//int maptilex = mapSelectionArea.getX() + tx;
					//int maptiley = mapSelectionArea.getY() + ty;

					int tileindex = getMap().getTileIndex(target_layer, mapSelectionArea.getX() + tx, mapSelectionArea.getY() + ty);
					if(tileindex!=0)next_layer_not_empty=1;
				}
			}

			if(next_layer_not_empty==1)
			{
				//status: tried to move selected tiles up a layer but the layer is not empty
				EditorMain.infoLabel.setTextError("MapCanvas: Tried to move selected tiles up to Layer "+target_layer+" ("+EditorMain.controlPanel.layerLabel[target_layer].getText()+") but Layer is not empty!");

			}
			else
			{
				CompoundEdit edit = new CompoundEdit();

				//if its all empty, move them up
				for(int ty = 0; ty < mapSelectionArea.getHeight(); ty++)
				{
					for(int tx = 0; tx < mapSelectionArea.getWidth(); tx++)
					{

						int maptilex = mapSelectionArea.getX() + tx;
						int maptiley = mapSelectionArea.getY() + ty;

						int tileindex = getMap().getTileIndex(selectedLayer, maptilex, maptiley);
						
						if(tileindex != 0) {
							edit.addEdit(new TileChangeEdit(this, target_layer, maptilex, maptiley, 0, tileindex));
							getMap().setTileIndex(target_layer, maptilex, maptiley, tileindex);
							paintTileXY(target_layer, maptilex,maptiley);
							
							edit.addEdit(new TileChangeEdit(this, selectedLayer, maptilex, maptiley, tileindex, 0));
							getMap().setTileIndex(selectedLayer, maptilex, maptiley, 0);
							paintTileXY(selectedLayer, maptilex,maptiley);
						}
					}
				}
				
				edit.end();
				if(edit.isSignificant()) undoManager.addEdit(edit);


				//set the status bar: moved selected tiles up a layer
				EditorMain.infoLabel.setTextSuccess("MapCanvas: Moved selected tiles up to Layer "+target_layer+" ("+EditorMain.controlPanel.layerLabel[target_layer].getText()+")");

			}

		}
		repaint();
	}

	//===============================================================================================
	public void shiftSelectedTilesDownALayer()
	{//===============================================================================================

		//dont care if the next layer is enabled or not (so can shift tiles to a disabled layer)
		//but dont shift the tiles onto a layer that has tiles in it already


		int next_layer_not_empty=0;
		int target_layer=0;

		if(MapData.isTileLayer(selectedLayer)==false)return;
		if(selectedLayer==MapData.MAP_LIGHT_MASK_LAYER)return;
		if(selectedLayer==MapData.MAP_HIT_LAYER)return;
		if(selectedLayer==MapData.MAP_CAMERA_BOUNDS_LAYER)return;
		if(selectedLayer==MapData.MAP_SHADER_LAYER)return;

		//skip shadow layers
		if(selectedLayer==MapData.MAP_GROUND_SHADOW_LAYER)return;
		if(selectedLayer==MapData.MAP_OBJECT_SHADOW_LAYER)return;
		if(selectedLayer==MapData.MAP_SPRITE_SHADOW_LAYER)return;

		if(selectedLayer==MapData.MAP_GROUND_LAYER)return;
		if(selectedLayer==MapData.MAP_GROUND_DETAIL_LAYER)target_layer=MapData.MAP_GROUND_LAYER;
		if(selectedLayer==MapData.MAP_SHADER_LAYER)return;
		if(selectedLayer==MapData.MAP_GROUND_SHADOW_LAYER)return;
		if(selectedLayer==MapData.MAP_OBJECT_LAYER)target_layer=MapData.MAP_GROUND_DETAIL_LAYER;
		if(selectedLayer==MapData.MAP_OBJECT_DETAIL_LAYER)target_layer=MapData.MAP_OBJECT_LAYER;
		if(selectedLayer==MapData.MAP_OBJECT_SHADOW_LAYER)return;
		if(selectedLayer==MapData.MAP_ABOVE_LAYER)target_layer=MapData.MAP_OBJECT_DETAIL_LAYER;
		if(selectedLayer==MapData.MAP_ABOVE_DETAIL_LAYER)target_layer=MapData.MAP_ABOVE_LAYER;


		if(mapSelectionArea.isShowing)
		{

			//check the selected tiles on the next layer
			for(int ty = 0; ty < mapSelectionArea.getHeight(); ty++)
			{
				for(int tx = 0; tx < mapSelectionArea.getWidth(); tx++)
				{

					//int maptilex = mapSelectionArea.getX() + tx;
					//int maptiley = mapSelectionArea.getY() + ty;

					int tileindex = getMap().getTileIndex(target_layer, mapSelectionArea.getX() + tx, mapSelectionArea.getY() + ty);
					if(tileindex!=0)next_layer_not_empty=1;
				}
			}

			if(next_layer_not_empty==1)
			{

				EditorMain.infoLabel.setTextError("MapCanvas: Tried to move selected tiles down to Layer "+target_layer+" ("+EditorMain.controlPanel.layerLabel[target_layer].getText()+") but Layer is not empty!");
			}
			else
			{
				CompoundEdit edit = new CompoundEdit();

				//if its all empty, move them up
				for(int ty = 0; ty < mapSelectionArea.getHeight(); ty++)
				{
					for(int tx = 0; tx < mapSelectionArea.getWidth(); tx++)
					{

						int maptilex = mapSelectionArea.getX() + tx;
						int maptiley = mapSelectionArea.getY() + ty;

						int tileindex = getMap().getTileIndex(selectedLayer, maptilex, maptiley);
						
						if(tileindex != 0) {
							edit.addEdit(new TileChangeEdit(this, target_layer, maptilex, maptiley, 0, tileindex));
							getMap().setTileIndex(target_layer, maptilex, maptiley, tileindex);
							paintTileXY(target_layer, maptilex,maptiley);
							
							edit.addEdit(new TileChangeEdit(this, selectedLayer, maptilex, maptiley, tileindex, 0));
							getMap().setTileIndex(selectedLayer, maptilex, maptiley, 0);
							paintTileXY(selectedLayer, maptilex,maptiley);
						}
					}
				}

				edit.end();
				if(edit.isSignificant()) undoManager.addEdit(edit);

				EditorMain.infoLabel.setTextSuccess("MapCanvas: Moved selected tiles down to Layer "+target_layer+" ("+EditorMain.controlPanel.layerLabel[target_layer].getText()+")");

			}

		}
		repaint();
	}


	//===============================================================================================
	public void outputEnabledLayersToTexturedMesh(String dirpath)
	{//===============================================================================================



		//press key get popup window asking for name of mesh
			int tx1 = mapSelectionArea.x1;
			int tx2 = mapSelectionArea.x2;

			int ty1 = mapSelectionArea.y1;
			int ty2 = mapSelectionArea.y2;

			StringDialog sw = new StringDialog(new Frame(), "name of mesh");
			sw.show("");

			String texname = sw.newName.getText();
			//String l = n.substring(0, 1);
			//String f = l.toUpperCase() + n.substring(1);


		//take visible layers, combine them into one image with transparency at 2x scale


			//TODO: do this at hq2x (hq2x full map, float coordinates, clip from full image)


			int selectionwidth = (tx2-tx1)*8;
			int selectionheight = (ty2-ty1)*8;

			int imagewidth = selectionwidth*2;
			int imageheight = selectionheight*2;

			BufferedImage image = E.getGraphicsConfiguration().createCompatibleImage(imagewidth, imageheight, Transparency.TRANSLUCENT);


			Graphics g = image.getGraphics();
			g.setColor(new Color(0, 0, 0, 0));
			g.fillRect(0, 0, imagewidth, imageheight);


			//draw transparent tile for each enabled layer into image

				//for each enabled layer (not counting shadows or aux layers)

				//for each tile in mapSelectionArea area

				//for each pixel in tile

				//if pixel is color 0 dont draw

				//else draw (at 2x size)

				for(int l=0; l<MapData.layers; l++)
				{

					//skip aux layers

					//valid layers = 0,1,(2),4,5,(6),7,8
					//invalid layers = 3,9,10,11

					if(
							MapData.isTileLayer(l)==false ||
							l == MapData.MAP_HIT_LAYER||
							l == MapData.MAP_LIGHT_MASK_LAYER||
							//l == SHADOW_LAYER ||
							l == MapData.MAP_CAMERA_BOUNDS_LAYER||
							//l == MapData.SPRITE_SHADOW_LAYER||
							l == MapData.MAP_SHADER_LAYER
							//l == OBJECTSHADOW_LAYER
						)continue;

					if(!EditorMain.controlPanel.showLayerCheckbox[l].isSelected())continue;


					//9 is lighting
					//10 is camera
					//11 is hit



					int itx=0;//image tile x
					int ity=0;

					//for each mapSelectionArea tile
					for(int sty=ty1;sty<ty2;sty++)//mapSelectionArea tile y
					{
						for(int stx=tx1;stx<tx2;stx++)
						{

							//g.drawImage(ItileTranslucent[], 0, 0, this);

							int tileindex = getMap().layerTileIndex[l][stx][sty];
							if(tileindex!=0)
							{
								//for each pixel in the tile
								for(int py=0;py<8;py++)
									for(int px=0;px<8;px++)
									{
										//get pixel
										int palindex = Project.tileset.tilePaletteIndex[tileindex][px][py];

										//if pixel isnt 0, apply to image
										if(palindex!=0)
										{
											int cr = Project.getSelectedPalette().getRed(palindex);
											int cg = Project.getSelectedPalette().getGreen(palindex);
											int cb = Project.getSelectedPalette().getBlue(palindex);

											if(l == MapData.MAP_GROUND_SHADOW_LAYER|| l == MapData.MAP_OBJECT_SHADOW_LAYER)
											{
												g.setColor(new Color(cr,cg,cb,128));
											}
											else
											{
												g.setColor(new Color(cr,cg,cb));
											}

											//get x and y in image...
											//int imagepixelindex = ((ity*imagewidth*8*2)+itx*8*2)+(py*8*2)+px*2;

											int imagepixelx = (itx*8*2)+(px*2);
											int imagepixely = ((ity*8*2)+(py*2));


											g.fillRect(imagepixelx, imagepixely, 2, 2);
										}
									}
							}

							itx++;
						}

						itx=0;
						ity++;

					}

				}


		//save image as filename MAPfolder/piecename.png

			//if not exist MAPfolder make MAPfolder
			if(dirpath==null)dirpath = EditorMain.exportDirectory;
			Utils.makeDir(dirpath + "tex\\" + getMap().name());



			//save png out

				{
					Iterator<ImageWriter> writers = ImageIO.getImageWritersByFormatName("png");
					ImageWriter writer = (ImageWriter) writers.next();

					FileOutputStream fouts = null;
					File fout = null;
					MemoryCacheImageOutputStream mos = null;

					try
					{
						fout = new File(dirpath + "tex\\" + getMap().name() + "\\" + texname + ".png");


						//while exist name.png name=namenumber.png

						int q=0;
						while(fout.exists())
						{
							texname = texname.concat("" + q);
							fout = new File(dirpath + "tex\\" + getMap().name() + "\\" + texname + ".png");
							q++;
						}

						fouts = new FileOutputStream(fout);
						mos = new MemoryCacheImageOutputStream(fouts);
					}
					catch(FileNotFoundException fnfe){System.out.println("Could not create file.");return;}

					writer.setOutput(mos);
					ImageWriteParam iwp = writer.getDefaultWriteParam();
					try
					{
						writer.write(null, new IIOImage(image, null, null), iwp);//param);
					}
					catch(IllegalStateException IE){System.err.println("The output has not been set.");}
					catch(IllegalArgumentException IAE){System.err.println("Image is null.");}
					catch(IOException IOe){System.err.println("An error occured during writing.");}

					writer.dispose();

					try
					{
						mos.close();
						fouts.close();
					}
					catch(IOException e){}
				}



		//output texture collada referencing this

String colladastring = "<?xml version=\"1.0f\" encoding=\"UTF-8\" standalone=\"no\" ?>"+"\n"+
					"<COLLADA xmlns=\"http://www.collada.org/2005/11/COLLADASchema\" version=\"1.4.1\">"+"\n"+
					"    <asset>"+"\n"+
					"        <contributor>"+"\n"+
					"            <authoring_tool>Google SketchUp 8.0f.4811</authoring_tool>"+"\n"+
					"        </contributor>"+"\n"+
					"        <created>2011-09-08T13:18:23Z</created>"+"\n"+
					"        <modified>2011-09-08T13:18:23Z</modified>"+"\n"+
					"        <unit meter=\"0.0f2539999969303608\" name=\"inch\" />"+"\n"+
					"        <up_axis>Z_UP</up_axis>"+"\n"+
					"    </asset>"+"\n"+
					"    <library_visual_scenes>"+"\n"+
					"        <visual_scene id=\"ID1\">"+"\n"+
					"            <node name=\"SketchUp\">"+"\n"+
					"                <instance_geometry url=\"#ID2\">"+"\n"+
					"                    <bind_material>"+"\n"+
					"                        <technique_common>"+"\n"+
					"                            <instance_material symbol=\"Material2\" target=\"#ID3\">"+"\n"+
					"                                <bind_vertex_input semantic=\"UVSET0\" input_semantic=\"TEXCOORD\" input_set=\"0\" />"+"\n"+
					"                            </instance_material>"+"\n"+
					"                        </technique_common>"+"\n"+
					"                    </bind_material>"+"\n"+
					"                </instance_geometry>"+"\n"+
					"            </node>"+"\n"+
					"        </visual_scene>"+"\n"+
					"    </library_visual_scenes>"+"\n"+
					"    <library_geometries>"+"\n"+
					"        <geometry id=\"ID2\">"+"\n"+
					"            <mesh>"+"\n"+
					"                <source id=\"ID8\">"+"\n"+
					"                    <float_array id=\"ID12\" count=\"12\">" + selectionwidth + " 0 0 " + selectionwidth + " " + selectionheight + " 0 0 " + selectionheight + " 0 0 0 0</float_array>"+"\n"+
					"                    <technique_common>"+"\n"+
					"                        <accessor count=\"4\" source=\"#ID12\" stride=\"3\">"+"\n"+
					"                            <param name=\"X\" type=\"float\" />"+"\n"+
					"                            <param name=\"Y\" type=\"float\" />"+"\n"+
					"                            <param name=\"Z\" type=\"float\" />"+"\n"+
					"                        </accessor>"+"\n"+
					"                    </technique_common>"+"\n"+
					"                </source>"+"\n"+
					"                <source id=\"ID9\">"+"\n"+
					"                    <float_array id=\"ID13\" count=\"12\">-0 -0 1 -0 -0 1 -0 -0 1 -0 -0 1</float_array>"+"\n"+
					"                    <technique_common>"+"\n"+
					"                        <accessor count=\"4\" source=\"#ID13\" stride=\"3\">"+"\n"+
					"                            <param name=\"X\" type=\"float\" />"+"\n"+
					"                            <param name=\"Y\" type=\"float\" />"+"\n"+
					"                            <param name=\"Z\" type=\"float\" />"+"\n"+
					"                        </accessor>"+"\n"+
					"                    </technique_common>"+"\n"+
					"                </source>"+"\n"+
					"                <source id=\"ID11\">"+"\n"+
					"                    <float_array id=\"ID14\" count=\"8\">1 0 1 1 0 1 0 0</float_array>"+"\n"+
					"                    <technique_common>"+"\n"+
					"                        <accessor count=\"4\" source=\"#ID14\" stride=\"2\">"+"\n"+
					"                            <param name=\"S\" type=\"float\" />"+"\n"+
					"                            <param name=\"T\" type=\"float\" />"+"\n"+
					"                        </accessor>"+"\n"+
					"                    </technique_common>"+"\n"+
					"                </source>"+"\n"+
					"                <vertices id=\"ID10\">"+"\n"+
					"                    <input semantic=\"POSITION\" source=\"#ID8\" />"+"\n"+
					"                    <input semantic=\"NORMAL\" source=\"#ID9\" />"+"\n"+
					"                </vertices>"+"\n"+
					"                <polylist count=\"1\" material=\"Material2\">"+"\n"+
					"                    <input offset=\"0\" semantic=\"VERTEX\" source=\"#ID10\" />"+"\n"+
					"                    <input offset=\"1\" semantic=\"TEXCOORD\" source=\"#ID11\" />"+"\n"+
					"                    <vcount>4</vcount>"+"\n"+
					"                    <p>0 0 1 1 2 2 3 3</p>"+"\n"+
					"                </polylist>"+"\n"+
					"            </mesh>"+"\n"+
					"        </geometry>"+"\n"+
					"    </library_geometries>"+"\n"+
					"    <library_materials>"+"\n"+
					"        <material id=\"ID3\" name=\"material_0\">"+"\n"+
					"            <instance_effect url=\"#ID4\" />"+"\n"+
					"        </material>"+"\n"+
					"    </library_materials>"+"\n"+
					"    <library_effects>"+"\n"+
					"        <effect id=\"ID4\">"+"\n"+
					"            <profile_COMMON>"+"\n"+
					"                <newparam sid=\"ID6\">"+"\n"+
					"                    <surface type=\"2D\">"+"\n"+
					"                        <init_from>ID5</init_from>"+"\n"+
					"                    </surface>"+"\n"+
					"                </newparam>"+"\n"+
					"                <newparam sid=\"ID7\">"+"\n"+
					"                    <sampler2D>"+"\n"+
					"                        <source>ID6</source>"+"\n"+
					"                    </sampler2D>"+"\n"+
					"                </newparam>"+"\n"+
					"                <technique sid=\"COMMON\">"+"\n"+
					"                    <lambert>"+"\n"+
					"                        <diffuse>"+"\n"+
					"                            <texture texture=\"ID7\" texcoord=\"UVSET0\" />"+"\n"+
					"                        </diffuse>"+"\n"+
					"                    </lambert>"+"\n"+
					"                </technique>"+"\n"+
					"            </profile_COMMON>"+"\n"+
					"        </effect>"+"\n"+
					"    </library_effects>"+"\n"+
					"    <library_images>"+"\n"+
					"        <image id=\"ID5\">"+"\n"+
					"            <init_from>" + texname + ".png" + "</init_from>"+"\n"+
					"        </image>"+"\n"+
					"    </library_images>"+"\n"+
					"    <scene>"+"\n"+
					"        <instance_visual_scene url=\"#ID1\" />"+"\n"+
					"    </scene>"+"\n"+
					"</COLLADA>"+"\n";



		File f;
		f = new File(dirpath + "tex\\" + getMap().name() + "\\" + texname + ".dae");
		PrintWriter pw;
		try
		{
			pw = new PrintWriter(new BufferedWriter(new FileWriter(f)));
		} catch(IOException e)
		{
			return;
		}

		pw.println(colladastring);
		pw.close();



		EditorMain.infoLabel.setTextSuccess("MapCanvas: Output selected area to 2X texture and COLLADA quad: "+dirpath + "tex\\" + getMap().name() + "\\" + texname + ".dae");


	}




	//===============================================================================================
	public void toggleMapGrid()
	{//===============================================================================================
		showMapGrid = !showMapGrid;
		repaint();

	}

	//===============================================================================================
	public void toggleLightBlackMasking()
	{//===============================================================================================
		lightBlackMasking = !lightBlackMasking;
		updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();

	}

	//===============================================================================================
	public void toggleLightScreenBlending()
	{//===============================================================================================
		lightScreenBlending = !lightScreenBlending;
		updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();

	}

	//===============================================================================================
	public void toggleMoveEntityByPixel()
	{//===============================================================================================
		moveEntityByPixel = !moveEntityByPixel;

	}
	//===============================================================================================
	public void toggleLayerImageBuffer()
	{//===============================================================================================
		if(useLayerImageBuffer == true)
		{
			EditorMain.infoLabel.setTextSuccess("MapCanvas: Turned layer buffer OFF");
			getMap().destroyLayerImages();
			useLayerImageBuffer = false;

		}
		else if(useLayerImageBuffer == false)
		{
			EditorMain.infoLabel.setTextSuccess("MapCanvas: Turned layer buffer ON");
			useLayerImageBuffer = true;
		}


		//definitely have to redraw everything
		updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();
	}


	//===============================================================================================
	public void togglePreviewMode()
	{//===============================================================================================
		if(previewMode == 1)
		{
			previewMode = 0;
		}
		else if(previewMode == 0)
		{
			previewMode = 1;
		}

		previewX = mapSelectionArea.x1 * 8;
		previewY = mapSelectionArea.y1 * 8;



		//E.mapScrollPane.setScrollPosition(0, 0);

		EditorMain.mapScrollPane.getHorizontalScrollBar().setValue(0);
		EditorMain.mapScrollPane.getVerticalScrollBar().setValue(0);



		int viewportSizeX = EditorMain.mapScrollPane.getViewport().getWidth();//E.mapScrollPane.getViewportSize().width
		int viewportSizeY = EditorMain.mapScrollPane.getViewport().getHeight();//E.mapScrollPane.getViewportSize().height

		Graphics G = getGraphics();
		G.translate(drawOffsetX(),drawOffsetY());
		G.setColor(Color.BLACK);
		G.fillRect(0, 0, viewportSizeX, viewportSizeY);
		G.dispose();

		repaint();
	}


	//===============================================================================================
	public void deleteSelectedArea()
	{//===============================================================================================
		if(getMap().getSelectedAreaIndex()!=-1)
		{
			Area area = getMap().getSelectedArea();
			undoManager.addEdit(new MapObjectRemoveEdit(getMap(), area));

			getMap().removeArea(getMap().getSelectedAreaIndex());
			getMap().setSelectedAreaIndex(-1);

			//the action layer just gets drawn when i repaint mapCanvas
			repaint();

			EditorMain.infoLabel.setTextSuccess("MapCanvas: Deleted Map Action");
		}
	}

	//===============================================================================================
	public void deleteSelectedLight()
	{//===============================================================================================
		if(getMap().getSelectedLightIndex()!=-1)
		{

			int mapX = getMap().getSelectedLight().xP();
			int mapY = getMap().getSelectedLight().yP();
			int radius = getMap().getSelectedLight().radiusPixels1X();
			int width = getMap().getSelectedLight().wP();
			int height = getMap().getSelectedLight().hP();

			//TODO: have to calculate this based on blendFalloff

			//store these for later, we will update the tiles at these positions
			int sx = (mapX-radius);
			int sy = (mapY-radius);
			int sw = ((radius*2)+width);
			int sh = ((radius*2)+height);


			Light light = getMap().getSelectedLight();
			undoManager.addEdit(new MapObjectRemoveEdit(getMap(), light));

			getMap().removeLight(getMap().getSelectedLightIndex());
			getMap().setSelectedLightIndex(-1);

			//if buffered, need to update lights layer and redraw it into mapcanvasimage
			if(useLayerImageBuffer==true)
			{
				getMap().updateLayerBufferImage(MapData.MAP_LIGHT_LAYER);
				drawBufferedLayerImagesIntoMapCanvasImage();

				repaint();
			}


			//if unbuffered, only need to paint the tiles that the light covers into the mapcanvasimage
			if(useLayerImageBuffer==false)
			{
				for(int x=sx/8;x<((sx+sw)/8)+1;x++)
				for(int y=sy/8;y<((sy+sh)/8)+1;y++)
					paintTileXY(MapData.MAP_LIGHT_LAYER,x,y);

				repaint();
			}


			EditorMain.infoLabel.setTextSuccess("MapCanvas: Deleted Map Light");
		}
	}

	//===============================================================================================
	public void deleteSelectedDoor()
	{//===============================================================================================
		if(getMap().getSelectedDoorIndex()!=-1)
		{

			//store these values for later
			int sx = getMap().getSelectedDoor().xP()/8;
			int sy = getMap().getSelectedDoor().yP()/8;
			int sw = getMap().getSelectedDoor().wP()/8;
			int sh = getMap().getSelectedDoor().hP()/8;

			Door door = getMap().getSelectedDoor();
			undoManager.addEdit(new MapObjectRemoveEdit(getMap(), door));

			getMap().removeDoor(getMap().getSelectedDoorIndex());
			getMap().setSelectedDoorIndex(-1);


			//buffered:
			//here i only need to refresh the map sprite layer buffer
			//then i need to redraw all the layers
			if(useLayerImageBuffer)
			{
				getMap().updateLayerBufferImage(MapData.MAP_DOOR_LAYER);
				drawBufferedLayerImagesIntoMapCanvasImage();

				repaint();
			}


			//unbuffered:
			//i need to redraw the mapcanvas, but only where the sprites are, really.
			//might be fastest to actually repaint tile xy where the sprites are, especially for huge maps.
			if(!useLayerImageBuffer)
			{

				for(int x=sx;x<sx+sw;x++)
				for(int y=sy;y<sy+sh;y++)
					paintTileXY(MapData.MAP_DOOR_LAYER,x,y);

				repaint();
			}

			EditorMain.infoLabel.setTextSuccess("MapCanvas: Deleted Door");
		}
	}

	//===============================================================================================
	public void deleteSelectedEntity()
	{//===============================================================================================
		if(getMap().getSelectedEntityIndex()!=-1)
		{

			//store these values for later
			int sx = getMap().getSelectedEntity().xP()/8;
			int sy = getMap().getSelectedEntity().yP()/8;
			int sw = (getMap().getSelectedEntity().wP()/8)+1;
			int sh = (getMap().getSelectedEntity().hP()/8)+1;

			Entity entity = getMap().getSelectedEntity();
			undoManager.addEdit(new MapObjectRemoveEdit(getMap(), entity));

			getMap().removeEntity(getMap().getSelectedEntityIndex());
			getMap().setSelectedEntityIndex(-1);


			//buffered:
			//here i only need to refresh the map sprite layer buffer
			//then i need to redraw all the layers
			if(useLayerImageBuffer)
			{
				getMap().updateLayerBufferImage(MapData.MAP_ENTITY_LAYER);
				drawBufferedLayerImagesIntoMapCanvasImage();

				repaint();
			}


			//unbuffered:
			//i need to redraw the mapcanvas, but only where the sprites are, really.
			//might be fastest to actually repaint tile xy where the sprites are, especially for huge maps.
			if(!useLayerImageBuffer)
			{

				for(int x=sx;x<sx+sw;x++)
				for(int y=sy;y<sy+sh;y++)
					paintTileXY(MapData.MAP_ENTITY_LAYER,x,y);

				repaint();
			}

			EditorMain.infoLabel.setTextSuccess("MapCanvas: Deleted Map Sprite");
		}
	}

	public void scrollTo(Entity s)
	{
		if(s!=null)
		{
			scrollToPixelXY((int)(s.xP()+s.wP()/2), (int)(s.yP()+s.hP()/2));
		}

	}

	public void scrollTo(Light o)
	{
		if(o!=null)
		{
			scrollToPixelXY((int)(o.xP()+o.wP()/2), (int)(o.yP()+o.hP()/2));
		}

	}

	public void scrollTo(Area o)
	{
		if(o!=null)
		{
			scrollToPixelXY((int)(o.xP()+o.wP()/2), (int)(o.yP()+o.hP()/2));
		}

	}

	public void scrollTo(Door s)
	{
		if(s!=null)
		{
			scrollToPixelXY((int)(s.xP()+s.wP()/2), (int)(s.yP()+s.hP()/2));
		}

	}

	public void scrollToTop(Entity s)
	{
		if(s!=null)
		{
			scrollToPixelXYTop((int)(s.xP()+s.wP()/2), (int)(s.yP()+s.hP()/2));
		}

	}

	public void scrollToTop(Light o)
	{
		if(o!=null)
		{
			scrollToPixelXYTop((int)(o.xP()+o.wP()/2), (int)(o.yP()+o.hP()/2));
		}

	}

	public void scrollToTop(Area o)
	{
		if(o!=null)
		{
			scrollToPixelXYTop((int)(o.xP()+o.wP()/2), (int)(o.yP()+o.hP()/2));
		}

	}

	public void scrollToTop(Door s)
	{
		if(s!=null)
		{
			scrollToPixelXYTop((int)(s.xP()+s.wP()/2), (int)(s.yP()+s.hP()/2));
		}

	}

	public void scrollToTileXY(int tX, int tY)
	{
		scrollToPixelXY(tX*8, tY*8);

	}








}

