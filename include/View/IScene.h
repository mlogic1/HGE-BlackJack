#pragma once

class IScene
{
public:
	IScene() = default;
	IScene(const IScene& other) = delete;
	virtual ~IScene() {};
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
};