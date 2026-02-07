package com.bobsgame.editor;

import java.awt.*;
import java.text.DateFormat;
import java.util.Date;

import javax.swing.JLabel;
import javax.swing.JPanel;

import com.bobsgame.EditorMain;
import com.bobsgame.editor.MapCanvas.MapCanvas;

public class InfoLabelPanel extends JPanel {
	public int soundsOnOff = 1;

	EditorMain E;
	Runtime rt = Runtime.getRuntime();


	public JLabel text = new JLabel();


	public InfoLabelPanel(String s, EditorMain e) {
		E = e;

		text = new JLabel("", JLabel.LEFT);

		setLayout(new BorderLayout());
		add(text, BorderLayout.WEST);

		setBackground(Color.BLACK);

		text.setForeground(Color.WHITE);

		setTextNoConsole(s);

		//rt = Runtime.getRuntime();
	}

	public void setTextSuccess(String s) {
		text.setForeground(Color.GREEN);
		setTextAndConsole(s);

		if (soundsOnOff == 1) {
			Toolkit.getDefaultToolkit().beep();
		}
	}

	public void setTextError(String s) {
		text.setForeground(Color.RED);
		setTextAndConsole(s);

		if (soundsOnOff == 1) {
			Toolkit.getDefaultToolkit().beep();
			Toolkit.getDefaultToolkit().beep();
			Toolkit.getDefaultToolkit().beep();
			Toolkit.getDefaultToolkit().beep();
			Toolkit.getDefaultToolkit().beep();
		}
	}

	public void setTextNoConsole(String s) {
		text.setForeground(Color.WHITE);

		String d = DateFormat.getDateTimeInstance().format(new Date());
		text.setText(d + "  |  " + s);

		updateStats();
	}

	public void setTextAndConsole(String s) {
		String d = DateFormat.getDateTimeInstance().format(new Date());
		text.setText(d + "  |  " + s);
		System.out.println(d + "  |  " + s);

		updateStats();
		//Toolkit.getDefaultToolkit().sync();
	}

	public void setText(String s) {
		text.setForeground(Color.WHITE);
		setTextAndConsole(s);
	}

	public void updateStats() {
		if (rt == null) rt = Runtime.getRuntime();
		int mb = 1024 * 1024;

		if (E != null) {
			long usedMemory = (rt.totalMemory() - rt.freeMemory()) / mb;
			if (E.statsLabel != null) {
				E.statsLabel.setText("Zoom: " + (MapCanvas.zoom / 8.0f) * 100 + "% | Used: " + usedMemory + " MB | Free: " + rt.freeMemory() / mb + " MB | Total: " + rt.totalMemory() / mb + " MB | Max: " + rt.maxMemory() / mb + " MB");
			}
			if (E.infoLabelPanel != null) {
				E.infoLabelPanel.validate();
			}
		}
	}

	public void toggleSoundsOnOff() {
		if (soundsOnOff == 1) {
			soundsOnOff = 0;
		} else if (soundsOnOff == 0) {
			soundsOnOff = 1;
		}
	}
}
