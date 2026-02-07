#include "stdafx.h"
#include "LibretroGame.h"
#include "src/Utility/ControlsManager.h"
#include "src/Utility/gl/GLUtils.h"
#include "src/Utility/audio/AudioManager.h"
#include <cstdarg>

LibretroGame* LibretroGame::instance = nullptr;

static void retroLogCallback(enum retro_log_level level, const char *fmt, ...)
{
    char buffer[4096];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    string msg(buffer);
    // Remove newline at end if present
    if (!msg.empty() && msg.back() == '\n') msg.pop_back();

    switch (level)
    {
        case RETRO_LOG_DEBUG: LibretroGame::log.debug(msg); break;
        case RETRO_LOG_INFO: LibretroGame::log.info(msg); break;
        case RETRO_LOG_WARN: LibretroGame::log.warn(msg); break;
        case RETRO_LOG_ERROR: LibretroGame::log.error(msg); break;
        default: LibretroGame::log.info(msg); break;
    }
}

LibretroGame::LibretroGame(ND* nD) : NDGameEngine(nD)
{
    instance = this;
}

LibretroGame::~LibretroGame()
{
    Mix_HookMusic(NULL, NULL);
    unloadGame();
    if (coreHandle)
    {
        if (retro_deinit) retro_deinit();
#ifdef __WINDOWS__
        FreeLibrary((HMODULE)coreHandle);
#else
        dlclose(coreHandle);
#endif
    }
    if(instance == this) instance = nullptr;
}

void LibretroGame::init()
{
    super::init();
    titleMenuShowing = true;
    currentPath = Main::getPath();
    
    BobFile(Main::getPath() + "data/libretro/system").createDirectories();
    BobFile(Main::getPath() + "data/libretro/saves").createDirectories();
}

void LibretroGame::titleMenuUpdate()
{
    if (titleMenu == nullptr)
    {
        titleMenu = make_shared<BobMenu>(this, "Emulator");
        titleMenu->add("Load Core...", "Load Core");
        titleMenu->add("Load Game...", "Load Game");
        titleMenu->add("Resume");
        titleMenu->add("Save State", "Save State");
        titleMenu->add("Load State", "Load State");
        titleMenu->add("Exit");
    }

    if (getControlsManager()->miniGame_UP_Pressed()) titleMenu->up();
    if (getControlsManager()->miniGame_DOWN_Pressed()) titleMenu->down();

    if (getControlsManager()->miniGame_CONFIRM_Pressed())
    {
        if (titleMenu->isSelectedID("Load Core"))
        {
            selectingCore = true;
            fileBrowserMenu = make_shared<BobMenu>(this, "Select Core");
            updateFileBrowser();
            titleMenuShowing = false;
        }
        else if (titleMenu->isSelectedID("Load Game"))
        {
            selectingCore = false;
            fileBrowserMenu = make_shared<BobMenu>(this, "Select Game");
            updateFileBrowser();
            titleMenuShowing = false;
        }
        else if (titleMenu->isSelectedID("Resume"))
        {
            if (retro_run) 
            {
                titleMenuShowing = false;
                lastFrameTime = 0;
                accumulatedTime = 0;
            }
        }
        else if (titleMenu->isSelectedID("Save State"))
        {
            saveState(0);
            titleMenuShowing = false;
        }
        else if (titleMenu->isSelectedID("Load State"))
        {
            loadState(0);
            titleMenuShowing = false;
        }
        else if (titleMenu->isSelectedID("Exit"))
        {
            unloadGame();
            nD->setGame(nullptr);
        }
    }
}

void LibretroGame::updateFileBrowser()
{
    if (fileBrowserMenu->menuItems->size() == 0)
    {
        fileBrowserMenu->add("..", "..");
        BobFile dir(currentPath);
        vector<string> files = dir.list();
        for (const string& f : files)
        {
            fileBrowserMenu->add(f, f);
        }
    }

    if (getControlsManager()->miniGame_UP_Pressed()) fileBrowserMenu->up();
    if (getControlsManager()->miniGame_DOWN_Pressed()) fileBrowserMenu->down();

    if (getControlsManager()->miniGame_CONFIRM_Pressed())
    {
        shared_ptr<BobMenu::MenuItem> item = fileBrowserMenu->getSelectedMenuItem();
        if (item)
        {
            string selected = item->id;
            if (selected == "..")
            {
                // Go up directory
                size_t pos = currentPath.find_last_of("/\\");
                if (pos != string::npos) currentPath = currentPath.substr(0, pos);
                fileBrowserMenu->clear();
            }
            else
            {
                string fullPath = currentPath + "/" + selected;
                BobFile f(fullPath);
                if (f.isDirectory())
                {
                    currentPath = fullPath;
                    fileBrowserMenu->clear();
                }
                else
                {
                    if (selectingCore)
                    {
                        if (loadCore(fullPath))
                        {
                            fileBrowserMenu = nullptr;
                            titleMenuShowing = true;
                        }
                    }
                    else
                    {
                        if (loadGame(fullPath))
                        {
                            fileBrowserMenu = nullptr;
                            titleMenuShowing = false; // Start game
                        }
                    }
                }
            }
        }
    }

    if (getControlsManager()->miniGame_CANCEL_Pressed())
    {
        fileBrowserMenu = nullptr;
        titleMenuShowing = true;
    }
}

bool LibretroGame::loadCore(const string& corePath)
{
    if (coreHandle)
    {
        if (retro_deinit) retro_deinit();
#ifdef __WINDOWS__
        FreeLibrary((HMODULE)coreHandle);
#else
        dlclose(coreHandle);
#endif
        coreHandle = nullptr;
    }

#ifdef __WINDOWS__
    coreHandle = LoadLibrary(corePath.c_str());
#else
    coreHandle = dlopen(corePath.c_str(), RTLD_LAZY);
#endif

    if (!coreHandle)
    {
        log.error("Failed to load core: " + corePath);
        return false;
    }

#ifdef __WINDOWS__
    #define LOAD_SYM(x) x = (decltype(x))GetProcAddress((HMODULE)coreHandle, #x)
#else
    #define LOAD_SYM(x) x = (decltype(x))dlsym(coreHandle, #x)
#endif

    LOAD_SYM(retro_init);
    LOAD_SYM(retro_deinit);
    LOAD_SYM(retro_api_version);
    LOAD_SYM(retro_get_system_info);
    LOAD_SYM(retro_get_system_av_info);
    LOAD_SYM(retro_set_environment);
    LOAD_SYM(retro_set_video_refresh);
    LOAD_SYM(retro_set_audio_sample);
    LOAD_SYM(retro_set_audio_sample_batch);
    LOAD_SYM(retro_set_input_poll);
    LOAD_SYM(retro_set_input_state);
    LOAD_SYM(retro_set_controller_port_device);
    LOAD_SYM(retro_reset);
    LOAD_SYM(retro_run);
    LOAD_SYM(retro_serialize_size);
    LOAD_SYM(retro_serialize);
    LOAD_SYM(retro_unserialize);
    LOAD_SYM(retro_cheat_reset);
    LOAD_SYM(retro_cheat_set);
    LOAD_SYM(retro_load_game);
    LOAD_SYM(retro_load_game_special);
    LOAD_SYM(retro_unload_game);
    LOAD_SYM(retro_get_region);
    LOAD_SYM(retro_get_memory_data);
    LOAD_SYM(retro_get_memory_size);

    if (!retro_init) 
    {
        log.error("Failed to load retro_init symbol");
        return false;
    }

    retro_set_environment(retroEnvironment);
    retro_set_video_refresh(retroVideoRefresh);
    retro_set_audio_sample(retroAudioSample);
    retro_set_audio_sample_batch(retroAudioSampleBatch);
    retro_set_input_poll(retroInputPoll);
    retro_set_input_state(retroInputState);

    retro_init();

    return true;
}

bool LibretroGame::loadGame(const string& gamePath)
{
    if (!retro_load_game) return false;

    struct retro_game_info info = {0};
    info.path = gamePath.c_str();
    
    shared_ptr<ByteArray> data = FileUtils::loadByteFileFromExePath(gamePath);
    if(data)
    {
        info.data = data->data();
        info.size = data->size();
    }

    if (!retro_load_game(&info))
    {
        log.error("Failed to load game: " + gamePath);
        return false;
    }

    struct retro_system_av_info av_info;
    retro_get_system_av_info(&av_info);

    fps = av_info.timing.fps;
    if (fps <= 0.0) fps = 60.0;

    // Initialize videoTexture with av_info geometry
    shared_ptr<ByteArray> emptyData = make_shared<ByteArray>(av_info.geometry.base_width * av_info.geometry.base_height * 4);
    videoTexture = GLUtils::getTextureFromData("Libretro", av_info.geometry.base_width, av_info.geometry.base_height, emptyData.get());

    if (retro_set_controller_port_device)
    {
        retro_set_controller_port_device(0, RETRO_DEVICE_JOYPAD);
    }

    currentGamePath = gamePath;
    loadSRAM();
    
    lastFrameTime = 0;
    accumulatedTime = 0;

    Mix_HookMusic(audioCallback, this);

    return true;
}

void LibretroGame::unloadGame()
{
    if (retro_unload_game)
    {
        saveSRAM();
        retro_unload_game();
    }
    currentGamePath = "";
}

void LibretroGame::loadSRAM()
{
    if (!retro_get_memory_data || !retro_get_memory_size) return;

    void* data = retro_get_memory_data(RETRO_MEMORY_SAVE_RAM);
    size_t size = retro_get_memory_size(RETRO_MEMORY_SAVE_RAM);

    if (data && size > 0)
    {
        string savePath = Main::getPath() + "data/libretro/saves/" + FileUtils::getFileNameWithoutExtension(currentGamePath) + ".srm";
        shared_ptr<ByteArray> fileData = FileUtils::loadByteFileFromExePath(savePath);
        if (fileData && fileData->size() == size)
        {
            memcpy(data, fileData->data(), size);
            log.info("Loaded SRAM from " + savePath);
        }
    }
}

void LibretroGame::saveSRAM()
{
    if (!retro_get_memory_data || !retro_get_memory_size) return;

    void* data = retro_get_memory_data(RETRO_MEMORY_SAVE_RAM);
    size_t size = retro_get_memory_size(RETRO_MEMORY_SAVE_RAM);

    if (data && size > 0)
    {
        string savePath = Main::getPath() + "data/libretro/saves/" + FileUtils::getFileNameWithoutExtension(currentGamePath) + ".srm";
        FileUtils::saveByteFile(savePath, (u8*)data, size);
        log.info("Saved SRAM to " + savePath);
    }
}

void LibretroGame::saveState(int slot)
{
    if (!retro_serialize_size || !retro_serialize) return;

    size_t size = retro_serialize_size();
    if (size == 0) return;

    shared_ptr<ByteArray> data = make_shared<ByteArray>(size);
    if (retro_serialize(data->data(), size))
    {
        string savePath = Main::getPath() + "data/libretro/saves/" + FileUtils::getFileNameWithoutExtension(currentGamePath) + ".state" + to_string(slot);
        FileUtils::saveByteFile(savePath, data);
        log.info("Saved state to " + savePath);
    }
}

void LibretroGame::loadState(int slot)
{
    if (!retro_unserialize) return;

    string savePath = Main::getPath() + "data/libretro/saves/" + FileUtils::getFileNameWithoutExtension(currentGamePath) + ".state" + to_string(slot);
    shared_ptr<ByteArray> data = FileUtils::loadByteFileFromExePath(savePath);
    
    if (data && data->size() > 0)
    {
        if (retro_unserialize(data->data(), data->size()))
        {
            log.info("Loaded state from " + savePath);
        }
    }
}

void LibretroGame::update()
{
    super::update(); // Handles titleMenu update

    if (fileBrowserMenu)
    {
        updateFileBrowser();
        return; // Don't run game while browsing
    }

    if (!titleMenuShowing)
    {
        if (retro_run)
        {
            long long currentTime = System::currentHighResTimer();
            if (lastFrameTime == 0) lastFrameTime = currentTime;
            
            double delta = System::getTicksBetweenTimes(lastFrameTime, currentTime);
            lastFrameTime = currentTime;
            
            accumulatedTime += delta;
            
            if (accumulatedTime > 200.0) accumulatedTime = 200.0;

            double frameTime = 1000.0 / fps;
            
            while (accumulatedTime >= frameTime)
            {
                retro_run();
                accumulatedTime -= frameTime;
            }
        }
        else
        {
            titleMenuShowing = true;
        }
    }
}

void LibretroGame::render()
{
    if (titleMenuShowing && titleMenu)
    {
        titleMenu->render();
    }

    if (fileBrowserMenu)
    {
        fileBrowserMenu->render();
    }

    if (!titleMenuShowing && !fileBrowserMenu && videoTexture)
    {
        // Draw video texture to screen
        float screenW = (float)GLUtils::getViewportWidth();
        float screenH = (float)GLUtils::getViewportHeight();
        
        float texW = (float)videoTexture->getImageWidth();
        float texH = (float)videoTexture->getImageHeight();
        
        if (texW > 0 && texH > 0)
        {
            float scale = min(screenW / texW, screenH / texH);
            float w = texW * scale;
            float h = texH * scale;
            float x = (screenW - w) / 2.0f;
            float y = (screenH - h) / 2.0f;
            
            GLUtils::drawTexture(videoTexture.get(), x, x + w, y, y + h, 1.0f, GLUtils::FILTER_NEAREST);
        }
    }
}

bool LibretroGame::retroEnvironment(unsigned cmd, void* data)
{
    switch (cmd)
    {
        case RETRO_ENVIRONMENT_GET_LOG_INTERFACE:
        {
            struct retro_log_callback *cb = (struct retro_log_callback *)data;
            cb->log = retroLogCallback;
            return true;
        }
        case RETRO_ENVIRONMENT_GET_CAN_DUPE:
            *(bool*)data = true;
            return true;
        case RETRO_ENVIRONMENT_SET_PIXEL_FORMAT:
        {
            const enum retro_pixel_format *fmt = (enum retro_pixel_format *)data;
            if (instance) instance->pixelFormat = *fmt;
            return true;
        }
        case RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY:
        {
            const char** dir = (const char**)data;
            static string sysDir = Main::getPath() + "data/libretro/system";
            *dir = sysDir.c_str();
            return true;
        }
        case RETRO_ENVIRONMENT_GET_SAVE_DIRECTORY:
        {
            const char** dir = (const char**)data;
            static string saveDir = Main::getPath() + "data/libretro/saves";
            *dir = saveDir.c_str();
            return true;
        }
        case RETRO_ENVIRONMENT_GET_VARIABLE:
        {
            struct retro_variable *var = (struct retro_variable *)data;
            if (instance && instance->variables.count(var->key))
            {
                var->value = instance->variables[var->key].c_str();
                return true;
            }
            return false;
        }
    }
    return false;
}

void LibretroGame::retroVideoRefresh(const void* data, unsigned width, unsigned height, size_t pitch)
{
    if (instance && data)
    {
        if (!instance->videoTexture || instance->videoTexture->getImageWidth() != width || instance->videoTexture->getImageHeight() != height)
        {
             shared_ptr<ByteArray> emptyData = make_shared<ByteArray>(width * height * 4);
             instance->videoTexture = GLUtils::getTextureFromData("Libretro", width, height, emptyData.get());
        }

        static std::vector<u32> conversionBuffer;
        if (conversionBuffer.size() < width * height) conversionBuffer.resize(width * height);
        u32* output = conversionBuffer.data();

        if (instance->pixelFormat == RETRO_PIXEL_FORMAT_XRGB8888)
        {
            // XRGB8888 (0x00RRGGBB) -> LE: BB GG RR XX
            // GL_RGBA expects RR GG BB AA
            // Need to swap B and R, and set A to FF
            
            const u32* input = (const u32*)data;
            unsigned pitchPixels = pitch / 4;

            for (unsigned y = 0; y < height; y++)
            {
                const u32* line = input + y * pitchPixels;
                for (unsigned x = 0; x < width; x++)
                {
                    u32 pixel = line[x];
                    u8 r = (pixel >> 16) & 0xFF;
                    u8 g = (pixel >> 8) & 0xFF;
                    u8 b = pixel & 0xFF;
                    
                    // Output: 0xAABBGGRR (LE) -> RR GG BB AA
                    output[y * width + x] = (0xFF << 24) | (b << 16) | (g << 8) | r;
                }
            }
            GLUtils::updateTexture(instance->videoTexture, 0, 0, width, height, (u8*)output);
        }
        else if (instance->pixelFormat == RETRO_PIXEL_FORMAT_RGB565)
        {
            // RGB565 -> RGBA8888
            unsigned pitchPixels = pitch / 2;
            
            for (unsigned y = 0; y < height; y++)
            {
                const u16* line = (const u16*)((const u8*)data + y * pitch);
                for (unsigned x = 0; x < width; x++)
                {
                    u16 pixel = line[x];
                    u8 r = (pixel >> 11) & 0x1F;
                    u8 g = (pixel >> 5) & 0x3F;
                    u8 b = pixel & 0x1F;
                    
                    r = (r << 3) | (r >> 2);
                    g = (g << 2) | (g >> 4);
                    b = (b << 3) | (b >> 2);
                    
                    output[y * width + x] = (0xFF << 24) | (b << 16) | (g << 8) | r;
                }
            }
            GLUtils::updateTexture(instance->videoTexture, 0, 0, width, height, (u8*)output);
        }
        else if (instance->pixelFormat == RETRO_PIXEL_FORMAT_0RGB1555)
        {
             // 0RGB1555 -> RGBA8888
             unsigned pitchPixels = pitch / 2;

             for (unsigned y = 0; y < height; y++)
             {
                 const u16* line = (const u16*)((const u8*)data + y * pitch);
                 for (unsigned x = 0; x < width; x++)
                 {
                     u16 pixel = line[x];
                     u8 r = (pixel >> 10) & 0x1F;
                     u8 g = (pixel >> 5) & 0x1F;
                     u8 b = pixel & 0x1F;

                     r = (r << 3) | (r >> 2);
                     g = (g << 3) | (g >> 2);
                     b = (b << 3) | (b >> 2);

                     output[y * width + x] = (0xFF << 24) | (b << 16) | (g << 8) | r;
                 }
             }
             GLUtils::updateTexture(instance->videoTexture, 0, 0, width, height, (u8*)output);
        }
    }
}

void LibretroGame::retroAudioSample(int16_t left, int16_t right)
{
    if (instance)
    {
        std::lock_guard<std::mutex> lock(instance->audioMutex);
        instance->audioBuffer.push_back(left);
        instance->audioBuffer.push_back(right);
        if (instance->audioBuffer.size() > 44100 * 2) {
             instance->audioBuffer.clear();
        }
    }
}

size_t LibretroGame::retroAudioSampleBatch(const int16_t* data, size_t frames)
{
    if (instance)
    {
        std::lock_guard<std::mutex> lock(instance->audioMutex);
        instance->audioBuffer.insert(instance->audioBuffer.end(), data, data + frames * 2);
        if (instance->audioBuffer.size() > 44100 * 2) {
             instance->audioBuffer.clear();
        }
    }
    return frames;
}

void LibretroGame::retroInputPoll()
{
    // Poll input
}

int16_t LibretroGame::retroInputState(unsigned port, unsigned device, unsigned index, unsigned id)
{
    if (port == 0 && device == RETRO_DEVICE_JOYPAD && instance)
    {
        shared_ptr<ControlsManager> cm = instance->getControlsManager();
        if(!cm) return 0;

        switch(id)
        {
            case RETRO_DEVICE_ID_JOYPAD_B: return cm->MINIGAME_ACTION_HELD ? 1 : 0;
            case RETRO_DEVICE_ID_JOYPAD_Y: return cm->MINIGAME_RUN_HELD ? 1 : 0;
            case RETRO_DEVICE_ID_JOYPAD_SELECT: return cm->MINIGAME_SELECT_HELD ? 1 : 0;
            case RETRO_DEVICE_ID_JOYPAD_START: return cm->MINIGAME_START_HELD ? 1 : 0;
            case RETRO_DEVICE_ID_JOYPAD_UP: return cm->MINIGAME_UP_HELD ? 1 : 0;
            case RETRO_DEVICE_ID_JOYPAD_DOWN: return cm->MINIGAME_DOWN_HELD ? 1 : 0;
            case RETRO_DEVICE_ID_JOYPAD_LEFT: return cm->MINIGAME_LEFT_HELD ? 1 : 0;
            case RETRO_DEVICE_ID_JOYPAD_RIGHT: return cm->MINIGAME_RIGHT_HELD ? 1 : 0;
            case RETRO_DEVICE_ID_JOYPAD_A: return cm->MINIGAME_A_HELD ? 1 : 0;
            case RETRO_DEVICE_ID_JOYPAD_X: return cm->MINIGAME_X_HELD ? 1 : 0;
            case RETRO_DEVICE_ID_JOYPAD_L: return cm->MINIGAME_L_HELD ? 1 : 0;
            case RETRO_DEVICE_ID_JOYPAD_R: return cm->MINIGAME_R_HELD ? 1 : 0;
        }
    }
    return 0;
}

void LibretroGame::audioCallback(void *udata, Uint8 *stream, int len)
{
    LibretroGame* self = (LibretroGame*)udata;
    if (!self) return;

    memset(stream, 0, len);

    std::lock_guard<std::mutex> lock(self->audioMutex);

    size_t bytesNeeded = len;
    size_t bytesAvailable = self->audioBuffer.size() * sizeof(int16_t);

    size_t bytesToCopy = (bytesAvailable < bytesNeeded) ? bytesAvailable : bytesNeeded;

    if (bytesToCopy > 0)
    {
        memcpy(stream, self->audioBuffer.data(), bytesToCopy);
        size_t samplesConsumed = bytesToCopy / sizeof(int16_t);
        self->audioBuffer.erase(self->audioBuffer.begin(), self->audioBuffer.begin() + samplesConsumed);
    }
}
