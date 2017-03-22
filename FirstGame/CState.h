//Cau truc co ban cua mot State (Scene) cho cac State khac ke thua

#ifndef __CSTATE_H__
#define __CSTATE_H__

namespace GameTutor
{
	class CState
	{
	public:
		CState() {}
		virtual ~CState() {}

	public:
		virtual void Init() = 0; //Init State(Scene)
		virtual void Update() = 0; //Update State(Scene) 
		virtual void Render() = 0; //Render State(Scene)
		virtual void Exit() = 0; //Exit State(Scene)
	};
}

#endif 