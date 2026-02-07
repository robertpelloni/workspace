package com.bobsgame.client.state;
import com.bobsgame.client.LWJGLUtils;


import org.slf4j.LoggerFactory;

import ch.qos.logback.classic.Logger;

import com.bobsgame.client.Cache;
import com.bobsgame.client.engine.game.gui.GUIManager;
import com.bobsgame.client.engine.game.gui.MenuPanel;

import de.matthiasmann.twl.Button;
import de.matthiasmann.twl.DialogLayout;
import de.matthiasmann.twl.GUI;
import de.matthiasmann.twl.Label;
import de.matthiasmann.twl.ScrollPane;
import easing.Easing;

public class LegalScreen extends MenuPanel {
	public static Logger log = (Logger) LoggerFactory.getLogger(LegalScreen.class);

	DialogLayout legalPanel;

	Button noButton;
	Button okButton;

	public LegalScreen() {
		super();

		legalPanel = new DialogLayout();
		legalPanel.setTheme("legalpanel");

		Label legalPanelLabel = new Label("LEGAL");
		legalPanelLabel.setCanAcceptKeyboardFocus(false);
		legalPanelLabel.setTheme("bigLabel");



		Label legalTextLabel = new Label();
		legalTextLabel.setCanAcceptKeyboardFocus(false);
		legalTextLabel.setTheme("fontTahoma11White");
		//legalTextLabel.setFont(new Font());
		//legalTextLabel.setAlignment(Alignment.CENTER);
		legalTextLabel.setText(
			(
			"NO WARRANTY"+"\n"
			+"\n"
			+"This program will download and write data files in \""+Cache.cacheDir+"\" " +"\n"
			+"and do other game-like things such as access your game controller, play sounds, and display graphics. " +"\n"
			+"I am not responsible for any damages, however unlikely. If it blows up your computer and sets your house on fire it is not my fault."+"\n"
			+"\n"
			+"It will also share your IP address with and directly connect to other players. "+"\n"
			+"It is your responsibility to keep your OS updated and firewalled. If someone hacks your unpatched Windows 95® installation it is your problem."+"\n"
			+"\n"
			+"\n"
//			+"If you have a regularly updated OS (or a wireless router) this should be perfectly safe, but I cannot be held "+"\n"
//			+"responsible if your friends are evil superhackers and somehow manage to steal your desktop wallpaper."+"\n"
//			+"\n"
//			+"\n"
			//+"HEALTH AND SAFETY WARNING"+"\n"
			+"MENTAL HEALTH AND SAFETY WARNING"+"\n"
			+"\n"
//			+"Video games are Pavlovian mind control devices designed to break you into obedient, mindless consumers through subconscious" +"\n"
//			+"iconography by binding your wrists and forcing you to watch yourself live your life on a screen during childhood formative years." +"\n"
//			+"This produces an endless crop of hypnotized worker slaves for the industry mind masters to abuse and throw away." +"\n"
			+"If you have epilepsy or some other condition that detracts from your usefulness as a potential brainwashed minion, you may not play this game."+"\n"
			+"That said, if you somehow manage to hurt yourself playing this game, it isn't my fault. May cause insanity and death. (But probably not.)"+"\n"
			+"\n"
			+"\n"
			//+"If you have epilepsy or some other condition that make playing games dangerous, you may not play this game."+"\n"
			//+"If you somehow manage to hurt yourself playing this game, it isn't my fault."+"\n"
			//+"That said, if you somehow manage to hurt yourself playing this game, it isn't my fault. May cause insanity and death. Don't fall off."+"\n"
//			+"Companies are basically big pyramid schemes that leverage psychic power over their customers through reputation. " +"\n"
//			+"If you ever find yourself arguing for or against a brand in an argument, " +"\n"
//			+"you are essentially a cult member and you don't even know it. "+"\n"
//			+"\n"
			//+"While I have made every effort to make this game as addictive and fascinating as possible in my efforts " +"\n"
			//+"to become the ultimate pyramid master, for my own benefit I suggest you take breaks every 15 minutes." +"\n"
			//+"This ensures your brain will get trapped in a cognitive dissonance bondage loop, wanting to play but knowing that it's bad for you. " +"\n"
			//+"This internal conflict will hopefully break your will, making you into a helpless slave under my psychic control." +"\n"
			//+"\n"
			//+"That said, if you somehow manage to hurt yourself, it isn't my fault. "+"\n"
			//+"Also, don't play if you have epilepsy. You shouldn't even be reading this!" +"\n"

			//+"\n"
			+"THE BINDING"+"\n"
			+"\n"
			+"By clicking \"I Agree,\" you agree that you agree to the following agreements:" +"\n"
			//+"I understand that \"Robert Pelloni\" (also known as \"bob\") is an irresponsible madman and"+"\n"
			//+"I agree not to sue or hold him or \"bob's game corporation\" responsible for any reason."+"\n"
			+"I agree not to sue or hold \"Robert Pelloni\" (also known as \"bob\") or his associated company responsible for any reason."+"\n"
			+"I am of legal age or have permission from my legal guardian to agree to a legal agreement and to play this game."+"\n"
			//+"I agree not to share \"spoilers,\" post videos of gameplay or content, or post a \"review\" or preview in any online or print publication."+"\n"//reverse engineer, decompile or disassemble, or copy any content within."+"\n"
			//+"I understand this game is a \"live\" work of art, it is the game \"bob\" wanted to play, and that it is, in fact, \"bob's game\"."//and I will not review it or compare it to other games."+"\n"
//			+"\n"
//			+"I agree to stop purchasing and consuming products designed under the assumption that I am a mindless idiot,"+"\n"
//			+"and instead will seek out intelligent, sincere, and meaningful works produced by true independent artists."+"\n"
//			+"\n"
//			+"I understand that popular gaming websites and magazines are tabloids run by a network of corporate insiders, that the "+"\n"
//			+"commercial \"game industry\" is essentially a racketeering ring, and that most of the \"indie\" games that get promoted are by people"+"\n"
//			+"associated with one of the major industry powers, which actively seek to control the market and prevent outsiders from gaining influence."+"\n"
//			+"I agree to reevaluate my assumptions and to consider that what I read might be a deliberate disinformation or smear campaign run by"+"\n"
//			+"a professional PR firm hired by a multibillion dollar corporate conglomerate, instead of accepting it at face value like a mindless sheep."+"\n"
//			+"I agree to accept this as a serious truth, and to also accept it as a harmless joke when politically advantageous."+"\n"
//			+"I understand this is not a conspiracy theory, but a fact learned through experience with the industry, "+"\n"
//			+"and I agree to research the names and seek out the connections myself instead of dismissing it."+"\n"
//			+"\n"
//			+"I understand that the movie industry is controlled by the ratings board which is run by the same dozen executives that control the theaters and studios."+"\n"
//			+"I realize that politics and corruption infiltrate all industries, and that they would make a law against it, except the politicians were funded by those industries."+"\n"
//			+"\n"
			+""
			)//.toUpperCase()
		);

		okButton = new Button("I Agree");
		okButton.setCanAcceptKeyboardFocus(false);
		okButton.addCallback(new Runnable() {
			@Override
			public void run() {
				doAgree();
			}
		});

		noButton = new Button("I Disagree");
		noButton.setCanAcceptKeyboardFocus(false);
		noButton.addCallback(new Runnable() {
			@Override
			public void run() {
				doDisagree();
			}
		});

		legalPanel.setHorizontalGroup(
				legalPanel.createParallelGroup(
					legalPanel.createParallelGroup().addMinGap(400),
					legalPanel.createSequentialGroup(
						legalPanel.createParallelGroup().addMinGap(50),
						legalPanel.createParallelGroup(
							legalPanel.createSequentialGroup().addGap().addWidget(legalPanelLabel).addGap(),
							legalPanel.createSequentialGroup().addGap().addWidget(legalTextLabel).addGap(),
							legalPanel.createSequentialGroup().addGap().addWidget(noButton).addGap().addWidget(okButton).addGap()
						),
						legalPanel.createParallelGroup().addMinGap(50)
					)
				)
		);

		legalPanel.setVerticalGroup(
			legalPanel.createSequentialGroup(
				legalPanel.createSequentialGroup().addMinGap(20),
				legalPanel.createParallelGroup(legalPanelLabel),
				legalPanel.createSequentialGroup().addMinGap(20),
				legalPanel.createParallelGroup(legalTextLabel),
				legalPanel.createSequentialGroup().addMinGap(20),
				legalPanel.createParallelGroup(okButton, noButton),
				legalPanel.createSequentialGroup().addMinGap(50)
			)
		);

		// layout

		insideScrollPaneLayout.setHorizontalGroup(
			insideScrollPaneLayout.createParallelGroup(
				insideScrollPaneLayout.createSequentialGroup().addGap().addWidget(legalPanel).addGap()
			)
		);

		insideScrollPaneLayout.setVerticalGroup(
			insideScrollPaneLayout.createSequentialGroup(
				insideScrollPaneLayout.createSequentialGroup().addGap(),
				insideScrollPaneLayout.createParallelGroup().addWidget(legalPanel),
				insideScrollPaneLayout.createSequentialGroup().addGap()
			)
		);


		// scrollpane

		scrollPane = new ScrollPane(insideScrollPaneLayout);

		scrollPane.setTheme(GUIManager.scrollPaneTheme);
		scrollPane.setCanAcceptKeyboardFocus(false);
		scrollPane.setExpandContentSize(true);


		//add scrollpane to outside panel

		//mainPanelLayout.add(scrollPane);

		mainPanelLayout.setCanAcceptKeyboardFocus(false);
		mainPanelLayout.setHorizontalGroup(
			mainPanelLayout.createParallelGroup(scrollPane)
		);

		mainPanelLayout.setVerticalGroup(
			mainPanelLayout.createSequentialGroup(scrollPane)
		);

		add(mainPanelLayout);

		legalPanel.adjustSize();

		setActivated(true);
	}

	boolean _clickedOK = false;
	boolean _clickedCancel = false;

	public synchronized boolean clickedOK_S() {
		return _clickedOK;
	}

	public synchronized boolean clickedCancel_S() {
		return _clickedCancel;
	}

	public synchronized void setClickedOK_S(boolean b) {
		_clickedOK = b;
	}

	public synchronized void setClickedCancel_S(boolean b) {
		_clickedCancel = b;
	}

	public void update() {
		if (isActivated == true) {
			if (isScrollingDown == false) {
				ticksSinceTurnedOff = 0;
				ticksSinceTurnedOn += 32;
				scrollUp();
			} else if (isScrollingDown == true) {
				ticksSinceTurnedOn = 0;
				ticksSinceTurnedOff += 32;
				scrollDown();
			}
		}
	}

	public void onScrolledUp() {
		getGUI().setTooltipDelay(1);
	}

	@Override
	protected void layout() {
		// login panel is centered
		legalPanel.adjustSize();
		legalPanel.setPosition(
			insideScrollPaneLayout.getInnerX() + (insideScrollPaneLayout.getInnerWidth() - legalPanel.getWidth()) / 2,
			insideScrollPaneLayout.getInnerY() + (insideScrollPaneLayout.getInnerHeight() - legalPanel.getHeight()) / 2
		);

		super.layout();
	}

	public void setButtonsVisible(boolean b) {
		noButton.setVisible(b);
		okButton.setVisible(b);
	}

	public void scrollDown() {
		if (ticksSinceTurnedOff <= fadeOutTime) {
			screenY = (float) (Easing.easeOutCubic(ticksSinceTurnedOff, 0, LWJGLUtils.SCREEN_SIZE_Y, fadeOutTime));
			layout();
		} else {
			isActivated = false;
			isScrollingDown = false;
			super.setVisible(false);
		}
	}

	void doDisagree() {
		GUI gui = getGUI();
		if (gui != null) {
			setButtonsVisible(false);
			// create thread, this needs to be a thread because Button.doCallback(Runnable) only calls Runnable.run() which does NOT create a thread.
			new Thread(new Runnable() {
				public void run() {
					try {
						Thread.currentThread().setName("Legal_doDisagree");
					} catch (SecurityException e) {
						e.printStackTrace();
					}

					setActivated(false);

					while (isScrollingDown()) {
						try {
							Thread.sleep(500);
						} catch (Exception e){
						}
					}

					setClickedCancel_S(true);
				}
			}).start();
		}
	}

	void doAgree() {
		GUI gui = getGUI();
		if (gui != null) {
			setButtonsVisible(false);

			// create thread, this needs to be a thread because Button.doCallback(Runnable) only calls Runnable.run() which does NOT create a thread.
			new Thread(new Runnable() {
				public void run() {
					try {
						Thread.currentThread().setName("Legal_doOK");
					} catch (SecurityException e) {
						e.printStackTrace();
					}

					setActivated(false);

					while (isScrollingDown()) {
						try {
							Thread.sleep(500);
						} catch (Exception e) {
						}
					}

					setClickedOK_S(true);
				}
			}
			).start();
		}
	}

	public void renderBefore() {
		if (isScrollingDown() == true) return;
		if (isActivated() == false) return;
		// additional rendering calls go here (after gui is drawn)
	}

	public void render() {
		if (isScrollingDown() == true) return;
		if (isActivated() == false) return;
		// additional rendering calls go here (after gui is drawn)
	}
}
