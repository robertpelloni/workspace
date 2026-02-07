package com.bobsgame.editor.ControlPanel;

import java.awt.*;
import java.awt.event.*;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.WindowConstants;

import com.bobsgame.EditorMain;

import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.TilesetPalette;


//===============================================================================================
public class ColorWindow extends JFrame implements WindowListener, ActionListener, AdjustmentListener, KeyListener, MouseListener, TextListener
{//===============================================================================================

	/**
	 *
	 */
	private static final long serialVersionUID = 1L;
	protected JPanel rgbTextFieldPanel, hsbTextFieldPanel, hsbScrollbarPanel, buttonPanel, rootPanel;
	public TextField redTextField, greenTextField, blueTextField;
	public TextField hueTextField, saturationTextField, brightnessTextField;

	public int r, g, b;
	public int h, s, v;
	public Scrollbar redScrollbar, greenScrollbar, blueScrollbar;
	public Scrollbar hueScrollbar, saturationScrollbar, brightnessScrollbar;

	protected JButton okButton, applyButton;

	JLabel redLabel,greenLabel,blueLabel,hueLabel,saturationLabel,brightnessLabel;

	protected PaletteCanvas P;
	protected EditorMain E;

	protected ColorGrid cGrid;
	protected int index;
	public boolean mapType = true;

	public int maxRGBValue=255;


	//===============================================================================================
	public ColorWindow(String s)
	{//===============================================================================================
		super(s);
		setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
	}


	//===============================================================================================
	public ColorWindow()
	{//===============================================================================================
		super("Set RGB/HSB");
	}



	//===============================================================================================
	public ColorWindow(PaletteCanvas pp)
	{//===============================================================================================
		super("Set RGB/HSB");
		P = pp;
		E = P.E;

		build();
	}

	//===============================================================================================
	public void build()
	//===============================================================================================
	{

		setSize(512+10, 815);
		setBackground(SystemColor.menu);

		setLayout(new BorderLayout());

		rootPanel = new JPanel();
		rootPanel.setLayout(new BoxLayout(rootPanel,BoxLayout.PAGE_AXIS));




		//-------------------------
		// RGB TEXT FIELDS
		//-------------------------
			rgbTextFieldPanel = new JPanel(new FlowLayout());

			redLabel = new JLabel("R", JLabel.CENTER);
			greenLabel = new JLabel("G", JLabel.CENTER);
			blueLabel = new JLabel("B", JLabel.CENTER);

			redLabel.setFont(new Font("Arial", Font.BOLD, 12));
			greenLabel.setFont(new Font("Arial", Font.BOLD, 12));
			blueLabel.setFont(new Font("Arial", Font.BOLD, 12));

			redTextField = new TextField("0");
			redTextField.addTextListener(this);
			greenTextField = new TextField("0");
			greenTextField.addTextListener(this);
			blueTextField = new TextField("0");
			blueTextField.addTextListener(this);

			redLabel.setForeground(Color.RED);
			//redLabel.setBackground(Color.BLACK);
			greenLabel.setForeground(Color.GREEN.darker());
			//greenLabel.setBackground(Color.BLACK);
			blueLabel.setForeground(Color.BLUE);
			//blueLabel.setBackground(Color.BLACK);

			redTextField.setFont(new Font("Arial", Font.BOLD, 12));
			greenTextField.setFont(new Font("Arial", Font.BOLD, 12));
			blueTextField.setFont(new Font("Arial", Font.BOLD, 12));
			redTextField.setForeground(Color.RED);
			greenTextField.setForeground(Color.GREEN.darker());
			blueTextField.setForeground(Color.BLUE);
			//redTextField.setBackground(Color.BLACK);
			//greenTextField.setBackground(Color.BLACK);
			//blueTextField.setBackground(Color.BLACK);

			rgbTextFieldPanel.add(redLabel);
			rgbTextFieldPanel.add(redTextField);
			rgbTextFieldPanel.add(greenLabel);
			rgbTextFieldPanel.add(greenTextField);
			rgbTextFieldPanel.add(blueLabel);
			rgbTextFieldPanel.add(blueTextField);

			rootPanel.add(rgbTextFieldPanel);

		//-------------------------
		// RGB SCROLLBARS
		//-------------------------

			JPanel rgbScrollbarPanel = new JPanel(new GridLayout(0,1,0,0));

			redScrollbar = new Scrollbar(Scrollbar.HORIZONTAL, 0, 1, 0, 256);
			redScrollbar.addAdjustmentListener(this);
			greenScrollbar = new Scrollbar(Scrollbar.HORIZONTAL, 0, 1, 0, 256);
			greenScrollbar.addAdjustmentListener(this);
			blueScrollbar = new Scrollbar(Scrollbar.HORIZONTAL, 0, 1, 0, 256);
			blueScrollbar.addAdjustmentListener(this);

			redScrollbar.setForeground(Color.RED);
			redScrollbar.setBackground(Color.RED);
			greenScrollbar.setForeground(Color.GREEN);
			greenScrollbar.setBackground(Color.GREEN);
			blueScrollbar.setForeground(Color.BLUE);
			blueScrollbar.setBackground(Color.BLUE);


			redScrollbar.setSize(new Dimension(400, 10));
			greenScrollbar.setSize(new Dimension(400, 10));
			blueScrollbar.setSize(new Dimension(400, 10));

			rgbScrollbarPanel.add(redScrollbar);
			rgbScrollbarPanel.add(greenScrollbar);
			rgbScrollbarPanel.add(blueScrollbar);

			rootPanel.add(rgbScrollbarPanel);

		//-------------------------
		// HSB TEXT FIELDS
		//-------------------------

			hsbTextFieldPanel = new JPanel();


			hueLabel = new JLabel("H", JLabel.CENTER);
			saturationLabel = new JLabel("S", JLabel.CENTER);
			brightnessLabel = new JLabel("B", JLabel.CENTER);

			hueLabel.setFont(new Font("Arial", Font.BOLD, 12));
			saturationLabel.setFont(new Font("Arial", Font.BOLD, 12));
			brightnessLabel.setFont(new Font("Arial", Font.BOLD, 12));

			hueLabel.setForeground(Color.MAGENTA);
			//hueLabel.setBackground(Color.BLACK);
			saturationLabel.setForeground(Color.GRAY);
			//saturationLabel.setBackground(Color.BLACK);
			brightnessLabel.setForeground(Color.WHITE);
			//brightnessLabel.setBackground(Color.BLACK);


			hueTextField = new TextField("0");
			hueTextField.addTextListener(this);
			saturationTextField = new TextField("0");
			saturationTextField.addTextListener(this);
			brightnessTextField = new TextField("0");
			brightnessTextField.addTextListener(this);




			hsbTextFieldPanel.add(hueLabel);
			hsbTextFieldPanel.add(hueTextField);
			hsbTextFieldPanel.add(saturationLabel);
			hsbTextFieldPanel.add(saturationTextField);
			hsbTextFieldPanel.add(brightnessLabel);
			hsbTextFieldPanel.add(brightnessTextField);

			rootPanel.add(hsbTextFieldPanel);

		//-------------------------
		// HSB ADJUSTMENT BUTTONS
		//-------------------------

			hsbScrollbarPanel = new JPanel(new GridLayout(0,1,0,0));

			hueScrollbar = new Scrollbar(Scrollbar.HORIZONTAL, 0, 1, 0, 256);
			hueScrollbar.addAdjustmentListener(this);
			saturationScrollbar = new Scrollbar(Scrollbar.HORIZONTAL, 0, 1, 0, 256);
			saturationScrollbar.addAdjustmentListener(this);
			brightnessScrollbar = new Scrollbar(Scrollbar.HORIZONTAL, 0, 1, 0, 256);
			brightnessScrollbar.addAdjustmentListener(this);


			hueScrollbar.setSize(new Dimension(400, 10));
			saturationScrollbar.setSize(new Dimension(400, 10));
			brightnessScrollbar.setSize(new Dimension(400, 10));

			hsbScrollbarPanel.add(hueScrollbar);
			hsbScrollbarPanel.add(saturationScrollbar);
			hsbScrollbarPanel.add(brightnessScrollbar);


			rootPanel.add(hsbScrollbarPanel);

		//-------------------------
		// OK/APPLY BUTTONS
		//-------------------------

			buttonPanel = new JPanel(new FlowLayout());

			okButton = new JButton("OK");
			applyButton = new JButton("Apply");
			applyButton.addActionListener(this);
			okButton.addActionListener(this);
			buttonPanel.add(okButton);
			buttonPanel.add(applyButton);

			rootPanel.add(buttonPanel);


		add(rootPanel, BorderLayout.NORTH);

		cGrid = new ColorGrid(this);

		cGrid.setSize(512,512+cGrid.offsetY);
		cGrid.validate();

		add(cGrid, BorderLayout.CENTER);

		addWindowListener(this);

		cGrid.addKeyListener(this);
		redTextField.addKeyListener(this);
		greenTextField.addKeyListener(this);
		blueTextField.addKeyListener(this);
		hueTextField.addKeyListener(this);
		saturationTextField.addKeyListener(this);
		brightnessTextField.addKeyListener(this);
		redScrollbar.addKeyListener(this);
		greenScrollbar.addKeyListener(this);
		blueScrollbar.addKeyListener(this);
		hueScrollbar.addKeyListener(this);
		saturationScrollbar.addKeyListener(this);
		brightnessScrollbar.addKeyListener(this);
		okButton.addKeyListener(this);
		applyButton.addKeyListener(this);

		redScrollbar.addMouseListener(this);
		greenScrollbar.addMouseListener(this);
		blueScrollbar.addMouseListener(this);
		hueScrollbar.addMouseListener(this);
		saturationScrollbar.addMouseListener(this);
		brightnessScrollbar.addMouseListener(this);

		setResizable(false);

	}

	//===============================================================================================
	public TilesetPalette getPalette()
	{//===============================================================================================
		return Project.getSelectedPalette();
	}


	//===============================================================================================
	public void showColorWindow(int colorIndex, boolean openedByMap)
	{//===============================================================================================

		mapType = openedByMap;

		index = colorIndex;

		redTextField.setText("" + (getPalette().getRed(index)));
		redScrollbar.setValue((getPalette().getRed(index)));

		greenTextField.setText("" + (getPalette().getGreen(index)));
		greenScrollbar.setValue((getPalette().getGreen(index)));

		blueTextField.setText("" + (getPalette().getBlue(index)));
		blueScrollbar.setValue((getPalette().getBlue(index)));

		h = (getPalette().hsbi[index][0]);
		s = (getPalette().hsbi[index][1]);
		v = (getPalette().hsbi[index][2]);

		hueTextField.setText("" + (h));
		hueScrollbar.setValue(h);

		saturationTextField.setText("" + (s));
		saturationScrollbar.setValue(s);

		brightnessTextField.setText("" + (v));
		brightnessScrollbar.setValue(v);



		setVisible(true);


		try
		{
			setAlwaysOnTop(true);
		}
		catch(SecurityException se){}

	}




	//===============================================================================================
	public void adjustmentValueChanged(AdjustmentEvent ae)
	{//===============================================================================================

		if(
			ae.getSource()==redScrollbar||
			ae.getSource()==greenScrollbar||
			ae.getSource()==blueScrollbar
		)
		{

			r = redScrollbar.getValue();
			g = greenScrollbar.getValue();
			b = blueScrollbar.getValue();

			if(r > maxRGBValue)r = maxRGBValue;
			if(g > maxRGBValue)g = maxRGBValue;
			if(b > maxRGBValue)b = maxRGBValue;

			if(redScrollbar.getValue() != r)redScrollbar.setValue(r);
			if(greenScrollbar.getValue() != g)greenScrollbar.setValue(g);
			if(blueScrollbar.getValue() != b)blueScrollbar.setValue(b);

			redScrollbar.setBackground(new Color(r,0,0));
			greenScrollbar.setBackground(new Color(0,g,0));
			blueScrollbar.setBackground(new Color(0,0,b));

			float hsbf[] = new float[3];
			Color.RGBtoHSB(r, g, b, hsbf);
			h = Math.round(hsbf[0] * (float)maxRGBValue);
			s = Math.round(hsbf[1] * (float)maxRGBValue);
			v = Math.round(hsbf[2] * (float)maxRGBValue);

			if(hueScrollbar.getValue() != h)hueScrollbar.setValue(h);
			if(saturationScrollbar.getValue() != s)saturationScrollbar.setValue(s);
			if(brightnessScrollbar.getValue() != v)brightnessScrollbar.setValue(v);

			if(Integer.parseInt(redTextField.getText())!=r)redTextField.setText("" + r);
			if(Integer.parseInt(greenTextField.getText())!=g)greenTextField.setText("" + g);
			if(Integer.parseInt(blueTextField.getText())!=b)blueTextField.setText("" + b);


		}

		if(
				ae.getSource()==hueScrollbar||
				ae.getSource()==saturationScrollbar||
				ae.getSource()==brightnessScrollbar
			)
			{

				h = hueScrollbar.getValue();
				s = saturationScrollbar.getValue();
				v = brightnessScrollbar.getValue();

				if(h > maxRGBValue)h = maxRGBValue;
				if(s > maxRGBValue)s = maxRGBValue;
				if(v > maxRGBValue)v = maxRGBValue;

				if(hueScrollbar.getValue() != h)hueScrollbar.setValue(h);
				if(saturationScrollbar.getValue() != s)saturationScrollbar.setValue(s);
				if(brightnessScrollbar.getValue() != v)brightnessScrollbar.setValue(v);

				Color rgbColor = new Color(Color.HSBtoRGB(h/(float)maxRGBValue, s/(float)maxRGBValue, v/(float)maxRGBValue));

				r=rgbColor.getRed();
				g=rgbColor.getGreen();
				b=rgbColor.getBlue();

				if(redScrollbar.getValue() != r)redScrollbar.setValue(r);
				if(greenScrollbar.getValue() != g)greenScrollbar.setValue(g);
				if(blueScrollbar.getValue() != b)blueScrollbar.setValue(b);

				if(Integer.parseInt(hueTextField.getText())!=h)hueTextField.setText("" + h);
				if(Integer.parseInt(saturationTextField.getText())!=s)saturationTextField.setText("" + s);
				if(Integer.parseInt(brightnessTextField.getText())!=v)brightnessTextField.setText("" + v);

			}


	}


	//===============================================================================================
	public void textValueChanged(TextEvent te)
	{//===============================================================================================




		if(
				te.getSource()==redTextField||
				te.getSource()==greenTextField||
				te.getSource()==blueTextField
		)
		{

			//get text values

				r = Integer.parseInt(redTextField.getText());
				g = Integer.parseInt(greenTextField.getText());
				b = Integer.parseInt(blueTextField.getText());

				if(r > maxRGBValue)r = maxRGBValue;
				if(g > maxRGBValue)g = maxRGBValue;
				if(b > maxRGBValue)b = maxRGBValue;


				if(Integer.parseInt(redTextField.getText())!=r)redTextField.setText("" + r);
				if(Integer.parseInt(greenTextField.getText())!=g)greenTextField.setText("" + g);
				if(Integer.parseInt(blueTextField.getText())!=b)blueTextField.setText("" + b);





			if(redScrollbar.getValue() != r)redScrollbar.setValue(r);
			if(greenScrollbar.getValue() != g)greenScrollbar.setValue(g);
			if(blueScrollbar.getValue() != b)blueScrollbar.setValue(b);

			if(te.getSource()==blueTextField)cGrid.repaintColorWheelBackground(b);
			cGrid.paint(redScrollbar.getValue(), greenScrollbar.getValue(), blueScrollbar.getValue());



			float hsbf[] = new float[3];
			Color.RGBtoHSB(r, g, b, hsbf);
			h = Math.round(hsbf[0] * (float)maxRGBValue);
			s = Math.round(hsbf[1] * (float)maxRGBValue);
			v = Math.round(hsbf[2] * (float)maxRGBValue);


			if(hueScrollbar.getValue() != h)hueScrollbar.setValue(h);
			if(saturationScrollbar.getValue() != s)saturationScrollbar.setValue(s);
			if(brightnessScrollbar.getValue() != v)brightnessScrollbar.setValue(v);


			//don't update hue textfield when moving rgb, this will update h first, then s, then b, which changes the rgb values unevenly and gets into a race condition.
			//instead, i have it update the hsb textfields on mousereleased with a mouselistener

			//if(Integer.parseInt(hueTextField.getText())!=h)hueTextField.setText("" + h);
			//if(Integer.parseInt(saturationTextField.getText())!=s)saturationTextField.setText("" + s);
			//if(Integer.parseInt(brightnessTextField.getText())!=v)brightnessTextField.setText("" + v);


		}

		if(
				te.getSource()==hueTextField||
				te.getSource()==saturationTextField||
				te.getSource()==brightnessTextField
		)
		{
			h = Integer.parseInt(hueTextField.getText());
			s = Integer.parseInt(saturationTextField.getText());
			v = Integer.parseInt(brightnessTextField.getText());

			if(h > maxRGBValue)h = maxRGBValue;
			if(s > maxRGBValue)s = maxRGBValue;
			if(v > maxRGBValue)v = maxRGBValue;

			if(Integer.parseInt(hueTextField.getText())!=h)hueTextField.setText("" + h);
			if(Integer.parseInt(saturationTextField.getText())!=s)saturationTextField.setText("" + s);
			if(Integer.parseInt(brightnessTextField.getText())!=v)brightnessTextField.setText("" + v);

			if(hueScrollbar.getValue() != h)hueScrollbar.setValue(h);
			if(saturationScrollbar.getValue() != s)saturationScrollbar.setValue(s);
			if(brightnessScrollbar.getValue() != v)brightnessScrollbar.setValue(v);

			Color rgbColor = new Color(Color.HSBtoRGB(h/(float)maxRGBValue, s/(float)maxRGBValue, v/(float)maxRGBValue));

			r=rgbColor.getRed();
			g=rgbColor.getGreen();
			b=rgbColor.getBlue();


			if(redScrollbar.getValue() != r)redScrollbar.setValue(r);
			if(greenScrollbar.getValue() != g)greenScrollbar.setValue(g);
			if(blueScrollbar.getValue() != b)blueScrollbar.setValue(b);


			//only update rgb textfields if moving hsb.
			//we don't mind the rgb values jittering while moving the hsb sliders, we just don't want the rgb jittering while adjusting rgb itself!



			//another solution here would be to not use textValueChanged at all, which doesn't differentiate between programmatically changing the text and the user changing it
			//instead, i could put keylistener on textField and only update when the user types in information.
			//then i could programmatically change the text all i wanted and only update when i specified...

			//but for now, this works pretty well. it sometimes moves the rgb sliders a value or two on mousereleased, that's not too bad.


			//this sets the textfields but doesn't do it three times like below which isn't necessary
			adjustmentValueChanged(new AdjustmentEvent(redScrollbar,AdjustmentEvent.ADJUSTMENT_VALUE_CHANGED,AdjustmentEvent.TRACK,0));

			//if(Integer.parseInt(redTextField.getText())!=r)redTextField.setText("" + r);
			//if(Integer.parseInt(greenTextField.getText())!=g)greenTextField.setText("" + g);
			//if(Integer.parseInt(blueTextField.getText())!=b)blueTextField.setText("" + b);
		}

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
	public void windowOpening(WindowEvent we)
	{//===============================================================================================
	}
	//===============================================================================================
	public void windowClosing(WindowEvent we)
	{//===============================================================================================
		setVisible(false);
	}



	//===============================================================================================
	public void actionPerformed(ActionEvent ae)
	{//===============================================================================================

		if(ae.getSource() == okButton)okButton();

		if(ae.getSource() == applyButton)applyButton();

	}


	//===============================================================================================
	@Override
	public void keyTyped(KeyEvent e)
	{//===============================================================================================
	}
	//===============================================================================================
	public void keyPressed(KeyEvent ke)
	{//===============================================================================================
		if(ke.getKeyCode() == KeyEvent.VK_ENTER)
		{
			actionPerformed(new ActionEvent(okButton,ActionEvent.ACTION_PERFORMED,""));
		}

	}
	//===============================================================================================
	@Override
	public void keyReleased(KeyEvent e)
	{//===============================================================================================
	}




	//===============================================================================================
	public void okButton()
	{//===============================================================================================
		getPalette().setColorDataFromRGB(index, r, g, b);
		P.repaint();
		EditorMain.tileCanvas.updateAllTiles();
		EditorMain.tileCanvas.paint();

		EditorMain.controlPanel.paletteCanvas.selectColor(index);

		if(mapType == true)
		{

			//since we're changing colors, we should redraw all the layers
			//this could be optimized by finding which tiles actually changed and then repainting only those tiles on mapcanvas or in layers
			//but for now we'll just update everything
			EditorMain.mapCanvas.updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();

			EditorMain.infoLabel.setTextSuccess("Color " + index + " Set To RGB " + r + "," + g + "," + b);

		}
		else
		{
			EditorMain.multipleTileEditor.editCanvas.repaintBufferImage();
			EditorMain.multipleTileEditor.controlPanel.repaint();
			EditorMain.multipleTileEditor.infoLabel.setTextSuccess("Color " + index + " Set To RGB " + r + "," + g + "," + b);

		}

		setVisible(false);
	}

	//===============================================================================================
	public void applyButton()
	{//===============================================================================================


		getPalette().setColorDataFromRGB(index, r, g, b);
		P.repaint();
		EditorMain.tileCanvas.updateAllTiles();
		EditorMain.tileCanvas.paint();

		EditorMain.controlPanel.paletteCanvas.selectColor(index);

		if(mapType == true)
		{

			//since we're changing colors, we should redraw all the layers
			//this could be optimized by finding which tiles actually changed and then repainting only those tiles on mapcanvas or in layers
			//but for now we'll just update everything
			EditorMain.mapCanvas.updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();

			EditorMain.infoLabel.setTextSuccess("Color " + index + " Set To RGB " + r + "," + g + "," + b);

		}
		else
		{
			EditorMain.multipleTileEditor.editCanvas.repaintBufferImage();
			EditorMain.multipleTileEditor.controlPanel.repaint();
			EditorMain.multipleTileEditor.infoLabel.setTextSuccess("Color " + index + " Set To RGB " + r + "," + g + "," + b);

		}

	}
	//===============================================================================================
	@Override
	public void mouseClicked(MouseEvent e)
	{//===============================================================================================
	}

	//===============================================================================================
	@Override
	public void mousePressed(MouseEvent e)
	{//===============================================================================================
	}

	//===============================================================================================
	@Override
	public void mouseReleased(MouseEvent e)
	{//===============================================================================================



		if(
				e.getSource()==redScrollbar||
				e.getSource()==greenScrollbar||
				e.getSource()==blueScrollbar
		)
		{
			if(Integer.parseInt(hueTextField.getText())!=h)hueTextField.setText("" + h);
			if(Integer.parseInt(saturationTextField.getText())!=s)saturationTextField.setText("" + s);
			if(Integer.parseInt(brightnessTextField.getText())!=v)brightnessTextField.setText("" + v);

		}



		if(
				e.getSource()==hueScrollbar||
				e.getSource()==saturationScrollbar||
				e.getSource()==brightnessScrollbar
		)
		{
			if(Integer.parseInt(redTextField.getText())!=r)redTextField.setText("" + r);
			if(Integer.parseInt(greenTextField.getText())!=g)greenTextField.setText("" + g);
			if(Integer.parseInt(blueTextField.getText())!=b)blueTextField.setText("" + b);

		}
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
