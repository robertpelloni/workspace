package com.bobsgame.editor.Project.Sprite;

import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import com.bobsgame.editor.Project.Sprite.Sprite.Layer;
import com.bobsgame.shared.SpriteData;
import com.bobsgame.shared.Utils;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

public class SpriteProject {

    public SpriteData spriteData;
    public List<LayerState> layers = new ArrayList<>();

    public static class LayerState {
        public String name;
        public boolean visible;
        public float opacity;
        public String encodedPixels; // GZIP + Base64

        public LayerState() {}

        public LayerState(Layer layer, int frames, int width, int height) {
            this.name = layer.name;
            this.visible = layer.visible;
            this.opacity = layer.opacity;
            this.encodedPixels = encodePixels(layer.pixels, frames, width, height);
        }

        private String encodePixels(int[][][] pixels, int frames, int width, int height) {
            // Flatten 3D array to 1D int array
            int[] flat = new int[frames * width * height];
            int idx = 0;
            for(int f=0; f<frames; f++) {
                for(int y=0; y<height; y++) {
                    for(int x=0; x<width; x++) {
                        flat[idx++] = pixels[f][x][y];
                    }
                }
            }
            return Utils.encodeStringToBase64(Utils.zipByteArrayToString(Utils.getByteArrayFromIntArray(flat)));
        }

        public int[][][] decodePixels(int frames, int width, int height) {
            int[][][] pixels = new int[frames][width][height];

            byte[] bytes = Utils.unzipStringToByteArray(Utils.decodeBase64String(encodedPixels));
            int[] flat = Utils.getIntArrayFromByteArray(bytes);

            int idx = 0;
            for(int f=0; f<frames; f++) {
                for(int y=0; y<height; y++) {
                    for(int x=0; x<width; x++) {
                        if (idx < flat.length) {
                            pixels[f][x][y] = flat[idx++];
                        }
                    }
                }
            }
            return pixels;
        }
    }

    public SpriteProject() {}

    public static void save(Sprite sprite, File file) throws IOException {
        SpriteProject project = new SpriteProject();
        project.spriteData = sprite.getData();

        for (Layer layer : sprite.getLayers()) {
            project.layers.add(new LayerState(layer, sprite.frames(), sprite.wP(), sprite.hP()));
        }

        Gson gson = new GsonBuilder().setPrettyPrinting().create();
        try (FileWriter writer = new FileWriter(file)) {
            gson.toJson(project, writer);
        }
    }

    public static Sprite load(File file) throws IOException {
        Gson gson = new Gson();
        SpriteProject project;
        try (FileReader reader = new FileReader(file)) {
            project = gson.fromJson(reader, SpriteProject.class);
        }

        // Reconstruct Sprite
        // We use the constructor that takes SpriteData
        Sprite sprite = new Sprite(project.spriteData);

        // Clear default layer created by constructor
        sprite.getLayers().clear();

        for (LayerState ls : project.layers) {
            // Create layer
            // Accessing inner class constructor requires instance of outer class?
            // Or if Layer is static? Layer is not static in Sprite.java.
            // "public class Layer implements Serializable" -> It is non-static inner class.
            // So we need sprite.new Layer(...)

            Layer layer = sprite.new Layer(ls.name, sprite.frames(), sprite.wP(), sprite.hP());
            layer.visible = ls.visible;
            layer.opacity = ls.opacity;
            layer.pixels = ls.decodePixels(sprite.frames(), sprite.wP(), sprite.hP());

            sprite.getLayers().add(layer);
        }

        // If no layers loaded (shouldn't happen for valid file), add default
        if (sprite.getLayers().isEmpty()) {
            sprite.addLayer();
        }

        sprite.activeLayerIndex = sprite.getLayers().size() - 1;

        return sprite;
    }
}
