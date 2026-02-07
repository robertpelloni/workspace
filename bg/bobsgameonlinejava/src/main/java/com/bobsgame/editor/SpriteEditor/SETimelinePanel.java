package com.bobsgame.editor.SpriteEditor;

import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;

import javax.swing.BorderFactory;
import javax.swing.DefaultListCellRenderer;
import javax.swing.DefaultListModel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.ListSelectionModel;
import javax.swing.ScrollPaneConstants;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.Sprite.Sprite;

public class SETimelinePanel extends JPanel implements ListSelectionListener {

	private static final long serialVersionUID = 1L;
	private SpriteEditor SE;
	private JList<Integer> frameList;
	private DefaultListModel<Integer> frameListModel;
	private boolean ignoreSelection = false;

	public SETimelinePanel(SpriteEditor se) {
		this.SE = se;
		setLayout(new java.awt.BorderLayout());
		setPreferredSize(new Dimension(600, 80));
		setBorder(BorderFactory.createTitledBorder("Timeline"));

		frameListModel = new DefaultListModel<>();
		frameList = new JList<>(frameListModel);
		frameList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		frameList.setLayoutOrientation(JList.HORIZONTAL_WRAP);
		frameList.setVisibleRowCount(1);
		frameList.setCellRenderer(new FrameCellRenderer());
		frameList.addListSelectionListener(this);

		// Handle clicks
		frameList.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				// double click?
			}
		});

		JScrollPane scrollPane = new JScrollPane(frameList);
		scrollPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_NEVER);
		scrollPane.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_ALWAYS);

		add(scrollPane, java.awt.BorderLayout.CENTER);
	}

	public void updateTimeline() {
		ignoreSelection = true;
		frameListModel.clear();
		Sprite s = Project.getSelectedSprite();
		if (s != null) {
			for (int i = 0; i < s.frames(); i++) {
				frameListModel.addElement(i);
			}
			frameList.setSelectedIndex(s.getSelectedFrameIndex());
			frameList.ensureIndexIsVisible(s.getSelectedFrameIndex());
		}
		ignoreSelection = false;
		repaint();
	}

	@Override
	public void valueChanged(ListSelectionEvent e) {
		if (e.getValueIsAdjusting() || ignoreSelection) return;

		int index = frameList.getSelectedIndex();
		if (index >= 0) {
			Sprite s = Project.getSelectedSprite();
			if (s != null && index < s.frames()) {
				s.setFrame(index);
				SE.frameControlPanel.updateSpriteInfo();
				SE.frameControlPanel.updateFrames();
				SE.editCanvas.repaintBufferImage();
				SE.editCanvas.repaint();
			}
		}
	}

	class FrameCellRenderer extends DefaultListCellRenderer {
		@Override
		public Component getListCellRendererComponent(JList<?> list, Object value, int index, boolean isSelected, boolean cellHasFocus) {
			super.getListCellRendererComponent(list, value, index, isSelected, cellHasFocus);
			setText(""); // No text, just image

			Integer frameIndex = (Integer) value;
			Sprite s = Project.getSelectedSprite();
			if (s != null) {
				// This might be slow if we create image every time.
				// Sprite.getFrameImage returns a new BufferedImage each call.
				// For a simple list, it might be okay, but caching is better.
				// For now, let's just call it.
				BufferedImage img = s.getFrameImage(frameIndex);

				// Scale it to fit 64x64
				int size = 64;
				Image scaled = img.getScaledInstance(size, size, Image.SCALE_FAST);
				setIcon(new javax.swing.ImageIcon(scaled));

				setToolTipText("Frame " + frameIndex);

				if(isSelected) {
					setBackground(Color.BLUE);
				} else {
					setBackground(Color.DARK_GRAY);
				}
				setOpaque(true);
			}

			return this;
		}
	}
}
