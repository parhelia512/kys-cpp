#include "Button.h"
#include "Font.h"
#include "TextureManager.h"

Button::Button(const std::string& path, int normal_id, int pass_id /*= -1*/, int press_id /*= -1*/) : Button()
{
    setTexture(path, normal_id, pass_id, press_id);
}

Button::~Button()
{
}

void Button::dealEvent(BP_Event& e)
{
    result_ = -1;
    if (e.type == BP_MOUSEBUTTONUP)
    {
        if (inSide(e.motion.x, e.motion.y))
        {
            result_ = 0;
        }
    }
}

void Button::draw()
{
    //视情况重新计算尺寸
    if (w_ * h_ == 0)
    {
        auto tex = TextureManager::getInstance()->getTexture(texture_path_, texture_normal_id_);
        if (tex)
        {
            w_ = tex->w;
            h_ = tex->h;
        }
    }
    int x = x_;
    int y = y_;
    auto id = texture_normal_id_;
    BP_Color color = { 255, 255, 255, 255 };
    uint8_t alpha = alpha_;
    if (state_ == NodeNormal)
    {
        if (texture_normal_id_ == texture_pass_id_)
        {
            color = { 224, 224, 224, 255 };
        }
    }
    if (state_ == NodePass)
    {
        id = texture_pass_id_;
        alpha = 240;
        x += 2;
    }
    else if (state_ == NodePress)
    {
        id = texture_press_id_;
        alpha = 255;
        x += 2;
        y += 2;
    }
    TextureManager::getInstance()->renderTexture(texture_path_, id, x, y, color, alpha);

    if (!text_.empty())
    {
        BP_Color color_text = color_normal_;
        if (state_ == NodePass)
        {
            color_text = color_pass_;
        }
        else if (state_ == NodePress)
        {
            color_text = color_press_;
        }
        Font::getInstance()->drawWithBox(text_, font_size_, x + text_x_, y + text_y_, color_text, 255, alpha);
    }
}

ButtonGetKey::~ButtonGetKey()
{
}

void ButtonGetKey::dealEvent(BP_Event& e)
{
    if (e.type == BP_KEYUP)
    {
        result_ = e.key.keysym.sym;
        setExit(true);
    }
}
