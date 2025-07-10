#pragma once
#include <stdint.h>

class Led {
public:
    enum class State {
        On,
        Off,
        Toggle_500ms,
        Toggle_1000ms,
        Toggle_2000ms,
        Toggle_4000ms
    };

    // Constructor takes a hardware control function
    Led(void (*set_fn)(bool), State initial_state = State::Off)
        : _set_led_state(set_fn), _current_state(initial_state) 
    {
        // Set initial hardware state
        _set_led_state(_current_state == State::On);
    }

    // Update function - call in main loop
    void update(uint32_t current_ms) {
        if (_current_state == State::On || _current_state == State::Off) {
            return; // No updates needed for static states
        }

        uint32_t toggle_interval;
        switch (_current_state) {
            case State::Toggle_500ms:  toggle_interval = 500;  break;
            case State::Toggle_1000ms: toggle_interval = 1000; break;
            case State::Toggle_2000ms: toggle_interval = 2000; break;
            case State::Toggle_4000ms: toggle_interval = 4000; break;
            default: return;
        }

        if (current_ms - _last_toggle_time >= toggle_interval) {
            _current_output = !_current_output;
            _set_led_state(_current_output);
            _last_toggle_time = current_ms;
        }
    }

    // Change LED state
    void setState(State new_state){
        if (_current_state != new_state) {
            _current_state = new_state;

            // Immediate state change for On/Off
            if (new_state == State::On) {
                _set_led_state(true);
                _current_output = true;
            } else if (new_state == State::Off) {
                _set_led_state(false);
                _current_output = false;
            }

            // Reset toggle timing when changing modes
            _last_toggle_time = 0;
        }
    }

    // Get current state
    State getState() const { return _current_state; }

private:
    void (*_set_led_state)(bool); // Hardware control function
    State _current_state;
    uint32_t _last_toggle_time = 0;
    bool _current_output = false;
};