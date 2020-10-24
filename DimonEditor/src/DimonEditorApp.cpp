#include <Dimon.h>
#include <Dimon/Core/Entry.h>
// Entry Point
#include "EditorLayer.h"

namespace Dimon {
	class DimonEditor : public Application
	{
	public:
		DimonEditor() 
		: Application("GameEngine Dimon"){
			//PushLayer(new  ExampleLeyer());
			PushLayer(new  EditorLayer());
		}
		~DimonEditor() {};
	};

	Application* CreateApplication() {
		return new DimonEditor();
	}
}