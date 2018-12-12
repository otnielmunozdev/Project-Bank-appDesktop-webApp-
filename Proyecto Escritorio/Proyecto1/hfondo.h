#ifndef HFONDO_H
#define HFONDO_H
#include <QThread>

class HFondo : public QThread
{
    public:
        bool Funcionando;
        HFondo();
        kill();
    private:
        void run();
};

#endif // HFONDO_H
