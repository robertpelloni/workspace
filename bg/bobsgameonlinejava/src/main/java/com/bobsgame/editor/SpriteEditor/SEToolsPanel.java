package com.bobsgame.editor.SpriteEditor;

import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.ButtonGroup;
import javax.swing.JPanel;
import javax.swing.JToggleButton;

import com.bobsgame.EditorMain;
import com.bobsgame.editor.SpriteEditor.Tools.EraserBrush;
import com.bobsgame.editor.SpriteEditor.Tools.FillBrush;
import com.bobsgame.editor.SpriteEditor.Tools.MagicWandBrush;
import com.bobsgame.editor.SpriteEditor.Tools.PixelBrush;

public class SEToolsPanel extends JPanel implements ActionListener {

	private static final long serialVersionUID = 1L;
	protected SpriteEditor SE;

	private JToggleButton pencilButton;
	private JToggleButton eraserButton;
	private JToggleButton fillButton;
	private JToggleButton magicWandButton;
	private JToggleButton pixelPerfectButton; // Not in group, toggle option
	private ButtonGroup toolGroup;

	public SEToolsPanel(SpriteEditor se) {
		this.SE = se;
		setLayout(new FlowLayout(FlowLayout.LEFT));
		setBorder(EditorMain.border);

		toolGroup = new ButtonGroup();

		pencilButton = new JToggleButton("Pencil");
		pencilButton.addActionListener(this);
		pencilButton.setSelected(true);
		toolGroup.add(pencilButton);
		add(pencilButton);

		pixelPerfectButton = new JToggleButton("Pixel Perfect");
		pixelPerfectButton.addActionListener(this);
		add(pixelPerfectButton);

		eraserButton = new JToggleButton("Eraser");
		eraserButton.addActionListener(this);
		toolGroup.add(eraserButton);
		add(eraserButton);

		fillButton = new JToggleButton("Fill");
		fillButton.addActionListener(this);
		toolGroup.add(fillButton);
		add(fillButton);

		magicWandButton = new JToggleButton("Wand");
		magicWandButton.addActionListener(this);
		toolGroup.add(magicWandButton);
		add(magicWandButton);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == pencilButton || e.getSource() == pixelPerfectButton) {
			if(!pencilButton.isSelected()) {
				// If we clicked pixel perfect but eraser was selected, switch to pencil?
				// Or does pixel perfect apply to eraser too? Usually just pencil.
				// For now, let's keep it simple. If we toggle pixel perfect, we don't necessarily switch tool unless needed.
				// But we need to update the current brush if it is a PixelBrush.
			}

			if (pencilButton.isSelected()) {
				PixelBrush pb = new PixelBrush();
				pb.setPixelPerfect(pixelPerfectButton.isSelected());
				SE.editCanvas.currentBrush = pb;
			}
		}

		if(e.getSource() == eraserButton) {
			SE.editCanvas.currentBrush = new EraserBrush();
		} else if(e.getSource() == fillButton) {
			SE.editCanvas.currentBrush = new FillBrush();
		} else if(e.getSource() == magicWandButton) {
			SE.editCanvas.currentBrush = new MagicWandBrush();
		}
	}

}
