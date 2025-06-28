// SimpleScheduler.h
#pragma once
#include <stdint.h>


class simpleTimer {
public:
    // Initialize with current time
    simpleTimer() : _lastTime(0) {}

    // Update internal time tracking (call once per loop())
    void update(uint32_t current_time) {
        _currentTime = current_time;
    }

    // Check if interval (ms) has passed for Task 1
    bool checkTask(uint32_t interval) {
        if (_currentTime - _lastTime >= interval) {
            _lastTime = _currentTime;
            return true;
        }
        return false;
    }


private:
    uint32_t _currentTime;
    uint32_t _lastTime;
};
