#pragma once

#include "Dimon/Core.h"
#include <winsock2.h>
namespace Dimon {
	class ChatServer {

    private:

    public:
        static void Create();
        static ChatServer* Get();
	};
}