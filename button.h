#include <hgesprite.h>
#include <hgevector.h>

/* ID's Explained:

1 - Hit Me
2 - Stand
3 - Exit Game

*/

class Button{

private:
    HTEXTURE BTexture;
    HTEXTURE BTextureMouseIn;
    hgeVector location;
    hgeSprite *Sprite;
    HGE *hgep;
    int id;

    // Texturechanged also says if the mouse is inside button
    bool TextureChanged;

public:
    Button(HGE *hge, hgeVector loc, const char* Texture1, const char* Texture2, int _id){
        hgep = hge;
        TextureChanged = false;
        location = loc;
        id = _id;
        std::cout<<"Loading "<<Texture1<<std::endl;
        BTexture = hgep->Texture_Load(Texture1);
        std::cout<<"Loading "<<Texture2<<std::endl;
        BTextureMouseIn = hgep->Texture_Load(Texture2);
        Sprite = new hgeSprite(BTexture, 0, 0, 128, 32);
    }


    void MouseIn(float mouseX, float mouseY){
        if(mouseX >= location.x && mouseX <= location.x + 128  && mouseY >= location.y && mouseY <= location.y + 32){
            if(!TextureChanged){
                Sprite->SetTexture(BTextureMouseIn);
                TextureChanged = true;
            }
        }
    }

    void MouseOut(float mouseX, float mouseY){
        if(mouseX < location.x || mouseX > location.x + 128  || mouseY < location.y || mouseY > location.y + 32){
            if(TextureChanged){
                Sprite->SetTexture(BTexture);
                TextureChanged = false;
            }
        }
    }

    int GetID(){
        return id;
    }

    bool GetState(){
        return TextureChanged;
    }


    ~Button(){
        hgep->Texture_Free(BTexture);
        hgep->Texture_Free(BTextureMouseIn);
        delete Sprite;
    }

    void RenderButton(){
        Sprite->Render(location.x, location.y);
    }
};
