/*
  ==============================================================================

    Theme.h
    Created: 28 May 2016 6:40:22pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef THEME_H_INCLUDED
#define THEME_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class Theme;

class Appearence
{
public:
    
    enum Name {
        Space,
        Dusk
    };
    
    static std::shared_ptr<Theme> theme();
    
    static void setTheme(Name name);
    
private:
    
    static std::shared_ptr<Theme> themeInstance;
    
};

class Theme
{
    
public:
    
    enum Level {
        Default,
        Info,
        Primary,
        Warning,
        Error
    };
    
    virtual ~Theme() {}
    
    virtual void label(Label& label, Level level = Default) = 0;
    virtual void field(Label& label, Level level = Default) = 0;
    virtual void indicator(Label& label, Level level = Default) = 0;
    
    virtual void textButton(TextButton& textButton, Level level = Default) = 0;
    
    virtual void paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected, Level level = Default) = 0;
    
    virtual void paintMainBackground (Component& component, Graphics& g) = 0;
    
};

class SpaceTheme : public Theme {
    
public:
    
    // blue dark :
    // blue good : 94 201 201 - 149 253 253 - 122 198 179
    // red warn : 243 109 48 - 250 185 109
    
    
    SpaceTheme();
    
    void label(Label& label, Level level = Default) override;
    void field(Label& label, Level level = Default) override;
    void indicator(Label& label, Level level = Default) override;
    
    void textButton(TextButton& textButton, Level level = Default) override;
    
    void paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected, Level level = Default) override;
    
    void paintMainBackground (Component& component, Graphics& g) override {};
    
private:
    
    Font defaultFont;
    Font boldFont;
    Font titleFont;
    
};


#endif  // THEME_H_INCLUDED
