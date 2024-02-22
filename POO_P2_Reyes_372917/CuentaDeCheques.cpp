#include "CuentaDeCheques.h"
#include<iostream>
#include<string.h>

CuentaDeCheques::CuentaDeCheques(string num, string ownr, int blnc)
{
    accNum = num;
    owner = ownr;
    balance = blnc;
    time_t tm = time(0);
    lasTranDate = ctime(&tm);
}

void CuentaDeCheques::depo(int cuan)
{
    balance += cuan;
    actTranDate();
}

void CuentaDeCheques::witd(int cuan)
{
    balance -= cuan;
    actTranDate();
}

CuentaDeCheques::CuentaDeCheques(string num, string ownr, int blnc)
{
}

void CuentaDeCheques::prtbill()
{
    cout << "Numero de cuenta: " << accNum << endl;
    cout << "Propietario: " << owner << endl;
    cout << "Saldo: " << balance << endl;
    cout << "Fecha de la ultima transaccion: " << lasTranDate << endl;
}

void CuentaDeCheques::tran(CuentaDeCheques& dest, int cuan)
{
    if (cuan <= balance) {
        balance -= cuan;
        dest.witd(cuan);
        actTranDate();
        dest.actTranDate();
    }
    else {
        cout << "Saldo insuficiente para transferencia." << endl;
    }
}

void CuentaDeCheques::actTranDate()
{
    time_t tm = time(0);
    lasTranDate = ctime(&tm);
}
