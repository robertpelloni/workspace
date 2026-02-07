package com.bobsgame.client.engine.game.gui.stuffMenu.subMenus;

import com.bobsgame.client.engine.game.gui.stuffMenu.SubPanel;
import com.bobsgame.net.BobNet;

import de.matthiasmann.twl.Label;
import de.matthiasmann.twl.TextArea;
import de.matthiasmann.twl.EditField;
import de.matthiasmann.twl.Button;
import de.matthiasmann.twl.textarea.SimpleTextAreaModel;
import de.matthiasmann.twl.Event;

//=========================================================================================================================
public class MessagesPanel extends SubPanel
{//=========================================================================================================================

    private TextArea chatLog;
    private SimpleTextAreaModel chatLogModel;
    private EditField chatInput;
    private Button sendButton;
    private StringBuilder logBuilder = new StringBuilder();

	//=========================================================================================================================
	public MessagesPanel()
	{//=========================================================================================================================

		super();

        chatLogModel = new SimpleTextAreaModel();
        chatLog = new TextArea(chatLogModel);
        chatLog.setTheme("textarea");

        chatInput = new EditField();
        chatInput.addCallback(new EditField.Callback() {
            public void callback(int key) {
                if (key == Event.KEY_RETURN) {
                    sendChatMessage();
                }
            }
        });

        sendButton = new Button("Send");
        sendButton.addCallback(new Runnable() {
            @Override
            public void run() {
                sendChatMessage();
            }
        });

		Label label = new Label("Messages");
		label.setCanAcceptKeyboardFocus(false);

		insideLayout.setHorizontalGroup
		(
            insideLayout.createParallelGroup()
				.addWidget(label)
                .addWidget(chatLog)
                .addGroup(insideLayout.createSequentialGroup()
                    .addWidget(chatInput)
                    .addWidget(sendButton)
                )
		);

		insideLayout.setVerticalGroup
		(
			insideLayout.createSequentialGroup()
				.addWidget(label)
                .addWidget(chatLog)
                .addGroup(insideLayout.createParallelGroup()
                    .addWidget(chatInput)
                    .addWidget(sendButton)
                )
		);
	}

    private void sendChatMessage() {
        String msg = chatInput.getText();
        if(msg.length() > 0) {
            if(SubPanel.GameClientTCP() != null) {
                SubPanel.GameClientTCP().send(BobNet.Chat_Message + msg + BobNet.endline);
            }
            chatInput.setText("");
        }
    }

    public void addMessage(String msg) {
        logBuilder.append(msg).append("\n");
        chatLogModel.setText(logBuilder.toString());
    }

}
