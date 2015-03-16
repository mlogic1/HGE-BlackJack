#include <hge.h>
#include <hgevector.h>

class Card{
private:
    int value;
    HGE *hgep;
    HTEXTURE texture;
    hgeSprite *sprite;
    hgeVector location;


public:

    Card(HGE *hge, int val){
        hgep = hge;
        value = val;
        location.x = 50;
        location.y = 500;
    }


    void LoadTexture(const char* path){
        texture = hgep->Texture_Load(path);
        sprite = new hgeSprite(texture, 0, 0, 500, 726);
    }

    void SetValue(int val){
        value = val;
    }

    int GetValue(){
        return value;
    }


    ~Card(){
        hgep->Texture_Free(texture);
        delete sprite;
    }

    hgeVector GetLocation(){
        return location;
    }

    void SetLocation(hgeVector newloc){
        location = newloc;
    }


    void RenderCard(){
        sprite->RenderEx(location.x, location.y, 0, 0.25f, 0);
    }

    void SetTexture(HTEXTURE texture){
        sprite->SetTexture(texture);
    }

    void SetTexture(const char* path){
        texture = hgep->Texture_Load(path);
        sprite->SetTexture(texture);
    }

    void SetDefaultTexture(){
        sprite->SetTexture(texture);
    }

};
