#pragma once

#include <miniaudio.h>
#include <iostream>
#include <type_traits>
#include "Common/AudioCommands.h"

#include "Common/Log.h"

namespace Tapedawf {
    class AudioEngine {
    public:
        AudioEngine() = default;
        ~AudioEngine() { shutdown(); }

        bool init(AudioControls& controls, uint32_t sampleRate = 48000, uint32_t channels = 2) {
            m_controls = &controls;

            ma_device_config deviceConfig = ma_device_config_init(ma_device_type_playback);

            deviceConfig.playback.format = ma_format_f32;
            deviceConfig.playback.channels = channels;
            deviceConfig.sampleRate = sampleRate;
            deviceConfig.dataCallback = audioCallbackStatic;
            deviceConfig.pUserData = this;

            if (ma_device_init(NULL, &deviceConfig, &m_device) != MA_SUCCESS) {
                LOG("AudioEngine", "Failed to initialize playback device.");
                return false;
            }

            char deviceName[256];
            if (ma_device_get_name(&m_device, ma_device_type_playback, deviceName, sizeof(deviceName), NULL) == MA_SUCCESS) {
                LOG("AudioEngine", "Playback device initialized: {}", deviceName);
            }

            return true;
        }

        bool start() {
            return ma_device_start(&m_device) == MA_SUCCESS;
        }

        void stop() {
            ma_device_stop(&m_device);
        }

        void shutdown() {
            if (ma_device_get_state(&m_device) != ma_device_state_uninitialized) {
                ma_device_uninit(&m_device);
            }
        }

    private:
        ma_device m_device{};
        AudioControls* m_controls{nullptr};

        static void audioCallbackStatic(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {
            auto* engine = static_cast<AudioEngine*>(pDevice->pUserData);
            engine->processAudio(static_cast<float*>(pOutput), frameCount, pDevice->playback.channels);
        }

        void processAudio(float* pOutputBuffer, uint32_t frameCount, uint32_t channels) {
            if (!m_controls) return;

            AudioCommand cmd;
            while (m_controls->commandQueue.try_dequeue(cmd)) {
                std::visit([](auto&& arg) {
                    using T = std::decay_t<decltype(arg)>;

                    if constexpr (std::is_same_v<T, PlayCommand>) {
                        // Playback start
                    } else if constexpr (std::is_same_v<T, StopCommand>) {
                        // Playback stop
                    } else if constexpr (std::is_same_v<T, AddNodeCommand>) {
                        // Node insertion
                    }
                }, cmd);
            }

            float gain = m_controls->masterGain.load(std::memory_order_relaxed);

            size_t totalSamples = static_cast<size_t>(frameCount) * channels;

            for (size_t i = 0; i < totalSamples; ++i) {
                pOutputBuffer[i] *= gain;
            }

            // TODO - Pass buffer down into DAG processor
        }
    };
}