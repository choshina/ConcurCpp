#ifndef TINT_H_
#define TINT_H_

class Tint{
private:
	int a;
public:
	Tint(){}
	Tint(int m_a){a = m_a;}
	int get(){return a;}
	void set(int m_a){a = m_a;}
	
};

#endif
