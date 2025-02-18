BUILD_DIR=build
ANDROID_HOME=/home/vamshi/Android/Sdk
ANDROID_NDK_STANDALONE=/home/vamshi/Android/Sdk/ndk/28.0.12916984/toolchains/llvm/prebuilt/linux-x86_64
#JAVAC_OPTS=-source 1.8 -target 1.8 -cp .:$(ANDROID_HOME)/platforms/android-35/android.jar
JAVAC_OPTS=-Xlint:deprecation -cp .:$(ANDROID_HOME)/platforms/android-35/android.jar

APP_PROCESS=app_process
JARFILE=mediaEncoder.jar
ifeq ($(ARCH),arm)
TARGET=--target=armv7-none-linux-androideabi19 -march=armv7-a -mfpu=vfpv3-d16
APP_PROCESS=app_process32
else
TARGET=--target=aarch64-none-linux-android21
endif
CLASSES_DIR := $(BUILD_DIR)/classes
CLASSES := $(wildcard $(CLASSES_DIR)/*/*.class)
#print_classes:
#	@echo "Classes to include in DEX:"
#	@echo $(CLASSES_DIR)
#	@echo $(CLASSES)


$(BUILD_DIR)/$(JARFILE) : MediaEncoder.java
	test -d $(BUILD_DIR) || mkdir $(BUILD_DIR)	
	$(JAVA_HOME)/bin/javac $(JAVAC_OPTS) -d $(BUILD_DIR)/classes MediaEncoder.java
	$(ANDROID_HOME)/build-tools/35.0.1/d8 --output $(BUILD_DIR)/$(JARFILE)  $(BUILD_DIR)/classes/*.class

$(BUILD_DIR)/libhello.so : hello-jni.c
	test -d $(BUILD_DIR) || mkdir $(BUILD_DIR)
	$(ANDROID_NDK_STANDALONE)/bin/clang \
		$(TARGET) --gcc-toolchain=$(ANDROID_NDK_STANDALONE) \
		--sysroot $(ANDROID_NDK_STANDALONE)/sysroot \
		-L$(ANDROID_NDK_STANDALONE)/sysroot/usr/lib \
		-shared -g -DANDROID -fdata-sections -ffunction-sections -funwind-tables \
		-fstack-protector-strong -no-canonical-prefixes -fno-addrsig -fPIC \
		$(CFLAGS) -Wl,--exclude-libs,libgcc.a -Wl,--exclude-libs,libatomic.a \
		-Wl,--build-id -Wl,--warn-shared-textrel \
		-Wl,--no-undefined -Wl,--as-needed \
		$(LINKFLAGS) -Wl,-llog \
		-Wl,-soname,libhello.so \
		-o $(BUILD_DIR)/libhello.so hello-jni.c 
$(BUILD_DIR)/mediaEncoder : run.sh.m4
	m4 -D JARFILE=$(JARFILE) -D APP_PROCESS=$(APP_PROCESS) -D MAIN_CLASS=MediaEncoder run.sh.m4 > $(BUILD_DIR)/mediaEncoder
all: $(BUILD_DIR)/$(JARFILE) $(BUILD_DIR)/libhello.so $(BUILD_DIR)/mediaEncoder
.PHONY : clean deploy
deploy : all
	adb shell mkdir /data/local/tmp/mediaEncoder
	adb push --sync $(BUILD_DIR)/$(JARFILE)  $(BUILD_DIR)/libhello.so  $(BUILD_DIR)/mediaEncoder /data/local/tmp/mediaEncoder/
	adb shell chmod a+x /data/local/tmp/mediaEncoder/mediaEncoder
	$(info 	adb shell /data/local/tmp/mediaEncoder/mediaEncoder) 
clean :
	test -d $(BUILD_DIR) && rm -rf $(BUILD_DIR) || true
	adb shell -n "test -d /data/local/tmp/mediaEncoder && rm -rf /data/local/tmp/mediaEncoder || true"
