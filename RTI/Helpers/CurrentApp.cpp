#include "CurrentApp.h"

CurrentApp* CurrentApp::s_instance = NULL;

Application* CurrentApp::get()
{
    if (!s_instance)
        s_instance = new CurrentApp();

    return s_instance->m_app;
}
void CurrentApp::set(Application * app)
{
    if (!s_instance)
        s_instance = new CurrentApp();

    s_instance->m_app = app;
}

CurrentApp::CurrentApp()
{
    m_app = NULL;
}