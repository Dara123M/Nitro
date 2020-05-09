#include "precomp.h"

#include "AudioController.h"

bool Nitro::AudioController::Init(Engine::AudioManager* audioManager_)
{
	ASSERT(audioManager_ != nullptr, "Must pass a valid audioManager");
	if (!audioManager_->LoadMusic("Resource/Sound/music.ogg", "background_music"))
	{
		LOG_WARNING("Failed to load music.ogg");
		return false;
	}
	
	if (!audioManager_->LoadMusic("Resource/Sound/music_end.mp3", "score_music"))
	{
		LOG_WARNING("Failed to load music_end.mp3");
		return false;
	}

	if (!audioManager_->LoadSoundEffect("Resource/Sound/jump.wav", "jump_sound"))
	{
		LOG_WARNING("Failed to load jump.wav");
		return false;
	}
	if (!audioManager_->LoadSoundEffect("Resource/Sound/finish.ogg", "finish_sound"))
	{
		LOG_WARNING("Failed to load finish.ogg");
		return false;
	}
	//audioManager_->PlayMusic("background_music");
	return true;
}

void Nitro::AudioController::Update(float dt, Engine::AudioManager* audioManager_)
{
}
