package com.bobsgame.client.engine.text;

import org.slf4j.LoggerFactory;

import ch.qos.logback.classic.Logger;

import com.bobsgame.client.console.Console;
import com.bobsgame.shared.Utils;


//=========================================================================================================================
public class BobFont
{//=========================================================================================================================


	public static Logger log = (Logger) LoggerFactory.getLogger(BobFont.class);




	public static byte[] font_Palette_ByteArray;











	//=========================================================================================================================
	public class BitmapFont
	{//=========================================================================================================================


		public String filename;
		public int maxCharHeight=12;//this is from the very top to the bottom below the baseline, including shadow
		//public int baselineHeight;//this is where the underhang part of "qypgj" starts and most letters end
		//public int shadowWidth;//this is how many pixels past the letter should be drawn but not counted as space

		public int blockHeight=32;//this is the height of each character block, including spacing between glyphs
		public int blockWidth=32;//this is the width of the input bitmap

		public byte[] byteArray = null;//this holds the actual indexed pixel data

		public boolean outlined = false;



		public BitmapFont(String filename, int maxCharHeight, int blockHeight, boolean outlined)
		{
			this.filename = filename;
			this.maxCharHeight = maxCharHeight;
			this.blockHeight=blockHeight;
			this.outlined = outlined;


			byteArray = Utils.loadByteFile(filename);


		}


	}




	//static public byte[] fontTinyByteArray;
	//static public byte[] fontHugeByteArray;



//	font_bob_16_hq2x.bin ... ok
//	font_bob_16_shadow2_hq2x.bin ... ok

//	font_bob_8.bin ... ok
//	font_bob_8_shadow1.bin ... ok

//	font_normal_11.bin ... ok
//	font_normal_11_outlined.bin ... ok
//	font_normal_11_shadow1.bin ... ok

//	font_normal_16_hq2x.bin ... ok
//	font_normal_16_outlined.bin ... ok
//	font_normal_16_outlined_shadow1.bin
//	font_normal_16_shadow_hq2x.bin ...

//	font_normal_8.bin ... ok
//	font_normal_8_outlined.bin ... ok
//	font_normal_8_outlined_shadow1.bin
//	font_normal_8_outlined_shadow2.bin

//	font_normal_8_shadow1.bin ... ok
//	font_normal_8_shadow3.bin ... ok

//	font_small_16_hq2x.bin ... ok
//	font_small_16_shadow3_hq2x.bin ...

//	font_small_8.bin ... ok
//	font_small_8_outlined.bin ... ok
//	font_small_8_shadow1.bin ... ok

	static public BitmapFont font_bob_16;
	static public BitmapFont font_bob_16_shadow2;

	static public BitmapFont font_bob_8;
	static public BitmapFont font_bob_8_shadow1;

	static public BitmapFont font_normal_11;
	static public BitmapFont font_normal_11_outlined;
	static public BitmapFont font_normal_11_shadow1;

	static public BitmapFont font_normal_16;
	static public BitmapFont font_normal_16_outlined_smooth;
	static public BitmapFont font_normal_16_outlined_blocky;
	static public BitmapFont font_normal_16_outlined_blocky_shadow1;
	static public BitmapFont font_normal_16_shadow1;

	static public BitmapFont font_normal_8;
	static public BitmapFont font_normal_8_outlined;
	static public BitmapFont font_normal_8_outlined_shadow1;
	static public BitmapFont font_normal_8_outlined_shadow2;
	static public BitmapFont font_normal_8_shadow1;
	static public BitmapFont font_normal_8_shadow3;

	static public BitmapFont font_small_16;
	static public BitmapFont font_small_16_shadow3;
	static public BitmapFont font_small_16_outlined_smooth;
	static public BitmapFont font_small_16_outlined_smooth_shadow;
	static public BitmapFont font_small_16_outlined_blocky;

	static public BitmapFont font_small_8;
	static public BitmapFont font_small_8_outlined;
	static public BitmapFont font_small_8_shadow1;



	//static public int FONT_TINY_HEIGHT=7;
	//static public int FONT_HUGE_HEIGHT=12;


	//static public int FONT_HUGE_ID=3;
	//static public int FONT_TINY_ID=1;



	//=========================================================================================================================
	public BobFont()
	{//=========================================================================================================================






		font_Palette_ByteArray = Utils.loadByteFile("res/fonts/text.pal");


		//fontTinyByteArray = Utils.HARDWARE_load_file("res/fonts/font_tiny.bin");
		//fontHugeByteArray = Utils.HARDWARE_load_file("res/fonts/font_huge.bin");


		font_bob_16 = new BitmapFont("res/fonts/font_bob_16_hq2x.bin",36,32,false);//fix height
		font_bob_16_shadow2 = new BitmapFont("res/fonts/font_bob_16_hq2x_shadow2.bin",38,32,false);//fix height

		font_bob_8 = new BitmapFont("res/fonts/font_bob_8.bin",20,16,false);//fix height
		font_bob_8_shadow1 = new BitmapFont("res/fonts/font_bob_8_shadow1.bin",22,16,false);//fix height

		font_normal_11 = new BitmapFont("res/fonts/font_normal_11.bin",15,24,false);
		font_normal_11_outlined = new BitmapFont("res/fonts/font_normal_11_outlined.bin",17,24,true);
		font_normal_11_shadow1 = new BitmapFont("res/fonts/font_normal_11_shadow1.bin",16,24,false);

		font_normal_16 = new BitmapFont("res/fonts/font_normal_16_hq2x.bin",20,32,false);
		font_normal_16_outlined_smooth = new BitmapFont("res/fonts/font_normal_16_hq2x_outlined.bin",22,32,true);
		font_normal_16_outlined_blocky = new BitmapFont("res/fonts/font_normal_16_nearest2x_outlined.bin",22,32,true);
		font_normal_16_outlined_blocky_shadow1 = new BitmapFont("res/fonts/font_normal_16_nearest2x_outlined_shadow1.bin",23,32,true);
		font_normal_16_shadow1 = new BitmapFont("res/fonts/font_normal_16_hq2x_shadow.bin",22,32,false);

		font_normal_8 = new BitmapFont("res/fonts/font_normal_8.bin",10,16,false);
		font_normal_8_outlined = new BitmapFont("res/fonts/font_normal_8_outlined.bin",12,16,true);
		font_normal_8_outlined_shadow1 = new BitmapFont("res/fonts/font_normal_8_outlined_shadow1.bin",13,16,true);
		font_normal_8_outlined_shadow2 = new BitmapFont("res/fonts/font_normal_8_outlined_shadow2.bin",14,16,true);
		font_normal_8_shadow1 = new BitmapFont("res/fonts/font_normal_8_shadow1.bin",11,16,false);
		font_normal_8_shadow3 = new BitmapFont("res/fonts/font_normal_8_shadow3.bin",13,16,false);

		font_small_16 = new BitmapFont("res/fonts/font_small_16_hq2x.bin",18,32,false);
		font_small_16_shadow3 = new BitmapFont("res/fonts/font_small_16_hq2x_shadow3.bin",20,32,false);
		font_small_16_outlined_smooth = new BitmapFont("res/fonts/font_small_16_hq2x_outlined.bin",20,32,true);
		font_small_16_outlined_smooth_shadow = new BitmapFont("res/fonts/font_small_16_hq2x_outlined_shadow2.bin",20,32,true);
		font_small_16_outlined_blocky = new BitmapFont("res/fonts/font_small_16_nearest2x_outlined.bin",20,32,true);

		font_small_8 = new BitmapFont("res/fonts/font_small_8.bin",9,16,false);
		font_small_8_outlined = new BitmapFont("res/fonts/font_small_8_outlined.bin",11,16,true);
		font_small_8_shadow1 = new BitmapFont("res/fonts/font_small_8_shadow1.bin",10,16,false);






	}












	//=========================================================================================================================
	public void change_font()
	{//=========================================================================================================================


	}












	static public boolean is_a_vowel(char c)
	{//=========================================================================================================================

		switch(c)
		{
			case 'a':
			case 'e':
			case 'i':
			case 'o':
			case 'u':
			case 'y':
			case 'A':
			case 'E':
			case 'I':
			case 'O':
			case 'U':
			case 'Y': return true;
			default: return false;
		}

	}












	//=========================================================================================================================
	public static int getFontIndexForChar(char c)
	{//=========================================================================================================================
		int i=-1;
		switch(c)
		{
			case 'A': {i=CHAR_A; break;}
			case 'B': {i=CHAR_B; break;}
			case 'C': {i=CHAR_C; break;}
			case 'D': {i=CHAR_D; break;}
			case 'E': {i=CHAR_E; break;}
			case 'F': {i=CHAR_F; break;}
			case 'G': {i=CHAR_G; break;}
			case 'H': {i=CHAR_H; break;}
			case 'I': {i=CHAR_I; break;}
			case 'J': {i=CHAR_J; break;}
			case 'K': {i=CHAR_K; break;}
			case 'L': {i=CHAR_L; break;}
			case 'M': {i=CHAR_M; break;}
			case 'N': {i=CHAR_N; break;}
			case 'O': {i=CHAR_O; break;}
			case 'P': {i=CHAR_P; break;}
			case 'Q': {i=CHAR_Q; break;}
			case 'R': {i=CHAR_R; break;}
			case 'S': {i=CHAR_S; break;}
			case 'T': {i=CHAR_T; break;}
			case 'U': {i=CHAR_U; break;}
			case 'V': {i=CHAR_V; break;}
			case 'W': {i=CHAR_W; break;}
			case 'X': {i=CHAR_X; break;}
			case 'Y': {i=CHAR_Y; break;}
			case 'Z': {i=CHAR_Z; break;}
			case 'a': {i=CHAR_a; break;}
			case 'b': {i=CHAR_b; break;}
			case 'c': {i=CHAR_c; break;}
			case 'd': {i=CHAR_d; break;}
			case 'e': {i=CHAR_e; break;}
			case 'f': {i=CHAR_f; break;}
			case 'g': {i=CHAR_g; break;}
			case 'h': {i=CHAR_h; break;}
			case 'i': {i=CHAR_i; break;}
			case 'j': {i=CHAR_j; break;}
			case 'k': {i=CHAR_k; break;}
			case 'l': {i=CHAR_l; break;}
			case 'm': {i=CHAR_m; break;}
			case 'n': {i=CHAR_n; break;}
			case 'o': {i=CHAR_o; break;}
			case 'p': {i=CHAR_p; break;}
			case 'q': {i=CHAR_q; break;}
			case 'r': {i=CHAR_r; break;}
			case 's': {i=CHAR_s; break;}
			case 't': {i=CHAR_t; break;}
			case 'u': {i=CHAR_u; break;}
			case 'v': {i=CHAR_v; break;}
			case 'w': {i=CHAR_w; break;}
			case 'x': {i=CHAR_x; break;}
			case 'y': {i=CHAR_y; break;}
			case 'z': {i=CHAR_z; break;}
			case '.': {i=CHAR_PERIOD; break;}
			case ',': {i=CHAR_COMMA; break;}
			case '\'':{i=CHAR_QUOTE; break;}// /'
			case '': {i=CHAR_QUOTE; break;}// /'
			case '!': {i=CHAR_EXCLAMATION; break;}
			case '?': {i=CHAR_QUESTIONMARK; break;}
			case '=': {i=CHAR_EQUALS; break;}
			case '\\':{i=CHAR_BACKSLASH; break;}
			case '/': {i=CHAR_FRONTSLASH; break;}
			case '^': {i=CHAR_CARET; break;}
			case '_': {i=CHAR_UNDERSCORE; break;}
			case '&': {i=CHAR_AMPERSAND; break;}
			case '+': {i=CHAR_PLUS; break;}
			case '#': {i=CHAR_POUND; break;}
			case '$': {i=CHAR_DOLLAR; break;}
			case '%': {i=CHAR_PERCENT; break;}
			case '(': {i=CHAR_OPENPARENTHESIS; break;}
			case ')': {i=CHAR_CLOSEPARENTHESIS; break;}
			case '"': {i=CHAR_DOUBLEQUOTE; break;}
			case '*': {i=CHAR_ASTERISK; break;}
			case '-': {i=CHAR_MINUS; break;}
			case ':': {i=CHAR_COLON; break;}
			case ';': {i=CHAR_SEMICOLON; break;}
			case '|': {i=CHAR_PIPE; break;}
			case '`': {i=CHAR_BACKQUOTE; break;}
			case '~': {i=CHAR_TILDE; break;}
			case '@': {i=CHAR_AT; break;}
			case '{': {i=CHAR_OPENCURLYBRACKET; break;}
			case '}': {i=CHAR_CLOSECURLYBRACKET; break;}
			case '[': {i=CHAR_OPENSQUAREBRACKET; break;}
			case ']': {i=CHAR_CLOSESQUAREBRACKET; break;}
			case '0': {i=CHAR_0; break;}
			case '1': {i=CHAR_1; break;}
			case '2': {i=CHAR_2; break;}
			case '3': {i=CHAR_3; break;}
			case '4': {i=CHAR_4; break;}
			case '5': {i=CHAR_5; break;}
			case '6': {i=CHAR_6; break;}
			case '7': {i=CHAR_7; break;}
			case '8': {i=CHAR_8; break;}
			case '9': {i=CHAR_9; break;}

			case 'Ñ': {i=CHAR_dN; break;}
			case 'á': {i=CHAR_aa; break;}
			case 'é': {i=CHAR_ae; break;}
			case 'í': {i=CHAR_ai; break;}
			case 'ó': {i=CHAR_ao; break;}
			case 'ú': {i=CHAR_au; break;}
			case 'ñ': {i=CHAR_dn; break;}
			case '¡': {i=CHAR_iE; break;}
			case '¿': {i=CHAR_iQ; break;}
			case 'É': {i=CHAR_aE; break;}
			case 'Í': {i=CHAR_aI; break;}
			case 'Á': {i=CHAR_aA; break;}

			case '»': {i=CHAR_RR; break;}
			case '«': {i=CHAR_LL; break;}
			case 'â': {i=CHAR_ca; break;}
			case 'ê': {i=CHAR_ce; break;}
			case 'î': {i=CHAR_ci; break;}
			case 'ô': {i=CHAR_co; break;}
			case 'û': {i=CHAR_cu; break;}
			case 'à': {i=CHAR_ga; break;}
			case 'è': {i=CHAR_ge; break;}
			case 'ë': {i=CHAR_de; break;}
			case 'ç': {i=CHAR_cc; break;}
			case '': {i=CHAR_lo; break;}

			case 'Ó': {i=CHAR_aO; break;}
			case 'ù': {i=CHAR_gu; break;}

			case 'Ï': {i=CHAR_dI; break;}
			case 'Ä': {i=CHAR_dA; break;}
			case 'Ö': {i=CHAR_dO; break;}
			case 'Ü': {i=CHAR_dU; break;}
			case 'ä': {i=CHAR_da; break;}
			case 'ö': {i=CHAR_do; break;}
			case 'ü': {i=CHAR_du; break;}
			case 'ß': {i=CHAR_dB; break;}


			case ' ': {i=CHAR_SPACE; break;}

			case '\n':{i=-1;break;}

			case '<':{
						String e = "Parsed a '<'.";
						Console.error(e);
						log.error(e);

						i=-1;
						break;
					}
			case '>':{
						String e = "Parsed a '>'.";
						Console.error(e);
						log.error(e);

						i=-1;
						break;
					}

			default: {i=CHAR_BLOCK;break;}
		}

		return i;
	}












	//=========================================================================================================================
	static int getNextWordLength(String text, int in_position, BitmapFont font)
	{//=========================================================================================================================

		int next_word_length=0;

		int length = text.length();

		int temp_position=in_position;

		while(
				temp_position<length
				&&
				//we should be starting on a space or the beginning of the test. include the starting space, up to the next space
				(text.charAt(temp_position)!=' '||temp_position==in_position)//if it's the start of the string or it's not a space
				&&
				isCurrentPositionANewline(text,temp_position)==false
				//&&
				//text.charAt(temp_position)!='<'

		)
		{
			//skip over tags
			if(temp_position<length&&text.charAt(temp_position)=='<')
			{
				int x=0;
				while(temp_position+x<length&&text.charAt(temp_position+x)!='>')
				{
					x++;
				}
				temp_position+=x;
				temp_position++;//for the '>'

				continue;
			}

			if(temp_position<length)
			{
				next_word_length+=getCharWidth(BobFont.getFontIndexForChar(text.charAt(temp_position)), font);
				//add a space between letters for all fonts but outlined
				//if(font_id!=Font.FONT_OUTLINED_ID)
					next_word_length++;

				temp_position++;
			}
		}



		return next_word_length;
	}




	//=========================================================================================================================
	static boolean isCurrentPositionANewline(String t, int position)
	{//=========================================================================================================================
		if(
				(t.charAt(position)=='\n')//or its a newline
				||
				(position<t.length()-1&&t.charAt(position)=='<'&&t.charAt(position+1)=='.')//newline
				||
				(
						position<t.length()-2&&
						t.charAt(position)=='<'&&
						t.charAt(position+1)=='N'&&
						t.charAt(position+2)=='E'
				)
		)
		{

			return true;
		}
		else
		return false;
	}









	//=========================================================================================================================
	static int getFontPixelValueAtIndex(int index, BitmapFont font)
	{//=========================================================================================================================

		if(index>font.byteArray.length)return -1;
		return font.byteArray[index];



	}












	//=========================================================================================================================
	static int getCharWidth(int letter_index, BitmapFont font)
	{//=========================================================================================================================

		if(letter_index==-1)return 0;

		int x=0;
		int y=0;
		int w=0;
		for(x=font.blockWidth-1;x>=0;x--)
			for(y=0;y<font.maxCharHeight;y++)
				if(BobFont.getFontPixelValueAtIndex((letter_index*font.blockWidth*font.blockHeight)+(y*font.blockWidth)+x, font)!=0)
				{
					w=x+1;
					x=-1;
					y=font.maxCharHeight;
					break;
				}

		if(letter_index==BobFont.getFontIndexForChar(' '))
		{
			w=3;

			if(font.maxCharHeight>10)w=5;

			//WIDTH OF SPACE IS DETERMINED HERE //was 3?
		}

		return w;
	}






	//=========================================================================================================================
//		 CHAR DEFINES
	//=========================================================================================================================

	static public int CHAR_A							=0;
	static public int CHAR_B							=1;
	static public int CHAR_C							=2;
	static public int CHAR_D							=3;
	static public int CHAR_E							=4;
	static public int CHAR_F							=5;
	static public int CHAR_G							=6;
	static public int CHAR_H							=7;
	static public int CHAR_I							=8;
	static public int CHAR_J							=9;
	static public int CHAR_K							=10;
	static public int CHAR_L							=11;
	static public int CHAR_M							=12;
	static public int CHAR_N							=13;
	static public int CHAR_O							=14;
	static public int CHAR_P							=15;
	static public int CHAR_Q							=16;
	static public int CHAR_R							=17;
	static public int CHAR_S							=18;
	static public int CHAR_T							=19;
	static public int CHAR_U							=20;
	static public int CHAR_V							=21;
	static public int CHAR_W							=22;
	static public int CHAR_X							=23;
	static public int CHAR_Y							=24;
	static public int CHAR_Z							=25;
	static public int CHAR_a							=26;
	static public int CHAR_b							=27;
	static public int CHAR_c							=28;
	static public int CHAR_d							=29;
	static public int CHAR_e							=30;
	static public int CHAR_f							=31;
	static public int CHAR_g							=32;
	static public int CHAR_h							=33;
	static public int CHAR_i							=34;
	static public int CHAR_j							=35;
	static public int CHAR_k							=36;
	static public int CHAR_l							=37;
	static public int CHAR_m							=38;
	static public int CHAR_n							=39;
	static public int CHAR_o							=40;
	static public int CHAR_p							=41;
	static public int CHAR_q							=42;
	static public int CHAR_r							=43;
	static public int CHAR_s							=44;
	static public int CHAR_t							=45;
	static public int CHAR_u							=46;
	static public int CHAR_v							=47;
	static public int CHAR_w							=48;
	static public int CHAR_x							=49;
	static public int CHAR_y							=50;
	static public int CHAR_z							=51;
	static public int CHAR_0							=52;
	static public int CHAR_1							=53;
	static public int CHAR_2							=54;
	static public int CHAR_3							=55;
	static public int CHAR_4							=56;
	static public int CHAR_5							=57;
	static public int CHAR_6							=58;
	static public int CHAR_7							=59;
	static public int CHAR_8							=60;
	static public int CHAR_9							=61;
	static public int CHAR_EXCLAMATION					=62;
	static public int CHAR_QUESTIONMARK			=63;
	static public int CHAR_PERIOD					=64;
	static public int CHAR_COMMA					=65;
	static public int CHAR_QUOTE					=66;
	static public int CHAR_DOUBLEQUOTE			=67;
	static public int CHAR_COLON					=68;
	static public int CHAR_SEMICOLON				=69;
	static public int CHAR_FRONTSLASH				=70;
	static public int CHAR_BACKSLASH				=71;
	static public int CHAR_ASTERISK				=72;
	static public int CHAR_PLUS						=73;
	static public int CHAR_MINUS					=74;
	static public int CHAR_EQUALS					=75;
	static public int CHAR_UNDERSCORE				=76;
	static public int CHAR_CARET					=77;
	static public int CHAR_BACKQUOTE				=78;
	static public int CHAR_TILDE					=79;
	static public int CHAR_OPENPARENTHESIS		=80;
	static public int CHAR_CLOSEPARENTHESIS		=81;
	static public int CHAR_OPENANGLEBRACKET		=82;
	static public int CHAR_CLOSEANGLEBRACKET	=83;
	static public int CHAR_OPENCURLYBRACKET		=84;
	static public int CHAR_CLOSECURLYBRACKET	=85;
	static public int CHAR_OPENSQUAREBRACKET	=86;
	static public int CHAR_CLOSESQUAREBRACKET	=87;
	static public int CHAR_PIPE						=88;
	static public int CHAR_AT						=89;
	static public int CHAR_POUND					=90;
	static public int CHAR_DOLLAR					=91;
	static public int CHAR_PERCENT					=92;
	static public int CHAR_AMPERSAND				=93;
	static public int CHAR_BLOCK					=94;
	static public int CHAR_SPACE					=95;

	//spanish
	static public int CHAR_dN		=96;
	static public int CHAR_aa		=97;
	static public int CHAR_ae		=98;
	static public int CHAR_ai		=99;
	static public int CHAR_ao		=100;
	static public int CHAR_au		=101;
	static public int CHAR_dn		=102;
	static public int CHAR_iE		=103;
	static public int CHAR_iQ		=104;
	static public int CHAR_aE		=105;
	static public int CHAR_aI		=106;
	static public int CHAR_aA		=107;

	//�
	//�
	//�
	//�
	//�
	//�
	//�
	//�
	//�
	//�
	//�
	//�



	//french
	static public int CHAR_RR		=108;
	static public int CHAR_LL		=109;
	static public int CHAR_ca		=110;
	static public int CHAR_ce		=111;
	static public int CHAR_ci		=112;
	static public int CHAR_co		=113;
	static public int CHAR_cu		=114;
	static public int CHAR_ga		=115;
	static public int CHAR_ge		=116;
	static public int CHAR_de		=117;
	static public int CHAR_cc		=118;
	static public int CHAR_lo		=119;

	static public int CHAR_aO		=120;
	static public int CHAR_gu		=121;


	//�
	//�
	//�
	//�
	//�
	//�
	//�
	//�
	//�
	//�
	//�
	//�

	//�
	//�


	static public int CHAR_dI		=122;
	static public int CHAR_dA		=123;
	static public int CHAR_dO		=124;
	static public int CHAR_dU		=125;
	static public int CHAR_da		=126;
	static public int CHAR_do		=127;
	static public int CHAR_du		=128;
	static public int CHAR_dB		=129;

	//�
	//�
	//�
	//�
	//�
	//�
	//�
	//�








}
