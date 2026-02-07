# TWL LWJGL3

This is an extension for the TWL library which adds LWJGL3 rendering and input support.

## Download

You can download the latest build here [TWL-LWJGL3.jar](build/TWL-LWJGL3.jar)

## Usage (must read)

LWJGL3 utillizes GLFW which has a few restrictions when it comes to listening to input. GLFW has functions that allow you to set a single callback for a specific event - overwriting the current listener. This extension takes into account the previously registered callbacks therefore it MUST be initialized (renderer & input) after you've made your GLFW set callback calls. Otherwise you will overwrite the listeners in this extension and mouse and keyboard input will fail to be sent.

## What is TWL?

TWL is a graphical user interface library for Java built on top of OpenGL. It provides a rich set of standard widgets including labels, edit fields, tables, popups, tooltips, frames and a lot more. Different layout container are available to create even the most advanced user interfaces.

With the TextArea class TWL also features a powerful HTML renderer which supports a subset of XHTML/CSS: floating elements, tables, images, unordered lists, text alignment, justified text and background images. See the TextArea Demo for details. It is perfectly suited to create NPC chat dialogs in games or integrated help systems.

As games have a high demand on visual identity, TWL provides a very flexible theme manager. The theme manager decouples the visual representation of widgets from the code. Themes are specified in XML and PNG files with full alpha blending for effects such as glow or shadows. These themed can be created using the TWL Theme Editor, which also includes a powerful tool to create bitmap fonts from TrueType fonts.
