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

        static float GetFPS() {
            return 1.0f / deltaTime;
        }

        static float GetSmoothFPS() {
            return 1.0f / smoothedDeltaTime;
        }

        static void IncrementAppTime() {
            appTime += deltaTime;
        }

        static void SetDeltaTime(float newDeltaTime) {
            deltaTime = newDeltaTime;
            ComputeSmoothDeltaTime();
            IncrementAppTime();
        }

        static double GetAppTime() {
            return appTime;
        }


    private:
        static void ComputeSmoothDeltaTime() {
            smoothedDeltaTime = smoothFactor * deltaTime + (1.0f - smoothFactor) * smoothedDeltaTime;
        }
    private:
        static inline float deltaTime;

        static inline float smoothFactor = 0.9f;
        static inline float smoothedDeltaTime;
        static inline double appTime = 0.0f;
    };
}