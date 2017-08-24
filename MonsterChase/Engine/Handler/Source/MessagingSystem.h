#include <functional>
#include <vector>
#include "HashedString.h"

namespace Engine
{
	enum Message
	{
		PLAYER_CREATED = 0,
		PLAYER_DESTROYED,
		ACTOR_CREATED,
		ACTOR_DESTROYED,
		COLLISION
	};

	class MessagingSystem
	{
	public:
		MessagingSystem()
		{
			msg.push_back("Player created.\n");
			msg.push_back("Player destroyed.\n");
			msg.push_back("Actor created.\n");
			msg.push_back("Actor destroyed.\n");
			msg.push_back("Collision.\n");
		}

		void AddMessageHandler(const HashedString & i_Message, std::function<void(const HashedString &)> i_Handler, size_t msgIndex)
		{
			// just send it back a test message
			i_Handler(msg[msgIndex]);
		}
	private:
		std::vector<const char *> msg;
	};
}