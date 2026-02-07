package com.bobsgame.client.engine.game.gui.stuffMenu.subMenus;


//import org.lwjgl.input.Controller;
//import org.lwjgl.input.Controllers;
import org.lwjgl.glfw.GLFW;

import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.game.gui.stuffMenu.SubPanel;

import de.matthiasmann.twl.Button;
import de.matthiasmann.twl.DialogLayout;
import de.matthiasmann.twl.Label;
import de.matthiasmann.twl.Widget;

import java.nio.ByteBuffer;
import java.nio.FloatBuffer;


//=========================================================================================================================
public class ControlsPanel extends SubPanel
{//=========================================================================================================================



	Label[] buttonValueLabel;



	//=========================================================================================================================
	public ControlsPanel()
	{//=========================================================================================================================

		super();



		Label mainControlsLabel = new Label("Main Controls");
		mainControlsLabel.setCanAcceptKeyboardFocus(false);
		mainControlsLabel.setTheme("helpLabelBig");


	/*
		Label wasdLabel = new Label("(You can also control movement with \"WASD\")");
		wasdLabel.setCanAcceptKeyboardFocus(false);
		wasdLabel.setTheme("helpLabelSmall");
*/


		//up down left right wasd

		//zoom in/out
		//TODO: add mousewheel for this

		//TODO: add mouse click controls

		//TODO: add gameController support


		Widget keyboardImagePanel = new Widget()
		{
			public void layout()
			{

				//force the keyboard image to fit inside the layout/scrollpane/layout/layout

				thisDialogLayout.setBorderSize(0, 20);
				insideLayout.setBorderSize(0,20);
				scrollPane.setBorderSize(0,20);

				int w = (int)(thisDialogLayout.getWidth()*0.80f);
				if(w<0)w=128;

				//setMinSize(w,50);
				setMaxSize(w,390);
				//adjustSize();


			}

		};
		keyboardImagePanel.setTheme("keyboardImagePanel");



//		Label otherControlsLabel = new Label("Other Controls:");
//		otherControlsLabel.setCanAcceptKeyboardFocus(false);
//		otherControlsLabel.setTheme("helpLabelBig");
//
//		Label otherControlsTextLabel = new Label("F12 - Take Screenshot");
//		otherControlsTextLabel.setCanAcceptKeyboardFocus(false);
//		otherControlsTextLabel.setTheme("helpLabelSmall");



		Label gameControllerSetupLabel = new Label("Game Controller Setup");
		gameControllerSetupLabel.setCanAcceptKeyboardFocus(false);
		gameControllerSetupLabel.setTheme("helpLabelBig");


		Label gameControllerInfoLabel = new Label("\"bob's game\" supports most USB Game Controllers. Please plug your controller in before starting the game.");
		gameControllerInfoLabel.setCanAcceptKeyboardFocus(false);
		gameControllerInfoLabel.setTheme("helpLabelSmall");



/*
		Label scrollDownLabel = new Label("In the \"Stuff Menu,\" you can click with the mouse and scroll down with the mouse wheel.");
		scrollDownLabel.setCanAcceptKeyboardFocus(false);
		scrollDownLabel.setTheme("helpLabelSmall");
*/



		DialogLayout gameControllerLayout = new DialogLayout();
		gameControllerLayout.setCanAcceptKeyboardFocus(false);
		gameControllerLayout.setTheme("gameControllerSetupLayout");







		int buttons = 10;

		Label[] buttonLabel = new Label[buttons];
		buttonValueLabel = new Label[buttons];
		Button[] buttonButton = new Button[buttons];

		DialogLayout[] buttonLayout = new DialogLayout[buttons];


		for(int i=0;i<buttons;i++)
		{




			buttonLabel[i] = new Label("");
			buttonLabel[i].setCanAcceptKeyboardFocus(false);
			buttonLabel[i].setTheme("font16PurpleOutline");

			buttonValueLabel[i] = new Label("NONE");
			buttonValueLabel[i].setCanAcceptKeyboardFocus(false);
			buttonValueLabel[i].setTheme("font11WhiteOutline");

			buttonButton[i] = new Button("Set");
			buttonButton[i].setCanAcceptKeyboardFocus(false);

			final int threadi = i;

			buttonButton[i].addCallback(new Runnable()//even though this is a runnable, it is NOT a thread. fireCallback just calls Runnable.run() which does not create a thread.
			{
				public void run()
				{
					new Thread
					(

						new Runnable()
						{
							public void run()
							{
								try{Thread.currentThread().setName("ControlsPanel_setGameControllerInput");}catch(SecurityException e){e.printStackTrace();}

								int timer = 10000;
								buttonValueLabel[threadi].setText("Waiting for Game Controller input: "+timer/1000);

								//Controllers.clearEvents();


								boolean stop = false;
								while(stop==false)
								{
									//Controllers.poll();
                                    // GLFW polling is done in ClientMain

									try
									{
										Thread.sleep(100);
									}
									catch (InterruptedException e)
									{

										e.printStackTrace();
									}

									timer-=100;
									if(timer<=0)
									{
										buttonValueLabel[threadi].setText("NONE");
										return;
									}

									buttonValueLabel[threadi].setText("Waiting for Game Controller input: "+timer/1000);


                                    for (int j = GLFW.GLFW_JOYSTICK_1; j <= GLFW.GLFW_JOYSTICK_LAST; j++) {
                                        if (GLFW.glfwJoystickPresent(j)) {
                                            FloatBuffer axes = GLFW.glfwGetJoystickAxes(j);
                                            ByteBuffer buttons = GLFW.glfwGetJoystickButtons(j);

                                            if (axes == null || buttons == null) continue;

                                            float val = 0.0f;

                                            // Left Analog X (0)
                                            if (axes.capacity() > GLFW.GLFW_GAMEPAD_AXIS_LEFT_X) {
                                                val = axes.get(GLFW.GLFW_GAMEPAD_AXIS_LEFT_X);
                                                if(Math.abs(val)>0.5f&&Math.abs(val)<1.0f)
                                                {
                                                    if(val<0)val=-1.0f;
                                                    if(val>0)val=1.0f;

                                                    // Wait for release
                                                    //while(c.getXAxisValue()!=0.0f){Controllers.clearEvents();Controllers.poll();}

                                                    buttonValueLabel[threadi].setText("Left Analog X Axis "+val);

                                                    if(val<0)setButton(threadi,Engine.ControlsManager().gameController_LeftAnalog_XAxis_Negative);
                                                    else setButton(threadi,Engine.ControlsManager().gameController_LeftAnalog_XAxis_Positive);

                                                    Engine.ControlsManager().controller=j;

                                                    return;
                                                }
                                            }

                                            // Left Analog Y (1)
                                            if (axes.capacity() > GLFW.GLFW_GAMEPAD_AXIS_LEFT_Y) {
                                                val = axes.get(GLFW.GLFW_GAMEPAD_AXIS_LEFT_Y);
                                                if(Math.abs(val)>0.5f&&Math.abs(val)<1.0f)
                                                {
                                                    if(val<0)val=-1.0f;
                                                    if(val>0)val=1.0f;

                                                    buttonValueLabel[threadi].setText("Left Analog Y Axis "+val);

                                                    if(val<0)setButton(threadi,Engine.ControlsManager().gameController_LeftAnalog_YAxis_Negative);
                                                    else setButton(threadi,Engine.ControlsManager().gameController_LeftAnalog_YAxis_Positive);

                                                    Engine.ControlsManager().controller=j;

                                                    return;
                                                }
                                            }

                                            // Right Analog X (2 or similar, depends on mapping, but usually 2 or 3)
                                            // Using GLFW_GAMEPAD_AXIS_RIGHT_X = 2
                                            if (axes.capacity() > GLFW.GLFW_GAMEPAD_AXIS_RIGHT_X) {
                                                val = axes.get(GLFW.GLFW_GAMEPAD_AXIS_RIGHT_X);
                                                if(Math.abs(val)>0.5f&&Math.abs(val)<1.0f)
                                                {
                                                    if(val<0)val=-1.0f;
                                                    if(val>0)val=1.0f;

                                                    buttonValueLabel[threadi].setText("Right Analog X Axis "+val);

                                                    if(val<0)setButton(threadi,Engine.ControlsManager().gameController_RightAnalog_XAxis_Negative);
                                                    else setButton(threadi,Engine.ControlsManager().gameController_RightAnalog_XAxis_Positive);

                                                    Engine.ControlsManager().controller=j;

                                                    return;
                                                }
                                            }

                                            // Right Analog Y (3)
                                            // Using GLFW_GAMEPAD_AXIS_RIGHT_Y = 3
                                            if (axes.capacity() > GLFW.GLFW_GAMEPAD_AXIS_RIGHT_Y) {
                                                val = axes.get(GLFW.GLFW_GAMEPAD_AXIS_RIGHT_Y);
                                                if(Math.abs(val)>0.5f&&Math.abs(val)<1.0f)
                                                {
                                                    if(val<0)val=-1.0f;
                                                    if(val>0)val=1.0f;

                                                    buttonValueLabel[threadi].setText("Right Analog Y Axis "+val);

                                                    if(val<0)setButton(threadi,Engine.ControlsManager().gameController_RightAnalog_YAxis_Negative);
                                                    else setButton(threadi,Engine.ControlsManager().gameController_RightAnalog_YAxis_Positive);

                                                    Engine.ControlsManager().controller=j;

                                                    return;
                                                }
                                            }

                                            // Buttons
                                            for(int b=0;b<buttons.capacity();b++)
                                            {
                                                if(buttons.get(b) == GLFW.GLFW_PRESS)
                                                {
                                                    buttonValueLabel[threadi].setText("Button "+b);

                                                    // Wait for release
                                                    //while(c.isButtonPressed(i)!=false){Controllers.clearEvents();Controllers.poll();}

                                                    setButton(threadi,b);

                                                    Engine.ControlsManager().controller=j;

                                                    return;

                                                }

                                            }
                                        }
                                    }
								}

							}

						}
					).start();

				}
			});


			buttonLayout[i] = new DialogLayout();
			buttonLayout[i].setCanAcceptKeyboardFocus(false);

			buttonLayout[i].setHorizontalGroup
			(
					buttonLayout[i].createParallelGroup
					(

						buttonLayout[i].createParallelGroup(buttonLayout[i].createSequentialGroup().addWidget(buttonButton[i]).addGap().addWidgets(buttonLabel[i],buttonValueLabel[i]).addGap())

					)
			);

			buttonLayout[i].setVerticalGroup
			(
					buttonLayout[i].createSequentialGroup
					(

						buttonLayout[i].createSequentialGroup(buttonLayout[i].createParallelGroup(buttonButton[i],buttonLabel[i],buttonValueLabel[i]))

					)
			);


		}

		buttonLabel[0].setText("Up: ");
		buttonLabel[1].setText("Down: ");
		buttonLabel[2].setText("Left: ");
		buttonLabel[3].setText("Right: ");
		buttonLabel[4].setText("Action: ");
		buttonLabel[5].setText("Run/Cancel: ");
		buttonLabel[6].setText("Open nD: ");
		buttonLabel[7].setText("Stuff Menu: ");
		buttonLabel[8].setText("QuickZoom In: ");
		buttonLabel[9].setText("QuickZoom Out: ");




		gameControllerLayout.setHorizontalGroup
		(
				gameControllerLayout.createParallelGroup
				(
						gameControllerLayout.createSequentialGroup().addGap().addGroup(gameControllerLayout.createParallelGroup(buttonLayout)).addGap()
				)
		);

		gameControllerLayout.setVerticalGroup
		(
				gameControllerLayout.createSequentialGroup
				(
					gameControllerLayout.createSequentialGroup(buttonLayout)
				)
		);









		insideLayout.setHorizontalGroup
		(
				insideLayout.createParallelGroup
				(
						insideLayout.createParallelGroup(mainControlsLabel),
						insideLayout.createParallelGroup(keyboardImagePanel),
						//insideLayout.createParallelGroup(otherControlsLabel),
						//insideLayout.createParallelGroup(otherControlsTextLabel),
						//insideLayout.createParallelGroup(scrollDownLabel),
						//insideLayout.createParallelGroup(wasdLabel),
						insideLayout.createParallelGroup(gameControllerSetupLabel),
						insideLayout.createParallelGroup(gameControllerInfoLabel),
						insideLayout.createParallelGroup
						(
								insideLayout.createSequentialGroup().addGap().addGroup(insideLayout.createParallelGroup(gameControllerLayout)).addGap()
						)

				)
		);

		insideLayout.setVerticalGroup
		(
				insideLayout.createSequentialGroup
				(


					insideLayout.createSequentialGroup(mainControlsLabel),
					insideLayout.createSequentialGroup(keyboardImagePanel),
					//insideLayout.createSequentialGroup().addGap(20),
					//insideLayout.createSequentialGroup(otherControlsLabel),
					//insideLayout.createSequentialGroup(otherControlsTextLabel),
					//insideLayout.createSequentialGroup(wasdLabel),
					//insideLayout.createSequentialGroup().addGap(20),
					//insideLayout.createSequentialGroup(scrollDownLabel),
					insideLayout.createSequentialGroup().addGap(40),
					insideLayout.createSequentialGroup(gameControllerSetupLabel),
					insideLayout.createSequentialGroup(gameControllerInfoLabel).addGap(20),
					insideLayout.createSequentialGroup(gameControllerLayout)

				)
		);





	}


	//=========================================================================================================================
	public void setButton(int index, int value)
	{//=========================================================================================================================
		if(index==0)Engine.ControlsManager().JOY_UP = value;
		if(index==1)Engine.ControlsManager().JOY_DOWN = value;
		if(index==2)Engine.ControlsManager().JOY_LEFT = value;
		if(index==3)Engine.ControlsManager().JOY_RIGHT = value;
		if(index==4)Engine.ControlsManager().JOY_ACTION = value;
		if(index==5)Engine.ControlsManager().JOY_RUN = value;
		if(index==6)Engine.ControlsManager().JOY_ND = value;
		if(index==7)Engine.ControlsManager().JOY_STUFF = value;
		if(index==8)Engine.ControlsManager().JOY_ZOOMIN = value;
		if(index==9)Engine.ControlsManager().JOY_ZOOMOUT = value;

	}







}
