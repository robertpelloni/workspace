package com.bobsgame.shared;

import java.awt.Color;
import java.lang.reflect.Field;
import java.lang.reflect.Modifier;
import java.nio.FloatBuffer;
import java.util.Locale;

//import java.awt.Color;
//import de.matthiasmann.twl.Color;
//import org.newdawn.slick.Color;
//import org.lwjgl.util.Color;


public class BobColor extends java.awt.Color
{











	//BobColor lighter = null;
	//BobColor darker = null;






	static public BobColor clear	= new BobColor(0, 0, 0, 0);
	static public BobColor CLEAR	= clear;
	static public BobColor transparent	= clear;
	static public BobColor TRANSPARENT	= clear;








	static public BobColor black = new BobColor(0,0,0);
	static public BobColor BLACK = black;

	static public BobColor darkerGray=new BobColor(0.2f,0.2f,0.2f);
	static public BobColor DARKERGRAY=darkerGray;

	static public BobColor darkGray = new BobColor(0.35f,0.35f,0.35f);
	static public BobColor DARKGRAY = darkGray;
	static public BobColor DARK_GRAY = darkGray;

	static public BobColor gray = new BobColor(0.5f,0.5f,0.5f);
	static public BobColor GRAY = gray;

	static public BobColor lightGray = new BobColor(0.65f,0.65f,0.65f);
	static public BobColor LIGHTGRAY = lightGray;
	static public BobColor LIGHT_GRAY = lightGray;

	static public BobColor lighterGray=new BobColor(0.8f,0.8f,0.8f);
	static public BobColor LIGHTERGRAY=lighterGray;

	static public BobColor white = new BobColor(1.0f,1.0f,1.0f);
	static public BobColor WHITE = white;



	//-----------------------------------------

	public static BobColor cyan = new BobColor(0,255,255);//, lightCyan, darkCyan);
	public static BobColor CYAN = cyan;

	static public BobColor lightCyan=cyan.lighter();//new BobColor(150,255,255);
	static public BobColor LIGHTCYAN=lightCyan;

	static public BobColor darkCyan=cyan.darker();//new BobColor(0,220,220);
	static public BobColor DARKCYAN=darkCyan;

	static public BobColor darkerCyan=cyan.darker().darker();//new BobColor(0,180,180);
	static public BobColor DARKERCYAN=darkerCyan;



	//-----------------------------------------


	public static BobColor magenta	= new BobColor(255, 0, 127);//, lightMagenta, darkMagenta);
	public static BobColor MAGENTA	= magenta;

	static public BobColor lightMagenta=magenta.lighter();//new BobColor(255,120,127);
	static public BobColor LIGHTMAGENTA=lightMagenta;

	static public BobColor darkMagenta=magenta.darker();//new BobColor(150,0,75);
	static public BobColor DARKMAGENTA=darkMagenta;

	static public BobColor darkerMagenta=magenta.darker().darker();//new BobColor(127,0,64);
	static public BobColor DARKERMAGENTA=darkerMagenta;




	//-----------------------------------------


	static public BobColor yellow=new BobColor(255,255,0);//, lightYellow, darkYellow);
	static public BobColor YELLOW=yellow;

	static public BobColor lightYellow=yellow.lighter();//new BobColor(255,255,127);
	static public BobColor LIGHTYELLOW=lightYellow;

	static public BobColor darkYellow=yellow.darker();//new BobColor(200,200,0);
	static public BobColor DARKYELLOW=darkYellow;


	static public BobColor darkerYellow=yellow.darker().darker();//new BobColor(127,127,0);
	static public BobColor DARKERYELLOW=darkerYellow;




	//-----------------------------------------

	static public BobColor orange=new BobColor(255, 140, 0);//, lightOrange, darkOrange);
	static public BobColor ORANGE=orange;

	static public BobColor lightOrange=orange.lighter();//new BobColor(255, 190, 110);
	static public BobColor LIGHTORANGE=lightOrange;

	static public BobColor darkOrange=orange.darker();//new BobColor(220, 115, 0);
	static public BobColor DARKORANGE=darkOrange;

	static public BobColor darkerOrange=orange.darker().darker();//new BobColor(150, 90, 0);
	static public BobColor DARKERORANGE=darkerOrange;



	//-----------------------------------------

	static public BobColor red=new BobColor(255,0,0);//, lightRed, darkRed);
	static public BobColor RED=red;

	static public BobColor lightRed=red.lighter();//new BobColor(255,127,127);
	static public BobColor LIGHTRED=lightRed;

	static public BobColor darkRed=red.darker();//new BobColor(127,0,0);
	static public BobColor DARKRED=darkRed;

	static public BobColor darkerRed=red.darker().darker();//new BobColor(64,0,0);
	static public BobColor DARKERRED=darkerRed;




	//-----------------------------------------

	static public BobColor pink      = new BobColor(255, 0, 255);//, lightPink, darkPink);
	static public BobColor PINK      = pink;

	static public BobColor lightPink=pink.lighter();//new BobColor(255, 127, 255);
	static public BobColor LIGHTPINK=lightPink;

	static public BobColor darkPink=pink.darker();//new BobColor(127, 0, 127);
	static public BobColor DARKPINK=darkPink;

	static public BobColor darkerPink=pink.darker().darker();//new BobColor(64, 0, 64);
	static public BobColor DARKERPINK=darkerPink;



	//-----------------------------------------


	static public BobColor purple=new BobColor(127,0,255);//, lightPurple, darkPurple);
	static public BobColor PURPLE=purple;

	static public BobColor darkPurple=purple.darker();//new BobColor(63,0,127);
	static public BobColor DARKPURPLE=darkPurple;

	static public BobColor darkerPurple=purple.darker().darker();//new BobColor(47,0,95);
	static public BobColor DARKERPURPLE=darkerPurple;

	static public BobColor lightPurple=purple.lighter();//new BobColor(159,63,255);
	static public BobColor LIGHTPURPLE=lightPurple;


	//-----------------------------------------

	static public BobColor blue = new BobColor(0,0,255);//, lightBlue, darkBlue);
	static public BobColor BLUE = blue;

	static public BobColor lightBlue=blue.lighter();//new BobColor(150,150,255);
	static public BobColor LIGHTBLUE=lightBlue;

	static public BobColor darkBlue=blue.darker();//new BobColor(0,0,150);
	static public BobColor DARKBLUE=darkBlue;

	static public BobColor darkerBlue=blue.darker().darker();//new BobColor(0,0,64);
	static public BobColor DARKERBLUE=darkerBlue;



	//-----------------------------------------

	static public BobColor green = new BobColor(0,255,0);
	static public BobColor GREEN = green;

	static public BobColor lighterGreen=green.lighter().lighter();
	static public BobColor LIGHTERGREEN=lighterGreen;

	static public BobColor lightGreen=green.lighter();
	static public BobColor LIGHTGREEN=lightGreen;

	static public BobColor darkGreen=green.darker();
	static public BobColor DARKGREEN=darkGreen;

	static public BobColor darkerGreen=green.darker().darker();
	static public BobColor DARKERGREEN=darkerGreen;

	//-----------------------------------------

	static public BobColor aqua = new BobColor(0,150,255);
	static public BobColor AQUA = aqua;

	static public BobColor lighterAqua=aqua.lighter().lighter();
	static public BobColor LIGHTERAQUA=lighterAqua;

	static public BobColor lightAqua=aqua.lighter();
	static public BobColor LIGHTAQUA=lightAqua;

	static public BobColor darkAqua=aqua.darker();
	static public BobColor DARKAQUA=darkAqua;

	static public BobColor darkerAqua=aqua.darker().darker();
	static public BobColor DARKERAQUA=darkerAqua;


	//-----------------------------------------

	static public BobColor turquoise = new BobColor(0,255,150);
	static public BobColor TURQUOISE = turquoise;

	static public BobColor lighterTurquoise=turquoise.lighter().lighter();
	static public BobColor LIGHTERTURQUOISE=lighterTurquoise;

	static public BobColor lightTurquoise=turquoise.lighter();
	static public BobColor LIGHTTURQUOISE=lightTurquoise;

	static public BobColor darkTurquoise=turquoise.darker();
	static public BobColor DARKTURQUOISE=darkTurquoise;

	static public BobColor darkerTurquoise=turquoise.darker().darker();
	static public BobColor DARKERTURQUOISE=darkerTurquoise;


	//-----------------------------------------



	static public BobColor olive=new BobColor(64,72,0);
	static public BobColor burgandy=new BobColor(220,70,0);
	static public BobColor wine=new BobColor(200,80,0);

	/**
	 * Copy constructor
	 *
	 * @param color The color to copy into the new instance
	 */
	public BobColor(BobColor color)
	{
		super(color.rf(),color.gf(),color.bf(),color.af());
	}

	public BobColor(BobColor color, float a)
	{
		super(color.rf(),color.gf(),color.bf(),(float)a);
	}

	public BobColor(java.awt.Color color)
	{
		super(color.getRed(),color.getGreen(),color.getBlue(),color.getAlpha());
	}

//	public BobColor(de.matthiasmann.twl.Color color)
//	{
//		super(color.getRedFloat(),color.getGreenFloat(),color.getBlueFloat(),color.getAlphaFloat());
//	}

//	public BobColor(org.newdawn.slick.Color color)
//	{
//		super(color.getRed(),color.getGreen(),color.getBlue(),color.getAlpha());
//	}

//	public BobColor(org.lwjgl.util.Color color)
//	{
//		super(color.getRed(),color.getGreen(),color.getBlue(),color.getAlpha());
//	}
	/**
	 * Create a component based on the first 4 elements of a float buffer
	 *
	 * @param buffer The buffer to read the color from
	 */
	public BobColor(FloatBuffer buffer)
	{
		this(buffer.get(),buffer.get(),buffer.get(),buffer.get());
	}


//
//	public BobColor(int rgb, boolean hasAlpha)
//	{
//		super(rgb,hasAlpha);
//
//	}



	/**
	 * Create a 3 component color
	 *
	 * @param r The red component of the color (0.0f -> 1.0f)
	 * @param g The green component of the color (0.0f -> 1.0f)
	 * @param b The blue component of the color (0.0f -> 1.0f)
	 */
	public BobColor(float r,float g,float b)
	{
		super((float)Math.min(r,1.0f),(float)Math.min(g,1.0f),(float)Math.min(b,1.0f));
	}


	public BobColor(float r,float g,float b,float a)
	{
		super((float)Math.min(r,1.0f),(float)Math.min(g,1.0f),(float)Math.min(b,1.0f),(float)Math.min(a,1.0f));
	}


	public BobColor(int r,int g,int b)
	{
		super((int)Math.min(r,255.0f),(int)Math.min(g,255.0f),(int)Math.min(b,255.0f));
	}

//	public BobColor(int r,int g,int b, BobColor light, BobColor dark)
//	{
//		super((int)Math.min(r,255.0f),(int)Math.min(g,255.0f),(int)Math.min(b,255.0f));
//		//this.lighter = light;
//		//this.darker = dark;
//	}

	public BobColor(int r,int g,int b,int a)
	{
		super((int)Math.min(r,255.0f),(int)Math.min(g,255.0f),(int)Math.min(b,255.0f),(int)Math.min(a,255.0f));
	}

//	public BobColor(int value)
//	{
//		super(value,true);
//
//		int r = (value & 0x00FF0000) >> 16;
//		int g = (value & 0x0000FF00) >> 8;
//		int b =	(value & 0x000000FF);
//		int a = (value & 0xFF000000) >> 24;
//
//		if (a < 0) {
//			a += 256;
//		}
//		if (a == 0) {
//			a = 255;
//		}
//
//		this.r = r / 255.0f;
//		this.g = g / 255.0f;
//		this.b = b / 255.0f;
//		this.a = a / 255.0f;
//	}
//


	public float rf(){return getRed()/255.0f;}
	public float gf(){return getGreen()/255.0f;}
	public float bf(){return getBlue()/255.0f;}
	public float af(){return getAlpha()/255.0f;}

	public float r(){return getRed()/255.0f;}
	public float g(){return getGreen()/255.0f;}
	public float b(){return getBlue()/255.0f;}
	public float a(){return getAlpha()/255.0f;}

	public int ri(){return getRed();}
	public int gi(){return getGreen();}
	public int bi(){return getBlue();}
	public int ai(){return getAlpha();}

	public byte rb(){return (byte)getRed();}
	public byte gb(){return (byte)getGreen();}
	public byte bb(){return (byte)getBlue();}
	public byte ab(){return (byte)getAlpha();}

	public boolean hasAlpha(){return getAlpha()<255;}

	/**
	 * Decode a number in a string and process it as a color
	 * reference.
	 *
	 * @param nm The number string to decode
	 * @return The color generated from the number read
	 */
	public static BobColor decode(String nm) {
		return new BobColor(Integer.decode(nm).intValue());
	}

	/**
	 * Bind this color to the GL context
	 */
//	public void bind()
//	{
//		glColor4f(r,g,b,a);
//	}

//	/**
//	 * @see java.lang.Object#hashCode()
//	 */
//	public int hashCode() {
//		return ((int) (rf()+gf()+bf()+af())*255);
//	}

	/**
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
//	public boolean equals(Object other) {
//		if (other instanceof BobColor) {
//			BobColor o = (BobColor) other;
//			return ((o.r() == r()) && (o.g() == g()) && (o.b() == b()) && (o.a() == a()));
//		}
//
//		return false;
//	}



	/**
	 * Make a darker instance of this color
	 *
	 * @return The darker version of this color
	 */
	public BobColor darker() {
		//if(darker!=null)return darker;

		return darker(0.4f);
	}

	/**
	 * Make a darker instance of this color
	 *
	 * @param scale The scale down of RGB (i.e. if you supply 0.0f3 the color will be darkened by 3%)
	 * @return The darker version of this color
	 */
	public BobColor darker(float scale)
	{



		scale = 1 - scale;

		float[] hsbvals = RGBtoHSB(ri(),gi(),bi(),null);


		//if already darkest increase saturation
		if(hsbvals[2]==0.0f)
		{
			hsbvals[1]*=1.0f/scale;
			if(hsbvals[1]>1.0f)hsbvals[1]=1.0f;
		}

		hsbvals[2]*=scale;
		if(hsbvals[2]<0.0f)hsbvals[2]=0.0f;


		//BobColor temp = new BobColor(rf() * scale, gf() * scale, bf() * scale, af());

		BobColor temp = new BobColor(HSBtoRGB(hsbvals[0],hsbvals[1],hsbvals[2]));

		temp = new BobColor(temp.rf(),temp.gf(),temp.bf(),this.af());

		return temp;
	}

	/**
	 * Make a lighter instance of this color
	 *
	 * @return The lighter version of this color
	 */
	public BobColor lighter() {

		//if(lighter!=null)return lighter;

		return lighter(0.4f);
	}


	public BobColor brighter() {

		return lighter(0.4f);
	}
	/**
	 * Make a brighter instance of this color
	 *
	 * @param scale The scale up of RGB (i.e. if you supply 0.0f3 the color will be brightened by 3%)
	 * @return The brighter version of this color
	 */
	public BobColor lighter(float scale)
	{

		if(scale<1.0f)scale += 1.0f;


		float[] hsbvals = RGBtoHSB(ri(),gi(),bi(),null);

		//if already lightest, decrease saturation instead
		if(hsbvals[2]==1.0f)
		{
			hsbvals[1]*=1.0f/scale;
			if(hsbvals[1]<0.0f)hsbvals[1]=0.0f;
		}

		hsbvals[2]*=scale;
		if(hsbvals[2]>1.0f)hsbvals[2]=1.0f;


		//BobColor temp = new BobColor(rf() * scale, gf() * scale, bf() * scale, af());

		BobColor temp = new BobColor(HSBtoRGB(hsbvals[0],hsbvals[1],hsbvals[2]));

		temp = new BobColor(temp.rf(),temp.gf(),temp.bf(),this.af());

//		float r = rf();
//		float g = rf();
//		float b = rf();
//
//		if(r==0)r=0.1f;
//		if(g==0)g=0.1f;
//		if(b==0)b=0.1f;
//
//		if(scale<1.0f)scale += 1.0f;
//
//		BobColor temp = new BobColor(r * scale, g * scale, b * scale, af());

		return temp;
	}

	/**
	 * Multiply this color by another
	 *
	 * @param c the other color
	 * @return product of the two colors
	 */
	public BobColor multiply(BobColor c)
	{
		return new BobColor(rf() * c.rf(), gf() * c.gf(), bf() * c.bf(), af() * c.af());
	}



	/**
	 * Add another color to this one
	 *
	 * @param c The color to add
	 * @return The copy which has had the color added to it
	 */
	public BobColor addToCopy(BobColor c)
	{
		return new BobColor(rf()+c.rf(),gf()+c.gf(),bf()+c.bf(),af()+c.af());
	}

	/**
	 * Scale the components of the color by the given value
	 *
	 * @param value The value to scale by
	 * @return The copy which has been scaled
	 */
	public BobColor scaleCopy(float value)
	{
		return new BobColor(rf()*value,gf()*value,bf()*value,af()*value);
	}



	public static BobColor getHSBColor(float h, float s, float b)
	{
		return new BobColor(HSBtoRGB(h, s, b));
	}




















	//============================================
	//============================================
	//============================================
	//============================================
	//============================================
	//============================================

	// TWL Color

	//============================================
	//============================================
	//============================================
	//============================================
	//============================================
	//============================================







// public static final BobColor BLACK = new BobColor(0xFF000000);
	public static final BobColor SILVER = new BobColor(0xFFC0C0C0);
	//public static final BobColor GRAY = new BobColor(0xFF808080);
	//public static final BobColor WHITE = new BobColor(0xFFFFFFFF);
	public static final BobColor MAROON = new BobColor(0xFF800000);
// public static final BobColor RED = new BobColor(0xFFFF0000);
// public static final BobColor PURPLE = new BobColor(0xFF800080);
	public static final BobColor FUCHSIA = new BobColor(0xFFFF00FF);
	//public static final BobColor GREEN = new BobColor(0xFF008000);
	public static final BobColor LIME = new BobColor(0xFF00FF00);
	public static final BobColor OLIVE = new BobColor(0xFF808000);
// public static final BobColor ORANGE = new BobColor(0xFFFFA500);
// public static final BobColor YELLOW = new BobColor(0xFFFFFF00);
	public static final BobColor NAVY = new BobColor(0xFF000080);
	//public static final BobColor BLUE = new BobColor(0xFF0000FF);
	public static final BobColor TEAL = new BobColor(0xFF008080);
	//public static final BobColor AQUA = new BobColor(0xFF00FFFF);
	public static final BobColor SKYBLUE = new BobColor(0xFF87CEEB);

// public static final BobColor LIGHTBLUE    = new BobColor(0xFFADD8E6);
	public static final BobColor LIGHTCORAL   = new BobColor(0xFFF08080);
	//public static final BobColor LIGHTCYAN    = new BobColor(0xFFE0FFFF);
// public static final BobColor LIGHTGRAY    = new BobColor(0xFFD3D3D3);
// public static final BobColor LIGHTGREEN   = new BobColor(0xFF90EE90);
// public static final BobColor LIGHTPINK    = new BobColor(0xFFFFB6C1);
	public static final BobColor LIGHTSALMON  = new BobColor(0xFFFFA07A);
	public static final BobColor LIGHTSKYBLUE = new BobColor(0xFF87CEFA);
// public static final BobColor LIGHTYELLOW  = new BobColor(0xFFFFFFE0);

// public static final BobColor TRANSPARENT = new BobColor(0);














	//TODO: handle 16 bit BGR

	//TODO: handle all system palette colors

	//TODO: use real color descriptions and standards for "magenta" "fuschia" "rust" etc.

	//TODO: have more color conversion stuff. improve brighter/darker by converting to HSL and upping L


	public BobColor(int rgb) {

		this((rgb >> 16) & 0xFF, (rgb >> 8) & 0xFF, (rgb >> 0) & 0xFF);

	}

	public BobColor(int argb, boolean b) {

		this((argb >> 16) & 0xFF, (argb >> 8) & 0xFF, (argb >> 0) & 0xFF ,b?(argb >> 24) & 0xFF:255);

	}

	public int toARGB() {
		return ((ai() & 0xFF) << 24) |
				((ri() & 0xFF) << 16) |
				((gi() & 0xFF) <<  8) |
				((bi() & 0xFF)      );
	}


//    public float getRedFloat() {
//        return (r & 255) / 255f;
//    }
//
//    public float getGreenFloat() {
//        return (g & 255) / 255f;
//    }
//
//    public float getBlueFloat() {
//        return (b & 255) / 255f;
//    }
//
//    public float getAlphaFloat() {
//        return (a & 255) / 255f;
//    }

	public void getFloats(float[] dst, int off) {
		dst[off+0] = r();
		dst[off+1] = g();
		dst[off+2] = b();
		dst[off+3] = a();
	}

	/**
	 * Retrieves a color by it's name. This uses the case insensitive lookup
	 * for the color constants defined in this class.
	 *
	 * @param name the color name to lookup
	 * @return a Color or null if the name was not found
	 */
	public static BobColor getColorByName(String name) {
		name = name.toUpperCase(Locale.ENGLISH);
		try {
			Field f = BobColor.class.getField(name);
			if(Modifier.isStatic(f.getModifiers()) && f.getType() == BobColor.class) {
				return (BobColor)f.get(null);
			}
		} catch (Throwable ex) {
			// ignore
		}
		return null;
	}

	/**
	 * Parses a numeric or symbolic color. Symbolic names are resolved by getColorByName
	 *
	 * The following hex formats are supported:
	 * #RGB
	 * #ARGB
	 * #RRGGBB
	 * #AARRGGBB
	 *
	 * @param value the color to parse
	 * @return a Color object or null
	 * @throws NumberFormatException if the hex color code can't be parsed
	 * @see #getColorByName(java.lang.String)
	 */
	public static BobColor parserColor(String value) throws NumberFormatException {
		if(value.length() > 0 && value.charAt(0) == '#') {
			String hexcode = value.substring(1);
			switch (value.length()) {
				case 4: {
					int rgb4 = Integer.parseInt(hexcode, 16);
					int r = ((rgb4 >> 8) & 0xF) * 0x11;
					int g = ((rgb4 >> 4) & 0xF) * 0x11;
					int b = ((rgb4     ) & 0xF) * 0x11;
					return new BobColor(0xFF000000 | (r << 16) | (g << 8) | b);
				}
				case 5: {
					int rgb4 = Integer.parseInt(hexcode, 16);
					int a = ((rgb4 >> 12) & 0xF) * 0x11;
					int r = ((rgb4 >>  8) & 0xF) * 0x11;
					int g = ((rgb4 >>  4) & 0xF) * 0x11;
					int b = ((rgb4      ) & 0xF) * 0x11;
					return new BobColor((a << 24) | (r << 16) | (g << 8) | b);
				}
				case 7:
					return new BobColor(0xFF000000 | Integer.parseInt(hexcode, 16));
				case 9:
					return new BobColor((int)Long.parseLong(hexcode, 16));
				default:
					throw new NumberFormatException("Can't parse '" + value + "' as hex color");
			}
		}
		return BobColor.getColorByName(value);
	}

	/**
	 * Converts this color into it's hex string.
	 *
	 * If alpha is 255 then a string in "#RRGGBB" format is created,
	 * otherwise the "#AARRGGBB" format is created
	 *
	 * @return hex representation of this color
	 */
// @Override
	public String toHexString() {
		if(a() != 1) {
			return String.format("#%08X", toARGB());
		} else {
			return String.format("#%06X", toARGB() & 0xFFFFFF);
		}
	}

//    @Override
//    public boolean equals(Object obj) {
//        if(!(obj instanceof BobColor)) {
//            return false;
//        }
//        final BobColor other = (BobColor)obj;
//        return this.toARGB() == other.toARGB();
//    }

	@Override
	public int hashCode() {
		return toARGB();
	}

//    public BobColor multiply(BobColor other) {
//        return new Color(
//                mul(r, other.r),
//                mul(g, other.g),
//                mul(b, other.b),
//                mul(a, other.a));
//    }
//
//    private byte mul(byte a, byte b) {
//        return (byte)(((a & 255) * (b & 255)) / 255);
//    }
//











}
