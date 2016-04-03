#ifndef _CursorTextField_H_
#define _CursorTextField_H_

#include "cocos2d.h"

USING_NS_CC;

class CursorTextField : public TextFieldTTF, public TextFieldDelegate, public IMEDelegate
{
private:


	// �����ʼλ��
	Point m_beginPos;
	// ��꾫��
	Sprite * m_pCursorSprite;
	// ��궯��
	Action *m_pCursorAction;
	// �������
	Point m_cursorPos;
	//����򳤶�
	float inputFrameWidth;
	//�������������ַ���Unicode
	float inputMaxLength;
	int nLenCount;
	int codeNumType[50];    //ÿ���ַ���Ӧ���ֽ�����
	int codeCur;         //��ǰ�ڼ����ַ�
	int startCur;        //�п�ͷ�ַ��±�
	int endCur;          //��ĩβ�±�
	// �����������
	std::string m_pInputText;
	std::string inpuText; //��ǰ���������
public:
	CursorTextField();
	~CursorTextField();
	// static
	static CursorTextField * textFieldWithPlaceHolder(cocos2d::Node * node, const char *placeholder, const char *fontName, float fontSize);
	// Layer
	void onEnter();
	void onExit();
	bool init();
	// ��ʼ����꾫��
	void initCursorSprite(int nHeight);

	// TextFieldDelegate
	virtual bool onTextFieldAttachWithIME(TextFieldTTF *pSender) override;
	virtual bool onTextFieldDetachWithIME(TextFieldTTF * pSender) override;
	virtual bool onTextFieldInsertText(cocos2d::TextFieldTTF*  sender, const char * text, size_t nLen) override;
	virtual bool onTextFieldDeleteBackward(cocos2d::TextFieldTTF*  sender, const char * delText, size_t nLen) override;



	virtual void setPosition(const Point& pos);
	virtual void setPosition(float &x, float &y);

	void setCursorPositionX(float x); // ���ù��xλ��
	// �ѹ����ӵ��������һ��Ĳ���
	void AddCursor(Node *node);
	// Layer Touch
	bool onTouchBegan(Touch *pTouch, Event *pEvent);
	void onTouchEnded(Touch *pTouch, Event *pEvent);

	// �ж��Ƿ�����TextField��
	bool isInTextField(Touch *pTouch);
	// �õ�TextField����
	Rect getRect();

	// �����뷨
	void openIME();
	// �ر����뷨
	void closeIME();

	std::string split_text(std::string name, int len, int start);

	const char* getInputText();
	void setInpuntText(char* text);
	void setInputWidth(float width);
	void setInputMaxLength(float length);


	cocos2d::Node * parentNode;



protected:
	EventListenerTouchOneByOne * listener;
};

#endif