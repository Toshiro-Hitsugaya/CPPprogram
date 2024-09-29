#include <chrono>
class timer {
public:
    int startTime;
    timer() : startTime(0) {}

    void startTimer() {
        startTime = getCurrentTime(); //当前时间
    }

    int getElapsedTime() {
        return getCurrentTime() - startTime; //经过的时间
    }

private:
    int getCurrentTime() {
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
        return static_cast<int>(duration.count());
    }
};