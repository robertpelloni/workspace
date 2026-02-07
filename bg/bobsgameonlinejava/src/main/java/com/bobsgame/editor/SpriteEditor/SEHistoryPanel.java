package com.bobsgame.editor.SpriteEditor;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.BorderFactory;
import javax.swing.DefaultListCellRenderer;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.ListSelectionModel;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import com.bobsgame.editor.Undo.UndoManager;
import com.bobsgame.editor.Undo.UndoableEdit;

public class SEHistoryPanel extends JPanel implements ChangeListener, ActionListener {

	private static final long serialVersionUID = 1L;
	protected SpriteEditor SE;

	private JList<UndoableEdit> historyList;
	private DefaultListModel<UndoableEdit> historyListModel;
	private JButton clearButton;

	private boolean ignoreSelection = false;

	public SEHistoryPanel(SpriteEditor se) {
		this.SE = se;
		setLayout(new BorderLayout());

		historyListModel = new DefaultListModel<>();
		historyList = new JList<>(historyListModel);
		historyList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		historyList.setCellRenderer(new HistoryCellRenderer());

		// Add UndoManager listener
		// Note: We need to register this panel to the undo manager of the active canvas.
		// Since active canvas can change or its undo manager, we should handle that update.
		// For SpriteEditor, there's usually one active EditCanvas.

		SE.editCanvas.undoManager.addChangeListener(this);

		historyList.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				int index = historyList.locationToIndex(e.getPoint());
				if(index != -1) {
					UndoableEdit edit = historyListModel.getElementAt(index);
					// Logic:
					// If we click an item, we want to go to the state AFTER that item is done.
					// So nextEditIndex should become index + 1.

					UndoManager um = SE.editCanvas.undoManager;
					int currentNext = um.getNextEditIndex();
					int targetNext = index + 1;

					if (targetNext < currentNext) {
						// We need to undo until we are at targetNext
						// Current is 5. Target is 2.
						// Undo 5 (now 4). Undo 4 (now 3). Undo 3 (now 2).
						while (um.getNextEditIndex() > targetNext) {
							um.undo();
						}
					} else if (targetNext > currentNext) {
						// We need to redo until we are at targetNext
						while (um.getNextEditIndex() < targetNext) {
							um.redo();
						}
					}

					// If we click the selected one (current state), do nothing?
					// Or if we click older ones, undo.
					// If we click newer ones (grayed out), redo.

					SE.editCanvas.repaintBufferImage();
					SE.editCanvas.repaint();
				}
			}
		});

		JScrollPane scrollPane = new JScrollPane(historyList);
		add(scrollPane, BorderLayout.CENTER);

		clearButton = new JButton("Clear History");
		clearButton.addActionListener(this);
		add(clearButton, BorderLayout.SOUTH);

		updateList();
	}

	public void updateList() {
		UndoManager um = SE.editCanvas.undoManager;
		if (um == null) return;

		historyListModel.clear();
		for(UndoableEdit edit : um.getEdits()) {
			historyListModel.addElement(edit);
		}

		int nextIndex = um.getNextEditIndex();
		// Select the LAST done edit (index - 1)
		if(nextIndex > 0) {
			historyList.setSelectedIndex(nextIndex - 1);
			historyList.ensureIndexIsVisible(nextIndex - 1);
		} else {
			historyList.clearSelection();
		}

		historyList.repaint();
	}

	@Override
	public void stateChanged(ChangeEvent e) {
		updateList();
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == clearButton) {
			SE.editCanvas.undoManager.discardAllEdits();
			SE.editCanvas.repaintBufferImage();
			SE.editCanvas.repaint();
		}
	}

	class HistoryCellRenderer extends DefaultListCellRenderer {
		@Override
		public Component getListCellRendererComponent(JList<?> list, Object value, int index, boolean isSelected, boolean cellHasFocus) {
			super.getListCellRendererComponent(list, value, index, isSelected, cellHasFocus);

			if (value instanceof UndoableEdit) {
				UndoableEdit edit = (UndoableEdit) value;
				setText(edit.getPresentationName());

				UndoManager um = SE.editCanvas.undoManager;
				int nextIndex = um.getNextEditIndex();

				// Items at or after nextIndex are "Redoable" (future) - Gray them out
				if (index >= nextIndex) {
					setForeground(Color.GRAY);
				} else {
					setForeground(Color.BLACK);
				}

				// Highlight current state
				if (index == nextIndex - 1) {
					setBackground(new Color(200, 255, 200)); // Light Green
				} else {
					if (isSelected) {
						setBackground(list.getSelectionBackground());
					} else {
						setBackground(list.getBackground());
					}
				}
			}
			return this;
		}
	}
}
