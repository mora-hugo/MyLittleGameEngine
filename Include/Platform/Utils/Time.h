#pragma once

namespace HC {
    class Time {
    public:
        static float GetDeltaTime() {
            return deltaTime;
        }

        static float GetSmoothDeltaTime() {
            return smoothedDeltaTime;
        }

        static void SetDeltaTime(float newDeltaTime) {
            deltaTime = newDeltaTime;
            ComputeSmoothDeltaTime();
        }


    private:
        static void ComputeSmoothDeltaTime() {
            smoothedDeltaTime = smoothFactor * deltaTime + (1.0f - smoothFactor) * smoothedDeltaTime;
        }
    private:
        static inline float deltaTime;

        static inline float smoothFactor = 0.9f;
        static inline float smoothedDeltaTime;
    };
}