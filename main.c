

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
//#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <sys/ioctl.h>
#include <inttypes.h>  // For PRIi64
#include <signal.h>
#include <sys/ioctl.h>
#include <fcntl.h>  // For open() and O_RDWR
#include <error.h>

#include </home/vamshi/Downloads/android-ndk-r27b-linux/android-ndk-r27b/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/include/android/log.h>
#include </home/vamshi/Downloads/android-ndk-r27b-linux/android-ndk-r27b/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/include/media/NdkMediaCodec.h>
#include </home/vamshi/Downloads/android-ndk-r27b-linux/android-ndk-r27b/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/include/media/NdkMediaExtractor.h>
#include </home/vamshi/Downloads/android-ndk-r27b-linux/android-ndk-r27b/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/include/media/NdkMediaFormat.h>
#include </home/vamshi/Downloads/android-ndk-r27b-linux/android-ndk-r27b/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/include/android/native_window.h>

#include </home/vamshi/Downloads/android-ndk-r27b-linux/android-ndk-r27b/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/include/aaudio/AAudio.h>

int device_handle = -1;  // File descriptor for the device (initially -1)

// Stress parameters
#define NUM_THREADS 10            // Number of threads to stress ARM cores
#define BUFFER_SIZE_GB 2       // Memory buffer size in MB
#define DURATION_SEC 10          // Stress test duration in seconds
#define SINE_SAMPLES 384000      // High-fidelity audio sample rate
#define MAX_CMD_SIZE 256
// Define buffer constants
#define BUFFER_SIZE (1024 * 1024 * 10) // 10 MB buffer
#define NUM_BUFFERS 5                 // Number of buffers to allocate
#define CHUNK_SIZE (1024 * 1024 * 10) // 10 MB
#define NUM_CHUNKS 100               // Number of chunks to allocate in each loop iteration
#define LOOPS 10                     // Number of allocation-deallocation cycles

pthread_mutex_t lock; 

// Define HiFi DSP cores and VPU interaction API here (hypothetical)
#define HIFI_CORE_COUNT 4
#define MAX_VIDEO_DECODERS 2

char command[MAX_CMD_SIZE];
char buff[1024];





#define LOG_TAG "HiFi_Video_Processing"

#define ALOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)


ANativeWindow* window;

// Hypothetical IOCTL command for starting audio processing (replace with the correct command)
#define AUDIO_IOCTL_START 0x12345678  // Replace with actual ioctl command



// Function to simulate CPU-intensive computation
void* cpu_stress(void* arg) {
    long id = (long)arg;
    char path[256];
    char max_freq[16];
    FILE *file;
    printf("Thread %ld: CPU stress started\n", id);

    double result = 0.0;
    // for(int cpu=0;cpu<=8;cpu++)
    // {
    //     snprintf(command, sizeof(command), "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_max_freq", cpu);
    //     FILE *fp = fopen(command, "r");
    //     if (fp) {
    //         char freq[32];
    //         if (fgets(freq, sizeof(freq), fp)) {
    //             printf("CPU%d scaling_max Frequency: %s", cpu, freq);
    //         }
    //         fclose(fp);
    //     } 
    //     else {
    //         printf("Failed to read scaling_max frequency for CPU%d.\n", cpu);
    //     }
    // }

    for (long i = 0; i < 1e8; i++) {
        result += sin(i) * cos(i); // Dummy computation
    }
    snprintf(command, sizeof(command), "dumpsys cpuinfo | grep 'CPU usage' ");
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("Failed to run command");
        //return;
    }

    // Read and print the output line by line
    printf("Output of dumpsys meminfo:\n");
    while (fgets(buff, sizeof(buff), fp) != NULL) {
        printf("%s", buff);
    }

    // Close the pipe
    pclose(fp);


    

    // for(int cpu=0;cpu<=8;cpu++)
    // {
    //     snprintf(command, sizeof(command), "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_cur_freq", cpu);
    //     FILE *fp = fopen(command, "r");
    //     if (fp) {
    //         char freq[32];
    //         if (fgets(freq, sizeof(freq), fp)) {
    //             printf("CPU%d scaling_current Frequency: %s", cpu, freq);
    //         }
    //         fclose(fp);
    //     } 
    //     else {
    //         printf("Failed to read scaling_current frequency for CPU%d.\n", cpu);
    //     }
    // }


    printf("Thread %ld: CPU stress completed\n", id);
    return NULL;
}

void activateHiFiCores()
{
    printf("activateHificores\n");
    // Hypothetical function to engage HiFi DSP cores
    // This would require device-specific APIs or system-level calls
    ALOGD("Activating all HiFi Cores for high-fidelity audio processing...");

    // Open the device file (replace with actual audio device path)
    device_handle = open("/dev/acd-audio_ap_offload_rx", O_RDWR);  // Example device path
    if (device_handle < 0) {
        ALOGD("Failed to open the audio device.");
        return;
    }

    // Perform device-specific configuration (replace with actual ioctl commands)
    // Example: ioctl(device_handle, AUDIO_IOCTL_START, some_params);
    int result = ioctl(device_handle, AUDIO_IOCTL_START, NULL);  // Replace with actual command
    if (result != 0) {
        ALOGD("Failed to configure the audio device.");
    } else {
        ALOGD("Audio device activated and configured.");
    }

    // Close the device handle
    close(device_handle);
    ALOGD("All HiFi Cores activated.");
    
}

void processVideo(const char *inputVideoFile) {
    ALOGD("Starting video processing...");

    
    AMediaCodec *codec = NULL;
    AMediaFormat *format = NULL;
    FILE *inputFile = fopen(inputVideoFile, "rb");

    if (inputFile == NULL) {
        ALOGE("Failed to open input video file.");
        return;
    }

    // Initialize extractor and codec
   AMediaExtractor *extractor = AMediaExtractor_new();
    if (!extractor) {
        LOGE("Failed to create AMediaExtractor");
        return;
    }

    if (AMediaExtractor_setDataSource(extractor, inputVideoFile) != AMEDIA_OK) {
        ALOGE("Failed to set data source for video file.");
        goto cleanup;
    }
    size_t trackCount = AMediaExtractor_getTrackCount(extractor);
    int videoTrackIndex = -1;

    for (size_t i = 0; i < trackCount; i++) {
        format = AMediaExtractor_getTrackFormat(extractor, i);
        const char *mime;
        if (AMediaFormat_getString(format, AMEDIAFORMAT_KEY_MIME, &mime) &&
            strncmp(mime, "video/", 6) == 0) {
            videoTrackIndex = i;
            ALOGD("Found video track: %s", mime);
            break;
        }
        AMediaFormat_delete(format);
    }

        if (videoTrackIndex == -1) {
        ALOGE("No video track found in file.");
        goto cleanup;
    }

    AMediaExtractor_selectTrack(extractor, videoTrackIndex);

    // Create and configure codec
    const char *mime;
    AMediaFormat_getString(format, AMEDIAFORMAT_KEY_MIME, &mime);
    codec = AMediaCodec_createDecoderByType(mime);
    if (!codec) {
        ALOGE("Failed to create codec for mime: %s", mime);
        goto cleanup;
    }

    if (AMediaCodec_configure(codec, format, NULL, NULL, 0) != AMEDIA_OK) {
        ALOGE("Failed to configure codec.");
        goto cleanup;
    }

    AMediaCodec_start(codec);

     // Process video frames
    while (1) {
        ssize_t inputBufferIndex = AMediaCodec_dequeueInputBuffer(codec, 1000);
        if (inputBufferIndex >= 0) {
            size_t inputBufferSize;
            uint8_t *inputBuffer = AMediaCodec_getInputBuffer(codec, inputBufferIndex, &inputBufferSize);

            ssize_t sampleSize = AMediaExtractor_readSampleData(extractor, inputBuffer, inputBufferSize);
            if (sampleSize < 0) {
                ALOGD("End of stream reached.");
                AMediaCodec_queueInputBuffer(codec, inputBufferIndex, 0, 0, 0, AMEDIACODEC_BUFFER_FLAG_END_OF_STREAM);
                break;
            }

            int64_t presentationTimeUs = AMediaExtractor_getSampleTime(extractor);
            AMediaCodec_queueInputBuffer(codec, inputBufferIndex, 0, sampleSize, presentationTimeUs, 0);
            AMediaExtractor_advance(extractor);
        }

        AMediaCodecBufferInfo bufferInfo;
        ssize_t outputBufferIndex = AMediaCodec_dequeueOutputBuffer(codec, &bufferInfo, 1000);
        if (outputBufferIndex >= 0) {
            ALOGD("Decoded frame: %" PRIi64 " ms", bufferInfo.presentationTimeUs / 1000);

            // Process decoded frame (if needed)
            AMediaCodec_releaseOutputBuffer(codec, outputBufferIndex, true);
        } else if (outputBufferIndex == AMEDIACODEC_INFO_OUTPUT_FORMAT_CHANGED) {
            ALOGD("Output format changed.");
        } else if (outputBufferIndex == AMEDIACODEC_INFO_TRY_AGAIN_LATER) {
            // No output available yet
        }
    }

    ALOGD("Video processing completed.");

    cleanup:
        if (codec) {
            AMediaCodec_stop(codec);
            AMediaCodec_delete(codec);
        }
        if (extractor) {
            AMediaExtractor_delete(extractor);
        }
        if (format) {
            AMediaFormat_delete(format);
        }

    ALOGD("Video processing completed.");
}

// Function to allocate and stress memory
void memory_stress() {

    printf("Allocating %d MB of memory...\n", BUFFER_SIZE_GB);
    size_t buffer_size = (size_t)BUFFER_SIZE_GB * 1024 * 1024 * 1024;
    char* buffer = (char*)malloc(buffer_size);
    if (!buffer) {
        perror("Memory allocation failed");
        return;
    }

    memset(buffer, 0xFF, buffer_size); // Fill memory with data
    //snprintf(command, sizeof(command), "dumpsys meminfo");
    snprintf(command, sizeof(command), "dumpsys meminfo | grep -E 'Free RAM:' ");
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("Failed to run command");
        return;
    }

    // Read and print the output line by line
    printf("Output of dumpsys meminfo:\n");
    while (fgets(buff, sizeof(buff), fp) != NULL) {
        printf("%s", buff);
    }

    // Close the pipe
    pclose(fp);

    //sleep(10);
    printf("Memory stress test completed\n");
    free(buffer);
}


// Shader sources
const char* vertexShaderSource =
"#version 300 es\n"
"layout(location = 0) in vec4 position;\n"
"void main() {\n"
"    gl_Position = position;\n"
"}\n";
 
const char* fragmentShaderSource =
"#version 300 es\n"
"precision mediump float;\n"
"out vec4 color;\n"
"const int MATRIX_SIZE = 16;\n"
"uniform mat4 matrixA[MATRIX_SIZE];\n"
"uniform mat4 matrixB[MATRIX_SIZE];\n"
"void main() {\n"
"    mat4 result = mat4(1.0);\n"
"    for (int i = 0; i < MATRIX_SIZE; i++) {\n"
"        result *= matrixA[i] * matrixB[i];\n"
"    }\n"
"    float intensity = result[0][0];\n"
"    color = vec4(intensity, 0.0, 0.0, 1.0);\n"
"}\n";



// Function to simulate GPU stress using dummy operations
void gpu_stress() {
    printf("GPU stress simulation started\n");
    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(display, NULL, NULL);

    EGLConfig config;
    EGLint numConfigs;
    EGLint attribs[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
        EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
        EGL_NONE
    };
    eglChooseConfig(display, attribs, &config, 1, &numConfigs);

    EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
    EGLContext context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);

    EGLSurface surface = eglCreatePbufferSurface(display, config, NULL);
    eglMakeCurrent(display, surface, surface, context);

    // Compile Vertex Shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Compile Fragment Shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Create Shader Program
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glUseProgram(program);

    // Vertex Data
    const GLfloat triangleVertices[] = {
        0.0f,  0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
    };
    GLint positionAttrib = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(positionAttrib);
    glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, 0, triangleVertices);

    // Rendering Loop
    for (int frame = 0; frame < 10000; frame++) {
        glClear(GL_COLOR_BUFFER_BIT);
        for (int i = 0; i < 10000; i++) {
            glDrawArrays(GL_TRIANGLES, 0, 3); // Draw Triangle
        }
        eglSwapBuffers(display, surface); // Swap Framebuffers
        usleep(16000); // ~60 FPS
    }

    // Cleanup
    eglDestroySurface(display, surface);
    eglDestroyContext(display, context);
    eglTerminate(display);
    printf("GPU stress simulation completed\n");
}


// Function to check shader compilation
void checkShaderCompilation(GLuint shader) {
    GLint success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("Shader Compilation Error: %s\n", infoLog);
    }
}
 
// Function to check program linking
void checkProgramLinking(GLuint program) {
    GLint success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        printf("Program Linking Error: %s\n", infoLog);
    }
}
 
// Tensor Core Stress Test Function
void* tensorCoreStressTest() {
 printf("Starting Tensor Core Stress Test...\n");

    pthread_mutex_lock(&lock);
    // Step 1: Initialize EGL
    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (display == EGL_NO_DISPLAY) {
        printf("Failed to get EGL display.\n");
        pthread_mutex_unlock(&lock);
        return NULL;
    }
    printf("EGL display initialized.\n");
 
    // Step 2: Initialize EGL
    if (!eglInitialize(display, NULL, NULL)) {
        printf("EGL initialization failed.\n");
        pthread_mutex_unlock(&lock);
        return NULL;
    }
    printf("EGL initialized successfully.\n");
 
    // Step 3: Choose EGL configuration
    EGLConfig config;
    EGLint numConfigs;
    EGLint attribs[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
        EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
        EGL_NONE
    };
    if (!eglChooseConfig(display, attribs, &config, 1, &numConfigs) || numConfigs == 0) {
        printf("Failed to choose EGL config.\n");
        eglTerminate(display);
        pthread_mutex_unlock(&lock);
        return NULL;
    }
    // if (numConfigs == 0) {
    //     printf("No valid EGL config found.\n");
    //     return NULL;
    // }
 
    // Step 4: Create EGL context with OpenGL ES 3.x
    EGLint contextAttribs[] = {
        EGL_CONTEXT_CLIENT_VERSION, 3,
        EGL_NONE
    };
    EGLContext context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);
    if (context == EGL_NO_CONTEXT) {
        printf("Failed to create EGL context. EGL Error: 0x%x\n", eglGetError());
        eglTerminate(display);
        pthread_mutex_unlock(&lock);
        return NULL;
    }
 
    // Step 5: Create an EGL surface
    EGLSurface surface = eglCreatePbufferSurface(display, config, NULL);
    if (surface == EGL_NO_SURFACE) {
        printf("Failed to create EGL surface. EGL Error: 0x%x\n", eglGetError());
        eglDestroyContext(display, context);
        eglTerminate(display);
        pthread_mutex_unlock(&lock);
        return NULL;
    }
 
    // Step 6: Make the EGL context current
    if (!eglMakeCurrent(display, surface, surface, context)) {
        printf("Failed to make EGL context current. EGL Error: 0x%x\n", eglGetError());
        eglDestroySurface(display, surface);
        eglDestroyContext(display, context);
        eglTerminate(display);
        pthread_mutex_unlock(&lock);
        return NULL;
    }
    printf("EGL context made current successfully.\n");
 
    // Step 7: Check OpenGL ES version
    const char* version = (const char*)glGetString(GL_VERSION);
    printf("OpenGL ES Version: %s\n", version);
    if (version == NULL || strstr(version, "OpenGL ES 3") == NULL) {
        printf("OpenGL ES 3.x not supported.\n");
        eglDestroySurface(display, surface);
        eglDestroyContext(display, context);
        eglTerminate(display);        
        pthread_mutex_unlock(&lock);
        return NULL;
    }
 
    // Step 8: Compile and link shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    checkShaderCompilation(vertexShader);
 
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    checkShaderCompilation(fragmentShader);
 
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkProgramLinking(shaderProgram);
 
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLenum glError = glGetError();
    if (glError != GL_NO_ERROR) {
        printf("OpenGL Error after shader setup: 0x%x\n", glError);
        pthread_mutex_unlock(&lock);
        return NULL;
    }
 
    // Step 9: Generate and fill matrices
    GLint matrixLocA = glGetUniformLocation(shaderProgram, "matrixA");
    GLint matrixLocB = glGetUniformLocation(shaderProgram, "matrixB");
    if (matrixLocA == -1 || matrixLocB == -1) {
        printf("Failed to get uniform locations for matrices.\n");
        return NULL;
    }
 
    float matrixA[16][4][4];
    float matrixB[16][4][4];
    
    for (int i = 0; i < 16; i++) {
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                matrixA[i][row][col] = (float)rand() / (float)(RAND_MAX + 1);
                matrixB[i][row][col] = (float)rand() / (float)(RAND_MAX + 1);
            }
        }
    }
 
    // Step 10: Upload matrices to GPU
    glUseProgram(shaderProgram);
    glUniformMatrix4fv(matrixLocA, 16, GL_FALSE, &matrixA[0][0][0]);
    glUniformMatrix4fv(matrixLocB, 16, GL_FALSE, &matrixB[0][0][0]);

    if (matrixLocA == -1 || matrixLocB == -1) {
    printf("Error: Invalid uniform locations for matrices.\n");
    pthread_mutex_unlock(&lock);
    return NULL;
}
 
    // Step 11: Render loop to sustain workload
    for (int frame = 0; frame < 20000; frame++) {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        eglSwapBuffers(display, surface); // Ensure to swap buffers for rendering.
    }
    for(int cpu=0;cpu<=8;cpu++)
    {
        snprintf(command, sizeof(command), "/sys/class/thermal/thermal_zone%d/temp", cpu);
        FILE *fp = fopen(command, "r");
        if (fp) {
            char freq[32];
            if (fgets(freq, sizeof(freq), fp)) {
                printf("CPU%d thermal temperature: %s", cpu, freq);
            }
            fclose(fp);
        } 
        else {
            printf("Failed to read thermal temperature for CPU%d.\n", cpu);
        }
    }

 
    printf("Tensor Core Stress Test Completed.\n");
 
    // Step 12: Cleanup
    glDeleteProgram(shaderProgram);
    eglDestroySurface(display, surface);
    eglDestroyContext(display, context);
    eglTerminate(display);
    pthread_mutex_unlock(&lock);
 
    return NULL;
}


// Function to generate high-fidelity audio for stress
void hifi_stress() {
    printf("High-fidelity audio processing simulation started\n");

    for (long i = 0; i < SINE_SAMPLES; i++) {
        double t = (double)i / SINE_SAMPLES;
        double sample = sin(2 * M_PI * 20000 * t); // 20 kHz sine wave
        (void)sample; // Suppress unused variable warning
    }

    printf("High-fidelity audio processing simulation completed\n");
}


/**
 * Simulates video decoding and rendering with potential errors for testing.
 * 
 * @param videoFilePath - The path of the video file to process.
 * @param window - A valid ANativeWindow pointer.
 * @return int - 0 on success, -1 on failure.
 */
int process_video(const char* inputVideoFile, ANativeWindow* window) {
    LOGI("Starting video processing for: %s", inputVideoFile);

    // Simulate loading the video file
    if (strstr(inputVideoFile, "error")) { // Simulate an error condition
        LOGE("Error: Failed to load video file: %s", inputVideoFile);
        return -1;
    }

    // Simulate decoding process
    LOGI("Simulating video decoding...");
    for (int i = 0; i < 10; i++) {
        if (i == 5) { // Simulate a decoding error at frame 5
            LOGE("Error: Decoding failed at frame %d", i);
            return -1;
        }
        LOGI("Decoded frame %d successfully", i);
    }

    // Simulate rendering process
    LOGI("Simulating video rendering...");
    if (window == NULL) {
        LOGE("Error: Invalid ANativeWindow provided for rendering");
        return -1;
    }

    for (int i = 0; i < 10; i++) {
        if (i == 8) { // Simulate a rendering error at frame 8
            LOGE("Error: Rendering failed at frame %d", i);
            return -1;
        }
        LOGI("Rendered frame %d successfully", i);
    }

    LOGI("Video processing completed successfully.");
    return 0;
}


/**
 * Creates a dummy ANativeWindow using EGL for testing purposes.
 * 
 * @return ANativeWindow* - A valid ANativeWindow pointer or NULL if creation fails.
 */
ANativeWindow* create_dummy_window() {
    // Get default display
    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (display == EGL_NO_DISPLAY) {
        LOGE("Failed to get EGL display");
        return NULL;
    }

    // Initialize EGL
    if (!eglInitialize(display, NULL, NULL)) {
        LOGE("Failed to initialize EGL");
        return NULL;
    }

    // Configure EGL
    EGLConfig config;
    EGLint numConfigs;
    EGLint configAttrs[] = {
        EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
        EGL_BLUE_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_RED_SIZE, 8,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_NONE
    };

    if (!eglChooseConfig(display, configAttrs, &config, 1, &numConfigs) || numConfigs == 0) {
        LOGE("Failed to choose EGL config");
        eglTerminate(display);
        return NULL;
    }

    // Create an offscreen surface
    EGLint pbufferAttrs[] = {
        EGL_WIDTH, 1,
        EGL_HEIGHT, 1,
        EGL_NONE
    };
    EGLSurface surface = eglCreatePbufferSurface(display, config, pbufferAttrs);
    if (surface == EGL_NO_SURFACE) {
        LOGE("Failed to create EGL Pbuffer surface");
        eglTerminate(display);
        return NULL;
    }

    // Make the surface current
    if (!eglMakeCurrent(display, surface, surface, EGL_NO_CONTEXT)) {
        LOGE("Failed to make EGL surface current");
        eglDestroySurface(display, surface);
        eglTerminate(display);
        return NULL;
    }

    // Create a dummy ANativeWindow
    window = eglGetCurrentSurface(EGL_DRAW);
    if (!window) {
        LOGE("Failed to get ANativeWindow from EGL surface");
        eglDestroySurface(display, surface);
        eglTerminate(display);
        return NULL;
    }

    return window;
}
void segfault_handler(int sig) {
    LOGE("Segmentation fault (signal %d) encountered!", sig);
    exit(1);
}

void init(const char *inputVideoFile)
{
    pthread_t threads[NUM_THREADS];
    pthread_t TensorThread;
    for(int cpu=0;cpu<=8;cpu++)
    {
        snprintf(command, sizeof(command), "/sys/devices/system/cpu/cpu%d/cpufreq/cpuinfo_max_freq", cpu);
        FILE *fp = fopen(command, "r");
        if (fp) {
            char freq[32];
            if (fgets(freq, sizeof(freq), fp)) {
                printf("CPU%d Maximum Frequency on a device: %s", cpu, freq);
            }
            fclose(fp);
        } 
        else {
            printf("Failed to read Maximum frequency on a device for CPU%d.\n", cpu);
        }
    }
    memory_stress();
    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, cpu_stress, (void*)i);
    }
    gpu_stress();
    // for (long i = 0; i < NUM_THREADS; i++) {
    //     pthread_create(&threads[i], NULL, tensorCoreStressTest, (void*)i);
    //     //sleep(5);
    // }
    tensorCoreStressTest();
    ALOGD("Input video file: %s", inputVideoFile);
    activateHiFiCores();
    printf("after active\n");
    processVideo(inputVideoFile);
    //sleep(25);

    LOGE("Video file path: %s", inputVideoFile);

    // // Create a dummy ANativeWindow
    window = create_dummy_window();
    if (!window) {
        LOGE("Failed to create dummy ANativeWindow");
        //return -1;
    }

    // // Simulate video decoding/rendering with the provided file path
    LOGE("Successfully initialized video decoding for: %s", inputVideoFile);
    
    // Process the video file
    if (process_video(inputVideoFile, window) != 0) {
        LOGE("Video processing encountered errors.");
        ANativeWindow_release(window);
        //return -1;
    }

    // // Release resources
     ANativeWindow_release(window);

    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
}




// Main function
int main(int argc, char **argv) {
      if (argc != 2) {
        fprintf(stderr,"Usage: %s <input_video_file>\n", argv[0]);
        return -1;
    }
    signal(SIGSEGV, segfault_handler); // Handle segmentation faults

    printf("Starting Pixel phone stress test...\n");

    const char *inputVideoFile = argv[1];

    init(inputVideoFile);
    

    printf("Stress test completed.\n");
    return EXIT_SUCCESS;
}

