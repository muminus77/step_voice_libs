#ifndef SPIRIT_VOICE_H
#define SPIRIT_VOICE_H

#include <ros/ros.h>
#include <ros/package.h>

#include <std_msgs/String.h>

#include <speak_lib.h>

#include <cstdlib>
#include <cstdio>
#include <cstring>

#define USE_DEBUG 1

namespace spirit
{
class RobotVoice
{
public:
    enum Voice {MALE, FEMALE, POLISH};
    ros::NodeHandle nh;
    ros::NodeHandle ph;

    RobotVoice(Voice voice);

    void SayIt(int param, std::string status = "");


private:

    espeak_VOICE voice_select;
    Voice current_voice;
    int phrases_said;

    std::string getVoiceFileName(Voice voice);
};
}

#endif //SPIRIT_VOICE_H
