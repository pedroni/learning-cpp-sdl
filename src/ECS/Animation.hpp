#ifndef Animation_hpp
#define Animation_hpp

struct Animation {
    const char *path;
    int frames;
    int frameWidth;
    int speed;

    Animation() {}

    Animation(const char *path, int frames, int frameWidth, int speed) {
        this->path = path;
        this->frames = frames;
        this->frameWidth = frameWidth;
        this->speed = speed;
    }
};

#endif
