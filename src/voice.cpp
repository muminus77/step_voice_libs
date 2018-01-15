#include <step_voice_libs/voice.h>

namespace spirit
{
RobotVoice::RobotVoice(Voice voice):
    ph("~")
{
    espeak_Initialize(AUDIO_OUTPUT_PLAYBACK, 0, NULL, 0);
    // See speak_lib.h for details and range of the parameters below
    int rate, volume, pitch, range, punctuation;
    int voice_num, dialect_num, capitals, wordgap, age, gender;

    // Fetch default parameters
    rate = 250;// espeak_GetParameter(espeakRATE, 0);
    volume = espeak_GetParameter(espeakVOLUME, 0);
    pitch = espeak_GetParameter(espeakPITCH, 0);
    range = espeak_GetParameter(espeakRANGE, 0);
    punctuation = espeak_GetParameter(espeakPUNCTUATION, 0);
    capitals = espeak_GetParameter(espeakCAPITALS, 0);
    wordgap = 0;//espeak_GetParameter(espeakWORDGAP, 0);

    voice_num = 1;
    dialect_num = 1;

    age=0;
    gender=2;

    std::string voice_name, dialect, file;
    voice_name = "english";
    dialect = "en-us";
    file=getVoiceFileName(voice);


//    std::memset(&voice_select,0,sizeof(voice_select));
//    voice_select.name = voice_name.c_str();
//    voice_select.languages = dialect.c_str();
//    voice_select.identifier= file.c_str();
//    voice_select.age = age; // 0=not specified, or age in years
//    voice_select.gender = gender; // 0=none, 1=male, 2=female
    //        if (espeak_SetVoiceByProperties(&voice_select) != EE_OK) {
    //                ROS_ERROR("Could not set espeak voice properties. Aborting.");
    //            }
    if (espeak_SetVoiceByName(file.c_str()) != EE_OK) {
        ROS_ERROR("Could not set espeak voice. Aborting.");
    }

//    if (espeak_SetParameter(espeakRATE, rate, 0) != EE_OK) {
//                ROS_ERROR("Could not set espeak rate. Aborting.");
//            }
//    if (espeak_SetParameter(espeakWORDGAP, wordgap, 0) != EE_OK) {
//        ROS_ERROR("Could not set espeak wordgap. Aborting.");
//    }
    current_voice=voice;
    phrases_said=0;
}

void RobotVoice::SayIt(int param, std::string status)
{
    std::string langs[3];
    langs[0]="mb-en1";
    langs[1]="female5";
    langs[2]="mb-pl1";

    espeak_Synth(status.c_str(), status.length()+1, 0, POS_CHARACTER, 0,
                     espeakCHARS_AUTO | espeakPHONEMES | espeakENDPAUSE, NULL, NULL);
    espeak_Synchronize();
    phrases_said++;


}

std::string RobotVoice::getVoiceFileName(RobotVoice::Voice voice)
{
    std::string voice_file;
    switch(voice)
    {
    case MALE:
        voice_file="mb-en1";
        break;
    case FEMALE:
        voice_file="female5";
        break;
    case POLISH:
        voice_file="mb-pl1";
    }
    current_voice=voice;
    return voice_file;
}
}
