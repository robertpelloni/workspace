package com.bobsgame.editor.SpriteEditor;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;

import javax.swing.BorderFactory;
import javax.swing.DefaultListCellRenderer;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSlider;
import javax.swing.ListSelectionModel;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import com.bobsgame.EditorMain;
import com.bobsgame.editor.Project.Sprite.Sprite;
import com.bobsgame.editor.Project.Sprite.Sprite.Layer;

public class SELayerPanel extends JPanel implements ActionListener, ListSelectionListener, ChangeListener, ItemListener {

	private static final long serialVersionUID = 1L;
	protected SpriteEditor SE;

	public JList<Layer> layerList;
	public DefaultListModel<Layer> layerListModel;

	private JButton addLayerButton;
	private JButton removeLayerButton;
	private JButton duplicateLayerButton;
	private JButton moveUpButton;
	private JButton moveDownButton;

	private JCheckBox visibleCheckBox;
	private JCheckBox referenceCheckBox;
	private JSlider opacitySlider;
	private JLabel opacityLabel;

	private boolean ignoreEvents = false;

	public SELayerPanel(SpriteEditor se) {
		this.SE = se;
		setLayout(new BorderLayout());
		setBorder(BorderFactory.createTitledBorder("Layers"));
		setPreferredSize(new Dimension(200, 300));

		// List
		layerListModel = new DefaultListModel<>();
		layerList = new JList<>(layerListModel);
		layerList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		layerList.setCellRenderer(new LayerCellRenderer());
		layerList.addListSelectionListener(this);

		JScrollPane listScrollPane = new JScrollPane(layerList);
		add(listScrollPane, BorderLayout.CENTER);

		// Controls Panel
		JPanel controlsPanel = new JPanel(new BorderLayout());

		// Properties
		JPanel propsPanel = new JPanel(new GridLayout(3, 1));
		visibleCheckBox = new JCheckBox("Visible");
		visibleCheckBox.addItemListener(this);
		propsPanel.add(visibleCheckBox);

		referenceCheckBox = new JCheckBox("Reference Layer");
		referenceCheckBox.addItemListener(this);
		propsPanel.add(referenceCheckBox);

		JPanel opacityPanel = new JPanel(new BorderLayout());
		opacityLabel = new JLabel("Op: 100%");
		opacitySlider = new JSlider(0, 100, 100);
		opacitySlider.addChangeListener(this);
		opacityPanel.add(opacityLabel, BorderLayout.WEST);
		opacityPanel.add(opacitySlider, BorderLayout.CENTER);
		propsPanel.add(opacityPanel);

		controlsPanel.add(propsPanel, BorderLayout.NORTH);

		// Buttons
		JPanel buttonsPanel = new JPanel(new GridLayout(2, 3));
		Font smallFont = new Font("Tahoma", Font.PLAIN, 10);

		addLayerButton = new JButton("+");
		addLayerButton.setFont(smallFont);
		addLayerButton.addActionListener(this);

		removeLayerButton = new JButton("-");
		removeLayerButton.setFont(smallFont);
		removeLayerButton.addActionListener(this);

		duplicateLayerButton = new JButton("Dup");
		duplicateLayerButton.setFont(smallFont);
		duplicateLayerButton.addActionListener(this);

		moveUpButton = new JButton("Up");
		moveUpButton.setFont(smallFont);
		moveUpButton.addActionListener(this);

		moveDownButton = new JButton("Dn");
		moveDownButton.setFont(smallFont);
		moveDownButton.addActionListener(this);

		buttonsPanel.add(addLayerButton);
		buttonsPanel.add(duplicateLayerButton);
		buttonsPanel.add(removeLayerButton);
		buttonsPanel.add(moveUpButton);
		buttonsPanel.add(moveDownButton);

		controlsPanel.add(buttonsPanel, BorderLayout.SOUTH);

		add(controlsPanel, BorderLayout.SOUTH);
	}

	public void updateLayerList() {
		ignoreEvents = true;
		layerListModel.clear();
		Sprite s = SpriteEditor.getSprite();
		if(s != null) {
			for(Layer l : s.getLayers()) {
				// Add to top of list so index 0 is at bottom (visual stack)
				// Or just list normally?
				// Typically layer list shows top layer at top.
				// Our list index 0 is bottom layer.
				// So we should reverse iteration for UI, but map index carefully.
				// Let's keep it simple: Index 0 is bottom layer (background), shown at top of list?
				// No, usually top of list is top layer.
				// I'll add them in reverse order.
				layerListModel.add(0, l);
			}

			// Select active layer
			// s.activeLayerIndex is 0-based index.
			// If list is reversed, selected index in list is (size - 1 - activeIndex)
			int listIndex = (s.getLayers().size() - 1) - s.activeLayerIndex;
			layerList.setSelectedIndex(listIndex);

			updateControls();
		}
		ignoreEvents = false;
	}

	private void updateControls() {
		Layer l = layerList.getSelectedValue();
		if(l != null) {
			visibleCheckBox.setEnabled(true);
			visibleCheckBox.setSelected(l.visible);
			referenceCheckBox.setEnabled(true);
			referenceCheckBox.setSelected(l.isReference);
			opacitySlider.setEnabled(true);
			opacitySlider.setValue((int)(l.opacity * 100));
			opacityLabel.setText("Op: " + (int)(l.opacity * 100) + "%");
		} else {
			visibleCheckBox.setEnabled(false);
			referenceCheckBox.setEnabled(false);
			opacitySlider.setEnabled(false);
		}
	}

	@Override
	public void valueChanged(ListSelectionEvent e) {
		if(e.getValueIsAdjusting() || ignoreEvents) return;

		int index = layerList.getSelectedIndex();
		if(index >= 0) {
			Sprite s = SpriteEditor.getSprite();
			if(s != null) {
				// Map list index (top-down) back to layer index (bottom-up)
				int layerIndex = (s.getLayers().size() - 1) - index;
				s.activeLayerIndex = layerIndex;
				updateControls();
				SE.editCanvas.repaintBufferImage();
				SE.editCanvas.repaint();
			}
		}
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		Sprite s = SpriteEditor.getSprite();
		if(s == null) return;

		if(e.getSource() == addLayerButton) {
			s.addLayer();
			updateLayerList();
			SE.editCanvas.repaintBufferImage();
			SE.editCanvas.repaint();
		} else if(e.getSource() == removeLayerButton) {
			int index = layerList.getSelectedIndex();
			if(index >= 0) {
				int layerIndex = (s.getLayers().size() - 1) - index;
				s.removeLayer(layerIndex);
				updateLayerList();
				SE.editCanvas.repaintBufferImage();
				SE.editCanvas.repaint();
			}
		} else if(e.getSource() == duplicateLayerButton) {
			int index = layerList.getSelectedIndex();
			if(index >= 0) {
				int layerIndex = (s.getLayers().size() - 1) - index;
				Layer active = s.getLayers().get(layerIndex);
				Layer copy = active.duplicate();
				s.getLayers().add(layerIndex + 1, copy); // Add above current
				s.activeLayerIndex = layerIndex + 1;
				updateLayerList();
				SE.editCanvas.repaintBufferImage();
				SE.editCanvas.repaint();
			}
		}

	}

	@Override
	public void stateChanged(ChangeEvent e) {
		if(ignoreEvents) return;
		if(e.getSource() == opacitySlider) {
			Layer l = layerList.getSelectedValue();
			if(l != null) {
				l.opacity = opacitySlider.getValue() / 100f;
				opacityLabel.setText("Op: " + (int)(l.opacity * 100) + "%");
				SE.editCanvas.repaintBufferImage();
				SE.editCanvas.repaint();
			}
		}
	}

	@Override
	public void itemStateChanged(ItemEvent e) {
		if(ignoreEvents) return;
		if(e.getSource() == visibleCheckBox) {
			Layer l = layerList.getSelectedValue();
			if(l != null) {
				l.visible = visibleCheckBox.isSelected();
				layerList.repaint(); // update renderer text
				SE.editCanvas.repaintBufferImage();
				SE.editCanvas.repaint();
			}
		} else if(e.getSource() == referenceCheckBox) {
			Layer l = layerList.getSelectedValue();
			if(l != null) {
				l.isReference = referenceCheckBox.isSelected();
				layerList.repaint(); // update renderer text
				SE.editCanvas.repaintBufferImage();
				SE.editCanvas.repaint();
			}
		}
	}

	class LayerCellRenderer extends DefaultListCellRenderer {
		@Override
		public Component getListCellRendererComponent(JList<?> list, Object value, int index, boolean isSelected, boolean cellHasFocus) {
			super.getListCellRendererComponent(list, value, index, isSelected, cellHasFocus);
			if(value instanceof Layer) {
				Layer l = (Layer)value;
				String text = l.name;
				if(l.isReference) text += " (Ref)";
				if(!l.visible) text += " (Hidden)";
				setText(text);
				if(!l.visible) setForeground(Color.GRAY);
				else if(l.isReference) setForeground(Color.BLUE);
				else setForeground(Color.BLACK);
			}
			return this;
		}
	}

}
