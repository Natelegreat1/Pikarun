#include "Event.h"

Event::Event() {
}

Event::~Event() {	}

void Event::OnEvent(SDL_Event * e)
{
    switch(e->type) {
        case SDL_ACTIVEEVENT: {
            switch(e->active.state) {
                case SDL_APPMOUSEFOCUS: {
                    if ( e->active.gain )    OnMouseFocus();
                    else OnMouseBlur();
					
                    break;
                }
                case SDL_APPINPUTFOCUS: {
                    if ( e->active.gain )    OnInputFocus();
                    else OnInputBlur();
					
                    break;
                }
                case SDL_APPACTIVE:    {
                    if ( e->active.gain )    OnRestore();
                    else OnMinimize();
					
                    break;
                }
            }
            break;
        }
			
        case SDL_KEYDOWN: {
            OnKeyDown(e->key.keysym.sym,e->key.keysym.mod,e->key.keysym.unicode);
            break;
        }
			
        case SDL_KEYUP: {
            OnKeyUp(e->key.keysym.sym,e->key.keysym.mod,e->key.keysym.unicode);
            break;
        }
			
        case SDL_MOUSEMOTION: {
            OnMouseMove(e->motion.x,e->motion.y,e->motion.xrel,e->motion.yrel,(e->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,(e->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,(e->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
            break;
        }
			
        case SDL_MOUSEBUTTONDOWN: {
            switch(e->button.button) {
                case SDL_BUTTON_LEFT: {
                    OnLButtonDown(e->button.x,e->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    OnRButtonDown(e->button.x,e->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE: {
                    OnMButtonDown(e->button.x,e->button.y);
                    break;
                }
            }
            break;
        }
			
        case SDL_MOUSEBUTTONUP:    {
            switch(e->button.button) {
                case SDL_BUTTON_LEFT: {
                    OnLButtonUp(e->button.x,e->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    OnRButtonUp(e->button.x,e->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE: {
                    OnMButtonUp(e->button.x,e->button.y);
                    break;
                }
            }
            break;
        }
					
        case SDL_QUIT: {
            OnExit();
            break;
        }
			
        case SDL_SYSWMEVENT: {
            //Ignore
            break;
        }
			
        case SDL_VIDEORESIZE: {
            OnResize(e->resize.w,e->resize.h);
            break;
        }
			
        case SDL_VIDEOEXPOSE: {
            OnExpose();
            break;
        }
			
        default: {
            OnUser(e->user.type,e->user.code,e->user.data1,e->user.data2);
            break;
        }
    }
}

void Event::OnInputFocus() {
    //Pure virtual, do nothing
}

void Event::OnInputBlur() {
    //Pure virtual, do nothing
}

void Event::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
    //Pure virtual, do nothing
}

void Event::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
    //Pure virtual, do nothing
}

void Event::OnMouseFocus() {
    //Pure virtual, do nothing
}

void Event::OnMouseBlur() {
    //Pure virtual, do nothing
}

void Event::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle) {
    //Pure virtual, do nothing
}

void Event::OnLButtonDown(int mX, int mY) {
    //Pure virtual, do nothing
}

void Event::OnLButtonUp(int mX, int mY) {
    //Pure virtual, do nothing
}

void Event::OnRButtonDown(int mX, int mY) {
    //Pure virtual, do nothing
}

void Event::OnRButtonUp(int mX, int mY) {
    //Pure virtual, do nothing
}

void Event::OnMButtonDown(int mX, int mY) {
    //Pure virtual, do nothing
}

void Event::OnMButtonUp(int mX, int mY) {
    //Pure virtual, do nothing
}

void Event::OnMinimize() {
    //Pure virtual, do nothing
}

void Event::OnRestore() {
    //Pure virtual, do nothing
}

void Event::OnResize(int w,int h) {
    //Pure virtual, do nothing
}

void Event::OnExpose() {
    //Pure virtual, do nothing
}

void Event::OnExit() {
    //Pure virtual, do nothing
}

void Event::OnUser(Uint8 type, int code, void* data1, void* data2) {
    //Pure virtual, do nothing
}