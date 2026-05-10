#include "Animation.h"

Animation::Animation(sf::Sprite &sprite, sf::IntRect frame_rect, unsigned frames, unsigned frames_duration)
    : sprite(sprite), frameRect(frame_rect), frames(frames), frame(0), timer(0)
{
    frameDurations = new unsigned[frames];
    for (int i = 0; i < frames; ++i)
        frameDurations[i] = frames_duration;
    sprite.setTextureRect(frameRect);
}

Animation::Animation(sf::Sprite &sprite, sf::IntRect frame_rect, unsigned frames, std::vector<unsigned> frame_durations)
    : sprite(sprite), frameRect(frame_rect), frames(frames), frame(0), timer(0)
{
    frameDurations = new unsigned[frames] {};
    for (int i = 0; i < frame_durations.size(); ++i)
        frameDurations[i] = frame_durations[i];
    sprite.setTextureRect(frameRect);
}

Animation::~Animation()
{
    delete[] frameDurations;
}

void Animation::Play(float dt)
{
    if (timer >= frameDurations[frame])
    {
        frame = (frame + 1) % frames;
        timer = 0.f;
    }
    
    frameRect.position.x = frame * frameRect.size.x;
    sprite.setTextureRect(frameRect);
    timer += dt * 1000;
}

void Animation::ResetAnimation()
{
    frame = 0;
    timer = 0.f;
}
