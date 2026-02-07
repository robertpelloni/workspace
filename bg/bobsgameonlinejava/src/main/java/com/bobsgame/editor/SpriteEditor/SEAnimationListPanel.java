package com.bobsgame.editor.SpriteEditor;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BorderFactory;
import javax.swing.DefaultListCellRenderer;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.Sprite.Sprite;
import com.bobsgame.shared.SpriteAnimationSequence;

public class SEAnimationListPanel extends JPanel implements ListSelectionListener, ActionListener {

	private static final long serialVersionUID = 1L;
	private SpriteEditor SE;
	private JList<SpriteAnimationSequence> animList;
	private DefaultListModel<SpriteAnimationSequence> animListModel;

	private JButton playButton;
	private JButton deleteButton;

	private boolean ignoreSelection = false;

	public SEAnimationListPanel(SpriteEditor se) {
		this.SE = se;
		setLayout(new BorderLayout());
		setBorder(BorderFactory.createTitledBorder("Animations (Tags)"));
		setPreferredSize(new Dimension(200, 150));

		animListModel = new DefaultListModel<>();
		animList = new JList<>(animListModel);
		animList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		animList.setCellRenderer(new AnimationCellRenderer());
		animList.addListSelectionListener(this);

		JScrollPane scrollPane = new JScrollPane(animList);
		add(scrollPane, BorderLayout.CENTER);

		JPanel buttonPanel = new JPanel();
		playButton = new JButton("Play");
		playButton.addActionListener(this);
		deleteButton = new JButton("Delete");
		deleteButton.addActionListener(this);

		buttonPanel.add(playButton);
		buttonPanel.add(deleteButton);

		add(buttonPanel, BorderLayout.SOUTH);
	}

	public void updateList() {
		ignoreSelection = true;
		animListModel.clear();
		Sprite s = Project.getSelectedSprite();
		if (s != null) {
			for (SpriteAnimationSequence anim : s.animationList()) {
				animListModel.addElement(anim);
			}

			// Try to select current animation based on frame
			SpriteAnimationSequence current = s.getClosestAnimationForCurrentFrame();
			if(current != null) {
				animList.setSelectedValue(current, true);
			}
		}
		ignoreSelection = false;
	}

	@Override
	public void valueChanged(ListSelectionEvent e) {
		if (e.getValueIsAdjusting() || ignoreSelection) return;

		SpriteAnimationSequence selected = animList.getSelectedValue();
		if (selected != null) {
			Sprite s = Project.getSelectedSprite();
			if (s != null) {
				s.setFrame(selected.frameStart);
				SE.frameControlPanel.updateSpriteInfo();
				SE.frameControlPanel.updateFrames();
				SE.editCanvas.repaintBufferImage();
				SE.editCanvas.repaint();
			}
		}
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if (e.getSource() == playButton) {
			// Trigger play in SEFrameControlPanel?
			// Need to set sequence text field to this animation's range?
			// SpriteAnimationSequence doesn't strictly define end frame, usually implies "until next animation".
			// But for now, let's just ensure we are at the start frame and maybe start the timer.

			// TODO: Implement "Play Range"
		} else if (e.getSource() == deleteButton) {
			SpriteAnimationSequence selected = animList.getSelectedValue();
			if (selected != null) {
				Sprite s = Project.getSelectedSprite();
				if (s != null) {
					s.animationList().remove(selected);
					updateList();
					SE.frameControlPanel.updateSpriteInfo(); // Update text fields
				}
			}
		}
	}

	class AnimationCellRenderer extends DefaultListCellRenderer {
		@Override
		public Component getListCellRendererComponent(JList<?> list, Object value, int index, boolean isSelected, boolean cellHasFocus) {
			super.getListCellRendererComponent(list, value, index, isSelected, cellHasFocus);
			if (value instanceof SpriteAnimationSequence) {
				SpriteAnimationSequence anim = (SpriteAnimationSequence) value;
				setText(anim.frameSequenceName + " (Frame " + anim.frameStart + ")");
			}
			return this;
		}
	}
}
