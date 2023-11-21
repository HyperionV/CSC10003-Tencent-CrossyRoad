#pragma once

#include <xaudio2.h>
#include <iostream>
#include <string>
using namespace std;
#ifdef _XBOX 
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif

#ifndef _XBOX
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif
class Audio
{
protected:
    HRESULT hr;
    IXAudio2* pXAudio2;
    IXAudio2SourceVoice* pSourceVoice;
    IXAudio2MasteringVoice* pMasterVoice;
    HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition);
    HRESULT ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset);
public:

    Audio();
    int Play(string path, float volume = 1, bool ShouldLoop = false); // plays the audio file with specified volume and can be looped
    string BasePath; // Directory where all audio files (relevant to project) are stored i.e if all audio files are stored in "D:\game" than set BasePath to "D:\game", this will be automatically added in path of every audio file
    void Stop();
    void clearBuffer();
};
string getCurrentDirectoryOnWindows();
class MyVoiceCallback : public IXAudio2VoiceCallback
{
public:
    virtual void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32 BytesRequired) override {}
    virtual void STDMETHODCALLTYPE OnVoiceProcessingPassEnd() override {}
    virtual void STDMETHODCALLTYPE OnStreamEnd() override {
        SetEvent(hStreamEndEvent); // Signal the event when the stream ends
    }
    virtual void STDMETHODCALLTYPE OnBufferStart(void* pBufferContext) override {}
    virtual void STDMETHODCALLTYPE OnBufferEnd(void* pBufferContext) override {}
    virtual void STDMETHODCALLTYPE OnLoopEnd(void* pBufferContext) override {}
    virtual void STDMETHODCALLTYPE OnVoiceError(void* pBufferContext, HRESULT Error) override {}

    HANDLE hStreamEndEvent; // Event to signal when the stream ends

    MyVoiceCallback() : hStreamEndEvent(CreateEvent(nullptr, FALSE, FALSE, nullptr)) {}
    virtual ~MyVoiceCallback() { CloseHandle(hStreamEndEvent); }
};
