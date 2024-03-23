#include "Application.h"

class CurrentApp
{
public:
    static Application* get();
    static void set(Application* );

protected:

    CurrentApp();

    static CurrentApp* s_instance;

    Application* m_app;
};