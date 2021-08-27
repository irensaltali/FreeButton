class FreeButton{
    public:
        typedef void (*f)();
        FreeButton();
        FreeButton(int pin);
        int Read();
        void OnPressed(f callback);
        void OnUnPressed(f callback);
        void OnPressedForDuration(f callback, unsigned int duration);
        void SetPin(int pin);

    protected:
        int currentPin;
        unsigned int LongPressDuration;
        f _pressed_callback;
        f _un_pressed_callback;
        f _pressed_for_duration_callback;
        int lastState;
        int safeRead();
};