#pragma once
#include <stdint.h>

class Button {
public:
    // Constructor with configurable timing parameters (in milliseconds)
    // Default: 400ms double-click timeout, 1000ms long-press threshold
    explicit Button(uint16_t double_click_timeout = 400, uint16_t long_press_threshold = 1000)
        : double_click_timeout_(double_click_timeout),
          long_press_threshold_(long_press_threshold) {}

    // Call this regularly with current button state (true=pressed, false=released)
    // and current time in milliseconds
    void update(bool is_pressed_now, uint16_t current_time) {
        // Detect rising edge (button pressed)
        if (is_pressed_now && !was_pressed_) {
            handle_press(current_time);
        }
        // Detect falling edge (button released)
        else if (!is_pressed_now && was_pressed_) {
            handle_release(current_time);
        }

        // Check for click timeout
        if (click_count_ > 0 && (current_time - last_release_time_) > double_click_timeout_) {
            if (click_count_ == 1) {
                if (click_callback_) click_callback_(last_click_duration_);
            } 
            else if (click_count_ == 2) {
                if (double_click_callback_) double_click_callback_(last_click_duration_, prev_click_duration_);
            }
            click_count_ = 0;
        }

        was_pressed_ = is_pressed_now;
    }

    // Callback setters
    void set_click_callback(void (*callback)(uint16_t duration)) {
        click_callback_ = callback;
    }

    void set_double_click_callback(void (*callback)(uint16_t first_duration, uint16_t second_duration)) {
        double_click_callback_ = callback;
    }

    void set_long_press_callback(void (*callback)(uint16_t duration)) {
        long_press_callback_ = callback;
    }

    // Get current state
    bool is_pressed() const { return was_pressed_; }
    uint8_t pending_clicks() const { return click_count_; }

private:
    void handle_press(uint16_t current_time) {
        press_time_ = current_time;
        
        // Store previous click duration if this is a potential double-click
        if (click_count_ == 1) {
            prev_click_duration_ = last_click_duration_;
        }
    }

    void handle_release(uint16_t current_time) {
        last_click_duration_ = current_time - press_time_;
        last_release_time_ = current_time;

        // Check for long press
        if (last_click_duration_ >= long_press_threshold_) {
            if (long_press_callback_) long_press_callback_(last_click_duration_);
            click_count_ = 0; // Long press cancels click counting
        } else {
            click_count_++;
        }
    }

    // Configuration
    const uint16_t double_click_timeout_;
    const uint16_t long_press_threshold_;

    // State tracking
    bool was_pressed_ = false;
    uint16_t press_time_ = 0;
    uint16_t last_release_time_ = 0;
    uint16_t last_click_duration_ = 0;
    uint16_t prev_click_duration_ = 0;
    uint8_t click_count_ = 0;

    // Callbacks (using function pointers for smaller memory footprint)
    void (*click_callback_)(uint16_t) = nullptr;
    void (*double_click_callback_)(uint16_t, uint16_t) = nullptr;
    void (*long_press_callback_)(uint16_t) = nullptr;
};