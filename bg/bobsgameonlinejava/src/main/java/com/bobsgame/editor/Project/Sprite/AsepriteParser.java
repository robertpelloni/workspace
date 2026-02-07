package com.bobsgame.editor.Project.Sprite;

import java.io.UnsupportedEncodingException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.ArrayList;
import java.util.List;

public final class AsepriteParser {

    private static final int FIRST_FRAME_OFFSET = 128;
    private final ByteBuffer buffer;

    public AsepriteParser(byte[] bytes) {
        this.buffer = ByteBuffer.wrap(bytes).order(ByteOrder.LITTLE_ENDIAN);
    }

    public Header header() {
        return new Header();
    }

    public Frame frame(int number) {
        int offset = FIRST_FRAME_OFFSET;
        for (int i = 0; i < number; i++) { // 0-based index? ASE.java was 1-based logic? "i < number" loop starts at 1?
            // ASE.java: for (int i = 1; i < number; i++)
            // If number is 0 (first frame), loop doesn't run. Frame(FIRST_FRAME_OFFSET).
            // If number is 1 (second frame), loop runs once.
            // My API will be 0-indexed.

            // To find frame 'number', we skip 'number' frames.
            int frameBytes = (int) new Frame(offset).bytes();
            offset += frameBytes;
        }
        return new Frame(offset);
    }

    public List<Frame> parseFrames() {
        List<Frame> frames = new ArrayList<>();
        int count = header().frames();
        int offset = FIRST_FRAME_OFFSET;
        for(int i=0; i<count; i++) {
            Frame f = new Frame(offset);
            frames.add(f);
            offset += f.bytes();
        }
        return frames;
    }

    /**
     * DWORD: A 32-bit unsigned integer value
     */
    private long dword(int index) {
        return Integer.toUnsignedLong(buffer.getInt(index));
    }

    /**
     * WORD: A 16-bit unsigned integer value
     */
    private int word(int index) {
        return Short.toUnsignedInt(buffer.getShort(index));
    }

    private int short_(int index) {
        return buffer.getShort(index);
    }

    /**
     * STRING:
     * WORD: string length (number of bytes)
     * BYTE[length]: characters (in UTF-8) The '\0' character is not included.
     */
    private String string(int index) {
        int length = stringLength(index);
        byte[] dst = new byte[length];
        buffer.position(index + 2); // ???
        buffer.get(dst, 0, length);
        try {
            return new String(dst, "UTF-8");
        } catch (UnsupportedEncodingException e) {
            throw new RuntimeException("Problem decoding string in ASE file", e);
        }
    }

    private int stringLength(int index) {
        return word(index);
    }

    /**
     * BYTE: An 8-bit unsigned integer value
     */
    private int byte_(int index) {
        return Byte.toUnsignedInt(buffer.get(index));
    }

    public class Header {

        public long fileSize() {
            return dword(0);
        }

        public int frames() {
            return word(6);
        }

        public int width() {
            return word(8);
        }

        public int height() {
            return word(10);
        }

        public int colorDepth() {
            return word(12);
        }

        public long flags() {
            return dword(14);
        }

        public int speed() {
            return word(18);
        }

        public int transparentColorPaletteEntryIndex() {
            return byte_(28);
        }

        public int numberOfColors() {
            return word(32);
        }

        public int pixelWidth() {
            return byte_(34);
        }

        public int pixelHeight() {
            return byte_(35);
        }

    }

    public class Frame {

        private final int offset;

        Frame(int offset) {
            this.offset = offset;
        }

        public long bytes() {
            return dword(offset);
        }

        public int numberOfChunks() {
            return word(offset + 6);
        }

        public int duration() {
            return word(offset + 8);
        }

        public List<Chunk> chunks() {
            List<Chunk> chunks = new ArrayList<>(numberOfChunks());
            int currentOffset = this.offset + 16;
            for (int i = 0; i < numberOfChunks(); i++) {
                Chunk chunk = new Chunk(currentOffset);
                chunks.add(chunk);
                currentOffset += chunk.size();
            }
            return chunks;
        }

        public class Chunk {

            private final int offset;

            Chunk(int offset) {
                this.offset = offset;
            }

            public long size() {
                return dword(offset);
            }

            public int type() {
                return word(offset + 4);
            }

            public boolean isLayer() {
                return type() == 0x2004;
            }

            public boolean isCel() {
                return type() == 0x2005;
            }

            public boolean isPalette() {
                return type() == 0x2019;
            }

            public PaletteChunk palette() {
                return new PaletteChunk(offset + 6);
            }

            public LayerChunk layer() {
                return new LayerChunk(offset + 6);
            }

            public CelChunk cel() {
                // Chunk Header is 6 bytes.
                return new CelChunk(offset + 6, size() - 6);
            }

            public class PaletteChunk {

                private final int offset;

                PaletteChunk(int offset) {
                    this.offset = offset;
                }

                public long totalNumberOfEntries() {
                    return dword(offset);
                }

                public long firstColorIndexToChange() {
                    return dword(offset + 4);
                }

                public long lastColorIndexToChange() {
                    return dword(offset + 8);
                }

                public List<PaletteEntry> entries() {
                    List<PaletteEntry> entries = new ArrayList<>();
                    int currentOffset = offset + 20;
                    for (int i = 0; i < totalNumberOfEntries(); i++) {
                        PaletteEntry entry = new PaletteEntry(currentOffset);
                        entries.add(entry);
                        currentOffset += entry.size();
                    }
                    return entries;
                }

                public class PaletteEntry {

                    private final int offset;

                    PaletteEntry(int offset) {
                        this.offset = offset;
                    }

                    public int flags() {
                        return word(offset);
                    }

                    public boolean hasName() {
                        return (flags() & 1) == 1;
                    }

                    public int red() {
                        return byte_(offset + 2);
                    }

                    public int green() {
                        return byte_(offset + 3);
                    }

                    public int blue() {
                        return byte_(offset + 4);
                    }

                    public int alpha() {
                        return byte_(offset + 5);
                    }

                    public String name() {
                        return string(offset + 6);
                    }

                    public int size() {
                        int size = 6;
                        if (hasName()) {
                            return size + 2 + stringLength(offset + 6);
                        } else {
                            return size;
                        }
                    }

                }

            }

            public class LayerChunk {
                private final int offset;

                LayerChunk(int offset) {
                    this.offset = offset;
                }

                public int flags() {
                    return word(offset);
                }

                public boolean visible() {
                    return (flags() & 1) == 1;
                }

                public boolean editable() {
                    return (flags() & 2) == 2;
                }

                public int type() {
                    return word(offset + 2);
                }

                public boolean imageLayer() {
                    return type() == 0;
                }

                public boolean groupLayer() {
                    return type() == 1;
                }

                public int childLevel() {
                    return word(offset + 4);
                }

                public int blendMode() {
                    return word(offset + 10);
                }

                public int opacity() {
                    return byte_(offset + 12); // Corrected to byte, docs say BYTE
                }

                public String name() {
                    return string(offset + 16);
                }
            }

            public class CelChunk {
                private final int offset;
                private final long chunkSize; // Data size

                CelChunk(int offset, long chunkSize) {
                    this.offset = offset;
                    this.chunkSize = chunkSize;
                }

                public int layerIndex() { return word(offset); }
                public int x() { return short_(offset + 2); }
                public int y() { return short_(offset + 4); }
                public int opacity() { return byte_(offset + 6); }
                public int celType() { return word(offset + 7); }

                // 7 reserved bytes

                public int width() {
                    if (celType() == 1) return 0; // Linked
                    return word(offset + 16);
                }

                public int height() {
                    if (celType() == 1) return 0;
                    return word(offset + 18);
                }

                public byte[] getData() {
                    if (celType() == 1) return null; // Linked

                    // Data starts at offset + 20
                    // Length = chunkSize - 20 (Header 16 + 4 WH) ?
                    // Header (offset 0 to 15) is 16 bytes.
                    // W (16-17), H (18-19).
                    // Data at 20.
                    // Total Cel Header size is 20 bytes?
                    // Check docs:
                    // WORD Layer Index (2)
                    // SHORT X (2)
                    // SHORT Y (2)
                    // BYTE Opacity (1)
                    // WORD Type (2)
                    // BYTE[7] Reserved (7)
                    // Total = 16 bytes.

                    // If type 0 or 2:
                    // WORD Width (2)
                    // WORD Height (2)
                    // PIXELS...
                    // Total Header = 20 bytes.

                    int dataOffset = offset + 20;
                    int dataLen = (int)(chunkSize - 20);

                    byte[] data = new byte[dataLen];
                    buffer.position(dataOffset);
                    buffer.get(data, 0, dataLen);
                    return data;
                }

                public int linkedFrame() {
                    // Type 1: Linked Cel
                    // Frame position to link with
                    return word(offset + 16); // ?? Docs say at offset 16?
                    // "WORD Frame position to link with"
                }
            }
        }
    }

}
