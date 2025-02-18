import android.media.MediaCodec;
import android.media.MediaCodecInfo;
import android.media.MediaFormat;
import android.media.MediaMuxer;
import android.media.MediaCodec.BufferInfo;
import java.io.FileInputStream;
import java.nio.ByteBuffer;

public class MediaEncoder {

    private static final String MIME_TYPE = "audio/mp4a-latm";
    private static final int SAMPLE_RATE = 44100;
    private static final int BIT_RATE = 128000;
    private static final int CHANNEL_COUNT = 2;
    private static final int BUFFER_SIZE = 2048;

    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java MediaEncoder <input.pcm> <output.mp4>");
            return;
        }

        try {
            encodePcmToAac(args[0], args[1]);
            System.out.println("Encoding complete. Output file: " + args[1]);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void encodePcmToAac(String inputPath, String outputPath) throws Exception {
        MediaCodec codec = MediaCodec.createEncoderByType(MIME_TYPE);
        MediaFormat format = MediaFormat.createAudioFormat(MIME_TYPE, SAMPLE_RATE, CHANNEL_COUNT);
        format.setInteger(MediaFormat.KEY_BIT_RATE, BIT_RATE);
        format.setInteger(MediaFormat.KEY_AAC_PROFILE, MediaCodecInfo.CodecProfileLevel.AACObjectLC);
        format.setInteger(MediaFormat.KEY_MAX_INPUT_SIZE, BUFFER_SIZE);

        codec.configure(format, null, null, MediaCodec.CONFIGURE_FLAG_ENCODE);
        codec.start();

        FileInputStream inputStream = new FileInputStream(inputPath);
        MediaMuxer muxer = new MediaMuxer(outputPath, MediaMuxer.OutputFormat.MUXER_OUTPUT_MPEG_4);

        boolean endOfStream = false;
        byte[] buffer = new byte[BUFFER_SIZE];
        BufferInfo bufferInfo = new BufferInfo();
        int audioTrackIndex = -1;
        boolean muxerStarted = false;

        while (!endOfStream) {
            int inputBufferIndex = codec.dequeueInputBuffer(10000);
            if (inputBufferIndex >= 0) {
                ByteBuffer inputBuffer = codec.getInputBuffer(inputBufferIndex);
                if (inputBuffer != null) {
                    inputBuffer.clear();
                    int bytesRead = inputStream.read(buffer);
                    if (bytesRead == -1) {
                        codec.queueInputBuffer(inputBufferIndex, 0, 0, 0, MediaCodec.BUFFER_FLAG_END_OF_STREAM);
                        endOfStream = true;
                    } else {
                        inputBuffer.put(buffer, 0, bytesRead);
                        codec.queueInputBuffer(inputBufferIndex, 0, bytesRead, 0, 0);
                    }
                }
            }

            int outputBufferIndex = codec.dequeueOutputBuffer(bufferInfo, 10000);
            while (outputBufferIndex >= 0) {
                ByteBuffer outputBuffer = codec.getOutputBuffer(outputBufferIndex);

                if (outputBuffer != null && bufferInfo.size > 0) {
                    if (!muxerStarted) {
                        audioTrackIndex = muxer.addTrack(codec.getOutputFormat());
                        muxer.start();
                        muxerStarted = true;
                    }

                    outputBuffer.position(bufferInfo.offset);
                    outputBuffer.limit(bufferInfo.offset + bufferInfo.size);

                    if ((bufferInfo.flags & MediaCodec.BUFFER_FLAG_CODEC_CONFIG) != 0) {
                        System.out.println("Writing CSD...");
                    } else {
                        muxer.writeSampleData(audioTrackIndex, outputBuffer, bufferInfo);
                    }
                }

                codec.releaseOutputBuffer(outputBufferIndex, false);
                outputBufferIndex = codec.dequeueOutputBuffer(bufferInfo, 10000);
            }
        }

        inputStream.close();
        codec.stop();
        codec.release();

        if (muxerStarted) {
            muxer.stop();
            muxer.release();
        }

        System.out.println("Encoding complete.");
    }
}

