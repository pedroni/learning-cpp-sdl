#ifndef Animation_hpp
#define Animation_hpp

struct Animation {
    const char *path;
    int frames;
    int speed;
    int frameWidth;

    Animation() {}

    Animation(const char *path, int frames, int speed, int frameWidth) {
        this->path = path;
        this->frames = frames;
        this->speed = speed;
        this->frameWidth = frameWidth;
    }
};

#endif
