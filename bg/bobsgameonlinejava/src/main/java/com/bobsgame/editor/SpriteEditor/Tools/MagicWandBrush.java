package com.bobsgame.editor.SpriteEditor.Tools;

import java.awt.Graphics;
import java.util.LinkedList;
import java.util.Queue;
import java.awt.Point;

import com.bobsgame.editor.SpriteEditor.SECanvas;

public class MagicWandBrush implements Brush {

    @Override
    public String getName() {
        return "Magic Wand";
    }

    @Override
    public void onMousePress(SECanvas canvas, int x, int y, int color, int modifiers) {
        int w = canvas.getSprite().wP();
        int h = canvas.getSprite().hP();

        if (x < 0 || x >= w || y < 0 || y >= h) return;

        int targetColor = canvas.getPixel(x, y);
        boolean[][] visited = new boolean[w][h];
        boolean[][] maskFull = new boolean[w][h];

        Queue<Point> q = new LinkedList<>();
        q.add(new Point(x, y));
        visited[x][y] = true;
        maskFull[x][y] = true;

        int minX = x, maxX = x, minY = y, maxY = y;

        while (!q.isEmpty()) {
            Point p = q.poll();

            // Check neighbors (4-way)
            int[] dx = {0, 0, 1, -1};
            int[] dy = {1, -1, 0, 0};

            for (int i = 0; i < 4; i++) {
                int nx = p.x + dx[i];
                int ny = p.y + dy[i];

                if (nx >= 0 && nx < w && ny >= 0 && ny < h && !visited[nx][ny]) {
                    if (canvas.getPixel(nx, ny) == targetColor) {
                        visited[nx][ny] = true;
                        maskFull[nx][ny] = true;
                        q.add(new Point(nx, ny));

                        if (nx < minX) minX = nx;
                        if (nx > maxX) maxX = nx;
                        if (ny < minY) minY = ny;
                        if (ny > maxY) maxY = ny;
                    }
                }
            }
        }

        // Create cropped mask
        int width = maxX - minX + 1;
        int height = maxY - minY + 1;
        boolean[][] mask = new boolean[width][height];

        for (int ix = 0; ix < width; ix++) {
            for (int iy = 0; iy < height; iy++) {
                mask[ix][iy] = maskFull[minX + ix][minY + iy];
            }
        }

        canvas.getSelectionBox().setMask(mask);
        canvas.getSelectionBox().setLocation(minX, minY);
        canvas.getSelectionBox().setSize(width, height);
        canvas.getSelectionBox().isShowing = true;

        canvas.setText("Magic Wand Selected: " + width + "x" + height);
        canvas.repaint();
    }

    @Override
    public void onMouseDrag(SECanvas canvas, int x, int y, int color, int modifiers) {
        // Drag could potentially add to selection?
    }

    @Override
    public void onMouseRelease(SECanvas canvas, int x, int y, int color, int modifiers) {
    }

    @Override
    public void onPaint(Graphics g, SECanvas canvas) {
    }
}
