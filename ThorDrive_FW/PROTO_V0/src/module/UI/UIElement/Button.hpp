#pragma once
#include <stdint.h>
#include <stdbool.h>

class Button {
public:
    // Event Types
    enum class Event: uint8_t {
        Pressed,
        Released,
        SingleClick,
        DoubleClick,
        TripleClick,
        LongClick,
        ExtraLongClick
    };

    // Timing Configuration
    struct Config {
        uint16_t debounce_ms = 100;
        uint16_t long_press_ms = 4000;
        uint16_t extra_long_press_ms = 10000;
        uint16_t multi_click_timeout_ms = 1000;
        uint8_t max_clicks = 3;
    };

    // Callback
    typedef void (*EventHandler)(Event);

    // Constructor (takes a state-reader function)
    Button(bool (*read_state)(void), const Config& config)
        : _read_state(read_state), _config(config) {}


void update(uint32_t current_ms) {
    bool current_state = _read_state();

    // Debounce logic
    if (current_state != _last_state) {
        if ((current_ms - _last_change_time) >= _config.debounce_ms) {
            _last_state = current_state;
            _last_change_time = current_ms;

            if (current_state) {
                // Pressed
                _press_time = current_ms;
                _notify(Event::Pressed);
            } else {
                // Released
                _notify(Event::Released);

                uint32_t press_duration = current_ms - _press_time;

                if (press_duration >= _config.extra_long_press_ms) {
                    _notify(Event::ExtraLongClick);
                }
                else if (press_duration >= _config.long_press_ms) {
                    _notify(Event::LongClick);
                }
                else {
                    _click_count++;
                    _multi_click_timeout = current_ms + _config.multi_click_timeout_ms;
                }
            }
        }
    }

    // Multi-click decision logic
    if (!current_state && _click_count > 0 && current_ms >= _multi_click_timeout) {
        switch (_click_count) {
            case 1: _notify(Event::SingleClick); break;
            case 2: _notify(Event::DoubleClick); break;
            case 3: _notify(Event::TripleClick); break;
        }
        _click_count = 0;
    }
}

    // Subscribe to events
    void subscribe(EventHandler handler) { _event_handler = handler; }

private:
    bool (*_read_state)(void); // Hardware read function
    EventHandler _event_handler = nullptr;
    Config _config;

    // Internal state tracking
    uint32_t _press_time = 0;
    bool _last_state = false;
    uint32_t _last_change_time = 0;
    uint32_t _multi_click_timeout = 0;
    uint8_t _click_count = 0;

    void _notify(Event event){
        if (_event_handler) {
            _event_handler(event);
        }
    }
};