#include "precomp.h"
#include "GameModeController.h"
#include "TextureController.h"
#include "TextController.h"
#include "GameComponents.h"
//#include "Input/InputManager.h"
namespace Nitro {
	bool Nitro::GameModeController::Init(Engine::EntityManager* entityManager_) 
	{
		ASSERT(entityManager_ != nullptr, "Must pass a valid entity manager");

		m_GameMode = GameMode::MenuMode;
		auto players = entityManager_->GetAllEntitiesWithComponent<Engine::PlayerComponent>();
		auto player1 = players[0];
		auto player2 = players[1];
		if (player1->GetComponent<PlayerTagComponent>()->m_PlayerTag == PlayerTag::Two)
		{
			std::swap(player1, player2);
		}

		
	    auto start = Engine::Entity::Create();
		start->AddComponent<Engine::TextComponent>("PRESS ENTER OR Q TO START");
		start->AddComponent<Engine::TransformComponent>(400,20.f);
		start->AddComponent<TextInfoComponent>(PlayerTag::One, TextInfoType::Start, player1);
		entityManager_->AddEntity(std::move(start));

		auto pause = Engine::Entity::Create();
		pause->AddComponent<Engine::TextComponent>(" ");
		pause->AddComponent<Engine::TransformComponent>(300, 20.f);
		pause->AddComponent<TextInfoComponent>(PlayerTag::Two, TextInfoType::Pause, player2);
		entityManager_->AddEntity(std::move(pause));

		return true;
	}

	void Nitro::GameModeController::Update(float dt, Engine::EntityManager* entityManager_, Engine::AudioManager* audioManager_, Engine::InputManager* inputManager_/*, GameMode* gameMode_*/)
	{
		ASSERT(entityManager_ != nullptr, "Must pass a valid entity manager");

		auto texts = entityManager_->GetAllEntitiesWithComponent<Engine::TextComponent>();

		for (auto text : texts) {
			auto tekst = text->GetComponent<Engine::TextComponent>();
			auto info = text->GetComponent<TextInfoComponent>();

			switch (m_GameMode) {
			case GameMode::MenuMode: {


				if (info->m_Type== TextInfoType::Start && (inputManager_->IsActionInState("Start1Game", Engine::EInputActionState::Pressed) || inputManager_->IsActionInState("Start2Game", Engine::EInputActionState::Pressed))) {
					m_GameMode = GameMode::PlayingMode;
					audioManager_->PlayMusic("background_music");
					tekst->m_text = " ";
				}

			}break;
			case GameMode::PlayingMode: {

				if (info->m_Type == TextInfoType::Pause && (inputManager_->IsActionInState("Pause1Game", Engine::EInputActionState::Pressed) || inputManager_->IsActionInState("Pause2Game", Engine::EInputActionState::Pressed))) {
					m_GameMode = GameMode::PauseMode;
					audioManager_->PauseMusic();
					tekst->m_text = "PAUSE II";

				}
			}break;
			case GameMode::PauseMode: {

				if (info->m_Type == TextInfoType::Pause && (inputManager_->IsActionInState("Pause1Game", Engine::EInputActionState::Pressed) || inputManager_->IsActionInState("Pause2Game", Engine::EInputActionState::Pressed))) {
					m_GameMode = GameMode::PlayingMode;
					audioManager_->ResumeMusic();
					tekst->m_text = " ";

				}
			}break;
			case GameMode::ScoreMode: {}break;
			};

		}
	}

};