#pragma once

class Carte {

private :
	int val;
	int point;

	void setPoint(int newPoint);
	void setVal(int newVal);

public :
	int getPointCarte();
	int getValCarte();
};