#pragma once
#include "Object.h"
#include "../Framework/Utils.h"

class VertexArrayObj : public Object
{
protected:
	VertexArray vertexArray;
	Texture* texture;
	Origins origin;

public:
	VertexArrayObj();
	~VertexArrayObj();

	VertexArray& GetVA();
	void SetTexture(Texture* tex);
	Texture* GetTextre() const;
	FloatRect GetGlobalBounds() const;

	void SetOrigin(Origins newOrigin);
	Origins GetOrigin() const;

	virtual void SetPos(const Vector2f& pos);
	virtual const Vector2f& GetPos() const;

	virtual void Draw(RenderWindow& window);


};

