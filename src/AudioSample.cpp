#include "AudioSample.h"
#include "OpenALSoundPlayer.h"
#include "ofMain.h"

AudioSample::~AudioSample()
{
    if(bEditorMode)
    {
        disableEditorMode();
    }
}
AudioSample::AudioSample()
{
    totalDelay = 0;
    curDelay = 0;
    gain = 1.0f;
    pitch = 1.0f;
    config = nullptr;
    bEditorMode = false;
    bSelected = false;
    //cout << "constructor, config = " << config << endl;
}

//--------------------------------------------------------------
AudioSample::AudioSample(const AudioSample& parent)
{
    totalDelay = parent.totalDelay;
    curDelay = parent.curDelay;
    gain = parent.gain;
    pitch = parent.gain;
    config = parent.config;
    bEditorMode = parent.bEditorMode;
    bSelected = parent.bSelected;

    sample_path = parent.sample_path;
    audioPlayer = parent.audioPlayer;

    setWidth(parent.getWidth());
    setHeight(parent.getHeight());
}

//--------------------------------------------------------------
void AudioSample::render(ofVec3f pos)
{
    setPosition(pos);

    ofPushStyle();

    ofSetColor(255);
    ofDrawRectRounded(getPosition(), getWidth(),getHeight(),config->x_scale*5);

    if(audioPlayer->isPlaying())
    {
        ofSetColor(200);
    } else {
        ofSetColor(255);
    }

    if(bSelected) {
        ofNoFill();
        ofSetColor(255,0,0);
        ofDrawRectRounded(pos, config->sample_gui_width*audioPlayer->getPosition(),35*config->y_scale,config->x_scale*5);
    }
    ofDrawRectRounded(pos, config->sample_gui_width*audioPlayer->getPosition(),35*config->y_scale,config->x_scale*5);

    ofSetColor(50);
    std::filesystem::path p(sample_path);
    string name = p.filename().string(); //audioPlayer->getFormatString()
    config->f2().drawString(name,pos.x+20*config->x_scale,pos.y+22*config->y_scale);

    ofPopStyle();
}

//--------------------------------------------------------------
void AudioSample::enableEditorMode()
{
    if(!bEditorMode) {
        enableEvents();
        ofAddListener(this->clickedEvent, this, &AudioSample::onClicked);
        bEditorMode = true;
    }


}

//--------------------------------------------------------------
void AudioSample::disableEditorMode()
{
    if(bEditorMode) {
        disableEvents();
        ofRemoveListener(this->clickedEvent, this, &AudioSample::onClicked);
        bEditorMode = false;
    }
}

//--------------------------------------------------------------
void AudioSample::onClicked(ClickArgs& args) {
    ofLogNotice() << "Clicked AudioSample: " << sample_path;

}
