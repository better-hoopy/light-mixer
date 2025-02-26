class Player {
    public:

    // GPIO pins for the red, green and blue potentiometers
    uint8_t potPinR;
    uint8_t potPinG;
    uint8_t potPinB;

    // This variable defines how many brightness levels there should be for each color
    uint8_t numberOfBrightnessLevels = 4;

    // This variable defines how much dead space should be between each brightness level, so they don't toggle back and forth if they're right on the edge
    uint8_t deadZoneAmount = 2;

    // Calculated brightness for the red, green and blue LEDs
    uint8_t levelR;
    uint8_t levelG;
    uint8_t levelB;

    // Calculated brightness for the red, green and blue LEDs
    uint8_t valR;
    uint8_t valG;
    uint8_t valB;

    Player(uint8_t r, uint8_t g, uint8_t b) {
        potPinR = r;
        potPinG = g;
        potPinB = b;
    }

    void pollPots() {
        levelR = calculateBrightnessLevel(potPinR, levelR);
        levelG = calculateBrightnessLevel(potPinG, levelG);
        levelB = calculateBrightnessLevel(potPinB, levelB);

        valR = calculateBrightness(levelR);
        valG = calculateBrightness(levelG);
        valB = calculateBrightness(levelB);
    }

    // numberOfBrightnessLevels : [ possible brightness values ]
    // 2: [ 0, 255 ]
    // 3: [ 0, 128, 255 ]
    // 4: [ 0, 85, 170, 255 ]
    // 5: [ 0, 64, 128, 192, 255 ]
    uint8_t calculateBrightnessLevel(uint8_t potPin, uint8_t oldBrightnessLevel) {
        uint8_t brightnessLevel = oldBrightnessLevel;
        uint8_t newBrightness = map(analogRead(potPin), 0, 4095, 0, 255);
        for (uint8_t i = 0; i < numberOfBrightnessLevels; i++) {
            uint8_t lowEnd = i * (255 / numberOfBrightnessLevels) + (i == 0 ? 0 : deadZoneAmount);
            uint8_t highEnd = (i + 1) * (255 / numberOfBrightnessLevels);
            if (i + 1 == numberOfBrightnessLevels) {
                highEnd = 255;
            }
            if (newBrightness >= lowEnd && newBrightness <= highEnd) {
                return i;
            }
        }
        return brightnessLevel;
    }

    uint8_t calculateBrightness(uint8_t level) {
        // because of division rounding in the last return statement, the maths
        // might not make exactly 0 and 255 for the limits (in fact, they might
        // overflow), so pin the limits with some special `if` statements:
        if (level <= 0) {
            return 0;
        }
        if (level >= numberOfBrightnessLevels - 1) {
            return 255;
        }
        return level * (255 / (numberOfBrightnessLevels - 1));
    }
};
