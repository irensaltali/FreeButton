class FreeButton{
    public:
        typedef void (*f)();
        FreeButton();
        FreeButton(int pin, bool pullup_enable=true, bool active_low=false);
        int Read();
        void OnPressed(f callback);
        void OnUnPressed(f callback);
        void OnPressedForDuration(f callback, unsigned int duration);
        void SetPin(int pin);

    protected:
        f _pressed_callback;
        f _un_pressed_callback;
        f _pressed_for_duration_callback;
        int lastState;
        bool safeRead();

    private:
        int _currentPin;
        unsigned int _longPressDuration;
        unsigned int _debouncedTime;
        int _active_low;

};