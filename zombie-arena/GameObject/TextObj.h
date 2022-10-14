#pragma once
#include "Object.h"

class TextObj : public Object
{
protected:
	Text text;

public:
	TextObj();
	virtual ~TextObj();

	Text& GetSfmlText() { return text; }
	virtual void Draw(RenderWindow& window) override;

	void SetFont(Font& font);
	void SetText(string text);
	const string& GetText() const;
};

