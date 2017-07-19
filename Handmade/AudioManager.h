/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : February 2017

  -----------------------------------------------------------------------------------------------

- This class encapsulates an audio manager which will load music, sound effects and voice audio
  files from disk and store them as FMOD sound objects in a map, with a string reference to that
  audio object. Currently the audio files supported are MP3, WAV, OGG, FLAC, <TBA>. To access any
  particular audio inside the map the string reference is needed to sift through the map and find 
  the audio. Audio objects can also be unloaded from memory individually or in bulk. This class is 
  a Singleton. The main member variable is m_audioSystem, which is a handle on the entire FMOD audio
  sub-system and is used to actually play any audio. 

- Two enum types have been created. The RemoveType enum is used when removing audio objects from
  the map. Either one single specific FMOD audio object can be removed, or the entire map of audio
  objects can be cleared. The AudioType enum is there for letting the manager class know what type
  of audio it will de dealing with. 

- To use this class, a Audio object needs to be created inside the game client code. Then that
  audio object will be able to link to a specific FMOD audio object from within the Audio Manager.
  The GetAudioData() function is used to request the FMOD sound pointer and link the audio data with
  the audio object. The other getter routine GetAudioSystem() will return the FMOD audio system pointer
  which is used inside the Audio class' Play() function to play audio. 

- The LoadFromFile() routine will load in the audio data from a file and store the audio in the 
  correct audio map. Both the music and voice audio is loaded into memory in a streamed way, so
  as to save on memory because these files can become plentiful and large. SFX files are loaded
  in directly into memory and kept there. Streamed audio is CPU intensive!

- An Output() routine is there for debug purposes only and will print to the console how many audio
  objects are currently stored in each of the three supported maps.

*/

#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <map>
#include <string>
#include <fmod.hpp>
#include "Singleton.h"

class AudioManager
{

public:

	enum RemoveType { CUSTOM_AUDIO, ALL_AUDIO };
	enum AudioType  { SFX_AUDIO, MUSIC_AUDIO, VOICE_AUDIO };
	
public:

	friend class Singleton<AudioManager>;

public :

	FMOD::System* GetAudioSystem();
	FMOD::Sound* GetAudioData(AudioType audioType, const std::string& mapIndex);

public :

	bool Initialize();
	bool LoadFromFile(const std::string& filename, AudioType audioType, const std::string& mapIndex);

public :

	void Update();
	
public :

	void UnloadFromMemory(AudioType audioType, RemoveType removeType, const std::string& mapIndex = "");
	void ShutDown();

public:

	void Output();

private:

	AudioManager();
	AudioManager(const AudioManager&);
	AudioManager& operator=(const AudioManager&);

private :

	FMOD::System* m_audioSystem;
	
	std::map<std::string, FMOD::Sound*> m_sfxDataMap;
	std::map<std::string, FMOD::Sound*> m_musicDataMap;	
	std::map<std::string, FMOD::Sound*> m_voiceDataMap;	

};

typedef Singleton<AudioManager> TheAudio;

#endif