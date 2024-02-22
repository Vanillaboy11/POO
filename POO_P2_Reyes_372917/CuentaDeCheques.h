#pragma once
#include "Persona.h"
#include <string>
using namespace std;


class CuentaDeCheques
{
protected:
	string owner;
	string accNum;
	int balance;
	string lasTranDate;

public:
	CuentaDeCheques(string num, string ownr, int blnc);

	void depo(int cuan);
	void witd(int cuan);
	void tran(CuentaDeCheques& dest, int amnt);

	void prtbill();

private:
	void actTranDate();

};

